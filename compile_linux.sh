#!/bin/bash
DIR="$( cd -P "$( dirname "$0" )" && pwd )"
LEFT=$DIR/chonkybois_build/firmware-left
RIGHT=$DIR/chonkybois_build/firmware-right
KB=keyboards/lil_chonky_bois

BSP_PATH=.arduino15/packages/adafruit/hardware/nrf52
BSP_VERSION=0.24.0
rm -rf $DIR/chonkybois_build
mkdir -p $DIR/chonkybois_build

cp -r $DIR/firmware $LEFT
cp -r $DIR/firmware $RIGHT

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


arduino-cli compile \
	--fqbn community_nrf52:nrf52:pca10056 \
	$LEFT \
	--output-dir $DIR/build-left

python3 $HOME/$BSP_PATH/$BSP_VERSION/tools/uf2conv/uf2conv.py \
	$DIR/build-left/build/firmware.ino.hex -c -f 0xADA52840 \
	-o $DIR/build-left/build/firmware-left.ino.uf2

arduino-cli compile \
	--fqbn community_nrf52:nrf52:pca10056 \
	$RIGHT \
	--output-dir $DIR/build-right

python3 $HOME/$BSP_PATH/$BSP_VERSION/tools/uf2conv/uf2conv.py \
	$DIR/build-right/build/firmware.ino.hex -c -f 0xADA52840 \
	-o $DIR/build-right/build/firmware-right.ino.uf2



