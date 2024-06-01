#pragma once
#pragma comment(lib,"winmm.lib")
#include "HeaderGame.h"
#include "SystemGame.h"

const int WIDTH = 80;
const int HEIGHT = 28;
#define APPLE '0' ;

string MSSV = "23120223231202242312011323120250";
string CurrentSnake = "71202132";
string fullMSSV = "2312021723120223231202242312011323120250";
Direction direction = Direction::right; // bien theo doi di chuyen cua con ran (mac dinh la right)

Point apple;                            // bien dai dien cho vi tri cua qua tao
Point WinPoint;                         // bien dai dien cho vi tri qua man
Point SecondWP;
Point prevTail;                         // bien luu vitri cua ran trc khi di chuyen
int score = 0;                          // bien luu tru diem so
int speed = 300;                        // bien toc do cua man choi
string Name;                            // bien luu tru ten nguoi choi, ban dau khoi tao rong
int n;
int level = 1;
int manchoi = 0;
const int LimitPlayers = 1000;          // so luong nguoi choi toi da luu duoc
bool checkMusic = true;                 // check trang thai nhac nen
bool isPaused = false;                  // check trang thai pause game
bool isOnSnake = false;                 // bien check trang thai cua ran
bool checkWin = false;                  // bien check xem nguoi choi qua 4 man chua             
bool checkSave = false;                 // bien check xem man choi co duoc mo tu saveGame kh
bool PointOnHeight = 0;                 // bien check vi tri winPoint
bool Left = 0;                          // Neu winPoint bên trai
bool Up = 0;                            // Neu winPoint bên phai
char date[20];                          // bien luu ngay choi
char thoigian[20];                      // bien luu thoi gian choi

const unsigned char horizontalLineTop = 223; //viền trên
const unsigned char horizontalLineBottom = 220; // viền dưới 
const unsigned char verticalLine = 219; // viền trái, phải 
const unsigned char topLeftCorner = 219; // góc trái trên
const unsigned char topRightCorner = 219;
const unsigned char bottomLeftCorner = 219;
const unsigned char bottomRightCorner = 219;

vector<Point> snake;

vector<string> saveFiles;

vector<Point> Wall_WinPoint{
    Point{},    // O giua phia sau Point
    Point{},    // Ben trai phia sau
    Point{},    // Ben phai phia sau
    Point{},    // Ben trai
    Point{},    // Ben phai cua ben phai phia sau
    Point{},    // Ben phai
};

vector<Point> Wall_lv1{};

vector<Point> Wall_lv2{
    Point{17,6},
    Point{32,6},
    Point{16,6},
    Point{16,12},
    Point{16,18},
    Point{16,24},
    Point{17,24},
    Point{32,24},
    Point{48,6},
    Point{63,6},
    Point{64,6},
    Point{64,12},
    Point{48,24},
    Point{63,24},
    Point{64,18},
    Point{64,24},
};

vector<Point> Wall_lv3{
    Point{10,6},
    Point{60,6},
    Point{15,12},
    Point{70,12},
    Point{10,18},
    Point{60,18},
    Point{15,24},
    Point{70,24},
};

int direc = 1;
void MoveWall_lv3() {

    SetColor(116);

    gotoxy(Wall_lv3[0].x, Wall_lv3[0].y);
    cout << " ";
    gotoxy(Wall_lv3[4].x, Wall_lv3[4].y);
    cout << " ";
    gotoxy(Wall_lv3[1].x, Wall_lv3[1].y);
    cout << " ";
    gotoxy(Wall_lv3[5].x, Wall_lv3[5].y);
    cout << " ";

    // Kiểm tra nếu tường chạm biên trái hoặc phải màn hình
    if (Wall_lv3[0].x <= 2 || Wall_lv3[1].x >= WIDTH - 1) {
        direc = -direc; // Đảo hướng
    }

    Wall_lv3[0].x += direc;
    Wall_lv3[1].x += direc;
    Wall_lv3[4].x += direc;
    Wall_lv3[5].x += direc;

    // Vẽ lại tường sau khi cập nhật vị trí
    drawWall(Wall_lv3);

}

vector<Point> Wall_lv4{
    Point{17,24},
    Point{64,24},
    Point{16,6},
    Point{16,24},
    Point{17,6},
    Point{63,6},
    Point{64,6},
    Point{64,18},
    Point{33,18},
    Point{63,18},
    Point{32,12},
    Point{32,18},
    Point{33,12},
    Point{48,12},
};

vector<Point> Wall(int n) {
    switch (n) {
    case 1:
        return Wall_lv1;
        break;
    case 2:
        return Wall_lv2;
        break;
    case 3:
        return Wall_lv3;
        break;
    case 4:
        return Wall_lv4;
        break;
    }
    return Wall_lv1;
}

//====================================== Draw Game Functions ======================================
// ve board game
void drawBox() {
    SetColor(116);
    // ve chieu dai
    for (int i = 1; i < 81; i++) {
        gotoxy(i, 0);
        cout << horizontalLineBottom;
        gotoxy(i, 28);
        cout << horizontalLineTop;
    }

    for (int i = 1; i < 28; i++) {
        gotoxy(1, i);
        cout << verticalLine;
        gotoxy(80, i);
        cout << verticalLine;
    }

    // -----------------------------------------------------
    SetColor(113);
    gotoxy(82, 0);
    for (int i = 82; i < 118; i++) {

        if (i == 82 || i == 118) cout << topLeftCorner;
        else cout << horizontalLineTop;
    }
    cout << topRightCorner;


    gotoxy(82, 28);
    for (int i = 82; i < 118; i++) {
        if (i == 82 || i == 118) cout << topLeftCorner;
        else cout << horizontalLineBottom;
    }
    cout << bottomRightCorner;

    gotoxy(82, 12);
    for (int i = 82; i < 118; i++) {

        cout << horizontalLineBottom;
    }
    cout << bottomRightCorner;

    for (int i = 0; i < 28; i++) {
        gotoxy(82, i);
        cout << verticalLine;
        gotoxy(118, i);
        cout << verticalLine;
    }
}

// ham ve cac button
void drawButton(const string& text, bool highlighted, int xPos, int yPos) {
    const int buttonWidth = 26;
    const int buttonHeight = 3;

    int borderColor = 8; // Màu đỏ cho khung viền
    // Vẽ khung viền của nút button
    SetColor(borderColor); // Đặt màu sắc cho khung viền là màu mặc định

    yPos += 7; // Dời các ô xuống 7 ô

    SetColor(highlighted ? 10 : borderColor);
    gotoxy(xPos, yPos);
    cout << topLeftCorner;
    for (int i = 0; i < buttonWidth - 2; ++i) cout << horizontalLineTop;
    cout << topRightCorner;


    for (int i = 1; i <= buttonHeight - 2; ++i) {
        gotoxy(xPos, yPos + i);
        cout << verticalLine << setw(buttonWidth - 2) << ' ' << verticalLine; // Đảm bảo kích thước của dòng là buttonWidth - 1
    }

    gotoxy(xPos, yPos + buttonHeight - 1);
    cout << bottomLeftCorner;
    for (int i = 0; i < buttonWidth - 2; ++i) cout << horizontalLineBottom;
    cout << bottomRightCorner;

    // Đặt màu sắc cho phần văn bản bên trong nút button
    SetColor(highlighted ? 10 : 8);
    int textStartX = xPos + (buttonWidth - text.length()) / 2;
    int textStartY = yPos + (buttonHeight - 1) / 2;
    gotoxy(textStartX, textStartY);
    cout << text;
}

// ham ve ra menu (gom nhieu button)
void drawMenu(const vector<string>& options, int highlightedOption, const int startX, const int startY) {
    const int buttonSpacing = 1; // Khoảng cách giữa các nút button

    // Xóa các nút button đã vẽ trước đó
    for (int i = 0; i < options.size(); ++i) {
        gotoxy(startX, startY + i * (buttonSpacing + 3) + 8); // Di chuyển con trỏ in đến vị trí của nút button cũ
        cout << string(26, ' '); // Xóa nút button bằng cách in một chuỗi rỗng có độ dài bằng kích thước của nút button
    }

    // Vẽ các nút button mới
    for (int i = 0; i < options.size(); ++i) {
        drawButton(options[i], i == highlightedOption, startX, startY + i * (buttonSpacing + 3));
    }

}

// menu game gom newgame, continue va back
void NewGameandContinued(int& keyPressed) {
    vector<string> options = { "NEW GAME", "CONTINUE", "BACK" };
    size_t highlightedOption = 0;

    while (true) {

        drawMenu(options, highlightedOption, 47, 3);

        int key = _getch();

        if (key == 'w' || key == 72) {  // Up arrow
            PlaySound(TEXT("Sound//click1.wav"), NULL, SND_ASYNC);
            highlightedOption = (highlightedOption - 1 + options.size()) % options.size();
        }
        else if (key == 's' || key == 80) {  // Down arrow
            PlaySound(TEXT("Sound//click1.wav"), NULL, SND_ASYNC);
            highlightedOption = (highlightedOption + 1) % options.size();
        }
        else if (key == 13) {  // Enter key
            // Trả về giá trị của phím được nhấn
            PlaySound(TEXT("Sound//click1.wav"), NULL, SND_ASYNC);
            keyPressed = highlightedOption + 1; // Vì chỉ số của options bắt đầu từ 0, nên cần +1 để phù hợp với các trường hợp trong switch case
            break;
        }
    }

}

