<p align="center">
    <img src="/res/readme/duckGameTitle.png" alt="Logo del Juego" width="250" />
</p>

Repositorio para el Trabajo Práctico grupal de la materia "Taller de Programacion", Cátedra Veiga, 2do Cuatrimestre 2024.

<hr/>

## Integrantes

| <center>Alumno</center>          | <center>Padrón</center> | <center>Mail</center>  | <center>GitHub</center>                                                                                                                                                          |
| :------------------------------- | :---------------------: | :--------------------- | :------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Marcelo Agustin Origoni**      |         109903          | morigoni@fi.uba.ar     | <img align="center" src="https://github.com/MarceloAgustinOrigoniGuillaume.png" height=32 width=32 /> [MarceloAgustinOrigoni](https://github.com/MarceloAgustinOrigoniGuillaume) |
| **Alejandro Schamun**            |         108545          | aschamun@fi.uba.ar     | <img align="center" src="https://github.com/AleSchamun.png" height=32 width=32 /> [AleSchamun](https://github.com/AleSchamun)                                                    |
| **Sebastian Mauricio Vintoñuke** |         106063          | svintonuke@fi.uba.ar         | <img align="center" src="https://github.com/SebastianVintonuke.png" height=32 width=32 /> [SebastianVintonuke](https://github.com/SebastianVintonuke)                            |
| **Agustin Pelliciari**           |         108172          | apelliciari@fi.uba.ar  | <img align="center" src="https://github.com/agpelliciari.png" height=32 width=32 /> [agpelliciari](https://github.com/agpelliciari)                                              |

<hr/>

## Manual de Usuario

### Compilacion y Buildeo
A partir del siguiente comando se compilara el juego e instalaran las dependencias necesarias para su ejecucion

```sh
./build_game.sh
```
Las **dependencias** necesarias son las siguientes:
- SDL2 / SDL2pp (v0.18.1)
- SDL Mixer (v2.6.3) / TTF (v2.20.2) / Image (v2.6.3)
- Qt

**Sistema operativo** necesario para ejecutar el juego:
- Ubuntu 24.02
### Ejecucion del juego

Para iniciar una partida se debera levantar un **servidor** del juego, esto es posible con el siguiente comando:
```sh
./taller_server 2048
```
Luego, en una nueva terminal, sera necesario conectarse a este servidor mediante un **cliente**, por esta razon se debe ejecutar la siguiente linea:
```sh
./taller_client
```
Para crear y cargar un mapa personalizado utilizando elementos del juego debera ejecutar el siguiente comando:

```sh
./taller_editor
```
Tambien tendra la posibilidad de modificar un mapa previamente creado y cargado a traves del comando anterior.


Para validar distintas funcionalidades del juego tendra tests automatizados que se ejecutaran luego de la siguiente linea:

```sh
./taller_tests
```

### Controles In-Game

| Control                   | Action                           |
| ------------------------- | -------------------------------- |
| `M`                       | Mute Music                       |

| Player 1    | Player2     | Action                           |
| ----------- | ----------- | -------------------------------- |
| `A`         | `→`         | Go Left                          |
| `D`         | `←`         | Go Right                         |
| `W`         | `↑`         | Jump                             |
| `S`	      | `↓`         | Ragdoll                          |
| `E`	      | `O`         | Aim Up                           |
| `C`         | `L`         | Grab Weapon / Put on Armour, Hat |
| `V`         | `P`         | Fire Weapon                      |

### Controles del Editor

| Control                     | Action       |
| --------------------------- | ------------ |
| `Left Mouse Click`          | Add Block    |
| `Right Mouse Click`         | Remove Block |
| `Scroll`                    | Change Block |
| `Ctrl + Scroll Up`          | Zoom In      |
| `Ctrl + Scroll Down`        | Zoom Out     |
| `Middle Mouse Click + Drag` | Drag the Map |


### Armas

- Granada
- Banana
- Pew-Pew Laser
    ![Alt Text](/res/readme/gifs/pewpew.gif)
- Laser Rifle
- AK47
- Pistola de Duelos
- Pistola Cowboy
    ![Alt Text](/res/readme/gifs/cowboy.gif)
- Magnum
- Escopeta
    ![Alt Text](/res/readme/gifs/shotgun.gif)
- Sniper
    ![Alt Text](/res/readme/gifs/sniper.gif)
- Armaduras y Cascos

<hr>

## Creditos

Los siguientes archivos:

- socket.cpp y socket.h
- resolver.cpp y resolver.h
- resolvererror.cpp y resolvererror.h
- liberror.cpp y liberror.h

Fueron tomados del repositorio [hands-on-sockets](https://github.com/eldipa/hands-on-sockets-in-cpp) con licencia: **GPL v2**

Los siguientes archivos:

- thread.h
- queue.h

Fueron tomados del repositorio [hands-on-threads](https://github.com/eldipa/hands-on-threads) con licencia: **GPL v2**
