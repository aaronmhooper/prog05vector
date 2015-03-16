// Header file for program 05 with vectors instead of arrays
#include <stdlib.h>        // for atoi
using namespace std;

// Function to count the number of entries in the input file
int CountLines(ifstream& inDataCount)
{
  // Pre:  count = 0, located at top of input file
  // Post: count = number of entries in input file, located back at top of input file
  string line;
  int count = 0;
  
  while (getline(inDataCount, line))
    {
        count++;
    }
    
  inDataCount.clear(); // Empty the file stream buffer to get rid of end-line character
  inDataCount.seekg(0, ios::beg); // Places read bit back at beginning of file
  return count;
}
 
// Function that gets data from input file and assigns it to a two-dimensional vector 10 times
void GetData(int numberOfLines, ifstream& inDataGet, vector<vector <int> >& myData) // file streams and vectors must be passed by reference
{
  // Pre:  Empty two-dimensional vector with size 0x0, located at top of input file
  // Post: Two-dimensional vector filled with a list of 10 numbers copied into 10 columns for vector size 10x10
  string line;
  int a;
  vector<int> row;
  
  while (! inDataGet.eof())
    {
       row.clear();  // Empty a temporary one-dimensional integer type vector, size 0x0
       getline(inDataGet, line);
       a = atoi(line.c_str());  // Convert string output of getline to integer (requires #include stdlib.h)   
       for (int i=0; i<numberOfLines;i++)
          {
            row.push_back(a); // Assign number from input file to temporary vector 10 times, vector size 10x1 when finished
          }
        myData.push_back(row); // Assign temporary vector to 2d vector one row at a time, 2d vector size 10x10 when finished
    }
  inDataGet.clear();
  inDataGet.seekg(0, ios::beg);
}

// Function to print contents of 2d vector into a formatted 10x10 table
void PrintData (ofstream& outData, vector<vector <int> >& myData)
{
  // Pre:  Ouput file is empty
  // Post: Output file contains a formatted 10x10 table with 2d vector contents
  for ( vector<vector<int> >::iterator it1 = myData.begin(); it1 != myData.end(); ++it1 ) // Goes through vector row by row
    {
      	    for ( vector<int>::iterator it2 = (*it1).begin(); it2 != (*it1).end(); ++ it2 ) // Goes through each row column by column
	      {
	      	outData << left << setw(5) << (*it2) << " "; // Prints contents of each row X column coordinate from vector to output file
      	}      
      	outData << endl;// Iterator (it1, it2) is a pointer to a location in the vector
     }                                                 //    must use a * (*it1, *it2) to access the value at the location
  outData << endl;                       //    the iterator is pointing to
}
 
// Fuction that adds one to every even number in the vector
void AddOne(vector<vector <int> >& myData)
{
  // Pre:  Each column matches the input file
  // Post: Every even number has been incremented by one
  for ( vector<vector<int> >::iterator it1 = myData.begin(); it1 != myData.end(); ++it1 )
    {
      for ( vector<int>::iterator it2 = (*it1).begin(); it2 != (*it1).end(); ++ it2 )
	      {
	      	if (*it2%2==0) *it2+=1; //Adds one to each row X column coordinate with an even value
      	}
     }
}

// Function to add two to every number in an odd numbered row (numbering starts at 0)
void AddToOddIndex (vector<vector <int> >& myData, int numberOfLines)
{
  // Pre:  Each value matches input file except even numbers have been incremented by one
  // Post: Every number in an odd numbered row is incremented by two
  for(int i=0; i<numberOfLines; i++) // Increments the variable i (row number) through every row in the vector
    {
      for ( vector<int>::iterator it2 = myData[i].begin(); it2 != myData[i].end(); ++ it2 ) // Iterates through every item (column) in each row
	      {
	      	if (i%2!=0) *it2+=2; // Adds two to each in the row if i (row number) is odd
      	}
     }
}

