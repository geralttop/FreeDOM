#include "User.h"
#include <fstream>
#include <iostream>
#include <string>
#include <cctype>

User::User(string log, string p, float bal) {
	login = log;
	pass = p;
	balance = bal;
}
User::User() {

}
float User::getBalance() {
	return balance;
}
void User::setBalance(float bal) {
	balance = bal;
}

vector<User> User::writingUsers()
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

void User::checkingLoginData(vector<User> users)
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

void User::UsSignInUp(vector<User> users)
{
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

bool User::validatePassword(const std::string& password)
{
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

bool User::validateLogin(const std::string& login)
{
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

void User::SignInUs(std::vector<User> users)
{
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
