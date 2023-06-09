# NachOS Client

Este programa conecta a un servidor de figuras de LEGO y obtiene las partes necesarias para construir una dada figura haciendo uso del ambiente NachOS.

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

El uso del programa es tal como es indicado en el README principal de NachOS:

    cd userprog/
    make depend
    cd ..
    make

## Uso

Ejecuta el programa de la siguiente forma:

    ./userprog/nachos -x ./test/client

El programa solicitará el nombre de la figura por entrada estándar.

## Estructura del programa

El programa se vale de la estructura nativa del ambiente NachOS, así como de la implementación de los llamados a sistema necesarios para llevar a cabo la funcionalidad mínima para operar como cliente.

Los llamados implementados son los siguientes:

- `Read`: Lee desde un descriptor de archivo, retorna el número de bytes leídos.
- `Write`: Escribe a un descriptor de archivo, retorna el número de bytes escritos.
- `Socket`: Genera un nuevo socket, retorna su descriptor de archivo.
- `Connect`: Conecta un socket a una dirección y puerto, retorna el resultado.
- `Close`: Cierra la conexión a un socket, no retorna nada.

Además, se escribe y se prepara `client.c`, el cual compila al programa de prueba `client` que se ejecuta para hacer el llamado al servidor.

## Licencia

Copyright © 2023 Ariel Arevalo Alvarado. Todos los derechos reservados.  
Copyright © 2023 Antonio Badilla Olivas. Todos los derechos reservados.  
Copyright © 2023 Jean Paul Chacon Gonzalez. Todos los derechos reservados.  
Copyright © 2023 Geancarlo Rivera Hernandez. Todos los derechos reservados.  
