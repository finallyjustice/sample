#!/usr/sbin/dtrace -qs

/*
 * # sudo ./open-vhost-scsi.d
 *
 * # modprobe fbt
 * # modprobe systrace
 *
 * open() /opt/rh/devtoolset-8/root/usr/lib64/tls/x86_64/libc.so.6 entry 20846445612, vhost_scsi_hotp
 * open() return 20846445616, vhost_scsi_hotp
 * open() /opt/rh/devtoolset-8/root/usr/lib64/tls/libc.so.6 entry 20846445620, vhost_scsi_hotp
 * open() return 20846445622, vhost_scsi_hotp
 * open() /opt/rh/devtoolset-8/root/usr/lib64/x86_64/libc.so.6 entry 20846445625, vhost_scsi_hotp
 * open() return 20846445627, vhost_scsi_hotp
 * open() /opt/rh/devtoolset-8/root/usr/lib64/libc.so.6 entry 20846445629, vhost_scsi_hotp
 * open() return 20846445631, vhost_scsi_hotp
 * open() /opt/rh/devtoolset-8/root/usr/lib/tls/x86_64/libc.so.6 entry 20846445634, vhost_scsi_hotp
 * open() return 20846445635, vhost_scsi_hotp
 * open() /opt/rh/devtoolset-8/root/usr/lib/tls/libc.so.6 entry 20846445638, vhost_scsi_hotp
 * open() return 20846445640, vhost_scsi_hotp
 * open() /opt/rh/devtoolset-8/root/usr/lib/x86_64/libc.so.6 entry 20846445642, vhost_scsi_hotp
 * open() return 20846445644, vhost_scsi_hotp
 * open() /opt/rh/devtoolset-8/root/usr/lib/libc.so.6 entry 20846445647, vhost_scsi_hotp
 * open() return 20846445648, vhost_scsi_hotp
 * open() /opt/rh/devtoolset-8/root/usr/lib64/dyninst/tls/x86_64/libc.so.6 entry 20846445651, vhost_scsi_hotp
 * open() return 20846445653, vhost_scsi_hotp
 * open() /opt/rh/devtoolset-8/root/usr/lib64/dyninst/tls/libc.so.6 entry 20846445655, vhost_scsi_hotp
 * open() return 20846445657, vhost_scsi_hotp
 * open() /opt/rh/devtoolset-8/root/usr/lib64/dyninst/x86_64/libc.so.6 entry 20846445660, vhost_scsi_hotp
 * open() return 20846445662, vhost_scsi_hotp
 * open() /opt/rh/devtoolset-8/root/usr/lib64/dyninst/libc.so.6 entry 20846445664, vhost_scsi_hotp
 * open() return 20846445666, vhost_scsi_hotp
 * open() /opt/rh/devtoolset-8/root/usr/lib/dyninst/tls/x86_64/libc.so.6 entry 20846445669, vhost_scsi_hotp
 * open() return 20846445670, vhost_scsi_hotp
 * open() /opt/rh/devtoolset-8/root/usr/lib/dyninst/tls/libc.so.6 entry 20846445673, vhost_scsi_hotp
 * open() return 20846445674, vhost_scsi_hotp
 * open() /opt/rh/devtoolset-8/root/usr/lib/dyninst/x86_64/libc.so.6 entry 20846445677, vhost_scsi_hotp
 * open() return 20846445678, vhost_scsi_hotp
 * open() /opt/rh/devtoolset-8/root/usr/lib/dyninst/libc.so.6 entry 20846445681, vhost_scsi_hotp
 * open() return 20846445683, vhost_scsi_hotp
 * open() /etc/ld.so.cache entry 20846445686, vhost_scsi_hotp
 * open() return 20846445688, vhost_scsi_hotp
 * open() /lib64/libc.so.6 entry 20846445694, vhost_scsi_hotp
 * open() return 20846445697, vhost_scsi_hotp
 * open() /dev/vhost-scsi entry 20846445781, vhost_scsi_hotp
 * vhost_scsi_open() entry 20846445790
 * vhost_scsi_open() return 20846446598
 * open() return 20846446600, vhost_scsi_hotp
 */

dtrace:::BEGIN
{
}

fbt:vhost_scsi:vhost_scsi_open:entry
{
    printf("vhost_scsi_open() entry %d\n", timestamp/1000);
}

fbt:vhost_scsi:vhost_scsi_open:return
{
    printf("vhost_scsi_open() return %d\n", timestamp/1000);
}

syscall::open:entry
/execname == "vhost_scsi_hotp"/
{
    printf("open() %s entry %d, %s\n", copyinstr(arg0), timestamp/1000, execname);
}

syscall::open:return
/execname == "vhost_scsi_hotp"/
{
    printf("open() return %d, %s\n", timestamp/1000, execname);
}


dtrace:::END
{
}
