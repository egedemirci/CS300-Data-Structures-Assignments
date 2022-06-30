#include <iostream>
#include <string>
#include "Stack.h"
#include "Stack.cpp"
#include <fstream>
#include <vector>
#include <random>
using namespace std;

//Ege Demirci - Homework 1 - Maze - 28287



//This cell struct will help to build a maze.
struct cell{
	int x_coordinate;
	int y_coordinate;
	bool up_wall;
	bool down_wall;
	bool left_wall;
	bool right_wall;
	bool visit_check;
	cell (int x = 0, int y=0){
		this->x_coordinate = x;
		this->y_coordinate = y;
	};
};

//
//This function controls the neighbor cells, if all the neighbors are visited it will return true,
//	if one or none of the neighbors are visited it will return false.
bool neighborCheck(vector<vector<cell>> maze,int y,int x,int row,int column){
	if (y == 0 && x == 0){  /*lower left corner*/
		return maze[y+1][x].visit_check && maze[y][x+1].visit_check;
	}	
	else if(x==0 && y==row-1){ /*upper left corner*/
		return maze[y-1][x].visit_check && maze[y][x+1].visit_check;
	}
	else if(x==column-1 && y==0){ /*lower right corner*/
		return maze[y][x-1].visit_check && maze[y+1][x].visit_check;
	}
	else if(x==column-1 && y==row-1){ /*upper right corner*/
		return maze[y][x-1].visit_check && maze[y-1][x].visit_check;
	}
	else if ((y == 0 && x != 0 && x != column-1)){ /*low edges*/
		return maze[y][x-1].visit_check && maze[y][x+1].visit_check && maze[y+1][x].visit_check;
	}
	else if((y==row-1 && x !=0 && x!=column-1)){ /*up edges*/
		return maze[y][x-1].visit_check && maze[y][x+1].visit_check && maze[y-1][x].visit_check;
	}
	else if((y != 0 && y != row-1 && x==0)) { /*left edges*/
		return maze[y-1][x].visit_check && maze[y+1][x].visit_check && maze[y][x+1].visit_check;
	}
	else if ((x == column-1 && y != row-1 && y !=0)){ /*right edges */
		return maze[y-1][x].visit_check && maze[y+1][x].visit_check && maze[y][x-1].visit_check;
	}
	else{/* not edge or corner points*/
		return maze[y][x-1].visit_check && maze[y][x+1].visit_check 
			&& maze[y+1][x].visit_check && maze[y-1][x].visit_check;
	}
}

