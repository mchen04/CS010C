#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

int main() {
   //initializing all variables needed
   string filename, FirstName, LastName ;
   double score1, score2, score3, average ;
   double midterm1avg = 0, midterm2avg = 0,  finalavg = 0 ; //averages must be initializated at 0 to add values to them
   char grade ;
   double count = 0 ; //count starts at 0 to keep track
   
   cin >> filename ; //input filename
   
   ifstream inFS ; //making ifstream
   inFS.open(filename) ; //opening file in ifstream using filename
   
   if (!inFS.is_open()) //checking if ifstream file opened
   {
      cout << filename << "did not open." ;
      return 0 ;
   }
   
   ofstream outFS ; //making ofstream
   outFS.open("report.txt") ; //opening a file to output onto
   
   if (!outFS.is_open()) //checking if ofstream file opened 
   {
      cout << "report.txt did not open." ;   
      return 1 ;
   }
   
   //while loop which takes in a set amount of variables
   while (inFS >> FirstName >> LastName >> score1 >> score2 >> score3) { 
      average = (score1 + score2 + score3) / 3 ; //calculates average 
      //adds to overall value of each test
      midterm1avg += score1 ; 
      midterm2avg += score2 ;
      finalavg += score3 ;
      count++ ; //increases per person, used for average calculation at end
      
      //if, if else, and else statements to determine grade letter
      if (average >= 90) {
         grade = 'A' ;
      }
      else if (average >= 80) 
      {
         grade = 'B' ;
      }
      else if (average >= 70) 
      {
         grade = 'C' ;
      }
      else if (average >= 60) 
      {
         grade = 'D' ;
      }
      else 
      {
         grade = 'F' ;
      }
      
      //outputting to file all student information
      outFS << FirstName << "\t" << LastName << "\t" << score1 << "\t" << score2 << "\t" << score3 << "\t" << grade << endl ;
   }
   outFS << endl ;
   
   //calculating averages of all students
   midterm1avg /= count ;
   midterm2avg /= count ;
   finalavg /= count ;
   
   outFS << fixed << setprecision(2) ; //set decimal points to 2 
   //outputting all student calcualted scores
   outFS << "Averages: midterm1 " << midterm1avg << ", midterm2 " << midterm2avg << ", final " << finalavg << endl ;
   
   //closing both files
   inFS.close() ;
   outFS.close() ;
   
   return 0;
}