// menu gom resetgame va backmenu
void RestartandBackMenu(int& keyPressed) {
    vector<string> options = { "RESTART GAME", "BACK MENU" };
    size_t highlightedOption = 0;

    while (true) {

        drawMenu(options, highlightedOption, 47, 13);

        int key = _getch();

        if (key == 'w' || key == 72) {  // Up arrow
            PlaySound(TEXT("Sound//click1.wav"), NULL, SND_ASYNC);
            highlightedOption = (highlightedOption - 1 + options.size()) % options.size();
        }
        else if (key == 's' || key == 80) {  // Down arrow
            PlaySound(TEXT("Sound//click1.wav"), NULL, SND_ASYNC);
            highlightedOption = (highlightedOption + 1) % options.size();
        }
        else if (key == 13) {  // Enter key
            // Trả về giá trị của phím được nhấn
            PlaySound(TEXT("Sound//click1.wav"), NULL, SND_ASYNC);
            keyPressed = highlightedOption + 1; // Vì chỉ số của options bắt đầu từ 0, nên cần +1 để phù hợp với các trường hợp trong switch case
            break;
        }
    }
}

// button new (dang trong giai doan nghien cuu)
void MENU(int& keyPressed) {
    vector<string> options = { "START", "RANKING", "SETTING", "ABOUT US", "EXIT" };
    size_t highlightedOption = 0;

    while (true) {

        drawMenu(options, highlightedOption, 47, 3);

        int key = _getch();

        if (key == 'w' || key == 72) {  // Up arrow
            PlaySound(TEXT("Sound//click1.wav"), NULL, SND_ASYNC);
            highlightedOption = (highlightedOption - 1 + options.size()) % options.size();
        }
        else if (key == 's' || key == 80) {  // Down arrow
            PlaySound(TEXT("Sound//click1.wav"), NULL, SND_ASYNC);
            highlightedOption = (highlightedOption + 1) % options.size();
        }
        else if (key == 13) {  // Enter key
            // Trả về giá trị của phím được nhấn
            PlaySound(TEXT("Sound//click1.wav"), NULL, SND_ASYNC);
            keyPressed = highlightedOption + 1; // Vì chỉ số của options bắt đầu từ 0, nên cần +1 để phù hợp với các trường hợp trong switch case
            break;
        }
    }
}

// ve cong qua man moi
void drawGate(Point WP, bool OnHeight, bool Left, bool Up) {
    SetColor(113);
    if (OnHeight) {
        if (Left) {
            Wall_WinPoint[0].x = WP.x - 1;      //Phia sau
            Wall_WinPoint[0].y = WP.y;

            Wall_WinPoint[1].x = WP.x - 1;      //Phia sau ben trai
            Wall_WinPoint[1].y = WP.y - 1;

            Wall_WinPoint[2].x = WP.x - 1;      //Phia sau secondWP
            Wall_WinPoint[2].y = WP.y + 1;

            Wall_WinPoint[3].x = WP.x;          //Ben trai
            Wall_WinPoint[3].y = WP.y - 1;

            Wall_WinPoint[4].x = WP.x - 1;      //Ben Phai phia sau cua secondWP
            Wall_WinPoint[4].y = WP.y + 2;

            Wall_WinPoint[5].x = WP.x;          //Ben Phai
            Wall_WinPoint[5].y = WP.y + 2;
        }
        else {
            Wall_WinPoint[0].x = WP.x + 1;      //Phia sau
            Wall_WinPoint[0].y = WP.y;

            Wall_WinPoint[1].x = WP.x + 1;      //Phia sau ben trai
            Wall_WinPoint[1].y = WP.y - 1;

            Wall_WinPoint[2].x = WP.x + 1;      //Phia sau SecondWP
            Wall_WinPoint[2].y = WP.y + 1;

            Wall_WinPoint[3].x = WP.x + 1;      //Phia sau ben phai cua secondWP
            Wall_WinPoint[3].y = WP.y + 2;

            Wall_WinPoint[4].x = WP.x;          //Ben Phai
            Wall_WinPoint[4].y = WP.y + 2;

            Wall_WinPoint[5].x = WP.x;          //Ben Trai
            Wall_WinPoint[5].y = WP.y - 1;
        }
    }
    else {
        if (Up) {
            Wall_WinPoint[0].x = WP.x;          //Phia sau
            Wall_WinPoint[0].y = WP.y - 1;

            Wall_WinPoint[1].x = WP.x - 1;      //Phia sau ben phai
            Wall_WinPoint[1].y = WP.y - 1;

            Wall_WinPoint[2].x = WP.x + 1;      //Phia sau WP
            Wall_WinPoint[2].y = WP.y - 1;

            Wall_WinPoint[3].x = WP.x - 1;      //Ben phai
            Wall_WinPoint[3].y = WP.y;

            Wall_WinPoint[4].x = WP.x + 2;      //Ben sau ben trai WP
            Wall_WinPoint[4].y = WP.y - 1;

            Wall_WinPoint[5].x = WP.x + 2;      //Ben Trai
            Wall_WinPoint[5].y = WP.y;
        }
        else {
            Wall_WinPoint[0].x = WP.x;          //Phia sau
            Wall_WinPoint[0].y = WP.y + 1;

            Wall_WinPoint[1].x = WP.x - 1;      //Phia sau ben trai
            Wall_WinPoint[1].y = WP.y + 1;

            Wall_WinPoint[2].x = WP.x + 1;      //Phia sau WP
            Wall_WinPoint[2].y = WP.y + 1;

            Wall_WinPoint[3].x = WP.x - 1;      //Ben trai
            Wall_WinPoint[3].y = WP.y;

            Wall_WinPoint[4].x = WP.x + 2;      //Phia sau ben phai WP
            Wall_WinPoint[4].y = WP.y + 1;

            Wall_WinPoint[5].x = WP.x + 2;      //Ben phai
            Wall_WinPoint[5].y = WP.y;
        }
    }
    for (int i = 0; i < Wall_WinPoint.size(); i++) {
        gotoxy(Wall_WinPoint[i].x, Wall_WinPoint[i].y);
        cout << char(219);
    }
}

// xoa cong qua man
void deleteGate_and_WP(Point& WP, bool OnHeight, bool Left, bool Up) {
    if (OnHeight) {
        if (Left) {
            Wall_WinPoint[0].x = WP.x - 1;      //Phia sau
            Wall_WinPoint[0].y = WP.y;

            Wall_WinPoint[1].x = WP.x - 1;      //Phia sau ben trai
            Wall_WinPoint[1].y = WP.y - 1;

            Wall_WinPoint[2].x = WP.x - 1;      //Phia sau secondWP
            Wall_WinPoint[2].y = WP.y + 1;

            Wall_WinPoint[3].x = WP.x;          //Ben trai
            Wall_WinPoint[3].y = WP.y - 1;

            Wall_WinPoint[4].x = WP.x - 1;      //Ben Phai phia sau cua secondWP
            Wall_WinPoint[4].y = WP.y + 2;

            Wall_WinPoint[5].x = WP.x;          //Ben Phai
            Wall_WinPoint[5].y = WP.y + 2;
        }
        else {
            Wall_WinPoint[0].x = WP.x + 1;      //Phia sau
            Wall_WinPoint[0].y = WP.y;

            Wall_WinPoint[1].x = WP.x + 1;      //Phia sau ben trai
            Wall_WinPoint[1].y = WP.y - 1;

            Wall_WinPoint[2].x = WP.x + 1;      //Phia sau SecondWP
            Wall_WinPoint[2].y = WP.y + 1;

            Wall_WinPoint[3].x = WP.x + 1;      //Phia sau ben phai cua secondWP
            Wall_WinPoint[3].y = WP.y + 2;

            Wall_WinPoint[4].x = WP.x;          //Ben Phai
            Wall_WinPoint[4].y = WP.y + 2;

            Wall_WinPoint[5].x = WP.x;          //Ben Trai
            Wall_WinPoint[5].y = WP.y - 1;
        }
    }
    else {
        if (Up) {
            Wall_WinPoint[0].x = WP.x;          //Phia sau
            Wall_WinPoint[0].y = WP.y - 1;

            Wall_WinPoint[1].x = WP.x - 1;      //Phia sau ben phai
            Wall_WinPoint[1].y = WP.y - 1;

            Wall_WinPoint[2].x = WP.x + 1;      //Phia sau WP
            Wall_WinPoint[2].y = WP.y - 1;

            Wall_WinPoint[3].x = WP.x - 1;      //Ben phai
            Wall_WinPoint[3].y = WP.y;

            Wall_WinPoint[4].x = WP.x + 2;      //Ben sau ben trai WP
            Wall_WinPoint[4].y = WP.y - 1;

            Wall_WinPoint[5].x = WP.x + 2;      //Ben Trai
            Wall_WinPoint[5].y = WP.y;
        }
        else {
            Wall_WinPoint[0].x = WP.x;          //Phia sau
            Wall_WinPoint[0].y = WP.y + 1;

            Wall_WinPoint[1].x = WP.x - 1;      //Phia sau ben trai
            Wall_WinPoint[1].y = WP.y + 1;

            Wall_WinPoint[2].x = WP.x + 1;      //Phia sau WP
            Wall_WinPoint[2].y = WP.y + 1;

            Wall_WinPoint[3].x = WP.x - 1;      //Ben trai
            Wall_WinPoint[3].y = WP.y;

            Wall_WinPoint[4].x = WP.x + 2;      //Phia sau ben phai WP
            Wall_WinPoint[4].y = WP.y + 1;

            Wall_WinPoint[5].x = WP.x + 2;      //Ben phai
            Wall_WinPoint[5].y = WP.y;
        }
    }
    for (int i = 0; i < Wall_WinPoint.size(); i++) {
        gotoxy(Wall_WinPoint[i].x, Wall_WinPoint[i].y);
        cout << " ";
        Wall_WinPoint[i].x = 81;
        Wall_WinPoint[i].y = 31;
    }
    WP.x = 81;
    WP.y = 31;
}

