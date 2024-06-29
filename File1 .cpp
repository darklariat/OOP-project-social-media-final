#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <cstdlib>
#include "class User.h"
#include "class Page.h"
#include "class Post.h"
using namespace std;

template <typename T>

void delete2D(int rows, T** arr)
{
	for (int i = 0; i < rows; i++)
	{
		delete[] arr[i];
	}
	delete[]arr;
}

class App
{
public:
	int currentUser;
	int userTotal;
	int currentpage;
	User** User_List;

	void set_User();
	void set_page(int);
	void InputData(fstream&, int);
	void Input();
	void Run();
	void print_Comment(int, int, int, int);
	void print_Post(int, int, int);
	void View_Post();
	void print_Page(int, int);
	void View_Home(int, int, int);
	void Add_Like();
	void View_Liked();
	void Addcomment();
	void View_Timeline();
	void View_FriendList();
	void View_Page();
	void Add_Memory();
	App()
	{
		User_List = new User * [7];
		User_List[0] = new User[1];
	}
	~App() { delete[]User_List; }
	void Add_User(int capacity, User**& User_List, string name, int ID, int* liked_pages, int likedpages, int* friendss, int numfriends, int Pagenum)
	{
		User** temp = new User * [capacity + 1];
		if (capacity == 0)
		{
			temp[0] = new User(name, ID, liked_pages, likedpages, friendss, numfriends, Pagenum);
		}

		else
		{
			for (int i = 0; i < capacity; i++)
			{
				temp[i] = User_List[i];
			}
			temp[capacity] = new User(name, ID, liked_pages, likedpages, friendss, numfriends, Pagenum);
			if (User_List)
			{
				delete[] User_List;
			}
		}
		User_List = temp;
	}
};

void App::set_User()
{
	cout << "Welcome to Social Media!\nWhat user would you like to access the app through?\n";
	do
	{
		cin >> currentUser;
	} while (currentUser < 0 || currentUser > userTotal);
	set_page(currentUser);

}

void App::set_page(int user)
{
	cout << "\nPages: \n";
	for (int i = 0; i < User_List[user - 1][0].pagenum; i++)
	{
		cout << ((User_List[user - 1][0].owned_Pages[i][0].ID) % 10);
		cout << "." << User_List[user - 1][0].owned_Pages[i][0].Title;
		cout << endl;
	}
	cout << endl << "Page choice: ";
	do
	{
		cin >> currentpage;
	} while (currentpage < 0 || currentpage > User_List[user - 1][0].pagenum);
	cout << endl;
}

void App::Input()
{
	fstream data;
	data.open("E:\\university resorces\\VS community\\2nd semester\\OOP project social media\\User1.txt");
	if (!data)
	{
		cout << "File1 not open\n";
	}
	else
	{
		data >> userTotal;
		InputData(data, 1);
	}

	data.open("E:\\university resorces\\VS community\\2nd semester\\OOP project social media\\User2.txt");
	if (!data) { cout << "File2 not open\n"; }
	else { InputData(data, 2); }
	

	data.open("E:\\university resorces\\VS community\\2nd semester\\OOP project social media\\User3.txt");
	if (!data) { cout << "File3 not open\n"; }
	else { InputData(data, 3); }
	

	data.open("E:\\university resorces\\VS community\\2nd semester\\OOP project social media\\User4.txt");
	if (!data) { cout << "File4 not open\n"; }
	else { InputData(data, 4); }
	

	data.open("E:\\university resorces\\VS community\\2nd semester\\OOP project social media\\User5.txt");
	if (!data) { cout << "File5 not open\n"; }
	else { InputData(data, 5); }
	

	data.open("E:\\university resorces\\VS community\\2nd semester\\OOP project social media\\User6.txt");
	if (!data) { cout << "File6 not open\n"; }
	else { InputData(data, 6); }
	

	data.open("E:\\university resorces\\VS community\\2nd semester\\OOP project social media\\User7.txt");
	if (!data) { cout << "File7 not open\n"; }
	else { InputData(data, 7); }
	
}

