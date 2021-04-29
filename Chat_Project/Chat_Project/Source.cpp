#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "Chat.h"

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
	bool check = 0; // првоерка аторизации
	int selection = 0; // выбор меню регистрации или входа
	string name; // имя получателя сообщения
	int id = 0, iter = 0; // id это индекс отправляющего пользователя в массиве, хранящем данные пользователей, iter это индекс пользователя, получающего сообщение.
	bool is_I = 0; // переменная используется для проверки отправлялось ли пользователю сообщение ранее. При отправке первого сообщения. пользователь ищется в массиве по указанному имени, далее его индекс записывается в iter и все последующие сообщения отправляются уже по этому индексу.
	char esc = 27;

	Chat A;
	A.newUser("Vasya", "Vasya@mail.ru", "Vasyanchik", "qwerty");
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
			A.entry(check, id);
			A.show_User_m(id); // вызывает метод show класса User, что бы вывести историю сообщений при входе.

			cout << "Введите ник получателя или введите 'ALL', что бы отправить сообщение всем пользователям: " << endl << endl;

			getline(cin, name);

			if (name != "ALL")
			{
				while (true)
				{
					A.send(name, check, is_I, id, iter);
					Sleep(800);

					if (_kbhit()) // выход из аккаунта по нажатию клавиши esc.
					{
						if (esc ==_getch())
						{
							check = 0;
							iter = 0;
							is_I = 0;
							id = 0;
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
					A.send(check);
					Sleep(800);

					if (_kbhit())
					{
						if (esc == _getch())
						{
							check = 0;
							id - 0;
							cout << endl << "Выполнен выход из системы." << endl;
							goto restart;
						}
					}
				}				
			}
		}
		else if (selection == 2)
		{
			cout << "Выполните вход в систему." << endl << endl;
			cin.get();
			A.entry(check, id);
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

					if (_kbhit()) // выход из аккаунта по нажатию клавиши esc.
					{
						if (esc == _getch())
						{
							check = 0;
							iter = 0;
							is_I = 0;
							id = 0;
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
					A.send(check);
					Sleep(800);

					if (_kbhit()) // выход из аккаунта по нажатию клавиши esc.
					{
						if (esc == _getch())
						{
							check = 0;
							id = 0;
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