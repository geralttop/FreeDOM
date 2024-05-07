// ������������ �����
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <fstream>
#include "User.h" // ���������������� ������������ ���� � ������������ ������ User
#include "Lib.h" // ���������������� ����������� ���� � ������������ �������
#include <Windows.h> // ���������� ��� ������ � Windows API
#include "Game.h"
#include "Dev.h"
#include <stdio.h>
#include <conio.h>
#include <chrono>
#include <thread>
#include <regex>

using namespace std;

// ������� ��� ������ ������������� �� ������ � ������ �� � ������
vector<User> writingUsers() {
    // �������� ������� �������������
    vector<User> users;

    // �������� ������ ��� ������
    ifstream ifUsLogin;
    ifstream ifUsPass;
    ifstream ifUsBalance;
    ifUsLogin.open("Data/userNames.txt");
    ifUsPass.open("Data/passOfUsers.txt");
    ifUsBalance.open("Data/userBalances.txt");

    // ���� ���������� ������ �� ������ � ������ �� � ������� ������������
    // ���� ������������, ���� �� ��������� ����� ����� (eof) ��� ifUsLogin
    int i = 0;
    while (!ifUsLogin.eof()) {
        // ���������� ��� �������� ������ ������������
        string login;
        string pass;
        string balance;

        // ���������� ������ �� ������
        getline(ifUsLogin, login);
        getline(ifUsPass, pass);
        getline(ifUsBalance, balance);

        // �������������� ������ � �������� � ����� � ��������� ������
        float fbalance = stof(balance);

        // �������� ������� ������������ � ������������ ������� � ���������� ��� � ������
        users.push_back(User(login, pass, fbalance, i));
        i++;
    }

    // �������� ������ ����� ���������� ������
    ifUsLogin.close();
    ifUsPass.close();
    ifUsBalance.close();

    // ������� ������� �������������
    return users;
}

vector<Dev> writingDevs() {
    // �������� ������� �������������
    std::vector<Dev> devs;

    // �������� ������ ��� ������
    std::ifstream ifDevLogin;
    std::ifstream ifDevPass;
    std::ifstream ifDevBalance;
    std::ifstream ifDevCardNum;

    ifDevLogin.open("Data/devNames.txt");
    ifDevPass.open("Data/passOfDevs.txt");
    ifDevBalance.open("Data/devBalances.txt");
    ifDevCardNum.open("Data/devCardNum.txt");

    // ���� ���������� ������ �� ������ � ������ �� � ������� ������������
    // ���� ������������, ���� �� ��������� ����� ����� (eof) ��� ifDevLogin
    int i = 0;
    while (!ifDevLogin.eof()) {
        // ���������� ��� �������� ������ ������������
        std::string login;
        std::string pass;
        std::string balance;
        std::string cardNum;

        // ���������� ������ �� ������
        std::getline(ifDevLogin, login);
        std::getline(ifDevPass, pass);
        std::getline(ifDevBalance, balance);
        std::getline(ifDevCardNum, cardNum);

        // �������������� ������ � �������� � ����� � ��������� ������
        float fbalance = std::stof(balance);

        // �������� ������� ������������ � ������������ ������� � ���������� ��� � ������
        devs.push_back(Dev(login, pass, fbalance, cardNum , i));
        i++;
    }

    // �������� ������ ����� ���������� ������
    ifDevLogin.close();
    ifDevPass.close();
    ifDevBalance.close();
    ifDevCardNum.close();

    // ������� ������� �������������
    return devs;
}

vector<Game> writingDevGames(string devName) {
    vector<Game> devGames;

    string pathAbout = "Data/DevGames/About/" + devName + "About.txt";
    string pathName = "Data/DevGames/" + devName + "Games.txt";
    string pathPrice = "Data/DevGames/Price/" + devName + "Price.txt";

    ifstream ifAbout;
    ifstream ifName;
    ifstream ifPrice;

    ifAbout.open(pathAbout);
    ifName.open(pathName);
    ifPrice.open(pathPrice);

    int i = 0;
    while (!ifName.eof()) {
        string name;
        string about;
        string price;
        
        getline(ifName, name);
        getline(ifAbout, about);
        getline(ifPrice, price);

        if (price == "") price = "0";
        float fprice = stof(price);
        //cout << fprice;
        devGames.push_back(Game(name, about, fprice, i));
        i++;
    }

    ifAbout.close();
    ifName.close();
    ifPrice.close();

    return devGames;
}

vector<Game> writngAllGames() {
    /*std::vector<int> vec1{ 1, 2, 3, 4, 5 };
    std::vector<int> vec2{ 0, 9, 8, 7, 6 };
    std::vector<int> sum(vec1.size());
    vec1.insert(vec1.end(), vec2.begin(), vec2.end());
    cout << vec1[6];*/
    vector<Game> allGames;
    vector<Dev> devs = writingDevs();
    for (int i = 0; i < devs.size(); i++) {
        vector<Game> devGames = writingDevGames(devs[i].getLogin());
        allGames.insert(allGames.end(), devGames.begin(), devGames.end());
    }
    return allGames;
}
//��� ��� ���� ��� ������� ����
// �������� ���������� �������
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

// ������� ��� ����������� ������� � ������� � ������� (x, y)
void GoToXY(short x, short y) {
    // ������������� ������� ������� � �������
    SetConsoleCursorPosition(hStdOut, { x, y });
}

// ������� ��� ���������� ���������� ������� � �������
void ConsoleCursorVisible(bool show, short size) {
    // �������� ���������� � ������� ��������� �������
    CONSOLE_CURSOR_INFO structCursorInfo;
    GetConsoleCursorInfo(hStdOut, &structCursorInfo);

    // �������� ��������� �������
    structCursorInfo.bVisible = show;

    // �������� ������ �������
    structCursorInfo.dwSize = size;

    // ��������� ��������� � ��������� �������
    SetConsoleCursorInfo(hStdOut, &structCursorInfo);
}
//���, ��� ���� ���� ��� ������� ���� �����������, �� ������ ����� ����������������

