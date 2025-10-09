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
int recMaze(int arr[][4], int n,int r,int c,int visited[][4],string path){
	
	
	if (r==n-1 && c==n-1){
		cout <<path<<endl;
		
		path="";
		for (int i=0;i<n;i++){
			for (int j=0;j<n;j++){
				cout <<visited[i][j]<<" ";
			}
			cout <<endl;
		}
		return 1;
	}
	//move right
	if(isSafe(arr,n,r,c+1,visited)){
		visited[r][c+1]=1;
		 recMaze(arr,n,r,c+1,visited,path+'R');
		visited[r][c+1]=0;
	}
	
	//move left
		if(isSafe(arr,n,r,c-1,visited)){
			visited[r][c-1]=1;
		 recMaze(arr,n,r,c-1,visited,path+'L');
			visited[r][c-1]=0;
	}		
	
	// move up
		if(isSafe(arr,n,r-1,c,visited)){
		visited[r-1][c]=1;
		 recMaze(arr,n,r-1,c,visited,path+'U');
		visited[r-1][c]=0;
	}	
	
	// move down
		if(isSafe(arr,n,r+1,c,visited)){
		visited[r+1][c]=1;	
		 recMaze(arr,n,r+1,c,visited,path+'D');
		visited[r+1][c]=0;
		
	}	
				
	
}


int main (){
	int n=4;
	int arr[4][4] = {
    {1, 0, 0, 0},
    {1, 1, 0, 1},
    {1, 1, 0, 0},
    {1, 1, 1, 1}
};

	string path;
	
	int visited[4][4] ={0};
		visited[0][0] =1;
	
	recMaze(arr,n,0,0,visited,path);
}
