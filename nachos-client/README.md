# Proyecto 2

## Introducción

En esta entrega, vamos a modificar la clases "AddrSpace" en los archivos "addrspace.h" y "addrspace.cc"
para darle soporte a la "paginación" en donde los elementos de memoria son manipulados como páginas.
Vamos a dividir la memoria de NachOS en 32 páginas de 128 bytes cada una (ambas constantes) y colocar las
estructuras de datos necesarias para realizar la administración de memoria.
También vamos a construir los llamados al sistema para la ejecución de hilos y procesos.

## Uso

El uso del programa es tal como es indicado en el README principal de NachOS:

* Ubicándose en la carpeta `NachOSx64/code/userprog`, uno debe primeramente llamar el comando `make depend`

* Hecho eso, ubicándose en la carpeta `NachOSx64/code`, uno llama el comando `make`

* Finalmente, uno llama `./userprog/nachos -x ./test/{PRUEBA}`, reemplazando `{PRUEBA}` por alguno de los programas de
  prueba que se hallan en la carpeta `test`

## Implementación

### addrspace

Para la funcionalidad de paginación en `addrspace` se optó por construir una clase aparte llamada `MemoryManager`, la
cual es encargada de mantener el rastro de cuáles páginas hay disponibles y de emitirlas a los procesos que buscan
construir su espacio de direcciones. La clase es un singleton compartido a nivel de sistema por todos los procesos en
ejecución, y se asegura de eliminar todas las páginas de la memoria al ser destruida.

Además se contruyó una clase `FileTable` que permite manetener el rastro de cuáles archivos están abiertos en un dado
espacio de direcciones, con el cuidado de asegurarse que esta tabla sea compartida entre hilos de un mismo proceso, acto
el cual es manejado dentro de `addrspace`.

Ambas de estas clases operan a base de `BitMap`, optando por una estrategia de ocupancia para sus elementos de borrado
retrasado. Cualquier elemento que se guarde en estas estructuras es borrado únicamente al finalizar la ejecución de la
máquina, y solamente cede su posición una vez la simulación determina que ya no se encuentra en uso el recurso indicado.

### exception

Para la funcionalidad agregada en `exception` se hizo uso de dos clases denominadas `ProcessTable` y `Process`, así como
el administrador de memoria previamente mencionado. Estas clases nos permiten mantener el rastro de los procesos que
están en espera en el sistema, facilitando así la posibilidad de ejecutarlos de forma auxiliar, y de unificar el flujo
de trabajo una vez que acaben. En general, es _scheduling_ es esencialmente cooperativo.

Además de la tabla de procesos, se agregaron clases `SemTable` para mantener el rastro de los semáforos generados de una
forma algo diferente a como se hace en la tabla de procesos. La tabla de semáforos utiliza más bien un `std::map` que
genera llaves de forma automática, en vez de un mapa de bits. Además de esta se agregó una clase de valor simple llamada
`Socket` para almacenar las características de TCP y SSL de un socket abierto.

Más allá de estas clases, el resto de la funcionalidad agregada en la forma de los diversos _syscalls_ solicitados se
hizo únicamente con base en lo expuesto en el libro de texto, siguiendo las descripciones naturales de las diversas
interrupciones, así como la interfaz que viene descrita para cada llamado de sistema en los comentarios.

## Pruebas

