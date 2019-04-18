#pragma once
#include <string>

using namespace std;

class Student {

  public:

	Student(); // default constructor
    Student(const string &cwid); // constructor with parameter
  	Student(const Student& rhs); //copy constructor
	Student& operator = (const Student& rhs); //assignement operator
    void addCourseGrade(const string &courseName, char grade); // add course name and grade to student's record
    double getGPA(); // calculate and return GPA
    void printTranscript(); // print transcript - see Student.cpp for the format
    string getCWID(); // return the CWID of this student

  private:

	char * _gradeAR;
	string *_courseAR;
	int numOfCourse; //the number of courses the student has taken
	int currMaxSize;
	string _cwid;

};
