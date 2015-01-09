#include <iostream>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace std;

#include "tube.h"

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* internal helper function which allocates a dynamic 2D array */
char **allocate_2D_array(int rows, int columns) {
  char **m = new char *[rows];
  assert(m);
  for (int r=0; r<rows; r++) {
    m[r] = new char[columns];
    assert(m[r]);
  }
  return m;
}

/* internal helper function which deallocates a dynamic 2D array */
void deallocate_2D_array(char **m, int rows) {
  for (int r=0; r<rows; r++)
    delete [] m[r];
  delete [] m;
}

/* internal helper function which gets the dimensions of a map */
bool get_map_dimensions(const char *filename, int &height, int &width) {
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

/* pre-supplied function to load a tube map from a file*/
char **load_map(const char *filename, int &height, int &width) {

  bool success = get_map_dimensions(filename, height, width);
  
  if (!success)
    return NULL;

  char **m = allocate_2D_array(height, width);
  
  ifstream input(filename);

  char line[512];
  char space[] = " ";

  for (int r = 0; r<height; r++) {
    input.getline(line, 512);
    strcpy(m[r], line);
    while ( (int) strlen(m[r]) < width )
      strcat(m[r], space);
  }
  
  return m;
}

/* pre-supplied function to print the tube map */
void print_map(char **m, int height, int width) {
  cout << setw(2) << " " << " ";
  for (int c=0; c<width; c++)
    if (c && (c % 10) == 0) 
      cout << c/10;
    else
      cout << " ";
  cout << endl;

  cout << setw(2) << " " << " ";
  for (int c=0; c<width; c++)
    cout << (c % 10);
  cout << endl;

  for (int r=0; r<height; r++) {
    cout << setw(2) << r << " ";    
    for (int c=0; c<width; c++) 
      cout << m[r][c];
    cout << endl;
  }
}

/* pre-supplied helper function to report the errors encountered in Question 3 */
const char *error_description(int code) {
  switch(code) {
  case ERROR_START_STATION_INVALID: 
    return "Start station invalid";
  case ERROR_ROUTE_ENDPOINT_IS_NOT_STATION:
    return "Route endpoint is not a station";
  case ERROR_LINE_HOPPING_BETWEEN_STATIONS:
    return "Line hopping between stations not possible";
  case ERROR_BACKTRACKING_BETWEEN_STATIONS:
    return "Backtracking along line between stations not possible";
  case ERROR_INVALID_DIRECTION:
    return "Invalid direction";
  case ERROR_OFF_TRACK:
    return "Route goes off track";
  case ERROR_OUT_OF_BOUNDS:
    return "Route goes off map";
  }
  return "Unknown error";
}

/* presupplied helper function for converting string to direction enum */
Direction string_to_direction(const char *token) {
  const char *strings[] = {"N", "W", "NW", "NE", "S", "E", "SE", "SW"};
  for (int n=0; n<8; n++) {
    if (!strcmp(token, strings[n])) 
      return (Direction) n;
  }
  return INVALID_DIRECTION;
}


bool get_symbol_position(char** map, int height, int width, char target, int& r, int& c){
    
    for(r = 0; r < height; r++){
	for(c = 0; c < width; c++){
	    if(map[r][c] == target)
		return true;
	}
    } 
    r = -1; c = -1;
    return false;
}

char get_symbol_for_station_or_line(const char* name){
    
    const char* filenames[2] = {"stations.txt","lines.txt"};
    ifstream in;
    char placeSymbol, space, placeName[128];
    for(int d = 0; d < 2; d++){
	in.open(filenames[d]);
	in.get(placeSymbol);
	while(!in.eof()){
	    in.get(space);
	    in.getline(placeName,128);
	    if(!strcmp(placeName,name)){
		in.close();
		return placeSymbol;
	    }
	    in.get(placeSymbol);
	}
	in.close();
    }
    return ' ';
}

char* get_name_for_station_or_line(char symbol){
    
    const char* filenames[2] = {"stations.txt","lines.txt"};
    ifstream in;
    char placeSymbol, space;

    static char placeName[128] = "";

    for(int d = 0; d < 2; d++){
	in.open(filenames[d]);
	in.get(placeSymbol);
	while(!in.eof()){
	    in.get(space);
	    in.getline(placeName,128);
	    if(placeSymbol == symbol){
		in.close();
		return placeName;
	    }
	    in.get(placeSymbol);
	}
	in.close();
    }
    strcpy(placeName," ");
    return placeName;
}

int validate_route(char** map, int height, int width, const char* start_station, char* route, char* destination){

    char startSymbol = get_symbol_for_station_or_line(start_station);
    if(!isalnum(startSymbol))
	return ERROR_START_STATION_INVALID;
    
    int currentRow, currentCol, linechanges = 0;
    char currentLine = '@';

    if(!get_symbol_position(map, height, width,startSymbol,currentRow,currentCol))
	return ERROR_START_STATION_INVALID;

    bool atStation = true, justAtStation = false;
    char* p;
    Direction current, previous = INVALID_DIRECTION;
    p = strtok(route,",");

    while(p){
	//Taking care of the movement
	int movement = move(map,height,width,p,currentRow,currentCol);
	if(movement != 0)
	    return movement;
	
	if(map[currentRow][currentCol] == ' ')
	    return ERROR_OUT_OF_BOUNDS;

	current = string_to_direction(p);
	
	//checking for linechanges

	justAtStation = atStation;
	atStation = isalnum(map[currentRow][currentCol]);

	if(backHopping(current, previous)){
	    if(justAtStation)
		linechanges++;
	    else
		return ERROR_BACKTRACKING_BETWEEN_STATIONS;
	}
	if(justAtStation){
	    if(map[currentRow][currentCol] != currentLine){
		if(previous != INVALID_DIRECTION)
		    linechanges++;
		currentLine = map[currentRow][currentCol];
	    }
	}

	else{
	    if(!atStation){
		if(map[currentRow][currentCol] != currentLine){
		    return ERROR_LINE_HOPPING_BETWEEN_STATIONS;
		}
	    }
	}

	previous = current;

	p = strtok(NULL,",");
    }

    if(!isalnum(map[currentRow][currentCol]))
	return ERROR_ROUTE_ENDPOINT_IS_NOT_STATION;
    
    strcpy(destination,get_name_for_station_or_line(map[currentRow][currentCol]));
    
    if(!strcmp(destination," "))
	return ERROR_ROUTE_ENDPOINT_IS_NOT_STATION;

    return linechanges;
}

int move(char** maze, int height, int width, char* dir, int& row, int& col){
    Direction d = string_to_direction(dir);
    if(d == ERROR_INVALID_DIRECTION)
	return d;
    switch(d){
    case N:
	row--;
	break;
    case E:
	col++;
	break;
    case S:
	row++;
	break;
    case W:
	col--;
	break;
    case NW:
	row--;
	col--;
	break;
    case NE:
	row--;
	col++;
	break;
    case SW:
	row++;
	col--;
	break;
    case SE:
	row++;
	col++;
	break;
    default:
	break;
    }
    if(row < 0|| row >= height)
	return ERROR_OUT_OF_BOUNDS;
    if(col < 0 || col >= width)
	return ERROR_OUT_OF_BOUNDS;
    return 0;
}

bool backHopping(Direction current, Direction previous){
    if(previous == INVALID_DIRECTION)
	return false;
    if(current == previous - 4)
	return true;
    if(current == previous + 4)
	return true;
    return false;
}
