
#include <iostream>
using namespace std;
class Node{
	public:
		
		int data;
		Node * next;
		Node * prev;
		Node * child;
		
		Node(int val){
			data = val;
			next = NULL;
			prev = NULL;
			child = NULL;
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
		
		Node * find(int val){
			Node * temp = head;
			while (temp!=NULL){
				if(temp->data == val)
				return temp;
			temp = temp -> next;
			}
		return NULL;
		}
		
		
		Node * gethead(){
			return head;
		}
};




Node * flatten(Node *head){
	
	if (head==NULL){
		return head;
	}
	
	Node *curr = head;
	while(curr!=NULL){
		if (curr->child!=NULL){
			// STEP 1 FLATTEN THE CHILD NODES
			
			Node * next = curr->next;
			curr->next= flatten(curr->child);
			
			curr->next->prev = curr;
			curr->child = NULL;
			
			// STEP 2 FIND TAIL
			
			
			while (curr->next!=NULL){
				curr = curr->next;
				
			}
			
			
			//  STEP 3 ATTACH TAIL with next ptr
			
			
			if (next!=NULL){
				curr->next = next;
				next -> prev = curr;
			}
			
		}
		
		curr=  curr->next;
		
	}
	return head;
}

void traverseNode(Node *head){
	 Node *temp = head;
    while(temp != NULL){
        cout << temp->data << " <=> ";
        temp = temp->next;
    }
    cout << "NULL" << endl;

	
}

int main(){
	
	DoublyList list1;
	list1.push_back(10);
	list1.push_back(20);
	list1.push_back(30);
	list1.push_back(40);
	Node* child1= list1.find(30);
	
	Node * headofList1 = list1.gethead();
	
	
	DoublyList list2;
	list2.push_back(50);
	list2.push_back(60);
	list2.push_back(70);
	list2.push_back(80);
	
	DoublyList list3;
	list3.push_back(100);
	list3.push_back(120);
	Node * headofList3 = list3.gethead(); 
	
	Node * child2 = list1.find(20);
	child2->child = headofList3;
	
	Node * headofList2 = list2.gethead();
	child1->child = headofList2;
	
	
	Node * final =flatten(headofList1);
	
	
	traverseNode(final);
	
	
	
	
	
	
	
	
	
}