void bankRequest() {
    SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
    ConsoleCursorVisible(false, 100);
    system("cls");
    GoToXY(15, 1);
    cout << "___";
    this_thread::sleep_for(std::chrono::milliseconds(200));

    SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
    system("cls");
    GoToXY(18, 1);
    cout << "___";
    this_thread::sleep_for(std::chrono::milliseconds(200));

    SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
    system("cls");
    GoToXY(21, 1);
    cout << "___";
    this_thread::sleep_for(std::chrono::milliseconds(200));

    SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
    system("cls");
    GoToXY(24, 1);
    cout << "___";
    this_thread::sleep_for(std::chrono::milliseconds(200));

    SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
    system("cls");
    GoToXY(27, 1);
    cout << "___";
    this_thread::sleep_for(std::chrono::milliseconds(200));

    SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
    GoToXY(30, 1);
    cout << "___";
    this_thread::sleep_for(std::chrono::milliseconds(200));

    SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
    system("cls");
    GoToXY(33, 2);
    cout << "|";
    GoToXY(33, 3);
    cout << "|";
    GoToXY(33, 4);
    cout << "|";
    this_thread::sleep_for(std::chrono::milliseconds(200));

    SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
    system("cls");
    GoToXY(33, 5);
    cout << "|";
    GoToXY(33, 6);
    cout << "|";
    GoToXY(33, 7);
    cout << "|";
    this_thread::sleep_for(std::chrono::milliseconds(200));

    SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
    system("cls");
    GoToXY(33, 8);
    cout << "|";
    GoToXY(33, 9);
    cout << "|";
    GoToXY(33, 10);
    cout << "|";
    this_thread::sleep_for(std::chrono::milliseconds(200));

    SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
    GoToXY(30, 11);
    cout << "___";
    this_thread::sleep_for(std::chrono::milliseconds(200));

    SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
    system("cls");
    GoToXY(27, 11);
    cout << "___";
    this_thread::sleep_for(std::chrono::milliseconds(200));

    SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
    system("cls");
    GoToXY(24, 11);
    cout << "___";
    this_thread::sleep_for(std::chrono::milliseconds(200));

    SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
    system("cls");
    GoToXY(21, 11);
    cout << "___";
    this_thread::sleep_for(std::chrono::milliseconds(200));

    SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
    system("cls");
    GoToXY(18, 11);
    cout << "___";
    this_thread::sleep_for(std::chrono::milliseconds(200));

    SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
    GoToXY(15, 11);
    cout << "___";
    this_thread::sleep_for(std::chrono::milliseconds(200));

    SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
    system("cls");
    GoToXY(15, 10);
    cout << "|";
    GoToXY(15, 9);
    cout << "|";
    GoToXY(15, 8);
    cout << "|";
    this_thread::sleep_for(std::chrono::milliseconds(200));

    SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
    system("cls");
    GoToXY(15, 7);
    cout << "|";
    GoToXY(15, 6);
    cout << "|";
    GoToXY(15, 5);
    cout << "|";
    this_thread::sleep_for(std::chrono::milliseconds(200));

    SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
    system("cls");
    GoToXY(15, 4);
    cout << "|";
    GoToXY(15, 3);
    cout << "|";
    GoToXY(15, 2);
    cout << "|";
    this_thread::sleep_for(std::chrono::milliseconds(200));

    SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
    system("cls");
    GoToXY(14, 7);
    cout << "���� ������� ��������";
    this_thread::sleep_for(std::chrono::milliseconds(1200));
    system("cls");
}

void BigText(int x, int y, int x1, string text) {
    int xx = x;
    for (int i = 0; i < text.length(); i++) {
        if (xx == x1) {
            xx = x;
            y++;
        }
        GoToXY(xx, y);
        xx++;
        cout << text[i];
    }
}
// ������� ��� ����� ������������ � �������
void SignInUs(bool isUser) {
    // ����������� ������� � ������� � ��� ���������
    ConsoleCursorVisible(true, 100);
  
    vector<User> users  = writingUsers();
    vector<Dev> devs = writingDevs();
    //cout << devs[0].getLogin() << endl << devs[0].getPass() << endl << devs[0].getBalance() << endl << devs[0].getCardNum();
    // ���������� ��� �������� ������ � ������ ������������
    string signInLogin;
    string signInPass;

    // ���������� ��� ����������� ������ � �������
    int x = 15, y = 5;
    GoToXY(x, y);
    SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
    cout << "������� ����� � ������";
    GoToXY(x, ++y);

    // ���� ������ ������������
    std::cout << "login: ";
    SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
    std::getline(std::cin, signInLogin);

    // ���� ������ ������������
    GoToXY(x, ++y);
    SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
    std::cout << "pass: ";
    char ch;
    while ((ch = _getch()) != '\r') {
        SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);// ������ ��������, ���� �� ����� ������ Enter
        if (ch == '\b') { // ���� ������ ������� Backspace
            if (!signInPass.empty()) {
                signInPass.pop_back(); // ������� ��������� ������
                cout << "\b \b"; // ������� ������ � ����� ������ Backspace ��� �������� ���������
            }
        }
        else {
            signInPass.push_back(ch); // ��������� ������ � ������
            cout << '*'; // ������� ��������� ������ �������
        }
    }
    cout << endl;

    if (isUser) {
        // �������� ������ � ������ ��� ������� ������������ � ������
        for (int i = 0; i < users.size(); i++) {
            if (users[i].getLogin() == signInLogin) {
                // ���� ����� ������, ��������� ������
                if (users[i].getPass() == signInPass) {
                    // ���� ������ ������, ������� ��������� �� �������� �����
                    UsCabinet(users[i]);
                }
                else {
                    // ���� ������ ��������, ������� ��������� �� ������ � ��������� ����
                    GoToXY(x, ++y);
                    SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
                    cout << "����� ������������ ������ ��� �����";
                    this_thread::sleep_for(std::chrono::milliseconds(1200));
                    system("cls");
                    SignInUs(isUser);
                }
                // ����� �� ������� ����� ��������� ����� ��� ����� ���������� ����� ������
                return;
            }
        }
    }
    else {
        // �������� ������ � ������ ��� ������� ������������ � ������
        for (int i = 0; i < devs.size(); i++) {
            if (devs[i].getLogin() == signInLogin) {
                // ���� ����� ������, ��������� ������
                if (devs[i].getPass() == signInPass) {
                    // ���� ������ ������, ������� ��������� �� �������� �����
                    DevCabinet(devs[i]);
                }
                else {
                    // ���� ������ ��������, ������� ��������� �� ������ � ��������� ����
                    GoToXY(x, ++y);
                    SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
                    cout << "����� ������������ ������ ��� �����";
                    this_thread::sleep_for(std::chrono::milliseconds(1200));
                    system("cls");
                    SignInUs(isUser);
                }
                // ����� �� ������� ����� ��������� ����� ��� ����� ���������� ����� ������
                return;
            }
        }
    }
    
    

    // ���� ����� �� ������, ������� ��������� �� ������ � ��������� ����
    GoToXY(x, ++y);
    SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
    cout << "������ ������������ ������ ��� �����\n";
    this_thread::sleep_for(std::chrono::milliseconds(1200));
    system("cls");
    SignInUs(isUser);
    // ����� �� ������� ����� ���������� ����� ������
    return;
}

