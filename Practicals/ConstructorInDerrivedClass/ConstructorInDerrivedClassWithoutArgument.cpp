#include<iostream>

using namespace std;

class Base {
	public:
		int a;
		
		Base() {
			a = 10;
		}
		
		void show_a () {
			cout<<"A = "<<a;
		}
};

class Derrived: public Base {
	public:
		int b;
		
		Derrived() {
			b = 20;
		}
		
		void show_b() {
			cout<<"B = "<<b;
		}
};

int main() {
	Derrived d;
	d.show_a();
	d.show_b();
	
	
	return 0;
}
