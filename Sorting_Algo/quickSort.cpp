#include  <iostream>
using namespace std;


int partition(int *arr,int start,int end){
	
	int idx=start-1;
	int pivot = arr[end];
	
	for (int j=start;j<end;j++){
		if (arr[j]<=pivot){
			idx++;
			swap(arr[j],arr[idx]);
		}
	}
	idx++;
	swap(arr[end],arr[idx]);
	return idx;
}


void quickSort(int *arr,int start, int end){
	
	if (start <end){
		int pivIdx = partition(arr,start,end);
		quickSort(arr,start,pivIdx-1);
		quickSort(arr,pivIdx+1,end);
	}
	
}

int main(){
	int arr[] = {50,40,30,20,10,-10};
	
	quickSort(arr,0,5);
	
	for (int i=0;i<6;i++){
		cout <<arr[i] <<" ";
	}
	cout <<endl;
}