//This function controls paths, if one neighbor cell is a visited and the wall which connects them are empty it will
//	return true.
bool pathCheck(vector<vector<cell>> maze,int y,int x){
	bool up=false,down=false,left=false,right=false;
	if ((maze[y][x].up_wall == 0) && (maze[y+1][x].visit_check == 0)){ /*check all neighbors.*/
		up = true;
	}
	if ((maze[y][x].left_wall == 0) && (maze[y][x-1].visit_check == 0)){
		left = true;
	}
	if ((maze[y][x].right_wall == 0) && (maze[y][x+1].visit_check == 0)){
		right = true;
	}
	if ((maze[y][x].down_wall == 0) && (maze[y-1][x].visit_check == 0)){
		down = true;
	}
	return (left || right || down || up);
}
vector<vector<cell>> mazeCreator(int row, int column){
	cell dummyCell; 
	vector<vector<cell>> maze(row,vector<cell>(column,dummyCell)); /*cell Matrix to construct maze.*/
	for (int k=0; k<row; k++){ /*assigns values to cells. by default all walls are full and all cells are visited.*/
		for (int j=0; j<column;j++){
			maze[k][j].x_coordinate = j;maze[k][j].y_coordinate = k;
			maze[k][j].up_wall = 1;	maze[k][j].down_wall = 1;
			maze[k][j].left_wall = 1; maze[k][j].right_wall = 1;
			maze[k][j].visit_check = 0;
		}
	}
	int currX=0,currY=0, visitCounter = 0, cellCounter = row*column,direction;
	Stack<cell> visitedCells; /*This stack will control all the process.*/
	visitedCells.push(maze[currY][currX]); /*add 0,0 coordinates to the stack.*/
	visitCounter++;/* since 0,0 is visited, visitcounter is now 1 and convert 0,0 visit_check to true.*/
	maze[currY][currX].visit_check = 1;
	while (visitCounter < cellCounter){ /*This while loop will run until all cells are visited.*/
		currX =  visitedCells.top().x_coordinate; /*Take current X of the top cell of the stack.*/
		currY =  visitedCells.top().y_coordinate; /*Take current Y of the top cell of the stack.*/
		direction = rand() % 4; /*Random number between 0 and 3.*/
		//If direction is 0, direction is UP so we will check up neighbor.
		if (direction == 0 && currY < row-1 && maze[currY+1][currX].visit_check == 0){
			maze[currY+1][currX].visit_check = 1;
			maze[currY][currX].up_wall = 0;
			maze[currY+1][currX].down_wall = 0;
			visitedCells.push(maze[currY+1][currX]);
			currY += 1;	visitCounter+=1;	
		}
		//If direction is 1, direction is left so we will check left neighbor.
		else if (direction == 1 && currX > 0 && maze[currY][currX-1].visit_check == 0){
			maze[currY][currX-1].visit_check = 1;
			maze[currY][currX].left_wall = 0;
			maze[currY][currX-1].right_wall = 0;
			visitedCells.push(maze[currY][currX-1]);
			currX -=1; visitCounter +=1;
		}
		//If direction is 2, direction is right so we will check right neighbor.
		else if (direction == 2 && currX < column-1 && maze[currY][currX+1].visit_check == 0){
			maze[currY][currX+1].visit_check = 1;
			maze[currY][currX+1].left_wall = 0;
			maze[currY][currX].right_wall = 0;
			visitedCells.push(maze[currY][currX+1]);
			currX +=1; visitCounter +=1;
		}
		//If direction is 3, direction is down so we will check up neighbor.
		else if (direction == 3 && currY > 0 && maze[currY-1][currX].visit_check == 0){
			maze[currY-1][currX].visit_check = 1;
			maze[currY-1][currX].up_wall = 0;
			maze[currY][currX].down_wall = 0;
			visitedCells.push(maze[currY-1][currX]);
			currY -=1; visitCounter +=1;
		}
		//If all neighbors are visited, pop the top cell and restart the process.
		if (neighborCheck(maze,currY,currX,row,column) == true){
			visitedCells.pop();
		}
	}
	visitedCells.makeEmpty();
	return maze; /*return the matrix.*/
}



