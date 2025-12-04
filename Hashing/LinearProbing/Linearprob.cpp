#include <iostream>
using namespace std;

class LinearProb{
	
	private:
		int size;
		int count;
		int *table;
		static const int Empty =-1;
		static const int Deleted=-2;
	public:
		
	LinearProb(int sizep){
		size=sizep;
		count=0;
		table = new int[size];
		for (int i=0;i<size;i++){
			table[i]=Empty;
		}
	}
	
	int hash(int key){
		if (key <0){
			key =-key;
		}
		return key%size;
	}
	
	void insertKey(int key){
		if (count==size){
			cout <<"Table is full"<<endl;
			return;
		}
		int idx = hash(key);
		int startidx = idx;
		
		while (table[idx]!=Empty && table[idx]!= Deleted){
			idx= (idx+1)%size;
			
			if (idx==startidx){
				cout <<"insertion failed."<<endl;
				return;
			}
		}
		table[idx]=key;
		count++;
	}
	
	bool searchKey(int key){
		int idx=hash(key);
		int startidx= idx;
		
		while (table[idx]!=Empty){
			if (table[idx]==key){
				return true;
			}
			else{
				idx= (idx+1)%size;
				if (startidx==idx){
					break;
				}
			}
		}
		return false;
	}
	
	
	bool deleteKey(int key){
		int idx= hash(key);
		int startidx=idx;
		
		while (table[idx]!=Empty){
			if (table[idx]==key){
				table[idx]=Deleted;
				count--;
				return true;
			}
			else{
				idx= (idx+1)%size;
				if (idx==startidx){
					return false;
				}
			}
		}
		return false;
	}
	 void display()  {
        cout << "Linear Probing Table (size = " << size << ")\n";
        for (int i = 0; i < size; ++i) {
            cout << i << ": ";
            if (table[i] == Empty) cout << "EMPTY\n";
            else if (table[i] == Deleted) cout << "DELETED\n";
            else cout << table[i] << "\n";
        }
    }
};

int main() {
    LinearProb ht(11);

    ht.insertKey(10);
    ht.insertKey(21);
    ht.insertKey(32);
    ht.insertKey(43);
    ht.insertKey(54);

    cout << "After inserts:\n";
    ht.display();

    cout << "\nSearch 32: " << (ht.searchKey(32) ? "Found" : "Not Found") << endl;
    cout << "Delete 32: " << (ht.deleteKey(32) ? "Deleted" : "Not Found") << endl;
    cout << "Search 32 again: " << (ht.searchKey(32) ? "Found" : "Not Found") << endl;

    cout << "\nTable now:\n";
    ht.display();

    return 0;
}
