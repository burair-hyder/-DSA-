#include <iostream>
using namespace std;


class Node{
	public:
		int data;
		Node * next;
		Node(int val){
			data=val;
			next=NULL;
		}
		
};

class HashChaining{
	
	private:
		static	int const size=10;
		Node * Table[size];
		
	public:
		HashChaining(){
			for (int i=0;i<10;i++){
				Table[i] = NULL;
			}
		}
		
		int hash(int i){
			if (i<0){
				i=-i;
			}
			return i%size;
		}
		
		void insertKey(int val){
			int key=  hash(val);
			
			 Table[key];
			Node * newNode = new Node(val);
			newNode->next= Table[key];
			Table[key]= newNode;
		}
		
		void deleteKey(int val){
			int key = hash(val);
			
			Node * curr = Table[key];
			Node * prev=NULL;
			while(curr!=NULL){
				if (curr->data==val){
					if (curr==Table[key]){
						Table[key] = Table[key] -> next;
					}
					else{
						//middle case
						prev->next= curr->next;
						
					}
					delete curr;
					cout <<"deleted"<<endl;
					return;
				}
				else{
					prev= curr;
					curr=curr->next;
				}
			}
			cout <<"Not found"<<endl;
			return;
		}
		
		
	bool searchKey(int key)  {
        int idx = hash(key);
        Node* cur = Table[idx];
        while (cur) {
            if (cur->data == key){
            	 return true;
			}
            cur = cur->next;
        }
        return false;
    }
    
    
    void display(){
    	for (int i=0;i<size;i++){
    		Node * temp= Table[i];
    		cout <<i+1<<": ";
    		while (temp != NULL){
    			cout <<temp->data<<"->";
    			temp = temp->next;
			}
			cout <<endl;
		}
	}
    
    
};
int main() {
    // choose table size (can be any integer)
    HashChaining ht;

    // Insert keys
    ht.insertKey(15);
    ht.insertKey(26);
    ht.insertKey(37);
    ht.insertKey(26); // duplicate allowed; appears at head of chain
    ht.insertKey(48);

    cout << "After inserts:\n";
    ht.display();

    cout << "\nSearch 26: " << (ht.searchKey(26) ? "Found" : "Not Found") << endl;
    cout << "Delete 26: " <<endl;
     ht.deleteKey(26);
    cout << "Search 26 again: " << (ht.searchKey(26) ? "Found" : "Not Found") << endl;

    cout << "\nFinal table:\n";
    ht.display();

    return 0;
}
