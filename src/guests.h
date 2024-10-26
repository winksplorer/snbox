#ifndef SNBOX_GUESTS_H
#define SNBOX_GUESTS_H

typedef enum OperatingSystem {
    WIN1,
    WIN3,
    WIN95,

    WINNT4,
    WIN2K,
    WINXP,
    WINVISTA,

    DEBIANBOOKWORM,
    REACTOS,
    OS2W4,
    NONE
} OperatingSystem;

typedef struct Guest {
    enum OperatingSystem os;
    int ram_size;
    short cpu_cores;
    char* hdd_url;
} Guest;

Guest getGuest(const char* name);
OperatingSystem getOS(const char* name);
#endif