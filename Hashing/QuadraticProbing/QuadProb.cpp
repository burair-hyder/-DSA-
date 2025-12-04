#include <iostream>
using namespace std;


class QuadProb{
	private:
		int size;
		int count;
		int *table;
		static const int empty =-1;
		static const int deleted =-2;
		
	public:
		int hash(int key){
		    if (key < 0) 
			  key = -key;
       		return key % size;
		}
		QuadProb(int s){
			size=s;
			count=0;
			table = new int[size];
			for (int i=0;i<size;i++){
				table[i]=empty;
			}
		}
		
		void insertKey(int key){
			if (count==size){
				cout <<"Full"<<endl;
				return;
			}
			int base=hash(key);
			int i=0;
			int idx;
			while (i<size){
				idx= (base+i*i) % size;
				if (table[idx]== empty || table[idx]==deleted){
					table[idx]=key;
					count++;
					return;
				}
				i++;
			}
			cout <<"Failed to insert"<<endl;
		}
		
		bool searchKey(int key){
			
			int base= hash(key);
			int i=0;
			int idx;
			
			while (i<size){
				idx= (base + i*i) % size;
				if(table[idx]==key){
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
			int base= hash(key);
			int i=0;
			int idx;
			
			while (i<size){
				idx = (base + i*i) % size;
				
				if(table[idx]==key){
					table[idx]=deleted;
					count--;
					return true;
				}
				if (table[idx]==empty){
					return false;
				}
				i++;
			}
			return false;
		}
		
		  void display() const {
        cout << "Quadratic Probing Table (size = " << size << ")\n";
        for (int i = 0; i < size; ++i) {
            cout << i << ": ";
            if (table[i] == empty) cout << "EMPTY\n";
            else if (table[i] == deleted) cout << "DELETED\n";
            else cout << table[i] << "\n";
        }
    }
};

int main() {
    QuadProb ht(11);

    ht.insertKey(5);
    ht.insertKey(16);
    ht.insertKey(27);
    ht.insertKey(38);
    ht.insertKey(49);

    cout << "After inserts:\n";
    ht.display();

    cout << "\nSearch 27: " << (ht.searchKey(27) ? "Found" : "Not Found") << endl;
    cout << "Delete 27: " << (ht.deleteKey(27) ? "Deleted" : "Not Found") << endl;
    cout << "Search 27 again: " << (ht.searchKey(27) ? "Found" : "Not Found") << endl;

    cout << "\nFinal table:\n";
    ht.display();

    return 0;
}
