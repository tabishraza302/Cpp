#include<iostream>

using namespace std;

class Test {
	public:
		int a, b, c;
		
		void input( int x, int y, int z) {
			a = x;
			b = y;
			c = z;
		}
		
		void display() {
			cout<<"A = "<<a;
			cout<<"B = "<<b;
			cout<<"C = "<<c;
		}
		
		void operator -- () {
			a = --a;
			b = --b;
			c = --c;
		}
};

int main() {
	Test t;
	
	t.input(10, 20, 30);
	--t;
	t.display();
	
	return 0;
}

