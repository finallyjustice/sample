#!/bin/sh

XENPATH=/home/zhang/src/mainline-xen

tar xvf seabios.tar.gz
mv seabios-dir ${XENPATH}/tools/firmware/.

cp ipxe.tar.gz ${XENPATH}/tools/firmware/etherboot/.

tar xvf qemu-xen-traditional.tar.gz
mv qemu-xen-traditional-dir ${XENPATH}/tools/.

tar xvf qemu-xen.tar.gz
mv qemu-xen-dir ${XENPATH}/tools/.

cp Makefile-firmware ${XENPATH}/tools/firmware/Makefile

cp Makefile-etherboot ${XENPATH}/tools/firmware/etherboot/Makefile

cp Makefile-tools ${XENPATH}/tools/Makefile
