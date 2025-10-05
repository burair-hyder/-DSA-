#include <iostream>
using namespace std;


void printSubset(char *arr,char *ans , int n,int i){
	
	if (i==n){
		cout <<"[ ";
		for (int i=0;i<n;i++){
				if (ans[i]!=' ')
					 cout <<" "<<ans[i]<<" ";
				
		}
		cout <<"]";
		cout <<endl;
		return ;
	}
	
	ans[i] = arr[i];
	
	printSubset(arr,ans,n,i+1);
	
	ans[i]=' ';
	printSubset(arr,ans,n,i+1);
	
	
}

int main(){

	char arr[] = {'1','2','3'};
	char *ans = new char[3];
	printSubset(arr,ans,3,0);
	
}
