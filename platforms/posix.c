#ifndef _POSIX_COMPAT_H_
#define _POSIX_COMPAT_H_
#include "platforms.h"

#include <sys/ioctl.h>
#include <unistd.h>

#ifndef _VOID_SET_WIDE_STREAM
#define _VOID_SET_WIDE_STREAM
static int set_wide_stream(FILE *stream)
{
    return fwide(stream, 1);
}
#endif

#ifndef _VOID_INIT_ALL_DEF                              // If there are *any* OS-specific things
#define _VOID_INIT_ALL_DEF                              // this function should never be used
int initialise_all() {
    return 0;
}
#endif

#ifndef _VOID_CONSOLE_CLEAR_DEF
#define _VOID_CONSOLE_CLEAR_DEF
int console_clear() {
    wputs_no_nl(L"\033[1;1H\033[2J");
    return 0;
}
#endif

#ifndef _VOID_CONSOLE_COLOUR_DEF
#define _VOID_CONSOLE_COLOUR_DEF
int console_colour(unsigned char colour) {              // This is way too complicated
    char bg = ((colour >> 4) & 0x0F);
    char fg = (colour & 0x0F);
	char bold = fg > 7;
	fg &= 7;
	bg &= 7;
	bg = (bg >> 2) | (bg & 2) | (bg & 1) << 2;
	fg = (fg >> 2) | (fg & 2) | (fg & 1) << 2;
    wprintf(L"\033[%d;3%d;4%dm", bold, fg & 7, bg & 7);
    return 0;
}
#endif

#ifndef _VOID_CONSOLE_CURSOR_DEF
#define _VOID_CONSOLE_CURSOR_DEF
int console_cursor(size_t x, size_t y) {
    wprintf(L"\033[%d;%dH", x, y);
    return 0;
}
#endif

#ifndef _VOID_CONSOLE_HIDE_CURSOR_DEF
#define _VOID_CONSOLE_HIDE_CURSOR_DEF
int console_hide_cursor(bool state) {
    if (state) {
        wputs_no_nl(L"\033[?25l");
    } else {
        wputs_no_nl(L"\033[?25h");
    }
    return 0;
}
#endif

#endif