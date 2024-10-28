# snbox

<img src="https://github.com/user-attachments/assets/588fabec-45ad-4567-b2e1-bbbba8668d4d" width="500">

A "Windows Sandbox"-like QEMU frontend. It lets you quickly start a VM, which is always fresh and always working on each boot. That's basically all it is.

This is my first actual C utility, and I know the code sucks and probably has a billion memory leaks and security issues (tell me about all issues btw).

Uses QEMU, libcurl and libarchive.

### How to build

1. Make sure you have libcurl, libarchive, qemu-system-x86, and clang installed. On Debian, run `sudo apt install libcurl4-openssl-dev libarchive-dev clang qemu-system-x86`
2. Clone this repo. `git clone https://github.com/winksplorer/snbox && cd snbox`
3. Build. `make`
4. Install. `sudo make install`

### How to use

When you run `snbox` without any arguments, it gives you a help message and lists all the possible operating systems.

To run an operarting system in snbox, simply do `snbox <os name>`, like for example, running Windows XP would be `snbox winxp`.

When you first start an operating system in snbox, you may notice it downloads and decompresses it for about 20 seconds. After the first time, it will start up instantly since snbox has cached it on your hard drive so you do not need to download it again.

### Current features:
- Currently supports quick-virtualizing MS-DOS 5, Windows 3.1, Windows NT 4.0, Windows 2000, Windows XP, and Haiku OS (r1beta5)
- All guest files are compressed (compression level 9 in 7z) so it doesn't take years to download a guest
- Guest files are "cached", so you don't need to download it each time
- Uses snapshots, so if you destroy a windows install, you can simply start it again and it's back to normal

### Current issues:
- Windows XP is the only guest that I have currently tested that audio works correctly
- Terrible code (seriously)
- No way to currently mount a CD in a guest without messing with QEMU console
- Currently a limited range of guest operating systems (I'm taking requests for what OS to add as a guest)
