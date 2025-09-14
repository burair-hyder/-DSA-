#include <iostream>
using namespace std;

class Node{
	
	public:
		
		int data;
		Node* next;
		
	
	Node(int val){
		data = val;
		next= nullptr;
	}
	
};



class LinkedList{
	
	
	
	public:
		Node* head;
	Node* tail;
		LinkedList(){
			
			head= nullptr;
			tail = nullptr;
		}
	
		void push_front(int val){
			
			Node* newNode = new Node(val);
			
			if (head==nullptr){
				head = newNode;
				tail = newNode;
			}
			else{
				newNode->next = head; 
				head= newNode;
				
			}
		}
		
		void push_back(int val){
			
			Node * newNode = new Node(val);
			
			if (head == nullptr){
				
				head=newNode;
				tail = newNode;
				
			}
			
			else{
				tail->next = newNode;
				tail = newNode;
				
			}
		} 
		
		
		
		void pop_front(){
			
			if (head==nullptr){
				cout <<"LL is empty"<<endl;
				return;
			}
			else{
				Node *temp = head;
				head = head->next;
				temp->next = nullptr;
				
				delete temp;
				
				
			}
		}
		
		void pop_back(){
			
			if (head==nullptr){
				cout <<"LL is empty"<<endl;
				return;
			}
			else{
				Node * prevNode = head;
				
				while (prevNode->next != tail){
					
					prevNode=prevNode->next;
					
					
				}
				prevNode->next = nullptr;
				delete tail;
				tail = prevNode;
			}
		}
		
		
		void insert(int val,int pos){
			if (pos<0){
				cout <<"Invalid Pos"<<endl;
				return;
			}
			else if (pos==0){
				push_front(val);
			}
			else{
				
				Node* temp= head;
				for (int i=0;i<pos-1;i++){
					temp = temp->next;
					if (temp== nullptr){
						cout<<"Invalid Pos, out of bouund"<<endl;
						return;
						
					}	
					
				}
				
				
				Node * newNode = new Node(val);
				newNode->next = temp->next;
				temp->next = newNode;
			}
		}
		void PrintLL(){
			Node* temp = head;
			
			while (temp!=nullptr){
				
				cout <<  temp->data<<"-> ";
				
				temp = temp->next;
			}
			cout <<"NULL"<<endl;
		}
		
		
		int search(int find){
			Node * temp = head;
			int index=0;
			while(temp!=nullptr){
				if (temp->data == find){
					return index;
				}
				else{
					temp = temp->next;
					index++;
				}
			}
			return -1;
			
		}
	
	
	Node* ReverseNew(){
		Node * newhead=NULL;
		Node * temp = head;
		
		while(temp!=NULL){
			
			int val= temp->data;
			Node * newNode = new Node(val);
			
			newNode->next = newhead;
			newhead=  newNode;
			temp=temp->next;	
		}
		return newhead;
	}
	
	void isPalin(){
	
		Node * rev = ReverseNew();
		Node * org = head;
		
		while (rev != NULL && org !=NULL){
			
			if (rev->data != org->data){
				cout <<"Is not Plaindrome."<<endl;
				return;
			}
			
			rev = rev->next;
			org = org->next;
			
		}
		cout <<"Is Palindrome."<<endl;
	
	}
			
		
	
	Node * gethead(){
		return head;
	}
	
	void sethead(Node * temp){
		head= temp;
	}
		 
};




int main(){
	LinkedList list1;
	
	list1.push_front(40);
	list1.push_front(20);
	list1.push_front(10);
	list1.push_front(20);
	list1.push_front(40);
	list1.PrintLL();
	
	list1.isPalin();
	
	LinkedList list2;

	list2.push_front(40);
	list2.push_front(20);
	list2.push_front(30);
	list2.push_front(50);
	list2.push_front(40);
	list2.PrintLL();
	
	list2.isPalin();
	

	


}