void App::InputData(fstream& data, int currentUser)
{
	int userID = 0, numlikedpages = 0, numfriends = 0, pageNum = 0, capacity = 0, pagenum = 0;
	string userName = " ";

	// user block
	data >> userID;
	data >> userName;
	data >> numfriends;
	int* friendss = new int[numfriends];
	for (int i = 0; i < numfriends; i++)
	{
		data >> friendss[i];
	}

	data >> numlikedpages;
	int* likedpages = new int[numlikedpages];
	for (int i = 0; i < numlikedpages; i++)
	{
		data >> likedpages[i];
	}
	data >> pagenum;

	Add_User(currentUser - 1, User_List, userName, userID, likedpages, numlikedpages, friendss, numfriends, pagenum);

	// page block

	int postnum = 0, likes = 0;
	for (int i = 0; i < pagenum; i++)
	{
		int id = 0, owner = 0;
		int* Postss = 0;
		string title = " ";
		data >> id;
		data >> owner;
		getline(data, title, ';');
		data >> postnum;
		Postss = new int[postnum];
		for (int j = 0; j < postnum; j++) { data >> Postss[j]; }
		data >> likes;
		User_List[currentUser - 1][0].Add_Page(i, id, owner, title, likes, Postss, postnum, i, pagenum);

		// post block

		for (int j = 0; j < postnum; j++)
		{
			int id1 = 0, activitytype = 0, likes = 0, comments = 0, date = 0, month = 0, year = 0;
			int* likedpeople = 0;
			int* commentpeople = 0;
			string title1 = " ", activityvalue = " ";
			data >> id1;
			getline(data, title1, ';');
			data >> activitytype;
			data >> activityvalue;
			data >> likes;
			likedpeople = new int[likes];
			for (int k = 0; k < likes; k++) { data >> likedpeople[k]; }
			data >> date;
			data >> month;
			data >> year;
			data >> comments;
			commentpeople = new int[comments];
			for (int l = 0; l < comments; l++)
			{
				data >> commentpeople[l];
			}

			User_List[currentUser - 1][0].owned_Pages[i][0].Add_post(j, postnum, id1, title1, likes, likedpeople, comments, activitytype, activityvalue, date, month, year);

			// comment block

			for (int k = 0; k < comments; k++)
			{
				int id2 = 0, page_id = 0, post_id = 0;
				string title2 = " ";

				data >> id2;
				data >> page_id;
				data >> post_id;
				getline(data, title2, ';');

				User_List[currentUser - 1][0].owned_Pages[i][0].Timeline[j][0].Add_Comment2(k, id2, page_id, post_id, title2);
			}

			delete[]likedpeople;
		}

		delete[]Postss;
	}

	delete[]friendss;
	delete[]likedpages;
	data.close();
}

void App::print_Comment(int usernum, int pagenum, int postnum, int commentnum)
{
	cout << "                 " << User_List[(User_List[usernum][0].owned_Pages[pagenum][0].Timeline[postnum][0].Comments[commentnum][0].User_ID) - 1][0].name << " wrote: ";
	cout << User_List[usernum][0].owned_Pages[pagenum][0].Timeline[postnum][0].Comments[commentnum][0].Text << endl;
}

void App::print_Post(int usernum, int pagenum, int postnum)
{
	if ((User_List[usernum][0].owned_Pages[pagenum][0].Timeline[postnum][0].ActivityType) != 0)
	{
		string activity = " ";
		if ((User_List[usernum][0].owned_Pages[pagenum][0].Timeline[postnum][0].ActivityType) == 1)
			activity = "feeling ";
		else if ((User_List[usernum][0].owned_Pages[pagenum][0].Timeline[postnum][0].ActivityType) == 2)
			activity = "thinking about ";
		else if ((User_List[usernum][0].owned_Pages[pagenum][0].Timeline[postnum][0].ActivityType) == 3)
			activity = "making ";
		else if ((User_List[usernum][0].owned_Pages[pagenum][0].Timeline[postnum][0].ActivityType) == 4)
			activity = "celebrating ";

		cout << "\n----- " << User_List[User_List[usernum][0].owned_Pages[pagenum][0].Owner - 1][0].name;
		cout << " is " << activity << User_List[usernum][0].owned_Pages[pagenum][0].Timeline[postnum][0].ActivityValue;
	}
	cout << User_List[usernum][0].owned_Pages[pagenum][0].Timeline[postnum][0].Description << "....." << User_List[usernum][0].owned_Pages[pagenum][0].Timeline[postnum][0].PublishDate.Day << "/" << User_List[usernum][0].owned_Pages[pagenum][0].Timeline[postnum][0].PublishDate.Month << "/" << User_List[usernum][0].owned_Pages[pagenum][0].Timeline[postnum][0].PublishDate.Year << "\n\n";
	//printing comments
	for (int j = 0; j < User_List[usernum][0].owned_Pages[pagenum][0].Timeline[postnum][0].Commentnum; j++)
	{
		print_Comment(usernum, pagenum, postnum, j);
	}
	cout << endl;
}

