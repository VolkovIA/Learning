#pragma once
#include <iostream>
#include <string>
using namespace std;

class Message
{
public:
	Message();

private:
	bool incoming;
	string text;
};

