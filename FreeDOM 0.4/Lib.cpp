// ������������ �����
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <fstream>
#include "User.h" // ���������������� ������������ ���� � ������������ ������ User
#include "Lib.h" // ���������������� ����������� ���� � ������������ �������
#include <Windows.h> // ���������� ��� ������ � Windows API
#include "Dev.h"
#include <stdio.h>
#include <conio.h>
#include <chrono>
#include <thread>

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
        devs.push_back(Dev(login, pass, fbalance, cardNum));
    }

    // �������� ������ ����� ���������� ������
    ifDevLogin.close();
    ifDevPass.close();
    ifDevBalance.close();
    ifDevCardNum.close();

    // ������� ������� �������������
    return devs;
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
    cout << "������� ����� � ������";
    GoToXY(x, ++y);

    // ���� ������ ������������
    std::cout << "login: ";
    std::getline(std::cin, signInLogin);

    // ���� ������ ������������
    GoToXY(x, ++y);
    std::cout << "pass: ";
    char ch;
    while ((ch = _getch()) != '\r') { // ������ ��������, ���� �� ����� ������ Enter
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
                    GoToXY(x, ++y);
                    cout << "���� �������� �������";
                }
                else {
                    // ���� ������ ��������, ������� ��������� �� ������ � ��������� ����
                    GoToXY(x, ++y);
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
                SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            }
            else {
                SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
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
        std::cout << "������ �� ������ ��������� ��������.";
        ConsoleCursorVisible(false, 100);
        this_thread::sleep_for(std::chrono::milliseconds(1200));
        system("cls");
        return false;
    }

    // �������� ������� �������� ����
    if (!hasLowercase) {
        GoToXY(15, 8);
        std::cout << "������ ������ ��������� ���� �� ���� �������� �����.";
        ConsoleCursorVisible(false, 100);
        this_thread::sleep_for(std::chrono::milliseconds(1200));
        system("cls");
        return false;
    }

    // �������� ������� ��������� ����
    if (!hasUppercase) {
        GoToXY(15, 8);
        std::cout << "������ ������ ��������� ���� �� ���� ��������� �����.";
        ConsoleCursorVisible(false, 100);
        this_thread::sleep_for(std::chrono::milliseconds(1200));
        system("cls");
        return false;
    }

    // �������� ������� ����
    if (!hasDigit) {
        GoToXY(15, 8);
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
    cout << "������� ������ ��� �����������";
    GoToXY(x, ++y);

    // ���� ������ ������������
    cout << "login: ";
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
    cout << "pass: ";
    char ch;
    while (true) { // ����������� ���� ��� ����� ������
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
            cout << "������� ������ ��� �����������";
            GoToXY(x, ++y);

            // ���� ������ ������������
            cout << "login: " << signUpLogin;
            GoToXY(x, ++y);

            // ���� ������ ������������
            cout << "pass: ";
        }
    }

    // ���� ���������� ������ ������������
    GoToXY(x, ++y);
    std::cout << "repit pass: ";
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
    cout << "������� ������ ��� �����������";
    GoToXY(x, ++y);

    // ���� ������ ������������
    cout << "login: ";
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
            std::cout << "����� ����� ��� �����";
            ConsoleCursorVisible(false, 100);
            this_thread::sleep_for(std::chrono::milliseconds(1200));
            system("cls");
            SignUpDev();
            return;
        }
    }

    GoToXY(x, ++y);
    cout << "CardNum: ";
    while (true) {
        getline(cin, signDevCardNum);
        if (!validateCardNumber(signDevCardNum)) {
            // ���� ����� ����� �� ������ ���������, ������� ��������� � ����������� ����� �����
            GoToXY(x, ++y);
            std::cout << "������������ ����� �����";
            ConsoleCursorVisible(false, 100);
            this_thread::sleep_for(std::chrono::milliseconds(1200));
            system("cls");
            x = 15, y = 5;
            GoToXY(x, y);
            cout << "������� ������ ��� �����������";
            GoToXY(x, ++y);

            // ���� ������ ������������
            cout << "login: " << signUpLogin;
            GoToXY(x, ++y);

            // ���� ������ ������������
            cout << "CardNum: ";
        }
        else break;
    }

    GoToXY(x, ++y);
    // ���� ������ ������������
    cout << "pass: ";
    char ch;
    while (true) { // ����������� ���� ��� ����� ������
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
            cout << "������� ������ ��� �����������";
            GoToXY(x, ++y);

            // ���� ������ ������������
            cout << "login: " << signUpLogin;
            GoToXY(x, ++y);

            //����� ������ �����
            cout << "CardNum: " << signDevCardNum;
            GoToXY(x, ++y);

            // ���� ������ ������������
            cout << "pass: ";
        }
    }

    // ���� ���������� ������ ������������
    GoToXY(x, ++y);
    std::cout << "repit pass: ";
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
        std::cout << "������ ����������� ��������\n";
        ConsoleCursorVisible(false, 100);
        this_thread::sleep_for(std::chrono::milliseconds(1200));
        goto reppas;
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
    ofDevBalance << std::endl << 0;
    ofDevPass << std::endl << signUpPass;
    ofDevCardNum << std::endl << signDevCardNum;

    // ����� ��������� �� �������� �����������
    GoToXY(x, ++y);
    std::cout << "����������� ������� ���������������";

    // �������� ������ ����� ������ ������
    ofDevLogin.close();
    ofDevBalance.close();
    ofDevPass.close();
    ofDevCardNum.close();
}

