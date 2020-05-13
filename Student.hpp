#ifndef _STUDENT_HPP_
#define _STUDENT_HPP_

#include <iostream>
#include <string>

using namespace std;

class Student{
public:
  Student(){
  }

  Student(int num){
    m_id = num;
  }

// --------------- Setters and Getters -----------------------

  void setid(int id){
    m_id = id;
  }

  int getid() const{
    return m_id;
  }



  void setName(string name){
    m_name = name;
  }

  string getName() const{
    return m_name;
  }



  void setLevel(string level){
    m_level = level;
  }

  string getLevel() const{
    return m_level;
  }



  void setMajor(string major){
    m_major = major;
  }

  string getMajor() const{
    return m_major;
  }



  void setGpa(double gpa){
    m_gpa = gpa;
  }

  double getGpa() const{
    return m_gpa;
  }



  void setAdvisor(int Advisorid){
    m_advisorid = Advisorid;
  }

  int getAdvisor() const{
    return m_advisorid;
  }

//-------------------- OVERRIDDEN OPERATORS -----------------------------------
  //
  // bool operator<(const Student &otherStudent){
  //   return (m_id < otherStudent.getid());
  // }

  // //for use with cout : student -> key
  friend ostream& operator<<(ostream& o, const Student& student){
    o << student.getName();
    return o;
  }
//
friend bool operator<(const Student &student1, const Student &student2){
  return (student1.getid() < student2.getid());
}

friend bool operator!=(const Student &student1, const Student &student2) {
	//cout << "hitting the override" << endl;
	return (student1.getid() != student2.getid());
	//return false;
}

private:
  int m_id;
  string m_name;
  string m_level;
  string m_major;
  double m_gpa;
  int m_advisorid;
};

#endif
