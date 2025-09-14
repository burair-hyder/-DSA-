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
			
		
	Node* ReverseKgroup(Node *head,int k){
		
		Node * temp = head;
		int count =0;
		// check if k nodes exist
		while(count<k){
			if (temp==NULL){
				return head;
			}
			temp = temp->next;	
			count++;
		}
		
		
		// recursively call for rest of LL
		
		
			Node * prevNode =ReverseKgroup(temp,k);
			
			// prevNode is the start ptr of the rest of LL
		// reverse the current group
			temp = head;  // start iterating from start
			count =0;
			
			while(count<k){
				
				Node * next= temp->next;  // save the address of next 
				temp->next=  prevNode;  // point first value to rest of LL
				prevNode = temp;  // make first value the fist ptr of the rest LL
				temp = next; // inc the temp
				count++;
			}
			
			head= prevNode; // prev Node is the new head of the linked list
			return head;
		
		
		
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
	list1.push_front(30);
	list1.push_front(20);
	list1.push_front(10);
	list1.push_front(60);
	list1.PrintLL();

	//testing k group function	
	
	Node* temp =list1.ReverseKgroup(list1.gethead(),3);
	list1.sethead(temp);
	list1.PrintLL();
	


}
