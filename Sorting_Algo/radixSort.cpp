#include <iostream>
using namespace std;

class Node{
	
	public:
		int data;
		Node * next;
		Node(int val){
			data= val;
			next = NULL;
			
		}
		
};

void insertinbucket(Node *& head, int val){
	
	Node *newNode= new Node(val);
	if (head==NULL){
		head=newNode;
		return;
	}
	
	Node * temp = head;
	while (temp->next != NULL){
		temp = temp->next;
	} 
	temp->next= newNode;
}


void clearBucket(Node*& head){
	
	Node * temp;
	
	while (head!=NULL){
		temp = head;
		head= head->next;
		delete temp;
	}
	
}

int getmax(int *arr,int n){
	int max= arr[0];
	
	for (int i=0;i<n;i++){
		if (arr[i]>=max){
			max=arr[i];
		}
		
	}
	return max;
}


void RadixSort(int *arr,int n){
	int max=getmax(arr,n );
	int exp=1;
	
	Node* Bucket[10];
	while (max/exp>0){
	// intialize bucket array with NULL;
	for (int i=0;i<10;i++){
		Bucket[i]=NULL;
	}
	
	
	for (int i=0;i<n;i++){
		int dig = (arr[i]/exp)%10;
		insertinbucket(Bucket[dig],arr[i]);
	}
	
	int idx=0;
	
	for (int i=0;i<10;i++){
		Node * temp = Bucket[i];
		while(temp!=NULL){
			arr[idx]=temp->data;
			idx++;
			temp = temp->next;
		}
		clearBucket(Bucket[i]);
	}
	exp = exp*10;
	
	
	}
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}


int main() {
    int arr[] = {170, 45, 75, 90, 802, 24, 2, 66};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Original array: ";
    printArray(arr, n);

    RadixSort(arr, n);

    cout << "Sorted array: ";
    printArray(arr, n);

    return 0;
}


