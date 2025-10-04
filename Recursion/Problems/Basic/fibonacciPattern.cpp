#include <iostream>
using namespace std;

void fibonacci(int n){
	static int x=0;
	static int y=1;
	static int i=0;

	if (n<=2){
		return;
	}
	if (i==0){
		cout<<x<<" ";
		cout <<y<<" ";
		i=2;	 
	}
	
	int sum= x+y;
	cout <<sum<<" ";
	x=y;
	y=sum;
	
	fibonacci(n-1);
	
	

}
int main(){
	fibonacci(7);
	
}
