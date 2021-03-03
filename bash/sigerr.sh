#!/bin/sh
#
# ifconfig: option `-q' not recognised.
# ifconfig: `--help' gives usage information.
# err trapped for ./sss.sh

sigerr() {
    echo "err trapped for $0"
}

trap sigerr ERR

ifconfig -a > /dev/null
ifconfig -a > /dev/null
ifconfig -q > /dev/null
