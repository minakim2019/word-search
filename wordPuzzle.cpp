/*
wordPuzzle.cpp
Mina Kim, mk3bnb
2/28/2020
*/

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "timer.h"
#include "timer.cpp"
#include "hashTable.h"
#include <cstdlib>
#include <unordered_set>

using namespace std;
#define MAXROWS 500
#define MAXCOLS 500
char grid[MAXROWS][MAXCOLS];

// Forward declarations
bool readInGrid (string filename, int &rows, int &cols);
string getWordInGrid (int startRow, int startCol, int dir, int len,
                     int numRows, int numCols);

bool readInGrid(string filename, int& rows, int& cols) {
    // try to open the file
    ifstream file(filename);
    // upon an error, return false
    if (!file.is_open()) {
        return false;
    }

    // first comes the number of rows
    file >> rows;
    cout << "There are " << rows << " rows." << endl;

    // then the columns
    file >> cols;
    cout << "There are " << cols << " cols." << endl;

    // and finally the grid itself
    string data;
    file >> data;

    // close the file
    file.close();

    // convert the string read in to the 2-D grid format into the
    // grid[][] array.
    // In the process, we'll print the grid to the screen as well.
    int pos = 0; // the current position in the input data
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            grid[r][c] = data[pos++];
            cout << grid[r][c];
        }
        cout << endl;
    }
    return true;
}

string getWordInGrid (int startRow, int startCol, int dir, int len,
                      int numRows, int numCols) {
    // the static-ness of this variable prevents it from being
    // re-declared upon each function invocation.  It also prevents it
    // from being deallocated between invocations.  It's probably not
    // good programming practice, but it's an efficient means to return
    // a value.
    static string output;
    output.clear(); // Since it's static we need to clear it
    output.reserve(256); // Can't set capacity in the constructor so do it the first time here

    // the position in the output array, the current row, and the
    // current column
    int r = startRow, c = startCol;
    // iterate once for each character in the output
    for (int i = 0; i < len; i++) {
        // if the current row or column is out of bounds, then break
        if (c >= numCols || r >= numRows || r < 0 || c < 0) {
            break;
        }

        // set the next character in the output array to the next letter
        // in the grid
        output += grid[r][c];

        // move in the direction specified by the parameter
        switch (dir) { // assumes grid[0][0] is in the upper-left
            case 0:
                r--;
                break; // north
            case 1:
                r--;
                c++;
                break; // north-east
            case 2:
                c++;
                break; // east
            case 3:
                r++;
                c++;
                break; // south-east
            case 4:
                r++;
                break; // south
            case 5:
                r++;
                c--;
                break; // south-west
            case 6:
                c--;
                break; // west
            case 7:
                r--;
                c--;
                break; // north-west
        }
    }

    return output;
}


//takes in dictionary file (argv[1]) and grid file (argv[2]) using cmd line parameters
int main(int argc, char** argv){
if(argc != 3){
    cout << "Missing parameters. Please try again." << endl;
    exit(1);
  }
  string dict = argv[1];
  int size = 0;
  string grd = argv[2];

  //Read in dictionary/print out words. Store words in hashtable
  ifstream scanner(dict.c_str());
  string str;
  if(scanner.is_open()){
    while(getline(scanner, str)){
      ++size; //get size of dictionary file for hashtable
    }
    scanner.close();
  }
  else{
    cout<<"file not found" << endl;
  }
  
  hashTable table(size);
  ifstream second_scan(dict.c_str());
  while(getline(second_scan, str)){
    if(str.length() > 2){
      table.insert(str);
    }
  }
  second_scan.close();
  
  //Read in the grid
  scanner.open(grd.c_str());
  int rows, cols;
  bool check = readInGrid(grd, rows, cols); 
  if(!check){
    cout << "failed to read in grid." << endl;
    exit(1);
  }

  timer t;
  t.start();
  //Word search
int numWords = 0;
for(int r = 0; r < rows; r++){ //search rows
  for(int c = 0; c < cols; c++){ //search cols
    for(int dir = 0; dir < 8; dir++){ //search direction
      string first = ""; //first and second are to prevent duplicates
      for(int len = 3; len <= 22; len++){
	string second = "";
	string word = getWordInGrid(r, c, dir, len, rows, cols);
	second = word;
	if(word.length() < 3){
	  break;
	}
	if(table.contains(word) && first != second){ //found
	  ++numWords;
	  first = second;
	  if(dir == 0){
	    cout << "N (" << r << ", " << c << "):  " << word << endl;
	  }
	  if(dir == 1){
	    cout << "NE (" << r << ", " << c << "):  " << word << endl;
	  }
	  if(dir == 2){
	    cout << "E (" << r << ", " << c << "):  " << word << endl;
	  }
	  if(dir == 3){
	    cout << "SE (" << r << ", " << c << "):  " << word << endl;
	  }
	  if(dir == 4){
	    cout << "S (" << r << ", " << c << "):  " << word << endl;
	  }
	  if(dir == 5){
	    cout << "SW (" << r << ", " << c << "):  " << word << endl;
	  }
	  if(dir == 6){
	    cout << "W (" << r << ", " << c << "):  " << word << endl;
	  }
	  if(dir == 7){
 	    cout << "NW (" << r << ", " << c << "):  " << word << endl;
	  }  
	}//endif
      }
    }
  }
 }
 t.stop();
cout << numWords << " words found" << endl;
 cout << t.getTime()*1000 << endl;

return 0;
  
  
}//end main
