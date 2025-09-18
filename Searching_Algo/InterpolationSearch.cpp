#include <iostream>
using namespace std;

int interpolationSearch(int array[],int size,int x){
	int low = 0 ;
	int high = size - 1 ;
	while(low<=high&&x>=array[low]&&x<=array[high]){
		if(low==high){
			if(array[low]==x){
				return low ;
			}
			return -1;
		}
		int pos = low + ((x-array[low])*(high-low)) / (array[high]-array[low]) ;
		if(array[pos] == x) return pos ;
		if(array[pos]<x) low = pos + 1 ;
		else high = pos - 1 ;
	}
	return -1 ; 
}
void InsertionSort(int arr[],int size){
	
	int curr;  
	int prev;
	
	
	for(int i=1;i<size;i++){
		curr= arr[i];  
		prev= i-1; 
		
		while(prev>=0 && arr[prev]>curr){ 
			arr[prev+1] = arr[prev]; 
			
			prev--;
		
		}
		
		arr[prev+1] = curr; 
		
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
	int tofind;
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
	
	cout <<"Enter Value to Search:";
	cin >>tofind;
	
	int index =interpolationSearch(arr,n,tofind);
	
	if (index!=-1){
		cout <<"Value found at index :"<<index<<endl;
	}
	else {
		cout <<"Value Not Found in the Array."<<endl;
	}
	
	
	return 0;
	
	
}
