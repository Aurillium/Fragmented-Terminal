#include "platforms.h"

// Draws an ASCII window with a set width, a title and text. Press 'X' to exit
int dialog(size_t width, const wchar_t* title, const wchar_t* text) {
    wputs_no_nl(THIN_B_BR);
    for (size_t i = 0; i < width - 4; i++) {
        wputs_no_nl(THIN_B_LR);
    }
    wputs_no_nl(THIN_B_BLR THIN_B_LR THIN_B_BL L"\n" THIN_B_TB);
    size_t written = fwrite(title, sizeof(wchar_t), min(width - 4, wcslen(title)), stdout);
    for (size_t i = 0; i < width - 4 - written; i++)
    {
        wputchar(L' ');
    }
    wputs_no_nl(THIN_B_TB L"X" THIN_B_TB L"\n" THIN_B_TBR);
    for (size_t i = 0; i < width - 4; i++) {
        wputs_no_nl(THIN_B_LR);
    }
    wputs_no_nl(THIN_B_TLR THIN_B_LR THIN_B_TBL L"\n" THIN_B_TB);
    for (size_t i = 0; i < width - 3; i++)
    {
        wputchar(L' ');
    }
    wchar_t* line = calloc(width - 4, sizeof(wchar_t));
    size_t offset = 0;
    size_t less_than = wcslen(text) / (width - 4) + (wcslen(text) % (width - 4) == 0 ? 0 : 1);
    for (size_t i = 0; i < less_than; i++)
    {
        wputs_no_nl(L" " THIN_B_TB L"\n" THIN_B_TB L" ");
        if (i == less_than - 1) {
            memset(line, 0, (width - 4) * sizeof(wchar_t));
            memcpy(line, (wchar_t*)text + offset, (wcslen(text) % (width - 4)) * sizeof(wchar_t));
        } else {
            memcpy(line, (wchar_t*)text + offset, (width - 4) * sizeof(wchar_t));
        }
        offset += width - 4;
        fwrite(line, sizeof(wchar_t), width - 4, stdout);
    }
    wputs_no_nl(L" " THIN_B_TB L"\n" THIN_B_TB L" ");
    for (size_t i = 0; i < width - 4; i++)
    {
        wputchar(L' ');
    }
    wputs_no_nl(L" " THIN_B_TB L"\n" THIN_B_TR THIN_B_LR);
    for (size_t i = 0; i < width - 4; i++)
    {
        wputs_no_nl(THIN_B_LR);
    }
    wputs_no_nl(THIN_B_LR THIN_B_TL);

    while (true) {
        int c = get_single_char();
        if (c == 'X' || c == 'x') {
            break;
        }
    }
    return 0;
}
int dialog_colour(uint_least8_t bg, uint_least8_t fg, size_t width, const wchar_t* title, const wchar_t* text) {
    console_colour(bg);
    wputs_no_nl(THIN_B_BR);
    for (size_t i = 0; i < width - 4; i++) {
        wputs_no_nl(THIN_B_LR);
    }
    wputs_no_nl(THIN_B_BLR THIN_B_LR THIN_B_BL L"\n" THIN_B_TB);
    console_colour(fg);
    size_t written = fwrite(title, sizeof(wchar_t), min(width - 4, wcslen(title)), stdout);
    console_colour(bg);
    for (size_t i = 0; i < width - 4 - written; i++)
    {
        wputchar(L' ');
    }
    wputs_no_nl(THIN_B_TB);
    console_colour((bg & 240) + 0x04);
    wputs_no_nl(L"X");
    console_colour(bg);
    wputs_no_nl(THIN_B_TB L"\n" THIN_B_TBR);
    for (size_t i = 0; i < width - 4; i++) {
        wputs_no_nl(THIN_B_LR);
    }
    wputs_no_nl(THIN_B_TLR THIN_B_LR THIN_B_TBL L"\n" THIN_B_TB);
    for (size_t i = 0; i < width - 3; i++)
    {
        wputchar(L' ');
    }
    wchar_t* line = calloc(width - 4, sizeof(wchar_t));
    size_t offset = 0;
    size_t less_than = wcslen(text) / (width - 4) + (wcslen(text) % (width - 4) == 0 ? 0 : 1);
    for (size_t i = 0; i < less_than; i++)
    {
        wputs_no_nl(L" " THIN_B_TB L"\n" THIN_B_TB L" ");
        if (i == less_than - 1) {
            memset(line, 0, (width - 4) * sizeof(wchar_t));
            memcpy(line, (wchar_t*)text + offset, (wcslen(text) % (width - 4)) * sizeof(wchar_t));
        } else {
            memcpy(line, (wchar_t*)text + offset, (width - 4) * sizeof(wchar_t));
        }
        offset += width - 4;
        console_colour(fg);
        fwrite(line, sizeof(wchar_t), width - 4, stdout);
        console_colour(bg);
    }
    wputs_no_nl(L" " THIN_B_TB L"\n" THIN_B_TB L" ");
    for (size_t i = 0; i < width - 4; i++)
    {
        wputchar(L' ');
    }
    wputs_no_nl(L" " THIN_B_TB L"\n" THIN_B_TR THIN_B_LR);
    for (size_t i = 0; i < width - 4; i++)
    {
        wputs_no_nl(THIN_B_LR);
    }
    wputs_no_nl(THIN_B_LR THIN_B_TL);

    while (true) {
        int c = get_single_char();
        if (c == 'X' || c == 'x') {
            break;
        }
    }
    return 0;
}
yn_dialog(size_t width, const wchar_t* title, const wchar_t* text) {
    wputs_no_nl(THIN_B_BR);
    for (size_t i = 0; i < width - 6; i++) {
        wputs_no_nl(THIN_B_LR);
    }
    wputs_no_nl(THIN_B_BLR THIN_B_LR THIN_B_BLR THIN_B_LR THIN_B_BL L"\n" THIN_B_TB);
    size_t written = fwrite(title, sizeof(wchar_t), min(width - 6, wcslen(title)), stdout);
    for (size_t i = 0; i < width - 6 - written; i++)
    {
        wputchar(L' ');
    }
    wputs_no_nl(THIN_B_TB L"Y" THIN_B_TB L"N" THIN_B_TB L"\n" THIN_B_TBR);
    for (size_t i = 0; i < width - 6; i++) {
        wputs_no_nl(THIN_B_LR);
    }
    wputs_no_nl(THIN_B_TLR THIN_B_LR THIN_B_TLR THIN_B_LR THIN_B_TBL L"\n" THIN_B_TB);
    for (size_t i = 0; i < width - 3; i++)
    {
        wputchar(L' ');
    }
    wchar_t* line = calloc(width - 4, sizeof(wchar_t));
    size_t offset = 0;
    size_t less_than = wcslen(text) / (width - 4) + (wcslen(text) % (width - 4) == 0 ? 0 : 1);
    for (size_t i = 0; i < less_than; i++)
    {
        wputs_no_nl(L" " THIN_B_TB L"\n" THIN_B_TB L" ");
        if (i == less_than - 1) {
            memset(line, 0, (width - 4) * sizeof(wchar_t));
            memcpy(line, (wchar_t*)text + offset, (wcslen(text) % (width - 4)) * sizeof(wchar_t));
        } else {
            memcpy(line, (wchar_t*)text + offset, (width - 4) * sizeof(wchar_t));
        }
        offset += width - 4;
        fwrite(line, sizeof(wchar_t), width - 4, stdout);
    }
    wputs_no_nl(L" " THIN_B_TB L"\n" THIN_B_TB L" ");
    for (size_t i = 0; i < width - 4; i++)
    {
        wputchar(L' ');
    }
    wputs_no_nl(L" " THIN_B_TB L"\n" THIN_B_TR THIN_B_LR);
    for (size_t i = 0; i < width - 4; i++)
    {
        wputs_no_nl(THIN_B_LR);
    }
    wputs_no_nl(THIN_B_LR THIN_B_TL);

    while (true) {
        int c = get_single_char();
        if (c == 'N' || c == 'n') {
            return 0;
        } else if (c == 'Y' || c == 'n') {
            return 1;
        }
    }
}