// ve tuong
void drawWall(vector<Point> WALL) {
    SetColor(116);
    for (int i = 0; i < WALL.size(); i += 2)
        for (int m = WALL[i].x; m <= WALL[i + 1].x; m++)
            for (int n = WALL[i].y; n <= WALL[i + 1].y; n++)
            {
                gotoxy(m, n);
                if (WALL[i].x == WALL[i + 1].x)
                    cout << (char)219;
                else if ((WALL[i].y == WALL[i + 1].y) && (WALL[i].y <= 15))
                    cout << (char)223;
                else cout << (char)220;
            }
}

// ve con ran
void drawSnake() {
    for (size_t i = 0; i < snake.size(); i++) {
        if (i == 0) SetColor(114);
        else if (i == 8) SetColor(115);
        else if (i == 16) SetColor(113);
        else if (i == 24) SetColor(125);
        else if (i == 32) SetColor(117);
        Point p = snake[i]; // lay vi tri phan tu con ran
        gotoxy(p.x, p.y);
        cout << CurrentSnake[snake.size() - i - 1];
    }
}

// animation khi con ran chet
void drawSnakeDie() {
    SetColor(116);
    for (size_t i = 0; i < snake.size(); i++) {
        Point p = snake[i]; //Lay vi tri phan tu con ran
        gotoxy(p.x, p.y);
        cout << "x";
        Sleep(100);
    }
}

// ham xoa cai duoi phia sau con ran
void drawHeadnTail() {
    gotoxy(prevTail.x, prevTail.y); // di toi duoi ran
    SetColor(114);
    cout << ' ';                    // xoa cai tail cu
}

// In cac thong tin ben canh khung board game
void displayScoreInGame(int level) {
    SetColor(112);
    gotoxy(WIDTH + 7, 3);
    cout << "Level: ";
    SetColor(113);
    cout << level;

    SetColor(112);
    gotoxy(WIDTH + 7, 6);
    cout << "Your score: ";
    SetColor(113);
    cout << score;

    SetColor(112);
    gotoxy(WIDTH + 7, 9);
    cout << "Your name: ";
    SetColor(113);
    cout << Name;

    SetColor(116);
    gotoxy(84, 18);
    cout << "Press <P> to Pause Game";

    SetColor(116);
    gotoxy(84, 22);
    cout << "MOVE SNAKE : A W S D";

    gotoxy(25, 29);
    SetColor(112);
    cout << "FIT@HCMUS - 23CTT03 - GROUP 04";
}

// hien thi bang rankscore
void displayHighScore(Info inf[], int n) {
    system("cls");
    setConsoleBackgroundColor(7);
    printTextUTF8("FileText//leaderboard.txt", 14, 0, 113);
    if (n == 1) {
        gotoxy(37, 25); cout << " NO DATA" << endl;
        return;
    }
    const int TABLEWIDTH = 100;
    const int height_1name = 1;

    int table_height = (n - 1) * height_1name;
    const int borderColor = 4;
    SetColor(borderColor);

    // Similar to the original function, sort the players
    quickSort(inf, 0, n - 1);

    SetColor(120);
    gotoxy(4, 7);
    cout << setw(4) << ' ';
    cout << topLeftCorner;
    for (int i = 0; i < TABLEWIDTH; i++) {

        if (i == 3 || i == 28 || i == 54 || i == 79) cout << topLeftCorner;
        else cout << horizontalLineTop;
    }
    cout << topRightCorner;
    cout << endl << setw(8) << ' ';
    cout << verticalLine << "NO." << verticalLine << setw(10) << ' ' << "NAME" << setw(10) << ' ' << verticalLine << setw(10) << ' ' << "SCORE" << setw(10) << ' ' << verticalLine << setw(10) << ' ' << "DATE" << setw(10) << ' ' << verticalLine << setw(8) << ' ' << "TIME" << setw(8) << ' ' << verticalLine;
    for (int i = 0; i < min(10, n); ++i) {
        cout << endl << setw(8) << ' ';
        cout << topLeftCorner;
        for (int i = 0; i < TABLEWIDTH; i++) {

            if (i == 3 || i == 28 || i == 54 || i == 79) cout << topLeftCorner;
            else cout << horizontalLineTop;
        }
        cout << topRightCorner;
        cout << endl << setw(8) << ' ';
        cout << verticalLine << setw(3) << ' ' << verticalLine << setw(24) << ' ' << verticalLine << setw(25) << ' ' << verticalLine << setw(24) << ' ' << verticalLine << setw(20) << ' ' << verticalLine;
    }
    cout << setw(8) << endl << ' ';
    cout << bottomLeftCorner;
    for (int i = 0; i < TABLEWIDTH; i++) {

        if (i == 3 || i == 28 || i == 54 || i == 79) cout << bottomLeftCorner;
        else cout << horizontalLineBottom;
    }
    cout << bottomRightCorner;

    SetColor(113);
    int tpy = 10;
    for (int i = 0; i < min(10, n); i++) {
        int tpx = 10;
        gotoxy(tpx, tpy); cout << i + 1;
        gotoxy(tpx + 7, tpy); cout << inf[i].name;
        gotoxy(tpx + 39, tpy); cout << inf[i].diem;
        gotoxy(tpx + 61, tpy); cout << inf[i].day;
        gotoxy(tpx + 85, tpy); cout << inf[i].time;
        tpy += 2;
    }
}

// setup vi tri tao cong
void CreateWinPoint() {
    int x, y;
    do {
        PointOnHeight = rand() % 2;

        if (PointOnHeight) {
            // dat 2 ben canh ngan
            x = rand() % 2;

            if (x == 0) {
                x = 3;
                Left = 1;
            }
            else {
                x = WIDTH - 2;
                Left = 0;
            }
            y = randomRange(2, HEIGHT - 3);
        }
        // dat tren 2 canh dai
        else {
            x = randomRange(3, WIDTH - 3);

            y = rand() % 2;
            if (y == 0) {
                y = 2;
                Up = true;
            }
            else {
                y = HEIGHT - 2;
                Up = false;
            }
        }

        // kiem tra xem co trung voi con ran khong
        for (size_t i = 0; i < snake.size(); i++) {
            if (snake[i].x == x && snake[i].y == y) {
                isOnSnake = true;
                break;
            }
        }
    } while (isOnSnake);

    WinPoint = { x,y };
    if (PointOnHeight) {
        SecondWP.x = x;
        SecondWP.y = y + 1;
    }
    else {
        SecondWP.x = x + 1;
        SecondWP.y = y;
    }
    drawGate(WinPoint, PointOnHeight, Left, Up);        //THEM CAI NAY
}

//====================================== Xu Ly File ====================================== 

// doc file anh 
void readImageFromFile(int** image, int height, int width, const string& filename, int backgroundcolor) {
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        for (int i = 0; i < height && getline(file, line); ++i) {
            istringstream iss(line);
            for (int j = 0; j < width && iss; ++j) {
                string token;
                if (getline(iss, token, ' ')) {
                    try {
                        image[i][j] = stoi(token);
                    }
                    catch (const invalid_argument&) {
                        image[i][j] = backgroundcolor;
                    }
                }
                else {
                    image[i][j] = backgroundcolor;
                }
            }
        }
        file.close();
    }
    else {
        cerr << "Unable to open file: " << filename << endl;
    }
}

