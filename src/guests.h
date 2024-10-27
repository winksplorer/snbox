#ifndef SNBOX_GUESTS_H
#define SNBOX_GUESTS_H

#include <stdbool.h>

typedef enum OperatingSystem {
    WIN3,

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
    OperatingSystem os;
    char* hdd_url;
    short cpu_cores;
    int ram_size;
    bool amd64;
    enum QemuVga vga;
    bool compressed_hdd;
} Guest;

Guest getGuest(const char* name);
OperatingSystem getOS(const char* name);
const char* osName(OperatingSystem os);
#endif