void pathfinder(vector<vector<cell>> maze,int id,int entryX,int entryY,int exitX,int exitY){
	int row = maze.size();
	int column = maze[0].size();
	for(int i=0; i < row; i++){ /*For the pathfinder, convert all the cells visited_check to false.*/
		for(int k=0;k<column;k++){
			maze[i][k].visit_check = 0;
		}
	}
	Stack<cell> printStack;
	Stack<cell> pathStack;
	int cellCounter = row*column,direction=0,currX=entryX, currY=entryY; /*same process as mazeCreator.*/
	pathStack.push(maze[currY][currX]);
	maze[currY][currX].visit_check = 1;
	bool gameOver = false; /*this boolean will check the game.*/
	while(gameOver == false){ /*run until enter and exit coordinates became equal.*/
		currX =  pathStack.top().x_coordinate;
		currY =  pathStack.top().y_coordinate;
		direction = rand() % 4;
		if (currX == exitX && currY == exitY){ /*If enter and exit coordinates are equal convert gameOver to true.*/
			gameOver = true;
			string filename = "maze_" + to_string(id) + "_path_" + to_string(entryX) + "_"
		+ to_string(entryY) + "_" + to_string(exitX) + "_" + to_string(exitY) + ".txt"; 
			ofstream output;
			output.open(filename.c_str()); 
			while(pathStack.isEmpty() == false){ /*Pop the pathStack and push the elements to the printStack.*/
                printStack.push(pathStack.topAndPop()); 
            }
			while (!printStack.isEmpty()) {
				output << printStack.top().x_coordinate << " " << printStack.top().y_coordinate << endl; 
                printStack.pop();
            }
			break;
		}
		//If direction is 0, the direction is up, check upper wall and upper neighbors.
		if (direction == 0 && currY < row-1 && maze[currY+1][currX].visit_check == 0 && maze[currY][currX].up_wall == 0){
			maze[currY+1][currX].visit_check = 1;
			pathStack.push(maze[currY+1][currX]);
			currY += 1;
		}
		//If direction is 1, the direction is left, check left wall and left neighbors.
		else if (direction == 1 && currX > 0 && maze[currY][currX-1].visit_check == 0 && maze[currY][currX].left_wall == 0){
			maze[currY][currX-1].visit_check = 1;
			pathStack.push(maze[currY][currX-1]);
			currX -=1;
		}
		//If direction is 2, the direction is right, check right wall and right neighbors.
		else if (direction == 2 && currX < column-1 && maze[currY][currX+1].visit_check == 0 && maze[currY][currX].right_wall==0){
			maze[currY][currX+1].visit_check = 1;
			pathStack.push(maze[currY][currX+1]);
			currX +=1; 
		}
		//If direction is 3, the direction is down, check down wall and down neighbors.
		else if (direction == 3 && currY > 0 && maze[currY-1][currX].visit_check == 0 && maze[currY][currX].down_wall == 0){
			maze[currY-1][currX].visit_check = 1;
			pathStack.push(maze[currY-1][currX]);
			currY -=1; 
		}
		//If there is no road to go, pop the pathStack.
		if ((currX != exitX || currY !=exitY) && ( (neighborCheck(maze,currY,currX,row,column) == 1) || (pathCheck(maze,currY,currX) == 0)) ){
			pathStack.pop();
		}
	}
	pathStack.makeEmpty();
	printStack.makeEmpty();
}

//This function creates output maze file.
void mazeOutput(vector<vector<cell>> maze, int id){
	int row = maze.size();
	int column = maze[0].size();
	ofstream output;
	string filename = "maze_" + to_string(id) + ".txt";
	output.open(filename.c_str());
	output << row << " " << column << endl;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			output << "x=" << maze[i][j].x_coordinate << " y=" <<  maze[i][j].y_coordinate << " l=" <<  maze[i][j].left_wall <<
				" r=" <<  maze[i][j].right_wall << " u=" <<  maze[i][j].up_wall << " d=" <<  maze[i][j].down_wall << endl;
		}
	}
	output.close();
}

int main(){
    vector<vector<vector<cell>>> mazeVector;
	int numberOfMazes, mazeID, rows, columns, entryX, entryY, exitX,exitY;
	cout << "Enter the number of mazes: "; /*Input from the user.*/
	cin >> numberOfMazes;
	cout << endl;
	cout << "Enter the number of rows and columns (M and N): ";
	cin >> rows >> columns;
	cout << endl;
	for(int z = 0; z < numberOfMazes; z++){ /*Create the mazes.*/
		mazeVector.push_back(mazeCreator(rows,columns));
		mazeOutput(mazeVector[z], z+1); /*Create the maze files. */
	}

	cout << "All mazes are generated." << endl << endl;
	cout << "Enter a maze ID between 1 to " << numberOfMazes << " inclusive to find a path: ";
	cin >> mazeID;
	cout << endl;
	cout << "Enter x and y coordinates of the entry points (x,y) or (column,row): ";
	cin >> entryX >> entryY;
	cout << endl;
	cout << "Enter x and y coordinates of the exit points (x,y) or (column,row): ";
	cin >> exitX >> exitY;
	
	pathfinder(mazeVector[mazeID-1], mazeID, entryX,entryY,exitX, exitY); /*create the pathfinder file. */
}
