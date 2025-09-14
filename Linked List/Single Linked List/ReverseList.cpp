	void reverseList(){
		
		Node * prev = NULL;
		Node * curr = head;
		Node * next = NULL;
		
		while(curr!=NULL){
			next =curr->next;
			curr->next = prev;
			
			prev= curr;
			curr= next;
		}
		head = prev;
	}
