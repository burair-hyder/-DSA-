#include <iostream>
using namespace std;


int interpolationSearch(int arr[],int size,int tofind){
	
	int low=0;
	int high=size-1;
	
	while (low<=high && tofind >=arr[low] && tofind <= arr[high]){
		
		if (high==low){
			if (arr[low]==tofind){
				return low;
			}
			else{
				return -1;
			}
		}
		
		
	int mid = low + ((high-low)/(arr[high]-arr[low])) * (tofind - arr[low]);
	
		if (arr[mid]==tofind){
			return mid;
		}
		else if (tofind > arr[mid]){
			low = mid+1;  
		}
		else {
			high = mid-1;
		}
	}
}

int main(){
	
		int arr[] = {2,4,6,8,10,12,14,16,18};
	
	int size =9;
	
	int tofind = 10;
	
	int res=  interpolationSearch(arr,size,tofind);
	cout <<res;
}
