// Aaron Hooper
// CS116
// Program 05 (with vectors)
// This program takes a list of integers from an input file, duplicates the list for a total of ten lists, adds one to every even number, 
//    adds two to every number in every other list, finds the minimum, maximum, and average values from the list, finds every value more
//    than 100 and prints the results.  It then sorts the numbers with the lowest filling the left most column and the highest in the right.
//
//  
// 1.  Declare input and output file streams, vector, and variables
// 2.  Open input and output data files
// 3.  Count the number of entries in the input file and store the value in numberOfLines
// 4.  Get data from input file and store it in a two-dimensional vector
// 5.  Add one to every even number in the list
// 6.  Add two to every number in an odd numbered column (number starts at 0)
// 7.  Print the contents of the vector into a formatted table with 10 rows and 10 columns
// 8.  Find the minimum, maximum, and average values 
// 9.  Print the minimum, maximum, and average values in a formatted list
// 10. Find every number greater than 100 and print them in a list
// 11. Sort the contents of the two-dimensional vector with the smallest numbers filling the left most column and the largest in the right
// 12. Print the contents of the sorted vector into a formatted table with 10 rows and 10 columns
// 13. Close input and output files


#include <iostream>        // for getline
#include <fstream>         // for ifstream and ofstream
#include <iomanip>         // for setw and left
#include <vector>          // for vector
#include "prog05vector.h"  // for function declarations
using namespace std;

int main()
{
  // Declare input and output file streams, vectors, and variables
  ifstream inData;
  ofstream outData;
  vector<vector<int> > myData; // Declare a two-dimensional vector of integer type (a vector filled with other integer type vectors)
  int numberOfLines, min, max;
  
  // Open input and output data files
  inData.open("in.data");
  outData.open("out.data");
  
  // Count the number of entries in the input file and store the value in numberOfLines
  numberOfLines = CountLines(inData);
  
  // Get data from input file and store it in a two-dimensional vector
  GetData(numberOfLines,inData, myData);
  
  // Add one to every even number in the list
  AddOne(myData);
  
  // Add two to every number in an odd numbered column (number starts at 0)
  AddToOddIndex(myData, numberOfLines);
  
  // Print the contents of the vector into a formatted table with 10 rows and 10 columns
  PrintData(outData, myData);
  
  // Find the minimum, maximum, and average values 
  FindMinMax(numberOfLines, min, max, myData);
  float avg = FindAverage(numberOfLines, myData);
  
  // Print the minimum, maximum, and average values in a formatted list
  PrintMinMaxAvg(min, max, avg, outData);
  
  // Find every number greater than 100 and print them in a list
  FindPrintMoreThan100(numberOfLines, outData, myData);
  
  // Sort the contents of the two-dimensional vector with the smallest numbers filling the left most column and the largest in the right
  Sort(numberOfLines, myData);
  
  // Print the contents of the sorted vector into a formatted table with 10 rows and 10 columns
  PrintData(outData, myData);
  
  // Close input and output files
  inData.close();
  outData.close();
}