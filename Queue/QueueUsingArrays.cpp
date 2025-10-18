#include  <iostream>
using namespace std;

class Queue{
	private :
		int * arr;
		int cap ;
		int size;
	public:
		Queue(int capp){
			cap =capp;
			arr= new int[cap];
			size=0;
		}
		
		bool isEmpty(){
			return size==0;
		}
		bool isFull(){
			return size==cap;
		}
		
		void Enqueue(int val){
			
			if (isFull()){
				cout <<"Queue is Full."<<endl;
				return;
			}
			else{
				arr[size]=val;
				size++;
			}
		}
		
		int Dequeue(){
			
			if (isEmpty()){
				cout <<"Queue is Empty."<<endl;
				return -1;
			}
			else{
				int temp=arr[0];
				
				for (int i=1;i<size;i++){
					arr[i-1]= arr[i];
				}
				size--;
				return temp;
			}
			
		}
		
		int getFront(){
			
			if (isEmpty()){
				cout <<"Queue is Empty."<<endl;
				return -1;
			}
			return arr[0];	
		}
		
		int getRear(){
			
			if (isEmpty()){
				cout <<"Queue is Empty."<<endl;
				return -1;
			}
			return arr[size-1];
			
			
		}
		
		
};

int main(){
	Queue Q1(5);
	Q1.Enqueue(10);
	Q1.Enqueue(20);
	cout <<"Dequeued: "<<Q1.Dequeue()<<endl;
	
	Q1.Enqueue(30);
	Q1.Enqueue(40);
	
	cout <<"Front: "<<Q1.getFront()<<endl;
	cout <<"Rear: "<<Q1.getRear()<<endl;
	
	
	while(!Q1.isEmpty()){
		cout <<Q1.getFront()<< " ";
		Q1.Dequeue();
	}
	

}
