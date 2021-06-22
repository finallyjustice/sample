#!/usr/bin/python

import argparse

class VM(object):
    def __init__(self, sock):
        self.sock = sock

    def dump(self):
        print("hello world! %s" % self.sock);

def main():
    parser = argparse.ArgumentParser(description="Mod Template")
    parser.add_argument("-s", "--socket", default="monitor.sock",
                        help="unix domain socket path")
    args = parser.parse_args()

    vm = VM(args.socket)
    vm.dump()

if __name__ == "__main__":
    main();