### addrspacetest

    ./userprog/nachos -x ./test/addrspacetest
    abcdefghijklmnopqrstuvwxyz{abcdefghijklmnopqrstuvwxyz{abcdefghijklmnopqrstuvwxyz{abcdefghijklmnopqrstuvwxyz{abcdefghijklmnopqrstuvwxyz{abcdefghijklmnopqrstuvwxyz{abcdefghijklmnopqrstuvwxyz{abcdefghijklmnopqrstuvwxyz{abcdefghijklmnopqrstuvwxyz{abcdefghijklmnopqrstuvwxyz{abcdefghijklmnopqrstuvwxyz{abcdefghijklmnopqrstuvwxyz{abcdefghijklmnopqrstuvwxyz{abcdefghijklmnopqrstuvwxyz{abcdefghijklmnopqrstuvwxyz{abcdefghijklmnopqrstuvwxyz{abcdefghijklmnopqrstuvwxyz{abcdefghijklmnopqrstuvwxyz{abcdefghijklmnopqrstuvwxyz{abcdefghijklmnopqrstuvwxyz{abcdefghijklmnopqrstuvwxyz{abcdefghijklmnopqrstuvwxyz{abcdefghijklmnopqrstuvwxyz{abcdefghijklmnopqrstuvwxyz{abcdefghijklmnopqrstuvwxyz{abcdefghijklmnopqrstuvwxyz{abcdefghijklmnopqrstuvwxyz{abcdefghijklmnopqrstuvwxyz{abcdefghijklmnopqrstuvwxyz{abcdefghijklmnopqrstuvwxyz{abcdefghijklmnopqrstuvwxyz{abcdefghijklmnopqrstuvwxyz{abcdefghijklmnopqrstuvwxyz{abcdefghijklmnopqrstuvwxyz{abcdefghijklmnopqrstuvwxyz{abcdefghijklmnopqrstuvwxyz{abcdefghijklmnopqrstuvwxyz{abcdefghijklmnopqrstuvwxy
    Exited code 0
    No threads ready or runnable, and no pending interrupts.
    Assuming the program completed.
    Machine halting!
    
    Ticks: total 31402, idle 0, system 630, user 30772
    Disk I/O: reads 0, writes 0
    Console I/O: reads 0, writes 0
    Paging: faults 0
    Network I/O: packets received 0, sent 0
    
    Cleaning up...

### shell

    ./userprog/nachos -x ./test/shell
    --
    ./test/addrspacetest
    abcdefghijklmnopqrstuvwxyz{abcdefghijklmnopqrstuvwxyz{abcdefghijklmnopqrstuvwxyz{abcdefghijklmnopqrstuvwxyz{abcdefghijkl
    mnopqrstuvwxyz{abcdefghijklmnopqrstuvwxyz{abcdefghijklmnopqrstuvwxyz{abcdefghijklmnopqrstuvwxyz{abcdefghijklmnopqrstuvwx
    yz{abcdefghijklmnopqrstuvwxyz{abcdefghijklmnopqrstuvwxyz{abcdefghijklmnopqrstuvwxyz{abcdefghijklmnopqrstuvwxyz{abcdefghi
    jklmnopqrstuvwxyz{abcdefghijklmnopqrstuvwxyz{abcdefghijklmnopqrstuvwxyz{abcdefghijklmnopqrstuvwxyz{abcdefghijklmnopqrstu
    vwxyz{abcdefghijklmnopqrstuvwxyz{abcdefghijklmnopqrstuvwxyz{abcdefghijklmnopqrstuvwxyz{abcdefghijklmnopqrstuvwxyz{abcdef
    ghijklmnopqrstuvwxyz{abcdefghijklmnopqrstuvwxyz{abcdefghijklmnopqrstuvwxyz{abcdefghijklmnopqrstuvwxyz{abcdefghijklmnopqr
    stuvwxyz{abcdefghijklmnopqrstuvwxyz{abcdefghijklmnopqrstuvwxyz{abcdefghijklmnopqrstuvwxyz{abcdefghijklmnopqrstuvwxyz{abc
    defghijklmnopqrstuvwxyz{abcdefghijklmnopqrstuvwxyz{abcdefghijklmnopqrstuvwxyz{abcdefghijklmnopqrstuvwxyz{abcdefghijklmno
    pqrstuvwxyz{abcdefghijklmnopqrstuvwxyz{abcdefghijklmnopqrstuvwxy
    Exited code 0
    --
    ./test/halt
    No threads ready or runnable, and no pending interrupts.
    Assuming the program completed.
    Machine halting!
    
    Ticks: total 33913, idle 0, system 2180, user 31733
    Disk I/O: reads 0, writes 0
    Console I/O: reads 0, writes 0
    Paging: faults 0
    Network I/O: packets received 0, sent 0
    
    Cleaning up...

### copy

Copy nunca finaliza, ya que mientras pueda leer del archivo, continua en el loop de while. No entiendo por qué se le
programó este comportamiento, ya que siempre puede seguir leyendo el archivo que desea desde el principio, cosa que hace
infinitamente. En cualquier caso, la aparición de `nachos.2` con un número de copias repetidas del contenido de
`nachos.1` indica que los syscalls de Create, Open, Read, y Write funcionan correctamente.