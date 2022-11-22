#include <iostream>
#include<mysql.h>         //these libraries were added by including folders to project option
#include<mysqld_error.h>  //and this particularly,when pasting the ".dill" to the project folder.
#include<sstream>
#include<limits>

using namespace std;

void showOptions(MYSQL* conn);

// Database details
char HOST[] = "localhost";
char USER[] = "root";
char PASS[] = "password";

// Login details
int isLoggedIn = 0; // Login status: 0 = Not Logged In, 1 = Logged In
string userId; // Logged in user id

class User {
	int balance = 0, pin, amount, qstate = 0;
	string username, fullName;
	
	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res;
	
	stringstream ss;
	
	public: 
		// Contructor		
		User(MYSQL* con) {
			conn = con; // Databse connection
		}
	
		// Taking user detail and creating user in database	
		void create() {
			system("cls");
			cout<<"Creating user Accout... \n\n";
			
			cin.ignore(); // To clear unprocessed and remaining buffer which include "\n"
			cout<<"Enter Name: ";
			getline(cin, fullName);
			
			cout<<"Enter username: ";
			cin>>username;
			
			cout<<"Create security pin: ";
			cin>>pin;
			
			system("cls");
			cout<<"Inserting user to databse..."<<endl;
				
			ss<<"INSERT INTO users(fullname, username, pin, balance) values('"<<fullName<<"','"<<username<<"','"<<pin<<"', '"<<"0');";
			string querry = ss.str();
			const char* q = querry.c_str();
			qstate = mysql_query(conn, q);
	
			if(qstate) {
				cout<<"Failed to create user..."<<endl;
				cout<<"\n\n";
				return; 
			} else {
				cout<<"User Created!"<<endl;	
			}
			cout<<"\n\n";
		}
		
		// Login functionality
		void login() {
			system("cls");
						
			cout<<"Enter username: ";
			cin>>username;
			cout<<"Enter pin: ";
			cin>>pin;
			
			cout<<"Checking login details..."<<endl;
			
			ss<<"SELECT id FROM users WHERE username='"<<username<<"' AND pin = "<<pin<<";";
			string querry = ss.str();
			const char* q = querry.c_str();
			qstate = mysql_query(conn, q);
		
			if(qstate) {
				cout<<"Failed to check details... Please check database conneciton."<<endl;				
				cout<<"\n\n";
				return;
			}else {
				res = mysql_store_result(conn);
				row=mysql_fetch_row(res);
				
				if(!row) {
					cout<<"Invalid login details!";
					cout<<"\n\n";
					return;
				} else {
					userId = row[0];
					isLoggedIn = 1;
				}
				cout<<"\n\n";
			}
		}
		
		//	Add fund to user balance	
		void deposit() {
			system("cls");		
				
			cout<<"Enter an amount to deposit: ";
			cin>>amount;
			
			cout<<"Depositing amout..."<<endl;
			
			// Fetching old balance
			{		
				ss<<"SELECT balance FROM users WHERE id = "<<userId<<";";
				string querry = ss.str();
				const char* q = querry.c_str();
				qstate = mysql_query(conn, q);
				
				if(qstate) {
					cout<<"Error fetching details"<<endl;
					cout<<"\n\n";
					return;
				}else {
					res = mysql_store_result(conn);
					row = mysql_fetch_row(res);
					
					if(row) {
						cout<<"Your old balance: "<<row[0]<<endl;
					}else {
						cout<<"Something went wrong!"<<endl;
						cout<<"\n\n";
						return;
					}
				}			
			}
			
			// Updating balance	
			{
				ss.str(""); // Clearing variable for further uses		
				ss<<"UPDATE users SET balance = balance + "<<amount<<" WHERE id = "<<userId<<";";
				string querry = ss.str();
				const char* q = querry.c_str();
				qstate = mysql_query(conn, q);
				
				if(qstate) {
					cout<<"Failed to update balance"<<endl;
					cout<<"\n\n";
					return; 
				} else {
					cout<<"Fund added successfully"<<endl;
				}
			}
			
			// Adding transaction details
			{
				ss.str("");
				ss<<"INSERT INTO transactions(userid, amount, type) VALUES ("<<userId<<", "<<amount<<", 'deposit');";
				string querry = ss.str();
				const char* q = querry.c_str();
				qstate = mysql_query(conn, q);
				
				if(qstate) {
					cout<<"Failed to update transations"<<endl;
					cout<<"\n\n";
					return; 
				} else {
					cout<<"Transaction details added"<<endl;
				}
			}
			
			// Fetching updated balance
			{
				ss.str(""); // Clearing stringstream variable for further uses
				ss<<"SELECT balance FROM users WHERE id = "<<userId<<";";
				string querry = ss.str();
				const char* q = querry.c_str();
				qstate = mysql_query(conn, q);
				
				if(qstate) {
					cout<<"Error fetching details"<<endl;
					cout<<"\n\n";
					return;
				}else {
					res = mysql_store_result(conn);
					row = mysql_fetch_row(res);
						
					if(row) {
						cout<<"Your new balance: "<<row[0]<<endl;
					}else {
						cout<<"Something went wrong!"<<endl;
						cout<<"\n\n";
						return;
					}
				}
			}
			
			cout<<"\n\n";
		}
		
