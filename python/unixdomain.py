#!/usr/bin/python

import argparse
import socket
import sys
import os

class Instance(object):
    def __init__(self, path):
        self.path = path

    def send(self):
        sock = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
        try:
            sock.connect(self.path)
        except socket.error, msg:
            print(msg)
            sys.exit(1)

        try:
            message = 'This is hello world! How are you doing!'
	    sock.sendall(message)

            amount_received = 0
            amount_expected = len(message)

            while amount_received < amount_expected:
                data = sock.recv(16)
                print("recv: %s" % data)
                amount_received += len(data)

        finally:
            sock.close()

    def recv(self):
        try:
            os.unlink(self.path)
        except OSError:
            if os.path.exists(self.path):
                raise

        sock = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
        sock.bind(self.path)
        sock.listen(1)

        while True:
            connection, client_address = sock.accept()
            print(client_address)
            try:
                while True:
                    data = connection.recv(16)
                    print("recv: %s" % data)
		    
                    if data:
                        connection.sendall(data)
                    else:
                        break;

            finally:
                 connection.close()

def main():
    parser = argparse.ArgumentParser(description="Mod Template")
    parser.add_argument("-s", "--socket", default="unix.sock",
                        help="unix domain socket path")
    parser.add_argument("-m", "--mode", help="client or server")
    args = parser.parse_args()

    instance = Instance(args.socket)

    if args.mode == "server":
        instance.recv()
    elif args.mode == "client":
        instance.send()
    else:
        print("please specific mode: client or server")

if __name__ == '__main__':
    main();
