#include "guests.h"

#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include "common.h"

/* 
 * Creates a guest structure from an OS name. 
 * This is also where you define guest configurations.
 */
Guest getGuest(const char* name) {
    Guest g;
    g.os = getOS(name);
    switch (g.os) {
        case DOS5:
            g.cpu_cores = 1; g.ram_size = 16; g.amd64 = false; g.vga = STANDARD;
            g.hdd_url = "https://winksplorer.net/snbox/dos5.qcow2.7z";
            break;
        case WIN3:
            g.cpu_cores = 1; g.ram_size = 16; g.amd64 = false; g.vga = STANDARD;
            g.hdd_url = "https://winksplorer.net/snbox/win3.qcow2.7z";
            break;
        case WINNT4:
            g.cpu_cores = 1; g.ram_size = 64; g.amd64 = false; g.vga = CIRRUS;
            g.hdd_url = "https://winksplorer.net/snbox/winnt4.qcow2.7z";
            break;
        case WIN2K:
            g.cpu_cores = 1; g.ram_size = 256; g.amd64 = false; g.vga = CIRRUS;
            g.hdd_url = "https://winksplorer.net/snbox/win2k.qcow2.7z";
            break;
        case WINXP:
            g.cpu_cores = 2; g.ram_size = 512; g.amd64 = false; g.vga = QXL;
            g.hdd_url = "https://winksplorer.net/snbox/winxp.qcow2.7z";
            break;
        case HAIKU:
            g.cpu_cores = 2; g.ram_size = 768; g.amd64 = true; g.vga = QXL;
            g.hdd_url = "https://winksplorer.net/snbox/haiku.qcow2.7z";
            break;
        default:
            errno = EINVAL;
            return g;
    }
    return g;
}

/* Returns the OperatingSystem enum representation of an OS. */
OperatingSystem getOS(const char* name) {
    if (!anystrcmp(name, "dos5", "dos", "msdos", "msdos5", "ms-dos", "ms-dos5", NULL)) return DOS5;
    else if (!strcmp(name, "win3")) return WIN3;
    else if (!anystrcmp(name, "winnt4", "winnt", "nt4", "nt", NULL)) return WINNT4;
    else if (!anystrcmp(name, "win2k", "win2000", "2k", "2000", NULL)) return WIN2K;
    else if (!anystrcmp(name, "winxp", "xp", NULL)) return WINXP;
    else if (!anystrcmp(name, "haiku", "haikuos", NULL)) return HAIKU;
    else return NONE;
}

/* Returns the display name of an OperatingSystem. */
const char* osName(OperatingSystem os) {
    switch (os) {
        case DOS5: return "Microsoft MS-DOS 5.00";
        case WIN3: return "Microsoft Windows 3.1";
        case WINNT4: return "Microsoft Windows NT 4.0 Workstation SP6";
        case WIN2K: return "Microsoft Windows 2000 Professional SP4";
        case WINXP: return "Microsoft Windows XP Professional SP3 x86";
        case HAIKU: return "Haiku OS r1beta5";
        default: return "?";
    }
}