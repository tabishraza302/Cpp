#include<iostream>

using namespace std;

class Alpha {
	public:
		int x;
		
		Alpha(int i) {
			x = i;
			cout<<"Alpha constructor initialized"<<endl;
		}
		
		void show_x() {
			cout<<"X = "<<x<<endl;
		}
};

class Beta {
	public: 
		float y;
		
		Beta(float j) {
			y = j;
			cout<<"Beta constructor initialized"<<endl;
		}
		
		void show_y() {
			cout<<"Y = "<<y<<endl;
		}
};

class Gamma : public Alpha, public Beta{
	public:
		int s, t;
//		int a, c, d;
//		float b;
		Gamma(int a, float b, int c, int d):Alpha(a), Beta(b){
			s = c;
			t = d;
			cout<<"Gamma constructor initialized"<<endl;
		}
		
		void show() {
			cout<<"S = "<<s<<endl;
			cout<<"T = "<<t<<endl;;
		}
};

int main() {
	Gamma g(10, 20.4, 30, 40);
	g.show_x();
	g.show_y();
	g.show();
}
