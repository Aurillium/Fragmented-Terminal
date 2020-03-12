#include <wchar.h>
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define THIN_B_TB L"\x2502"
#define THIN_B_LR L"\x2500"
#define THIN_B_TL L"\x2518"
#define THIN_B_TR L"\x2514"
#define THIN_B_BL L"\x2510"
#define THIN_B_BR L"\x250C"
#define THIN_B_BLR L"\x252C"
#define THIN_B_TLR L"\x2534"
#define THIN_B_TBR L"\x251C"
#define THIN_B_TBL L"\x2524"

typedef struct addr_ipv4
{
    uint_least32_t ip;
    uint_least16_t port;
} addr_ipv4;

typedef struct vector2 {
    size_t x;
    size_t y;
} vector2;

size_t wputs(const wchar_t* str) {
    size_t ret = fwrite(str, sizeof(wchar_t), wcslen(str), stdout);
    fwrite(L"\n", sizeof(wchar_t), 1, stdout);
    return ret;
}
size_t wputs_no_nl(const wchar_t* str) {
    return fwrite(str, sizeof(wchar_t), wcslen(str), stdout);;
}
int wputchar(wchar_t c) {
    return !fwrite(&c, sizeof(wchar_t), 1, stdout);
}
//int wputchar(char c) {
//    return wputchar((wchar_t)c);
//}