#!/bin/bash
UNAME=`uname -m`
INSTALL_DIR=/usr/local/lib/lv2/cheap_distortion.lv2
gksu -- mkdir -p $INSTALL_DIR
gksu -- cp -f manifest.ttl $INSTALL_DIR/manifest.ttl
gksu -- cp -f plugin.ttl $INSTALL_DIR/cheap_distortion.ttl
gksu -- chmod 775 $INSTALL_DIR/*.ttl
gksu -- cp -f so.$UNAME $INSTALL_DIR/cheap_distortion.so
