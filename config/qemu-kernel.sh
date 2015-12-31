#!/bin/sh

#/soft/qemu/bin/qemu-system-x86_64 -hda /media/zhang/Disk/LinuxSystem/12ubuntu/ubuntu12 -m 1024m -enable-kvm
#qemu-system-x86_64 -hda /media/Disk/LinuxSystem/12ubuntu/ubuntu12 -m 1024m -enable-kvm
#qemu-system-x86_64 -smp 2 -kernel /home/zhang/src/linux-3.14/arch/x86_64/boot/bzImage -hda  /media/zhang/Disk/linux/img/qemu-ubuntu-12/ubuntu12 -append "root=/dev/sda1 init=/sbin/init text" -monitor stdio -m 1024m -enable-kvm 
#qemu-system-x86_64 -smp 2 -kernel /home/zhang/src/linux-3.19/arch/x86_64/boot/bzImage -hda  /media/zhang/Disk/linux/img/qemu-ubuntu-12/ubuntu12 -append "root=/dev/sda1 init=/sbin/init text" -monitor stdio -m 1024m -net nic,model=i82559er -enable-kvm

qemu-system-x86_64 -smp 2  \
	-kernel /home/zhang/src/linux-3.19/arch/x86_64/boot/bzImage \
	-hda /media/zhang/Disk/linux/img/qemu-ubuntu-12/ubuntu12 \
	-append "root=/dev/sda1 init=/sbin/init text" \
	-monitor stdio -m 1024m -enable-kvm \