void App::print_Page(int usernum, int pagenum)
{
	cout << User_List[User_List[usernum][0].owned_Pages[pagenum][0].Owner - 1][0].name << "'s Page: ";
	cout << User_List[User_List[usernum][0].owned_Pages[pagenum][0].Owner - 1][0].owned_Pages[pagenum][0].Title << "\n                                                   --------- Timeline --------- \n";
	for (int i = 0; i < User_List[usernum][0].owned_Pages[pagenum][0].Postnum; i++)
	{
		print_Post(usernum, pagenum, i);
	}
}

void App :: View_Home(int usernum, int currentd, int currentm)
{
	//printing friend's posts
	for (int i = 0; i < User_List[usernum][0].friends_size; i++)
	{
		for (int j = 0; j < User_List[User_List[usernum][0].friends[i] - 1][0].pagenum; j++)
		{
			for (int k = 0; k < User_List[User_List[usernum][0].friends[i] - 1][0].owned_Pages[j][0].Postnum; k++)
			{
				int day = User_List[User_List[usernum][0].friends[i] - 1][0].owned_Pages[j][0].Timeline[k][0].PublishDate.Day;
				int month = User_List[User_List[usernum][0].friends[i] - 1][0].owned_Pages[j][0].Timeline[k][0].PublishDate.Month;
				if ( (day == currentd - 1 || day == currentd) && currentm == month)
				{
					int user = User_List[User_List[usernum][0].friends[i] - 1][0].ID - 1;
					int page = ((User_List[User_List[usernum][0].friends[i] - 1][0].owned_Pages[j][0].ID) % 10) - 1;
					int post = User_List[User_List[usernum][0].friends[i] - 1][0].owned_Pages[j][0].Timeline[k][0].ID - 1;
					print_Post(user, page, post);
				}
			}
		}
	}

	//printing liked pages' posts
	for (int i = 0; i < User_List[usernum][0].liked_Pages_size; i++)
	{
		for (int j = 0; j < User_List[(User_List[usernum][0].liked_Pages[i] / 10) - 1][0].pagenum; j++)
		{
			for (int k = 0; k < User_List[(User_List[usernum][0].liked_Pages[i] / 10) - 1][0].owned_Pages[j][0].Postnum; k++)
			{
				int day = User_List[(User_List[usernum][0].liked_Pages[i] / 10) - 1][0].owned_Pages[j][0].Timeline[k][0].PublishDate.Day;
				int month = User_List[(User_List[usernum][0].liked_Pages[i] / 10) - 1][0].owned_Pages[j][0].Timeline[k][0].PublishDate.Month;
				if ((day == currentd - 1 || day == currentd) && currentm == month)
				{
					int user = User_List[(User_List[usernum][0].liked_Pages[i] / 10) - 1][0].ID - 1;
					int page = ((User_List[(User_List[usernum][0].liked_Pages[i] / 10)- 1][0].owned_Pages[j][0].ID) % 10) - 1;
					int post = User_List[(User_List[usernum][0].liked_Pages[i] / 10)- 1][0].owned_Pages[j][0].Timeline[k][0].ID - 1;
					print_Post(user, page, post);
				}
			}
		}
	}
}

void App:: Add_Like()
{
	int user, pagenum, postid;
	cout << "\nEnter the user number, page number and post id you want to like\n";
	cin >> user >> pagenum >> postid;
	int like = User_List[user][0].owned_Pages[pagenum][0].Timeline[postid][0].Likes;
	like++;
	cout << like;
	User_List[user][0].owned_Pages[pagenum][0].Timeline[postid][0].Likes++;
	User_List[user][0].owned_Pages[pagenum][0].Timeline[postid][0].Liked_Users[like - 1] = currentUser;
}

void App:: View_Liked()
{
	int user, pagenum, postid;
	cout << "\nEnter the user number, page number and post id you want to view likes of\n";
	cin >> user >> pagenum >> postid;
	cout << "\nThe following people have liked the post: \n";
	for (int i = 0; i < User_List[user][0].owned_Pages[pagenum][0].Timeline[postid][0].Likes; i++)
	{
		cout << "User " << User_List[user][0].owned_Pages[pagenum][0].Timeline[postid][0].Liked_Users[i] - 1 << " - ";
		cout << User_List[User_List[user][0].owned_Pages[pagenum][0].Timeline[postid][0].Liked_Users[i] - 1][0].name << endl;
	}
}

