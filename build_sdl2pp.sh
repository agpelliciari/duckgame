#!/bin/bash

sudo apt-get --yes install update

#SDL2
echo Instalando paquetes necesarios para SDL2...
sudo apt-get --yes install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev libsdl2-gfx-dev

echo Instalando dependencias necesarias para SDL2pp...
SDL2PP_DIR="SDL2pp"
BUILD_DIR="build"
sudo apt-get --yes install libjpeg-dev libpng-dev libfreetype-dev libopusfile-dev libflac-dev libxmp-dev libfluidsynth-dev libwavpack-dev cmake libmodplug-dev libsdl2-dev
mkdir -p "$SDL2PP_DIR"
cd "$SDL2PP_DIR" || exit 1

#SDL2_IMAGE
echo Instalando SDL2_image...
REPO_SDL_IMAGE_URL="https://github.com/libsdl-org/SDL_image/archive/refs/tags/release-2.6.3.zip" # URL del ZIP del repositorio
SDL_IMAGE_ZIP_FILE="sdl2-image.zip" # Nombre del archivo ZIP descargado
SDL_IMAGE_EXTRACT_DIR="sdl2-image" # Directorio donde se descomprime el contenido

echo "Descargando el repositorio SDL2_image..."
curl -L -o "$SDL_IMAGE_ZIP_FILE" "$REPO_SDL_IMAGE_URL"
if [ $? -ne 0 ]; then
    echo "Error: No se pudo descargar el repositorio."
    exit 1
fi

echo "Descomprimiendo el repositorio SDL2_image..."
unzip -o "$SDL_IMAGE_ZIP_FILE"
if [ $? -ne 0 ]; then
    echo "Error: No se pudo descomprimir el archivo ZIP."
    exit 1
fi

cd "$SDL_IMAGE_EXTRACT_DIR" || exit 1
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR" || exit 1
cmake ..
make -j4
sudo make install

cd ../../ || exit 1

#SDL2_MIXER
echo Instalando SDL2_mixer...
REPO_SDL_MIXER_URL="https://github.com/libsdl-org/SDL_mixer/archive/refs/tags/release-2.6.3.zip" # URL del ZIP del repositorio
SDL_MIXER_ZIP_FILE="sdl2-mixer.zip" # Nombre del archivo ZIP descargado
SDL_MIXER_EXTRACT_DIR="sdl2-mixer" # Directorio donde se descomprime el contenido

echo "Descargando el repositorio SDL2_mixer..."
curl -L -o "$SDL_MIXER_ZIP_FILE" "$REPO_SDL_MIXER_URL"
if [ $? -ne 0 ]; then
    echo "Error: No se pudo descargar el repositorio."
    exit 1
fi

echo "Descomprimiendo el repositorio SDL2_mixer..."
unzip -o "$SDL_MIXER_ZIP_FILE"
if [ $? -ne 0 ]; then
    echo "Error: No se pudo descomprimir el archivo ZIP."
    exit 1
fi

cd "$SDL_MIXER_EXTRACT_DIR" || exit 1
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR" || exit 1
cmake ..
make -j4
sudo make install

cd ../../ || exit 1

#SDL2_TTF
echo Instalando SDL2_ttf...
REPO_SDL_TTF_URL="https://github.com/libsdl-org/SDL_mixer/archive/refs/tags/release-2.6.3.zip" # URL del ZIP del repositorio
SDL_TTF_ZIP_FILE="sdl2-ttf.zip" # Nombre del archivo ZIP descargado
SDL_TTF_EXTRACT_DIR="sdl2-ttf" # Directorio donde se descomprime el contenido

echo "Descargando el repositorio SDL2_ttf..."
curl -L -o "$SDL_TTF_ZIP_FILE" "$REPO_SDL_TTF_URL"
if [ $? -ne 0 ]; then
    echo "Error: No se pudo descargar el repositorio."
    exit 1
fi

echo "Descomprimiendo el repositorio SDL2_ttf..."
unzip -o "$SDL_TTF_ZIP_FILE"
if [ $? -ne 0 ]; then
    echo "Error: No se pudo descomprimir el archivo ZIP."
    exit 1
fi

cd "$SDL_TTF_EXTRACT_DIR" || exit 1
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR" || exit 1
cmake ..
make -j4
sudo make install

cd ../../ || exit 1

#SDL2PP 0.18
echo Instalando SDL2PP...
REPO_SDL2PP_URL="https://github.com/libSDL2pp/libSDL2pp/archive/refs/tags/0.18.1.zip" # URL del ZIP del repositorio
SDL2PP_ZIP_FILE="sdl2pp-018.zip" # Nombre del archivo ZIP descargado
SDL2PP_EXTRACT_DIR="sdl2pp-018" # Directorio donde se descomprime el contenido

echo "Descargando el repositorio SDL2PP..."
curl -L -o "$SDL2PP_ZIP_FILE" "$REPO_SDL2PP_URL"
if [ $? -ne 0 ]; then
    echo "Error: No se pudo descargar el repositorio."
    exit 1
fi

echo "Descomprimiendo el repositorio SDL2PP..."
unzip -o "$SDL2PP_ZIP_FILE"
if [ $? -ne 0 ]; then
    echo "Error: No se pudo descomprimir el archivo ZIP."
    exit 1
fi

cd "$SDL2PP_EXTRACT_DIR" || exit 1
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR" || exit 1
cmake ..
make -j4
sudo make install

cd ../../../ || exit 1