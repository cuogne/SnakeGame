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
#include <tchar.h>
#include <strsafe.h>
#include <locale>
#include <codecvt>
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

enum class Direction { up, right, down, left };


//====================================== Draw Game Functions ======================================

vector<Point> Wall(int n);
void drawBox();
void drawButton(const string& text, bool highlighted, int xPos, int yPos);
void drawMenu(const vector<string>& options, int highlightedOption, const int startX, const int startY);
void NewGameandContinued(int& key);
void RestartandBackMenu(int& keyPressed);
void MENU(int& key);
void drawGate(Point WP, bool OnHeight, bool Left, bool Up);
void deleteGate_and_WP(Point& WP, bool OnHeight, bool Left, bool Up);
void drawWall(vector<Point> WALL);
void drawSnake();
void drawSnakeDie();
void drawHeadnTail();
void displayScoreInGame(int level);
void displayHighScore(Info inf[], int n);
void CreateWinPoint();

//====================================== Xu Ly File ====================================== 

void readImageFromFile(int** image, int height, int width, const string& filename, int backgroundcolor);
void displayImage(int** image, int height, int width, int x, int y);
void printTextUTF8(const std::string& filePath, int x, int y, int numColor);
void loadSaveFiles(vector<string>& saveFiles);

//====================================== Logic Game Functions ======================================

int randomRange(int min, int max);
void createApple(vector<Point> WALL);
bool isOnWinPoint();
bool isOnSecondWP();
void growing();
void MoveFirstChar(string& source, string& dest);
bool isHitWall(vector<Point> WALL);
bool isBiteItself();
bool isAteApple();
void move();
int Adjust_speed(Direction direction, int level);

//====================================== Menu Game Play Functions ======================================

void showStartMenu();
void ready();
void inputInfoPlayer();
void pauseGame(bool enough_score);
void GetReady();
void startGame(int level);
void showEndMenu();
void saveGame();
void readSaveGame();
void handleGameSaves();
void resetSnake(string temp, int score, string idsv, int level);

void readFileHighScore(Info inf[], int& n);
void excuteReadFile();

//====================================== QuickSort Functions ======================================
void swap(Info& a, Info& b);
int partition(Info arr[], int low, int high);
void quickSort(Info arr[], int low, int high);