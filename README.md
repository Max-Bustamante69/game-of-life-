# Juego de la Vida de Conway

Este proyecto es una implementación del famoso autómata celular "Juego de la Vida" de John Conway, desarrollado en C utilizando la biblioteca SDL2 para la interfaz gráfica.

## Propósito del Proyecto

Este proyecto fue desarrollado como trabajo final para la materia de Organización de Computadores en la Universidad EAFIT. El objetivo principal fue aplicar los conceptos aprendidos en el curso, incluyendo:

- Programación en lenguaje C
- Manejo de memoria y estructuras de datos
- Uso de bibliotecas externas (SDL2)
- Optimización de código
- Operaciones a nivel de bits para optimización de memoria

## Implementación Técnica

### Optimización con Operaciones de Bits

El proyecto implementa una optimización significativa utilizando operaciones a nivel de bits en lugar de booleanos:

- Uso de `unsigned char` para almacenar el estado de las células (1 bit por célula)
- Operaciones de bits para manipular estados:
  - `& 1`: Para verificar si una célula está viva
  - `^= 1`: Para alternar el estado de una célula
  - `|= 1`: Para establecer una célula como viva
  - `&= 0`: Para establecer una célula como muerta

Esta implementación reduce el uso de memoria y mejora el rendimiento al:

- Reducir el tamaño de almacenamiento de cada célula de 1 byte (bool) a 1 bit
- Utilizar operaciones de bits que son más eficientes que operaciones lógicas
- Minimizar el uso de memoria al almacenar solo la información necesaria
- Eliminar la dependencia de tipos booleanos estándar para mayor consistencia en el manejo de bits

## Equipo de Desarrollo

Este proyecto fue desarrollado por:

- **Maximiliano Bustamante**
- **Valeria Hornung**

## Descripción

El Juego de la Vida es un autómata celular que simula la evolución de una población de células siguiendo reglas simples. Cada célula puede estar viva o muerta, y su estado en la siguiente generación depende del número de vecinos vivos que tenga.

### Reglas del Juego

1. Una célula viva con menos de 2 vecinos vivos muere (soledad)
2. Una célula viva con más de 3 vecinos vivos muere (sobrepoblación)
3. Una célula muerta con exactamente 3 vecinos vivos se convierte en una célula viva (reproducción)
4. Una célula viva con 2 o 3 vecinos vivos sobrevive a la siguiente generación

## Estructura del Código

El proyecto está organizado de la siguiente manera:

### Constantes y Configuración

- `WINDOW_WIDTH` y `WINDOW_HEIGHT`: Dimensiones de la ventana
- `CELL_SIZE`: Tamaño de cada célula en píxeles
- `GRID_ROWS` y `GRID_COLS`: Dimensiones de la grilla

### Funciones Principales

- `count_neighbors`: Cuenta los vecinos vivos de una célula
- `update_grid`: Actualiza el estado de la grilla según las reglas de Conway
- `clear_grid`: Limpia la grilla, estableciendo todas las células como muertas

### Control de la Simulación

- Espacio: Pausa/Reanuda la simulación
- C: Limpia la grilla
- ESC: Cierra la aplicación
- Click del mouse: Activa/Desactiva células

## Requisitos del Sistema

- Compilador de C (gcc, clang, o MSVC)
- SDL2
- Make (opcional, para usar el Makefile)

## Instalación

### Windows

1. Instalar MinGW o MSVC:

   - MinGW: Descargar e instalar desde [MinGW website](https://www.mingw-w64.org/)
   - MSVC: Instalar Visual Studio Community Edition

2. Instalar SDL2:

   - Descargar SDL2 development libraries desde [SDL website](https://www.libsdl.org/download-2.0.php)
   - Extraer los archivos en una ubicación de tu elección
   - Añadir la ruta de los binarios de SDL2 al PATH del sistema

3. Compilar el proyecto:
   ```bash
   gcc main.c -o game_of_life -I<ruta_a_SDL2_include> -L<ruta_a_SDL2_lib> -lSDL2main -lSDL2
   ```

### Linux

1. Instalar las dependencias:

   ```bash
   sudo apt-get update
   sudo apt-get install build-essential libsdl2-dev
   ```

2. Compilar el proyecto:
   ```bash
   gcc main.c -o game_of_life -lSDL2main -lSDL2
   ```

### macOS

1. Instalar Homebrew si no está instalado:

   ```bash
   /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
   ```

2. Instalar SDL2:

   ```bash
   brew install sdl2
   ```

3. Compilar el proyecto:
   ```bash
   gcc main.c -o game_of_life -I/usr/local/include -L/usr/local/lib -lSDL2main -lSDL2
   ```

## Ejecución

Después de compilar, ejecuta el programa:

```bash
./game.exe
```


