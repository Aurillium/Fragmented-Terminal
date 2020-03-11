#include <winsock2.h>       // Socket Header
#include <windows.h>        // Windows Header
#include <conio.h>			// Keys
#include <fcntl.h>
#include <io.h>

#pragma comment(lib, "Ws2_32.lib")

WSADATA wsa;
HANDLE hConsole;

typedef struct uni_socket {
    SOCKET s;
} uni_socket;

static int set_wide_stream(FILE *stream)
{
    return _setmode(_fileno(stream), _O_U16TEXT);
}

int initialise_all() {
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
	{
        // Failed
		return 1;
	}
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleMode(hConsole, ENABLE_VIRTUAL_TERMINAL_INPUT | ENABLE_PROCESSED_INPUT);
	return 0;
}

uni_socket new_socket() {
    uni_socket new_socket;
    if ((new_socket.s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
	{
		fprintf(stderr, "Could not create socket : %d" , WSAGetLastError());
	}
	// ...
	return new_socket;
}

int socket_connect(uni_socket *s, addr_ipv4 addr) {
	return 0;
}


void console_clear() {
	system("cls"); // Sorry, the other way is stupidly complicated.
    //printf("\033[1;1H\033[2J"); // Can't use on Windows
}

int console_colour(unsigned char colour) {
	return !SetConsoleTextAttribute(hConsole, colour);
}

int console_cursor(size_t x, size_t y) {				// Even this is over-complicated
	COORD c;
	c.X = x;
	c.Y = y;
	return !SetConsoleCursorPosition(hConsole, c);
}

int console_hide_cursor(bool state) {
	CONSOLE_CURSOR_INFO info;
	info.bVisible = !state;
	SetConsoleCursorInfo(hConsole, &info);
	return 0;
}

int console_size(vector2* size) {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	size->x = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    size->y = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	return 0;
}

int get_single_char() {
	return getch();
}