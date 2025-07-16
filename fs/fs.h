#include <storage/storage.h>
#include <toolbox/stream/stream.h>
#include <toolbox/stream/file_stream.h>

typedef struct FileStorage {
    Storage* storage;
    int max_len;
    char** files;
    uint16_t files_len;
} FileStorage;


// Allocate and create file storage
FileStorage* allocate_file_storage();


// Free file storage
void free_file_storage(FileStorage* fs);

// Reads contents of dir
void get_file_names(FileStorage* fs);
