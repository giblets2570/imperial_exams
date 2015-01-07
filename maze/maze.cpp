#include <iostream>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <cstring>

#include "maze.h"

using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* helper function which allocates a dynamic 2D array */
char **allocate_2D_array(int rows, int columns) {
  char **m = new char *[rows];
  assert(m);
  for (int r=0; r<rows; r++) {
    m[r] = new char[columns];
    assert(m[r]);
  }
  return m;
}

/* helper function which deallocates a dynamic 2D array */
void deallocate_2D_array(char **m, int rows) {
  for (int r=0; r<rows; r++)
    delete [] m[r];
  delete [] m;
}

/* helper function for internal use only which gets the dimensions of a maze */
bool get_maze_dimensions(const char *filename, int &height, int &width) {
  char line[512];
  
  ifstream input(filename);

  height = width = 0;

  input.getline(line,512);  
  while (input) {
    if ( (int) strlen(line) > width)
      width = strlen(line);
    height++;
    input.getline(line,512);  
  }

  if (height > 0)
    return true;
  return false;
}

/* pre-supplied function to load a maze from a file*/
char **load_maze(const char *filename, int &height, int &width) {

  bool success = get_maze_dimensions(filename, height, width);
  
  if (!success)
    return NULL;

  char **m = allocate_2D_array(height, width);
  
  ifstream input(filename);

  char line[512];

  for (int r = 0; r<height; r++) {
    input.getline(line, 512);
    strcpy(m[r], line);
  }
  
  return m;
}

/* pre-supplied function to print a maze */
void print_maze(char **m, int height, int width) {
  cout << setw(4) << " " << " ";
  for (int c=0; c<width; c++)
    if (c && (c % 10) == 0) 
      cout << c/10;
    else
      cout << " ";
  cout << endl;

  cout << setw(4) << " " << " ";
  for (int c=0; c<width; c++)
    cout << (c % 10);
  cout << endl;

  for (int r=0; r<height; r++) {
    cout << setw(4) << r << " ";    
    for (int c=0; c<width; c++) 
      cout << m[r][c];
    cout << endl;
  }
}

bool find_marker(char ch, char** maze, int height, int width, int& row, int& column){

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            if(maze[i][j] == ch){
                row = i;
                column = j;
                return true;
            }
        }
    }
    row = -1;
    column = -1;
    return false;
}


bool valid_solution(const char* path, char** maze, int height, int width){
    int step = 0,row,col;
    if(!find_marker('>',maze,height,width,row,col))
        return false;

    while(path[step] != '\0'){
        move(path[step],row,col);
        if(blockage(maze,height,width,row,col))
            return false;
        step++;
    }
    if(maze[row][col] != 'X')
        return false;
    return true;
}

void move(char direction, int& row, int& column){
    switch(direction){
        case 'E':
            column++;
            break;
        case 'W':
            column--;
            break;
        case 'N':
            row--;
            break;
        case 'S':
            row++;
            break;
        default:
            break;
    } 
    return;
}

void moveBack(char direction, int& row, int& column){
    switch(direction){
        case 'E':
            column--;
            break;
        case 'W':
            column++;
            break;
        case 'N':
            row++;
            break;
        case 'S':
            row--;
            break;
        default:
            break;
    } 
    return;
}

bool blockage(char** maze, int height, int width, int row, int col){
    if(row < 0 || col < 0 || row >=height || col >= width){
        return true;
    }
    return (maze[row][col] == '-' || maze[row][col] == '+' || maze[row][col] == '|' || maze[row][col] == '#');
}

void valid_directions(char** maze, int height, int width, int row, int col, char* result, char last){
    strcpy(result,"");
    int i = 0;
    //cout << "In valid directions ";
    if(!blockage(maze,height,width,row+1,col))
        result[i++] = 'S';
    if(!blockage(maze,height,width,row-1,col))
        result[i++] = 'N';
    if(!blockage(maze,height,width,row,col+1))
        result[i++] = 'E';
    if(!blockage(maze,height,width,row,col-1))
        result[i++] = 'W';
    result[i] = '\0';
    //cout << result << endl;
    return;
}

const char* find_path(char** maze, int height, int width, char start, char end){
    char path[512];
    int row, col;
    find_marker(start,maze,height,width,row,col);
    if(navigate(maze,path,height,width,row,col,end,' ')){
        return path;
    }
    return "no solutions";
}

bool navigate(char** maze, char* path, int height, int width, int row, int col,char end, char last){

    if(maze[row][col] == end){
        maze[row][col] = '#';
        return true;
    }

    maze[row][col] = '#';

    char directions[4];

    valid_directions(maze,height,width,row,col,directions,last);

    if(strlen(directions) == 0){
        return false;
    }

    int pathLength = strlen(path);
    char* newPath = new char[pathLength+2];
    newPath[pathLength+1] = '\0';
    int i = 0;

    while(directions[i] != '\0'){

        strcpy(newPath,path);
        newPath[pathLength] = directions[i];

        move(directions[i],row,col);
        if(navigate(maze,newPath,height,width,row,col,end,directions[i])){
            strcpy(path,newPath);
            delete newPath;
            return true;
        }
        maze[row][col] = ' ';
        moveBack(directions[i],row,col);
        i++;
    }
    delete newPath;
    return false;
}