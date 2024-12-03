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

# Manual de Usuario

## Índice de Contenidos

- [Manual de Usuario](#manual-de-usuario)
  - [Índice de Contenidos](#índice-de-contenidos)
  - [Requisitos del Sistema](#requisitos-del-sistema)
  - [Instalacion Automatizada](#instalacion-automatizada)
    - [Pasos para instalar el juego correctamente](#pasos-para-instalar-el-juego-correctamente)
  - [Ejecucion del juego](#ejecucion-del-juego)
    - [1. Levantar el servidor del juego](#1-levantar-el-servidor-del-juego)
    - [2. Conectar un cliente](#2-conectar-un-cliente)
  - [Editor de Mapas](#editor-de-mapas)
    - [Como crear un nuevo mapa](#como-crear-un-nuevo-mapa)
    - [Controles del Editor](#controles-del-editor)
  - [Tests Automatizados](#tests-automatizados)
    - [Comandos para ejecutar los tests](#comandos-para-ejecutar-los-tests)
      - [1. Protocolo](#1-protocolo)
      - [2. Integracion](#2-integracion)
      - [3. Logica del juego](#3-logica-del-juego)
  - [In-Game](#in-game)
    - [Controles](#controles)
    - [Equipamento](#equipamento)
      - [Pew-Pew Laser](#pew-pew-laser)
      - [Pistola Cowboy](#pistola-cowboy)
      - [Escopeta](#escopeta)
      - [Sniper](#sniper)
  - [Creditos](#creditos)

## Requisitos del Sistema

**Sistema operativo necesario:**  

- Ubuntu 24.02  

**Dependencias necesarias:**  

- SDL2: v0.18.1  
  
- SDL Mixer: v2.6.3  

- SDL TTF: v2.20.2  

- SDL Image: v2.6.3  

- Qt: Qt 5.15.10  

Para instalar las dependencias necesarias, ejecuta el siguiente comando:

```sh
./build_game.sh
```

## Instalacion Automatizada

Para simplificar la instalación, detallamos una serie de pasos que debera seguir para poder ejecutar el juego.

### Pasos para instalar el juego correctamente

1. Clonar el repositorio del proyecto:

```sh
git clone https://github.com/MarceloAgustinOrigoniGuillaume/duckgame.git
cd duckgame
```

2. Ejecutar el script de instalacion proporcionado en [Requisitos del sistema](#requisitos-del-sistema). Este script se encargara de:
   - Instalar las dependencias necesarias.
   - Configurar los archivos requeridos.
   - Compilar el juego.
  
3. Una vez completado, el juego estara listo para usarse.

## Ejecucion del juego

### 1. Levantar el servidor del juego

Ejecuta el siguiente comando para iniciar el servidor:

```sh
./taller_server 2048
```

### 2. Conectar un cliente

Abre una nueva terminal y ejecuta el siguiente comando:

```sh
./taller_client
```

## Editor de Mapas

El editor te permite crear y modificar mapas personalizados

### Como crear un nuevo mapa

1. Ejecutar el editor con el comando:

```sh
./taller_editor
```

2. Utilize los controles especificados dentro de [Controles del editor](#controles-del-editor) para construir su mapa.

3. Para guardar su mapa personalizado seleccione el boton `Save` .

**Para poder utilizar en el juego los mapas personalizados los debera guardar en la carpeta `/res/maps/`**

4. Para cargar un mapa ya creado seleccione el boton `Load` . 

### Controles del Editor

| Control                     | Action       |
| --------------------------- | ------------ |
| `Left Mouse Click`          | Add Block    |
| `Right Mouse Click`         | Remove Block |
| `Scroll`                    | Change Block |
| `Ctrl + Scroll Up`          | Zoom In      |
| `Ctrl + Scroll Down`        | Zoom Out     |
| `Middle Mouse Click + Drag` | Drag the Map |

## Tests Automatizados

El proyecto incluye un conjunto de pruebas automatizadas que validan diferentes aspectos del sistema, desde la lógica interna hasta la interacción con sockets y threads. A continuación, se describen los comandos disponibles y sus funciones:

### Comandos para ejecutar los tests

#### 1. Protocolo

Se testea el protocolo utilizando mocks de sockets y sin threads. Esto garantiza que los mensajes sean correctamente enviados y recibidos bajo condiciones controladas.

```sh
./tester_protocol
```

**Que valida:**

- Envío y recepción de datos a través del protocolo.

- Comportamiento esperado en condiciones de red simuladas.

#### 2. Integracion

Ejecuta pruebas de integración que incluyen el lobby, el servidor con sockets reales, y realiza benchmarks básicos para evaluar el rendimiento.

```sh
./tester_integration
```

**Que valida:**

- Interacción entre diferentes componentes del sistema.

- Correcto manejo de conexiones y comunicaciones reales (sockets y threads).

#### 3. Logica del juego

Prueba la lógica del juego aislada de los threads, asegurándose de que las operaciones internas se realicen correctamente y que los DTOs (Data Transfer Objects) se generen y envíen adecuadamente.

```sh
./tester_logic
```

**Que valida:**

- Reglas de la lógica del juego.

- Generación y procesamiento de datos enviados entre cliente y servidor.

## In-Game

### Controles

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

### Cajas

Las cajas se destruyen al recibir daño. Al romperse, pueden contener ítems en su interior o infligir daño en área.

![Alt Text](/res/readme/gifs/box-arma.gif)

![Alt Text](/res/readme/gifs/box-explosion.gif)


### Equipamento

| <center>Nombre</center>| <center>Imagen</center> | <center>Descripción</center> | <center>Capturas</center> |
| ----------------------- | ----------------------- | ---------------------------- | --------------------------------- |
| <center>Granada</center> | <center>![Granada](/res/readme/weapons/grenade.png)</center> | <center>Una granada estándar con daño en área.</center> | <center>[Granada In Game](#granada)</center> |
| <center>Banana</center> | <center>![Banana](/res/readme/weapons/banana.png)</center> | <center>Provocara un resbalon al que la pise. Para levantarse debera presionar la tecla corresponidente a la accion "Ragdoll".</center> | <center>[Banana In Game](#banana)</center> |
| <center>Pew-Pew Laser</center> | <center>![Pew Pew Laser](/res/weapons/pewpewLaser.png)</center> | <center>Laser semi-automatico de gran alcance</center> | <center>[Pew Pew Laser In Game](#pew-pew-laser)</center> |
| <center>Laser Rifle</center> | <center>![Laser Rifle](/res/weapons/laserRifle.png)</center> | <center>Un láser rápido con capacidad de disparo continuo, sus balas pueden rebotar en paredes.</center> | <center>[Laser Rifle In Game](#laser-rifle)</center> |
| <center>AK47</center> | <center>![AK47](/res/weapons/ak47.png)</center> | <center>Rifle automático con alto daño por segundo pero mucho retroceso.</center> | <center>[AK47 In Game](#ak47)</center> |
| <center>Pistola de Duelos</center> | <center>![Duelos](/res/readme/weapons/pistol.png)</center> | <center>Ideal para enfrentamientos uno a uno.</center> | <center>[Pistola de Duelos In Game](#pistola-de-duelos)</center> |
| <center>Pistola Cowboy</center> | <center>![Cowboy](/res/weapons/cowboyPistol.png)</center> | <center>Rápida y precisa, con estilo del viejo oeste.</center> | <center>[Cowboy In Game](#pistola-cowboy)</center> |
| <center>Magnum</center> | <center>![Magnum](/res/weapons/magnum.png)</center> | <center>Revolver poderoso con gran daño.</center> | <center>[Magnum In Game](#magnum)</center> |
| <center>Escopeta</center> | <center>![Escopeta](/res/weapons/shotgun.png)</center> | <center>Daño devastador a corta distancia.</center> | <center>[Escopeta In Game](#escopeta)</center> |
| <center>Sniper</center> | <center>![Sniper](/res/weapons/sniper.png)</center> | <center>Arma de largo alcance muy poderosa.</center> | <center>[Sniper In Game](#sniper)</center> |
| <center>Armadura de cuerpo</center> | <center>![Armadura](/res/armors/chestPlatePickup.png)</center> | <center>Absorbe balas/lasers sin producirle daño al que lo lleve.</center> | <center>[Armadura In Game](#armadura)</center> |
| <center>Armadura de cabeza</center> | <center>![Casco](/res/armors/helmetPickup.png)</center> | <center>Absorbe balas/lasers sin producirle daño al que lo lleve.</center> | <center>[Casco In Game](#casco)</center> |

#### Granada

![Alt Text](/res/readme/gifs/granada.gif)

#### Banana

![Alt Text](/res/readme/gifs/banana.gif)

#### Pew-Pew Laser
  
![Alt Text](/res/readme/gifs/pewpew.gif)

#### Laser Rifle
  
![Alt Text](/res/readme/gifs/laser-rifle.gif)

#### AK47

![Alt Text](/res/readme/gifs/ak47.gif)

#### Pistola de Duelos

![Alt Text](/res/readme/gifs/duel-pistol.gif)

#### Pistola Cowboy
  
![Alt Text](/res/readme/gifs/cowboy.gif)

#### Magnum

![Alt Text](/res/readme/gifs/magnum.gif)
  
#### Escopeta

![Alt Text](/res/readme/gifs/shotgun.gif)

#### Sniper
  
![Alt Text](/res/readme/gifs/sniper.gif)

#### Armadura
  
![Alt Text](/res/readme/gifs/armadura.gif)

#### Casco
  
![Alt Text](/res/readme/gifs/casco.gif)

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
