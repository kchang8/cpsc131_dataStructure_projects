#include "Student.h"

#include <iostream>

//Default constructor
Student::Student() {

	_gradeAR = new char[10];
	_courseAR = new string[10];
	numOfCourse = 0;
	currMaxSize = 10;

}
//adds CWID from user input
Student::Student(const string &cwid){

	_cwid=cwid;
	numOfCourse =0;
	currMaxSize = 10;
	_gradeAR =new char[10];
	_courseAR =new string[10];

}

//copy constructor to copy from one array to another
Student::Student(const Student &rhs){

	_cwid = rhs._cwid;
	numOfCourse = rhs.numOfCourse;
	currMaxSize = rhs.currMaxSize;

	_gradeAR = new char[rhs.currMaxSize];
	_courseAR = new string[rhs.currMaxSize];

	for(int i = 0; i < currMaxSize; i++){

		_gradeAR[i] = rhs._gradeAR[i];
		_courseAR[i] = rhs._courseAR[i];
  }

}

//Object operator
Student& Student::operator = (const Student &rhs){

	_cwid = rhs._cwid;
	delete[] _gradeAR;
	delete[] _courseAR;

	numOfCourse = rhs.numOfCourse;
	currMaxSize = rhs.currMaxSize;

	_gradeAR = new char[rhs.currMaxSize];
	_courseAR = new string[rhs.currMaxSize];

	for (int i = 0; i < currMaxSize; i++){

		_gradeAR[i] = rhs._gradeAR[i];
		_courseAR[i] = rhs._courseAR[i];
  }

  return *this;

}

// add course grade & grade from user input
void Student::addCourseGrade (const string &courseName, char grade) {

	if(numOfCourse == currMaxSize){

    char *chtemp =new char[currMaxSize*2];
    string *sttemp =new string[currMaxSize*2];

		for(int i=0; i<numOfCourse; i++){

			chtemp[i] = _gradeAR[i];
			sttemp[i]  = _courseAR[i];
		}

	chtemp[numOfCourse] = grade;
    sttemp[numOfCourse] = courseName;

    delete[] _gradeAR;
    delete[] _courseAR;

    currMaxSize *= 2;

    _gradeAR =chtemp;
    _courseAR = sttemp;

	}

	else {
  	//Add a grade to _gradeAR
    _gradeAR[numOfCourse] = grade;
	//Add a course to _courseAR
  	_courseAR[numOfCourse] = courseName;
	  //Every time a course is added, add it to numOfCourse
  	numOfCourse++;

	}

}

//calculated the gpa of the student
double Student::getGPA(){

  double total = 0;

  for (int i = 0; i < numOfCourse; i++){

  	switch(_gradeAR[i]){

  		case 'A' : total += 4;
      					break;
    	case 'B' : total += 3;
                		break;
        case 'C' : total += 2;
      					break;
        case 'D' : total += 1;
      					break;
        default: break;

  	}

  }

  return total/numOfCourse;

}

//prints out list of course name, grade, and gpa
void Student::printTranscript(){

	//prints out course name, grade, and gpa into the console
	for (int i = 0; i << numOfCourse; ++i){

		cout << _courseAR[i]<< " " << _gradeAR[i] <<endl;

	}

    cout << getGPA();

}

//returns cwid associated with student object
string Student::getCWID(){

  return _cwid;

}
