#define _HEADERGAME_H_

#include <conio.h>
#include <iostream>
#include <random>
#include <ctime>
#include <vector>
#include <windows.h>
#include <string>
#include <fstream>
#include <thread>
#include <sstream>
#include <mmsystem.h>
#include <chrono>
#include <iomanip>

using namespace std;

// Định nghĩa các mã màu ANSI
#define ANSI_COLOR_BLACK     "\x1b[30m" //0
#define ANSI_COLOR_RED     "\x1b[31m" //1
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m" //6
#define ANSI_COLOR_BRIGHTRED    "\x1b[91m" //7
#define ANSI_COLOR_BRIGHTGREEN    "\x1b[92m" //8
#define ANSI_COLOR_BRIGHTYELLOW    "\x1b[93m"//9
#define ANSI_COLOR_BRIGHTBLUE    "\x1b[94m"//10
#define ANSI_COLOR_BRIGHTMAGENTA    "\x1b[95m"//11
#define ANSI_COLOR_BRIGHTCYAN    "\x1b[96m"//12
#define ANSI_COLOR_BRIGHTWHITE    "\x1b[97m"//13
#define ANSI_COLOR_BRIGHTBLACK    "\x1b[90m"//14
#define ANSI_COLOR_WHITE    "\x1b[37m"//15
#define ANSI_COLOR_RESET   "\x1b[0m"

//============Struct Player============================
struct Info {
    string name;
    int diem;
    string day;
    string time;

    // Constructor
    Info() : diem(0) {}
};

//============ Game setup ==============================
struct Point {
    int x;
    int y;
};


//====================================== Draw Game Functions ======================================
void drawBox();
void drawSnake();
void drawHeadnTail();
void displayScoreInGame();
void displayHighScore(Info inf[], int n);
void INTRO(int& key);
void MoveFirstChar(string& source, string& dest);
void printTextUTF8(const std::string& filePath, int x, int y, int numColor);

void readImageFromFile(int** image, int height, int width, const string& filename, int backgroundcolor);
void displayImageColor(int** image, int height, int width, int x, int y);
void displayImageSnake(string fileName);

//====================================== Logic Game Functions ======================================
void createApple();
void growing();
bool isBiteItself();
bool isHitWall();
bool isAteApple();
void move();

//====================================== Menu Game Play Functions ======================================
void startGame();
void showStartMenu();
void inputInfoPlayer();
void pauseGame();
void quitGame();
void saveGame();
void showEndMenu();
void resetSnake();

void readFileHighScore(Info inf[], int& n);
void excuteReadFile();

//====================================== QuickSort Functions ======================================
void swap(Info& a, Info& b);
int partition(Info arr[], int low, int high);
void quickSort(Info arr[], int low, int high);