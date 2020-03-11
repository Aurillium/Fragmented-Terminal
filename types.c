#include "platforms.h"

typedef struct sprite {
    size_t sizeX;
    size_t sizeY;
    uint_least16_t *image;
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
    s.image = calloc(sizeX * sizeY, sizeof(uint16_t));
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
            }
        }
    }
    return 0;
}

int draw_to_screen(game_connection game, sprite image) {
    console_cursor(0, 0);
    //char* x_buffer = malloc(game.console_size.x);
    size_t x_lowest = (game.console_size.x > image.sizeX) ? image.sizeX : game.console_size.x;
    size_t y_lowest = (game.console_size.y > image.sizeY) ? image.sizeY : game.console_size.y;
    unsigned char colour = 0;
    for (size_t y = 0; y < y_lowest; y++) {
        for (size_t x = 0; x < x_lowest; x++)
        {
            if (colour != image.image[image.sizeX * y + x] >> 8) {
                // ~~Error on line below~~
                // No, I'm stupid
                game.screen.image[game.screen.sizeX * y + x] = image.image[image.sizeX * y + x];
                colour = image.image[image.sizeX * y + x] >> 8;
                console_colour(colour);
            }
            wputchar(image.image[image.sizeX * y + x] & 255);
        }
        if (y != y_lowest - 1) {
            wputchar(L'\n');
        }
    }
    return 0;
}

// IMPORTANT NOTE ON FILE FORMAT
// `fread` reads bytes in little-endian order, so if output looks strange, swap the colours and text
// IMPORTANT NOTE!!!
// Needs updating to work with the new wide chars
int read_image_from_file(sprite* image, const char* filename) {
    FILE* image_file;
    image_file = fopen(filename, "rb");
    if (image_file == NULL) {
        return 1;
    }
    size_t final_size = 0;
    final_size = fread(image->image, 2, image->sizeX * image->sizeY, image_file);
    if (final_size != image->sizeX * image->sizeY) {
        fclose(image_file);
        return 2;
    }
    fclose(image_file);
    return 0;
}

int draw_window(size_t width, const wchar_t* title, const wchar_t* text) {
    wputs_no_nl(THIN_B_BR);
    for (size_t i = 0; i < width - 4; i++) {
        wputs_no_nl(THIN_B_LR);
    }
    wputs_no_nl(THIN_B_BLR THIN_B_LR THIN_B_BL L"\n" THIN_B_TB);
    size_t written = fwrite(title, 2, min(width - 4, wcslen(title)), stdout);
    for (size_t i = 0; i < width - 4 - written; i++)
    {
        wputs_no_nl(L" ");
    }
    wputs_no_nl(THIN_B_TB L"X" THIN_B_TB L"\n" THIN_B_TBR);
    for (size_t i = 0; i < width - 4; i++) {
        wputs_no_nl(THIN_B_LR);
    }
    wputs_no_nl(THIN_B_TLR THIN_B_LR THIN_B_TBL L"\n" THIN_B_TB);

    while (true) {
        int c = get_single_char();
        if (c == 'X' || c == 'x') {
            break;
        }
    }
    return 0;
}

int refresh_screen(game_connection game) {
    console_clear();
    return 0;
}