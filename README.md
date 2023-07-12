# LEGO PI

Este proyecto incluye un cliente, un servidor de piezas, y un servidor proxy que proveen figuras de Lego.

## Tabla de Contenidos

- [Requisitos](#requisitos)
- [Compilación](#compilación)
- [Uso](#uso)
- [Licencia](#licencia)
- [Información sobre cliente](#información-sobre-el-cliente)

## Requisitos

- Compilador C++17
- CMake versión 3.24 o superior
- Biblioteca OpenSSL

## Compilación

Desde el directorio root del proyecto, cree un directorio de compilación, navegue hacia él y ejecute CMake para generar
el Makefile:

    mkdir build
    cd build
    cmake ..

Después de generar el Makefile, compile el programa:

    make

## Uso

El programa se ejecuta de la siguiente manera:

    ./lego-proxy [certPath]

    ./lego-server [certPath]

    ./lego-client [proxyAddress] [figure]

Donde `certPath` es la ubicación relativa del archivo de certificado, `proxyAddress` es la dirección IP del servidor
proxy, y `figure` es el nombre de una de las figuras por solicitar.

Los comandos anteriores ponen a correr al servidor proxy, el servidor de piezas, y el cliente, en orden, para demostrar
el funcionamiento normal del proyecto.

## Licencia

Copyright © 2023 Ariel Arevalo Alvarado. Todos los derechos reservados.  
Copyright © 2023 Antonio Badilla Olivas. Todos los derechos reservados.  
Copyright © 2023 Jean Paul Chacon Gonzalez. Todos los derechos reservados.  
Copyright © 2023 Geancarlo Rivera Hernandez. Todos los derechos reservados.

## Información sobre los subproyectos

* [Cliente](./lego-client/README.md)
* [Servidor](./lego-server/README.md)
* [Proxy](./lego-proxy/README.md)
