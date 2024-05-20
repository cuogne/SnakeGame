#include "HeaderGame.h"
#include "SystemGame.h"
int main() {
    resizeConsole(120, 30); // fix kich thuoc cua so
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

    std::this_thread::sleep_for(std::chrono::seconds(3));

    showStartMenu();

    for (int i = 0; i < 100; i++) {
        delete[] snakePic[i];
    }
    delete[] snakePic;
    
    //printTextUTF8("check.txt", 20, 3, 233);
    // ----------------------------------------------------------------------
    //int key = 0;
    //INTRO(key);

    // bang mau
	/*
	HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	int count = 1;
	for (int k = 0; k < 300; k++, count++)
	{
		// pick the colorattribute k you want
		SetConsoleTextAttribute(hConsoleOutput, k);
		cout << k << " ";
		if (count == 16) {
			count = 0;
			cout << "\n";
		}
	}
	*/

    /*
    UINT old_cp = GetConsoleOutputCP();
    SetConsoleOutputCP(CP_UTF8);
    gotoxy(10, 6);
    cout << u8"██╗  ██╗██╗   ██╗███╗   ██╗████████╗██╗███╗   ██╗ ██████╗     ███████╗███╗   ██╗ █████╗ ██╗  ██╗███████╗";
    gotoxy(10, 7);
    cout << u8"██║  ██║██║   ██║████╗  ██║╚══██╔══╝██║████╗  ██║██╔════╝     ██╔════╝████╗  ██║██╔══██╗██║ ██╔╝██╔════╝";
    gotoxy(10, 8);
    cout << u8"███████║██║   ██║██╔██╗ ██║   ██║   ██║██╔██╗ ██║██║  ███╗    ███████╗██╔██╗ ██║███████║█████╔╝ █████╗  ";
    gotoxy(10, 9);
    cout << u8"██╔══██║██║   ██║██║╚██╗██║   ██║   ██║██║╚██╗██║██║   ██║    ╚════██║██║╚██╗██║██╔══██║██╔═██╗ ██╔══╝  ";
    gotoxy(10, 10);
    cout << u8"██║  ██║╚██████╔╝██║ ╚████║   ██║   ██║██║ ╚████║╚██████╔╝    ███████║██║ ╚████║██║  ██║██║  ██╗███████╗";
    gotoxy(10, 11);
    cout << u8"╚═╝  ╚═╝ ╚═════╝ ╚═╝  ╚═══╝   ╚═╝   ╚═╝╚═╝  ╚═══╝ ╚═════╝     ╚══════╝╚═╝  ╚═══╝╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝";
    SetConsoleOutputCP(old_cp);
    */

    return 0;
}