// ������� ��� ����������� ���� ������ ����������� ��� �����������
void SignInUp(bool isUser) {
    // ������ ������� ���� ��� ������ ��������
    string Menu[] = { "�����", "������������������", "�����", "�����" };
    // ���������� ��� ������������ ��������� ������ ����
    int active_menu = 0;

    // ���� ��� ���������� ������
    bool T = true;
    // ���������� ��� ���������� ������� ������
    char ch;
    // ����������� ���� ��� ����������� ���� � ��������� ����� ������������
    while (T) {
        int x = 15, y = 5;
        GoToXY(x, y);
        // ���� ��� ����������� ������� ����
        for (int i = 0; i < size(Menu); i++) {
            // ��������� ����� ������ � ����������� �� ��������� ������ ����
            if (i == active_menu) {
                SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
            }
            else {
                SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
            }
            GoToXY(x, y++);
            cout << Menu[i] << endl;
        }
        // ���������� ������� �������
        ch = _getch();
        // ��������� ������� ������� ��� ����������� �� ����
        if (ch == -32) ch = _getch();
        switch (ch) {
        case 27: // ESC - ����� �� ���������
            exit(0);
        case 72: // UP - ����������� ����� �� ����
            if (active_menu == 0) {
                active_menu = size(Menu) - 1;
            }
            else if (active_menu > 0) {
                --active_menu;
            }
            break;
        case 80: // DOWN - ����������� ���� �� ����
            if (active_menu == size(Menu) - 1) {
                active_menu = 0;
            }
            else if (active_menu < size(Menu) - 1) {
                ++active_menu;
            }
            break;
        case 13: // ENTER - ����� ������ ����
            switch (active_menu) {
            case 0: // ���� � �������
                system("cls");
                SignInUs(isUser);
                return;
            case 1: // ����������� ������ ������������
                system("cls");
                if (isUser)
                    SignUpUs();
                else
                    SignUpDev();
                return;
            case 2: // ������� � ���������� ����
                system("cls");
                firstWin();
                return;
            case 3: // ����� �� ���������
                exit(0);
                break;
            }
            break;
        case 32: // SPACE - ������ �� ������, ��� ��� ���� �� ������ ����������� �� ������
            break;
        }
    }
}

// ������� ��� ��������� ������
bool validatePassword(const std::string& password) {
    // �������� ����� ������
    if (password.length() < 8) {
        // ����������� ������� � ������� � ����� ��������� �� ������
        GoToXY(15, 8);
        SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
        std::cout << "������ ������ ��������� �� ����� 8 ��������.";
        // ������� ������� � �������� ����� �������� ������
        ConsoleCursorVisible(false, 100);
        this_thread::sleep_for(std::chrono::milliseconds(1200));
        return false;
    }

    // ����� ��� �������� ������� �������� ����, ��������� ����, ���� � ��������
    bool hasLowercase = false;
    bool hasUppercase = false;
    bool hasDigit = false;
    bool hasSpace = false;

    // �������� ������� ������� � ������
    for (char c : password) {
        if (std::isspace(c)) {
            hasSpace = true;
        }
        else if (std::islower(c)) {
            hasLowercase = true;
        }
        else if (std::isupper(c)) {
            hasUppercase = true;
        }
        else if (std::isdigit(c)) {
            hasDigit = true;
        }
        else if (!isascii(c)) {
            // �������� �� ������������� �������
            GoToXY(15, 8);
            SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
            std::cout << "������ �� ������ ��������� ������������� ��������.";
            ConsoleCursorVisible(false, 100);
            this_thread::sleep_for(std::chrono::milliseconds(1200));
            system("cls");
            return false;
        }
    }

    // �������� ������� ��������
    if (hasSpace) {
        GoToXY(15, 8);
        SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
        std::cout << "������ �� ������ ��������� ��������.";
        ConsoleCursorVisible(false, 100);
        this_thread::sleep_for(std::chrono::milliseconds(1200));
        system("cls");
        return false;
    }

    // �������� ������� �������� ����
    if (!hasLowercase) {
        GoToXY(15, 8);
        SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
        std::cout << "������ ������ ��������� ���� �� ���� �������� �����.";
        ConsoleCursorVisible(false, 100);
        this_thread::sleep_for(std::chrono::milliseconds(1200));
        system("cls");
        return false;
    }

    // �������� ������� ��������� ����
    if (!hasUppercase) {
        GoToXY(15, 8);
        SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
        std::cout << "������ ������ ��������� ���� �� ���� ��������� �����.";
        ConsoleCursorVisible(false, 100);
        this_thread::sleep_for(std::chrono::milliseconds(1200));
        system("cls");
        return false;
    }

    // �������� ������� ����
    if (!hasDigit) {
        GoToXY(15, 8);
        SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
        std::cout << "������ ������ ��������� ���� �� ���� �����.";
        ConsoleCursorVisible(false, 100);
        this_thread::sleep_for(std::chrono::milliseconds(1200));
        system("cls");
        return false;
    }

    // ���� ��� �������� �������� �������, ���������� true
    return true;
}

