# LEGO Proxy

Este programa ejecuta a un servidor que redirige solicitudes y respuestas de figuras Lego.

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

Cree un directorio de compilación, navegue hacia él y ejecute CMake para generar el Makefile:

    mkdir build
    cd build
    cmake ..

Después de generar el Makefile, compile el programa:

    make

## Uso

El programa se ejecuta de la siguiente manera:

    ./lego-proxy [certPath]

Donde `certPath` es la ubicación relativa del archivo de certificado.

El programa anterior pone a correr al servidor que provee las figuras.

## Licencia

Copyright © 2023 Ariel Arevalo Alvarado. Todos los derechos reservados.  
Copyright © 2023 Antonio Badilla Olivas. Todos los derechos reservados.  
Copyright © 2023 Jean Paul Chacon Gonzalez. Todos los derechos reservados.  
Copyright © 2023 Geancarlo Rivera Hernandez. Todos los derechos reservados.
