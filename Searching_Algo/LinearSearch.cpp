#include <iostream>
using namespace std;

int main(){
	
	
	int *arr;
	int tofind;
	int temp;
	int count;
	bool flag=false;
	
	cout <<"Enter Number of values you want to store:";
	cin >>count;
	
	arr=  new int[count];
	
	for (int i=0;i<count;i++){
		cout <<"Enter Value "<<i+1<<" for the Array: ";
		cin >> arr[i];
	}
	cout <<"Enter value to find:";
	cin>>tofind;
	
	for (int i=0;i<count;i++){
		if(arr[i]==tofind){
			temp =i;
			flag =  true;
			break;
		}
	}
	
	if (flag ==true){
		cout <<"Value found at Index: " <<temp<<endl;;
	}
	else{
		cout <<"value not found"<<endl;
	}
	cout<<endl;
	cout <<"PRINTING ARRAY.";
	for (int i=0;i<count;i++){
		cout <<arr[i]<<", ";
	}
}
