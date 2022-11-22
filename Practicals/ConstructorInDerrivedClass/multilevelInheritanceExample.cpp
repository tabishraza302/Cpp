#include<iostream>

using namespace std;

class Student {
	public:
		string name = "Abc";
		int rollNo = 123;
};

class Test: public Student {
	public:
		int m1 = 10, m2 = 20;
};

class Result: public Test {
	public:
		int total = m1 + m2;
		
		void getResult () {
			cout<<"Name: "<<name;
			cout<<"Roll no: "<<rollNo;
			cout<<"Total marks = "<<total;
		}
};

int main () {
	Result r;
	r.getResult();
	
	return 0;
}