// hien thi anh
void displayImage(int** image, int height, int width, int x, int y) {
    // In ra hình ảnh pixel có màu
    int bar1 = 177; // mã ANSI
    int bar2 = 219;
    gotoxy(x, y);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            switch (image[i][j]) {
            case 0:
                cout << ANSI_COLOR_BLACK << (char)bar2 << (char)bar2;
                break;
            case 1:
                cout << ANSI_COLOR_RED << (char)bar2 << (char)bar2;
                break;
            case 2:
                cout << ANSI_COLOR_GREEN << (char)bar2 << (char)bar2;
                break;
            case 3:
                cout << ANSI_COLOR_YELLOW << (char)bar2 << (char)bar2;
                break;
            case 4:
                cout << ANSI_COLOR_BLUE << (char)bar2 << (char)bar2;
                break;
            case 5:
                cout << ANSI_COLOR_MAGENTA << (char)bar2 << (char)bar2;
                break;
            case 6:
                cout << ANSI_COLOR_CYAN << (char)bar2 << (char)bar2;
                break;
            case 7:
                cout << ANSI_COLOR_BRIGHTRED << (char)bar2 << (char)bar2;
                break;
            case 8:
                cout << ANSI_COLOR_BRIGHTGREEN << (char)bar2 << (char)bar2;
                break;
            case 9:
                cout << ANSI_COLOR_BRIGHTYELLOW << (char)bar2 << (char)bar2;
                break;
            case 10:
                cout << ANSI_COLOR_BRIGHTBLUE << (char)bar2 << (char)bar2;
                break;
            case 11:
                cout << ANSI_COLOR_BRIGHTMAGENTA << (char)bar2 << (char)bar2;
                break;
            case 12:
                cout << ANSI_COLOR_BRIGHTCYAN << (char)bar2 << (char)bar2;
                break;
            case 13:
                cout << ANSI_COLOR_BRIGHTWHITE << (char)bar2 << (char)bar2;
                break;
            case 14:
                cout << ANSI_COLOR_BRIGHTBLACK << (char)bar2 << (char)bar2;
                break;
            case 15:
                cout << ANSI_COLOR_WHITE << (char)bar2 << (char)bar2;
                break;

            default:
                cout << ANSI_COLOR_RESET << (char)bar2 << (char)bar2;
                break;
            }
        }
        gotoxy(x, ++y);

    }
}

// in cac ki tu dac biet chuan utf-8
void printTextUTF8(const string& filePath, int x, int y, int numColor) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cout << "Khong the mo file !!!" << endl;
        return;
    }

    UINT old_cp = GetConsoleOutputCP();
    SetConsoleOutputCP(CP_UTF8); // Set UTF-8 for console

    string line;
    while (getline(file, line)) {
        SetColor(numColor);
        gotoxy(x, y);
        cout << u8"" << line << "\n";
        y++;
    }

    SetConsoleOutputCP(old_cp); // Reset to old code page
    file.close();
}

