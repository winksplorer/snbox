#include <stdio.h>
#include <guests.h>
#include <errno.h>
#include <download.h>
#include <run.h>
#include <extract.h>
#include <common.h>

int main(int argc, char* argv[]) {
    printf("snbox 0.3 (%s %s)\nmade by winksplorer, licensed under MPL-2.0\n\n", __DATE__, __TIME__);
    createCacheFolder();

    if (argc == 1) printf("usage: snbox [os]\nruns a pre-installed QEMU VM. With no [os], it will print this message.\npossible operaing systems:\n\nwin3    Microsoft Windows 3.1\nwinnt4  Microsoft Windows NT 4.0 Workstation SP1\nwin2k   Microsoft Windows 2000\nwinxp   Microsoft Windows XP Professional SP3\nvista   Microsoft Windows Vista Ultimate\ndeb12   Debian 12.7 Bookworm\nreactos ReactOS 0.4.14\nos/2    IBM OS/2 Warp 4.52\n");

    else if (argc == 2) {
        Guest g = getGuest(argv[1]);
        if (g.os == NONE){
            perror("snbox: invalid guest");
            return errno;
        }
        printf("selected \"%s\"\n", osName(g.os));
        printf("%s", remove7zExt(getFilename(g.hdd_url)));
        return 0;

        if (g.compressed_hdd) {
            if (downloadFile(g.hdd_url, "snbox.qcow2.7z")) {
                perror("snbox: download failed");
                return errno;
            }
            printf("downloaded compressed hdd\n");

            if (extract_7z("snbox.qcow2.7z")) {
                perror("snbox: extraction failed");
                return errno;
            }
            printf("extracted hdd\n");
        } else {
            if (downloadFile(g.hdd_url, "snbox.qcow2")) {
                perror("snbox: download failed");
                return errno;
            }
            printf("downloaded hdd\n");
        }
        //run(g);
    }
}