# snbox

<img src="https://github.com/user-attachments/assets/588fabec-45ad-4567-b2e1-bbbba8668d4d" width="500">

A "Windows Sandbox"-like QEMU launcher. It lets you quickly start VMs, which are always fresh and always working on each boot. You won't ever need to install an OS.

### Building

1. Make sure you have libcurl, libarchive, qemu-system-x86, and clang installed.
2. Clone this repo. `git clone https://github.com/winksplorer/snbox && cd snbox`
3. Build. `make`
4. Install. Do `sudo make install` on Linux, or `sudo make install2` on macOS or other *nixs.

### Usage

When you run `snbox` without any arguments, it gives you a help message and lists all the possible operating systems.

To run an operarting system in snbox, simply do `snbox <os name>`, like for example, running Windows XP would be `snbox winxp`.

When you first start an operating system in snbox, you may notice it downloads and decompresses it for about 20 seconds. After the first time, it will start up instantly since snbox has cached it on your hard drive so you do not need to download it again.