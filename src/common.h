#ifndef SNBOX_COMMON_H
#define SNBOX_COMMON_H

const char* getFilename(const char* url);
const char* remove7zExt(const char* filename);
const char* getUsername(void);
void createCacheFolder(void);

#endif