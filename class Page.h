#pragma once
#include <iostream>
#include "class Post.h"
using namespace std;

class Page
{
public:
	int ID;
	int Owner;
	string Title;
	int likes;
	int* Posts;
	int Postnum;
	Post** Timeline;

	Page (int, int, string, int, int*, int);
	Page& operator = (const Page& other);
	~Page();
	void Add_post(int, int, int, string, int, int*, int, int, string, int, int, int);
	void Add_post1(int, int,int, string, int, int*, int, int, string, int, int, int, Post**&);
};

Page::Page(int id = 0, int owner = 0, string title = " ", int likes = 0, int* posts = 0, int postnum = 0)
{
	this->ID = id;
	this->Owner = owner;
	this->Title = title;
	this->likes = likes;
	this->Postnum = postnum;

	if (Posts != nullptr) {
		copy(posts, posts + postnum, Posts);
	}
	Timeline = new Post * [1];
	Timeline[0] = new Post[1];
}

Page& Page::operator=(const Page& other) 
{
	if (this != &other) {
		ID = other.ID;
		Owner = other.Owner;
		Title = other.Title;
		likes = other.likes;
		Postnum = other.Postnum;
		// Check if Posts needs to be reallocated
		if (Postnum != other.Postnum) {
			delete[] Posts;
			Posts = new int[other.Postnum];
		}
		// Copy the data
		copy(other.Posts, other.Posts + other.Postnum, Posts);
		copy(other.Timeline, other.Timeline + other.Postnum, Timeline);
	}
	return *this;
}

Page :: ~Page()
{
	delete[]Posts;
	delete[]Timeline;
}

void Page ::Add_post1(int currentpost,int postnum, int id, string title, int likes, int* likedpeople, int comments, int activitytype, string activityvalue, int day, int month, int year, Post**& Timeline)
{
	Post** temp = new Post * [currentpost + 1];
	if (currentpost == 0)
	{
		temp[0] = new Post(id, title, likes, likedpeople, comments, activitytype, activityvalue, day, month, year);
	}
	else 
	{
		for (int i = 0; i < currentpost; ++i)
		{
			temp[i] = Timeline[i];
		}
		temp[currentpost] = new Post(id, title, likes, likedpeople, comments, activitytype, activityvalue, day, month, year); // Create a new Post object
		if (Timeline)
		{
			delete[] Timeline;
		}
	}
	Timeline = temp;
}

void Page::Add_post(int currentpost, int postnum, int id, string title, int likes, int* likedpeople, int comments, int activitytype, string activityvalue, int day, int month, int year)
{
	Add_post1(currentpost, postnum, id, title, likes, likedpeople, comments, activitytype, activityvalue, day, month, year, Timeline);
}