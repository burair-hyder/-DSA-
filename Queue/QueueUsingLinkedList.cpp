#include <iostream>
using namespace std;
class Node{
	
	public:
		int data;
		Node * next;
		
		Node(int val){
			data= val;
			next= NULL;
		}
};

class Queue{
	private:
		int currSize;
		Node * front;
		Node * rear;
		
	public:
		Queue(){
			currSize=0;
			front=rear=NULL;
		}
		
		void Enqueue(int val){ // insert at rear
			Node * newNode=  new Node(val);
			
			if (empty()){
				front=rear=newNode;
			}	  
			else{
				 rear->next=newNode;
				 rear=newNode;
			}
			currSize++;
		}
		
		int Dequeue(){ // delete at head(front)
			
			if (empty()){
				cout <<"Queue Underflow."<<endl;
				return -1;
			}
			else{
				Node * temp = front;
				int removedData = temp->data;
				front  = front->next;
				if (front  == NULL){
					rear=NULL;
				}
				temp->next= NULL;
				delete temp;
				currSize--;
				return removedData;
			}
			
			
		}
		
		int getfront(){
			
			if (empty()){
				cout <<"Queue is Empty."<<endl;
				return -1;
			}
			return front->data;
		}
		
		bool empty(){
			return front==NULL;
		}
		
		int getsize(){
			return currSize;
		}
};
int main(){
	
	Queue Q1;
	Q1.Enqueue(10);
	Q1.Enqueue(20);
	cout <<"Dequeued: "<<Q1.Dequeue()<<endl;
	
	Q1.Enqueue(30);
	Q1.Enqueue(40);
	
	cout <<"Front: "<<Q1.getfront()<<endl;
	cout <<"Size: "<<Q1.getsize()<<endl;
	
	while(!Q1.empty()){
		cout <<Q1.getfront()<< " ";
		Q1.Dequeue();
	}
	
}