		//	Withdraw fund from user balance	
		void withdraw() {
			system("cls");		
				
			cout<<"Enter an amount to withdraw: ";
			cin>>amount;
			
			cout<<"Withdrawing amout..."<<endl;
			
			// Fetching old balance
			{		
				ss<<"SELECT balance FROM users WHERE id = "<<userId<<";";
				string querry = ss.str();
				const char* q = querry.c_str();
				qstate = mysql_query(conn, q);
				
				if(qstate) {
					cout<<"Error fetching details"<<endl;
					cout<<"\n\n";
					return;
				}else {
					res = mysql_store_result(conn);
					row = mysql_fetch_row(res);
					
					if(row) {
						cout<<"Your old balance: "<<row[0]<<endl;
					}else {
						cout<<"Something went wrong!"<<endl;
						cout<<"\n\n";
						return;
					}
				}
			}
			
			// Updating balance	
			{
				ss.str(""); // Clearing variable for further uses		
				ss<<"UPDATE users SET balance = balance - "<<amount<<" WHERE id = "<<userId<<";";
				string querry = ss.str();
				const char* q = querry.c_str();
				qstate = mysql_query(conn, q);
				
				if(qstate) {
					cout<<"Failed to withdraw... "<<endl;
					cout<<"\n\n";
					return; 
				} else {
					cout<<"Withdrawn money successfully"<<endl;	
				}
			}
			
			// Adding transaction details
			{
				ss.str("");
				ss<<"INSERT INTO transactions(userid, amount, type) VALUES ("<<userId<<", "<<amount<<", 'withdraw');";
				string querry = ss.str();
				const char* q = querry.c_str();
				qstate = mysql_query(conn, q);
				
				if(qstate){
					cout<<"Failed to update transations"<<endl;
					cout<<"\n\n";
					return;
				}else {
					cout<<"Transaction details added"<<endl;
				}
			}
			
			// Fetching updated balance
			{
				ss.str(""); // Clearing stringstream variable for further uses
				ss<<"SELECT balance FROM users WHERE id = "<<userId<<";";
				string querry = ss.str();
				const char* q = querry.c_str();
				qstate = mysql_query(conn, q);
				
				if(qstate) {
					cout<<"Error fetching details"<<endl;
					cout<<"\n\n";
					return;
				}else {
					res = mysql_store_result(conn);
					row = mysql_fetch_row(res);
						
					if(row) {
						cout<<"Your new balance: "<<row[0]<<endl;
						cout<<"\n\n";
					}else {
						cout<<"Something went wrong!"<<endl;
						cout<<"\n\n";
						return;
					}
				}
			}
		}	
		
		
		//	Transfer fund from one user to another user account	
		void transferFund()	{
			system("cls");
			
			int amount, account;
			
			cout<<"Transfering fund!"<<endl;
			
			cout<<"Enter amout you want to transfer: ";
			cin>>amount;
			cout<<"Enter account no to which you want to transfer: ";
			cin>>account;
			
			// Adding balance to reciever account			
			{		
				cout<<"Adding balance to reciever account..."<<endl;
				ss.str(""); // Clearing stringstream variable for further uses
				ss<<"UPDATE users SET balance = balance + "<<amount<<" WHERE id = "<<account<<";";
				string querry = ss.str();
				const char* q = querry.c_str();
				qstate = mysql_query(conn, q);
				
				if(qstate){
					cout<<"Failed to add balance to reciver account!"<<endl;
					cout<<"\n\n";
					return;
				}else {
					cout<<"Balance added to reciever Account!"<<endl;
				}
			}
			
			// Deducting balance from sender account			
			{
				ss.str(""); // Clearing stringstream variable for further uses
				ss<<"UPDATE users SET balance = balance - "<<amount<<" WHERE id = "<<userId<<";";
				string querry = ss.str();
				const char* q = querry.c_str();
				qstate = mysql_query(conn, q);
				if(qstate){
					cout<<"Failed to deduct balance from sender account!"<<endl;
					cout<<"\n\n";
					return;
				}else {
					cout<<"Balance deducted from sender Account!"<<endl;
					cout<<"\n\n";
				}
			}
		}
		
