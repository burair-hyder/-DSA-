#include <iostream>
using namespace std;

bool isSorted(int *arr,int n){
	
	if (n==0 || n==1){
		return true;
	}
	
	if (arr[n-1]>= arr[n-2]){
		isSorted(arr,n-1);
	}
	else{
		return false;
	}
}
int main(){
	int arr[] = {2,1};
	cout <<isSorted(arr,2);
	
}
