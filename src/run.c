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

    printf("b");

    snprintf(qemu_cmd, 20, "qemu-system-%s", g.amd64 ? "x86_64" : "i386");

    char* argv[8];

    //argv[0] = qemu_cmd;

    argv[0] = "-smp";
    char cores[2];
    snprintf(cores, 2, "%d", g.cpu_cores);
    argv[1] = cores;

    argv[2] = "-m";
    char mem[5];
    snprintf(mem, 5, "%d", g.ram_size);
    argv[3] = mem;

    argv[4] = "-drive";
    argv[5] = "file=snbox.qcow2,format=qcow2";
    argv[6] = "-vga";
    argv[7] = vga;

    printf("c %s\n", argv[4]);
    
    execvp(qemu_cmd, argv);
}