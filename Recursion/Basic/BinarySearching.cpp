#include <iostream>
using namespace std;

int recBinarySearch(int *arr,int target,int start,int end){
	
	if (start <end){
		
		int mid = (start+end)/2;
		if (arr[mid]== target){
			return mid;
		}
		else if (arr[mid]<target){
			return recBinarySearch(arr,target,mid+1,end);
		}
		else{
			return  recBinarySearch(arr,target,start,mid-1);
		}
	}
	return -1;
}
int main(){
	int arr[] = {1,5,10,16,170,2021};
		cout <<recBinarySearch(arr,2,0,5);
	
}
