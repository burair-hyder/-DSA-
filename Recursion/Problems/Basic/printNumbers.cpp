#include <iostream>
using namespace std;


void printNum(int n){
	
	if (n==1){
		cout <<1<<endl;
		return;
	}
	cout <<n<<" ";
	printNum(n-1);
}
int main(){
	
	printNum(6);
	
}
