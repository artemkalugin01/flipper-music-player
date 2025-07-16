#include <stdio.h>
#include <storage/storage.h>
#include <toolbox/stream/stream.h>
#include <toolbox/stream/file_stream.h>

#include "fs.h"
#include "core/core_defines.h"
#include "core/log.h"

#define FS_TAG "MusicPlayer [FS]"
#define FS_PATH "/ext/apps_data/Development/music_player"

#define MAX_SUPPORTED_FILES 50

FileStorage* allocate_file_storage() {
    FileStorage* fs = malloc(sizeof(FileStorage));
    if(fs == NULL) {
        FURI_LOG_E(FS_TAG, "Failed to allocate FileStorage struct");
        return NULL;
    }

    fs->storage = furi_record_open(RECORD_STORAGE);

    // max length of filename
    fs->max_len = 256;

    fs->files = malloc(MAX_SUPPORTED_FILES * sizeof(char*));
    if(fs->files == NULL) {
        FURI_LOG_E(FS_TAG, "Failed to allocate file list array");
        free(fs); 
        return NULL;
    }

    fs->files_len = 0; 

    return fs;
}

void free_file_storage(FileStorage* fs) {
    if(fs == NULL) {
        return;
    }
    // Close storage
    furi_record_close(RECORD_STORAGE);

    if(fs->files != NULL) {
        for(uint16_t i = 0; i < fs->files_len; i++) {
            if(fs->files[i] != NULL) {
                free(fs->files[i]);
            }
        }
        free(fs->files);
    }
    free(fs);
}

void get_file_names(FileStorage* fs) {
    /*
    if(fs == NULL || fs->storage == NULL || fs->files == NULL) {
        FURI_LOG_E(FS_TAG, "get_file_names received invalid FileStorage");
        FURI_LOG_E(FS_TAG, "fs is null %d", fs == NULL);
        FURI_LOG_E(FS_TAG, "fs->storage is null %d", fs->storage == NULL);
        FURI_LOG_E(FS_TAG, "fs->files is null %d", fs->files == NULL);
        return;
    }
    */

   File* assets_dir = storage_file_alloc(fs->storage);
    FURI_LOG_I(FS_TAG, "Opening \"%s\"...", FS_PATH);

    if(storage_dir_open(assets_dir, FS_PATH)) {
        FURI_LOG_I(FS_TAG, "\"%s\"... sucessfully opened", FS_PATH);

        FileInfo file_info;
        // for the name of the next found file
        char* name_buff = malloc(fs->max_len * sizeof(char));
        uint16_t buf_len = 0;

        // Read all the files in a folder
        while(true) {
            if(storage_dir_read(assets_dir, &file_info, name_buff, fs->max_len)) {
                {
                    FURI_LOG_I(FS_TAG, "File found: \"%s\"", name_buff);

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
                FURI_LOG_I(FS_TAG, "finished reading files from \"%s\"", FS_PATH);
                break;
            }
        }

        free(name_buff);

    } else {
        FURI_LOG_E(FS_TAG, "error while openning \"%s\"", FS_PATH);
    }

    storage_dir_close(assets_dir);
    storage_file_free(assets_dir);
}
