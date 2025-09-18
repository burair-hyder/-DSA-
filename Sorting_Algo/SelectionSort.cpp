#include <iostream>
using namespace std;


void selectionSort(int arr[],int size){
	
	
	for (int i=0;i<size-1;i++){
		int smallestIdx =i;// assume smallest is the first element of unsorted part
		
		for (int j=i+1;j<size;j++){
			
			if (arr[j]<arr[smallestIdx]){
				smallestIdx =j;
			}
		}
		
		int temp;
		temp = arr[i];
		arr[i] = arr[smallestIdx];
		arr[smallestIdx] = temp;
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
	selectionSort(arr,n);

	printArray(arr,n);
	
	return 0;
	
	
}
