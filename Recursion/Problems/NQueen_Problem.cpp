#include <iostream>
using namespace std;
void printBoard(char board[][10],int n){
	static  int sol=0;
	sol++;
	cout <<"SOLUTION #"<<sol<<":"<<endl;
	for (int i=0;i<n;i++){
		for (int j=0;j<n;j++){
			cout << board[i][j]<<" ";
		}
		cout <<endl;
	}
	cout <<endl;
}

bool isSafe(char board[][10], int row,int col,int n){
	
	// horizontal
	
	for (int i=0;i<row;i++){
		if (board[i][col]=='Q'){
			return false;
		}
	}
	// vertical 
	for (int j=0;j<n;j++){
		if (board[row][j]=='Q'){
		return false;
	}
	
	}
	// left diagonal
	
	for (int i=row,j=col;i>=0 && j>=0;i--,j--){
		if (board[i][j]=='Q'){
			return false;
		}
		
	}
	
		for (int i=row,j=col;i>=0 && j<n;i--,j++){
		if (board[i][j]=='Q'){
			return false;
		}
		
	}
	
	return true;

}
void nQueen(char board[][10],int row,int n){
	
	
	if (row==n){
		printBoard(board,n);
		return;
	}
	for (int j=0;j<n;j++){
		
		if (isSafe(board,row,j,n)){
			board[row][j]='Q';
			nQueen(board, row+1,n);
			board[row][j]='*';
		}
	}
}


  
int main() {
    int n;
    cout << "Enter number of queens: ";
    cin >> n;
    
    char board[10][10];

    // initialize board with '.'
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            board[i][j] = '*';

    nQueen(board, 0, n);

    return 0;
}



