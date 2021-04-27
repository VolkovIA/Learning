#pragma once
#include <iostream>
#include <string>
using namespace std;

class User
{
public:
	User();
	/*User(string name, string imale, string login, string pass);*/
	User(const User& other);
	~User();

	void setName(string name);
	void setImale(string imale);
	void setLogin(string login);
	void setPass(string pass);
	void setMessage(string& text);
	void addelementmess();

	int getSize();
	string getName();
	string getImale();
	string getLogin();
	string getPass();
	void showm();

	User& operator =(const User& other);

private:
	int size_;
	string name_;
	string imale_;
	string login_;
	string pass_;
	string* messages_;
};

