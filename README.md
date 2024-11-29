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

## Compilacion y Buildeo
```sh
./build_game.sh
```

<hr/>

## Ejecucion del juego

Servidor:

```sh
./taller_server 2048
```

Cliente:

```sh
./taller_client
```

Editor de mapas:

```sh
./taller_editor
```
Tests:

```sh
./taller_tests
```

<hr/>

### In-Game Controls

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

### Editor Controls

| Control                     | Action       |
| --------------------------- | ------------ |
| `Left Mouse Click`          | Add Block    |
| `Right Mouse Click`         | Remove Block |
| `Scroll`                    | Change Block |
| `Ctrl + Scroll Up`          | Zoom In      |
| `Ctrl + Scroll Down`        | Zoom Out     |
| `Middle Mouse Click + Drag` | Drag the Map |

<hr>

## Weapons

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
