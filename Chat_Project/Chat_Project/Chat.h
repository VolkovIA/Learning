#pragma once
#include <iostream>
#include <string>
#include "User.h"

class Chat
{
public:
	Chat();
	Chat(const Chat& other);
	~Chat();

	void registration();
	int entry(bool& check);
	void newUser(const string& name, const string& imale, const string& login, const string& pass);

	void addelement();
	void send(bool& check, const int& id);
	int send(const string& name, const bool& check, bool& is_I, const int& id, int& iter);
	void show_User_m(const int& id);

private:
	
	User* userData_;
	int size_;
	int id_data_;
	string outg_message_;
};

