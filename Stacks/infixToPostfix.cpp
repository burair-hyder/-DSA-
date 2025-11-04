#include <iostream>
#include <stack>
using namespace std;



// if operand  print
// if ( pop untill we found )
// if operator 
// pop from stack and print untill operator with less precdenacne




int precedence(char c){
	
	if (c=='^'){
		return 3;
		
}
	else if  (c=='*'||c=='/'){
		return 2;
	}
	else if (c=='+'||c=='-'){
		return 1;
	}
	else
	{
		return -1;
	}
}


string infixTopostfix(string s){
	
	stack <char> st;
	
	string res;
	
	
	for (int i=0;i<s.length();i++){
		if ((s[i]>='a'&& s[i]<='z')|| (s[i]>='A'&& s[i]<='Z')){
			res=res+s[i];
		}
		else if (s[i]=='('){
			st.push(s[i]);
		}
		else if (s[i]==')'){
			
			while (!st.empty() && st.top()!='('){
				res= res + st.top();
				st.pop();
			}
			st.pop(); // remove ( bracket	
		}
		else{
			
			while (!st.empty()&& precedence(st.top())>precedence(s[i])){
				res = res +st.top();
				st.pop();
			}
			st.push(s[i]);
		}
		
	}
	
	while (!st.empty()){
		res = res+st.top();
		st.pop();
	}
	
	return res;
	
}

int main(){
	cout <<infixTopostfix("(a-b/c)*(a/k-l)");
}
