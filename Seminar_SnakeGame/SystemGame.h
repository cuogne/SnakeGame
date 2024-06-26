#pragma once

#include <windows.h>

//====================================== System Game Functions ======================================
void SetColor(int x);
void gotoxy(int x, int y);
void ShowConsoleCursor(bool showFlag);
void ShowScrollbar(BOOL Show);
void FixConsoleWindow();
void resizeConsole(int width, int height);
void setConsoleBackgroundColor(int backgroundColor);