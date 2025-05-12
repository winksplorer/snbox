#include "common.h"
#include "download.h"
#include "extract.h"
#include "run.h"

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

/* Entry point. */
int main(int argc, char* argv[]) {
    printf("snbox 0.6 (%s %s)\nmade by winksplorer, licensed under MPL-2.0\n\n", __DATE__, __TIME__);
    createCacheFolder();

    if (argc == 1) printf("usage: snbox [os]\nruns a pre-installed QEMU VM. with no [os], it will print this message.\npossible operating systems:\n\ndos5    Microsoft MS-DOS 5.00\nwin3    Microsoft Windows 3.1\nwinnt4  Microsoft Windows NT 4.0 Workstation SP6\nwin2k   Microsoft Windows 2000 Professional SP4\nwinxp   Microsoft Windows XP Professional SP3 x86\nhaiku   Haiku OS r1beta5\n");

    else if (argc == 2) {
        Guest g = getGuest(argv[1]);
        if (!g.os){
            perror("snbox: invalid guest");
            return errno;
        }
        printf("selected \"%s\"\n", osName(g.os));

        char hdd_path[100];
        char* archive_path = malloc(50);

        // archive_path is the path to the compressed hdd, such as /tmp/haiku.qcow2.7z
        // hdd_path is the path to the UNcompressed (and cached) hdd, such as /home/wink/.snbox/haiku.qcow2

        snprintf(archive_path, 50, "/tmp/%s", getFilename(g.hdd_url));
        #if __APPLE__ // macOS
        snprintf(hdd_path, 100, "/Users/%s/Library/Application Support/snbox/%s", getUsername(), remove7zExt(getFilename(g.hdd_url)));
        #else // Literally anything else
        snprintf(hdd_path, 100, "/home/%s/.snbox/%s", getUsername(), remove7zExt(getFilename(g.hdd_url)));
        #endif

        if (!access(archive_path, F_OK)) remove(archive_path); // Remove archive if it already exists
        if (access(hdd_path, F_OK)) {
            // Download VM HDD
            printf("downloading compressed hdd... ");
            fflush(stdout);
            // "before" is unix epoch, so we can time download speeds
            unsigned long before = time(NULL);
            if (downloadFile(g.hdd_url, archive_path)) {
                perror("snbox: download failed");
                return errno;
            }
            // measure amount of seconds since "before", use ANSI code 32m for green
            printf("\033[32m%lus\033[0m\n", time(NULL)-before);

            // decompress VM HDD
            printf("decompressing hdd... ");
            fflush(stdout);
            // "before" is unix epoch, so we can time download speeds
            before = time(NULL);
            if (extract7z(archive_path)) {
                perror("snbox: extraction failed");
                return errno;
            }
            // measure amount of seconds since "before", use ANSI code 32m for green
            printf("\033[32m%lus\033[0m\n", time(NULL)-before);

            remove(archive_path);
        }

        free(archive_path);
        run(g, hdd_path);
    }
}