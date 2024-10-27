#include <run.h>
#include <guests.h>
#include <stdio.h>
#include <unistd.h>

void run(Guest g) {
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
            vga = "qxl";
            break;
        case VIRTIO:
            vga = "virtio";
            break;
    }

    snprintf(qemu_cmd, 20, "qemu-system-%s", g.amd64 ? "x86_64" : "i386");

    char* argv[10];

    argv[0] = qemu_cmd;

    argv[1] = "-smp";
    char cores[2];
    snprintf(cores, 2, "%d", g.cpu_cores);
    argv[2] = cores;

    argv[3] = "-m";
    char mem[5];
    snprintf(mem, 5, "%d", g.ram_size);
    argv[4] = mem;

    argv[5] = "-drive";
    argv[6] = "file=snbox.qcow2,format=qcow2";
    argv[7] = "-vga";
    argv[8] = vga;
    argv[9] = NULL;

    printf("starting qemu");
    
    execvp(qemu_cmd, argv);
}