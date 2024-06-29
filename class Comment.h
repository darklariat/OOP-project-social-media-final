#pragma once
#include<iostream>
#include"class User.h"
#include"class Page.h"
using namespace std;

class Comment
{
public:
	int ID;
	string Text;
	int User_ID;
	int Page_ID;
	int	Post_ID;

	Comment(int, int, int, string, int);
	Comment& operator = (const Comment& other);
	Comment(const Comment& other);
	~Comment();
};

Comment::Comment(int id = 0, int page_id = 0, int post_id = 0, string text = " ", int User_ID = 0)
{
	this->ID = id;
	this->Page_ID = page_id;
	this->Post_ID = post_id;
	this->User_ID = (page_id / 10);
	this->Text = text;
}

Comment& Comment :: operator = (const Comment& other)
{
	this->ID = other.ID;
	this->Text = other.Text;
	this->User_ID = other.User_ID;
	this->Page_ID = other.Page_ID;
	this->Post_ID = other.Post_ID;
	return *this;
}

Comment::Comment(const Comment& other): ID(other.ID), Text(other.Text), User_ID(other.User_ID), Page_ID(other.Page_ID), Post_ID(other.Post_ID) {}

Comment :: ~Comment(){}
