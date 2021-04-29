#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "Chat.h"

int chat_f();

int main()
{
	setlocale(LC_ALL, "ru");

	cout << "��������� ��������� ���������������� ������ ������������ ��� ����� � ��� ������������ �������." << endl
		<< "����� �� �������� ����� ������ ����� ����� ��������� � ������� enter,"
		<< endl << "� ���� ������ ��������� ��� 800 ����������� (������� sleep) � ����������� ������� ������� esc" << endl 
		<< "����� ����� � �������, ����� ��� �����������������, ��������� ���������� ��� ������� ���������." << endl 
		<<"�� ��� ��� � �� ����� ����������� ����� Message, ��� �� ������ �������� � ������ �������� � ��������� ���������." << endl << endl;

	chat_f();

	return 0;
}

int chat_f()
{
	bool check = 0; // �������� ����������
	int selection = 0; // ����� ���� ����������� ��� �����
	string name; // ��� ���������� ���������
	int id = 0, iter = 0; // id ��� ������ ������������� ������������ � �������, �������� ������ �������������, iter ��� ������ ������������, ����������� ���������.
	bool is_I = 0; // ���������� ������������ ��� �������� ������������ �� ������������ ��������� �����. ��� �������� ������� ���������. ������������ ������ � ������� �� ���������� �����, ����� ��� ������ ������������ � iter � ��� ����������� ��������� ������������ ��� �� ����� �������.
	char esc = 27;

	Chat A;
	A.newUser("Vasya", "Vasya@mail.ru", "Vasyanchik", "qwerty");
	A.newUser("2", "2", "2", "2");
	A.newUser("3", "3", "3", "3");

	while (selection != 1 && selection != 2)
	{
		restart:

		cout << "������� 1 ���� ������ ���������������� ������ ������������ ��� 2 ��� �� �����." << endl << endl;
		cin >> selection;

		if (selection == 1)
		{
			A.registration();

			cout << endl << "����������� ���������!" << endl << endl;
			cout << "��������� ���� � �������." << endl << endl;
			A.entry(check, id);
			A.show_User_m(id); // �������� ����� show ������ User, ��� �� ������� ������� ��������� ��� �����.

			cout << "������� ��� ���������� ��� ������� 'ALL', ��� �� ��������� ��������� ���� �������������: " << endl << endl;

			getline(cin, name);

			if (name != "ALL")
			{
				while (true)
				{
					A.send(name, check, is_I, id, iter);
					Sleep(800);

					if (_kbhit()) // ����� �� �������� �� ������� ������� esc.
					{
						if (esc ==_getch())
						{
							check = 0;
							iter = 0;
							is_I = 0;
							id = 0;
							cout << endl << "�������� ����� �� �������." << endl;
							goto restart;
						}
					}
				}				
			}
			else if (name == "ALL")
			{
				while (true)
				{
					A.send(check);
					Sleep(800);

					if (_kbhit())
					{
						if (esc == _getch())
						{
							check = 0;
							id - 0;
							cout << endl << "�������� ����� �� �������." << endl;
							goto restart;
						}
					}
				}				
			}
		}
		else if (selection == 2)
		{
			cout << "��������� ���� � �������." << endl << endl;
			cin.get();
			A.entry(check, id);
			A.show_User_m(id);

		user_name_error:

			cout << endl << "������� ��� ���������� ��� ������� 'ALL', ��� �� ��������� ��������� ���� �������������: " << endl << endl;
			getline(cin, name);

			if (name != "ALL")
			{
				while (true)
				{
					int err = A.send(name, check, is_I, id, iter);
					if (err)
					{
						goto user_name_error;
					}
					Sleep(800);

					if (_kbhit()) // ����� �� �������� �� ������� ������� esc.
					{
						if (esc == _getch())
						{
							check = 0;
							iter = 0;
							is_I = 0;
							id = 0;
							cout << endl << "�������� ����� �� �������." << endl;
							goto restart;
						}
					}
				}
			}
			else if (name == "ALL")
			{
				while (true)
				{
					A.send(check);
					Sleep(800);

					if (_kbhit()) // ����� �� �������� �� ������� ������� esc.
					{
						if (esc == _getch())
						{
							check = 0;
							id = 0;
							cout << endl << "�������� ����� �� �������." << endl;
							goto restart;
						}
					}
				}
			}
		}
	}
	return 0;
}