		// Show users available balance		
		void showBalance() {
			system("cls");
			
			ss.str(""); // Clearing stringstream variable for further uses
			ss<<"SELECT balance from users WHERE id = "<<userId<<";";
			string querry = ss.str();
			const char* q = querry.c_str();
			qstate = mysql_query(conn, q);
			
			if(qstate) {
				cout<<"Error fetching details"<<endl;
				cout<<"\n\n";
				return;
			}else {
				res = mysql_store_result(conn);
				row = mysql_fetch_row(res);
				
				if(row) {
					cout<<"Total balance: "<<row[0]<<endl;
					cout<<"\n\n";
				}else {
					cout<<"Something went wrong!"<<endl;
					cout<<"\n\n";
					return;
				}
			}
		}
		
		
		//	Get all transaction details of logged in user	
		void getAllTransactions() {
			system("cls");
			
			ss.str(""); // Clearing stringstream variable for further uses
			ss<<"SELECT * FROM transactions WHERE userid = "<<userId<<" ORDER BY id DESC;";
			string querry = ss.str();
			const char* q = querry.c_str();
			qstate = mysql_query(conn, q);
			
			if(qstate) {
				cout<<"Error fetching transaction details...";
				cout<<"\n\n";
				return;
			}else {
				res = mysql_store_result(conn);
				int count = mysql_num_fields(res);
				cout<<"All transaction details: "<<endl<<endl;
				cout<<'\t'<<"Id"<<'\t'<<"UserId"<<'\t'<<"Amount"<<'\t'<<"Time"<<'\t'<<'\t'<<'\t'<<"Type"<<endl<<endl;
				while(row = mysql_fetch_row(res)) {
					for(int i =0; i<count; i++) {
						cout<<"\t"<<row[i];
					}
					cout<<endl;
				}
				cout<<"\n\n";
			}
		}
		
		//	Logout user
		void logout() {
			isLoggedIn = 0;
			userId = "";
		}
		
		
		// This option is included here on purpose in world program it is not a good practice to
		// allow normal users to access database of all other users as they can get get username 
		// and password of other users which is considered as the breach of data and could lead to 
		// misuse of data...
		
		void getAllUsers() {
			system("cls");
			
//			MYSQL_ROW row;
//			MYSQL_RES* res;
			
			qstate = mysql_query(conn, "SELECT * FROM users;");
			if(!qstate) {
				res = mysql_store_result(conn);
				int count = mysql_num_fields(res);
				cout<<"All users detail: \n";
				while(row = mysql_fetch_row(res)) {
					for(int i =0; i<count; i++) {
						cout<<"\t"<<row[i];
					}
					cout<<endl;
				}
				cout<<"\n\n";
			}
		}
};

// Showing option to user
void showOptions(MYSQL* conn) {
	int choice;
	
	if(isLoggedIn) {
		cout<<"1. Deposit"<<endl;
		cout<<"2. Withdraw"<<endl;
		cout<<"3. Transfer Fund"<<endl;
		cout<<"4. Show Balance"<<endl;
		cout<<"5. Show transactions"<<endl;
		cout<<"6. Logout"<<endl;
	}else {
		cout<<"1. Create accout"<<endl;
		cout<<"2. Login"<<endl;
	}
	
	cout<<endl;
	cout<<"Select an option: ";
	cin>>choice;
	
	//	Objects
	User user(conn);
	
	if(isLoggedIn) {
		switch (choice){
			case 1:		
				user.deposit();
				showOptions(conn);
				break;
				
			case 2:
				user.withdraw();
				showOptions(conn);
				break;
				
			case 3:
				user.transferFund();
				showOptions(conn);
				break;
			
			case 4:
				user.showBalance();
				showOptions(conn);
				break;
				
			case 5:
				user.getAllTransactions();
				showOptions(conn);
				break;

			case 6:
				user.logout();
				showOptions(conn);
				break;
				
			default:
				cout<<"Select a valid option"<<endl<<endl;
				showOptions(conn);
				break;
		}
	} else {
		switch (choice){
			case 1:		
				user.create();
				showOptions(conn);
				break;
				
			case 2:
				user.login();
				showOptions(conn);
				break;
				
			default:
				cout<<"Select a valid option"<<endl<<endl;
				showOptions(conn);
				break;
		}
	}
}

int main() {
	//	Connecting to database
	cout<<"Connecting to database"<<endl;
	MYSQL* conn;
	conn = mysql_init(0);
	conn = mysql_real_connect(conn, HOST, USER, PASS, "bank", 3306, NULL, 0);
	
	if(!conn){
		cout<<"Error connecting to databse or database doesn't exist'"<<endl;
	} else {
		cout<<"Connected to database! enjoy... \n\n";
	}
	
	showOptions(conn);	
	     
	return 0;
}
