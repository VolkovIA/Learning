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

	void registration(); // Регистрация нового пользователя
	void entry(bool& check, int& id); // вход для уже зарегистрированного пользователя
	void newUser(const string& name, const string& imale, const string& login, const string& pass); // запись данных нового пользователя в массив во время регистрации

	void addelement(); // добавляет новый элемент в массив, хранящий данные пользоветелей.
	void send(bool& check); // отправка сообщений всем пользователям.
	int send(const string& name, const bool& check, bool& is_I, const int& id, int& iter); //отправка сообщений конкретному пользователю.
	void show_User_m(const int& id); // показывает историю сообщений при входе в аккаунт.

private:
	
	User* userData_;
	int size_;
	int id_data_;
	string outg_message_;
};

