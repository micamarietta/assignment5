#include <iostream>
#include <fstream>

#include <sstream>
#include <string>
//#include "BST.hpp"
#include "Student.hpp"
#include "TreeNode.hpp"
#include "Faculty.hpp"
#include "Database.hpp"
#include "stack.hpp"
using namespace std;

void InitStuFromFile(BST<Student> *stuTree) {
	ifstream inputStreamStu;
	inputStreamStu.open("studentTable.txt");
	if (inputStreamStu.fail()) {
		//file don't exist, new Student ST
		cout << " read student failed";
	}
	else {
		//student table does exist, populate the tree based on text file
		string curLine;
		if (inputStreamStu.is_open()) {
			while (getline(inputStreamStu, curLine)) {
				stringstream   linestream(curLine);
				string id;
				string name;
				string level;
				string major;
				string gpa;
				string adv;
				getline(linestream, id, ',');
				getline(linestream, name, ',');
				getline(linestream, level, ',');
				getline(linestream, major, ',');
				getline(linestream, gpa, ',');
				getline(linestream, adv, '\n');

				Student newStudent(stoi(id));
				newStudent.setName(name);
				newStudent.setLevel(level);
				newStudent.setMajor(major);
				newStudent.setGpa(stod(gpa));
				newStudent.setAdvisor(stoi(adv));
				stuTree->insert(newStudent);
			}
		}
	}
}
void InitFacFromFile(BST<Faculty> *facTree) {
	ifstream inputStreamFac;
	inputStreamFac.open("facultyTable.txt");
	if (inputStreamFac.fail()) {
		//file doesn't exist, new Faculty BST
		cout << "test";

	}
	else {
		//faculty table does exist, populate the tree based on text file
		string curLine;
		if (inputStreamFac.is_open()) {
			while (getline(inputStreamFac, curLine)) {
				stringstream   linestream(curLine);
				string id;
				string name;
				string level;
				string department;

				getline(linestream, id, ',');
				getline(linestream, name, ',');
				getline(linestream, level, ',');
				getline(linestream, department, '\n');

				Faculty newFac(stoi(id));
				newFac.setName(name);
				newFac.setLevel(level);
				newFac.setDep(department);
				facTree->insert(newFac);

			}
		}
	}
}
string GetFileContents(string fileName) {
	// read the file, return the contents
	ifstream file(fileName);
	stringstream buffer;
	buffer << file.rdbuf();
	string fileContents = buffer.str();
	file.close();
	return fileContents;
}
void PushFileToStack(GenStack<string> *stack, string fileName) {
	// read the file
	string fileContents = GetFileContents(fileName);

	// push the file contents into the stack
	stack->push(fileContents);
}
void OverwriteFile(string fileName, string fileContents) {
	ofstream output;
	output.open(fileName);
	output << fileContents;
	output.close();
}

