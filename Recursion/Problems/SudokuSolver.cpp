#include <iostream>
using namespace std;




bool isSafe(int board[9][9],int row,int col,int dig){
	
	// horizontal
	
	for (int j=0;j<9;j++){
		if (board[row][j]==dig){
			return false;
		}
	}
	
	// vertical 
		for (int i=0;i<9;i++){
		if (board[i][col]==dig){
			return false;
		}
	}
	
	// check grid 3*3 
	int sr = (row/3)*3;
	int sc = (col/3)*3;
	for (int i=sr;i<=sr+2;i++){
		for (int j=sc;j<=sc+2;j++){
			if (board[i][j]==dig){
				return false;
			}
			 
		}
	}
	
	
	return true;
}
bool solveSudoku(int board[9][9], int row,int col){
	
	if (row==9){
		return true;
	}
	
	int nextRow = row;
	int nextCol = col+1;
	if (nextCol ==9){
		nextRow = row +1;
		nextCol =0;
	}
	if (board[row][col]!=0){
		return solveSudoku(board,nextRow,nextCol);
	}
	
	//place correct
		
	for (int dig =1;dig<=9;dig++){
		if (isSafe(board,row,col,dig)){
			board[row][col] = dig;
			if (solveSudoku(board,nextRow,nextCol)){
				return true;
			}
			
			board[row][col]= 0;
		}
	}
	
	return false;
}

void printBoard(int board[9][9]){
	
		for (int i=0;i<9;i++){
			for (int j=0;j<9;j++){
				cout <<board[i][j]<<" ";
				
			}
			cout <<endl;
		}
}

int main() {
    int board[9][9] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    if (solveSudoku(board, 0, 0)) {
        cout << "Solved Sudoku:"<<endl;
        printBoard(board);
    } else {
        cout << "No solution exists!";
    }

    return 0;
}

