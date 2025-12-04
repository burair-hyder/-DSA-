#include <iostream>
using namespace std;



void rabinkarp(string text,string pat,int base=256,int prime=101){
	int n = text.length();
	int m = pat.length();
	
	int pHash =0;
	int tHash = 0;
	int h=1;
	
	for (int i=0;i<m-1;i++){
		h=  (h*base)%prime;
	}
	
	for (int i=0;i<m;i++){
		pHash = (base* pHash + pat[i]) % prime;
		tHash = (base * tHash + text[i])% prime;
	}
	
	for (int i=0;i<=n-m;i++){
		
		if(pHash==tHash){
			bool match = true;
			
			for (int j=0;j<m;j++){
				if (text[i+j]!=pat[j]){
					match = false;
					break;
					
				}
			}
			if (match){
				cout <<"Pattern found at index: "<<i<<endl;
			}
			
		}
		
		if (i+m<n){ // not last window   if i==n-m this means we are at last window 
			tHash = (base * (tHash-text[i] * h)+text[i+m])%prime;
			
			if (tHash <0){
				tHash = tHash +prime;
				
			}
		}
		
	}
	
	
}

int main(){
	string text = "Data structures and Algorithms are fun. Algorithms make tasks easier.";
	string pat  ="Algorithms";
	rabinkarp(text,pat);
	
}
