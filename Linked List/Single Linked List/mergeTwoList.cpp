Node * mergeTwoList(Node * h1,Node *h2){
	
		if (h1==NULL||h2==NULL){
			if (h1==NULL){
				return h2;
			}
			else{
				return h1;
			}
		}
		//case 1
		if (h1->data<=h2->data){
			
			h1->next = mergeTwoList(h1->next,h2);
			return h1;
		}
		
		else{
			//case2 
			h2->next = mergeTwoList(h1,h2->next);
			return h2;
		}
}
