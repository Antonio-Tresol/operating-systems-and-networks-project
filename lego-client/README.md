# LEGO Client

Este programa conecta a un servidor de figuras de LEGO y obtiene las partes necesarias para construir una dada figura.

## Tabla de Contenidos

- [Requisitos](#requisitos)
- [Compilación](#compilación)
- [Uso](#uso)
- [Estructura del Programa](#estructura-del-programa)
- [Licencia](#licencia)

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

Ejecuta el programa proporcionando el nombre de una figura LEGO como argumento:

    ./lego-client horse

El programa buscará información sobre la figura y mostrará los detalles en la salida estándar.

## Estructura del programa

El programa está organizado en varias clases y módulos que trabajan juntos para buscar y mostrar la información de las figuras LEGO.

- `Logger`: Clase de registro para mostrar información y mensajes de error en la salida estándar.
- `Figure`: Clase que representa una figura LEGO con su nombre y lista de partes.
- `FigureController`: Controlador encargado de gestionar la búsqueda y visualización de las figuras.
- `FigureRepository`: Repositorio encargado de buscar y procesar la información de las figuras desde la web.
- `HttpsClient`: Cliente HTTPS que realiza solicitudes GET a través de conexiones SSL.
- `IPv4SslSocket`: Clase que maneja conexiones SSL sobre IPv4.

## Licencia

Copyright © 2023 Ariel Arevalo Alvarado. Todos los derechos reservados.  
Copyright © 2023 Antonio Badilla Olivas. Todos los derechos reservados.  
Copyright © 2023 Jean Paul Chacon Gonzalez. Todos los derechos reservados.  
Copyright © 2023 Geancarlo Rivera Hernandez. Todos los derechos reservados.  
