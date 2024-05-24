#include "HeaderGame.h"
#include "SystemGame.h"
int main() {
    SetConsoleTitleW(L"Snake Game"); // set tieu de console
    FixConsoleWindow(); // fix phong to cua so
    ShowScrollbar(FALSE); // tat thanh cuon

    setConsoleBackgroundColor(7);
    SetColor(7);

    int** snakePic = new int* [100];
    for (int i = 0; i < 100; ++i)
        snakePic[i] = new int[100];
    
    readImageFromFile(snakePic, 21, 21, "FileText//SnakePic.txt", 15);
    displayImage(snakePic, 21, 21, 38, 5);

    this_thread::sleep_for(chrono::seconds(3));

    showStartMenu();
    //startGame(1);

    for (int i = 0; i < 100; i++) {
        delete[] snakePic[i];
    }
    delete[] snakePic;

    // test
    //cout << (char)219 << " " << (char)220 << " " << (char)223;
    return 0;
}
