#include <iostream>
using namespace std;

void merge(int *arr,int start,int mid,int end){
	
	int temp[end-start+1];
	int index=0;
	int i=start;
	int j=mid+1;
	
	while (i<=mid && j<=end){
		
		if (arr[i]<arr[j]){
			temp[index]=arr[i];
			i++;
			index++;
		}
		else{
			temp[index]=arr[j];
			j++;
			index++;
		}
	}
	
	while (i<=mid){
		temp[index]=arr[i];
			i++;
			index++;
	}
	
	while (j<=end){
		temp[index]=arr[j];
		j++;
		index++;
		
	}
	
	for (int idx=0;idx<(end-start+1);idx++){
		arr[start+idx]=temp[idx];
		
	}
}

void mergeSort(int * arr,int start,int end ){
	
	if (start<end){
		int mid = start + (end-start)/2;
		mergeSort(arr,start,mid);
		mergeSort(arr,mid+1,end);
		merge(arr,start,mid,end);
	}
}

int main(){
	int arr[] = {50,40,30,20,10,-10};
	
	mergeSort(arr,0,5);
	
	for (int i=0;i<6;i++){
		cout <<arr[i] <<" ";
	}
	cout <<endl;
}
