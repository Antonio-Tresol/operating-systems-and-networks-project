# LEGO Server

Este programa ejecuta a un servidor que provee a clientes con figuras de lego.

## Tabla de Contenidos

- [Requisitos](#requisitos)
- [Compilación](#compilación)
- [Uso](#uso)
- [Estructura del Programa](#estructura-del-programa)
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

    ./lego-server [certPath]

Donde `certPath` es la ubicación relativa del archivo de certificado.

El programa anterior pone a correr al servidor que provee las figuras.

## Estructura del programa

El programa está organizado en varias clases y módulos que trabajan juntos para realizar las distintas funcionalidades del servidor.

- `Logger`: Clase de registro para mostrar información y mensajes de error en la salida estándar.
- `Queue`: Clase de cola genérica que es segura para programas multi-hilo.
- `Semaphore`: Clase encapsuladora que funciona como interfaz para el uso de los semáforos de POSIX.
- `FigureController`: Controlador encargado de gestionar la búsqueda y visualización de las figuras.
- `FigureHtmlRepository`: Repositorio encargado de buscar y procesar la información de las figuras desde la web.
- `FigureHttpsServer`: Clase encargada del manejo de las peticiones entrantes que llegan al servidor.
- `Ipv4SslSocket`: Clase que maneja conexiones SSL sobre IPv4.

Es de suma importancia destacar que tanto la clase `Queue` como la clase `Semaphore` fueron tomadas de cursos anteriores y fueron realizadas por el profesor Jeisson Hidalgo.

## Licencia

Copyright © 2023 Ariel Arevalo Alvarado. Todos los derechos reservados.
Copyright © 2023 Antonio Badilla Olivas. Todos los derechos reservados.
Copyright © 2023 Jean Paul Chacon Gonzalez. Todos los derechos reservados.
Copyright © 2023 Geancarlo Rivera Hernandez. Todos los derechos reservados.

## Información sobre el Cliente

Si desea conocer información sobre el cliente se debe dirigir al
siguiente [archivo](../lego-client/README.md).