int main(int argc, char **argv) {

	GenStack<string> *stuStack = new GenStack<string>();
	GenStack<string> *facStack = new GenStack<string>();
	Database database;
	BST<Student> *masterStudent = new BST<Student>;
	BST<Faculty> *masterFaculty = new BST<Faculty>;
	bool stopPrompting = false;

	// initialize the trees from file
	//insert the files generated from the trees into the stack
	InitStuFromFile(masterStudent);
	PushFileToStack(stuStack, "studentTable.txt");
	InitFacFromFile(masterFaculty);
	PushFileToStack(facStack, "facultyTable.txt");

	//opening of the program
	while (!stopPrompting) {
		cout << "Welcome to the Student and Faculty Database." << endl;
		cout << "MENU:" << endl;
		cout << "1. Print all students and their information" << endl;
		cout << "2. Print all faculty and their information" << endl;
		cout << "3. Find and display student information given the student's id" << endl;
		cout << "4. Find and display faculty information given the faculty's id" << endl;
		cout << "5. Given a student's id, print the name and information of their advisor" << endl;
		cout << "6. Given a faculty's id, print the names and information of their advisees" << endl;
		cout << "7. Add a new student" << endl;
		cout << "8. Delete a student given an id" << endl;
		cout << "9. Add a new faculty" << endl;
		cout << "10. Delete a faculty member given the id" << endl;
		cout << "11. Change a student's advisor given the student and faculty ids" << endl;
		cout << "12. Remove an advisee from a faculty member given the ids" << endl;
		cout << "13. Rollback" << endl;
		cout << "14. Exit" << endl;
		cout << "----------------------------------------------------------------------------" << endl;
		cout << "Please type the number of the task you want to accomplish" << endl;

		int userInput = 0;
		cin >> userInput;

		if (userInput == 1) {
			cout << "All students in database: " << endl;
			database.optionOne(masterStudent);
		}
		else if (userInput == 2) {
			cout << "All faculty in the database: " << endl;
			database.optionTwo(masterFaculty, masterStudent);
		}
		else if (userInput == 3) {
			int stuIDtoFind = 0;
			cout << "What is the id of the student you want to find?" << endl;
			cin >> stuIDtoFind;
			database.optionThree(masterStudent, stuIDtoFind);
		}
		else if (userInput == 4) {
			int facIDtoFind = 0;
			cout << "What is the id of the faculty you want to find?" << endl;
			cin >> facIDtoFind;
			database.optionFour(masterFaculty, facIDtoFind, masterStudent);
		}
		else if (userInput == 5) {
			int stuIDtoFind = 0;
			cout << "What is the id of the student?" << endl;
			cin >> stuIDtoFind;
			database.optionFive(masterStudent, masterFaculty, stuIDtoFind);
		}
		else if (userInput == 6) {
			int facIDtoFind = 0;
			cout << "What is the id of the faculty?" << endl;
			cin >> facIDtoFind;
			database.optionSix(facIDtoFind, masterFaculty, masterStudent);
		}
		else if (userInput == 7) {
			database.optionSeven(masterStudent, masterFaculty);

			ofstream outputStream;
			outputStream.open("studentTable.txt");
			database.printTreeToFileStudent(masterStudent->getRoot(), outputStream);
			outputStream.close();

			PushFileToStack(stuStack, "studentTable.txt");
			PushFileToStack(facStack, "facultyTable.txt");
			//database.printTreeToFileFaculty(masterFaculty->getRoot(), outputStream, "facultyTable.txt");
		}
		else if (userInput == 8) {
			database.optionEight(masterStudent);

			ofstream outputStream;
			outputStream.open("studentTable.txt");
			database.printTreeToFileStudent(masterStudent->getRoot(), outputStream);
			outputStream.close();

			PushFileToStack(stuStack, "studentTable.txt");
			PushFileToStack(facStack, "facultyTable.txt");
			//database.printTreeToFileFaculty(masterFaculty->getRoot(), outputStream, "facultyTable.txt");

		}
		else if (userInput == 9) {
			database.optionNine(masterStudent, masterFaculty);

			ofstream outputStream;
			outputStream.open("facultyTable.txt");
			database.printTreeToFileFaculty(masterFaculty->getRoot(), outputStream);
			outputStream.close();

			PushFileToStack(stuStack, "studentTable.txt");
			PushFileToStack(facStack, "facultyTable.txt");
		}
		else if (userInput == 10) {
			database.optionTen(masterFaculty, masterStudent);

			ofstream outputStreamStu;
			outputStreamStu.open("studentTable.txt");
			database.printTreeToFileStudent(masterStudent->getRoot(), outputStreamStu);
			outputStreamStu.close();

			ofstream outputStreamFac;
			outputStreamFac.open("facultyTable.txt");
			database.printTreeToFileFaculty(masterFaculty->getRoot(), outputStreamFac);
			outputStreamFac.close();

			PushFileToStack(stuStack, "studentTable.txt");
			PushFileToStack(facStack, "facultyTable.txt");
			//database.printTreeToFileFaculty(masterFaculty->getRoot(), outputStream, "facultyTable.txt");
		}
		else if (userInput == 11) {
			database.optionEleven(masterFaculty, masterStudent);

			ofstream outputStream;
			outputStream.open("studentTable.txt");
			database.printTreeToFileStudent(masterStudent->getRoot(), outputStream);
			outputStream.close();

			PushFileToStack(stuStack, "studentTable.txt");
			PushFileToStack(facStack, "facultyTable.txt");
			//database.printTreeToFileFaculty(masterFaculty->getRoot(), outputStream, "facultyTable.txt");
		}
		else if (userInput == 12) {
			database.optionTwelve(masterStudent, masterFaculty);

			ofstream outputStream;
			outputStream.open("studentTable.txt");
			database.printTreeToFileStudent(masterStudent->getRoot(), outputStream);
			outputStream.close();

			PushFileToStack(stuStack, "studentTable.txt");
			PushFileToStack(facStack, "facultyTable.txt");
			//database.printTreeToFileFaculty(masterFaculty->getRoot(), outputStream, "facultyTable.txt");
		}
		else if (userInput == 13) {
			//rollback
			// pop the file stack twice to get the previous version
			stuStack->pop();
			string prevVersionStu = stuStack->pop();
			OverwriteFile("studentTable.txt", prevVersionStu);
			masterStudent = new BST<Student>();
			InitStuFromFile(masterStudent);

			// pop the file stack twice to get the previous version
			facStack->pop();
			string prevVersionFac = facStack->pop();
			OverwriteFile("facultyTable.txt", prevVersionFac);
			masterFaculty = new BST<Faculty>();
			InitFacFromFile(masterFaculty);

		}
		else if (userInput == 14) {
			cout << "Thank you for entering the database" << endl;
			stopPrompting = true;
		}
	}

	return 0;

}
