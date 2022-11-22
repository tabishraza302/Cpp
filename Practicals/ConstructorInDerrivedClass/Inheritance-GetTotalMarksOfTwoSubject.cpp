#include<iostream>

using namespace std;

class Subject1 {
	public:
		int m1;
	
};

class Subject2 {
	public:
		int m2;
};

class Result: public Subject1, public Subject2 {
	public:
		
		void getMarks() {
			cout<<"Enter marks for Subject 1: ";
			cin>>m1;
			cout<<"Enter marks for subject 2: ";
			cin>>m2;
		}
		

		
		void showResult() {
			int total = m1 + m2;
			cout<<"Total marks = "<<total;
		}
};

int main() {
	Result r;
	r.getMarks();
	r.showResult();
	
	return 0;
}
