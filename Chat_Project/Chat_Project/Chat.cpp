#include "Chat.h"
#include <conio.h>

Chat::Chat() : size_(10), id_data_(0), userData_(nullptr), outg_message_()
{
	userData_ = new User[size_];
}
Chat::Chat(const Chat& other)
{
	this->size_ = other.size_;
	this->id_data_ = other.id_data_;
	this->outg_message_ = other.outg_message_;
	this->userData_ = new User[other.size_];
	
	for (int i = 0; i < size_; i++)
	{
		this->userData_[i] = other.userData_[i];
	}
}
Chat::~Chat()
{
	delete[] userData_;
	userData_ = nullptr;
}

void Chat::registration() // Регистрация нового пользователя
{
	// данные, вводимые пользователем
	string name;
	string imale;
	string login;
	string pass;

	do
	{
		cout << endl << "Укажите имя пользователя: ";
		cin.ignore();
		getline(cin, name);
		if (name == "" && name != "\n")
		{
			cout << "Имя польвзователя не может быть пустым!" << endl;
		}
	} while (name =="" && name != "\n");

	do
	{
		cout << endl << "Укажите адрес электронной почты: ";
		getline(cin, imale);
		if (imale == "" && imale != "\n")
		{
			cout << "Адрес электронной почты не может быть пустым!" << endl;
		}
	} while (imale == "" && imale != "\n");
	
	do
	{
		cout << endl << "Придумайте логин: ";
		getline(cin, login);
		if (login == "" && login != "\n")
		{
			cout << "Логин не может быть пустым!" << endl;
		}
	} while (login == "" && login != "\n");
	
	do
	{
		cout << endl << "Укажите пароль: ";
		getline(cin, pass);
		if (pass == "" && pass != "\n")
		{
			cout << "Пароль должен состоять из симоволов!" << endl;
		}
	} while (pass == "" && pass != "\n");
	

	newUser(name, imale, login, pass);
}

void Chat::newUser(const string& name, const string& imale, const string& login, const string& pass) // запись данных нового пользователя в массив во время регистрации
{
	for (int i = 0; i < size_; i++)
	{
		if (userData_[i].getLogin() == "" && i < (size_ - 1)) // проверка, есть ли уже данные в элементе массива, если нет перейти к следующему элементу и так до предпоследнего.
		{
			userData_[i].setName(name);
			userData_[i].setImale(imale);
			userData_[i].setLogin(login);
			userData_[i].setPass(pass);
			break;
		}
		else if (userData_[i].getLogin() == "") // запись данных в последний элемент массива и увеличение массива на 10 элементов.
		{
			userData_[i].setName(name);
			userData_[i].setImale(imale);
			userData_[i].setLogin(login);
			userData_[i].setPass(pass);

			addelement(); // уведичивает массив на 10 элементов.
			break;
		}
	}
}

void Chat::addelement()
{
	User* dataTemp = new User[size_ + 10];

	for (int i = 0; i < size_; i++)
	{
		dataTemp[i] = userData_[i];
	}

	delete[] userData_;

	userData_ = dataTemp;

	dataTemp = nullptr;

	size_+=10;
}

void Chat::entry(bool& check, int& id) // вход для уже зарегистрированного пользователя. id индекс учётной записи в массиве, по нему отправленное сообщение записывается в историю сообщений отправляющему.
{
	string login, pass;

	while (!check) // проверяет лоиг и пароль, пока не будут введены верные
	{
		cout << "Введите логин: ";
		getline(cin, login);
		cout << "Введите пароль: ";
		getline(cin, pass);
		
		for (; id < size_; id++) // поиск соответсвтия
		{
			if (userData_[id].getLogin() == login && userData_[id].getPass() == pass)
			{
				check = 1;
				cout << endl << "Вход выполнен." << endl;
				break;
			}
		}
		if (!check)
		{
			id = 0;
			cout << "Неверные логин и(или) пароль, попробуйте ещё раз." << endl;
		}
	}
}

void Chat::send(bool& check) // отправка сообщений всем пользователям.
{

	if (check) // сделал на всякий случай проверку на авторизацию.
	{
		cout << endl << "Введите сообщение: " << endl;
		getline(cin, outg_message_);

		for (int i = 0; i < size_; i++)
		{
			if (userData_[i].getLogin() != "") // проверка, есть ли уже данные в элементе массива, хранящем историю сообщений, если нет, записать сообщение.
			{
				userData_[i].setMessage(outg_message_); // метод setMessage записывается сообщения в массив, если массив заполнен, вызывает метот, добавляющий новый элемент и записывает сообщение в него.
			}
			else
			{
				break;
			}
		}
	}
}
int Chat::send(const string& name, const bool& check, bool& is_I, const int& id, int& iter) //отправка сообщений конкретному пользователю.
{
	if (check)
	{
		if (!is_I) // когда отправляется первое сообщение, происходит поиск пользователя по указанному имени, когда пользователь найден отправляет сообщение по установленному индексу, что бы не перебирать массив каждый раз.
		{
			for (; iter < size_; iter++)
			{
				if (userData_[iter].getLogin() == name)
				{
					cout << endl << "Введите сообщение: " << endl;
					getline(cin, outg_message_);
					userData_[id].setMessage(outg_message_);
					userData_[iter].setMessage(outg_message_);
					is_I = 1;
					break;
				}
				else if (iter + 1 == size_ && userData_[iter].getLogin() != name)
				{
					cout << "Пользователя с таким именем не сущесвтует, попробуйте ещё раз." << endl;
					iter = 0;
					return 1;
				}
			}
		}
		else if (is_I) // отправляет сообщения по установленному индексу. 
		{
			cout << "Введите сообщение: ";
			getline(cin, outg_message_);
			userData_[id].setMessage(outg_message_);
			userData_[iter].setMessage(outg_message_);
		}
	}
	return 0;
}

void Chat::show_User_m(const int& id)
{
	userData_[id].showm();
}