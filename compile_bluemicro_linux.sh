#!/bin/bash
DIR="$( cd -P "$( dirname "$0" )" && pwd )"
LEFT=$DIR/chonkybois_build_micro/firmware-left
RIGHT=$DIR/chonkybois_build_micro/firmware-right
SINGLE=$DIR/chonkybois_build_micro/firmware-single
KB=keyboards/lil_chonky_bois

BSP_PATH=.arduino15/packages/adafruit/hardware/nrf52
BSP_VERSION=0.24.0
rm -rf $DIR/chonkybois_build_micro
mkdir -p $DIR/chonkybois_build_micro

cp -r $DIR/firmware $LEFT
cp -r $DIR/firmware $RIGHT
cp -r $DIR/firmware $SINGLE

pushd $LEFT
mv firmware.ino firmware-left.ino
cp $KB/config/left/keyboard_config.h .
cp $KB/hardware/pca10056/bluemicro840v1_0/hardware_config.h .
cp $KB/keymaps/default/keymap.* .
popd
pushd $RIGHT
mv firmware.ino firmware-right.ino
cp $KB/config/right/keyboard_config.h .
cp $KB/hardware/pca10056/bluemicro840v1_0/hardware_config.h .
cp $KB/keymaps/default/keymap.* .
popd
pushd $SINGLE
mv firmware.ino firmware-single.ino
cp $KB/config/single/keyboard_config.h .
cp $KB/hardware/pca10056/bluemicro840v1_0/hardware_config.h .
cp $KB/keymaps/default/keymap.* .
popd

arduino-cli compile \
	--fqbn community_nrf52:nrf52:pca10056 \
	$LEFT \
	--output-dir $DIR/build-left-micro
python3 $HOME/$BSP_PATH/$BSP_VERSION/tools/uf2conv/uf2conv.py \
	$DIR/build-left-micro/firmware-left.ino.hex -c -f 0xADA52840 \
	-o $DIR/build-left-micro/firmware-left.ino.uf2

arduino-cli compile \
	--fqbn community_nrf52:nrf52:pca10056 \
	$RIGHT \
	--output-dir $DIR/build-right-micro
python3 $HOME/$BSP_PATH/$BSP_VERSION/tools/uf2conv/uf2conv.py \
	$DIR/build-right-micro/firmware-right.ino.hex -c -f 0xADA52840 \
	-o $DIR/build-right-micro/firmware-right.ino.uf2

arduino-cli compile \
	--fqbn community_nrf52:nrf52:pca10056 \
	$SINGLE \
	--output-dir $DIR/build-single-micro
python3 $HOME/$BSP_PATH/$BSP_VERSION/tools/uf2conv/uf2conv.py \
	$DIR/build-single-micro/firmware-single.ino.hex -c -f 0xADA52840 \
	-o $DIR/build-single-micro/firmware-single.ino.uf2



