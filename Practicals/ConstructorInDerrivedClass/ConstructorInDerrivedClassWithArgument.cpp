#include<iostream>

using namespace std;

class Base {
	public:
		int a;
		
		Base(int b) {
			a = b;
		}
		
		void show_a () {
			cout<<"A = "<<a;
		}
};

class Derrived: public Base {
	public:
		int b;
		
		Derrived(int x, int y): Base(x) {
			b = y;
		}
		
		void show_b() {
			cout<<"B = "<<b;
		}
};

int main() {
	Derrived d(30, 40);
	d.show_a();
	d.show_b();
	
	
	return 0;
}
