#!/bin/bash
echo test
sudo ./i686-compiler make
sudo qemu-system-x86_64 -fda e93-os.img