// ������� ��� ��������� ������
bool validateLogin(const std::string& login) {
    // �������� ����� ������
    if (login.length() < 6) {
        // ����������� ������� � ������� � ����� ��������� �� ������
        GoToXY(15, 7);
        SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
        std::cout << "����� ������ ������ ���� �� ����� 6 ��������.\n";
        // ������� ������� � �������� ����� �������� ������
        ConsoleCursorVisible(false, 100);
        this_thread::sleep_for(std::chrono::milliseconds(1200));
        system("cls");
        return false;
    }

    // ���� ��� �������� ������� ����� � ������
    bool hasLetter = false;
    for (char c : login) {
        // �������� �� ��������� ������
        if (isalpha(static_cast<unsigned char>(c))) {
            hasLetter = true;
        }
        // �������� �� ������������� �������
        if (!isascii(c)) {
            GoToXY(15, 7);
            SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
            std::cout << "����� �� ������ ��������� ������������� �������.\n";
            ConsoleCursorVisible(false, 100);
            this_thread::sleep_for(std::chrono::milliseconds(1200));
            system("cls");
            return false;
        }
    }
    // �������� ������� ����� � ������
    if (!hasLetter) {
        GoToXY(15, 7);
        SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
        std::cout << "����� ������ ��������� ���� �� ���� �����.\n";
        ConsoleCursorVisible(false, 100);
        this_thread::sleep_for(std::chrono::milliseconds(1200));
        system("cls");
        return false;
    }

    // �������� �� ���������� �������� � ������
    for (char c : login) {
        // �������� �� ���������� ������
        if (isspace(static_cast<unsigned char>(c))) {
            GoToXY(15, 7);
            SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
            std::cout << "����� �� ������ ��������� �������.\n";
            ConsoleCursorVisible(false, 100);
            this_thread::sleep_for(std::chrono::milliseconds(1200));
            system("cls");
            return false;
        }
    }
    // ���� ��� �������� �������� �������, ���������� true
    return true;
}

bool validateCardNumber(const std::string& cardNumber) {
    // �������� �� ����� ������ �����
    if (cardNumber.length() != 16) {
        return false;
    }

    // �������� �� ��, ��� ��� ������� - �����
    for (char ch : cardNumber) {
        if (!isdigit(ch)) {
            return false;
        }
    }

    // ���� ����� ����� ������ ��� ��������, ���������� true
    return true;
}

bool validateGameName(const std::string& name) {
    if (name.length() <= 5) {
        return false;
    }

    // ���������� ��������� ��� ������ ���� (������� ��� ����������)
    std::regex letterRegex("[�-��-�a-zA-Z]");
    return std::regex_search(name, letterRegex);
}

// ������� ��� ����������� ������ ������������
void SignUpUs() {
    vector<User> users = writingUsers();
    // ����������� ������� � ������� � ��� ���������
    ConsoleCursorVisible(true, 100);

    // ���������� ��� �������� ������, ������ � ���������� ����� ������
    string signUpLogin;
    string signUpPass;
    string signUpRepitPass;

    // ���������� ��� ����������� ������ � �������
    int x = 15, y = 5;
    GoToXY(x, y);
    SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
    cout << "������� ������ ��� �����������";
    GoToXY(x, ++y);

    // ���� ������ ������������
    cout << "login: ";
    SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
    getline(cin, signUpLogin);

    // ��������� ������
    if (!validateLogin(signUpLogin)) {
        // ���� ����� �� ������ ���������, ����������� ����� �����
        SignUpUs();
        return;
    }
    User currentUser;
    // �������� ������� ������ � ���� �������������
    for (auto& user : users) {
        if (signUpLogin == user.getLogin()) {
            // ���� ����� ��� �����, ������� ��������� � ����������� ����� �����
            GoToXY(x, ++y);
            SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
            std::cout << "����� ����� ��� �����";
            ConsoleCursorVisible(false, 100);
            this_thread::sleep_for(std::chrono::milliseconds(1200));
            system("cls");
            SignUpUs();
            return;
        }
    }

    GoToXY(x, ++y);

    // ���� ������ ������������
    SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
    cout << "pass: ";
    char ch;
    while (true) {
        SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);// ����������� ���� ��� ����� ������
        signUpPass.clear(); // ������� ���������� ��� ������
        while ((ch = _getch()) != '\r') { // ������ ��������, ���� �� ����� ������ Enter
            if (ch == '\b') { // ���� ������ ������� Backspace
                if (!signUpPass.empty()) {
                    signUpPass.pop_back(); // ������� ��������� ������
                    cout << "\b \b"; // ������� ������ � ����� ������ Backspace ��� �������� ���������
                }
            }
            else {
                signUpPass.push_back(ch); // ��������� ������ � ������
                cout << '*'; // ������� ��������� ������ �������
            }
        }
        cout << endl;

        // ��������� ������
        if (validatePassword(signUpPass)) {
            break; // ���� ������ ������ ���������, ������� �� �����
        }
        else {
            reppas:
            // ���� ������ �� ������ ���������, ������� ��������� � ������ ������ ������
            system("cls");
            x = 15, y = 5;
            GoToXY(x, y);
            SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
            cout << "������� ������ ��� �����������";
            GoToXY(x, ++y);

            // ���� ������ ������������
            cout << "login: "; 
            SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
            cout << signUpLogin;
            GoToXY(x, ++y);

            // ���� ������ ������������
            SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
            cout << "pass: ";
        }
    }

    // ���� ���������� ������ ������������
    GoToXY(x, ++y);
    SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
    std::cout << "repit pass: ";
    signUpRepitPass.clear(); // ������� ���������� ��� ���������� ����� ������
    while ((ch = _getch()) != '\r') {
        SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);// ������ ��������, ���� �� ����� ������ Enter
        if (ch == '\b') { // ���� ������ ������� Backspace
            if (!signUpRepitPass.empty()) {
                signUpRepitPass.pop_back(); // ������� ��������� ������
                cout << "\b \b"; // ������� ������ � ����� ������ Backspace ��� �������� ���������
            }
        }
        else {
            signUpRepitPass.push_back(ch); // ��������� ������ � ������
            cout << '*'; // ������� ��������� ������ �������
        }
    }
    cout << endl;

    // �������� ������������ �������
    if (signUpPass != signUpRepitPass) {
        // ���� ������ �� ���������, ������� ��������� � ����������� ����� ������
        GoToXY(x, ++y);
        SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
        std::cout << "������ ����������� ��������\n";
        ConsoleCursorVisible(false, 100);
        this_thread::sleep_for(std::chrono::milliseconds(1200));
        goto reppas;
    }
    users.push_back(User(signUpLogin, signUpPass, 0, users.size()));
    // �������� ������ ��� ������ ������ ������������
    std::ofstream ofUsLogin;
    std::ofstream ofUsPass;
    std::ofstream ofUsBalance;
    ofUsLogin.open("Data/userNames.txt", std::ofstream::app);
    ofUsBalance.open("Data/userBalances.txt", std::ofstream::app);
    ofUsPass.open("Data/passOfUsers.txt", std::ofstream::app);

    // ������ ������ ������������ � �����
    ofUsLogin << std::endl << signUpLogin;
    ofUsBalance << std::endl << 0;
    ofUsPass << std::endl << signUpPass;

    // �������� ������ ����� ������ ������
    ofUsLogin.close();
    ofUsBalance.close();
    ofUsPass.close();

    // ����� ��������� �� �������� �����������
    UsCabinet(users[users.size()-1]);

    
}

