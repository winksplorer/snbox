#include "extract.h"
#include "common.h"

#include <archive.h>
#include <archive_entry.h>

int extract7z(const char* filename) {
    struct archive* a = archive_read_new();
    struct archive* ext = archive_write_disk_new();
    struct archive_entry* entry;

    archive_read_support_format_7zip(a);
    archive_read_support_filter_lzma(a);
    archive_write_disk_set_options(ext, ARCHIVE_EXTRACT_TIME);

    int r = archive_read_open_filename(a, filename, 10240);
    if (r != ARCHIVE_OK) {
        fprintf(stderr, "snbox: extraction error: opening archive failed: %s\n", archive_error_string(a));
        return r;
    }

    if (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        char path[256];
        #if __APPLE__
        snprintf(path, sizeof(path), "/Users/%s/Library/Application Support/snbox/%s", getUsername(), archive_entry_pathname(entry));
        #else
        snprintf(path, sizeof(path), "/home/%s/.snbox/%s", getUsername(), archive_entry_pathname(entry));
        #endif
        archive_entry_set_pathname(entry, path);

        r = archive_write_header(ext, entry);
        if (r != ARCHIVE_OK) {
            fprintf(stderr, "snbox: extraction error: header write failed: %s\n", archive_error_string(ext));
        } else {
            const void* buff;
            size_t size;
            la_int64_t offset;

            while (1) {
                r = archive_read_data_block(a, &buff, &size, &offset);
                if (r == ARCHIVE_EOF) break;
                if (r != ARCHIVE_OK) return r;

                r = archive_write_data_block(ext, buff, size, offset);
                if (r != ARCHIVE_OK) {
                    fprintf(stderr, "snbox: extraction error: write failed: %s\n", archive_error_string(ext));
                    return r;
                }
            }
        }
    }

    archive_read_close(a);
    archive_read_free(a);
    archive_write_close(ext);
    archive_write_free(ext);
    return 0;
}
