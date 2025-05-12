#ifndef SNBOX_GUESTS_H
#define SNBOX_GUESTS_H

#include <stdbool.h>

typedef enum OperatingSystem {
    NONE,
    
    DOS5,
    WIN3,

    WINNT4,
    WIN2K,
    WINXP,

    HAIKU
} OperatingSystem;

typedef enum QemuVga {
    STANDARD,
    CIRRUS,
    VMWARE,
    QXL,
    VIRTIO,
} QemuVga;

typedef struct Guest {
    OperatingSystem os; // OS
    char* hdd_url; // URL to the compressed qcow2 image
    short cpu_cores; // Amount of SMP CPU cores
    int ram_size; // Memory size in MB
    bool amd64; // x64 support
    enum QemuVga vga; // Video card
} Guest;

Guest getGuest(const char* name);
OperatingSystem getOS(const char* name);
const char* osName(OperatingSystem os);
#endif