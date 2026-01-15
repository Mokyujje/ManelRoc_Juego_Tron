#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h> 

void iniciarPartidaTron(bool contraIA);

int main() {
    // INICIAR 
    al_init();
    al_install_keyboard();
    al_init_font_addon();
    al_init_image_addon();
    al_init_primitives_addon();

    ALLEGRO_DISPLAY* ventana = al_create_display(640, 480);
    al_set_window_title(ventana, "Menu Manel i Roc - TRON");

    ALLEGRO_FONT* fuente = al_create_builtin_font();
    ALLEGRO_BITMAP* imagen = al_load_bitmap("jugar.png");

    ALLEGRO_EVENT_QUEUE* cola = al_create_event_queue();
    al_register_event_source(cola, al_get_keyboard_event_source());
    al_register_event_source(cola, al_get_display_event_source(ventana));

    bool terminar = false;
    int opcion = 0;

    while (!terminar) {
        ALLEGRO_EVENT evento;
        al_wait_for_event_timed(cola, &evento, 0.05);

        // --- LOGICA ---
        if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            terminar = true;
        }
        else if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {

            if (evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                if (opcion == 0) terminar = true;
                else opcion = 0;
            }

            if (opcion == 0) { // MENU PRINCIPAL
                if (evento.keyboard.keycode == ALLEGRO_KEY_1) opcion = 1;
                if (evento.keyboard.keycode == ALLEGRO_KEY_2) opcion = 2;
                if (evento.keyboard.keycode == ALLEGRO_KEY_3) opcion = 3;
                if (evento.keyboard.keycode == ALLEGRO_KEY_4) terminar = true;
            }
            else if (opcion == 1) { // MODO JUEGO
                if (evento.keyboard.keycode == ALLEGRO_KEY_1) {
                    iniciarPartidaTron(false);
                    al_set_target_backbuffer(ventana);
                    opcion = 0;
                }
                if (evento.keyboard.keycode == ALLEGRO_KEY_2) {
                    iniciarPartidaTron(true);
                    al_set_target_backbuffer(ventana);
                    opcion = 0;
                }
            }
        }

        // --- DIBUJAR ---
        al_clear_to_color(al_map_rgb(0, 0, 0));

        if (opcion == 0) { // DIBUJAR MENU
            al_draw_text(fuente, al_map_rgb(255, 255, 255), 320, 50, ALLEGRO_ALIGN_CENTER, "MENU PRINCIPAL");
            al_draw_text(fuente, al_map_rgb(0, 255, 0), 320, 150, ALLEGRO_ALIGN_CENTER, "1. Jugar");
            al_draw_text(fuente, al_map_rgb(0, 255, 0), 320, 200, ALLEGRO_ALIGN_CENTER, "2. Settings");
            al_draw_text(fuente, al_map_rgb(0, 255, 0), 320, 250, ALLEGRO_ALIGN_CENTER, "3. Creditos");
            al_draw_text(fuente, al_map_rgb(255, 0, 0), 320, 300, ALLEGRO_ALIGN_CENTER, "4. Salir");
        }
        else if (opcion == 1) { // DIBUJAR SELECCION MODO
            if (imagen) al_draw_bitmap(imagen, 250, 50, 0);
            al_draw_text(fuente, al_map_rgb(255, 255, 255), 320, 150, ALLEGRO_ALIGN_CENTER, "ELIGE MODO DE JUEGO:");
            al_draw_text(fuente, al_map_rgb(0, 255, 255), 320, 200, ALLEGRO_ALIGN_CENTER, "PULSA [1] -> 1 vs 1 (PVP)");
            al_draw_text(fuente, al_map_rgb(255, 0, 255), 320, 250, ALLEGRO_ALIGN_CENTER, "PULSA [2] -> 1 vs CPU (IA)");
            al_draw_text(fuente, al_map_rgb(255, 255, 0), 320, 420, ALLEGRO_ALIGN_CENTER, "ESC para volver");
        }
        else if (opcion == 2) { // SETTINGS
            al_draw_text(fuente, al_map_rgb(255, 255, 255), 320, 100, ALLEGRO_ALIGN_CENTER, "SETTINGS: Volumen 100%");
            al_draw_text(fuente, al_map_rgb(255, 255, 0), 320, 400, ALLEGRO_ALIGN_CENTER, "ESC para volver");
        }
        else if (opcion == 3) { // CREDITOS
            al_draw_text(fuente, al_map_rgb(255, 255, 255), 320, 100, ALLEGRO_ALIGN_CENTER, "CREDITOS: Hecho por Manel i Roc");
            al_draw_text(fuente, al_map_rgb(255, 255, 0), 320, 400, ALLEGRO_ALIGN_CENTER, "ESC para volver");
        }

        al_flip_display();

    } 

    // 3. LIMPIEZA
    al_destroy_display(ventana);
    al_destroy_event_queue(cola);
    if (imagen) al_destroy_bitmap(imagen);

    return 0;

}