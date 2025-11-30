#include <iostream>
using namespace std;


int bruteforcealgo(string text,string pat){
	int n  = text.length();
	int m = pat.length();
	
	for (int i=0;i<=n-m;i++){
		
		int j=0;
		while (j<m && text[i+j]== pat[j]){
			j++;
		}
		if (j==m){
			cout <<i<<" ";
		}
	}
}
int main(){
	string text = "the quick brown fox jumps over the lazy dog";
	string pat = "the";
	cout <<"Found at following Index: ";
	bruteforcealgo(text,pat);
	
	
}