void SignUpDev() {
    vector<Dev> devs = writingDevs();

    ConsoleCursorVisible(true, 100);

    // ���������� ��� �������� ������, ������ � ���������� ����� ������
    string signUpLogin;
    string signUpPass;
    string signUpRepitPass;
    string signDevCardNum;

    // ���������� ��� ����������� ������ � �������
    int x = 15, y = 5;
    GoToXY(x, y);
    SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
    cout << "������� ������ ��� �����������";
    GoToXY(x, ++y);

    // ���� ������ ������������
    cout << "login: ";
    SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
    getline(cin, signUpLogin);

    // ��������� ������
    if (!validateLogin(signUpLogin)) {
        // ���� ����� �� ������ ���������, ����������� ����� �����
        SignUpDev();
        return;
    }

    // �������� ������� ������ � ���� �������������
    for (auto& dev : devs) {
        if (signUpLogin == dev.getLogin()) {
            // ���� ����� ��� �����, ������� ��������� � ����������� ����� �����
            GoToXY(x, ++y);
            SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
            std::cout << "����� ����� ��� �����";
            ConsoleCursorVisible(false, 100);
            this_thread::sleep_for(std::chrono::milliseconds(1200));
            system("cls");
            SignUpDev();
            return;
        }
    }

    GoToXY(x, ++y);
    SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
    cout << "CardNum: ";
    while (true) {
        SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
        getline(cin, signDevCardNum);
        if (!validateCardNumber(signDevCardNum)) {
            // ���� ����� ����� �� ������ ���������, ������� ��������� � ����������� ����� �����
            GoToXY(x, ++y);
            SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
            std::cout << "������������ ����� �����";
            ConsoleCursorVisible(false, 100);
            this_thread::sleep_for(std::chrono::milliseconds(1200));
            system("cls");
            x = 15, y = 5;
            GoToXY(x, y);
            cout << "������� ������ ��� �����������";
            GoToXY(x, ++y);

            // ���� ������ ������������
            SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
            cout << "login: ";
            SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
            cout << signUpLogin;
            GoToXY(x, ++y);

            // ���� ������ ������������
            SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
            cout << "CardNum: ";
        }
        else break;
    }

    GoToXY(x, ++y);
    // ���� ������ ������������
    SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
    cout << "pass: ";
    
    char ch;
    while (true) { // ����������� ���� ��� ����� ������
        SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
        signUpPass.clear(); // ������� ���������� ��� ������
        while ((ch = _getch()) != '\r') { // ������ ��������, ���� �� ����� ������ Enter
            if (ch == '\b') { // ���� ������ ������� Backspace
                if (!signUpPass.empty()) {
                    signUpPass.pop_back(); // ������� ��������� ������
                    cout << "\b \b"; // ������� ������ � ����� ������ Backspace ��� �������� ���������
                }
            }
            else {
                signUpPass.push_back(ch); // ��������� ������ � ������
                cout << '*'; // ������� ��������� ������ �������
            }
        }
        cout << endl;

        // ��������� ������
        if (validatePassword(signUpPass)) {
            break; // ���� ������ ������ ���������, ������� �� �����
        }
        else {
        reppasdev:
            // ���� ������ �� ������ ���������, ������� ��������� � ������ ������ ������
            system("cls");
            x = 15, y = 5;
            GoToXY(x, y);
            SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
            cout << "������� ������ ��� �����������";
            GoToXY(x, ++y);

            // ���� ������ ������������
            SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
            cout << "login: ";
            SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
            cout << signUpLogin;
            GoToXY(x, ++y);

            //����� ������ �����
            SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
            cout << "CardNum: ";
            SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
            cout << signDevCardNum;
            GoToXY(x, ++y);

            // ���� ������ ������������
            SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
            cout << "pass: ";
        }
    }

    // ���� ���������� ������ ������������
    GoToXY(x, ++y);
    SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
    std::cout << "repit pass: ";
    SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
    signUpRepitPass.clear(); // ������� ���������� ��� ���������� ����� ������
    while ((ch = _getch()) != '\r') { // ������ ��������, ���� �� ����� ������ Enter
        if (ch == '\b') { // ���� ������ ������� Backspace
            if (!signUpRepitPass.empty()) {
                signUpRepitPass.pop_back(); // ������� ��������� ������
                cout << "\b \b"; // ������� ������ � ����� ������ Backspace ��� �������� ���������
            }
        }
        else {
            signUpRepitPass.push_back(ch); // ��������� ������ � ������
            cout << '*'; // ������� ��������� ������ �������
        }
    }
    cout << endl;

    // �������� ������������ �������
    if (signUpPass != signUpRepitPass) {
        // ���� ������ �� ���������, ������� ��������� � ����������� ����� ������
        GoToXY(x, ++y);
        SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
        std::cout << "������ ����������� ��������\n";
        ConsoleCursorVisible(false, 100);
        this_thread::sleep_for(std::chrono::milliseconds(1200));
        goto reppasdev;
        return;
    }
    
    
    // �������� ������ ��� ������ ������ ������������
    std::ofstream ofDevLogin;
    std::ofstream ofDevPass;
    std::ofstream ofDevBalance;
    std::ofstream ofDevCardNum;
    ofDevLogin.open("Data/devNames.txt", std::ofstream::app);
    ofDevBalance.open("Data/devBalances.txt", std::ofstream::app);
    ofDevPass.open("Data/passOfDevs.txt", std::ofstream::app);
    ofDevCardNum.open("Data/devCardNum.txt", std::ofstream::app);

    // ������ ������ ������������ � �����
    ofDevLogin << std::endl << signUpLogin;
    ofDevBalance << std::endl << "0";
    ofDevPass << std::endl << signUpPass;
    ofDevCardNum << std::endl << signDevCardNum;

    // ����� ��������� �� �������� �����������
    devs.push_back(Dev(signUpLogin, signUpPass, 0, signDevCardNum, devs.size()));

    // �������� ������ ����� ������ ������
    ofDevLogin.close();
    ofDevBalance.close();
    ofDevPass.close();
    ofDevCardNum.close();

    ofstream ofDevGames;
    ofstream ofGamesAbout;
    ofstream ofGamesPrice;

    ofDevGames.open("Data/DevGames/" + signUpLogin + "Games.txt");
    ofGamesAbout.open("Data/DevGames/About/" + signUpLogin + "About.txt");
    ofGamesPrice.open("Data/DevGames/Price/" + signUpLogin + "Price.txt");

    ofDevGames.close();
    ofGamesAbout.close();
    ofGamesPrice.close();

    DevCabinet(devs[devs.size() - 1]);
}

