#include <iostream>
using namespace std;

class MaxHeap{
	private:
		
		int *heap;
		int cap;
		int size;
		
	public:
		MaxHeap(int capp){
			cap =capp;
			size=0;
			heap=  new int[cap];
		}
		
		int parent(int i){
			return (i-1)/2;
		}
		int left(int i){
			return(i*2)+1;
		}
		int right(int i){
			return (i*2)+2;
		}
		
		void heapify_up(int i){
			
			while (i!=0 && heap[parent(i)] < heap[i]){
				swap(heap[parent(i)],heap[i]);
				i = parent(i);
			}
		}
		
		void insert(int val){
			
			if (size==cap){
				cout <<"Heap Overflow."<<endl;
			}
			
			heap[size]=val;
			heapify_up(size);
			size++;
		}
		
		void delete_max(){
			
			if (size==0){
				cout <<"Heap Underflow."<<endl;
			}
			
			cout <<"Delete Item: "<<heap[0]<<endl;
			
			heap[0] = heap[size-1];
			size--;
			heapify_down(0);
		}
		
		void heapify_down(int i){
			
			int l = left(i);
			int r = right(i);
			int largest = i;
			
			if (l<size && heap[l]>heap[largest]){
				largest = l;
			}
			if(r<size && heap[r]>heap[largest]){
				largest = r;
			}
			
			if (largest != i){
				swap(heap[i],heap[largest]);
				heapify_down(largest);
			}
		}
		
		
		
		void display() {
       		 for (int i = 0; i < size; i++)
             	cout << heap[i] << " ";
        		cout << endl;
    	}
		
		void update_key(int val,int i){
			if (i<0 || i>=size){
				cout <<"Invalid Index."<<endl;
				return;
			}
			
			int oldval = arr[i];
			arr[i] = val;
			
			if (val>oldval){
				heapify_up(i);
			}
			else{
				heapify_down(i);
			}
		}
		
		void delete_key(int i){
			
			if (i<0 || i>=size){
				cout <<"Invalid Index."<<endl;
				return ;
			}
			
			heap[i] = heap[size-1];
			size--;
			
			heapify_down(i);
			heapify_up(i);
		}
		
		
};

int main(){
	
	MaxHeap heap1(5);
	heap1.insert(8);
	heap1.insert(7);
	heap1.insert(6);
	heap1.insert(5);
	heap1.insert(4);
	heap1.display();
	
	
}
