This is about how to attach virtio-scsi (with scsi passthrough to VM).

1. Create the loop device image.

# dd if=/dev/zero of=disk.img bs=1M count=512 oflag=direct


2. Create two loopback scsi devices based on the same file.

# targetcli /backstores/fileio create name=lun1 file_or_dev=/home/zhang/img/loop-img/disk.img 
Created fileio lun1 with size 536870912

# targetcli /loopback create
Created target naa.5001405e8ff79e1b.

# targetcli /loopback/naa.5001405e8ff79e1b/luns create /backstores/fileio/lun1
Created LUN 0.

# targetcli /loopback create
Created target naa.5001405c0ebbd323.

# targetcli /loopback/naa.5001405c0ebbd323/luns create /backstores/fileio/lun1
Created LUN 0.

# sudo targetcli ls
o- / .................................................................................................................... [...]
  o- backstores ......................................................................................................... [...]
  | o- block ............................................................................................. [Storage Objects: 0]
  | o- fileio ............................................................................................ [Storage Objects: 1]
  | | o- lun1 ............................................. [/home/zhang/img/loop-img/disk.img (512.0MiB) write-back activated]
  | |   o- alua .............................................................................................. [ALUA Groups: 1]
  | |     o- default_tg_pt_gp .................................................................. [ALUA state: Active/optimized]
  | o- pscsi ............................................................................................. [Storage Objects: 0]
  | o- ramdisk ........................................................................................... [Storage Objects: 0]
  o- iscsi ....................................................................................................... [Targets: 0]
  o- loopback .................................................................................................... [Targets: 2]
  | o- naa.5001405c0ebbd323 ............................................................................ [naa.50014057776a2893]
  | | o- luns ....................................................................................................... [LUNs: 1]
  | |   o- lun0 .......................................... [fileio/lun1 (/home/zhang/img/loop-img/disk.img) (default_tg_pt_gp)]
  | o- naa.5001405e8ff79e1b ............................................................................ [naa.50014058adefd870]
  |   o- luns ....................................................................................................... [LUNs: 1]
  |     o- lun0 .......................................... [fileio/lun1 (/home/zhang/img/loop-img/disk.img) (default_tg_pt_gp)]
  o- vhost ....................................................................................................... [Targets: 0]


3. Configure multipath.conf as below (sde and sdf will be involved)

# cat /etc/multipath.conf 
defaults {
    user_friendly_names yes
}
blacklist {
    devnode "^vd*"
    devnode "sda"
    devnode "sdb"
    devnode "sdc"
    devnode "sdd"
    devnode "nvme0n1"
}

4. Enable multipathd. We will have multipath (based on sde and sdf) on KVM host.

# systemctl start multipathd

# multipath -l
mpathc (36001405f5ec2cd80cea447e936b9591e) dm-3 LIO-ORG ,lun1            
size=512M features='0' hwhandler='0' wp=rw
|-+- policy='service-time 0' prio=0 status=active
| `- 7:0:1:0 sde 8:64 active undef running
`-+- policy='service-time 0' prio=0 status=enabled
  `- 8:0:1:0 sdf 8:80 active undef running

# lsblk
NAME        MAJ:MIN RM   SIZE RO TYPE  MOUNTPOINT
sdf           8:80   0   512M  0 disk  
└─mpathc    252:3    0   512M  0 mpath 
sdd           8:48   0   1.1T  0 disk  
└─sdd1        8:49   0   1.1T  0 part  
  └─ol-home 252:2    0   3.2T  0 lvm   /home
sdb           8:16   0 557.9G  0 disk  
└─sdb1        8:17   0 557.9G  0 part  
  └─ol-home 252:2    0   3.2T  0 lvm   /home
sde           8:64   0   512M  0 disk  
└─mpathc    252:3    0   512M  0 mpath 
sdc           8:32   0   1.1T  0 disk  
└─sdc1        8:33   0   1.1T  0 part  
  └─ol-home 252:2    0   3.2T  0 lvm   /home
sda           8:0    0 557.9G  0 disk  
├─sda2        8:2    0 556.9G  0 part  
│ ├─ol-swap 252:1    0     4G  0 lvm   [SWAP]
│ ├─ol-home 252:2    0   3.2T  0 lvm   /home
│ └─ol-root 252:0    0    50G  0 lvm   /
└─sda1        8:1    0     1G  0 part  /boot


5. Assign the multipath device (mpathc) to QEMU. The lun is configured as 5 in VM.

# qemu-system-x86_64 -m 3000M -enable-kvm -smp 4 -vnc :7 \
  -net nic -net user,hostfwd=tcp::5027-:22 -hda ol7.qcow2 \
  -device virtio-scsi-pci,id=scsi0,num_queues=4 \
  -device scsi-block,drive=drive1,bus=scsi0.0,channel=0,scsi-id=0,lun=5 \
  -drive file=/dev/mapper/mpathc,if=none,id=drive1,cache=writethrough -serial stdio


6. Here are dmesg from VM. The lun=5 because we configured that in QEMU.

# dmesg | egrep "scsi|SCSI"
[    0.781893] SCSI subsystem initialized
[    1.133564] Block layer SCSI generic (bsg) driver version 0.4 loaded (major 246)
[    1.638232] scsi host0: ata_piix
[    1.644847] scsi host1: ata_piix
[    1.667264] scsi host2: Virtio SCSI HBA
[    1.669043] scsi 2:0:0:5: Direct-Access     LIO-ORG  lun1             4.0  PQ: 0 ANSI: 5
[    1.680048] scsi 2:0:0:5: alua: supports implicit and explicit TPGS
[    1.680055] scsi 2:0:0:5: alua: device naa.6001405f5ec2cd80cea447e936b9591e port group 0 rel port 1
[    1.685812] scsi 2:0:0:5: Power-on or device reset occurred
[    1.693877] scsi 2:0:0:5: alua: transition timeout set to 60 seconds
[    1.713537] scsi 2:0:0:5: alua: port group 00 state A non-preferred supports TOlUSNA
[    1.713694] scsi 2:0:0:5: alua: port group 00 state A non-preferred supports TOlUSNA
[    1.807015] scsi 0:0:0:0: Direct-Access     ATA      QEMU HARDDISK    2.5+ PQ: 0 ANSI: 5
[    1.810287] scsi 1:0:0:0: CD-ROM            QEMU     QEMU DVD-ROM     2.5+ PQ: 0 ANSI: 5
[    1.852224] sd 2:0:0:5: [sda] Attached SCSI disk
[    1.963626] sd 0:0:0:0: [sdb] Attached SCSI disk
[    1.996625] sr 1:0:0:0: [sr0] scsi3-mmc drive: 4x/4x cd/rw xa/form2 tray
[    2.004971] sr 1:0:0:0: Attached scsi CD-ROM sr0
[    5.697757] sd 2:0:0:5: Attached scsi generic sg0 type 0
[    5.700248] sd 0:0:0:0: Attached scsi generic sg1 type 0
[    5.708148] sr 1:0:0:0: Attached scsi generic sg2 type 5
