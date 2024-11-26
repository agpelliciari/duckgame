<p align="center">
    <img src="/res/duckGameTitle.png" alt="Logo del Juego" width="250" />
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

<hr width="100%" align="left" />

<hr/>

## Compilacion y buildeo
```sh
./build_game.sh
```

<hr width="100%" align="left" />

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

<hr width="100%" align="left" />

<hr/>

## Comandos
- Jugador 1:
  - `→` : Moverse a la derecha
  - `←` : Moverse a la izquierda
  - `↑` : Apuntar hacia arriba
  - `↓` : Agacharse
  - `Espacio` : Saltar
  - `P` : Disparar
  - `O` : Agarrar un objeto (arma/casco/armadura)
  - `L` : Soltar un objeto
  - `M` : Apagar musica

- Jugador 2 (en caso de seleccionar duos):
  - `D` : Moverse a la derecha
  - `A` : Moverse a la izquierda
  - `E` : Apuntar hacia arriba
  - `S` : Agacharse
  - `W` : Saltar
  - `G` : Disparar
  - `T` : Agarrar un objeto (arma/casco/armadura)
  - `F` : Soltar un objeto

<hr width="100%" align="left" />

<hr/>

## Creditos

Los siguientes archivos:

- socket.cpp y socket.h
- resolver.cpp y resolver.h
- resolvererror.cpp y resolvererror.h
- liberror.cpp y liberror.h

fueron tomados del repositorio [hands-on-sockets](https://github.com/eldipa/hands-on-sockets-in-cpp) con licencia: **GPL v2**

Los siguientes archivos:

- thread.h
- queue.h

fueron tomados del repositorio [hands-on-threads](https://github.com/eldipa/hands-on-threads) con licencia: **GPL v2**
