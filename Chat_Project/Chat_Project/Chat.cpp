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

void Chat::registration() // ����������� ������ ������������
{
	// ������, �������� �������������
	string name;
	string imale;
	string login;
	string pass;

	do
	{
		cout << endl << "������� ��� ������������: ";
		cin.ignore();
		getline(cin, name);
		if (name == "" && name != "\n")
		{
			cout << "��� ������������� �� ����� ���� ������!" << endl;
		}
	} while (name =="" && name != "\n");

	do
	{
		cout << endl << "������� ����� ����������� �����: ";
		getline(cin, imale);
		if (imale == "" && imale != "\n")
		{
			cout << "����� ����������� ����� �� ����� ���� ������!" << endl;
		}
	} while (imale == "" && imale != "\n");
	
	do
	{
		cout << endl << "���������� �����: ";
		getline(cin, login);
		if (login == "" && login != "\n")
		{
			cout << "����� �� ����� ���� ������!" << endl;
		}
	} while (login == "" && login != "\n");
	
	do
	{
		cout << endl << "������� ������: ";
		getline(cin, pass);
		if (pass == "" && pass != "\n")
		{
			cout << "������ ������ �������� �� ���������!" << endl;
		}
	} while (pass == "" && pass != "\n");
	

	newUser(name, imale, login, pass);
}

void Chat::newUser(const string& name, const string& imale, const string& login, const string& pass) // ������ ������ ������ ������������ � ������ �� ����� �����������
{
	for (int i = 0; i < size_; i++)
	{
		if (userData_[i].getLogin() == "" && i < (size_ - 1)) // ��������, ���� �� ��� ������ � �������� �������, ���� ��� ������� � ���������� �������� � ��� �� ��������������.
		{
			userData_[i].setName(name);
			userData_[i].setImale(imale);
			userData_[i].setLogin(login);
			userData_[i].setPass(pass);
			break;
		}
		else if (userData_[i].getLogin() == "") // ������ ������ � ��������� ������� ������� � ���������� ������� �� 10 ���������.
		{
			userData_[i].setName(name);
			userData_[i].setImale(imale);
			userData_[i].setLogin(login);
			userData_[i].setPass(pass);

			addelement(); // ����������� ������ �� 10 ���������.
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

void Chat::entry(bool& check, int& id) // ���� ��� ��� ������������������� ������������. id ������ ������� ������ � �������, �� ���� ������������ ��������� ������������ � ������� ��������� �������������.
{
	string login, pass;

	while (!check) // ��������� ���� � ������, ���� �� ����� ������� ������
	{
		cout << "������� �����: ";
		getline(cin, login);
		cout << "������� ������: ";
		getline(cin, pass);
		
		for (; id < size_; id++) // ����� ������������
		{
			if (userData_[id].getLogin() == login && userData_[id].getPass() == pass)
			{
				check = 1;
				cout << endl << "���� ��������." << endl;
				break;
			}
		}
		if (!check)
		{
			id = 0;
			cout << "�������� ����� �(���) ������, ���������� ��� ���." << endl;
		}
	}
}

void Chat::send(bool& check) // �������� ��������� ���� �������������.
{

	if (check) // ������ �� ������ ������ �������� �� �����������.
	{
		cout << endl << "������� ���������: " << endl;
		getline(cin, outg_message_);

		for (int i = 0; i < size_; i++)
		{
			if (userData_[i].getLogin() != "") // ��������, ���� �� ��� ������ � �������� �������, �������� ������� ���������, ���� ���, �������� ���������.
			{
				userData_[i].setMessage(outg_message_); // ����� setMessage ������������ ��������� � ������, ���� ������ ��������, �������� �����, ����������� ����� ������� � ���������� ��������� � ����.
			}
			else
			{
				break;
			}
		}
	}
}
int Chat::send(const string& name, const bool& check, bool& is_I, const int& id, int& iter) //�������� ��������� ����������� ������������.
{
	if (check)
	{
		if (!is_I) // ����� ������������ ������ ���������, ���������� ����� ������������ �� ���������� �����, ����� ������������ ������ ���������� ��������� �� �������������� �������, ��� �� �� ���������� ������ ������ ���.
		{
			for (; iter < size_; iter++)
			{
				if (userData_[iter].getLogin() == name)
				{
					cout << endl << "������� ���������: " << endl;
					getline(cin, outg_message_);
					userData_[id].setMessage(outg_message_);
					userData_[iter].setMessage(outg_message_);
					is_I = 1;
					break;
				}
				else if (iter + 1 == size_ && userData_[iter].getLogin() != name)
				{
					cout << "������������ � ����� ������ �� ����������, ���������� ��� ���." << endl;
					iter = 0;
					return 1;
				}
			}
		}
		else if (is_I) // ���������� ��������� �� �������������� �������. 
		{
			cout << "������� ���������: ";
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