void topUp(User currentUser) {
    system("cls");
    int x = 10, y = 5;
    GoToXY(x, y);

    string addBalance;
    string cardNum;
    cout << "������� �����, ������� ������ ��������";
    GoToXY(x, ++y);
    getline(cin, addBalance);
    GoToXY(x, ++y);

    cout << "CardNum: ";
    while (true) {
        getline(cin, cardNum);
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
            cout << addBalance;
            // ���� ������ ������������
            GoToXY(x, ++y);
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
    UsCabinet(currentUser);
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
    int x = 3, y = 1;
    GoToXY(3, 1);
    cout << "���� ���: " << currentUser.getLogin();
    GoToXY(30, 1);
    cout << "��� ������: " << currentUser.getBalance();

    string Menu[] = { "��������� ������", "������ ���� ���", "����� ���", "����� �� 1-�� ����", "�����"};
    int active_menu = 0;

    // ���������� ��� ������ ������� ������
    char ch;

    while (true) {
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
                topUp(currentUser);
                return;
                //balance
            case 1: // ���� ��� ������������
                system("cls");
                return;
            case 2: // ���� ��� ����������� (�� �����������)
                system("cls");
                return;
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
            cout << "��� ��������������� ��������� ����������� ���������� �������� �������������, � ������� �� ������ ��������� ����� ��: @geralttop. � �����, �� ����, �����. �������� �� ������� ������� �� ������ � ���������� ���� �������: �������, �������, ��������315. ������� ����� ������� �� ��, ��� �� ������ ��������������� ����, ����������� ������� � ����� ���. ������� ���� ��� ��������� (�������� �� ������ �. � ��� ��� ����� ������, ��� �������������, ������� �������� ��� � �����, ������� ��������� ���� ���������� � ����������� ���������� ���� � ���������. ������� ������ � ����� �� ����, ������� ������� � ����, � ������� � ������ � ���� ������.";
            _getch();
            system("cls");
            cout << " �� � �������� �������: ��������� ������ ���� � �����, � ���������� ���: '���, ��� ���� ������?'";
            return;
        }
    }
    _getch();
}
// ������ ���� ���������
void firstWin() {
    // ������������� ������ ���� �������
    system("mode con cols=49 lines=15");
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
            cout << "��� ��������������� ��������� ����������� ���������� �������� �������������, � ������� �� ������ ��������� ����� ��: @geralttop. � �����, �� ����, �����. �������� �� ������� ������� �� ������ � ���������� ���� �������: �������, �������, ��������315. ������� ����� ������� �� ��, ��� �� ������ ��������������� ����, ����������� ������� � ����� ���. ������� ���� ��� ��������� (�������� �� ������ �. � ��� ��� ����� ������, ��� �������������, ������� �������� ��� � �����, ������� ��������� ���� ���������� � ����������� ���������� ���� � ���������. ������� ������ � ����� �� ����, ������� ������� � ����, � ������� � ������ � ���� ������.";
            _getch();
            system("cls");
            cout << " �� � �������� �������: ��������� ������ ���� � �����, � ���������� ���: '���, ��� ���� ������?'";
            return;
        }
    }
}