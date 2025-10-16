#include <iostream>
#include <vector>
using namespace std;
void solve(const string& digits,int index,string & current,vector <string>& results, const vector <string>& allpossible);

vector <string> allcomb(string d){
	
	if (d.empty()){
		return {};
	}
	
	const vector <string> possible= {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
	
	vector <string> result;
	string  curr= "";
	
	solve(d,0,curr,result,possible);
	
	return result;
	
}


void solve(const string& digits,int index,string & current,vector <string>& results,const  vector <string>& allpossible){
	
	if (index==digits.size()){
		results.push_back(current);
		return;
	}
	
	int digit = digits[index] -'0';
	
	string letters =allpossible[digit];
	
	for (char c : letters){
		
		current.push_back(c);
		
		solve(digits,index+1,current,results,allpossible);
	
		current.pop_back();
	}
	
	
	
	
}

int main(){
//	Solution x;
    string d;
    
    cout << "enter digits (e.g., 23): ";
    cin >> d;
    
    vector<string> ans = allcomb(d);
    
    cout << "\ncombinations:\n";
    if (ans.empty()) {
        cout << "No combinations generated (input was empty or contained only 0s/1s)." << endl;
    } else {
        for (const auto& v : ans) {
            cout << v << " ";
        }
        cout << endl;
    }
    
    return 0;
}
