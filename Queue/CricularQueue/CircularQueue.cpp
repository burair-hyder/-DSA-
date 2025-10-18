#include <iostream>
using namespace std;

class CircularQueue{
	private :
		int *arr;
		int cap;
		int currsize;
		int front,rear;
		
	public:
		CircularQueue(int size){
			cap = size;
			arr= new int[cap];
			currsize=0;
			rear=-1;
			front =0;
		}
		
		bool isEmpty(){
			return currsize==0;
		}
		
		bool isFull(){
			return currsize==cap;
		}
		
		void Enqueue(int val){
			
			if (isFull()){
				cout <<"Queue is Full."<<endl;
				return;
			}
			else{
				rear=(rear+1)%cap;
				arr[rear]=val;
				cout <<"Inserted: "<<val<<endl;
				currsize++;
			}
		}
		
		int dequeue(){
			if (isEmpty()){
				cout <<"Queue is Empty."<<endl;
				return -1;
			}
			else{
				int temp=arr[front];
				front = (front +1)%cap;
				currsize--;
				return temp;
			}
		}
		
		int getfront(){
			
			if (isEmpty()){
				cout <<"Queue is Empty."<<endl;
				return -1;
			}
			
			return arr[front];
			
			
			
		}
		
		
		void display(){
			if (isEmpty()){
				cout <<"Queue is Empty."<<endl;
				return;
			}
			
			int i=front;
			
			while (true){
				cout <<arr[i]<<" ";
				if (i==rear){
					break;
				}
				i = (i+1)%cap;
					
			}
			cout <<endl;
		}
	
};

int main(){
	CircularQueue Q1(3);
	Q1.Enqueue(10);
	Q1.Enqueue(20);
	cout <<"Dequeued: "<<Q1.dequeue()<<endl;
	
	Q1.Enqueue(30);
	Q1.Enqueue(40);
	
	
	cout <<"Front: "<<Q1.getfront()<<endl;
	
	
	while(!Q1.isEmpty()){
		cout <<Q1.getfront()<< " ";
		Q1.dequeue();
	}
	
//	Q1.display();
}
