#ifndef _FACULTY_HPP_
#define _FACULTY_HPP_

#include <iostream>
#include <string>

using namespace std;

class Faculty {
public:
	Faculty() {
	}

	Faculty(int num) {
		m_id = num;
	}

	// --------------- Setters and Getters -----------------------

	void setid(int id) {
		m_id = id;
	}

	int getid() const {
		return m_id;
	}



	void setName(string name) {
		m_name = name;
	}

	string getName() const {
		return m_name;
	}



	void setLevel(string level) {
		m_level = level;
	}

	string getLevel() const {
		return m_level;
	}



	void setDep(string dep) {
		m_department = dep;
	}

	string getDep() const {
		return m_department;
	}



	//-------------------- OVERRIDDEN OPERATORS -----------------------------------
	  //
	  // bool operator<(const Faculty &otherFaculty){
	  //   return (m_id < otherFaculty.getid());
	  // }

	  // //for use with cout : student -> key
	friend ostream& operator<<(ostream& o, const Faculty& student) {
		o << student.getName();
		return o;
	}
	//
	friend bool operator<(const Faculty &student1, const Faculty &student2) {
		return (student1.getid() < student2.getid());
	}

	friend bool operator!=(const Faculty &student1, const Faculty &student2) {
		//cout << "hitting the override" << endl;
		return (student1.getid() != student2.getid());
		//return false;
	}

private:
	int m_id;
	string m_name;
	string m_level;
	string m_department;
};

#endif

