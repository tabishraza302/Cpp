#include<iostream>
#include<cstdlib>
#include<string>
#include<fstream>
#include<iostream>
// #include<json/json.h>

using namespace std;

class User {
	public: 
		string username, email, name;
		int pin, balance;
		
		void create() {
			system("cls");
			
			cout<<"Creating Account..."<<endl;
			cout<<"Enter username: ";
			cin>>username;
			cout<<"Enter email: ";
			cin>>email;
			cout<<"Enter name: ";
			cin>>name;
			cout<<"Enter pin: ";
			cin>>pin;
			
			// ofstream users("test.json")
			// users.close();
		}
};

int main() {
	User u;
	u.create();
	
	return 0;
}
