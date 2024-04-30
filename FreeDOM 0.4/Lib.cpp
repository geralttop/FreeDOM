#include "Lib.h"

//���������� �� ����� � ������ ������ � ������������
vector<User> writingUsers()
{
    vector<User> users; //��������� ������ ������������

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
    cout << "login";
    cin >> signInLogin;
    cout << "pass";
    cin >> signInPass;
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
    /*if (users[1].getLogin() == "asd") {
        cout << "Yes";
    }
    else {
        cout << users[1].getLogin();
    }*/
}


