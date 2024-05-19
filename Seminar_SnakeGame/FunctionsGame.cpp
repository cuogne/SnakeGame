#pragma once
#pragma comment(lib,"winmm.lib")
#include "HeaderGame.h"
#include "SystemGame.h"

const int WIDTH = 80;
const int HEIGHT = 28;
#define APPLE '0' ;

string MSSV = "23120223231202242312022523120250";
string CurrentSnake = "71202132";
string fullMSSV = "2312021723120223231202242312022523120250";
enum class Direction { up, right, down, left };
Direction direction = Direction::right; // bien theo doi di chuyen cua con ran (mac dinh la right)

Point apple;                            // bien dai dien cho vi tri cua qua tao
Point prevTail;                         // bien luu vitri cua ran trc khi di chuyen
int score = 0;                          // bien luu tru diem so
int speed = 300;                        // bien toc do cua man choi
string Name;                  // bien luu tru ten nguoi choi, ban dau khoi tao rong
int t, n;
const int LimitPlayers = 1000;          // so luong nguoi choi toi da luu duoc
bool checkMusic = true;                 // check trang thai nhac nen
bool isPaused = false;                  // check trang thai pause game
char date[20];
char thoigian[20];

const unsigned char horizontalLineTop = 223; //viền trên
const unsigned char horizontalLineBottom = 220; // viền dưới 
const unsigned char verticalLine = 219; // viền trái, phải 
const unsigned char topLeftCorner = 219; // góc trái trên
const unsigned char topRightCorner = 219;
const unsigned char bottomLeftCorner = 219;
const unsigned char bottomRightCorner = 219;

vector<Point> snake = {
    Point{WIDTH / 2 + 3, HEIGHT / 2},   // (48,15)
    Point{WIDTH / 2 + 2, HEIGHT / 2},   // (47,15)
    Point{WIDTH / 2 + 1, HEIGHT / 2},   // (46,15)
    Point{WIDTH / 2 + 0, HEIGHT / 2},   // (45,15)
    Point{WIDTH / 2 - 1, HEIGHT / 2},   // (44,15)
    Point{WIDTH / 2 - 2, HEIGHT / 2},   // (43,15)
    Point{WIDTH / 2 - 3, HEIGHT / 2},   // (42,15)
    Point{WIDTH / 2 - 4, HEIGHT / 2},   // (41,15)  
};

