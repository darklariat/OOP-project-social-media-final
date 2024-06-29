#pragma once
#include <iostream>
#include "class Comment.h"
#include "class Date and Memory.h"
using namespace std;

class Post
{
public:
	int ID;
	string Description;
	int Likes;
	int* Liked_Users;
	int Commentnum;
	int ActivityType;
	string ActivityValue;
	Date PublishDate;
	Comment** Comments;


	Post(int, string, int, int*, int, int, string, int, int, int, Comment**);
	Post& operator = (const Post& other);
	Comment** Add_Comment1(int, int, int, int, string, Comment**&);
	void Add_Comment2(int, int, int, int, string);
	void add_memory(int, string);
	~Post();
};

void Post::add_memory(int post_id, string d)
{

	/*return Comments;*/
}

Post::Post(int id = 0, string des = " ", int l = 0, int* l_users = 0, int c = 0, int at = 0, string av = " ", int d = 0, int m = 0, int y = 0, Comment** c1 = 0)
{
	this->ID = id;
	this->Description = des;
	this->Likes = l;
	this->Commentnum = c;
	this->Liked_Users = new int[10];
	copy(l_users, l_users + l, this->Liked_Users);
	this->ActivityType = at;
	this->ActivityValue = av;
	Date d1(d, m, y);
	PublishDate = d1;
}

Post& Post :: operator = (const Post& other)
{
	this->ID = other.ID;
	this->Description = other.Description;
	this->Likes = other.Likes;
	if (other.Liked_Users != nullptr) 
	{
		Liked_Users = new int[10];
		copy(other.Liked_Users, other.Liked_Users + Likes, Liked_Users);
	}
	else 
	{
		Liked_Users = nullptr;
	}
	this->Commentnum = other.Commentnum;
	this->ActivityType = other.ActivityType;
	this->ActivityValue = other.ActivityValue;
	this->PublishDate = other.PublishDate;
	if (other.Comments != nullptr)
	{
		Comments = new Comment*[Commentnum];
		copy(other.Comments, other.Comments + Commentnum, Comments);
	}
	return *this;
}

Post :: ~Post()
{
	delete[]Liked_Users;
	delete[]Comments;
}

Comment** Post::Add_Comment1(int commentnum, int id, int page_id, int post_id, string title, Comment**& Comments)
{
	Comment** temp = new Comment * [commentnum + 1];
	if (commentnum == 0)
	{
		temp[0] = new Comment(id, page_id, post_id, title);
	}
	else
	{
		for (int i = 0; i < commentnum; i++)
		{
			temp[i] = Comments[i];
		}
		temp[commentnum] = new Comment(id, page_id, post_id, title);
		if (Comments)
		{
			delete[] Comments;
		}
	}
	
	Comments = temp;
	return Comments;
}

void Post::Add_Comment2(int commentnum, int id, int page_id, int post_id, string title)
{
	Comments = Add_Comment1(commentnum, id, page_id, post_id, title, Comments);
}
