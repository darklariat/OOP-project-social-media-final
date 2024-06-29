#pragma once
#include<iostream>
#include"class Post.h"
using namespace std;

class Date
{
public:
	int Day;
	int Month;
	int Year;

	Date(int, int, int);
	Date& operator = (const Date& other);
};

Date::Date(int day = 0, int month = 0, int year = 0)
{
	this->Day = day;
	this->Month = month;
	this->Year = year;
}

Date& Date:: operator = (const Date& other)
{
	this->Day = other.Day;
	this->Month = other.Month;
	this->Year = other.Year;
	return *this;
}

class Memory
{
public:
	int post_id;
	string Description;

	Memory(int, string);
	Memory& operator = (const Memory& other);
};

Memory :: Memory(int post_id = 0, string D = " ")
{
	this->post_id = post_id;
	this->Description = D;
}

Memory& Memory:: operator = (const Memory& other)
{
	this->post_id = other.post_id;
	this->Description = other.Description;
	return *this;
}