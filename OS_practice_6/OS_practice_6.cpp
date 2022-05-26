#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <WinUser.h>

char mem[512];

void draw() {
    for (short i = 0; i < 512; i++) {
        COORD pos;
        pos.X = i % 32 + 1;
        pos.Y = i / 32 + 2;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
        std::cout << mem[i];
    }
}

int main() {
    CONSOLE_CURSOR_INFO inf;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &inf);
    inf.bVisible = false;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &inf);
    std::cout << "3\n";
    std::cout << char(218);
    for (short i = 0; i < 32; i++) std::cout << char(196);
    std::cout << char(191) << '\n';
    for (short i = 0; i < 16; i++) {
        std::cout << char(179);
        for (short j = 0; j < 32; j++) std::cout << ' ';
        std::cout << char(179) << '\n';
    }
    std::cout << char(192);
    for (short i = 0; i < 32; i++) std::cout << char(196);
    std::cout << char(217) << '\n';
    for (short i = 0; i < 512; i++) mem[i] = ' ';
    char alphabet[26];
    for (;;) {
        char input = _getch();
        if (input == 'a') {
            int size;
            std::cin >> size;
            char letter = 96;
            for (short i = 1; i <= 26; i++) {
                bool letterok = true;
                for (short j = 0; j < 26; j++) {
                    if (alphabet[j] == letter + i) {
                        letterok = false;
                        break;
                    }
                }
                if (letterok) {
                    letter = 96 + i;
                    break;
                }
            }
            if (letter == 96) {
                std::cout << "error\n";
                continue;
            }
            for (short i = 0; i < 512; i++) {
                bool ok = true;
                for (short j = 0; j < size; j++) {
                    if (mem[i + j] != ' ') {
                        ok = false;
                        break;
                    }
                }
                if (ok) {
                    for (short j = 0; j < size; j++) {
                        mem[i + j] = letter;
                        
                    }
                    break;
                }
            }
            draw();
        } else if (input == 'd') {
            input = _getch();
            for (short i = 0; i < 512; i++) if (mem[i] == input) mem[i] = ' ';
            draw();
        }
    }
}
