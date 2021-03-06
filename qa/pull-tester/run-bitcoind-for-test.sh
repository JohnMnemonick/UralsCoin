#!/bin/bash
# Copyright (c) 2013 The Bitsend Core developers
# Distributed under the MIT/X11 software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.
#
DATADIR="/c/projekt11/bitsend30/.bitsend"
rm -rf "$DATADIR"
mkdir -p "$DATADIR"/regtest
touch "$DATADIR/regtest/debug.log"
tail -q -n 1 -F "$DATADIR/regtest/debug.log" | grep -m 1 -q "Done loading" &
WAITER=$!
PORT=`expr $BASHPID + 10000`
"/c/projekt11/bitsend30/src/bitsendd.exe" -connect=0.0.0.0 -datadir="$DATADIR" -rpcuser=user -rpcpassword=pass -listen -keypool=3 -debug -debug=net -logtimestamps -port=$PORT -regtest -rpcport=`expr $PORT + 1` &
URALSD=$!

#Install a watchdog.
(sleep 10 && kill -0 $WAITER 2>/dev/null && kill -9 $URALSD $$)&
wait $WAITER

if [ -n "$TIMEOUT" ]; then
  timeout "$TIMEOUT"s "$@" $PORT
  RETURN=$?
else
  "$@" $PORT
  RETURN=$?
fi

(sleep 15 && kill -0 $URALSD 2>/dev/null && kill -9 $URALSD $$)&
kill $URALSD && wait $URALSD

# timeout returns 124 on timeout, otherwise the return value of the child
exit $RETURN
