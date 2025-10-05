// no extra space used,only single array manipulated!

#include <iostream>
using namespace std;


void permu(int *arr, int n,int i){
	
	if (i==n){
		
		for (int j=0;j<n;j++){
			cout <<arr[j]<<" ";
		}
		cout <<endl;
		return ;
	}	
	for (int x=i;x<n;x++){
		swap (arr[i],arr[x]);
		permu(arr,n,i+1);
		swap (arr[i],arr[x]);
		
	}
}

int main(){
	int arr[] ={1,2,3};
	int *ans  = new int[3];
	bool used[] ={false,false,false};
	
	permu(arr,3,0);
}