// ham doc toan bo file trong thu muc SaveGame (ham nay se truy cap thu muc)
void loadSaveFiles(vector<string>& saveFiles) {
    saveFiles.clear(); // Clear the current list

    WIN32_FIND_DATA ffd;
    TCHAR szDir[MAX_PATH];
    HANDLE hFind = INVALID_HANDLE_VALUE;

    StringCchCopy(szDir, MAX_PATH, TEXT("SaveGame\\*"));

    hFind = FindFirstFile(szDir, &ffd);

    if (INVALID_HANDLE_VALUE == hFind) {
        // Handle error
    }

    do {
        if (!(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            wstring_convert<codecvt_utf8<wchar_t>, wchar_t> converter;
            string filename = converter.to_bytes(ffd.cFileName);
            saveFiles.push_back(filename);
        }
    } while (FindNextFile(hFind, &ffd) != 0);

    FindClose(hFind);
}

//====================================== Logic Game Functions ======================================

// random

int randomRange(int min, int max) {
    static bool firstTime = true;
    if (firstTime) { // we only need to initialize the random number generator once
        srand(time(0)); // use current time as seed for random generator
        firstTime = false;
    }
    return min + rand() % (max - min + 1);
}

// random vi tri cua qua tao trong board game
void createApple(vector<Point> WALL) {          //ĐÂY LÀ HÀM CREATE APPLE MỚI ĐỂ KHÔNG BỊ NGƯNG ĐỘNG THỜI GIAN
    vector<Point> validPositions;
    bool isOnSnake = false;
    bool isOnWall = false;

    // Tạo danh sách các vị trí hợp lệ
    for (int x = 2; x < WIDTH - 2; ++x) {
        for (int y = 2; y < HEIGHT - 2; ++y) {
            isOnSnake = false;
            isOnWall = false;

            // Kiểm tra xem vị trí có trùng với rắn không
            for (const auto& segment : snake) {
                if (segment.x == x && segment.y == y) {
                    isOnSnake = true;
                    break;
                }
            }

            // Kiểm tra xem vị trí có trùng với tường không
            if (!isOnSnake) {
                for (size_t i = 0; i < WALL.size(); i += 2) {
                    for (int m = WALL[i].x; m <= WALL[i + 1].x; ++m) {
                        for (int n = WALL[i].y; n <= WALL[i + 1].y; ++n) {
                            if (m == x && n == y) {
                                isOnWall = true;
                                break;
                            }
                        }
                        if (isOnWall) break;
                    }
                    if (isOnWall) break;
                }
            }

            // Nếu vị trí không trùng với rắn hoặc tường, thêm vào danh sách vị trí hợp lệ
            if (!isOnSnake && !isOnWall && y != 5 && y != 19) {
                validPositions.push_back({ x, y });
            }
        }
    }

    // Kiểm tra nếu không có vị trí hợp lệ nào
    if (validPositions.empty()) {
        cerr << "Error: No valid position to place the apple.\n";
        return;
    }

    // Chọn ngẫu nhiên một vị trí hợp lệ
    Point chosenPosition = validPositions[randomRange(0, validPositions.size() - 1)];
    apple = chosenPosition;

    gotoxy(apple.x, apple.y);
    SetColor(112);
    cout << APPLE;
    cout.flush();
}

// Kiem tra neu cham vao WinPoint
bool isOnWinPoint() {
    // vi tri duoi con ran trung voi vi tri cua WinPoint
    return snake[0].x == WinPoint.x && snake[0].y == WinPoint.y;
}

// kiem tra neu cham vao secondWP
bool isOnSecondWP() {
    // vi tri duoi con ran trung voi vi tri cua Second WinPoint
    return snake[0].x == SecondWP.x && snake[0].y == SecondWP.y;
}

// tang do dai cho con ran khi no an trung apple
void growing() {
    if (!MSSV.empty()) {
        snake.push_back(prevTail); // push_back vao duoi con ran
        snake.push_back(prevTail);

        MoveFirstChar(MSSV, CurrentSnake);
        MoveFirstChar(MSSV, CurrentSnake);
    }
    else {
        snake.push_back(prevTail); // push_back vao duoi con ran
        snake.push_back(prevTail);

        MoveFirstChar(fullMSSV, CurrentSnake);
        MoveFirstChar(fullMSSV, CurrentSnake);
    }
}

// push vao con ran mssv
void MoveFirstChar(string& source, string& dest) {
    if (!source.empty()) {
        char first_char = source[0]; // Lấy ký tự đầu của chuỗi nguồn
        dest = first_char + dest; // Thêm ký tự vào cuối chuỗi đích
        source.erase(0, 1); // Xóa ký tự đầu tiên khỏi chuỗi nguồn
    }
}

// Kiem tra xem con ran co dung vao tuong khong
bool isHitWall(vector<Point> WALL) {
    for (int i = 0; i < WALL.size(); i += 2)
        for (int m = WALL[i].x; m <= WALL[i + 1].x; m++)
            for (int n = WALL[i].y; n <= WALL[i + 1].y; n++)
                for (auto& point : snake)
                    if ((point.x == m) && (point.y == n)) return true;

    for (int i = 0; i < Wall_WinPoint.size(); i++) {
        if ((snake[0].x == Wall_WinPoint[i].x) && (snake[0].y == Wall_WinPoint[i].y)) return true;
    }
    // neu dau con ran = 0 hoac = chieu cao or chieu rong
    return snake[0].x == 1 || snake[0].y == 0 || snake[0].x == WIDTH || snake[0].y == HEIGHT;
}

// Kiem tra xem neu con ran an trung qua tao
bool isAteApple() {
    // vi tri dau con ran trung voi vi tri cua qua tao
    return snake[0].x == apple.x && snake[0].y == apple.y;
}

// check xem ran co can trung than minh khong
bool isBiteItself() {
    Point head = snake[0];
    for (size_t i = 1; i < snake.size(); i++)
        if (head.x == snake[i].x && head.y == snake[i].y)
            return true;
    return false;
}

// ham xu li di chuyen cua con ran
void move() {
    if (isPaused == false) {
        prevTail = snake.back(); // luu vi tri phan duoi cua ran truoc khi di chuyen
        for (size_t i = snake.size() - 1; i > 0; i--)
            snake[i] = snake[i - 1]; // dung vong lap de di chuyen con ran = cach gan cac ptu trc = ptu phia sau
        if (direction == Direction::up)
            snake[0].y -= 1;
        else if (direction == Direction::down)
            snake[0].y += 1;
        else if (direction == Direction::left)
            snake[0].x -= 1;
        else if (direction == Direction::right)
            snake[0].x += 1;
    }
}

// ham tinh toc do cua con ran
int Adjust_speed(Direction direction, int level) {
    if (direction == Direction::up || direction == Direction::down) {
        return (150 - level * 10);
    }
    return (100 - level * 10);
}

//====================================== Menu Game Play Functions ======================================

// ham bat dau vao tro choi
void showStartMenu() {
    system("cls");

    ShowConsoleCursor(FALSE);

    Info* inf = new Info[LimitPlayers];

    if (checkMusic == true) { // check trang thai de bat nhac nen
        PlaySound(TEXT("Sound//soundtrack.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    }

    setConsoleBackgroundColor(7);
    SetColor(113);
    int** snakePic2 = new int* [100];
    for (int i = 0; i < 100; ++i)
        snakePic2[i] = new int[100];

    int** snakePic3 = new int* [100];
    for (int i = 0; i < 100; ++i)
        snakePic3[i] = new int[100];

    readImageFromFile(snakePic2, 21, 21, "FileText//SnakePic2.txt", 113);
    readImageFromFile(snakePic3, 21, 21, "FileText//SnakePic3.txt", 113);

    system("cls");

    setConsoleBackgroundColor(7);

    for (;;) {
        printTextUTF8("FileText//logo.txt", 20, 1, 113);
        displayImage(snakePic2, 21, 21, 2, 9);
        displayImage(snakePic3, 21, 21, 76, 9);

        int key = 0;
        MENU(key);

        switch (key) {

        case 1:					//BUTTON START
        {
            system("cls");
            inputInfoPlayer();
            break;
        }

        case 2:				//BUTTON RANKING
        {
            // xem bang xep hang
            system("cls");
            readFileHighScore(inf, n);
            displayHighScore(inf, n);
            while (key = _getch()) {
                if (key == '\r') {
                    PlaySound(TEXT("Sound//click1.wav"), NULL, SND_ASYNC);
                    break;
                }
            }
            system("cls");
            break;
        }

        case 3: {
            // bat tat nhac nen
            system("cls");
            setConsoleBackgroundColor(7);
            printTextUTF8("FileText//setting.txt", 30, 2, 113);
            static int count = 1;
            gotoxy(47, 15); cout << "MUSIC";
            SetColor(113);
            gotoxy(55, 15); cout << "<        >";
            SetColor(113);

            switch (count)
            {
            case 1:
            {
                gotoxy(59, 15);
                SetColor(116);
                cout << "ON ";
                break;
            }

            case 2:
            {
                gotoxy(59, 15);
                SetColor(116);
                cout << "OFF";
                break;
            }
            }
            gotoxy(40, 24);
            SetColor(113);
            cout << "(*) Press <Enter> to back to MENU" << endl;
            while (key = _getch()) {
                if (key == '\r') {
                    PlaySound(TEXT("Sound//click1.wav"), NULL, SND_ASYNC);
                    system("cls");
                    break;
                }
                if (key == 75 || key == 'a') {
                    count--;
                    if (count == 0) count = 2;
                }
                else if (key == 77 || key == 'd') {
                    count++;
                    if (count == 3) count = 1;
                }

                switch (count) {

                case 1: // TURN ON THE MUSIC
                    gotoxy(59, 15);
                    SetColor(116);
                    cout << "ON ";
                    if (!checkMusic) {
                        checkMusic = true;
                    }
                    break;
                case 2: // TURN OFF THE MUSIC
                    gotoxy(59, 15);
                    SetColor(116);
                    cout << "OFF";
                    if (checkMusic) {
                        PlaySound(0, 0, 0);
                        checkMusic = false;
                    }
                    break;
                }
            }
            break;
        }

        case 4:					//BUTTON ABOUT US
        {
            system("cls");
            setConsoleBackgroundColor(7);
            printTextUTF8("FileText//About.txt", 29, 4, 113);

            gotoxy(34, 24);
            SetColor(113);
            cout << "(*) Press <Enter> to back to MENU" << endl;
            while (key = _getch()) {
                if (key == '\r') {
                    PlaySound(TEXT("Sound//click1.wav"), NULL, SND_ASYNC);
                    break;
                }
            }
            system("cls");
            break;
        }

        case 5:					//BUTTON EXIT
        {
            SetColor(116);
            gotoxy(38, 12);
            for (int i = 38; i < 78; i++) {

                if (i == 38 || i == 78) cout << topLeftCorner;
                else cout << horizontalLineTop;
            }
            cout << topRightCorner;

            gotoxy(38, 20);
            for (int i = 38; i < 78; i++) {
                if (i == 38 || i == 78) cout << topLeftCorner;
                else cout << horizontalLineBottom;
            }
            cout << bottomRightCorner;

            for (int i = 12; i < 20; i++) {
                gotoxy(38, i);
                cout << verticalLine;
                gotoxy(78, i);
                cout << verticalLine;
            }

            // Fill color inside the frame
            SetColor(113);
            for (int i = 39; i < 78; i++) { // adjusted loop range
                for (int j = 13; j < 20; j++) {
                    gotoxy(i, j);
                    cout << " ";
                }
            }

            gotoxy(45, 14); // subtracted 2 from x-coordinate
            SetColor(116);
            cout << "Do you really want to quit?";

            int selectedButton = 0; // 0 for "YES", 1 for "NO"

            // Handle button press
            char ch;
            bool quitConfirmed = false;
            while (!quitConfirmed) {
                // Update button colors based on the selected button
                gotoxy(48, 18); // subtracted 2 from x-coordinate
                SetColor(selectedButton == 0 ? 113 : 116);
                cout << "YES";

                gotoxy(65, 18); // subtracted 2 from x-coordinate
                SetColor(selectedButton == 1 ? 113 : 116);
                cout << "NO";

                ch = _getch();
                if (ch == 'a') {
                    PlaySound(TEXT("Sound//click1.wav"), NULL, SND_ASYNC);
                    selectedButton = 0;
                }
                else if (ch == 'd') {
                    PlaySound(TEXT("Sound//click1.wav"), NULL, SND_ASYNC);
                    selectedButton = 1;
                }
                else if (ch == '\r') { // Enter key
                    if (selectedButton == 0) {
                        quitConfirmed = true;
                        system("cls");
                        exit(1);
                    }
                    else if (selectedButton == 1) {
                        quitConfirmed = true;
                        break;
                    }
                }
            }

            // Clear the frame
            for (int i = 38; i <= 78; i++) { // adjusted loop range
                for (int j = 12; j <= 20; j++) {
                    gotoxy(i, j);
                    cout << " ";
                }
            }
            break;
        }
        } // end of switch
    } // end of for loop

    delete[] inf;
    for (int i = 0; i < 100; ++i) {
        delete[] snakePic2[i];
        delete[] snakePic3[i];
    }
    delete[] snakePic2;
    delete[] snakePic3;
}

// ham 3 giay chuan bi
void ready() {
    //system("cls");
    PlaySound(TEXT("Sound//3-2-1.wav"), NULL, SND_ASYNC);

    printTextUTF8("FileText//ba.txt", 37, 10, 113);
    Sleep(1000);
    printTextUTF8("FileText//hai.txt", 37, 10, 113);
    Sleep(1000);
    for (int i = 37; i < 47; i++) {
        for (int j = 10; j < 18; j++) {
            gotoxy(i, j);
            SetColor(122);
            cout << " ";
        }
    }
    printTextUTF8("FileText//mot.txt", 37, 10, 113);
    Sleep(1000);
    for (int i = 37; i < 47; i++) {
        for (int j = 10; j < 18; j++) {
            gotoxy(i, j);
            SetColor(122);
            cout << " ";
        }
    }
    //startGame(); // Start the game
}

// Man hinh nhap thong tin nguoi choi
void inputInfoPlayer() {
    system("cls");
    setConsoleBackgroundColor(7);
    int key = 0;
    for (;;) {
        NewGameandContinued(key);
        switch (key) {
        case 1:					//BUTTON START
        {
            system("cls");
            // 40 - 10
            setConsoleBackgroundColor(7);
            for (int i = 5; i < 25; i++) {
                for (int j = 20; j < 100; j++) {
                    gotoxy(j, i);
                    SetColor(233);
                    cout << " ";
                }
            }

            // Input player's name
            gotoxy(40, 10);
            ShowConsoleCursor(TRUE);
            SetColor(225);
            cout << "Insert your name (Maximum 20 characters): ";
            SetColor(225);
            gotoxy(48, 20);
            cout << "Press <Enter> to continue";
            for (int i = 50; i < 70; i++) {
                SetColor(240);
                gotoxy(i, 15);
                cout << " ";
            }

            char yu;
            Name = "";
            gotoxy(50, 15);
            while (true) {
                yu = _getch();

                if (yu == '\t') {
                    continue;
                }

                if (yu == '\r') { // '\r' is the Enter key
                    if (!Name.empty()) {
                        PlaySound(TEXT("Sound//click1.wav"), NULL, SND_ASYNC);
                        break;
                    }
                }

                else if ((yu == '\b' || yu == '\177')) { // '\b' is the Backspace key, '\177' is the Delete key
                    if (Name.length() > 0) {
                        SetColor(240);
                        Name.pop_back();
                        cout << "\b \b"; // Erase the last character in the console
                        gotoxy(30, 17);
                        SetColor(228);
                        cout << "                                                       "; // Clear the error message
                        gotoxy(Name.length() + 50, 15); // Move the cursor back to the input
                    }
                }

                else if (Name.length() < 20) {
                    SetColor(240);
                    Name.push_back(yu);
                    cout << yu;
                }

                else {
                    gotoxy(45, 17);
                    SetColor(79);
                    cout << "Name cannot exceed 20 characters";
                    gotoxy(70, 15);
                }
            }

            MSSV = "23120223231202242312011323120250";
            CurrentSnake = "71202132";

            resetSnake(CurrentSnake, 0, MSSV, 1); // Reset snake's state

            system("cls");
            setConsoleBackgroundColor(7);
            printTextUTF8("FileText//guide.txt", 5, 1, 113);

            char ch;
            do {
                ch = _getch();
            } while (ch != '\r');

            setConsoleBackgroundColor(7);
            startGame(1);
            //ready();
            break;
        }

        case 2:
        {
            handleGameSaves();
            break;
        }

        case 3:
        {
            system("cls");
            showStartMenu();
            break;
        }

        }
    }
}

// ham pause game => co ca quit save trong nay
void pauseGame(bool enough_score) {
    // 21 - 61
    // 10 - 18
    bool checkContinue = false;
    SetColor(116);
    gotoxy(21, 10);
    for (int i = 21; i < 61; i++) {

        if (i == 21 || i == 61) cout << topLeftCorner;
        else cout << horizontalLineTop;
    }
    cout << topRightCorner;

    gotoxy(21, 18);
    for (int i = 21; i < 61; i++) {
        if (i == 21 || i == 61) cout << topLeftCorner;
        else cout << horizontalLineBottom;
    }
    cout << bottomRightCorner;

    for (int i = 10; i < 18; i++) {
        gotoxy(21, i);
        cout << verticalLine;
        gotoxy(61, i);
        cout << verticalLine;
    }
    // Fill màu trong khung
    SetColor(122);
    for (int i = 22; i < 61; i++) {
        for (int j = 11; j < 18; j++) {
            gotoxy(i, j);
            cout << " ";
        }
    }
    gotoxy(29, 12);
    SetColor(117);
    cout << "Do you want to continue ?";

    int selectedButton = 0; // 0 for "YES", 1 for "NO"

    // Handle button press
    char ch;
    bool quitConfirmed = false;
    while (!quitConfirmed) {
        // Update button colors based on the selected button
        gotoxy(25, 16);
        SetColor(selectedButton == 0 ? 113 : 116);
        cout << "SAVE";

        gotoxy(39, 16);
        SetColor(selectedButton == 1 ? 113 : 116);
        cout << "QUIT";

        gotoxy(50, 16);
        SetColor(selectedButton == 2 ? 113 : 116);
        cout << "CONTINUE";

        ch = _getch();
        if (ch == 'a') {
            PlaySound(TEXT("Sound//click1.wav"), NULL, SND_ASYNC);
            selectedButton = (selectedButton - 1 + 3) % 3; // Move to the left button
        }
        else if (ch == 'd') {
            PlaySound(TEXT("Sound//click1.wav"), NULL, SND_ASYNC);
            selectedButton = (selectedButton + 1) % 3; // Move to the right button
        }
        else if (ch == '\r') { // Enter key
            PlaySound(TEXT("Sound//click1.wav"), NULL, SND_ASYNC);
            if (selectedButton == 0) {
                quitConfirmed = true;
                isPaused = false;
                readSaveGame();
            }
            else if (selectedButton == 1) {
                quitConfirmed = true;
                isPaused = false;
                showEndMenu();
            }
            else if (selectedButton == 2) {
                quitConfirmed = true;
                checkContinue = true;
                break;
            }
        }
        if (checkContinue == true) {
            if (!enough_score) {
                SetColor(112);
                gotoxy(apple.x, apple.y);
                cout << APPLE;
            }
        }
    }

    // Clear the frame
    for (int i = 21; i <= 61; i++) {
        for (int j = 10; j <= 18; j++) {
            gotoxy(i, j);
            cout << " ";
        }
    }
    isPaused = false;
}

// 3 giay chuan bi
void GetReady() {
    gotoxy(35, 13);
    SetColor(113);
    cout << "GET READY..." << endl;
    // doi 3 giay de BAT DAU
    for (size_t i = 3; i > 0; i--) {
        gotoxy(40, 15);
        cout << i;
        Sleep(1000);
    }
    gotoxy(40, 15);
    cout << " ";
    gotoxy(35, 13);
    cout << "                            "; //xoa chuoi "GET READY..."
}

// ham hien thi tro choi (ran, apple,...)
void startGame(int level) {
    system("cls"); // clear man hinh

    // khi mo saveGame thi checkSave == true

    manchoi = level;
    bool enough_score = false;

    // diem dat toi da cua 1 man choi
    if (score == 80 * level || score == 80 * level && checkSave == true) {
        enough_score = true;
    }

    if (level > 4) {
        checkWin = true; // dat duoc man choi cuoi cung
        showEndMenu();
    }

    // level lon hon 2 + kh mo tu saveGame thi se tao cong di qua
    if (level >= 2 && checkSave == false) {
        if (direction == Direction::left) direction = Direction::right;
        else if (direction == Direction::right) direction = Direction::left;
        else if (direction == Direction::up) direction = Direction::down;
        else direction = Direction::up;

        if (isOnWinPoint()) {
            for (int i = snake.size() - 1; i >= 1; i--)
            {
                snake[i].x = WinPoint.x;
                snake[i].y = WinPoint.y;
            }
        }
        else if (isOnSecondWP()) {
            for (int i = snake.size() - 1; i >= 1; i--)
            {
                snake[i].x = SecondWP.x;
                snake[i].y = SecondWP.y;
            }
        }
        drawGate(WinPoint, PointOnHeight, Left, Up);
        move();
    }

    setConsoleBackgroundColor(7);
    ShowConsoleCursor(false);

    drawBox(); // ve khung
    drawWall(Wall(level)); // ve tuong
    displayScoreInGame(level); // hien thi diem
    if (level == 1) ready();

    drawSnake(); // ve con ran

    checkSave = false;

    // neu enough_score chua du
    if (enough_score == false) {
        createApple(Wall(level)); // tao qua tao
    }

    // neu level > 1 thi bat dau ve chuong ngai vat o cac man ke
    if (level > 1) {
        GetReady();
        drawWall(Wall(level));
    }

    bool isCreatedWinPoint = 0;
    int score_win = 80 * level;
    bool TimeWallDelay = 1;
    bool deletedGate = 1;

    while (true) {
        if (level >= 2 && deletedGate == 1) {
            int tail = snake.size() - 1;
            if (snake[tail].x != WinPoint.x && snake[tail].y != WinPoint.y) {
                deleteGate_and_WP(WinPoint, PointOnHeight, Left, Up);
                deletedGate = 0;
            }
            drawBox();
        }
        if (level == 3 && !enough_score) {
            if (TimeWallDelay) TimeWallDelay = 0;
            else TimeWallDelay = 1;
            if (!TimeWallDelay) {
                MoveWall_lv3();
            }
        }

        speed = Adjust_speed(direction, level); // Adjust game speed based on level

        if (_kbhit()) {
            char ch = _getch();
            ch = tolower(ch); // chuyen chu hoa thanh chu thuong de tranh loi capslock
            if (ch == 'a' && direction != Direction::right)
                direction = Direction::left;
            else if (ch == 'w' && direction != Direction::down)
                direction = Direction::up;
            else if (ch == 's' && direction != Direction::up)
                direction = Direction::down;
            else if (ch == 'd' && direction != Direction::left)
                direction = Direction::right;
            else if (ch == 'p') {
                isPaused = true; // gan trang thai dung 
                pauseGame(enough_score); // goi ham pause
                drawWall(Wall(level)); // ve lai tuong de tranh bi che
            }
        }

        move();          // ham di chuyen con ran
        drawSnake();     // ve duoi va dau ran		
        drawHeadnTail();

        if (isAteApple()) {
            // add am thanh khi con ran an qua tao
            PlaySound(TEXT("Sound//pop.wav"), NULL, SND_ASYNC);
            score += 20;                    // tang 1 diem khi an trung tao
            if (score == score_win) {
                enough_score = true;
            }
            displayScoreInGame(level);       // hien thi diem vua tang
            growing();                      // tang do dai cho con ran
            // neu chua du diem
            if (enough_score == false) {
                createApple(Wall(level));   // tao lai qua tao
            }
        }

        if (isBiteItself() || isHitWall(Wall(level))) { // neu con ran can vao than minh hoac dung vao tuong
            PlaySound(TEXT("Sound//gameover.wav"), NULL, SND_ASYNC);
            drawSnakeDie();
            Sleep(1000);
            showEndMenu(); // hien thi man hinh endgame
            break;
        }

        if (isCreatedWinPoint == false)
            if (enough_score) {
                CreateWinPoint();         //Neu da du diem thi tao cong
                isCreatedWinPoint = true; //Dat la da tao WinPoint de khong tao lai
            }

        if (!isOnWinPoint() && !isOnSecondWP())
            Sleep(speed);
        else {
            PlaySound(TEXT("Sound//EnterTheGate.wav"), NULL, SND_ASYNC);
            if (snake.size() > 0) {
                for (int i = snake.size() - 1; i >= 0; i--) {
                    gotoxy(snake[i].x, snake[i].y);
                    cout << " ";
                    Sleep(speed);
                }
            }
            startGame(++level);
        }
    }
}

// Hien thi menu khi thua
void showEndMenu() {
    system("cls");
    excuteReadFile(); // luu diem (tat se kh luu vao file nua)

    setConsoleBackgroundColor(7);

    if (checkWin == true) { // qua 4 man moi checkWin == true dc
        PlaySound(TEXT("Sound//victory.wav"), NULL, SND_ASYNC);
        printTextUTF8("FileText//victory.txt", 33, 2, 113);
        checkWin = false; // dat lai trang thai
        level = 1;
    }

    else {
        PlaySound(TEXT("Sound//lose.wav"), NULL, SND_ASYNC);
        printTextUTF8("FileText//youlose.txt", 28, 1, 116);
    }

    SetColor(113);
    gotoxy(39, 11);
    for (int i = 39; i < 81; i++) {

        if (i == 39 || i == 81) cout << topLeftCorner;
        else cout << horizontalLineTop;
    }
    cout << topRightCorner;

    gotoxy(39, 28);
    for (int i = 39; i < 81; i++) {
        if (i == 39 || i == 81) cout << topLeftCorner;
        else cout << horizontalLineBottom;
    }
    cout << bottomRightCorner;

    for (int i = 12; i < 28; i++) {
        gotoxy(39, i);
        cout << verticalLine;
        gotoxy(81, i);
        cout << verticalLine;
    }

    gotoxy(48, 14);
    SetColor(112);
    cout << "Your Name : ";
    SetColor(113);
    cout << Name << endl;

    gotoxy(48, 17);
    SetColor(112);
    cout << "Your Score: ";
    SetColor(113);
    cout << score << endl;

    int key = 0;
    for (;;) {
        RestartandBackMenu(key);
        switch (key) {
        case 1:					//BUTTON START
        {
            MSSV = "23120223231202242312011323120250";
            CurrentSnake = "71202132";
            resetSnake(CurrentSnake, 0, MSSV, 1);
            setConsoleBackgroundColor(14);
            startGame(1);
            break;
        }
        case 2:
        {
            system("cls");
            showStartMenu();
            break;
        }
        }
    }
}

// ham reset vi tri con ran khi choi lai
void resetSnake(string temp, int diem, string idsv, int level) {
    snake.clear();
    CurrentSnake = temp;
    // Xác định chiều dài của con rắn dựa trên CurrentSnake
    int length = CurrentSnake.size();

    // Khởi tạo lại con rắn dựa trên chiều dài của CurrentSnake
    if (level == 4) {
        for (int i = 0; i < length; ++i) {
            snake.push_back(Point{ WIDTH / 2 + 3 - i, HEIGHT / 2 - 10 }); // neu la man 4 thi set phia tren
        }
    }
    else {
        for (int i = 0; i < length; ++i) {
            snake.push_back(Point{ WIDTH / 2 + 3 - i, HEIGHT / 2 }); // Khởi tạo con rắn theo chiều ngang từ (WIDTH / 2 + 3, HEIGHT / 2) giảm dần
        }
    }

    // Reset các biến khác
    MSSV = idsv;
    fullMSSV = "2312021723120223231202242312011323120250";
    score = diem;
    direction = Direction::right;
}

// ham save game
void saveGame() {
    // Draw the frame
    SetColor(116);
    gotoxy(21, 10);
    for (int i = 21; i < 61; i++) {

        if (i == 21 || i == 61) cout << topLeftCorner;
        else cout << horizontalLineTop;
    }
    cout << topRightCorner;

    gotoxy(21, 18);
    for (int i = 21; i < 61; i++) {
        if (i == 21 || i == 61) cout << topLeftCorner;
        else cout << horizontalLineBottom;
    }
    cout << bottomRightCorner;

    for (int i = 10; i < 18; i++) {
        gotoxy(21, i);
        cout << verticalLine;
        gotoxy(61, i);
        cout << verticalLine;
    }

    // Fill color inside the frame
    SetColor(234);
    for (int i = 22; i < 61; i++) {
        for (int j = 11; j < 18; j++) {
            gotoxy(i, j);
            cout << " ";
        }
    }

    gotoxy(29, 12);
    SetColor(117);
    cout << "Do you want to save game?";

    int selectedButton = 0; // 0 for "YES", 1 for "NO"

    // Handle button press
    char ch;
    bool quitConfirmed = false;
    while (!quitConfirmed) {
        // Update button colors based on the selected button
        gotoxy(30, 16);
        SetColor(selectedButton == 0 ? 113 : 116);
        cout << "YES";

        gotoxy(50, 16);
        SetColor(selectedButton == 1 ? 113 : 116);
        cout << "NO";

        ch = _getch();
        if (ch == 'a') {
            PlaySound(TEXT("Sound//click1.wav"), NULL, SND_ASYNC);
            selectedButton = 0;
        }
        else if (ch == 'd') {
            PlaySound(TEXT("Sound//click1.wav"), NULL, SND_ASYNC);
            selectedButton = 1;
        }
        else if (ch == '\r') { // Enter key
            PlaySound(TEXT("Sound//click1.wav"), NULL, SND_ASYNC);
            if (selectedButton == 0) {
                quitConfirmed = true;
                readSaveGame();
            }
            else if (selectedButton == 1) {
                quitConfirmed = true;
                break;
            }
        }
    }

    // Clear the frame
    for (int i = 21; i <= 61; i++) {
        for (int j = 10; j <= 18; j++) {
            gotoxy(i, j);
            cout << " ";
        }
    }

    SetColor(113);
    gotoxy(apple.x, apple.y);
    cout << APPLE;
}

// doc va luu file
void readSaveGame() {
    system("cls");
    setConsoleBackgroundColor(7);
    string file;

    for (int i = 5; i < 25; i++) {
        for (int j = 20; j < 100; j++) {
            gotoxy(j, i);
            SetColor(225);
            cout << " ";
        }
    }
    SetColor(228);
    gotoxy(35, 20);
    cout << "Luu y: Ten file nhap vao khong co khoang trang !!!" << endl;
    gotoxy(35, 21);
    cout << "Chi can nhap ten file, khong can nhap dinh dang file" << endl;

    // Input player's name
    gotoxy(50, 10);
    ShowConsoleCursor(TRUE);
    SetColor(225);
    cout << "Nhap ten file de luu: " << endl;
    SetColor(225);
    for (int i = 50; i < 70; i++) {
        SetColor(240);
        gotoxy(i, 12);
        cout << " ";
    }
    gotoxy(50, 12);

    string filePath;
    ifstream checkFile;
    bool checkSameFile = false;

    do {
        char yu;
        file = "";
        gotoxy(50, 12);
        while (true) {
            yu = _getch();
            if (yu == ' ') { // If the input character is a space
                gotoxy(file.length() + 50, 12);
                continue; // Skip the rest of the loop and start over
            }
            if (yu == '\r') { // '\r' is the Enter key
                if (!file.empty()) {
                    break;
                }
            }
            else if ((yu == '\b' || yu == '\177')) { // '\b' is the Backspace key, '\177' is the Delete key
                if (file.length() > 0) {
                    SetColor(240);
                    file.pop_back();
                    cout << "\b \b"; // Erase the last character in the console
                    gotoxy(30, 14);
                    SetColor(228);
                    cout << "                                                       "; // Clear the error message
                    gotoxy(file.length() + 50, 12); // Move the cursor back to the input
                }
            }
            else if (file.length() < 20) {
                SetColor(240);
                file.push_back(yu);
                cout << yu;
            }
            else {
                gotoxy(42, 14);
                SetColor(79);
                cout << "File name cannot exceed 20 characters";
                gotoxy(70, 12);
            }
        }

        filePath = "SaveGame//" + file + ".txt";
        checkFile.open(filePath.c_str());
        // Rest of the code...
        if (checkFile.good()) {
            SetColor(224);
            gotoxy(35, 14);
            // File already exists, ask for a different name
            cout << "File da ton tai. Ban co muon ghi de len file nay?";

            // Display options
            gotoxy(55, 15);
            cout << "> Yes";
            gotoxy(55, 16);
            cout << "  No";

            // Handle arrow keys for selection
            char overwrite = 'y';
            while (true) {
                char ch = _getch();
                if (ch == 72 || ch == 'w') { // Up arrow key
                    gotoxy(55, 15);
                    cout << "> Yes";
                    gotoxy(55, 16);
                    cout << "  No";
                    overwrite = 'y';
                }
                else if (ch == 80 || ch == 's') { // Down arrow key
                    gotoxy(55, 15);
                    cout << "  Yes";
                    gotoxy(55, 16);
                    cout << "> No";
                    overwrite = 'n';
                }
                else if (ch == '\r') { // Enter key
                    break;
                }
            }

            if (overwrite == 'n') {
                // Clear the line
                gotoxy(50, 12);
                for (int i = 50; i < 70; i++) {
                    SetColor(240);
                    gotoxy(i, 12);
                    cout << " ";
                }
                // Clear the overwrite question
                gotoxy(35, 14);
                for (int i = 35; i < 100; i++) {
                    SetColor(224); // Set to background color
                    cout << " ";
                }
                gotoxy(55, 15);
                SetColor(224);
                cout << "     ";
                gotoxy(55, 16);
                cout << "     ";

                // Move the cursor back to the input position
                SetColor(240);
                gotoxy(50, 12);
                checkFile.close();
                continue;
            }
            if (overwrite == 'y') {
                checkSameFile = true;
                break;
            }
        }
        checkFile.close();
    } while (checkFile.good());

    ofstream outputFile(filePath.c_str(), ios::out);
    if (checkSameFile == false) {
        string fileName = file + ".txt";
        saveFiles.push_back(fileName);
    }

    if (!outputFile) {
        return;
    }
    if (saveFiles.size() > 20) {
        SetColor(113);
        gotoxy(35, 18);
        cout << "Da dat gioi han luu file. Khong the luu them file.";
        cout << "Vui long xoa cac file cu da choi";
        return;
    }

    outputFile << Name << endl;
    outputFile << score << endl;
    outputFile << CurrentSnake << endl;
    outputFile << MSSV << endl;
    outputFile << manchoi << endl;

    outputFile.close();

    // in thong bao sau khi nhap thanh cong
    SetColor(226);
    gotoxy(35, 18);
    cout << "Da luu file thanh cong. An phim enter de tiep tuc." << endl;
    char hi;
    do {
        hi = _getch();
    } while (hi != '\r');  // '\r' là mã ASCII của phím Enter

    // Chờ người dùng nhấn enter
    //cin.ignore();  // ignore the newline character left in the buffer by the previous input

    showStartMenu();
}

// man hinh chon file choi lai
void handleGameSaves() {
    system("cls");

    loadSaveFiles(saveFiles);// doc toan bo file tu thu muc SaveGame

    // Tính toán vị trí cần in
    int printStartPos = 5;

    int currentFileIndex = 0;

    setConsoleBackgroundColor(7);

    SetColor(113);
    gotoxy(39, 2);
    for (int i = 39; i < 81; i++) {

        if (i == 39 || i == 81) cout << topLeftCorner;
        else cout << horizontalLineTop;
    }
    cout << topRightCorner;

    gotoxy(39, 26);
    for (int i = 39; i < 81; i++) {
        if (i == 39 || i == 81) cout << topLeftCorner;
        else cout << horizontalLineBottom;
    }
    cout << bottomRightCorner;

    for (int i = 3; i < 26; i++) {
        gotoxy(39, i);
        cout << verticalLine;
        gotoxy(81, i);
        cout << verticalLine;
    }

    SetColor(125);
    gotoxy(45, 3);
    cout << "Chon file ban muon tiep tuc choi";
    gotoxy(52, 28);
    cout << "Press <B> to back";

    while (true) {
        // Print all files
        if (saveFiles.size() == 0) {
            gotoxy(50, 5);
            cout << "Chua co file luu ve !!!";
            gotoxy(50, 6);
            cout << "An phim <B> de tro ve";
        }

        for (int i = 0; i < saveFiles.size(); i++) {
            gotoxy(60 - saveFiles[i].length() / 2, printStartPos + i);
            if (i == currentFileIndex) {
                SetColor(113); // Highlight color
            }
            else {
                SetColor(124); // Normal color
            }
            cout << saveFiles[i] << endl;
        }

        // Wait for user input
        char ch = _getch();

        switch (ch) {

        case 'w':
        case 72: // Up arrow key
            PlaySound(TEXT("Sound//click1.wav"), NULL, SND_ASYNC);
            if (currentFileIndex > 0) {
                currentFileIndex--;
            }
            break;

        case 's':
        case 80: // Down arrow key
            PlaySound(TEXT("Sound//click1.wav"), NULL, SND_ASYNC);
            if (currentFileIndex < saveFiles.size() - 1) {
                currentFileIndex++;
            }
            break;

        case 'b':
        case 'B':
            system("cls");
            setConsoleBackgroundColor(0);
            inputInfoPlayer();
            return;


        case '\r': // Enter key
            SetColor(116);
            gotoxy(40, 10);
            for (int i = 40; i < 80; i++) {

                if (i == 40 || i == 80) cout << topLeftCorner;
                else cout << horizontalLineTop;
            }
            cout << topRightCorner;

            gotoxy(40, 18);
            for (int i = 40; i < 80; i++) {
                if (i == 40 || i == 80) cout << topLeftCorner;
                else cout << horizontalLineBottom;
            }
            cout << bottomRightCorner;

            for (int i = 10; i < 18; i++) {
                gotoxy(40, i);
                cout << verticalLine;
                gotoxy(80, i);
                cout << verticalLine;
            }

            // Fill color inside the frame
            SetColor(116);
            for (int i = 41; i < 80; i++) {
                for (int j = 11; j < 18; j++) {
                    gotoxy(i, j);
                    cout << " ";
                }
            }

            gotoxy(48, 12);
            SetColor(117);
            cout << "Select the options below";

            int selectedButton = 0; // 0 for "PLAY", 1 for "DELETE", 2 for "BACK"

            // Handle button press
            char ch;
            bool quitConfirmed = false;
            while (!quitConfirmed) {
                // Update button colors based on the selected button
                gotoxy(45, 16);
                SetColor(selectedButton == 0 ? 113 : 116);
                cout << "PLAY";

                gotoxy(57, 16);
                SetColor(selectedButton == 1 ? 113 : 116);
                cout << "DELETE";

                gotoxy(71, 16);
                SetColor(selectedButton == 2 ? 113 : 116);
                cout << "BACK";

                ch = _getch();
                if (ch == 'a') {
                    PlaySound(TEXT("Sound//click1.wav"), NULL, SND_ASYNC);
                    selectedButton = (selectedButton - 1 + 3) % 3; // Move to the left button
                }
                else if (ch == 'd') {
                    PlaySound(TEXT("Sound//click1.wav"), NULL, SND_ASYNC);
                    selectedButton = (selectedButton + 1) % 3; // Move to the right button
                }
                else if (ch == '\r') { // Enter key
                    PlaySound(TEXT("Sound//click1.wav"), NULL, SND_ASYNC);
                    if (selectedButton == 0) {
                        string fileName = saveFiles[currentFileIndex];
                        string filePath = "SaveGame//" + fileName;

                        ifstream load(filePath.c_str(), ios::in);

                        if (load.is_open()) {
                            // Read the first line for name
                            getline(load, Name);

                            // Read the second line for score
                            string score_str;
                            getline(load, score_str);
                            try {
                                score = stoi(score_str);
                            }
                            catch (invalid_argument& e) {
                                cerr << "Invalid score: " << score_str << '\n';
                                return;
                            }

                            // Read the remaining lines for coordinates
                            getline(load, CurrentSnake);
                            getline(load, MSSV);

                            string capdo;
                            getline(load, capdo);
                            level = stoi(capdo);

                            load.close();
                        }

                        else {
                            cerr << "Unable to open file";
                            return;
                        }

                        system("cls");

                        SetColor(234);
                        checkSave = true; // bao lai voi startGame rang file nay mo tu saveGame
                        resetSnake(CurrentSnake, score, MSSV, level);
                        startGame(level);
                        break;
                    }
                    else if (selectedButton == 1) {
                        // Handle "DELETE" button press
                        string fileName = saveFiles[currentFileIndex];
                        string filePath = "SaveGame//" + fileName;
                        const char* cFilePath = filePath.c_str();
                        if (remove(cFilePath) != 0) {
                            //perror("Error deleting file");
                        }
                        else {
                            //cout << "File successfully deleted";
                            // Remove the deleted file from the list
                            saveFiles.erase(saveFiles.begin() + currentFileIndex);
                            if (currentFileIndex > 0) {
                                currentFileIndex--; // Move the selection up if possible
                            }
                        }
                        handleGameSaves();
                    }
                    else if (selectedButton == 2) {
                        // Handle "BACK" button press
                        quitConfirmed = true;
                        handleGameSaves();
                        break;
                    }
                }
            }

            // Clear the frame
            for (int i = 40; i <= 81; i++) {
                for (int j = 10; j <= 18; j++) {
                    gotoxy(i, j);
                    cout << " ";
                }
            }

        }
    }
}

// doc thong tin tu file co chua ten va diem cua nguoi choi
void readFileHighScore(Info inf[], int& n) {
    ifstream filein("FileText//highscore.txt", ios::in);
    if (!filein.is_open()) {
        cout << "Khong the mo file !!!" << endl;
        return;
    }
    string info;
    int i = 0;
    while (getline(filein, info)) {
        if (info.empty()) continue;

        size_t prev = 0, next;
        next = info.find('-');
        int count = 0;
        while (next != string::npos) {
            switch (count) {
            case 0:
                inf[i].name = info.substr(prev, next - prev);
                break;
            case 1:
                inf[i].diem = stoi(info.substr(prev, next - prev));
                break;
            case 2:
                inf[i].day = info.substr(prev, next - prev);
                break;
            }
            prev = next + 1;
            next = info.find('-', prev);
            count++;
        }
        inf[i].time = info.substr(prev, next - prev);
        i++;
    }
    n = i;
    filein.close();
}

// luu vao trong struct Info
void excuteReadFile() {
    Info* inf = new Info[LimitPlayers]; // su dung cap phat dong de tranh tran bo nho stack

    auto now = chrono::system_clock::now();
    time_t now_time = chrono::system_clock::to_time_t(now);

    struct tm buf;
    localtime_s(&buf, &now_time);

    char date[20];
    strftime(date, sizeof(date), "%d/%m/%Y", &buf);

    char time[20];
    strftime(time, sizeof(time), "%H:%M:%S", &buf);

    ofstream outputFile("FileText//highscore.txt", ios::app);
    if (!outputFile) {
        cout << "khong the mo file" << endl;
        return;
    }
    //realTime(date, thoigian);

    outputFile << Name << "-" << score << "-" << date << "-" << time << endl;
    outputFile.close();

    readFileHighScore(inf, n);
    delete[] inf; // giai phong bo nho
}

//====================================== QuickSort Functions ======================================
// dung quick sort de sap xep diem nguoi choi
void swap(Info& a, Info& b) {
    Info temp = a;
    a = b;
    b = temp;
}
int partition(Info arr[], int low, int high) {
    Info pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j].diem > pivot.diem) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}
void quickSort(Info arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}