#include "Chat.h"
//#include <Windows.h>
#include <conio.h>

Chat::Chat() : size_(10), id_data_(0), userData_(nullptr), outg_message_()  //Конструктор класса
{
	userData_ = new User[size_];
}
Chat::Chat(const Chat& other) //Конструктор копирования
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
} //Деструктор

void Chat::registration()  //Функция регистрации
{
	//Переменные, которые предлагается ввести пользователию для регистрации аккаунта.

	string name;
	string imale;
	string login;
	string pass;

	//Ввод переменных
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
	

	newUser(name, imale, login, pass); // Запись данных.
}

void Chat::newUser(const string& name, const string& imale, const string& login, const string& pass) //метод записывает данные нового пользователя в динамический массив.
{
	for (int i = 0; i < size_; i++)
	{
		if (userData_[i].getLogin() == "" && i < (size_ - 1))
		{
			userData_[i].setName(name);
			userData_[i].setImale(imale);
			userData_[i].setLogin(login);
			userData_[i].setPass(pass);
			break;
		}
		else if (userData_[i].getLogin() == "")
		{
			userData_[i].setName(name);
			userData_[i].setImale(imale);
			userData_[i].setLogin(login);
			userData_[i].setPass(pass);

			addelement();
			break;
		}
	}
}

void Chat::addelement() //метод добавляет в динамический массив, в котором хранятся учётные данные, новый элемент, если массив заполнен и увеличивает размер массива на 10.
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

int Chat::entry(bool& check) //метод авторизации.
{
	string login, pass;
	int i = 0;

	while (!check)
	{
		cout << "Введите логин: ";
		getline(cin, login);
		cout << "Введите пароль: ";
		getline(cin, pass);
		
		for (; i < size_; i++)
		{
			if (userData_[i].getLogin() == login && userData_[i].getPass() == pass)
			{
				check = 1;
				cout << endl << "Вход выполнен." << endl;
				break;
			}
		}
		if (!check)
		{
			i = 0;
			cout << "Неверные логин и(или) пароль, попробуйте ещё раз." << endl;
		}
	}
	return i; //возвращает индекс элемента массива в котором хранится учётная запись пользователя.
}

void Chat::send(bool& check, const int& id = 0) //Метод отправки сообщений всем пользователям.
{

	if (check)
	{
		cout << endl << "Введите сообщение: " << endl;
		getline(cin, outg_message_);
		userData_[id].setMessage(outg_message_);

		for (int i = 0; i < size_; i++)
		{
			if (userData_[i].getLogin() != "")
			{
				userData_[i].setMessage(outg_message_);
			}
			else
			{
				break;
			}
		}
	}
}
int Chat::send(const string& name, const bool& check, bool& is_I, const int& id, int& iter) //Метод отправки сообщений конкретному пользователю.
{
	if (check)
	{
		//Проверка поиска, если пользовтелью было отправлено сообщение ранее, программа не будет снова перебирать весь массив. что бы найти его, а отправит сообщение сразу по нужному индексу.
		if (!is_I)
		{
			for (; iter < size_; iter++)
			{
				//Отправка сообщения и поиск адресата сообщения в массиве. Iter это индекс элемента массива.
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
		//Дальнейшая отправка сообщений по полученному индексу.
		else if (is_I)
		{
			cout << "Введите сообщение: ";
			getline(cin, outg_message_);
			userData_[id].setMessage(outg_message_);
			userData_[iter].setMessage(outg_message_);
		}
	}
	return 0;
}

//Вывод истории сообщений при входе в учётную запись.
void Chat::show_User_m(const int& id)
{
	userData_[id].showm();
}