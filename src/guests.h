#ifndef SNBOX_GUESTS_H
#define SNBOX_GUESTS_H

#include <stdbool.h>

typedef enum OperatingSystem {
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

typedef enum QemuVga {
    STANDARD,
    CIRRUS,
    VMWARE,
    QXL,
    VIRTIO,
} QemuVga;

typedef struct Guest {
    enum OperatingSystem os;
    int ram_size;
    short cpu_cores;
    char* hdd_url;
    enum QemuVga vga;
    bool amd64;
} Guest;

Guest getGuest(const char* name);
OperatingSystem getOS(const char* name);
#endif