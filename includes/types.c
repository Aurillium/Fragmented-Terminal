#include "platforms.h"

typedef struct sprite {
    size_t sizeX;
    size_t sizeY;
    uint_least8_t *colours;
    uint_least16_t *image;
    bool complete;
} sprite;

typedef struct game_connection {
    uni_socket s;
    vector2 console_size;
    vector2 screen_position;
    sprite screen;
    char state;
} game_connection;

typedef struct soul {
    uint_least16_t data[68];
} soul;

sprite new_sprite(size_t sizeX, size_t sizeY) {
    sprite s;
    s.sizeX = sizeX;
    s.sizeY = sizeY;
    s.image = calloc(sizeX * sizeY, sizeof(uint_least16_t));
    s.colours = calloc(sizeX * sizeY, sizeof(uint_least8_t));
    s.complete = true;
    return s;
}

int draw_sprite_over(sprite image, sprite screen, vector2 position) {
    size_t final_x = 0;
    size_t final_y = 0;
    for (size_t y = 0; y < image.sizeY; y++) {
        for (size_t x = 0; x < image.sizeX; x++) {
            final_x = position.x + x;
            final_y = position.y + y;
            if (final_x < screen.sizeX && 0 <= final_x && final_y < screen.sizeY && 0 <= final_y) {
                screen.image[final_y * screen.sizeX + final_x] = image.image[y * image.sizeX + final_x];
                screen.colours[final_y * screen.sizeX + final_x] = image.colours[y * image.sizeX + final_x];
            }
        }
    }
    return 0;
}

// Draws a sprite to the screen, as well as a `game_connection` buffer
int draw_to_screen(game_connection game, sprite image) {
    console_cursor(0, 0);
    //char* x_buffer = malloc(game.console_size.x);
    size_t x_lowest = (game.console_size.x > image.sizeX) ? image.sizeX : game.console_size.x;
    size_t y_lowest = (game.console_size.y > image.sizeY) ? image.sizeY : game.console_size.y;
    static unsigned char colour;
    for (size_t y = 0; y < y_lowest; y++) {
        for (size_t x = 0; x < x_lowest; x++)
        {
            game.screen.image[game.screen.sizeX * y + x] = image.image[image.sizeX * y + x];
            game.screen.colours[game.screen.sizeX * y + x] = image.colours[image.sizeX * y + x];
            if (colour != image.colours[image.sizeX * y + x]) {
                // ~~Error on line below~~
                // No, I'm stupid
                colour = image.colours[image.sizeX * y + x];
                console_colour(colour);
            }
            wputchar(image.image[image.sizeX * y + x]);
        }
        if (y != y_lowest - 1) {
            wputchar(L'\n');
        }
    }
    return 0;
}

int read_image_from_file(sprite* image, const char* filename) {
    FILE* image_file;
    image_file = fopen(filename, "rb");
    if (image_file == NULL) {
        return 1;
    }
    size_t final_size = 0;
    final_size = fread(image->image, sizeof(uint_least16_t), image->sizeX * image->sizeY, image_file);
    if (final_size != image->sizeX * image->sizeY) {
        fclose(image_file);
        image->complete = false;
        return 2;
    }
    final_size = 0;
    final_size = fread(image->colours, 1, image->sizeX * image->sizeY, image_file);
    if (final_size != image->sizeX * image->sizeY) {
        fclose(image_file);
        image->complete = false;
        return 3;
    }
    fclose(image_file);
    return 0;
}

int refresh_screen(game_connection game) {
    console_clear();
    return 0;
}