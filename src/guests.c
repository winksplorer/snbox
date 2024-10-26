#include <guests.h>
#include <string.h>
#include <errno.h>

Guest getGuest(const char* name) {
    Guest g;
    g.os = getOS(name);
    switch (g.os) {
        case WIN1:
            g.cpu_cores = 1; g.ram_size = 4;
            g.hdd_url = "https://winksplorer.net/snbox/win1.qcow2";
            break;
        case WIN3:
            g.cpu_cores = 1; g.ram_size = 12;
            g.hdd_url = "https://winksplorer.net/snbox/win3.qcow2";
            break;
        case WIN95:
            g.cpu_cores = 1; g.ram_size = 32;
            g.hdd_url = "https://winksplorer.net/snbox/win95.qcow2";
            break;
        case WINNT4:
            g.cpu_cores = 1; g.ram_size = 32;
            g.hdd_url = "https://winksplorer.net/snbox/winnt4.qcow2";
            break;
        case WIN2K:
            g.cpu_cores = 1; g.ram_size = 256;
            g.hdd_url = "https://winksplorer.net/snbox/win2k.qcow2";
            break;
        case WINXP:
            g.cpu_cores = 2; g.ram_size = 512;
            g.hdd_url = "https://winksplorer.net/snbox/winxp.qcow2";
            break;
        case WINVISTA:
            g.cpu_cores = 2; g.ram_size = 512;
            g.hdd_url = "https://winksplorer.net/snbox/winvista.qcow2";
            break;
        case DEBIANBOOKWORM:
            g.cpu_cores = 2; g.ram_size = 1024;
            g.hdd_url = "https://winksplorer.net/snbox/debianbookworm.qcow2";
            break;
        case REACTOS:
            g.cpu_cores = 1; g.ram_size = 512;
            g.hdd_url = "https://winksplorer.net/snbox/reactos.qcow2";
            break;
        case OS2W4:
            g.cpu_cores = 1; g.ram_size = 256;
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
    if (!strcmp(name, "win1")) return WIN1;

    else if (!strcmp(name, "win3")) return WIN3;

    else if (!strcmp(name, "win95")) return WIN95;

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