void topUp(User currentUser) {
    system("cls");
    int x = 10, y = 5;
    GoToXY(x, y);

    string addBalance;
    string cardNum;
    SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
    cout << "������� �����, ������� ������ ��������";
    GoToXY(x, ++y);
    SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
    getline(cin, addBalance);
    GoToXY(x, ++y);

    SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
    cout << "CardNum: ";
    while (true) {
        SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
        getline(cin, cardNum);
        SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
        if (!validateCardNumber(cardNum)) {
            // ���� ����� ����� �� ������ ���������, ������� ��������� � ����������� ����� �����
            GoToXY(x, ++y);
            std::cout << "������������ ����� �����";
            ConsoleCursorVisible(false, 100);
            this_thread::sleep_for(std::chrono::milliseconds(1200));
            system("cls");
            x = 10, y = 5;
            GoToXY(x, y);
            cout << "������� �����, ������� ������ ��������";
            GoToXY(x, ++y);
            SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
            cout << addBalance;
            // ���� ������ ������������
            GoToXY(x, ++y);
            SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
            cout << "CardNum: ";
        }
        else break;
    }
    
    float faddBalance = stof(addBalance);
    currentUser.setBalance(currentUser.getBalance() + faddBalance);
    vector<User> users = writingUsers();
    users[currentUser.getIndex()].setBalance(currentUser.getBalance());
    ofstream ofUsBalance;
    ofUsBalance.open("Data/userBalances.txt");
    ofUsBalance << users[0].getBalance();
    for (int i = 1; i < users.size(); i++) {
        ofUsBalance << endl << users[i].getBalance();
    }
    ofUsBalance.close();
    bankRequest();

    UsCabinet(currentUser);
    return;
}

void writeOff(Dev currenDev) {
    vector<Dev> devs = writingDevs();
    currenDev.setBalance(0);
    devs[currenDev.getIndex()].setBalance(currenDev.getBalance());
    
    ofstream ofDevBalance;
    ofDevBalance.open("Data/devBalances.txt");
    ofDevBalance << devs[0].getBalance();
    for (int i = 1; i < devs.size(); i++) {
        ofDevBalance << endl << devs[i].getBalance();
    }

    ofDevBalance.close();
    DevCabinet(currenDev);
    return;
}

void UsCabinet(User currentUser) {
    ConsoleCursorVisible(false, 100);
    system("cls");
    system("mode con cols=49 lines=15");
    /*int x = 10, y = 5;
    GoToXY(x, y);
    cout << "��� ������:";
    GoToXY(x, ++y);
    cout << currentUser.getBalance();
    GoToXY(x, ++y);
    cout << "���� ���:";
    GoToXY(x, ++y);
    cout << currentUser.getLogin();*/
    

    string Menu[] = { "��������� ������", "������ ���� ���", "����� ���", "����� �� 1-�� ����", "�����"};
    int active_menu = 0;

    // ���������� ��� ������ ������� ������
    char ch;

    while (true) {
        SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
        int x = 3, y = 1;
        GoToXY(3, 1);
        cout << "���� ���: " << currentUser.getLogin();
        GoToXY(30, 1);
        cout << "��� ������: " << currentUser.getBalance();
        x = 15, y = 5;
        GoToXY(x, y);
        // ���� ��� ����������� ������� ����
        for (int i = 0; i < size(Menu); i++) {
            // ��������� ����� ������ � ����������� �� ��������� ������ ����
            if (i == active_menu) {
                SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
            }
            else {
                SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
            }
            GoToXY(x, y++);
            cout << Menu[i] << endl;
        }
        // ���������� ������� �������
        ch = _getch();
        // ��������� ������� ������� ��� ����������� �� ����
        if (ch == -32) ch = _getch();
        switch (ch) {
        case 27: // ESC - ����� �� ���������
            exit(0);
        case 72: // UP - ����������� ����� �� ����
            if (active_menu == 0) {
                active_menu = size(Menu) - 1;
            }
            else if (active_menu > 0) {
                --active_menu;
            }
            break;
        case 80: // DOWN - ����������� ���� �� ����
            if (active_menu == size(Menu) - 1) {
                active_menu = 0;
            }
            else if (active_menu < size(Menu) - 1) {
                ++active_menu;
            }
            break;
        case 13: // ENTER - ����� ������ ����
            switch (active_menu) {
            case 0:
                topUp(currentUser);
                return;
                //balance
            case 1: // ���� ��� ������������
                system("cls");
                return;
            case 2: // ���� ��� ����������� (�� �����������)
                system("cls");
                GamesList(writngAllGames());
                break;
            case 3: // ����� �� ���������
                system("cls");
                firstWin();
                return;
            case 4:
                exit(0);
                return;
            }
            break;
        case 32: // SPACE - ����� ���������� � ������������ � ����� �� ����
            system("cls");
 
            _getch();
            system("cls");
            cout << " �� � �������� �������: ��������� ������ ���� � �����, � ���������� ���: '���, ��� ���� ������?'";
            return;
        }
    }
    _getch();
}

