#include <iostream>
using namespace std;



void InsertionSort(int arr[],int size){
	
	int curr;  
	int prev;
	
	
	for(int i=1;i<size;i++){
		curr= arr[i];  // the first element of unsorted part
		prev= i-1; // end of sorted part
		
		while(prev>=0 && arr[prev]>curr){ 
			arr[prev+1] = arr[prev]; // shift towards right the greater values in sorted part
			// to get to the correct index for current value
			prev--;
			// move backwards for comparsion 
		}
		
		arr[prev+1] = curr; // place the current value in the correct position
		
	}
	
	
}
void printArray(int arr[],int size){
	
	for (int i=0;i<size;i++){
		cout <<arr[i]<<" ";
	
	}
	cout <<endl;
}
int main(){
	
	int n;
	int *arr;
	cout <<"How many Values to Store in Array :";
	cin  >>n;
	
	arr=  new int[n];
	
	for(int i=0;i<n;i++){
		cout <<"Enter Value "<<i+1<<": ";
		cin >>arr[i];
	}
	
	cout <<"Unsorted Array:"<<endl;
	printArray(arr,n);

	cout <<"Sorted Array:"<<endl;
	InsertionSort(arr,n);

	printArray(arr,n);
	
	return 0;
	
	
}
