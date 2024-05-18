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
char Name[21] = "";                     // bien luu tru ten nguoi choi, ban dau khoi tao rong
int t, n;
const int LimitPlayers = 1000;          // so luong nguoi choi toi da luu duoc
bool checkMusic = true;                 // check trang thai nhac nen
bool isPaused = false;                  // check trang thai pause game
char date[20];
char thoigian[20];

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
    // -- ve 4 goc cua board game
    gotoxy(1, 0);
    cout << char(218);
    //cout << " ";

    gotoxy(1, HEIGHT);
    cout << char(192);
    //cout << " ";

    gotoxy(WIDTH, 0);
    cout << char(191);
    //cout << " ";

    gotoxy(WIDTH, HEIGHT);
    cout << char(217);
    //cout << " ";
    // --------------------------

    for (int i = 2; i < WIDTH; i++) {
        gotoxy(i, 0);
        cout << char(196);
        //cout << " ";
        gotoxy(i, HEIGHT);
        cout << char(196);
        //cout << " ";
    }

    for (int i = 1; i < HEIGHT; i++) {
        gotoxy(1, i);
        cout << "|";
        gotoxy(WIDTH, i);
        cout << "|";
    }

    gotoxy(16, 29);
    SetColor(233);
    cout << "Press <P> to pause game - Press <Q> to end game";

    // -----------------------------------------------------
    gotoxy(82, 0);
    cout << char(218);

    gotoxy(82, 28);
    cout << char(192);

    gotoxy(118, 0);
    cout << char(191);

    gotoxy(118, 28);
    cout << char(217);

    for (int i = 83; i < 118; i++) {
        gotoxy(i, 0);
        cout << char(196);
        gotoxy(i, 28);
        cout << char(196);
        gotoxy(i, 12);
        cout << '_';
    }

    for (int i = 1; i < 28; i++) {
        gotoxy(82, i);
        cout << '|';
        gotoxy(118, i);
        cout << '|';
    }
}

// ve mau nen cho background
void drawBackground(int width, int height, int x) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            SetColor(x);
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
    //displayFileDrawASCII("FileText//leaderboard.txt",0,1,234);
    //SetColor(234);

    printTextUTF8("FileText//leaderboard.txt", 19, 1, 234);
    int i;
    quickSort(inf, 0, n - 1); // sap xep danh sach

    // draw box highscore
    SetColor(228);
    gotoxy(40, 10);
    cout << "                LEADERBOARD" << endl;
    gotoxy(27, 12);
    cout << "--------------------------------------------------------------------------" << endl;
    gotoxy(27, 13);
    cout << "| No. |            Name            | Score |     Date     |     Time     |" << endl;
    gotoxy(27, 14);
    cout << "--------------------------------------------------------------------------" << endl;

    for (i = 0; i < min(10, n); i++) {
        gotoxy(30, 15 + i);
        {
            SetColor(237);
            cout << i + 1;
        }

        gotoxy(27, 15 + i);
        {
            SetColor(228);
            cout << "|";
        }

        gotoxy(36, 15 + i);
        {
            SetColor(237);
            cout << inf[i].name;
        }

        gotoxy(33, 15 + i);
        {
            SetColor(228);
            cout << "|";
        }
        gotoxy(65, 15 + i);
        {
            SetColor(237);
            cout << inf[i].diem;
        }
        gotoxy(62, 15 + i);
        {
            SetColor(228);
            cout << "|";
        }

        gotoxy(70, 15 + i);
        {
            SetColor(228);
            cout << "|";
        }

        gotoxy(73, 15 + i);
        {
            SetColor(237);

            cout << inf[i].day;
        }

        gotoxy(85, 15 + i);
        {
            SetColor(228);
            cout << "|";
        }

        gotoxy(89, 15 + i);
        {
            SetColor(237);
            cout << inf[i].time;
        }
        gotoxy(100, 15 + i);
        {
            SetColor(228);
            cout << "|";
        }
    }

    gotoxy(27, 15 + i);
    {
        SetColor(228);
        cout << "--------------------------------------------------------------------------" << endl;
    }
    gotoxy(47, 16 + i);
    {
        cout << "(*) Press enter to back to MENU" << endl;
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
void INTRO(int& key)
{
    char board = 'w';
    while (board != ' ')
    {
        gotoxy(30, 0);
        cout << "===================== WELCOME TO ======================= ";
        gotoxy(15, 1);
        /*cout << R"(
              /$$$$$$  /$$   /$$  /$$$$$$  /$$   /$$ /$$$$$$$$        /$$$$$$   /$$$$$$  /$$      /$$ /$$$$$$$$
             /$$__  $$| $$$ | $$ /$$__  $$| $$  /$$/| $$_____/       /$$__  $$ /$$__  $$| $$$    /$$$| $$_____/
            | $$  \__/| $$$$| $$| $$  \ $$| $$ /$$/ | $$            | $$  \__/| $$  \ $$| $$$$  /$$$$| $$
            |  $$$$$$ | $$ $$ $$| $$$$$$$$| $$$$$/  | $$$$$         | $$ /$$$$| $$$$$$$$| $$ $$/$$ $$| $$$$$
             \____  $$| $$  $$$$| $$__  $$| $$  $$  | $$__/         | $$|_  $$| $$__  $$| $$  $$$| $$| $$__/
             /$$  \ $$| $$\  $$$| $$  | $$| $$\  $$ | $$            | $$  \ $$| $$  | $$| $$\  $ | $$| $$
            |  $$$$$$/| $$ \  $$| $$  | $$| $$ \  $$| $$$$$$$$      |  $$$$$$/| $$  | $$| $$ \/  | $$| $$$$$$$$
             \______/ |__/  \__/|__/  |__/|__/  \__/|________/       \______/ |__/  |__/|__/     |__/|________/
)"
<< "\n";*/
        gotoxy(0, 10);
        cout << "  =============  ";
        if (board == 'a')
        {
            for (int i = 40; i < 69; i++)
            {
                gotoxy(i, 14);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 127);
            }
            key = 1;
        }
        gotoxy(0, 11);
        cout << "||             ||";
        gotoxy(0, 12);
        cout << "||    START    ||";
        gotoxy(0, 13);
        cout << "||             ||";
        gotoxy(0, 14);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        cout << "  =============  ";

        gotoxy(30, 10);
        cout << "  =============  ";

        if (board == 'd')
        {
            key = 2;
            for (int i = 40; i < 69; i++)
            {
                gotoxy(i, 20);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 127);
            }
        }
        gotoxy(30, 11);
        cout << "||             ||";
        gotoxy(30, 12);
        cout << "||     END     ||";
        gotoxy(30, 13);
        cout << "||             ||";
        gotoxy(30, 14);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        cout << "  =============  ";
        board = _getch();
    }
    system("cls");
}

