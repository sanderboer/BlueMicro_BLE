#!/bin/bash
DIR="$( cd -P "$( dirname "$0" )" && pwd )"

PREFIX=$DIR/chonkybois_build
OUTPUT=$PREFIX/build
SINGLE=$PREFIX/firmware-single
LEFT=$PREFIX/firmware-left
RIGHT=$PREFIX/firmware-right
KB=keyboards/lil_chonky_bois
KEYMAP=default

BSP_PATH=.arduino15/packages/adafruit/hardware/nrf52
BSP_VERSION=0.24.0
rm -rf $PREFIX
mkdir -p $PREFIX

mkdir $SINGLE
mkdir $LEFT
mkdir $RIGHT
cp $DIR/firmware/* $SINGLE
cp $DIR/firmware/* $LEFT
cp $DIR/firmware/* $RIGHT

pushd $LEFT
mv firmware.ino firmware-left.ino
cp $DIR/firmware/$KB/config/left/keyboard_config.h .
cp $DIR/firmware/$KB/hardware/pca10056/bluemicro840v1_0/hardware_config.h .
cp $DIR/firmware/$KB/keymaps/$KEYMAP/keymap.* .
popd
pushd $RIGHT
mv firmware.ino firmware-right.ino
cp $DIR/firmware/$KB/config/right/keyboard_config.h .
cp $DIR/firmware/$KB/hardware/pca10056/bluemicro840v1_0/hardware_config.h .
cp $DIR/firmware/$KB/keymaps/$KEYMAP/keymap.* .
popd
pushd $SINGLE
mv firmware.ino firmware-single.ino
cp $DIR/firmware/$KB/config/single/keyboard_config.h .
cp $DIR/firmware/$KB/hardware/pca10056/bluemicro840v1_0/hardware_config.h .
cp $DIR/firmware/$KB/keymaps/$KEYMAP/keymap.* .
popd

arduino-cli compile \
	--fqbn community_nrf52:nrf52:pca10056 \
	$LEFT \
	--output-dir $OUTPUT-left-micro
python3 $HOME/$BSP_PATH/$BSP_VERSION/tools/uf2conv/uf2conv.py \
	$OUTPUT-left-micro/firmware-left.ino.hex -c -f 0xADA52840 \
	-o $OUTPUT-left-micro/firmware-left.ino.uf2

arduino-cli compile \
	--fqbn community_nrf52:nrf52:pca10056 \
	$RIGHT \
	--output-dir $OUTPUT-right-micro
python3 $HOME/$BSP_PATH/$BSP_VERSION/tools/uf2conv/uf2conv.py \
	$OUTPUT-right-micro/firmware-right.ino.hex -c -f 0xADA52840 \
	-o $OUTPUT-right-micro/firmware-right.ino.uf2

# arduino-cli compile \
# 	--fqbn community_nrf52:nrf52:pca10056 \
# 	$SINGLE \
# 	--output-dir $OUTPUT-single-micro
# python3 $HOME/$BSP_PATH/$BSP_VERSION/tools/uf2conv/uf2conv.py \
# 	$OUTPUT-single-micro/firmware-single.ino.hex -c -f 0xADA52840 \
# 	-o $OUTPUT-single-micro/firmware-single.ino.uf2



