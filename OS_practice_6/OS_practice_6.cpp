#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <WinUser.h>

char mem[640];

void clear() {
    COORD pos;
    pos.X = 0;
    pos.Y = 20;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    std::cout << "                              \n                              ";
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void draw() {
    COORD pos;
    for (short i = 0; i < 640; i++) {
        pos.X = i % 40 + 1;
        pos.Y = i / 40 + 2;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
        std::cout << mem[i];
    }
    clear();
}

int main() {
    CONSOLE_CURSOR_INFO inf;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &inf);
    inf.bVisible = false;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &inf);
    std::cout << "3. Variable Sections\n";
    std::cout << char(218);
    for (short i = 0; i < 40; i++) std::cout << char(196);
    std::cout << char(191) << '\n';
    for (short i = 0; i < 16; i++) {
        std::cout << char(179);
        for (short j = 0; j < 40; j++) std::cout << ' ';
        std::cout << char(179) << '\n';
    }
    std::cout << char(192);
    for (short i = 0; i < 40; i++) std::cout << char(196);
    std::cout << char(217) << "\na - add task   d - delete task\n";
    for (short i = 0; i < 640; i++) mem[i] = ' ';
    bool taskLetterIsFree[26];
    for (short i = 0; i < 26; i++) taskLetterIsFree[i] = true;
    for (;;) {
        char input = _getch();
        clear();
        if (input == 'a') {
            char taskLetter = ' ';
            for (short i = 0; i < 26; i++) {
                if (taskLetterIsFree[i]) {
                    taskLetter = 97 + i;
                    taskLetterIsFree[i] = false;
                    break;
                }
            }
            if (taskLetter == ' ') {
                std::cout << "err: no free task letters";
                continue;
            }
            std::cout << "Size of new task: ";
            int size;
            std::cin >> size;
            if (size > 640) {
                std::cout << "err: not enough free space";
                taskLetterIsFree[taskLetter - 97] = true;
            } else {
                for (short i = 0; i < 640 - (size - 1); i++) {
                    bool ok = true;
                    for (short j = 0; j < size; j++) {
                        if (mem[i + j] != ' ') {
                            ok = false;
                            break;
                        }
                    }
                    if (ok) {
                        for (short j = 0; j < size; j++) mem[i + j] = taskLetter;
                        draw();
                        break;
                    }
                    if (i == 640 - size - 1 and ok == false) {
                        std::cout << "err: not enough free space";
                        taskLetterIsFree[taskLetter - 97] = true;
                    }
                }
            }
        } else if (input == 'd') {
            std::cout << "Letter of task: ";
            std::cin >> input;
            for (short i = 0; i < 640; i++) if (mem[i] == input) mem[i] = ' ';
            taskLetterIsFree[input - 97] = true;
            draw();
        }
    }
}
