#include <iostream>
using namespace std;

int isSafe(int arr[][4],int n,int i,int j,int visited[][4]){
	
	if (i>=0 && j>=0 && i<n && j<n && visited[i][j]==0){
		if (arr[i][j]==1){
			
			return 1;
		}
		if (arr[i][j]==2){
			return 2;
		}
		return -1;	
	}
	return -1;
	
	
	
}
int recMaze(int arr[][4], int n,int r,int c,int visited[][4],int health){
	static int paths=0;
	if (arr[0][0]==0){
		cout << "no starting point"<<endl;
		return 0;
	}
	if (r==n-1 && c==n-1&& health>0){
		paths++;
		for (int i=0;i<n;i++){
			for (int j=0;j<n;j++){
				cout << visited[i][j] <<" ";
			}
			
			cout  <<endl;
		}
		cout <<"Health Remaining:" <<health<<endl;
		cout <<endl;
		return 1;
	}
	//move right
	int val=isSafe(arr,n,r,c+1,visited);
	if(val!=-1 && health-val>0){
		
		health= health-val;
		visited[r][c+1]=1;
		 recMaze(arr,n,r,c+1,visited,health);
		visited[r][c+1]=0;
		health= health+val;
	}
	
	// move down
		 val=isSafe(arr,n,r+1,c,visited);
		if(val!=-1 && health-val>0){
			health= health-val;
		visited[r+1][c]=1;	
		 recMaze(arr,n,r+1,c,visited,health);
		visited[r+1][c]=0;
			health= health+val;
		
	}	
	//move left
			 val =isSafe(arr,n,r,c-1,visited);
		if(val!=-1 && health-val>0){
				health= health-val;
			visited[r][c-1]=1;
		 recMaze(arr,n,r,c-1,visited,health);
			visited[r][c-1]=0;
			health= health+val;
	}		
	
	
	// move up
			val = isSafe(arr,n,r-1,c,visited);
		if(val!=-1 && health-val>0){
				health= health-val;
		visited[r-1][c]=1;
		 recMaze(arr,n,r-1,c,visited,health);
		visited[r-1][c]=0;
			health= health+val;
	}	
	
		
	return paths;
}


int main (){
	int n=4;
	int arr[4][4] = {
    {1, 0, 0, 0},
    {1, 2, 0, 1},
    {1, 2, 0, 0},
    {1, 2, 1, 1}
};


	
	int visited[4][4] ={0};
		visited[0][0]=1;
	
cout <<	"total possible paths:"<< recMaze(arr,n,0,0,visited,16);
}
