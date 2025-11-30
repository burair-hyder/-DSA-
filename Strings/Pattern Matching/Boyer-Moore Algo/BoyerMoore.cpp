#include <iostream>
using namespace std;


void buildBadTable(string pattern, int *badchar){
	
	int m = pattern.length();
	for(int i=0;i<256;i++){
		badchar[i]=-1;
	}
	for(int i=0;i<m;i++){
		badchar[(int)pattern[i]]=i;
	}
}

void boyerMore(string text,string pattern){
	int n= text.length();
	int m= pattern.length();
	
	int shift=0;
	int *badchar = new int[256];
	buildBadTable(pattern,badchar);
	while (shift <=n-m){
		int j=m-1;
		
		while (j>=0 && text[shift+j]==pattern[j]){
			j--;
		}
		
		
		if (j<0){
			cout <<"Found at Index: "<<shift <<endl;
			
			if (shift+m<n){
				
				int next = text[shift+m];
				int lastOC =badchar[(int)next];
				shift = shift + m-lastOC;
				
			}
			else{
				shift = shift+1;
			}
		}
		else{
			
			int bad = shift+j;
			int lastOc = badchar[(int)text[bad]];
			
			int slide = j-lastOc;
			
			if (slide<1) slide=1;
			shift = shift+slide;  
		}
		
	}
}

int main(){
string 	DNA = "ACGTACGTGACG";
string 	pattern = "ACG";
	boyerMore(DNA,pattern);
	
}
