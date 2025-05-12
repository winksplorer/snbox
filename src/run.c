#include "run.h"

#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>

#include "common.h"

/* Runs a guest g in QEMU, with a qcow2 path hdd. */
void run(Guest g, const char* hdd) {
    char qemu_cmd[20];
    char* qarg[64];
    int i = 0;

    /* Choosing VGA card */
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
            #else
            vga = "qxl";
            #endif
            break;
        case VIRTIO:
            vga = "virtio";
            break;
    }

    /* Choose QEMU binary based on if guest is 64-bit */
    snprintf(qemu_cmd, 20, "qemu-system-%s", g.amd64 ? "x86_64" : "i386");

    /* Add initial arguments */
    strarr_add(qarg, &i, 
        qemu_cmd,
        "-smp", fmt("%d", g.cpu_cores), // CPU threads
        "-m", fmt("%d", g.ram_size), // Memory size (MB)
        "-drive", fmt("file=%s,format=qcow2", hdd), // HDD path
        "-vga", vga, // Graphics adapter
        "-snapshot", // Do not save changes to the HDD
        "-accel", // First half of accelerator option
        NULL
    );

    /* Choose accelerator */
    #if defined(__arm64__) || defined(__aarch64__) // You cannot accel x86 QEMU on ARM
        strarr_add(qarg, &i, "tcg", NULL);
    #else // Assume x86
        #if __APPLE__ // macOS
        strarr_add(qarg, &i, "hvf", NULL);
        #else
        strarr_add(qarg, &i, "kvm", NULL);
        #endif
    #endif
    
    /* OS-specific switches */
    if (g.os == WINNT4) {
        /* Windows NT 4.0 */

        i -= 2; // This removes "-accel <accelerator>". NT4 cannot be accelerated
        strarr_add(qarg, &i,
            "-cpu", "pentium3", // NT4 requires the pentium3 CPU option
            NULL
        );
    } else if (g.os == WINXP) {
        /* Windows XP x86 */
        
        strarr_add(qarg, &i, 
            "-usbdevice", "tablet", // Gets the mouse working with QXL
            "-device", "AC97", // Audio device
            "-netdev", "user,id=lan",
            "-device", "rtl8139,netdev=lan", // XP requires RTL8139 network controller
            NULL
        );
    } else if (g.os == WIN2K) {
        /* Windows 2000 */
        
        strarr_add(qarg, &i, 
            "-device", "AC97", // Audiio device
            "-netdev", "user,id=lan",
            "-device", "rtl8139,netdev=lan", // 2K requires RTL8139 network controller
            NULL
        );
    }
    qarg[i++] = NULL;

    /* If compiled with make EXT_CFLAGS=-DSN_SHOWCMD, then list qemu args */
    #ifdef SN_SHOWCMD
    for (int j = 0; j <= 63; j++) {
        if (!qarg[j]) break;
        printf("qarg[%d] = %s\n", j, qarg[j]);
    }
    printf("\n");
    #endif

    printf("starting qemu\n");
    
    execvp(qemu_cmd, qarg);
    perror("could not start qemu");
    _exit(1);
}