void PageList(Game game) {
    SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
    system("cls");
    GoToXY(5, 1);
    cout << game.getName();
    GoToXY(40, 1);
    cout << game.getPrice();
    BigText(2, 3, 48, game.getAbout());
    /*GoToXY(5, 2);
    cout << game.getAbout();*/
    while (true) {
        char ch = _getch();
        if (ch == 27) {
            system("cls");
            return;
        }
    }
}

void FindGame(vector<Game> games) {
    vector<Game> filtergames;

    cout << "������� �������� ����";
    string name;
    getline(cin, name);

    for (int i = 0; i < games.size(); i++) {
        size_t found = games[i].getName().find(name);
        if (found != std::string::npos) filtergames.push_back(games[i]);
    }

    system("cls");
    GamesList(filtergames);
    return;
}

void GamesList(vector<Game> games) {
    
    int x = 5, x1 = 40, y = 1;

    int active_menu = 0;

    // ���������� ��� ������ ������� ������
    char ch;
    int minShowGame = 0, maxShomGame = 10;
    if (maxShomGame > games.size()) maxShomGame = games.size();
    while (true) {
        GoToXY(10, 12);
        SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
        cout << "<- ��. ���.          ��. ���. -> ";
        GoToXY(10, 13);
        cout << "�����(Ecs)        ����� ���(Space)";
        bool isCanNext = true, isCanPrev = true;
        int x = 5, x1 = 42, y = 1;
        GoToXY(x, y);
        // ���� ��� ����������� ������� ����
        for (int i = minShowGame; i < maxShomGame; i++) {
            // ��������� ����� ������ � ����������� �� ��������� ������ ����
            if (i == active_menu) {
                SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
            }
            else {
                SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
            }
            GoToXY(x, y++);
            cout << games[i].getName() << endl;
            y--;
            GoToXY(x1, y++);
            cout << games[i].getPrice();
        }
        // ���������� ������� �������
        ch = _getch();
        // ��������� ������� ������� ��� ����������� �� ����
        if (ch == -32) ch = _getch();
        switch (ch) {
        case 27: // ESC - ����� �� ���������
            system("cls");
            return;
        case 72: // UP - ����������� ����� �� ����
            
            if (active_menu > 0) {
                --active_menu;
                if (active_menu < minShowGame) {
                    system("cls");
                    maxShomGame = active_menu + 1;
                    if (minShowGame - 10 < 0) {
                        minShowGame = 0;
                    }
                    else minShowGame -= 10;

                }
            }
            break;
        case 80: // DOWN - ����������� ���� �� ����
            
            if (active_menu < games.size() - 1) {
                ++active_menu;
                if (active_menu > maxShomGame - 1) {
                    system("cls");
                    minShowGame = active_menu;
                    if (maxShomGame + 10 > games.size())
                        maxShomGame = games.size();
                    else maxShomGame += 10;
                }
            }
            break;
        case 77:
            system("cls");
            if (maxShomGame + 10 > games.size()) {
                if (minShowGame + 10 < games.size()) {
                    minShowGame += 10;
                    if (active_menu + 10 > games.size()) active_menu += games.size() - 1;
                    else active_menu += 10;
                }
               
                maxShomGame = games.size();
            }
            else {
                active_menu += 10;
                minShowGame += 10;
                maxShomGame += 10;
            }
            break;
        case 75:
            system("cls");
            if (minShowGame - 10 < 0) {
                minShowGame = 0;
                if (maxShomGame - 10 < 0) {
                    maxShomGame = 10;
                }
                if (maxShomGame > games.size()) maxShomGame = games.size();
            }
            else {
                active_menu -= 10;
                maxShomGame = minShowGame;
                minShowGame -= 10;
            }
            break;
        case 13: // ENTER - ����� ������ ����
            PageList(games[active_menu]);
            //return;
            break;
        case 70: // SPACE - ����� ���������� � ������������ � ����� �� ����
            system("cls");
            _getch();
            system("cls");
            cout << " �� � �������� �������: ��������� ������ ���� � �����, � ���������� ���: '���, ��� ���� ������?'";
            return;
        case 32:
            system("cls");
            FindGame(games);
            break;
        }
    }



    /*for (int i = 0; i < games.size(); i++) {
        y += 1;
        GoToXY(x, y);
        cout << games[i].getName();
        GoToXY(x1, y);
        cout << games[i].getPrice();
    }*/
    _getch();
}

void addGame(string DevName) {
    system("cls");
    vector<Game> allGames = writngAllGames();
    int x = 10, y = 2;

    string name;
    string about;
    string price;

    GoToXY(x, y);
    cout << "�������� ����: ";
    getline(cin, name);

    if (!validateGameName(name)) {
        GoToXY(x, ++y);
        cout << "�������� ���� ������ ���� ������� 5 �������� � ��������� ���� �� 1 �����." << endl;
        this_thread::sleep_for(chrono::milliseconds(1200));
        addGame(DevName);
        return;
    }
    for (int i = 0; i < allGames.size(); i++) {
        if (name == allGames[i].getName()) {
            GoToXY(x, ++y);
            cout << "����� �������� ��� ������";
            this_thread::sleep_for(std::chrono::milliseconds(1200));
            addGame(DevName);
            return;
        }
    }
    

    GoToXY(x, ++y);
    cout << "���� ��� ����: ";
    getline(cin, price);

    GoToXY(x, ++y);
    cout << "�������� ����: ";
    GoToXY(3, ++y);
    getline(cin, about); //440 �������� ��������

    ofstream ofGameName;
    ofstream ofAboutGame;
    ofstream ofPriceGame;

    ofGameName.open("Data/DevGames/" + DevName + "Games.txt", ofstream::app);
    ofAboutGame.open("Data/DevGames/About/" + DevName + "About.txt", ofstream::app);
    ofPriceGame.open("Data/DevGames/Price/" + DevName + "Price.txt", ofstream::app);
    
    if (writingDevGames(DevName)[0].getName() == "") {
        ofGameName << name;
        ofAboutGame << about;
        ofPriceGame << price;
    }
    else {
        ofGameName << endl << name;
        ofAboutGame << endl << about;
        ofPriceGame << endl << price;
    }
    

    ofGameName.close();
    ofAboutGame.close();
    ofPriceGame.close();
    
    system("cls");
    return;
}

