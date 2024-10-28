#include <common.h>
#include <string.h>
#include <pwd.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

/* Gets the filename from a URL or path. */
const char* getFilename(const char* url) {
    const char* last_slash = strrchr(url, '/');
    if (last_slash) return last_slash + 1;
    return url;
}

/* Removes last 3 characters of a string. */
const char* remove7zExt(const char* filename) {
    // Duplicate the filename so it's writable
    char* modifiable_filename = strdup(filename);
    if (modifiable_filename == NULL) { return NULL; }
    
    size_t len = strlen(modifiable_filename);
    if (len > 3) modifiable_filename[len - 3] = '\0';
    
    return modifiable_filename;
}

/* Gets UNIX username. */
const char* getUsername(void) {
    struct passwd *pw = getpwuid(geteuid());
    if (pw) return pw->pw_name;
    return "?";
}

/* Creates ~/.snbox if it doesn't exist */
void createCacheFolder(void) {
    char* folder = malloc(100);
    snprintf(folder, 100, "/home/%s/.snbox", getUsername());

    struct stat st = {0};
    if (stat(folder, &st) == -1) {
        mkdir(folder, 0700);
    }

    free(folder);
}