// doc file anh
void readImageFromFile(int** image, int height, int width, const string& filename, int backgroundcolor) {
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        for (int i = 0; i < height && std::getline(file, line); ++i) {
            istringstream iss(line);
            for (int j = 0; j < width && iss; ++j) {
                string token;
                if (getline(iss, token, ' ')) {
                    try {
                        image[i][j] = std::stoi(token);
                    }
                    catch (const invalid_argument& e) {
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

// hien thi file anh co mau
void displayImageColor(int** image, int height, int width, int x, int y) {
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

// hien thi anh con ran
void displayImageSnake(string fileName) {
    ShowConsoleCursor(FALSE);
    system("color 80");
    SetColor(7);

    const int rows = 21;
    const int cols = 21;
    int** snakePic = new int* [rows];
    for (int i = 0; i < rows; ++i) {
        snakePic[i] = new int[cols];
    }
    readImageFromFile(snakePic, rows, cols, fileName, 14);
    displayImageColor(snakePic, rows, cols, 38, 5);
    while (_kbhit()) {
        char key = _getch(); // Đọc phím nhấn vào
        if (key != '\r') {

        }
    }
    std::this_thread::sleep_for(std::chrono::seconds(2));
    for (int i = 0; i < rows; ++i) {
        delete[] snakePic[i];
    }
    delete[] snakePic;
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

    Info* inf = new Info[LimitPlayers];

    if (checkMusic == true) { // check trang thai de bat nhac nen
        PlaySound(TEXT("Sound//soundtrack.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    }

    drawBackground(29, 120, 234); // fill mau cho background

    // meo hieu sao bi loi dong cuoi nen phai tu fill ngoai
    for (int i = 0; i < 120; i++) {
        gotoxy(i, 30);
        SetColor(234);
        cout << " ";
    }

    int Set[] = { 234,228,228,228,228,228 }; // color option
    int counter = 1;
    char key;

    for (;;) {
        //displayFileDrawASCII("FileText//logo.txt", 10, 2, 233);
        printTextUTF8("FileText//logo.txt", 18, 2, 233);

        ShowConsoleCursor(FALSE);
        ShowScrollbar(0);

        gotoxy(55, 12);
        SetColor(Set[0]);
        cout << "START";

        gotoxy(55, 15);
        SetColor(Set[1]);
        cout << "GUIDE";

        gotoxy(54, 18);
        SetColor(Set[2]);
        cout << "RANKING";

        gotoxy(54, 21);
        SetColor(Set[3]);
        cout << "SETTING";

        gotoxy(54, 24);
        SetColor(Set[4]);
        cout << "ABOUT US";

        gotoxy(53, 27);
        SetColor(Set[5]);
        cout << "QUIT GAME";

        key = _getch();

        if (key == 72 || key == 'w' && (counter >= 2 && counter <= 6)) {
            counter--;
            PlaySound(TEXT("Sound//click1.wav"), NULL, SND_ASYNC);
            if (counter < 1) {
                counter = 6; // Quay lại dòng EXIT
            }
        }
        if (key == 80 || key == 's' && (counter >= 1 && counter <= 5)) {
            PlaySound(TEXT("Sound//click1.wav"), NULL, SND_ASYNC);
            counter++;
            if (counter > 6) {
                counter = 1; // Quay lại dòng START
            }
        }

        for (int j = 0; j < 6; j++) {
            Set[j] = 228;
        }

        switch (counter) {
        case 1: {
            Set[0] = 234; break;
        }
        case 2: {
            Set[1] = 234; break;
        }
        case 3: {
            Set[2] = 234; break;
        }
        case 4: {
            Set[3] = 234; break;
        }
        case 5: {
            Set[4] = 234; break;
        }
        case 6: {
            Set[5] = 234; break;
        }
        }
        if (key == '\r') {
            PlaySound(TEXT("Sound//click1.wav"), NULL, SND_ASYNC);
            switch (counter) {
            case 1://BUTTON START
            {
                inputInfoPlayer(); // vao nhap ten va chon level
                break;
            }
            case 2:	//BUTTON INSTRUCTIONS
            {
                system("cls");
                // doc huong dan su dung truoc khi dung
                printTextUTF8("FileText//guide.txt", 0, 2, 237);
                gotoxy(25, 24);
                SetColor(237);
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
            case 3://BUTTON RANKING
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
            case 4: // BUTTON SETTING
            {
                // bat tat nhac nen
                system("cls");
                printTextUTF8("FileText//setting.txt", 30, 2, 237);
                static int count = 1;
                gotoxy(47, 15); cout << "MUSIC";
                SetColor(226);
                gotoxy(55, 15); cout << "<        >";
                SetColor(224);

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
                SetColor(237);
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
            case 5://BUTTON ABOUT US
            {
                system("cls");

                printTextUTF8("FileText//About.txt", 29, 4, 237);

                gotoxy(34, 24);
                SetColor(226);
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
            case 6:	//BUTTON EXIT
            {
                // them giao dien exit game ;-;
                //40 - 80
                //12 - 20
                gotoxy(40, 12);
                cout << char(218);
                gotoxy(40, 20);
                cout << char(192);
                gotoxy(80, 12);
                cout << char(191);
                gotoxy(80, 20);
                cout << char(217);

                for (int i = 41; i < 80; i++) {
                    gotoxy(i, 12);
                    cout << char(196);

                    gotoxy(i, 20);
                    cout << char(196);
                }

                for (int i = 13; i < 20; i++) {
                    gotoxy(40, i);
                    cout << '|';

                    gotoxy(80, i);
                    cout << '|';
                }

                // Fill color inside the frame
                SetColor(234);
                for (int i = 41; i < 80; i++) {
                    for (int j = 13; j < 20; j++) {
                        gotoxy(i, j);
                        cout << " ";
                    }
                }

                gotoxy(47, 14);
                SetColor(229);
                cout << "Do you really want to quit?";

                int selectedButton = 0; // 0 for "YES", 1 for "NO"

                // Handle button press
                char ch;
                bool quitConfirmed = false;
                while (!quitConfirmed) {
                    // Update button colors based on the selected button
                    gotoxy(50, 18);
                    SetColor(selectedButton == 0 ? 225 : 228);
                    cout << "YES";

                    gotoxy(70, 18);
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
                            exit(1);
                        }
                        else if (selectedButton == 1) {
                            quitConfirmed = true;
                            break;
                        }
                    }
                }

                // Clear the frame
                for (int i = 40; i <= 80; i++) {
                    for (int j = 12; j <= 20; j++) {
                        gotoxy(i, j);
                        cout << " ";
                    }
                }
            }
            }
        }
    }
    delete[] inf;
}

// Man hinh nhap thong tin nguoi choi
void inputInfoPlayer() {
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
    cin.getline(Name, 20);
    PlaySound(TEXT("Sound//click1.wav"), NULL, SND_ASYNC);
    resetSnake(); // Reset snake's state

    speed = (550 - t * 100); // Adjust game speed based on level

    //drawBackground(120, 29, 234); // fill mau cho background
    SetColor(234);
    startGame(); // Start the game
}

// man hinh pausegame
void pauseGame() {
    // 21 - 61
    // 8 - 16
    gotoxy(21, 8);
    cout << char(218);

    gotoxy(21, 16);
    cout << char(192);

    gotoxy(61, 8);
    cout << char(191);

    gotoxy(61, 16);
    cout << char(217);
    // --------------------------
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
    // 21 - 61
    // 8 - 16
    gotoxy(21, 8);
    cout << char(218);

    gotoxy(21, 16);
    cout << char(192);

    gotoxy(61, 8);
    cout << char(191);

    gotoxy(61, 16);
    cout << char(217);
    // --------------------------
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
    // Fill màu trong khung
    SetColor(234);
    for (int i = 22; i < 61; i++) {
        for (int j = 9; j < 16; j++) {
            gotoxy(i, j);
            cout << " ";
        }
    }
    gotoxy(28, 12);
    SetColor(229);
    cout << "Do you want to save game ?";

    char ch;
    bool enterPressed = false; // bien ktra xem phim enter da duoc nhan chua
    while (!enterPressed) {
        ch = _getch();
        if (ch != '\r') {
        }
        else if (ch == '\r') {
            enterPressed = true;
            isPaused = false;

            // --------------------------
            for (int i = 21; i < 61; i++) {
                gotoxy(i, 8);
                cout << " ";
                gotoxy(i, 16);
                cout << " ";
            }

            for (int i = 8; i < 17; i++) {
                gotoxy(21, i);
                cout << ' ';
                gotoxy(61, i);
                cout << ' ';
            }
            gotoxy(28, 12);
            cout << "                                 ";

            SetColor(225);
            gotoxy(apple.x, apple.y);
            cout << APPLE;
        }
    }
}

// ham quit game 
void quitGame() {
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

    gotoxy(29, 10);
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

    ShowConsoleCursor(false); // tat con tro nhap

    drawBox();      // goi ham ve board game
    drawSnake();    // ve con ran
    createApple();  // tao random qua tao
    displayScoreInGame(); // hien thi diem

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
                saveGame();
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

    printTextUTF8("FileText//youlose.txt", 28, 1, 234);

    SetColor(225);
    // -- ve 4 goc cua board game
    // 39 81 - 7 20
    gotoxy(39, 10);
    cout << char(218);

    gotoxy(39, 25);
    cout << char(192);

    gotoxy(81, 10);
    cout << char(191);

    gotoxy(81, 25);
    cout << char(217);
    // --------------------------
    for (int i = 40; i < 81; i++) {
        gotoxy(i, 10);
        cout << char(196);
        gotoxy(i, 25);
        cout << char(196);
    }

    for (int i = 11; i < 25; i++) {
        gotoxy(39, i);
        cout << '|';
        gotoxy(81, i);
        cout << '|';
    }

    int Set[] = { 234,228,228,228 }; // Màu sắc của các lựa chọn
    int counter = 1; // Lựa chọn hiện tại
    char key;

    while (true) {
        //system("cls");
        ShowConsoleCursor(FALSE);
        ShowScrollbar(0);
        {
            gotoxy(48, 13);
            SetColor(234);
            cout << "Your Name : ";
            SetColor(237);
            cout << Name << endl;
        }
        {
            gotoxy(48, 15);
            SetColor(234);
            cout << "Your Score: ";
            SetColor(237);
            cout << score << endl;
        }

        // Hiển thị các lựa chọn
        gotoxy(54, 18);
        SetColor(Set[0]);
        cout << "RESTART GAME";

        gotoxy(55, 20);
        SetColor(Set[1]);
        cout << "MENU GAME";

        gotoxy(55, 22);
        SetColor(Set[2]);
        cout << "QUIT GAME";

        key = _getch();

        // Xử lý các phím mũi tên lên và xuống để di chuyển lựa chọn
        if ((key == 72 || key == 'w') && (counter >= 2 && counter <= 3)) {
            PlaySound(TEXT("Sound//click1.wav"), NULL, SND_ASYNC);
            counter--;
            if (counter < 1) {
                counter = 3;
            }
        }
        if ((key == 80 || key == 's') && (counter >= 1 && counter <= 2)) {
            PlaySound(TEXT("Sound//click1.wav"), NULL, SND_ASYNC);
            counter++;
            if (counter > 3) {
                counter = 1;
            }
        }

        // Đặt màu cho các lựa chọn
        for (int j = 0; j < 3; j++) {
            Set[j] = 228;
        }

        switch (counter) {
        case 1: {
            Set[0] = 234; break;
        }
        case 2: {
            Set[1] = 234; break;
        }
        case 3: {
            Set[2] = 234; break;
        }
        }

        // Xử lý khi người dùng nhấn Enter
        if (key == '\r') {
            switch (counter) {
            case 1: {
                PlaySound(TEXT("Sound//click1.wav"), NULL, SND_ASYNC);
                resetSnake();
                startGame();
                break;
            }
            case 2: {
                PlaySound(TEXT("Sound//click1.wav"), NULL, SND_ASYNC);
                system("cls");
                showStartMenu();
                break;
            }
            case 3: {
                PlaySound(TEXT("Sound//click1.wav"), NULL, SND_ASYNC);
                exit(0);
                break;
            }
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