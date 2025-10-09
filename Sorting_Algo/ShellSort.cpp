#include <iostream>
using namespace std;


void shellSort(int *arr,int n){
	
	
	for (int gap =n/2 ; gap>0;gap = gap/2){
		
		for (int i=gap ; i<n ;i++){
			
			int curr= arr[i];
			int prev = i-gap;
			
			while (prev >=0 && arr[prev]>curr){
				arr[prev+gap] = arr[prev];
				prev = prev- gap;
				 
			}
		arr[prev+gap] = curr;
		}
	}
}

int main(){
	
	int arr[]={5000,0,-1,0,5};
	
	 shellSort(arr,5);
	
	for (int i=0;i<5;i++){
		cout <<arr[i]<<" ";
	}
}
