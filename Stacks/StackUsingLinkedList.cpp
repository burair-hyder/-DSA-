#include <iostream>
using namespace std;

class Node{
	public:
		int data;
		Node  * next;
		
		Node(int val){
			data=  val;
			next = NULL;
		}
};

class myStack{
	
	private: 
		Node * top;
		int count;
	public:
		myStack(){
			top = NULL;
			count =0;
		}
		
		void push(int val){
			Node * temp = new Node(val);
			
			temp->next = top;
			top=temp;
			count++;
		}
		
		int pop(){
			
			if (top==NULL){
				cout <<"Stack UnderFlow."<<endl;
				return -1;
			}
			
			Node * temp = top;
			top = top->next;
			int val = temp->data;
			delete temp;
			count--;
			return val;
		}
		
		int peek(){
			if (top==NULL){
				cout <<"Stack is Empty."<<endl;
				return -1;
			}
			return top->data;	
		}
		
		int size(){
			return count;
		}
		
		bool isEmpty(){
			if (top==NULL) return true;
			else return false;
		}
		
};

int main(){
	
	myStack s1;
	
	s1.peek();
	s1.push(10);
	cout <<"Element at top: "<<s1.peek()<<endl;
	s1.push(20);
	s1.push(30);
	s1.push(40);
	s1.push(50);
	s1.push(60);
	cout <<"Element at top: "<<s1.peek()<<endl;
	cout <<"Current Size: "<<s1.size()<<endl;
	
	while (s1.isEmpty()!= true){
		cout <<"Element Popped: "<<s1.pop()<<endl;
	}
	s1.pop();
	
}