void App::Addcomment()
{
	int user, pagenum, postid, pagenum1;
	string enter;
	cout << "\nEnter the user number, page number and post id you want to add comment on\n";
	cin >> user >> pagenum >> postid;
	pagenum1 = ((currentUser) * 10) + (currentpage + 1);
	cout << "\nEnter your Comment (add ; at end of comment to terminate input): ";
	getline(cin, enter, ';');
	int commentn = User_List[user][0].owned_Pages[pagenum][0].Timeline[postid][0].Commentnum++;
	cout << commentn;
	User_List[user][0].owned_Pages[pagenum][0].Timeline[postid][0].Add_Comment2(commentn, commentn, pagenum1, postid, enter);
}

void App::View_Post()
{
	int usernum, pagenum, postnum;
	cout << "\nEnter the user number, page number and post id you want to view\n";
	cin >> usernum >> pagenum >> postnum;
	print_Post(usernum, pagenum, postnum);
}

void App::View_Timeline()
{
	for (int i = 0; i < User_List[currentUser - 1][0].pagenum; i++)
	{
		print_Page(currentUser - 1, i);
		cout << "--------------------------------------------------------------------------------------------------------\n";
	}
}

void App::View_FriendList()
{
	int choose = 0;
	cout << "\nEnter the User whose friend list you want to check: ";
	cin >> choose;
	cout << endl;
	cout << "Friends List: \n";
	for (int i = 0; i < User_List[choose - 1][0].friends_size; i++)
	{
		cout << User_List[User_List[choose - 1][0].friends[i] - 1][0].name << endl;
	}
	cout << endl;
}

void App::View_Page()
{
	int usernum = 0, pagenum = 0;
	cout << "\nEnter the user number and page number of user you want to view\n";
	cin >> usernum >> pagenum;
	print_Page(usernum, pagenum);
}

void App::Add_Memory()
{
	int usernum, pagenum, postnum;
	string desc = " ";
	cout << "\nEnter the user number, page number and post id whose memory you want to add\n";
	cin >> usernum >> pagenum >> postnum;
	cout << "Enter the string you want to add\n";
	getline(cin, desc, ';');
	//User_List[usernum][0].owned_Pages[pagenum][0].Timeline[postnum][0].add_memeory(postnum, desc);
}

void App::Run()
{
	Date current(27, 10, 2017);
	int choice = 1;
	int totalchoice = 5;
	while (choice != 0)
	{
		if (choice == 1)
			set_User();
		else if (choice == 2)
			View_Home(currentUser, current.Day, current.Month);
		else if (choice == 3)
			Add_Like();
		else if (choice == 4)
			View_Liked();
		else if (choice == 5)
			Addcomment();
		else if (choice == 6)
			View_Post();
		else if (choice == 7)
			View_Timeline();
		else if (choice == 8)
			View_FriendList();
		else if (choice == 9)
			View_Page();
		else if (choice == 10)
			Add_Memory();


			//View_Home(4, 27, 10);
			/*print_Page(6, 1);
			cout << "--------------------------------------\n";
			print_Post(0, 0, 0);
			cout << "--------------------------------------\n";
			print_Comment(1, 0, 0, 0);
			cout << "--------------------------------------\n";*/

			/*View_Liked(2, 0, 0);
			Add_Like(2, 0, 0);
			View_Liked(2, 0, 0);*/

		cout << "------------------------------------------------------------------------------------------------------------------------\n";

		cout << "\n-------------------------------------------------------\n";
		cout << "\n-   Number List:                                      -\n";
		cout << "-   0. Quit App                                       -\n";
		cout << "-   1. set/change user                                -\n";
		cout << "-   2. View Home                                      -\n";
		cout << "-   3. Add like to post                               -\n";
		cout << "-   4. View the users that liked a post               -\n";
		cout << "-   5. Add a comment                                  -\n";
		cout << "-   6. View a post                                    -\n";
		cout << "-   7. View Timeline                                  -\n";
		cout << "-   8. View Friends list                              -\n";
		cout << "-   9. View a page                                    -\n";
		cout << "-   10. Add a memory                                  -\n";
		cout << "\n-------------------------------------------------------\n";

		cout << "\nEnter Command no.: ";
		cin >> choice;

		cout << "------------------------------------------------------------------------------------------------------------------------\n";
	}
}

int main()
{
	App A1;
	system("color 5F");
	A1.Input();
	A1.Run();
	return 0;
}