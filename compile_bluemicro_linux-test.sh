#!/bin/bash
DIR="$( cd -P "$( dirname "$0" )" && pwd )"
PREFIX=$DIR/chonkybois_build_test
OUTPUT=$PREFIX/build-single
SINGLE=$PREFIX/firmware
KB=keyboards/lil_chonky_bois_testbed
KEYMAP=default

BSP_PATH=.arduino15/packages/adafruit/hardware/nrf52
BSP_VERSION=0.24.0
rm -rf $PREFIX
mkdir -p $PREFIX

mkdir $SINGLE
cp $DIR/firmware/* $SINGLE

pushd $SINGLE
# mv firmware.ino firmware-single.ino
cp $DIR/firmware/$KB/config/single/keyboard_config.h .
cp $DIR/firmware/$KB/hardware/pca10056/bluemicro840v1_0/hardware_config.h .
cp $DIR/firmware/$KB/keymaps/$KEYMAP/keymap.cpp .
cp $DIR/firmware/$KB/keymaps/$KEYMAP/keymap.h .
popd

arduino-cli compile \
	--fqbn community_nrf52:nrf52:pca10056 \
	$SINGLE \
	--output-dir $OUTPUT
python3 $HOME/$BSP_PATH/$BSP_VERSION/tools/uf2conv/uf2conv.py \
	$OUTPUT/firmware.ino.hex -c -f 0xADA52840 \
	-o $OUTPUT/firmware.ino.uf2



