#pragma once
#include<iostream>
#include "class Page.h"
using namespace std;

class User
{
public:
	string name;
	int ID;
	int pagenum;
	int* liked_Pages;
	int liked_Pages_size;
	int* friends;
	int friends_size;
	Page** owned_Pages;

	User(string, int, int*, int, int*, int, int);
	~User();
	User& operator = (const User&);
	string get_name() { return name; }
	int get_ID() { return ID; }
	void set_name(string name) { this->name = name; }
	void set_ID(int ID) { this->ID = ID; }
	void Add_Page1(int, int, int, string, int, int*, int, int, int, Page**&);
	void Add_Page(int, int, int, string, int, int*, int, int, int);
};

User:: User(string name = " ", int ID = 0, int* liked_pages = 0, int likedpages = 0, int* friendss = 0, int numfriends = 0, int pagenum = 0)
{
	this->name = name;
	this->ID = ID;
	this->liked_Pages_size = likedpages;
	this->liked_Pages = new int[likedpages];
	copy(liked_pages, liked_pages + likedpages, this->liked_Pages);
	this->friends_size = numfriends;
	this->friends = new int[numfriends];
	copy(friendss, friendss + numfriends, this->friends);
	this->pagenum = pagenum;
	owned_Pages = new Page * [1];
	owned_Pages[0] = new Page[1];
}

User& User :: operator = (const User& other)
{
	if (this != &other)
	{
		name = other.name;
		ID = other.ID;
		delete[] liked_Pages;
		liked_Pages = new int[other.liked_Pages_size];
		copy(other.liked_Pages, other.liked_Pages + other.liked_Pages_size, this->liked_Pages);
		delete[] friends;
		friends = new int[other.friends_size];
		copy(other.friends, other.friends + other.friends_size, this->friends);
		pagenum = other.pagenum;
	}
	return *this;
}

User :: ~User()
{
	delete[]liked_Pages;
	delete[]friends;
}

void User::Add_Page1(int currentpage, int ID, int Owner, string Title, int likes, int* posts, int postnum, int currentpost, int pagenum, Page**& owned_Pages)
{
	Page** temp = new Page * [currentpage + 1];
	if (currentpage == 0)
	{
		temp[0] = new Page(ID, Owner, Title, likes, posts, postnum);
	}

	else
	{
		for (int i = 0; i < currentpage; ++i)
		{
			temp[i] = owned_Pages[i];
		}
		temp[currentpage] = new Page(ID, Owner, Title, likes, posts, postnum);
		if (owned_Pages)
		{
			delete[]owned_Pages;
		}
	}
    owned_Pages = temp;
}

void User::Add_Page(int currentpage, int ID, int Owner, string Title, int likes, int* posts, int postnum, int currentpost, int pagenum)
{
	Add_Page1(currentpage, ID, Owner, Title, likes, posts, postnum, currentpost, pagenum, owned_Pages);
}