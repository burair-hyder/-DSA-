#include <iostream>
using namespace std;


class Node{
	
	public:
		int data;
		Node *next;
		
		Node(int val){
			data= val;
			next= NULL;
		}
		
		
};

class CL{
	Node * head;
	Node * tail;
	
	public:
		
		CL(){
			head=tail=NULL;
		}
		
		void insetAtbeg(int val){
			Node * newNode = new Node(val);
			
			if (head==NULL){
				head=tail=newNode;
				tail->next = head;
				
			}
			else{
				newNode->next=  head;
				head=newNode;
				tail->next = head;
				
			}
		}
		void insertAtEnd(int val){
			Node * newNode = new Node(val);
			if (head==NULL){
				head=tail=newNode;
				tail ->next = head;
				
			}
			else{
				newNode ->next= head;
				tail ->next = newNode;
				tail = newNode;
			}
		}
		
		void deleteAtbeg(){
			
			if (head==NULL){
				cout <<"Empty list."<<endl;
				return ;
			}
			else if (head==tail){
				delete head;
				head=tail=NULL;
			}
			else{
				Node * temp = head;
				head=  head->next;
				tail->next = head;
				temp ->next = NULL;
				delete temp;
			}
		}
		void deleteAtend(){
			if (head==NULL){
					cout <<"Empty list."<<endl;
				return ;
			}
			else if (head==tail){
				delete head;
				head=tail=NULL;
			}
			else{
				Node * prev = head;
				Node * temp = tail;
				while (prev->next != tail){
					prev = prev->next;
				}
				
				tail = prev;
				tail ->next= head;
				temp ->next = NULL;
				delete temp;
	
			}
		}
		void printList(){
			
			if (head==NULL){
				cout <<"Empty list."<<endl;
				return ;
				
			}
			cout <<head->data<<"->";
			Node * temp=head->next;
			while (temp!=head){
				cout <<temp->data <<"->";
				temp = temp ->next;
			}
			cout << "HEAD"<<endl;
		}
};

int main(){
	
	CL l1;
	l1.insertAtEnd(1);
	l1.insertAtEnd(2);
	l1.insetAtbeg(0);
	l1.insetAtbeg(-1);
	l1.printList();
	l1.deleteAtbeg();
	l1.printList();
	l1.deleteAtend();
	l1.printList();
	l1.deleteAtbeg();
	l1.printList();
	l1.deleteAtbeg();
}
