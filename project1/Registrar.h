#pragma once
#include <string>
#include <stdexcept>
#include "Student.h"

using namespace std;

class Registrar {
public:

	Registrar(); //default constructor
	Registrar(const Registrar& rhs); // copy constructor
	Registrar& operator = (const Registrar& rhs); //object operator
	void readTextfile(string filename); // Load information from a text file with the given filename: THIS IS COMPLETE
	void addLine(string courseName, string cwid, char grade); // process a line from the text file
	Student& getStudent(string cwid) const; // return the Student object corresponding to a given CWID

private:

	string filename; //name of txt file
	int numOfStudents; //current member of students in the array
	int maxSize; //max size of students that can be stored
	Student *_studentAR; //array to hold students

};
