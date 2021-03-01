#!/sbin/dtrace -qs

fbt::nested_vmx_run:entry
{
    printf("nested_vmx_run()\n");
    exit(0);
}
