#include <iostream>
using namespace std;

class Node{
	public:
		
		int data;
		Node * next;
		Node * prev;
		
		Node(int val){
			data = val;
			next = NULL;
			prev = NULL;
		}
};

class DoublyList{
		
		Node * head;
		Node * tail;
		
	public:
		DoublyList(){
			head = NULL;
			tail = NULL;
			
		}
		
		void push_front(int val){
			
		
			Node * newNode = new Node(val);
			
			if (head==NULL){
				head=newNode;
				tail=newNode;
			}
			else{
				newNode->next = head;
				head->prev = newNode;
				head= newNode;	
			}
	
		}
		
		void push_back(int val){
			
			Node * newNode = new Node(val);
			
			
			if (head==NULL){
				head=tail=newNode;
			}
			else{
				newNode->prev = tail;
				tail->next = newNode;
				tail = newNode;
			}
			
		}
		
		
		void pop_front(){
				
			if (head==NULL){
				cout<<"Doubly List is already empty!"<<endl;
				return;
			}
			Node * temp = head;
			
			head = head->next;
			
			if(head!=NULL){ // checks if only 1 element exist then no need
				head->prev = NULL;
					
			}
			else{
				tail=NULL; // makes tail null since the last element also got removed
			}
			temp->next = NULL;
			delete temp;
		}
		
		
		void pop_back(){
			
			if (head==NULL){
				cout <<"Doubly list is already empty.";
				return;
			}
			
			Node * temp = tail;
			
			tail = tail->prev;
			
			if (tail!=NULL){
				tail->next = NULL;
			
			}
			else{
				head=NULL; // makes head null since the last element also got removed
			}
			temp->prev = NULL;
			delete temp;
		}
		
		
		void PrintLL(){
			
			Node * temp= head;
			
			while(temp!=NULL){
				
				cout <<temp->data <<" <=> ";
				temp= temp->next;
			}
			cout <<"NULL"<<endl;
		}

	void insertatPos(int val, int pos){
			
			if (pos<0){
				cout <<"Invalid Pos."<<endl;
				return;
			}
			else if (pos==0){
				insertAtBeg(val);
			}
			else{
				Node * temp =head;
				Node * newNode = new Node(val);
				for (int i=0;i<pos-1;i++){
					temp = temp->next;
					if (temp==NULL){
						cout <<"Invalid pos."<<endl;
						return ;
					}
					
				}
				if (temp->next == NULL) {
            		temp->next = newNode;
            		newNode->prev = temp;
           			tail = newNode;
        }
       			 else{
		
					newNode->next = temp->next;
					temp->next->prev = newNode;
					temp->next = newNode;
					newNode->prev= temp;
			}
			}
		}
		
};



int main(){
	
	DoublyList DList1;
	
	DList1.push_front(30);
	DList1.push_front(20);
	DList1.push_front(10);
	
	DList1.push_back(40);
	
	DList1.PrintLL();
	
	
	DList1.pop_front();
	DList1.PrintLL();
	
	DList1.pop_front();
	DList1.PrintLL();
	
	DList1.pop_front();
	DList1.PrintLL();

	DList1.pop_back();
	DList1.PrintLL();
	
	DList1.pop_back();
	DList1.PrintLL();
		

	
	
	
	
	

	
}
