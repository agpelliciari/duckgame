#!/bin/bash

sudo apt-get --yes install update

#GENERAL
echo Instalando paquetes generales necesarios...
sudo apt-get --yes install cmake
sudo apt-get --yes install g++
sudo apt-get --yes install build-essential libgl1-mesa-dev libclang-16-dev

#SDL2PP
./build_sdl2pp.sh

#QT

#COMPILACION DEL JUEGO
echo "Compilando el juego..."
cmake . && make
