#include <iostream>
using namespace std;


void computeLPS(string pattern,int * LPS){
	int m = pattern.length();	
	int i=1;
	int len =0;
	LPS[0] =0;
	
	
	// check pat[i] == pat[len]
	// lps[i] = len 
	// len++
	// i++
	
	//  if not (else)
	//		 if len != 0 
	//			 len = LPS[len-1]
	// 		if len ==0
	//				i++
	
	while (i<m){
		
		if (pattern[i]==pattern[len]){
			len++;
			LPS[i]=len;
			i++;
		}
		else{
			if (len!=0){
				len = LPS[len-1];
				
			}
			else{
				LPS[i]=0;
				i++;
			}
		}
	}
	
}

void KMP(string text,string pattern ){
	int  m= pattern.length();
	int  n= text.length();
	
	int * LPS = new int[m];
	computeLPS(pattern,LPS);
	int  i=0;
	int  j=0;
	
	while (i<n){
		
		if (text[i]==pattern[j]){
			i++;
			j++;
			
		}
		if (j==m){
			cout <<"Found at Index: "<<i-j<<endl;
			j = LPS[j-1];
			
		}
		else if (pattern[j]!=text[i]){
			if (j!=0){
				j = LPS[j-1];
			}
			else{
				i++;
			}
		}
	}
		
}

int main(){
	string Text = "ababababc";
	string  Pattern = "abab";
	
	KMP(Text,Pattern);
}
