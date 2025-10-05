#include <iostream>
using namespace std;


void Permu(int *arr,int * ans,bool * used, int n , int i){
	
	if (i==n){
		for (int  i=0;i<n;i++){
			cout <<ans[i]<<" ";
		}
		cout <<endl;
		return;
	}
	
	for (int x=0;x<n;x++){
		if (used[x]==false){
			ans[i] = arr[x];
			used[x]=true;
			Permu(arr,ans,used,n,i+1);
			ans[i]=-1;
			used[x]=false;
		}
	}
}

int main(){
	int arr[] ={1,2,3};
	int *ans  = new int[3];
	bool used[] ={false,false,false};
	
	Permu(arr,ans,used,3,0);
}