// Function to find the minimum and maximum values in a two-dimensional vector
void FindMinMax (int numberOfLines, int &min, int &max,vector<vector <int> >& myData)
{
  // Pre:  Min value is 1000 (higher than any number in input file), max value is 0 (lower than any value in input file)
  // Post: Min value is set to lowest number in the vector, max value is set to highest number in the vector
  min = 1000;
  max = 0;
  for ( vector<vector<int> >::iterator it1 = myData.begin(); it1 != myData.end(); ++it1 ) // Iterates through each row
    {
      for ( vector<int>::iterator it2 = (*it1).begin(); it2 != (*it1).end(); ++ it2 ) // Iterates through each item (column) in each row
	      {
	      	if (*it2>max) max=*it2; 
	      	if (*it2<min) min=*it2;
      	}
     }
}

// Function to find the average value of the of all the numbers in the vector
float FindAverage (int numberOfLines, vector<vector <int> >& myData)
{ 
  // Pre:  Total and avg variables are 0
  // Post:  Average value is assigned to avg and retuned to main()
  float total=0.0;
  float avg;
  // Since each column is a copy of the first, only one column needs to be totaled to find the average value
  for (int i=0; i<numberOfLines; i++) // Increments through each row
	  {
	   	total+=myData[i].at(0);  // Adds the value of each location in column 0 to running total
  	}
  avg = float(total)/float(numberOfLines);
  return avg;
}

// Print the minimum, maximum, and average values in a formatted list
void PrintMinMaxAvg (int min, int max, float avg, ofstream& outData)
{
  // Pre:  Output file contains a 10x10 table of values from vector
  // Post: Minimum, maximum, and average values are added in a formatted list at the bottom of the output file
  outData << left << setw(8) << "Max:" << setw(5) << max << endl;
  outData << left << setw(8) << "Min:" << setw(5) << min << endl;
  outData << left << setw(8) << "Avg:" << setw(5) << avg << endl;
  outData << endl;
}

// Function that finds any number in the vector greater than 100 and prints it to the output file in a list with a header
void FindPrintMoreThan100 (int numberOfLines, ofstream& outData, vector<vector <int> >& myData)
{
  // Pre:  Output file contains table, minimum, maximum and average values
  // Post: Every number greater than 100 is added to the end of the output file in a list with a header
  outData << left << "*--<Values greater than 100>--*" << endl;
  for (int i=0; i<numberOfLines; i++) // Every column is identical, so only one is searched to avoid repeating values
    {
      if (myData[i].at(0) > 100) outData << left << myData[i].at(0) << endl;
    }
    outData << endl;
}

// Function to sort the values in a vector from smalles to largest (selection sort) and format the vector with the lowest values in the left 
//     most column and the highest values in the right most column
void Sort (int numberOfLines, vector<vector <int> >& myData)
{
  
  int temp; // Temporary variable used for swapping values
  for (int i=0; i<numberOfLines-1; i++) // Every column is identical so only one column need sorted 
    {
      int low = i; // Storing the index (location) of the smaller value
      for (int j=i+1;j<numberOfLines;j++ )
        {
          if (myData[j].at(0) < myData[low].at(0)) // Compares each locations value with the next locations value
            {
              low=j; // If the lower index has higher value assign the higher index to the variable low
            }        // Loops through the entire column to ensure lowest value has its index assigned to low
        }
      if (low > i) // If the index stored in low is higher than the current location the values of both locations are swapped
       {
         temp = myData[i].at(0);
         myData[i].at(0) = myData[low].at(0);
         myData[low].at(0) = temp;
       }
    }

  int m=9;
  for (int n=numberOfLines-1; n>=0; n--) // Copies the highest value in the first column into every row in the last column
    {                                    // Loops through each lower value and copies the value into the respective column
      for (int p=0; p<numberOfLines; p++)
        {
           myData[p].at(n)=myData[m].at(0);
         }
       m--;
    }
}