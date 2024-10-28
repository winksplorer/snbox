#include <guests.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

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
    if (!strcmp(name, "dos5") ||
        !strcmp(name, "dos") ||
        !strcmp(name, "msdos") ||
        !strcmp(name, "msdos5") ||
        !strcmp(name, "ms-dos") ||
        !strcmp(name, "ms-dos5")) return DOS5;

    else if (!strcmp(name, "win3")) return WIN3;

    else if (!strcmp(name, "winnt4") ||
        !strcmp(name, "winnt") ||
        !strcmp(name, "nt4") ||
        !strcmp(name, "nt")) return WINNT4;

    else if (!strcmp(name, "win2k") ||
        !strcmp(name, "win2000") ||
        !strcmp(name, "2k") ||
        !strcmp(name, "2000")) return WIN2K;

    else if (!strcmp(name, "winxp") ||
        !strcmp(name, "xp")) return WINXP;

    else if (!strcmp(name, "haikuos") || !strcmp(name, "haiku")) return HAIKU;
    
    else return NONE;
}

/* Returns the display name of an OperatingSystem. */
const char* osName(OperatingSystem os) {
    switch (os) {
        case DOS5:
            return "Microsoft MS-DOS 5.00";
        case WIN3:
            return "Microsoft Windows 3.1";
        case WINNT4:
            return "Microsoft Windows NT 4.0 Workstation SP6";
        case WIN2K:
            return "Microsoft Windows 2000 Professional SP4";
        case WINXP:
            return "Microsoft Windows XP Professional SP3 x86";
        case HAIKU:
            return "Haiku OS r1beta5";
        default:
            return "?";
    }
}