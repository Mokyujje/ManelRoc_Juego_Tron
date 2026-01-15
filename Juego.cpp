#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h> 
#include <allegro5/allegro_ttf.h>
#include <iostream>
#include "Moto.h" 

// Dimensiones de la ventana de juego
const int ANCHO = 800;
const int ALTO = 600;

// Grid logico para colisiones
const int COLS = ANCHO / TAMANO_MOTO;
const int FILAS = ALTO / TAMANO_MOTO;
bool grid[COLS][FILAS];

void iniciarPartidaTron(bool contraIA) {

    // --- SETUP DE LA VENTANA DE JUEGO ---
    ALLEGRO_DISPLAY* displayJuego = al_create_display(ANCHO, ALTO);
    al_set_window_title(displayJuego, "TRON - En partida");

    ALLEGRO_FONT* fuente = al_create_builtin_font();

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 15.0);

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(displayJuego));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    for (int i = 0; i < COLS; i++)
        for (int j = 0; j < FILAS; j++)
            grid[i][j] = false;

    // Crear las Motos
    Moto j1(50, 300, al_map_rgb(204, 18, 56), 1, 0);
    Moto j2(750, 300, al_map_rgb(0, 255, 255), -1, 0);

    bool running = true;
    bool redraw = true;
    int ganador = 0;

    al_start_timer(timer);

    // --- BUCLE DE JUEGO ---
    while (running) {
        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            running = false;
            ganador = 0;
        }
        else if (event.type == ALLEGRO_EVENT_TIMER) {

            // --- CEREBRO DE LA IA ---
            if (contraIA && j2.estaViva()) {
                int nextX = (j2.getX() + j2.getDirX() * VELOCIDAD) / TAMANO_MOTO;
                int nextY = (j2.getY() + j2.getDirY() * VELOCIDAD) / TAMANO_MOTO;
                bool peligro = (nextX < 0 || nextX >= COLS || nextY < 0 || nextY >= FILAS || grid[nextX][nextY]);

                if (peligro) {
                    if (j2.getDirX() != 0) {
                        int upY = (j2.getY() - VELOCIDAD) / TAMANO_MOTO;
                        if (upY >= 0 && !grid[(int)j2.getX() / TAMANO_MOTO][upY]) j2.cambiarDireccion(0, -1);
                        else j2.cambiarDireccion(0, 1);
                    }
                    else {
                        int leftX = (j2.getX() - VELOCIDAD) / TAMANO_MOTO;
                        if (leftX >= 0 && !grid[leftX][(int)j2.getY() / TAMANO_MOTO]) j2.cambiarDireccion(-1, 0);
                        else j2.cambiarDireccion(1, 0);
                    }
                }
            }

            // --- MOVER ---
            if (j1.estaViva()) j1.mover();
            if (j2.estaViva()) j2.mover();

            // --- COLISIONES J1 ---
            int c1 = j1.getX() / TAMANO_MOTO;
            int f1 = j1.getY() / TAMANO_MOTO;

            if (c1 < 0 || c1 >= COLS || f1 < 0 || f1 >= FILAS || grid[c1][f1]) {
                j1.matar();
                ganador = 2;
                running = false;
            }
            else grid[c1][f1] = true;

            // --- COLISIONES J2 ---
            int c2 = j2.getX() / TAMANO_MOTO;
            int f2 = j2.getY() / TAMANO_MOTO;

            if (c2 < 0 || c2 >= COLS || f2 < 0 || f2 >= FILAS || grid[c2][f2]) {
                j2.matar();
                ganador = 1;
                running = false;
            }
            else grid[c2][f2] = true;

            redraw = true;
        }
        else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (event.keyboard.keycode) {
                // J1
            case ALLEGRO_KEY_W: j1.cambiarDireccion(0, -1); break;
            case ALLEGRO_KEY_S: j1.cambiarDireccion(0, 1); break;
            case ALLEGRO_KEY_A: j1.cambiarDireccion(-1, 0); break;
            case ALLEGRO_KEY_D: j1.cambiarDireccion(1, 0); break;

                // J2
            case ALLEGRO_KEY_UP:    if (!contraIA) j2.cambiarDireccion(0, -1); break;
            case ALLEGRO_KEY_DOWN:  if (!contraIA) j2.cambiarDireccion(0, 1); break;
            case ALLEGRO_KEY_LEFT:  if (!contraIA) j2.cambiarDireccion(-1, 0); break;
            case ALLEGRO_KEY_RIGHT: if (!contraIA) j2.cambiarDireccion(1, 0); break;

            case ALLEGRO_KEY_ESCAPE: running = false; break;
            }
        }

        // --- DIBUJAR JUEGO ---
        if (redraw && al_is_event_queue_empty(queue) && running) {
            redraw = false;
            al_clear_to_color(al_map_rgb(40, 40, 41));

            for (int i = 0; i < COLS; i++) {
                for (int j = 0; j < FILAS; j++) {
                    if (grid[i][j])
                        al_draw_filled_rectangle(i * TAMANO_MOTO, j * TAMANO_MOTO, (i + 1) * TAMANO_MOTO, (j + 1) * TAMANO_MOTO, al_map_rgb(200, 200, 200));
                }
            }
            j1.dibujar();
            j2.dibujar();
            al_flip_display();
        }
    }

    if (ganador != 0) {
        al_clear_to_color(al_map_rgb(0, 0, 0));

        if (ganador == 1) {
            // Gana J1
            al_draw_text(fuente, al_map_rgb(204, 18, 56), ANCHO / 2, ALTO / 2 - 10, ALLEGRO_ALIGN_CENTER, "!!! GANADOR: JUGADOR 1 !!!");
        }
        else if (ganador == 2) {
            // Gana J2
            al_draw_text(fuente, al_map_rgb(0, 255, 255), ANCHO / 2, ALTO / 2 - 10, ALLEGRO_ALIGN_CENTER, "!!! GANADOR: JUGADOR 2 !!!");
        }

        al_draw_text(fuente, al_map_rgb(255, 255, 255), ANCHO / 2, ALTO / 2 + 20, ALLEGRO_ALIGN_CENTER, "Volviendo al menu...");

        al_flip_display();
        al_rest(3.0);
    }

    // LIMPIEZA
    al_destroy_font(fuente);
    al_destroy_display(displayJuego);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
}