#include <iostream>
using namespace std;

bool isSafe(int arr[][4],int n,int i,int j,int visited[][4]){
	
	if (i>=0 && j>=0 && i<n && j<n && visited[i][j]==0){
		if (arr[i][j]==1){
			return true;
		}
		return false;	
	}
	return false;
	
	
	
}
bool recMaze(int arr[][4], int n,int r,int c,int visited[][4]){
	static int paths=0;
	if (arr[0][0]==0){
		cout << "no starting point";
		return 0;
	}
	if (r==n-1 && c==n-1){
		paths++;
		for (int i=0;i<n;i++){
			for (int j=0;j<n;j++){
				cout << visited[i][j] <<" ";
			}
			
			cout  <<endl;
		}
		cout <<endl;
		return true;
	}
	//move right
	if(isSafe(arr,n,r,c+1,visited)){
		visited[r][c+1]=1;
		if( recMaze(arr,n,r,c+1,visited)) return true;
		visited[r][c+1]=0;
	}
	
	// move down
		if(isSafe(arr,n,r+1,c,visited)){
		visited[r+1][c]=1;	
		if (recMaze(arr,n,r+1,c,visited)) return true;
		visited[r+1][c]=0;
		
	}	
	//move left
		if(isSafe(arr,n,r,c-1,visited)){
			visited[r][c-1]=1;
		if ( recMaze(arr,n,r,c-1,visited)) return true;
			visited[r][c-1]=0;
	}		
	
	// move up
		if(isSafe(arr,n,r-1,c,visited)){
		visited[r-1][c]=1;
		if (recMaze(arr,n,r-1,c,visited)) return true;
		visited[r-1][c]=0;
	}	
	
				
	return false;
}


int main (){
	int n=4;
	int arr[4][4] = {
    {1, 0, 0, 0},
    {1, 1, 1, 1},
    {1, 1, 0, 0},
    {1, 1, 1, 1}
};


	
	int visited[4][4] ={0};
		visited[0][0]=1;
	
cout << recMaze(arr,n,0,0,visited);
}
