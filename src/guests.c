#include <guests.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

Guest getGuest(const char* name) {
    Guest g;
    g.os = getOS(name);
    switch (g.os) {
        case WIN3:
            g.cpu_cores = 1; g.ram_size = 16; g.amd64 = false; g.vga = STANDARD; g.compressed_hdd = false;
            g.hdd_url = "https://winksplorer.net/snbox/win3.qcow2";
            break;
        case WINNT4:
            g.cpu_cores = 1; g.ram_size = 64; g.amd64 = false; g.vga = CIRRUS; g.compressed_hdd = true;
            g.hdd_url = "https://winksplorer.net/snbox/winnt4.qcow2.7z";
            break;
        case WIN2K:
            g.cpu_cores = 1; g.ram_size = 256; g.amd64 = false; g.vga = CIRRUS; g.compressed_hdd = false;
            g.hdd_url = "https://winksplorer.net/snbox/win2k.qcow2";
            break;
        case WINXP:
            g.cpu_cores = 2; g.ram_size = 512; g.amd64 = false; g.vga = CIRRUS; g.compressed_hdd = false;
            g.hdd_url = "https://winksplorer.net/snbox/winxp.qcow2";
            break;
        case WINVISTA:
            g.cpu_cores = 2; g.ram_size = 512; g.amd64 = true; g.vga = CIRRUS; g.compressed_hdd = false;
            g.hdd_url = "https://winksplorer.net/snbox/winvista.qcow2";
            break;
        case DEBIANBOOKWORM:
            g.cpu_cores = 2; g.ram_size = 1024; g.amd64 = true; g.vga = VIRTIO; g.compressed_hdd = false;
            g.hdd_url = "https://winksplorer.net/snbox/debianbookworm.qcow2";
            break;
        case REACTOS:
            g.cpu_cores = 1; g.ram_size = 512; g.amd64 = false; g.vga = STANDARD; g.compressed_hdd = false;
            g.hdd_url = "https://winksplorer.net/snbox/reactos.qcow2";
            break;
        case OS2W4:
            g.cpu_cores = 1; g.ram_size = 256; g.amd64 = false; g.vga = STANDARD; g.compressed_hdd = false;
            g.hdd_url = "https://winksplorer.net/snbox/os2w4.qcow2";
            break;
        default:
            errno = EINVAL;
            Guest ERR; g.os = NONE;
            return ERR;
    }
    return g;
}

OperatingSystem getOS(const char* name) {
    if (!strcmp(name, "win3")) return WIN3;

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

    else if (!strcmp(name, "winvista") ||
        !strcmp(name, "vista")) return WINVISTA;

    else if (!strcmp(name, "debianbookworm") ||
        !strcmp(name, "debian12") ||
        !strcmp(name, "deb12") ||
        !strcmp(name, "debbookworm")) return DEBIANBOOKWORM;

    else if (!strcmp(name, "reactos") || !strcmp(name, "ros")) return REACTOS;

    else if (!strcmp(name, "os/2") ||
        !strcmp(name, "os2") ||
        !strcmp(name, "os2warp4") ||
        !strcmp(name, "os/2warp4") ||
        !strcmp(name, "os2w4") ||
        !strcmp(name, "os/2w4")) return OS2W4;
    
    else return NONE;
}

const char* osName(OperatingSystem os) {
    switch (os) {
        case WIN3:
            return "Microsoft Windows 3.1";
        case WINNT4:
            return "Microsoft Windows NT 4.0 Workstation SP1";
        case WIN2K:
            return "Microsoft Windows 2000";
        case WINXP:
            return "Microsoft Windows XP Professional SP3";
        case WINVISTA:
            return "Microsoft Windows Vista Ultimate";
        case DEBIANBOOKWORM:
            return "Debian 12.7 Bookworm";
        case REACTOS:
            return "ReactOS 0.4.14";
        case OS2W4:
            return "IBM OS/2 Warp 4.52";
        default:
            return "?";
    }
}