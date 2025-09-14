#include <iostream>
using namespace std;

class Node{
	
	public:
		
		int data;
		Node* next;
		Node * child;
		
	
	Node(int val){
		data = val;
		next= nullptr;
		child = NULL;
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
			
			curr->child = NULL;
			
			// STEP 2 FIND TAIL
			
			
			while (curr->next!=NULL){
				curr = curr->next;
				
			}
			
			
			//  STEP 3 ATTACH TAIL with next ptr
			
			
			if (next!=NULL){
				curr->next = next;
			}
			
		}
		
		curr=  curr->next;
		
	}
	return head;
}

void traverseNode(Node *head){
	 Node *temp = head;
    while(temp != NULL){
        cout << temp->data << " -> ";
        temp = temp->next;
    }
    cout << "NULL" << endl;

	
}


int main(){
	LinkedList List1;
	List1.push_back(1);
	List1.push_back(2);
	List1.push_back(3);
	List1.push_back(4);
	
	
	LinkedList List2;
	List2.push_back(5);
	List2.push_back(6);
	
	
		
	LinkedList List3;
	List3.push_back(7);
	List3.push_back(8);
	
	
	Node * node2 = List1.find(2);
	node2->child = List2.gethead();
	
	Node * node6 = List2.find(6);
	node6->child = List3.gethead();
	
	
	cout <<"Flattened List:"<<endl;
	
	
	Node * final = flatten(List1.gethead());
	traverseNode(final);
}



