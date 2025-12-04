#include <iostream>
using namespace std;


class RehashingLinear{
	
	private:
		int *table;
		int size;
		int count;
		
		static const int empty = -1;
		static const int deleted =-2;
		
		int hash(int key){
			if (key<0){
				key =-key;
			}
			return key%size;
		}
		
		bool isPrime(int n){
			if (n<=1){
				return false;
			}
			if(n<=3){
				return true;
			}
			if (n%2==0){
				return false;
			}
			for (int i=3;i*i<n;i+=2){
				if (n%i==0){
					return false;
				}
			}
			return true;
		}
		
		int nextprime(int  n){
			while(!isPrime(n)){
				n++;
			}
			return n;
		}
		
		double loadFactor(){
			return (double)count/(double)size;
		}
		
		void rehash(){
			int oldsize = size;
			int *oldtable= table;
			
			int target = size*2;
			int newsize = nextprime(target);
			
			int *newtable = new int[newsize];
			size=newsize;
			for (int i=0;i<size;i++){
				newtable[i]=empty;
			}
			
			count =0;
			table =newtable;
			for (int i=0;i<oldsize;i++){
				if (oldtable[i]!=empty && oldtable[i]!= deleted){
					insertKey(oldtable[i]);
					
				}
			}
			
			delete[] oldtable;
			
			
			cout <<"rehashed to new size"<<size<<endl;
		}
		
		
		public:
			RehashingLinear(int sizep){
				int s = sizep;
				if (s<3){
					s=3;
				}
				size = nextprime(s);
				table = new int[size];
				for (int i=0;i<size;i++){
					table[i] = empty;
					
				}
				count=0;
			}
			
			void insertKey(int key){
				
				if ((count+1)> (0.7*size)){
					rehash();
				}
				
				int idx= hash(key);
				int startidx=idx;
				
				while (table[idx]!=empty && table[idx]!=deleted){
					idx = (idx+1)%size;
					if (idx==startidx){
						cout <<"failed to insert"<<endl;
						return;
					}
				}
				table[idx]=key;
				cout <<"inserted: "<<key<<endl;
				count++;
				
			}
			
			
			bool searchKey(int key){
				
				int idx=hash(key);
				int startidx=idx;
				
				while (table[idx]!=empty){
					if (table[idx]==key){
						return true;
					}
					idx=(idx+1)%size;
					if (idx==startidx){
						return false;
					}
					
				}
				return false;
			}
			
			
			bool deleteKey(int key){
				
				int idx=hash(key);
				int startidx= idx;
				
				while (table[idx]!=empty){
					if (table[idx]==key){
						table[idx]=deleted;
						count--;
						return true;
					}
					idx = (idx+1)% size;
					
					if (startidx==idx){
						return false;
					}
				
				}
				return false;	
			}
			
		
void display()  {
        cout << "Rehashing Linear Table (size = " << size << ", count = " << count  << ", loadFactor = " << loadFactor() << ")\n";
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
    // initial small size to demonstrate rehashing
    RehashingLinear ht(5);

    // Insert enough items to trigger rehash
    ht.insertKey(10);
    ht.insertKey(21);
    ht.insertKey(32);
    ht.insertKey(43); // should trigger rehash on next insert possibly
    ht.insertKey(54); // this may trigger rehash

    cout << "After inserts (with rehash when needed):\n";
    ht.display();

    cout << "\nSearch 21: " << (ht.searchKey(21) ? "Found" : "Not Found") << endl;
    cout << "Delete 21: " << (ht.deleteKey(21) ? "Deleted" : "Not Found") << endl;
    cout << "Search 21 again: " << (ht.searchKey(21) ? "Found" : "Not Found") << endl;

    cout << "\nFinal table:\n";
    ht.display();

    return 0;
}
