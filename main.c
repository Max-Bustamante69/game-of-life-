#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#undef main






//Constantes para el renderizado de la grilla
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define CELL_SIZE 10
#define GRID_ROWS (WINDOW_HEIGHT / CELL_SIZE)
#define GRID_COLS (WINDOW_WIDTH / CELL_SIZE)

// Estado de la grilla usando bits
unsigned char grid[GRID_ROWS][GRID_COLS] = {0};
unsigned char next_grid[GRID_ROWS][GRID_COLS] = {0};
unsigned char running = 1;
unsigned char simulation_running = 0;

// Función para contar vecinos vivos
int count_neighbors(int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;
            
            int nx = (x + i + GRID_ROWS) % GRID_ROWS;
            int ny = (y + j + GRID_COLS) % GRID_COLS;
            
            // Usar operación AND con 1 para verificar si el bit está activo
            if (grid[nx][ny] & 1) count++;
        }
    }
    return count;
}

// Función para actualizar la grilla según las reglas de Conway
void update_grid() {
    for (int x = 0; x < GRID_ROWS; x++) {
        for (int y = 0; y < GRID_COLS; y++) {
            int neighbors = count_neighbors(x, y);
            // Usar operación AND con 1 para obtener el estado actual
            unsigned char cell = grid[x][y] & 1;
            
            // Aplicar las reglas de Conway usando operaciones de bits
            if (cell && (neighbors < 2 || neighbors > 3)) {
                next_grid[x][y] = 0; // Célula muere
            } 
            else if (!cell && neighbors == 3) {
                next_grid[x][y] = 1; // Célula nace
            } 
            else {
                next_grid[x][y] = cell; // Mantiene su estado
            }
        }
    }
    
    // Copiar next_grid a grid
    for (int x = 0; x < GRID_ROWS; x++) {
        for (int y = 0; y < GRID_COLS; y++) {
            grid[x][y] = next_grid[x][y];
        }
    }
}

// Función para limpiar la grilla
void clear_grid() {
    for (int x = 0; x < GRID_ROWS; x++) {
        for (int y = 0; y < GRID_COLS; y++) {
            grid[x][y] = 0;
        }
    }
}



int main(int argc, char* argv[]) {

    // Mark parameters as used to fix warnings
    (void)argc;
    (void)argv;

    // Inicializar SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Crear ventana
    SDL_Window* window = SDL_CreateWindow(
        "Conway's Game of Life",
         SDL_WINDOWPOS_CENTERED,
         SDL_WINDOWPOS_CENTERED,
         WINDOW_WIDTH,
         WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Crear renderizador
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }    // Bucle principal del juego
    SDL_Event event;
    Uint32 last_update = 0;
    const Uint32 UPDATE_INTERVAL = 100; // Actualizar cada 100ms

    while (running) {
        // Manejar eventos
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
            else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_SPACE:
                        simulation_running = !simulation_running;
                        break;
                    case SDLK_c:
                        clear_grid();
                        break;
                    case SDLK_ESCAPE:
                        running = 0;
                        break;
                }
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int mouse_x, mouse_y;
                SDL_GetMouseState(&mouse_x, &mouse_y);
                int grid_col = mouse_x / CELL_SIZE;
                int grid_row = mouse_y / CELL_SIZE;
                
                if (grid_row >= 0 && grid_row < GRID_ROWS && grid_col >= 0 && grid_col < GRID_COLS) {
                    // Usar operación XOR con 1 para alternar el estado del bit
                    grid[grid_row][grid_col] ^= 1;
                }
            }
        }

        // Actualizar simulación
        Uint32 current_time = SDL_GetTicks();
        if (simulation_running && current_time - last_update > UPDATE_INTERVAL) {
            update_grid();
            last_update = current_time;
        }

        // Limpiar pantalla
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Dibujar grilla
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        for (int row = 0; row < GRID_ROWS; row++) {
            for (int col = 0; col < GRID_COLS; col++) {
                // Usar operación AND con 1 para verificar si el bit está activo
                if (grid[row][col] & 1) {
                    SDL_Rect cell = {
                        col * CELL_SIZE,
                        row * CELL_SIZE,
                        CELL_SIZE-1,
                        CELL_SIZE-1
                    };
                    SDL_RenderFillRect(renderer, &cell);
                }
            }
        }

        // Dibujar lineas de la grilla
        SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);
        for (int x = 0; x <= WINDOW_WIDTH; x += CELL_SIZE) {
            SDL_RenderDrawLine(renderer, x, 0, x, WINDOW_HEIGHT);
        }
        for (int y = 0; y <= WINDOW_HEIGHT; y += CELL_SIZE) {
            SDL_RenderDrawLine(renderer, 0, y, WINDOW_WIDTH, y);
        }

        // Actualizar pantalla
        SDL_RenderPresent(renderer);
    }

    // Limpiar
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}