#include <iostream>
using namespace std;

void bubbleSort(int arr[],int size){
	
	int boundary = size-1;
	bool noswaps = false;
	int temp;
	
	while (noswaps==false){
		
		noswaps = true;
		
		for(int i=0;i<boundary;i++){
			
			if (arr[i]>arr[i+1]){
				temp = arr[i+1];
				arr[i+1] = arr[i];
				arr[i] = temp;
				noswaps = false;
			}	
		}
		boundary--;
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
	bubbleSort(arr,n);

	printArray(arr,n);
	
	return 0;
	
	
}
