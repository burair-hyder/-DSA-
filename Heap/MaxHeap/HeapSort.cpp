#include <iostream>
using namespace std;

// for max heap
bool isHeap(int *arr, int n){
	
	for (int i=0;i<=(n-2)/2;i++){
		
		int left = 2*i+1;
		int right = 2*i+2;
		
		// check left
		if (left<n && arr[i]<arr[left]){
			return false;
		}
		if(right<n && arr[i]<arr[right]){
			return false;
		}
	}
	return true;
}


// convert this arr to max heap
// need helper heapify down

void heapify_down(int *arr,int i,int n){
	int l=2*i+1;
	int r=2*i+2;
	int largest =i;
	
	if (l<n && arr[l]>arr[largest]){
			largest = l;
			}
	if(r<n && arr[r]>arr[largest]){
			largest = r;
			}
			
	if (largest != i){
			swap(arr[i],arr[largest]);
			heapify_down(arr,largest,n);
			}
}

void convertTomaxHeap(int *arr, int n){
	
	int lastparent = (n-2)/2;
	
	for (int i=lastparent;i>=0;i--){
		heapify_down(arr,i,n);
	}
}

void heapSort(int *arr, int n ){
	convertTomaxHeap(arr,n);
	for (int i=n-1;i>=1;i--){
		swap(arr[0],arr[i]);
		heapify_down(arr,0,i);  // last element sortedc	
	}
	
}


int main() {
    int arr[] = {0, 7, 6, 5, 4};
    int n = 5;

    cout << "Original array: ";
    for(int i = 0; i < n; i++){
        cout << arr[i] << " ";
	}
    cout << endl;

    if(isHeap(arr, n)){
        cout << "This array is already a Max-Heap."<<endl;
	}
    else{
        cout << "This array is NOT a Max-Heap."<<endl;;
	}

    convertTomaxHeap(arr, n);
    cout << "After building Max-Heap: ";
    for(int i = 0; i < n; i++){
        cout << arr[i] << " ";
	}
    cout << endl;

    heapSort(arr, n);
    cout << "After Heap Sort (ascending): ";
    for(int i = 0; i < n; i++){
        cout << arr[i] << " ";
	}
    cout << endl;

    return 0;
}
