#include "run.h"
#include "guests.h"

#include <stdio.h>
#include <unistd.h>

/* Runs a guest in QEMU. */
void run(Guest g, const char* hdd) {
    char qemu_cmd[20];

    char* vga;
    switch (g.vga) {
        case STANDARD:
            vga = "std";
            break;
        case CIRRUS:
            vga = "cirrus";
            break;
        case VMWARE:
            vga = "vmware";
            break;
        case QXL:
            #if __APPLE__ // No QXL on macOS, fallback to cirrus
            vga = "cirrus";
            #else // Literally anything else
            vga = "qxl";
            #endif
            break;
        case VIRTIO:
            vga = "virtio";
            break;
    }

    snprintf(qemu_cmd, 20, "qemu-system-%s", g.amd64 ? "x86_64" : "i386");

    char* argv[21];

    argv[0] = qemu_cmd;

    // cpu cores
    argv[1] = "-smp";
    char cores[2];
    snprintf(cores, 2, "%d", g.cpu_cores);
    argv[2] = cores;

    // memory
    argv[3] = "-m";
    char mem[5];
    snprintf(mem, 5, "%d", g.ram_size);
    argv[4] = mem;

    // HDD
    argv[5] = "-drive";
    char drive[100];
    snprintf(drive, 100, "file=%s,format=qcow2", hdd);
    argv[6] = drive;

    // video
    argv[7] = "-vga";
    argv[8] = vga;

    // important, so qemu doesn't save changes to the cached hdd
    argv[9] = "-snapshot";

    // accelerator
    argv[10] = "-accel";

    #if defined(__arm64__) || defined(__aarch64__)
        // you cannot accel x86 qemu on arm.
        argv[11] = "tcg";
    #else // assume x86
        #if __APPLE__ // macOS
        argv[11] = "hvf";
        #else // Literally anything else
        argv[11] = "kvm";
        #endif
    #endif
    
    // OS-specific switches
    if (g.os == WINNT4) {
        /* Windows NT 4.0 quirks:
         * 1. Requires pentium3 cpu option
         * 2. Cannot be accelerated
         */
        argv[10] = "-cpu";
        argv[11] = "pentium3";
        argv[12] = NULL;
    } else if (g.os == WINXP) {
        /* Windows XP quirks:
         * 1. Not sure, but tablet usbdevice seems to get the mouse working when using virtio-win QXL driver
         * 2. Even then, Ctrl+Alt+G'ing in QEMU breaks the mouse until you release
         * 3. AC97 is required for audio
         */
        argv[12] = "-usbdevice";
        argv[13] = "tablet";
        argv[14] = "-device";
        argv[15] = "AC97";
        argv[16] = "-netdev";
        argv[17] = "user,id=lan";
        argv[18] = "-device";
        argv[19] = "rtl8139,netdev=lan";
        argv[20] = NULL;
    } else if (g.os == WIN2K) {
        /* Windows 2000 quirks:
         * 1. AC97 is required for audio
         */
        argv[12] = "-device";
        argv[13] = "AC97";
        argv[14] = "-netdev";
        argv[15] = "user,id=lan";
        argv[16] = "-device";
        argv[17] = "rtl8139,netdev=lan";
        argv[18] = NULL;
    }
    else argv[12] = NULL;

    printf("starting qemu\n");
    
    execvp(qemu_cmd, argv);
}
