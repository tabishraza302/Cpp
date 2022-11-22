#include<iostream>

using namespace std;

int main() {
	int arr[5] = {1,2,3,4,5};
	int *ptr = arr;
	
	int i;
	for ( i = 0; i < 5; i++) {
		cout<<ptr[i]<<endl;
	}
	
	return 0;
}
