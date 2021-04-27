#include "User.h"

User::User() : name_(), imale_(), login_(), pass_(), messages_(), size_(20)
{
	//std::cout << "Вызвался конструктор " << this << std::endl;
	messages_ = new string[size_];
}
//User::User(string name, string imale, string login, string pass) : name_(name), imale_(imale), login_(login), pass_(pass), size_(10)
//{
//	//std::cout << "Вызвался конструктор " << this << std::endl;
//	inc_message_ = new string[size_];
//}
User::User(const User& other)
{
	//std::cout << "Вызвался конструктор копирования " << this << std::endl;

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
User::~User()
{
	//std::cout << "Вызвался деструктор " << this << std::endl;
	delete[] messages_;
	messages_ = nullptr;
}

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
void User::setMessage(string& text)
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
void User::addelementmess()
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

void User::showm()
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

User& User::operator =(const User& other)
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