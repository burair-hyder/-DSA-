#include <iostream>
using namespace std;

class DoubleHashing{
	private:
		int size;
		int count;
		int *table;
		static const int empty=-1;
		static const int deleted=-2;
		
	public:
		DoubleHashing(int s){
			size=s;
			count=0;
			table = new int[size];
			
			for(int i=0;i<size;i++){
				table[i]=empty;
			}
		}
		
		int hash1(int key){
			if (key<0){
				key = -key;
			}
			return key%size;
		}
		
		int hash2(int key){
			int prime=7;
			if (key<0){
				key = -key;
			}
			return prime - (key%prime);
		}
		
		void insertKey(int key){
			if(count==size){
				cout <<"Full"<<endl;
				return;
			}
			
			int base=hash1(key);
			int step = hash2(key);
			int i=0;
			int idx;
			
			while (i<size){
				idx = (base + step*i)%size;
				if (table[idx]==empty){
					table[idx]=key;
					count++;
					return;
				}
				else{
					i++;
				}
			}
			cout <<"Insertion failed."<<endl;
		}
		
		bool searchKey(int key){
			
			int base= hash1(key);
			int step =hash2(key);
			int i=0;
			int idx;
			
			while (i<size){
				idx= (base + i*step) % size;
				if (table[idx]==key){
					return true;
				}
				if (table[idx]==empty){
					return false;
				}
				i++;
			}
			return false;
		}
		
		bool deleteKey(int key){
			int base= hash1(key);
			int step =hash2(key);
			int i=0;
			int idx;
			
			while (i<size){
				idx=  (base+ i * step) % size;
				
				if (table[idx]==key){
					table[idx]= deleted;
					count--;
					return true;
				}
				if (table[idx]==empty){
					return false;
				}
			}
			return false;
			
		}
		
  void display() const {
        cout << "Double Hashing Table (size = " << size << ")\n";
        for (int i = 0; i < size; ++i) {
            cout << i << ": ";
            if (table[i] == empty) cout << "EMPTY\n";
            else if (table[i] == deleted) cout << "DELETED\n";
            else cout << table[i] << "\n";
        }
    }
};

// Demo
int main() {
  DoubleHashing  ht(11);

    ht.insertKey(10);
    ht.insertKey(22);
    ht.insertKey(31);
    ht.insertKey(4);
    ht.insertKey(15);

    cout << "After inserts:\n";
    ht.display();

    cout << "\nSearch 31: " << (ht.searchKey(31) ? "Found" : "Not Found") << endl;
    cout << "Delete 31: " << (ht.deleteKey(31) ? "Deleted" : "Not Found") << endl;
    cout << "Search 31 again: " << (ht.searchKey(31) ? "Found" : "Not Found") << endl;

    cout << "\nFinal table:\n";
    ht.display();

    return 0;
}