//====================================== Draw Game Functions ======================================
// ve board game
void drawBox() {
    SetColor(228);

    gotoxy(1, 0);
    for (int i = 1; i < 80; i++) {

        if (i == 1 || i == 80) cout << topLeftCorner;
        else cout << horizontalLineTop;
    }
    cout << topRightCorner;

    gotoxy(1, 28);
    for (int i = 1; i < 80; i++) {
        if (i == 1 || i == 80) cout << topLeftCorner;
        else cout << horizontalLineBottom;
    }
    cout << bottomRightCorner;

    for (int i = 1; i < 28; i++) {
        gotoxy(1, i);
        cout << verticalLine;
        gotoxy(80, i);
        cout << verticalLine;
    }

    gotoxy(16, 29);
    SetColor(233);
    cout << "Press <P> to pause game - Press <Q> to end game";

    // -----------------------------------------------------
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

void drawButton(const std::string& text, bool highlighted, int xPos, int yPos) {
    const int buttonWidth = 26;
    const int buttonHeight = 3;

    int borderColor = 8; // Màu đỏ cho khung viền
    // Vẽ khung viền của nút button
    SetColor(borderColor); // Đặt màu sắc cho khung viền là màu mặc định

    yPos += 8; // Dời các ô xuống 4 ô

    SetColor(highlighted ? 10 : borderColor);
    gotoxy(xPos, yPos);
    cout << topLeftCorner;
    for (int i = 0; i < buttonWidth - 2; ++i) cout << horizontalLineTop;
    cout << topRightCorner;


    for (int i = 1; i <= buttonHeight - 2; ++i) {
        gotoxy(xPos, yPos + i);
        std::cout << verticalLine << std::setw(buttonWidth - 2) << ' ' << verticalLine; // Đảm bảo kích thước của dòng là buttonWidth - 1
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

void drawMenu(const std::vector<std::string>& options, int highlightedOption, const int startX, const int startY) {
    const int buttonSpacing = 1; // Khoảng cách giữa các nút button

    // Xóa các nút button đã vẽ trước đó
    for (int i = 0; i < options.size(); ++i) {
        gotoxy(startX, startY + i * (buttonSpacing + 3) + 8); // Di chuyển con trỏ in đến vị trí của nút button cũ
        cout << std::string(26, ' '); // Xóa nút button bằng cách in một chuỗi rỗng có độ dài bằng kích thước của nút button
    }

    // Vẽ các nút button mới
    for (int i = 0; i < options.size(); ++i) {
        drawButton(options[i], i == highlightedOption, startX, startY + i * (buttonSpacing + 3));
    }

}

void NewGameandContinued(int& keyPressed) {
    std::vector<std::string> options = { "NEW GAME", "CONTINUE"};
    size_t highlightedOption = 0;

    while (true) {

        drawMenu(options, highlightedOption,47,3);

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

void RestartandBackMenu(int& keyPressed) {
    std::vector<std::string> options = { "RESTART GAME", "BACK MENU" };
    size_t highlightedOption = 0;

    while (true) {

        drawMenu(options, highlightedOption,47,12);

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

// ve mau nen cho background
void drawBackground(int x, int maxX, int y, int maxY, int numColor) {
    for (int i = x; i < maxX; i++) {
        for (int j = y; j < maxY; j++) {
            SetColor(numColor);
            cout << " ";
        }
        cout << endl;
    }
}

// ve con ran
void drawSnake() {
    SetColor(226);
    for (size_t i = 0; i < snake.size(); i++) {
        Point p = snake[i]; // lay vi tri phan tu con ran
        gotoxy(p.x, p.y);
        cout << CurrentSnake[snake.size() - i - 1];
    }
}

// ham xoa cai duoi phia sau con ran
void drawHeadnTail() {
    gotoxy(prevTail.x, prevTail.y); // di toi duoi ran
    SetColor(226);
    cout << ' ';                    // xoa cai tail cu
}

// In cac thong tin ben canh khung board game
void displayScoreInGame() {
    SetColor(226);
    gotoxy(WIDTH + 7, 3);
    cout << "Speed: ";
    SetColor(237);
    cout << t;

    SetColor(226);
    gotoxy(WIDTH + 7, 6);
    cout << "Your score: ";
    SetColor(237);
    cout << score;

    SetColor(226);
    gotoxy(WIDTH + 7, 9);
    cout << "Your name: ";
    SetColor(237);
    cout << Name;
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

// push vao con ran mssv
void MoveFirstChar(string& source, string& dest) {
    if (!source.empty()) {
        char first_char = source[0]; // Lấy ký tự đầu của chuỗi nguồn
        dest = first_char + dest; // Thêm ký tự vào cuối chuỗi đích
        source.erase(0, 1); // Xóa ký tự đầu tiên khỏi chuỗi nguồn
    }
}

// button new (dang trong giai doan nghien cuu)
void INTRO(int& keyPressed) {
    std::vector<std::string> options = { "START", "RANKING", "SETTING", "ABOUT US", "EXIT" };
    size_t highlightedOption = 0;

    while (true) {

        drawMenu(options, highlightedOption,47,3);

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

// doc file anh
void displayFile(const string& fileName, int x, int y, int numColor) {
    ifstream file(fileName); // mo file
    string line; // bien nay se duyet qua tung dong trong file .txt

    if (file.is_open()) {
        while (getline(file, line)) {
            gotoxy(x, y);
            SetColor(numColor);
            //system("color 80");

            cout << line << endl;
            y++;
        }
        file.close(); // dong file
    }
    else {
        return;
    }
}

void readImageFromFile(int** image, int height, int width, const string& filename, int backgroundcolor) {
    ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        for (int i = 0; i < height && std::getline(file, line); ++i) {
            std::istringstream iss(line);
            for (int j = 0; j < width && iss; ++j) {
                std::string token;
                if (std::getline(iss, token, ' ')) {
                    try {
                        image[i][j] = std::stoi(token);
                    }
                    catch (const std::invalid_argument&) {
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
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}

void displayImage(int** image, int height, int width, int x, int y) {
    // In ra hình ảnh pixel có màu
    int bar1 = 177; // mã ANSI
    int bar2 = 219;
    gotoxy(x, y);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            switch (image[i][j]) {
            case 0:
                std::cout << ANSI_COLOR_BLACK << (char)bar2 << (char)bar2;
                break;
            case 1:
                std::cout << ANSI_COLOR_RED << (char)bar2 << (char)bar2;
                break;
            case 2:
                std::cout << ANSI_COLOR_GREEN << (char)bar2 << (char)bar2;
                break;
            case 3:
                std::cout << ANSI_COLOR_YELLOW << (char)bar2 << (char)bar2;
                break;
            case 4:
                std::cout << ANSI_COLOR_BLUE << (char)bar2 << (char)bar2;
                break;
            case 5:
                std::cout << ANSI_COLOR_MAGENTA << (char)bar2 << (char)bar2;
                break;
            case 6:
                std::cout << ANSI_COLOR_CYAN << (char)bar2 << (char)bar2;
                break;
            case 7:
                std::cout << ANSI_COLOR_BRIGHTRED << (char)bar2 << (char)bar2;
                break;
            case 8:
                std::cout << ANSI_COLOR_BRIGHTGREEN << (char)bar2 << (char)bar2;
                break;
            case 9:
                std::cout << ANSI_COLOR_BRIGHTYELLOW << (char)bar2 << (char)bar2;
                break;
            case 10:
                std::cout << ANSI_COLOR_BRIGHTBLUE << (char)bar2 << (char)bar2;
                break;
            case 11:
                std::cout << ANSI_COLOR_BRIGHTMAGENTA << (char)bar2 << (char)bar2;
                break;
            case 12:
                std::cout << ANSI_COLOR_BRIGHTCYAN << (char)bar2 << (char)bar2;
                break;
            case 13:
                std::cout << ANSI_COLOR_BRIGHTWHITE << (char)bar2 << (char)bar2;
                break;
            case 14:
                std::cout << ANSI_COLOR_BRIGHTBLACK << (char)bar2 << (char)bar2;
                break;
            case 15:
                std::cout << ANSI_COLOR_WHITE << (char)bar2 << (char)bar2;
                break;

            default:
                std::cout << ANSI_COLOR_RESET << (char)bar2 << (char)bar2;
                break;
            }
        }
        gotoxy(x, ++y);

    }
}

//====================================== Logic Game Functions ======================================

// random vi tri cua qua tao trong board game
void createApple() {
    srand(static_cast<unsigned int>(time(0)));
    int x, y;
    bool isOnSnake; // bien check trang thai cua ran
    do {
        isOnSnake = false; // gia su la ran chua trung 
        x = rand() % (WIDTH - 2) + 2;
        y = rand() % (HEIGHT - 1) + 1;

        // kiem tra xem vi tri qua tao co trung voi con ran khong
        for (size_t i = 0; i < snake.size(); i++) {
            if (snake[i].x == x && snake[i].y == y) {
                isOnSnake = true;
                break;
            }
        }

        // kiem tra xem con ran co nam tren boardgame khong
        if (!isOnSnake && (x == 0 || x == WIDTH || y == 0 || y == HEIGHT - 1)) {
            isOnSnake = true;
        }

    } while (isOnSnake);

    apple = { x, y }; // set vi tri moi cho apple

    gotoxy(x, y);
    SetColor(225);
    cout << APPLE;
    cout.flush();
}

// tang do dai cho con ran khi no an trung apple
void growing() {
    snake.push_back(prevTail); // push_back vao duoi con ran
    // kiem tra xem chuoi mssv da het chua
    if (!MSSV.empty()) {
        MoveFirstChar(MSSV, CurrentSnake);
    }
    // neu da het thi dung chuoi fullMSSV de them vao
    else {
        MoveFirstChar(fullMSSV, CurrentSnake);
    }
}

// Kiem tra xem con ran co dung vao tuong khong
bool isHitWall() {
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
    SetColor(7);
    int** snakePic2 = new int* [100];
    for (int i = 0; i < 100; ++i)
        snakePic2[i] = new int[100];

    int** snakePic3 = new int* [100];
    for (int i = 0; i < 100; ++i)
        snakePic3[i] = new int[100];

    readImageFromFile(snakePic2, 21, 21, "FileText//SnakePic2.txt", 15);
    readImageFromFile(snakePic3, 21, 21, "FileText//SnakePic3.txt", 15);

    system("cls");

    for (;;) {
        setConsoleBackgroundColor(7);
        printTextUTF8("FileText//logo.txt", 20, 1, 113);
        displayImage(snakePic2, 21, 21, 2, 9);
        displayImage(snakePic3, 21, 21, 76, 9);
        int key = 0;
        INTRO(key);
        /*if (key == '\r') {*/
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
            SetColor(7);
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
                gotoxy(59, 15); cout << "ON ";
                break;
            }

            case 2:
            {
                gotoxy(59, 15); cout << "OFF";
                break;
            }
            }
            gotoxy(40, 24);
            SetColor(113);
            cout << "(*) Press enter to back to MENU" << endl;
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
                    cout << "ON ";
                    if (!checkMusic) {
                        checkMusic = true;
                    }
                    break;
                case 2: // TURN OFF THE MUSIC
                    gotoxy(59, 15);
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

        case 5:					//BUTTON EXIT
        {
            SetColor(228);
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
            SetColor(238);
            for (int i = 39; i < 78; i++) { // adjusted loop range
                for (int j = 13; j < 20; j++) {
                    gotoxy(i, j);
                    cout << " ";
                }
            }

            gotoxy(45, 14); // subtracted 2 from x-coordinate
            SetColor(228);
            cout << "Do you really want to quit?";

            int selectedButton = 0; // 0 for "YES", 1 for "NO"

            // Handle button press
            char ch;
            bool quitConfirmed = false;
            while (!quitConfirmed) {
                // Update button colors based on the selected button
                gotoxy(48, 18); // subtracted 2 from x-coordinate
                SetColor(selectedButton == 0 ? 225 : 228);
                cout << "YES";

                gotoxy(65, 18); // subtracted 2 from x-coordinate
                SetColor(selectedButton == 1 ? 225 : 228);
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

        case 4:					//BUTTON ABOUT US
        {
            system("cls");
            setConsoleBackgroundColor(7);
            printTextUTF8("FileText//About.txt", 29, 4, 113);

            gotoxy(34, 24);
            SetColor(113);
            cout << "(*) Press enter to back to MENU" << endl;
            while (key = _getch()) {
                if (key == '\r') {
                    PlaySound(TEXT("Sound//click1.wav"), NULL, SND_ASYNC);
                    break;
                }
            }
            system("cls");
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

    printTextUTF8("FileText//ba.txt", 37, 10, 225);
    Sleep(1000);
    printTextUTF8("FileText//hai.txt", 37, 10, 225);
    Sleep(1000);
    for (int i = 37; i < 47; i++) {
        for (int j = 10; j < 18; j++) {
            gotoxy(i, j);
            SetColor(234);
            cout << " ";
        }
    }
    printTextUTF8("FileText//mot.txt", 37, 10, 225);
    Sleep(1000);
    for (int i = 37; i < 47; i++) {
        for (int j = 10; j < 18; j++) {
            gotoxy(i, j);
            SetColor(234);
            cout << " ";
        }
    }
    //startGame(); // Start the game
}

// Man hinh nhap thong tin nguoi choi
void inputInfoPlayer() {
    system("cls");
    int key = 0;
    for (;;) {
        
        NewGameandContinued(key);
        switch (key) {
        case 1:					//BUTTON START
        {
            system("cls");
            t = 5; // Assign the selected level to variable t
            // 40 - 10
            for (int i = 5; i < 25; i++) {
                for (int j = 20; j < 100; j++) {
                    gotoxy(j, i);
                    SetColor(116);
                    cout << " ";
                }
            }
            // Input player's name
            gotoxy(40, 10);
            ShowConsoleCursor(TRUE);
            SetColor(116);
            cout << "Insert your name (Maximum 20 characters): ";
            SetColor(116);
            gotoxy(48, 20);
            cout << "Press enter to continue";
            cout << endl;
            cout << endl;
            cout << endl;
            for (int i = 50; i < 70; i++) {
                SetColor(240);
                gotoxy(i, 15);
                cout << " ";
            }
            gotoxy(50, 15);
            getline(cin, Name);
            PlaySound(TEXT("Sound//click1.wav"), NULL, SND_ASYNC);
            resetSnake(); // Reset snake's state

            speed = (550 - t * 100); // Adjust game speed based on level

            //drawBackground(120, 29, 234); // fill mau cho background
            SetColor(234);

            system("cls");
            setConsoleBackgroundColor(7);
            printTextUTF8("FileText//guide.txt", 5, 1, 113);
            char ch = _getch();
            if (ch == '\r') {
                setConsoleBackgroundColor(14);
                startGame();
            }
            //ready();
            break;
        }
        case 2:
        {
            
            system("cls");
            showStartMenu();

            // dang phat trien phan save game (neu kip ;-;)
            /*
            for (int i = 5; i < 25; i++) {
                for (int j = 20; j < 100; j++) {
                    gotoxy(j, i);
                    SetColor(116);
                    cout << " ";
                }
            }
            ifstream filein("FileText//FileNameSaveGame.txt", ios::in);
            if (!filein.is_open()) {
                cout << "Khong the mo file !!!" << endl;
                return;
            }

            std::vector<std::string> saveFiles;
            std::string line;
            int lineNumber = 0;
            while (std::getline(filein, line)) {
                saveFiles.push_back(line);
                lineNumber++;
            }

            filein.close();
            system("cls");

            // Tính toán vị trí cần in
            int printStartPos = (30 - lineNumber) / 2;

            // In danh sách các file ra giữa màn hình
            for (int i = 0; i < saveFiles.size(); i++) {
                gotoxy(60 - saveFiles[i].length() / 2, printStartPos + i);
                cout << saveFiles[i] << endl;  // Thêm dòng này
            }

            string fileName;
            gotoxy(50, 25);
            cout << "Nhap file can choi: "; cin >> fileName;

            string filePath = "SaveGame//" + fileName;
            ifstream load(filePath.c_str(), ios::in);

            if (load.is_open()) {
                // Read the first line for name
                getline(load, Name);

                // Read the second line for score
                std::string score_str;
                getline(load, score_str);
                try {
                    score = std::stoi(score_str);
                }
                catch (std::invalid_argument& e) {
                    std::cerr << "Invalid score: " << score_str << '\n';
                    return ;
                }

                // Read the remaining lines for coordinates
                std::string line;
                while (getline(load, line)) {
                    std::istringstream iss(line);
                    int x, y;
                    if (iss >> x >> y) {
                        snake.push_back({ x, y });
                    }
                }
                load.close();
            }
            else {
                std::cerr << "Unable to open file";
                return;
            }

            system("cls");
            SetColor(234);
            startGame();
            */
            break;
        }
        }

    }
}

// man hinh pausegame
void pauseGame() {
    // 21 - 61
    // 8 - 16
    SetColor(228);
    gotoxy(21, 8);
    for (int i = 21; i < 61; i++) {

        if (i == 21 || i == 61) cout << topLeftCorner;
        else cout << horizontalLineTop;
    }
    cout << topRightCorner;

    gotoxy(21, 16);
    for (int i = 21; i < 61; i++) {
        if (i == 21 || i == 61) cout << topLeftCorner;
        else cout << horizontalLineBottom;
    }
    cout << bottomRightCorner;

    for (int i = 8; i < 16; i++) {
        gotoxy(21, i);
        cout << verticalLine;
        gotoxy(61, i);
        cout << verticalLine;
    }
    // Fill màu trong khung
    SetColor(234);
    for (int i = 22; i < 61; i++) {
        for (int j = 9; j < 16; j++) {
            gotoxy(i, j);
            cout << " ";
        }
    }
    gotoxy(29, 12);
    SetColor(229);
    cout << "Press enter to continue...";

    char ch;
    bool enterPressed = false; // bien ktra xem phim enter da duoc nhan chua
    while (!enterPressed) {
        ch = _getch();
        if (ch != '\r') {
        }
        else if (ch == '\r') {
            enterPressed = true;
            gotoxy(29, 12);
            cout << "                          ";
            // doi 3 giay de tiep tuc tro choi
            for (size_t i = 3; i > 0; i--) {
                gotoxy(41, 12);
                cout << i;
                Sleep(1000);
            }
            gotoxy(41, 12);
            cout << " ";

            // --------------------------
            for (int i = 21; i <= 61; i++) {
                for (int j = 8; j <= 16; j++) {
                    gotoxy(i, j);
                    cout << " ";
                }
            }
        }

        SetColor(225);
        gotoxy(apple.x, apple.y);
        cout << APPLE;
    }
    isPaused = false;
}

// ham save game (dang trong giai doan phat trien)
void saveGame() {
    // Draw the frame
    gotoxy(21, 8);
    cout << char(218);
    gotoxy(21, 16);
    cout << char(192);
    gotoxy(61, 8);
    cout << char(191);
    gotoxy(61, 16);
    cout << char(217);

    for (int i = 22; i < 61; i++) {
        gotoxy(i, 8);
        cout << char(196);
        gotoxy(i, 16);
        cout << char(196);
    }

    for (int i = 9; i < 16; i++) {
        gotoxy(21, i);
        cout << '|';
        gotoxy(61, i);
        cout << '|';
    }

    // Fill color inside the frame
    SetColor(234);
    for (int i = 22; i < 61; i++) {
        for (int j = 9; j < 16; j++) {
            gotoxy(i, j);
            cout << " ";
        }
    }

    gotoxy(28, 10);
    SetColor(229);
    cout << "Do you want to save game?";

    int selectedButton = 0; // 0 for "YES", 1 for "NO"

    // Handle button press
    char ch;
    bool quitConfirmed = false;
    while (!quitConfirmed) {
        // Update button colors based on the selected button
        gotoxy(30, 14);
        SetColor(selectedButton == 0 ? 225 : 228);
        cout << "YES";

        gotoxy(50, 14);
        SetColor(selectedButton == 1 ? 225 : 228);
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
        for (int j = 8; j <= 16; j++) {
            gotoxy(i, j);
            cout << " ";
        }
    }

    SetColor(225);
    gotoxy(apple.x, apple.y);
    cout << APPLE;
}

// ham quit game 
void quitGame() {
    // Draw the frame
    SetColor(228);
    gotoxy(21, 8);
    for (int i = 21; i < 61; i++) {

        if (i == 21 || i == 61) cout << topLeftCorner;
        else cout << horizontalLineTop;
    }
    cout << topRightCorner;

    gotoxy(21, 16);
    for (int i = 21; i < 61; i++) {
        if (i == 21 || i == 61) cout << topLeftCorner;
        else cout << horizontalLineBottom;
    }
    cout << bottomRightCorner;

    for (int i = 8; i < 16; i++) {
        gotoxy(21, i);
        cout << verticalLine;
        gotoxy(61, i);
        cout << verticalLine;
    }

    // Fill color inside the frame
    SetColor(234);
    for (int i = 22; i < 61; i++) {
        for (int j = 9; j < 16; j++) {
            gotoxy(i, j);
            cout << " ";
        }
    }

    gotoxy(28, 10);
    SetColor(229);
    cout << "Do you really want to quit?";

    int selectedButton = 0; // 0 for "YES", 1 for "NO"

    // Handle button press
    char ch;
    bool quitConfirmed = false;
    while (!quitConfirmed) {
        // Update button colors based on the selected button
        gotoxy(30, 14);
        SetColor(selectedButton == 0 ? 225 : 228);
        cout << "YES";

        gotoxy(50, 14);
        SetColor(selectedButton == 1 ? 225 : 228);
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
                showEndMenu();
            }
            else if (selectedButton == 1) {
                quitConfirmed = true;
                break;
            }
        }
    }

    // Clear the frame
    for (int i = 21; i <= 61; i++) {
        for (int j = 8; j <= 16; j++) {
            gotoxy(i, j);
            cout << " ";
        }
    }

    SetColor(225);
    gotoxy(apple.x, apple.y);
    cout << APPLE;
}

// ham hien thi tro choi (ran, apple,...)
void startGame() {
    system("cls"); // clear man hinh

    bool checkReady = false;
    ShowConsoleCursor(false); // tat con tro nhap

    drawBox();      // goi ham ve board game
    displayScoreInGame(); // hien thi diem

    while (checkReady == false) {
        ready();
        checkReady = true;
    }

    createApple();  // tao random qua tao
    drawSnake();    // ve con ran

    while (true) {
        // ham check phim an an tu ban phim
        if (_kbhit()) { // thuoc thu vien <conio.h>
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
                isPaused = true;
                pauseGame();
            }
            else if (ch == 'g') {
                //saveGame(); dang thuc hien
            }
            else if (ch == 'q') // Quit game
            {
                quitGame();
            }
        }

        move();          // ham di chuyen con ran
        drawSnake();    // ve duoi va dau ran
        drawHeadnTail();

        if (isAteApple()) {
            // add am thanh khi con ran an qua tao
            PlaySound(TEXT("Sound//pop.wav"), NULL, SND_ASYNC);
            score += 10;        // tang 1 diem khi an trung tao
            displayScoreInGame();     // hien thi diem vua tang
            growing();          // tang do dai cho con ran
            createApple();      // tao lai qua tao
        }

        if (isBiteItself() || isHitWall()) { // neu con ran can vao than minh hoac dung vao tuong
            PlaySound(TEXT("Sound//gameover.wav"), NULL, SND_ASYNC);
            Sleep(1000);
            showEndMenu(); // hien thi man hinh endgame
            break;
        }
        Sleep(speed);
    }
}

// Hien thi menu khi thua
void showEndMenu() {
    system("cls");
    excuteReadFile(); // luu diem (tat se kh luu vao file nua)

    setConsoleBackgroundColor(7);

    printTextUTF8("FileText//youlose.txt", 28, 1, 116);
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
                resetSnake();
                setConsoleBackgroundColor(14);
                startGame();
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
void resetSnake() {
    snake.clear();
    // khoi tao lai con ran nhu ban dau
    snake = {
        Point{WIDTH / 2 + 3, HEIGHT / 2},   // (48,15)
        Point{WIDTH / 2 + 2, HEIGHT / 2},   // (47,15)
        Point{WIDTH / 2 + 1, HEIGHT / 2},   // (46,15)
        Point{WIDTH / 2 + 0, HEIGHT / 2},   // (45,15)
        Point{WIDTH / 2 - 1, HEIGHT / 2},   // (44,15)
        Point{WIDTH / 2 - 2, HEIGHT / 2},   // (43,15)
        Point{WIDTH / 2 - 3, HEIGHT / 2},   // (42,15)
        Point{WIDTH / 2 - 4, HEIGHT / 2},   // (41,15)  
    };

    // Reset cac variable khac
    MSSV = "23120223231202242312022523120250";
    CurrentSnake = "71202132";
    fullMSSV = "2312021723120223231202242312022523120250";
    score = 0;

    direction = Direction::right;
}

// doc va luu file
void readSaveGame() {
    system("cls");
    string file;
    
    for (int i = 5; i < 25; i++) {
        for (int j = 20; j < 100; j++) {
            gotoxy(j, i);
            SetColor(116);
            cout << " ";
        }
    }

    gotoxy(40, 17);
    cout << "Luu y: Ten file nhap vao khong co khoang trang !!!";

    gotoxy(40, 10);
    ShowConsoleCursor(TRUE);
    SetColor(116);
    cout << "Nhap ten file can luu: "; cin >> file;
    SetColor(116);

    string filePath = "SaveGame//" + file + ".txt";

    ofstream outputFile(filePath.c_str(), ios::app);
    ofstream fileName("FileText//FileNameSaveGame.txt", ios::app);

    if (!outputFile) {
        cout << "khong the mo file" << endl;
        return;
    }
    outputFile << Name << endl;
    outputFile << score << endl;

    // Lưu tọa độ của con rắn
    for (const auto& point : snake) {
        outputFile << point.x << " " << point.y << endl;
    }

    fileName << file + ".txt";
    cout << endl;
    cout << endl;
    cout << endl;

    outputFile.close();
    fileName.close();
    // In ra thông báo
    gotoxy(30, 20);
    cout << "Da luu file thanh cong. An phim enter de tiep tuc." << endl;

    // Chờ người dùng nhấn enter
    cin.ignore();  // ignore the newline character left in the buffer by the previous input
    cin.get();  // wait for the user to press enter

    showStartMenu();
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

    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);

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