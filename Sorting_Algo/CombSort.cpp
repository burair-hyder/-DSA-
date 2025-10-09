#include <iostream>
using namespace std;


void combsort(int *arr,int n){
	
	int gap =n;
	bool noswap = false;
	
	while (gap!=1 && noswap==false){
		
		gap = gap/1.3;
		if (gap<1){
			gap =1;
		}
		noswap = true;
		
		for (int i=0;i+gap<n;i++){
			
			if (arr[i]>arr[i+gap]){
				swap(arr[i],arr[i+gap]);
				noswap =false;
			}
		}
		
	}
}

int main(){
	
	int arr[] ={4,10,50,0,-1};
	combsort(arr,5);
	
	for (int i=0;i<5;i++){
		cout <<arr[i]<<" ";
	}
}
