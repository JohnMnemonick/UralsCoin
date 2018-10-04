#!/bin/sh

TOPDIR=${TOPDIR:-$(git rev-parse --show-toplevel)}
SRCDIR=${SRCDIR:-$TOPDIR/src}
MANDIR=${MANDIR:-$TOPDIR/doc/man}

URALSD=${URALSD:-$SRCDIR/uralsd}
URALSCLI=${URALSCLI:-$SRCDIR/urals-cli}
URALSTX=${URALSTX:-$SRCDIR/urals-tx}
URALSQT=${URALSQT:-$SRCDIR/qt/urals-qt}

[ ! -x $URALSD ] && echo "$URALSD not found or not executable." && exit 1

# The autodetected version git tag can screw up manpage output a little bit
BSDVER=($($URALSCLI --version | head -n1 | awk -F'[ -]' '{ print $6, $7 }'))

# Create a footer file with copyright content.
# This gets autodetected fine for uralsd if --version-string is not set,
# but has different outcomes for urals-qt and urals-cli.
echo "[COPYRIGHT]" > footer.h2m
$URALSD --version | sed -n '1!p' >> footer.h2m

for cmd in $URALSD $URALSCLI $URALSTX $URALSQT; do
  cmdname="${cmd##*/}"
  help2man -N --version-string=${BSDVER[0]} --include=footer.h2m -o ${MANDIR}/${cmdname}.1 ${cmd}
  sed -i "s/\\\-${BSDVER[1]}//g" ${MANDIR}/${cmdname}.1
done

rm -f footer.h2m
