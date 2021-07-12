#!/bin/bash
BSP_URL=https://github.com/jpconstantineau/Community_nRF52_Arduino/releases/latest/download/package_jpconstantineau_boards_index.json
BSP_PATH=.arduino15/packages/community_nrf52/hardware/nrf52
BSP_URL_ADA=https://adafruit.github.io/arduino-board-index/package_adafruit_index.json
BSP_PATH_ADA=.arduino15/packages/adafruit/hardware/nrf52
pip3 install adafruit-nrfutil
arduino-cli config init
arduino-cli core update-index
arduino-cli core update-index --additional-urls $BSP_URL_ADA
arduino-cli core install adafruit:nrf52 --additional-urls $BSP_URL_ADA
arduino-cli core update-index --additional-urls $BSP_URL
arduino-cli core install community_nrf52:nrf52 --additional-urls $BSP_URL
arduino-cli core list
arduino-cli board listall
arduino-cli lib list
