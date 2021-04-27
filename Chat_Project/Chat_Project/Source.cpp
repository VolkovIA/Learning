#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "Chat.h"

//void addelement(int*& arr, int& size, const int value)
//{
//	int* arrTemp = new int[size + 1];
//
//	for (int i = 0; i < size; i++)
//	{
//		arrTemp[i] = arr[i];
//	}
//
//	arrTemp[size] = value;
//
//	delete[] arr;
//
//	arr = arrTemp;
//
//	arrTemp = nullptr;
//
//	++size;
//}

int chat_f();

int main()
{
	setlocale(LC_ALL, "ru");

	cout << "Программа позволяет зарегистрировать нового пользователя или зайти в уже существующий аккаунт." << endl
		<< "Выйти из аккаунта можно только после ввода сообщения и нажатия enter,"
		<< endl << "в этот момент программа ждёт 800 миллисекунд (функция sleep) и отслеживает нажатие клавиши esc" << endl 
		<< "После входа в аккаунт, новый или предустановленный, программа показывает всю историю сообщений." << endl 
		<<"Но так как я не успел реализовать класс Message, она не делает различий в выводе входящих и исходящих сообщений." << endl << endl;

	chat_f();

	return 0;
}

int chat_f()
{
	bool check = 0;
	int selection = 0;
	string name;
	int id = 0, iter = 0; // id - индекс элемента массива, в котором хранится учётная запись пользователя отправляющего сообщение. iter то же самое, но для пользоветеля получающего сообщение.
	bool is_I = 0; // переменная для проверки в методе send класса chat.
	char esc = 27; //esc для выходы из учётной записи.

	Chat A;
	A.newUser("Vasya", "Vasya@mail.ru", "Vasyanchik", "qwerty"); //предустановленные учётные записи.
	A.newUser("2", "2", "2", "2");
	A.newUser("3", "3", "3", "3");

	while (selection != 1 && selection != 2)
	{
		restart:

		cout << "Нажмите 1 если хотите зарегистрировать нового пользователя или 2 что бы войти." << endl << endl;
		cin >> selection;

		if (selection == 1)
		{
			A.registration();

			cout << endl << "Регистрация завершена!" << endl << endl;
			cout << "Выполните вход в систему." << endl << endl;
			id = A.entry(check);
			A.show_User_m(id);

			cout << "Введите ник получателя или введите 'ALL', что бы отправить сообщение всем пользователям: " << endl << endl;

			getline(cin, name);

			if (name != "ALL")
			{
				while (true)
				{
					A.send(name, check, is_I, id, iter);
					Sleep(800);

					if (_kbhit())
					{
						if (esc ==_getch()) // выход из учётной записи по нажатию клавиши esc
						{
							check = 0;
							iter = 0;
							is_I = 0;
							cout << endl << "Выполнен выход из системы." << endl;
							goto restart;
						}
					}
				}				
			}
			else if (name == "ALL")
			{
				while (true)
				{
					A.send(check, id);
					Sleep(800);

					if (_kbhit()) // выход из учётной записи по нажатию клавиши esc
					{
						if (esc == _getch())
						{
							check = 0;
							cout << endl << "Выполнен выход из системы." << endl;
							break;
						}
					}
				}				
			}
		}
		else if (selection == 2)
		{
			cout << "Выполните вход в систему." << endl << endl;
			cin.get();
			id = A.entry(check);
			A.show_User_m(id);

		user_name_error:

			cout << endl << "Введите ник получателя или введите 'ALL', что бы отправить сообщение всем пользователям: " << endl << endl;
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

					if (_kbhit()) // выход из учётной записи по нажатию клавиши esc
					{
						if (esc == _getch())
						{
							check = 0;
							iter = 0;
							cout << endl << "Выполнен выход из системы." << endl;
							goto restart;
						}
					}
				}
			}
			else if (name == "ALL")
			{
				while (true)
				{
					A.send(check, id);
					Sleep(800);

					if (_kbhit())
					{
						if (esc == _getch()) // выход из учётной записи по нажатию клавиши esc
						{
							check = 0;
							cout << endl << "Выполнен выход из системы." << endl;
							goto restart;
						}
					}
				}
			}
		}
	}
	return 0;
}