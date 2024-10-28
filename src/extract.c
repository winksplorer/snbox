#include <extract.h>
#include <archive.h>
#include <archive_entry.h>
#include <common.h>

/* Helper function for extract_7z. */
int copyData(struct archive* ar, struct archive* aw) {
    const void* buff;
    size_t size;
    la_int64_t offset;
    int r;

    while (1) {
        r = archive_read_data_block(ar, &buff, &size, &offset);
        if (r == ARCHIVE_EOF)
            return ARCHIVE_OK;
        if (r != ARCHIVE_OK)
            return r;
        r = archive_write_data_block(aw, buff, size, offset);
        if (r != ARCHIVE_OK) {
            fprintf(stderr, "snbox: extraction error: write failed: %s\n", archive_error_string(aw));
            return r;
        }
    }
}

/* Extracts a 7zip archive to ~/.snbox. */
int extract7z(const char *filename) {
    struct archive_entry* entry;

    struct archive* a = archive_read_new();
    struct archive* ext = archive_write_disk_new();

    archive_read_support_format_7zip(a);
    archive_read_support_compression_all(a);
    archive_write_disk_set_options(ext, ARCHIVE_EXTRACT_TIME);

    int r = archive_read_open_filename(a, filename, 10240);
    if (r != ARCHIVE_OK) {
        fprintf(stderr, "snbox: extraction error: opening archive failed: %s\n", archive_error_string(a));
        return r;
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        char path[100];
        snprintf(path, 100, "/home/%s/.snbox/%s", getUsername(), archive_entry_pathname(entry));
        archive_entry_set_pathname(entry, path);

        r = archive_write_header(ext, entry);
        if (r != ARCHIVE_OK) fprintf(stderr, "snbox: extraction error: header write failed: %s\n", archive_error_string(ext));
        else {
            copyData(a, ext);
            archive_write_finish_entry(ext);
        }
    }

    archive_read_close(a);
    archive_read_free(a);
    archive_read_close(ext);
    archive_read_free(ext);
    return 0;
}