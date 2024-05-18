#include "SystemGame.h"
#include <iostream>

//====================================== System Game Functions ======================================

// set mau sac
void SetColor(int x) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
}

// ham di chuyen con tro toi vi tri (x,y) ; o day kich thuoc console la 120x30 
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// hien thi con tro chuot
void ShowConsoleCursor(bool showFlag) {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag;
    SetConsoleCursorInfo(out, &cursorInfo);
}

// hien thi thanh cuon doc
void ShowScrollbar(BOOL Show)				//HIDE SCROLLBAR
{
    HWND hWnd = GetConsoleWindow();
    ShowScrollBar(hWnd, SB_BOTH, Show);
}

void FixConsoleWindow()
{
    HWND consoleWindow = GetConsoleWindow();
    LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
    style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
    SetWindowLong(consoleWindow, GWL_STYLE, style);
}

void resizeConsole(int width, int height)
{
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);
    MoveWindow(console, r.left, r.top, width, height, TRUE);
}

void setConsoleBackgroundColor(int backgroundColor) {
    // Lấy handle tới console output
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Lấy thông tin hiện tại của console
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);

    // Lưu màu chữ hiện tại
    WORD textColor = consoleInfo.wAttributes & 0x0F;

    // Thiết lập màu nền và giữ nguyên màu chữ
    WORD attributes = (backgroundColor << 4) | textColor;
    SetConsoleTextAttribute(hConsole, attributes);

    // Lấy kích thước của console
    COORD coord = { 0, 0 };
    DWORD count;
    DWORD consoleSize = consoleInfo.dwSize.X * consoleInfo.dwSize.Y;

    // Điền màu nền mới cho toàn bộ console
    FillConsoleOutputAttribute(hConsole, attributes, consoleSize, coord, &count);

    // Di chuyển con trỏ về đầu console
    SetConsoleCursorPosition(hConsole, coord);
}

