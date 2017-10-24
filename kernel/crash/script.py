from pykdump.API import *

print("pykdump sample")

cmd = "net"
output = exec_crash_command(cmd)
print(output)

jiffies = readSymbol("jiffies")
print("jiffies is %d" % jiffies)

if symbol_exists("all_bdevs"):
    print("symbol all_bdevs exist")
else:
    print("symbol all_bdevs not exist")

