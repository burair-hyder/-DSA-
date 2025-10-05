#include <iostream>
using namespace std;


void printSubset(char *arr,char *ans , int n,int i,char** power){
	static int x=0; 
		if (i == n) {
        	power[x] = new char[n]; 
			int y=0;      
        	for (int j=0;j<n;j++){
        		if (ans[j]!=' ')
        		power[x][y]=ans[j];
        		y++;
			}      
        		x++;
       	
        	return;
    }
	
	ans[i] = arr[i];
	
	printSubset(arr,ans,n,i+1,power);
	
	ans[i]=' ';
	printSubset(arr,ans,n,i+1,power);
	
	
}

int main(){
	char ** power = new char*[8];
	char arr[] = {'1','2','3'};
	char *ans = new char[3];
	printSubset(arr,ans,3,0,power);
	
	
	for (int i=0;i<8;i++){
		cout <<"[";
		for (int  j=0;j<3;j++){
			cout <<power[i][j] <<" ";
		}
		cout <<"]";
	}
	
}
