#include <iostream>
#include <fstream>
#include <stdexcept>
#include "Registrar.h"

using namespace std;

//default constructor
Registrar::Registrar(){

	_studentAR = new Student[10];
	numOfStudents = 0;
	maxSize = 10;

}

//copy constructor
Registrar::Registrar(const Registrar &rhs){

	numOfStudents = rhs.numOfStudents;
	maxSize = rhs.maxSize;

	_studentAR =  new Student[rhs.maxSize];

	for(int i = 0; i < maxSize; i++){

		_studentAR[i] = rhs._studentAR[i];

	}

}

//object operator
Registrar& Registrar::operator = (const Registrar &rhs){

	delete[] _studentAR;

	numOfStudents = rhs.numOfStudents;
	maxSize = rhs.maxSize;

	_studentAR =  new Student[rhs.maxSize];

   for(int i = 0; i < maxSize; i++){

	   _studentAR[i] = rhs._studentAR[i];
   }

	return *this;

}


// Load information from a text file with the given filename
// THIS FUNCTION IS COMPLETE
void Registrar::readTextfile(string filename) {
	ifstream myfile(filename);

	if (myfile.is_open()) {
		cout << "Successfully opened file " << filename << endl;
		string courseName;
		string cwid;
		char grade;
		while (myfile >> courseName >> cwid >> grade) {
			addLine(courseName, cwid, grade);
		}
		myfile.close();
	}
	else
		throw invalid_argument("Could not open file " + filename);
}


// process a line from the text file
void Registrar::addLine(string courseName, string cwid, char grade){

	try{

		getStudent(cwid).addCourseGrade(courseName, grade);
	}

	catch(invalid_argument &e){

    if (numOfStudents == maxSize){

    	Student *stutemp = new Student[maxSize*2];
    	for(int i = 0; i< numOfStudents; i++){

    		stutemp[i] = _studentAR[i];
    	}

    	stutemp[numOfStudents] = Student(cwid);
    	stutemp[numOfStudents].addCourseGrade(courseName, grade);

    	delete[] _studentAR;

    	maxSize = maxSize*2;


    	_studentAR = stutemp;

    }

    else{

	_studentAR[numOfStudents] = Student(cwid);
	_studentAR[numOfStudents].addCourseGrade(courseName, grade);

	}

	numOfStudents++;

	}
}

//pulls student object with corresponding cwid
Student& Registrar::getStudent(string cwid) const{

	for (int i = 0; i < numOfStudents; i++){

	if (cwid == _studentAR[i].getCWID()) return _studentAR[i];

    }

		throw invalid_argument("This CWID is invalid");

}