void DevCabinet(Dev currentDev) {
    ConsoleCursorVisible(false, 100);
    system("cls");

    string Menu[] = { "������� ������ �� �����", "������ ���� ���", "�������� ����", "����� �� 1-�� ����", "�����" };
    int active_menu = 0;

    // ���������� ��� ������ ������� ������
    char ch;

    while (true) {
        SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
        GoToXY(3, 1);
        cout << "���� �����: " << currentDev.getLogin();
        GoToXY(30, 1);
        cout << "��� ������: " << currentDev.getBalance();
        int x = 15, y = 5;
        GoToXY(x, y);
        // ���� ��� ����������� ������� ����
        for (int i = 0; i < size(Menu); i++) {
            // ��������� ����� ������ � ����������� �� ��������� ������ ����
            if (i == active_menu) {
                SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
            }
            else {
                SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
            }
            GoToXY(x, y++);
            cout << Menu[i] << endl;
        }
        // ���������� ������� �������
        ch = _getch();
        // ��������� ������� ������� ��� ����������� �� ����
        if (ch == -32) ch = _getch();
        switch (ch) {
        case 27: // ESC - ����� �� ���������
            exit(0);
        case 72: // UP - ����������� ����� �� ����
            if (active_menu == 0) {
                active_menu = size(Menu) - 1;
            }
            else if (active_menu > 0) {
                --active_menu;
            }
            break;
        case 80: // DOWN - ����������� ���� �� ����
            if (active_menu == size(Menu) - 1) {
                active_menu = 0;
            }
            else if (active_menu < size(Menu) - 1) {
                ++active_menu;
            }
            break;
        case 13: // ENTER - ����� ������ ����
            switch (active_menu) {
            case 0:
                bankRequest();
                writeOff(currentDev);
                return;
                //balance
            case 1: // ���� ��� ������������
                system("cls");
                GamesList(writingDevGames(currentDev.getLogin()));
                break;
            case 2: // ���� ��� ����������� (�� �����������)
                //system("cls");
                addGame(currentDev.getLogin());
                break;
            case 3: // ����� �� ���������
                system("cls");
                firstWin();
                return;
            case 4:
                exit(0);
                return;
            }
            break;
        case 32: // SPACE - ����� ���������� � ������������ � ����� �� ����
            system("cls");
 
            _getch();
            system("cls");
            cout << " �� � �������� �������: ��������� ������ ���� � �����, � ���������� ���: '���, ��� ���� ������?'";
            return;
        }
    }
    _getch();
    return;
}


void AboutApp() {
    cout << "����� ����� -- ��� ������ �����\n������� ����� -- ��� ������ ����� �������� ����� ������������� � ������� ������� �����-����\n������� -- ���� �������� � ����������";
    _getch();
    system("cls");
}
// ������ ���� ���������
void firstWin() {
    // ������������� ������ ���� �������
    system("mode con cols=49 lines=15");
    //AboutApp();
    // ��������� ��������� ������� � �������
    ConsoleCursorVisible(false, 100);

    // ������ ������� ����
    string Menu[] = { "����� ���", "User", "Developer", "�����" };

    // ���������� ��� ������������ ��������� ������ ����
    int active_menu = 1;

    // ���������� ��� ������ ������� ������
    char ch;

    bool isUser;

    // ����������� ���� ��� ����������� ���� � ��������� ����� ������������
    GoToXY(15, 5);
    SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
    cout << Menu[0];
    while (true) {
        int x = 15, y = 6;
        GoToXY(x, y);
        // ���� ��� ����������� ������� ����
        for (int i = 1; i < size(Menu); i++) {
            // ��������� ����� ������ � ����������� �� ��������� ������ ����
            if (i == active_menu) {
                SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
            }
            else {
                SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
            }
            GoToXY(x, y++);
            cout << Menu[i] << endl;
        }
        // ���������� ������� �������
        ch = _getch();
        // ��������� ������� ������� ��� ����������� �� ����
        if (ch == -32) ch = _getch();
        switch (ch) {
        case 27: // ESC - ����� �� ���������
            exit(0);
        case 72: // UP - ����������� ����� �� ����
            if (active_menu == 1) {
                active_menu = size(Menu) - 1;
            }
            else if (active_menu > 1) {
                --active_menu;
            }
            break;
        case 80: // DOWN - ����������� ���� �� ����
            if (active_menu == size(Menu) - 1) {
                active_menu = 1;
            }
            else if (active_menu < size(Menu) - 1) {
                ++active_menu;
            }
            break;
        case 13: // ENTER - ����� ������ ����
            switch (active_menu) {
            case 1: // ���� ��� ������������
                system("cls");
                isUser = true;
                SignInUp(isUser);
                return;
            case 2: // ���� ��� ����������� (�� �����������)
                system("cls");
                isUser = false;
                SignInUp(isUser);
                return;
            case 3: // ����� �� ���������
                exit(0);
                break;
            }
            break;
        case 32: // SPACE - ����� ���������� � ������������ � ����� �� ����
            system("cls");
            cout << "����� �� ������� �����";
            _getch();
            system("cls");
            cout << " �� � �������� �������: ��������� ������ ���� � �����, � ���������� ���: '���, ��� ���� ������?'";
            return;
        }
    }
}