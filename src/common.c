#include <common.h>
#include <string.h>
#include <pwd.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

const char* getFilename(const char* url) {
    const char* last_slash = strrchr(url, '/');
    if (last_slash) return last_slash + 1;
    return url;
}

const char* remove7zExt(const char* filename) {
    // Duplicate the filename so it's writable
    char* modifiable_filename = strdup(filename);
    if (modifiable_filename == NULL) { return NULL; }
    
    size_t len = strlen(modifiable_filename);
    if (len > 3) modifiable_filename[len - 3] = '\0';
    
    return modifiable_filename;
}

const char* getUsername() {
    struct passwd *pw = getpwuid(geteuid());
    if (pw) return pw->pw_name;
    return "?";
}

const char* getCacheFolder() {
    char folder[100];
    snprintf(folder, 100, "/home/%s/.snbox", getUsername());
}

void createCacheFolder() {
    const char* folder = getCacheFolder();
    struct stat st = {0};
    if (stat(folder, &st) == -1) {
        mkdir(folder, 0700);
    }
}