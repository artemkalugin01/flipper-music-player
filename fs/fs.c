#include <storage/storage.h>
#include <toolbox/stream/stream.h>
#include <toolbox/stream/file_stream.h>

#include "fs.h"

#define FS_TAG "MusicPlayer [FS]"

FileStorage* allocate_file_storage(){
    FileStorage* fs = malloc(sizeof(FileStorage));

    // Storage open
    fs->storage = furi_record_open(RECORD_STORAGE);
    fs->max_len = 200; // too small actually

    fs->files = (char**)malloc(sizeof(char) * (fs->max_len + 1));
    fs->dirs = (char**)malloc(sizeof(char) * (fs->max_len + 1));
    fs->files_len = 0;
    fs->dirs_len = 0;

    return fs;
}


void free_file_storage(FileStorage* fs){
    // Close storage
    furi_record_close(RECORD_STORAGE);
    free(fs->files);
    free(fs->dirs);
}

void read_dir(FileStorage* fs, char* path){
    File* assets_dir = storage_file_alloc(fs->storage);
    FURI_LOG_I(FS_TAG, "Opening \"%s\"...", path);

    if(storage_dir_open(assets_dir, path)) {
        FURI_LOG_I(FS_TAG, "\"%s\"... sucessfully opened", path);

        FileInfo file_info;
        // for the name of the next found file
        char* name_buff = malloc(fs->max_len * sizeof(char));
        uint16_t buf_len = 0;

        // Read all the files in a folder
        while(true) {
            if(storage_dir_read(assets_dir, &file_info, name_buff, fs->max_len)) {
                if(file_info_is_dir(&file_info)) {
                    FURI_LOG_I(FS_TAG, "Directory found: \"%s\"", name_buff);

                    buf_len = strlen(name_buff) + 1;

                    fs->dirs[fs->dirs_len] =
                        malloc(buf_len * sizeof(char));
                    memcpy(
                        fs->dirs[fs->dirs_len],
                        name_buff,
                        buf_len);
                    fs->dirs_len++;
                } else {
                    FURI_LOG_I(FS_TAG, "File found: \"%s\"", name_buff);

                    // Сохраняем имя файла для дальнейшего использования
                    buf_len = strlen(name_buff) + 1;

                    fs->files[fs->files_len] =
                        malloc(buf_len * sizeof(char));
                    memcpy(
                        fs->files[fs->files_len],
                        name_buff,
                        buf_len);
                    fs->files_len++;
                }
            } else {
                FURI_LOG_E(FS_TAG, "error while reading files from \"%s\"", path);
                break;
            }
        }

        free(name_buff);

    } else {
        FURI_LOG_I(FS_TAG, "error while openning \"%s\"", path);
    }

    storage_dir_close(assets_dir);
    storage_file_free(assets_dir);

}
