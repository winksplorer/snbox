#include "common.h"

#include <string.h>
#include <pwd.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

/* Gets the filename from a URL or path. */
const char* getFilename(const char* url) {
    const char* last_slash = strrchr(url, '/');
    if (last_slash) return last_slash + 1;
    return url;
}

/* Removes last 3 characters of a string. */
const char* remove7zExt(const char* filename) {
    char* modifiable_filename = strdup(filename);
    if (!modifiable_filename) return NULL;
    
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

/* Creates ~/.snbox if it doesn't exist. */
void createCacheFolder(void) {
    char* folder = malloc(100);
    #if __APPLE__
    snprintf(folder, 100, "/Users/%s/Library/Application Support/snbox", getUsername());
    #else
    snprintf(folder, 100, "/home/%s/.snbox", getUsername());
    #endif

    struct stat st = {0};
    if (stat(folder, &st) == -1)  mkdir(folder, 0700);
    free(folder);
}

/* Checks a variety of strings (anything past s1) against s1. */
int anystrcmp(const char* s1, ...)
{
    va_list ap;
    va_start(ap, s1);
    char* alias;
    while ((alias = va_arg(ap, char*)))
        if (!strcmp(s1, alias)) {
            va_end(ap);
            return 0;
        }
    va_end(ap);
    return 1;
}

/* Adds arguments to a char** argv, and increments an index i. */
void strarr_add(char** argv, int* i, ...) {
    va_list ap;
    va_start(ap, i);
    const char* arg;
    while ((arg = va_arg(ap, const char*)) != NULL)
        argv[(*i)++] = (char*)arg;
    va_end(ap);
}

/* A simple printf wrapper. This causes a memory leak if you don't free() it's output.
 * snbox doesn't free this, since it execvp's almost immediately, so it doesn't really matter.
 */
char* fmt(const char* fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    char* out;
    vasprintf(&out, fmt, ap);
    va_end(ap);
    return out;
}