int BinarySearch(int arr[],int size,int target){
	
	int left =0;
	int right = size-1;
	while (left <= right){
		
		int mid = left +(right-left)/2;
		
		if (arr[mid] == target){
			return mid;
		}
		else if (target > arr[mid]){
			left = mid + 1;
		}
		else {
			right = mid-1;
			
		}
	}
	return -1;
	
	
	
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
	
	//out <<"Unsorted Array:"<<endl;
	//printArray(arr,n);

	//cout <<"Sorted Array:"<<endl;
	InsertionSort(arr,n);

	//printArray(arr,n);
	
	cout <<"Enter Value to Search:";
	cin >>tofind;
	
	int index =BinarySearch(arr,n,tofind);
	
	if (index!=-1){
		cout <<"Value found at index :"<<index<<endl;
	}
	else {
		cout <<"Value Not Found in the Array."<<endl;
	}
	
	
	return 0;
	
	
}
