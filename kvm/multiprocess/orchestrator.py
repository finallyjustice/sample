#!/usr/bin/python

# This script is based on python 2.7.5
#
# /usr/bin/python --version
# Python 2.7.5

import subprocess
import sys
import socket

QEMU_BIN="/home/zhang/kvm/qemu-6.0.0/build/x86_64-softmmu/qemu-system-x86_64"

proxy_sock, remote_sock = socket.socketpair(socket.AF_UNIX,
                                            socket.SOCK_STREAM)

remote_cmd = QEMU_BIN + " " \
             "-machine x-remote -nodefaults " + \
	     "-device lsi53c895a,id=lsi0 " + \
	     "-object x-remote-object,id=robj1,devid=lsi0,fd=" + \
	     str(remote_sock.fileno()) + " " \
             "-drive id=drive1,if=none,file=test.qcow2 " + \
             "-device scsi-hd,id=scsi1,drive=drive1,bus=lsi0.0,scsi-id=0"

local_cmd = QEMU_BIN + " " \
            "-enable-kvm -smp 4 -m 4G -vnc :7 -hda ol7.qcow2 " + \
	    "-object memory-backend-memfd,id=mem0,size=4G " + \
	    "-numa node,memdev=mem0 " + \
	    "-net nic -net user,hostfwd=tcp::5027-:22 " + \
	    "-device x-pci-proxy-dev,id=lsi0,fd=" + str(proxy_sock.fileno())

p1 = subprocess.Popen(remote_cmd, shell=True, stderr=subprocess.PIPE)
p2 = subprocess.Popen(local_cmd, shell=True, stderr=subprocess.PIPE)

while True:
    out = p2.stderr.read(1)
    if out == '' and p2.poll() != None:
        break
    if out != '':
        sys.stdout.write(out)
        sys.stdout.flush()
