#include<iostream>
#include<cmath>

using namespace std;

class Abc {
	public:
		
		void add(int n) {
			int i = n, iSum = 0;
			while (i < (n + 10)) {
				iSum = iSum + i;
				i++;
			}
			
			cout<<"Total added integer : "<<iSum<<endl;
		}
		
		void add(double n) {
			int i = abs(n);
			double fsum;
			while(i < (abs(n) + 5)) {
				fsum = fsum + i;
				i++;
			}
			
			cout<<"Total added flaot : "<<fsum<<endl;
		}
};

int main() {
	Abc a;
	
	a.add(1);
	a.add(1.5);
	
	return 0;
}
