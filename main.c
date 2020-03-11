#include "platforms.h"

game_connection main_game_connection;

int run_game()
{
    sprite test_image;
    test_image = new_sprite(2, 3);
    if (read_image_from_file(&test_image, "test_image.bin")) {
        wputs(L"Error reading from file!");
    }
    main_game_connection.screen = new_sprite(10, 10);
    main_game_connection.console_size.x = 10;
    main_game_connection.console_size.y = 10;
    //draw_to_screen(main_game_connection, test_image);
    draw_window(20, L"X to exit game.", L"hello");

    console_colour(0x07);
    return 0;
}

int main(size_t argc, char** argv) {
    setlocale(LC_ALL, "");
    puts("No crash...");
    set_wide_stream(stdout); // ALL STRINGS MUST BE WIDE NOW
    wputs(L"Testing...");
    //#if OS_TYPE == 6 || OS_TYPE == 7
    //// If Windows set up the ANSI escapes by calling `system`
    //system("echo " MESSAGE);
    //#else
    wputs(MESSAGE);
    //#endif
    wputs(L"We're getting some things set up for you...");
    // Platform-specific init
    if (initialise_all()) {
        wputs(L"Sorry, an error occurred.");
        return 1;
    }
    // Game init
    vector2 con_size;
    console_size(&con_size);
    main_game_connection.console_size = con_size;
    main_game_connection.screen.sizeX = con_size.x;
    main_game_connection.screen.sizeY = con_size.y;
    console_colour(0x07);
    console_clear();
    console_cursor(0, 0);
    console_hide_cursor(true);
    // Actual game
    int game_ret = run_game();
    // Reset terminal
    console_colour(0x07);
    console_clear();
    console_hide_cursor(false);
    console_cursor(0, 0);
    // End program
    return game_ret;
}