#include <iostream>
using namespace std;

const int N=5;
void printSolution(int sol[N][N]);
bool solveMazeUtil(int maze[N][N], int x, int y, int sol[N][N]);
bool isSafe(int maze[N][N], int x, int y);
void solveMaze(int maze[N][N]);

bool isSafe(int maze[N][N], int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < N && maze[x][y] == 1);
}


bool solveMazeUtil(int maze[N][N], int x, int y, int sol[N][N]) {

    if (x == N - 1 && y == N - 1) {
        sol[x][y] = 1;
        return true;
    }

    if (isSafe(maze, x, y) && sol[x][y]==0) {
        sol[x][y] = 1;

    if (solveMazeUtil(maze, x, y + 1, sol)){
		return true;
	}
		if(solveMazeUtil(maze, x, y-1, sol)) {
		return true;
	}
	if(solveMazeUtil(maze, x-1, y, sol)) {
		return true;
	}
    
    if (solveMazeUtil(maze, x + 1, y, sol)){
    	return true;
	} 

        sol[x][y] = 0;
        return false;
    }

    return false;
}




void solveMaze(int maze[N][N]) {
    int sol[N][N] = {0};

    if (!solveMazeUtil(maze, 0, 0, sol)) {
        cout << "No solution exists"<<endl;
        return;
    }

    cout << "Path found (4 directions):"<<endl;
    printSolution(sol);
}

void printSolution(int sol[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << sol[i][j] << " ";
        cout << endl;
    }
}
int main() {
    int maze[N][N] = {
        {1, 0, 0, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 1, 0, 1, 0},
        {1, 1, 1, 1, 0},
        {0, 0, 0, 1, 1}
    };

    solveMaze(maze);
    return 0;
}
