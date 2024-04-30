#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <fstream>
#include "User.h"
#include "Lib.h"
#include <Windows.h>
#include <stdio.h>
#include <conio.h>

using namespace std;

//���������� �� ����� � ������ ������ � ������������
vector<User> writingUsers()
{
    vector<User> users; //��������� ������ �������������

    //��������� ����� ��� ������
    ifstream ifUsLogin; 
    ifstream ifUsPass;
    ifstream ifUsBalance;
    ifUsLogin.open("userNames.txt");
    ifUsPass.open("passOfUsers.txt");
    ifUsBalance.open("userBalances.txt");
    
    //���� ����������� ������ �� ����� � ������������ �� � ������� ������������
    while (!ifUsLogin.eof())
    {
        string login;
        string pass;
        string balance;

        getline(ifUsLogin, login);
        getline(ifUsPass, pass);
        getline(ifUsBalance, balance);
        float fbalance = stof(balance);

        users.push_back(User(login, pass, fbalance));
    }

    //�������� ���������� �����
    ifUsLogin.close();
    ifUsPass.close();
    ifUsBalance.close();

    return users;
}

void checkingLoginData(vector<User> users)
{
    string signInLogin;
    string signInPass;
    cin.ignore();
    std::cout << "login: ";
    std::getline(std::cin, signInLogin);
    std::cout << "pass: ";
    std::getline(std::cin, signInPass);
    for (int i = 0; i < users.size(); i++) {
        if (users[i].getLogin() == signInLogin) {
            if (users[i].getPass() == signInPass) {
                cout << "���� �������� �������";
            }
            else {
                cout << "����� ������������ ������, ���������� ��� ���\n";
                checkingLoginData(users);
            }
            return;
        }
    }
    cout << "������ ������������ �����, ���������� ��� ���\n";
    checkingLoginData(users);
    return;
}

void UsSignInUp(vector<User> users) {
    int choose;
    cout << "1. �����\n2. ������������������\n";
    cin >> choose;
    system("cls");
    switch (choose)
    {
    case (1):
        checkingLoginData(users);
        break;
    case (2):
        SignInUs(users);
        break;
    default:
        break;
    }
}

bool validatePassword(const std::string& password) {
    if (password.length() < 8) {
        std::cout << "������ ������ ��������� �� ����� 8 ��������." << std::endl;
        return false;
    }

    bool hasLowercase = false;
    bool hasUppercase = false;
    bool hasDigit = false;
    bool hasSpace = false;

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
            std::cout << "������ �� ������ ��������� ������������� ��������." << std::endl;
            return false;
        }
    }

    if (hasSpace) {
        std::cout << "������ �� ������ ��������� ��������." << std::endl;
        return false;
    }

    if (!hasLowercase) {
        std::cout << "������ ������ ��������� ���� �� ���� �������� �����." << std::endl;
        return false;
    }

    if (!hasUppercase) {
        std::cout << "������ ������ ��������� ���� �� ���� ��������� �����." << std::endl;
        return false;
    }

    if (!hasDigit) {
        std::cout << "������ ������ ��������� ���� �� ���� �����." << std::endl;
        return false;
    }

    return true;
}

bool validateLogin(const std::string& login) {
    // �������� �� ����� ������
    if (login.length() < 6) {
        std::cout << "����� ������ ������ ���� �� ����� 6 ��������.\n";
        return false;
    }

    // �������� �� ������� ����� � ���������� ������������� ��������
    bool hasLetter = false;
    for (char c : login) {
        if (isalpha(static_cast<unsigned char>(c))) {
            hasLetter = true;
        }
        // �������� �� ������������� �������
        if (c >= 128) {
            std::cout << "����� �� ������ ��������� ������������� �������.\n";
            return false;
        }
    }
    if (!hasLetter) {
        std::cout << "����� ������ ��������� ���� �� ���� �����.\n";
        return false;
    }

    // �������� �� ���������� ��������
    for (char c : login) {
        if (isspace(static_cast<unsigned char>(c))) {
            std::cout << "����� �� ������ ��������� �������.\n";
            return false;
        }
    }

    return true;
}

void SignInUs(std::vector<User> users) {
    std::string signUpLogin;
    std::string signUpPass;
    std::string signUpRepitPass;
    std::cout << "login: ";
    std::cin >> signUpLogin;

    if (!validateLogin(signUpLogin)) {
        SignInUs(users); // ����������� ����� �����
        return;
    }

    for (auto& user : users) {
        if (signUpLogin == user.getLogin()) {
            system("cls");
            std::cout << "����� ����� ��� �����\n";
            SignInUs(users);
            return;
        }
    }
    std::cout << "pass: ";
    std::cin.ignore(); // ������� ����� ����� ����� ������� ������
    std::getline(std::cin, signUpPass); // ��������� ������ � ���������
    if (!validatePassword(signUpPass)) {
        SignInUs(users);
        return;
    }
    std::cout << "repit pass: ";
    std::getline(std::cin, signUpRepitPass); // ��������� ��������� ������ � ���������
    if (signUpPass != signUpRepitPass) {
        system("cls");
        std::cout << "������ ����������� ��������\n";
        SignInUs(users);
        return;
    }

    std::ofstream ofUsLogin;
    std::ofstream ofUsPass;
    std::ofstream ofUsBalance;
    ofUsLogin.open("userNames.txt", std::ofstream::app);
    ofUsBalance.open("userBalances.txt", std::ofstream::app);
    ofUsPass.open("passOfUsers.txt", std::ofstream::app);

    ofUsLogin << std::endl << signUpLogin;
    ofUsBalance << std::endl << 0;
    ofUsPass << std::endl << signUpPass;
    std::cout << "������������ ������� ���������������";

    ofUsLogin.close();
    ofUsBalance.close();
    ofUsPass.close();
}

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); // �������� ���������� �������
// ��������� ������ � ����� x,y 
void GoToXY(short x, short y)
{
    SetConsoleCursorPosition(hStdOut, { x, y });
}

void ConsoleCursorVisible(bool show, short size)
{
    CONSOLE_CURSOR_INFO structCursorInfo;
    GetConsoleCursorInfo(hStdOut, &structCursorInfo);
    structCursorInfo.bVisible = show; // �������� ��������� �������
    structCursorInfo.dwSize = size;   // �������� ������ �������
    SetConsoleCursorInfo(hStdOut, &structCursorInfo);
}


void firstWin() {
    ConsoleCursorVisible(false, 100);

    string Menu[] = {"��� User", "��� Developer"};
    int active_menu = 0;

    
    bool T = true;
    char ch;
    while (T)
    {
        int x = 15, y = 5;
        GoToXY(x, y);

        for (int i = 0; i < size(Menu); i++)
        {
            if (i == active_menu) 	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            else 	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
            GoToXY(x, y++);
            cout << Menu[i] << endl;
        }
        ch = _getch();
        if (ch == -32) ch = _getch(); // ����������� ���������
        switch (ch)
        {
        case 27:
            exit(0);
        case 72:
            if (active_menu > 0)
                --active_menu;
            break;
        case 80:
            if (active_menu < size(Menu) - 1)
                ++active_menu;
            break;
        case 13:
            switch (active_menu)
            {
            case 0:
                system("CLS");
                GoToXY(x, y);
                SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                cout << "������������ ������ \"" << Menu[active_menu] << "\"";
                _getch();
                system("CLS");
                break;
            case 1:
                system("cls");
                cout << "���� ��� ����������� ��� ����������";
                break;
            }
            break;
            
        }
    }
    _getch();
}