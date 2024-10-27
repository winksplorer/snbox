#include <stdio.h>
#include <guests.h>
#include <errno.h>
#include <download.h>
#include <run.h>

int main(int argc, char* argv[]) {
    printf("snbox 0.1\n");
    if (argc == 1) printf("Usage: snbox [os]\nRuns a pre-installed QEMU VM. With no [os], it will print this message.\nPossible operaing systems:\n\nwin3    Microsoft Windows 3.1\nwin95   Microsoft Windows 95\nwinnt4  Microsoft Windows NT 4 Workstation SP6\nwin2k   Microsoft Windows 2000\nwinxp   Microsoft Windows XP Professional SP3\nvista   Microsoft Windows Vista Ultimate\ndeb12   Debian 12.7 Bookworm\nreactos ReactOS 0.4.14\nos/2    IBM OS/2 Warp 4.52\n");

    else if (argc == 2) {
        Guest g = getGuest(argv[1]);
        downloadFile(g.hdd_url, "snbox.qcow2");
        printf("a");
        run(g);
    }
}