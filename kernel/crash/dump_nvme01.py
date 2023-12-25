import datetime
import os
import shutil
from pykdump.API import *

def print_to_file(out, folder, name):
    if name == "" or folder[0] == '/':
        print("Failed to write to " + folder+"/"+name)
        os._exit(1)

    crashfile = open(folder+"/"+name, "wb")
    crashfile.write(out.encode('utf-8'))
    crashfile.close()


def dump_nvme_dev(index, nvme_dev):


def dump_nvme_subsystem(index, nvme_subsystem):
    for nvme_ctrl in readSUListFromHead(nvme_subsystem.ctrls, "subsys_entry", "struct nvme_ctrl"):
        print(nvme_ctrl)
        nvme_ctrl_base = "{:x}".format(nvme_ctrl)
        nvme_dev_base = hex(int(nvme_ctrl_base, 16) - ctrl_offset)
        cmd = "nvme_dev " + nvme_dev_base
        out = exec_crash_command(cmd)
        file_name = "nvme_dev_" + str(index).rjust(3, '0') + "_" + nvme_dev_base + ".txt"
        print_to_file(out, directory, file_name)

        directory_ctrl = directory + "/" + str(index).rjust(3, '0')
        os.makedirs(directory_ctrl)

        nvme_dev = readSU("struct nvme_dev", int(nvme_dev_base, 16))
        dump_nvme_dev(index, nvme_dev)


ct = datetime.datetime.now()
ts = ct.timestamp()

directory = "data_" + str(ts)

if os.path.exists(directory):
    shutil.rmtree(directory)
os.makedirs(directory)

# dump sys
out = exec_crash_command("sys")
print_to_file(out, directory, "sys.txt")

# dump log
out = exec_crash_command("log")
print_to_file(out, directory, "log.txt")

# dump "ps -m"
#out = exec_crash_command("ps -m")
#print_to_file(out, directory, "ps_-m.txt")


out = exec_crash_command("nvme_dev.ctrl").splitlines()[1].split()[0][1:-1]
print("nvme_dev.ctrl offset: " + out)
ctrl_offset = int(out)

cnt_subsys = 0

for nvme_subsystem in readSUListFromHead(sym2addr("nvme_subsystems"), "entry", "struct nvme_subsystem"):
    nvme_subsystem_base = "{:x}".format(nvme_subsystem)
    cmd = "nvme_subsystem " + nvme_subsystem_base
    out = exec_crash_command(cmd)
    file_name = "nvme_subsystem_" + str(cnt_subsys).rjust(3, '0') + "_" + nvme_subsystem_base + ".txt"
    print_to_file(out, directory, file_name)

    dump_nvme_subsystem(cnt_subsys, nvme_subsystem)

    cnt_subsys = cnt_subsys + 1
