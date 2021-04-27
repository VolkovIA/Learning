#include "User.h"

User::User() : name_(), imale_(), login_(), pass_(), messages_(), size_(20) //Конструктор
{
	messages_ = new string[size_];
}

User::User(const User& other) // Конструктор копирования.
{
	this->size_ = other.size_;
	this->name_ = other.name_;
	this->imale_ = other.imale_;
	this->login_ = other.login_;
	this->pass_ = other.pass_;
	this->messages_ = new string[other.size_];

	for (int i = 0; i < other.size_; i++)
	{
		this->messages_[i] = other.messages_[i];
	}
}
User::~User() // Деструктор
{
	delete[] messages_;
	messages_ = nullptr;
}

//Сеттеры.
void User::setName(std::string name)
{
	name_ = name;
}
void User::setImale(std::string imale)
{
	imale_ = imale;
}
void User::setLogin(std::string login)
{
	login_ = login;
}
void User::setPass(std::string pass)
{
	pass_ = pass;
}

void User::setMessage(string& text) //Запись отправленного сообщения в историю свою и адресата.
{
	for (int i = 0; i < size_; i++)
	{
		if (messages_[i] == "" && i < (size_ - 1))
		{
			messages_[i] = text;
			break;
		}
		else if (messages_[i] == "")
		{
			messages_[i] = text;
			addelementmess();
			break;
		}
	}
}
void User::addelementmess() //Добавление элемента массива, хранящего сообщения.
{
	string* messTemp = new string[size_ + 20];

	for (int i = 0; i < size_; i++)
	{
		messTemp[i] = messages_[i];
	}

	delete[] messages_;

	messages_ = messTemp;

	messTemp = nullptr;

	size_ += 20;
}

// Геттеры
int User::getSize()
{
	return size_;
}
string User::getName()
{
	return name_;
}
string User::getImale()
{
	return imale_;
}
string User::getLogin()
{
	return login_;
}
string User::getPass()
{
	return pass_;
}

void User::showm() // Выводит сообщения, если элемент массива содержит текст.
{
	cout << endl << endl;
	for (int i = 0; i < size_; i++)
	{
		if (messages_[i] != "")
		{
			cout << messages_[i] << endl;
		}
		else
		{
			break;
		}
	}
}

User& User::operator =(const User& other) // Перегрузка оператора присваивания.
{
	this->size_ = other.size_;
	this->name_ = other.name_;
	this->imale_ = other.imale_;
	this->login_ = other.login_;
	this->pass_ = other.pass_;

	if (this->messages_ != nullptr)
	{
		delete[]this->messages_;
	}

	this->messages_ = new string[other.size_];

	for (int i = 0; i < other.size_; i++)
	{
		this->messages_[i] = other.messages_[i];
	}

	return *this;
}