#include <iostream>
#include "BST.hpp"
#include "TreeNode.hpp"
#include "Student.hpp"
#include "Faculty.hpp"
#include <fstream>
using namespace std;

class Database {
public:
	Database() {

	}

	~Database() {

	}

	void optionOne(BST<Student> *tree) {
		//printing all of the students and their informations
		printStuTreeAll(tree->getRoot(), tree);
	}

	void optionTwo(BST<Faculty> *tree, BST<Student> *stuTree) {
		//printing all of the faculty and their information
		printFacTreeAll(tree->getRoot(), stuTree, tree);
	}

	void optionThree(BST<Student> *tree, int idToFind) {
		//given a student id, print the information of the student
		Student dummy(idToFind);
		if (tree->search(idToFind) != NULL) {
			printAllInfoOneStudent(tree->search(idToFind));
		}
		else {
			cout << "This student does not exist" << endl;
		}
	}

	void optionFour(BST<Faculty> *tree, int idToFind, BST<Student> *sTree) {
		//given a faculty id, print the information of the faculty
		Faculty dummy(idToFind);
		if (tree->search(dummy) != NULL) {
			printAllInfoOneFaculty(tree->search(dummy), sTree);
		}
		else {
			cout << "This faculty does not exist" << endl;
		}
	}

	void optionFive(BST<Student> *sTree, BST<Faculty> *tree, int idToFind) {
		//given a student id, print the information of the students advisor
		Student dummy(idToFind);
		TreeNode<Student> *stu = sTree->search(dummy);
		if (stu == NULL) {
			cout << "Student does not exist" << endl;
			return;
		}
		int facId = stu->key.getAdvisor();
		Faculty newFac(facId);
		printAllInfoOneFaculty(tree->search(newFac), sTree);
	}

	void optionSix(int idToFind, BST<Faculty> *tree, BST<Student> *sTree) {
		//given a faculty id, print the information of the faculty's advisees
		Faculty dummy(idToFind);
		TreeNode<Faculty> *fac = tree->search(dummy);
		if (fac == NULL) {
			cout << "Faculty does not exist" << endl;
			return;
		}
		printAdvisorStudentsRecursiveMoreInfo(fac->key, sTree->getRoot());
	}

	void optionSeven(BST<Student> *sTree, BST<Faculty> *tree){
		//add a new student
		Student newStudent(0);
		int id = 0;
		string name = "";
		string major = "";
		string level = "";
		double gpa = 0.00;
		int advisor = 0;

		cout << "What is the student's id number?" << endl;
		cin >> id;
		newStudent.setid(id);
		if (sTree->search(newStudent) != NULL) {
			cout << "A student with this id already exists" << endl;
			cout << "Cannot add this student" << endl;
			return;
		}

		cout << "What is the student's name?" << endl;
		cin >> name;

		cout << "What is the student's major?" << endl;
		cin >> major;

		cout << "What is the student's level? (freshman, sophomore, junior, senior)" << endl;
		cin >> level;

		cout << "What is the student's gpa?" << endl;
		cin >> gpa;

		cout << "What is the id of the student's advisor?" << endl;
		cin >> advisor;
		Faculty dummy(advisor);
		if (tree->search(dummy) != NULL) {
			//the student is being added
			newStudent.setid(id);
			newStudent.setName(name);
			newStudent.setLevel(level);
			newStudent.setMajor(major);
			newStudent.setGpa(gpa);
			newStudent.setAdvisor(advisor);
			sTree->insert(newStudent);
			cout << newStudent.getName() << " has been added to the database" << endl;
		}
		else {
			cout << "There is no faculty with this id number" << endl;
			cout << "Cannot add this student" << endl;
			return;
		}
	}

	void optionEight(BST<Student> *sTree) {
		//delete a student given the id number
		int id = 0;
		cout << "What is the id of the student that you want to delete?" << endl;
		cin >> id;
		Student newStudent(id);

		Student stuToDelete = sTree->search(newStudent)->key;
		if (stuToDelete != NULL) {
			sTree-> deleteNode(stuToDelete);
			cout << stuToDelete.getName() << " has been removed from the database" << endl;
		}
		else {
			cout << "No student with this ID exists in the database" << endl;
			return;
		}
	}

	void optionNine(BST<Student> *sTree,BST<Faculty>*tree) {
		//add a new faculty
		Faculty newFac(0);
		int id = 0;
		string name = "";
		string department = "";
		string level = "";

		cout << "What is the faculty's id number?" << endl;
		cin >> id;
		newFac.setid(id);
		if (tree->search(newFac) != NULL) {
			cout << "A faculty with this id already exists" << endl;
			cout << "Cannot add this faculty" << endl;
			return;
		}

		cout << "What is the faculty's name?" << endl;
		cin >> name;

		cout << "What is the faculty's department?" << endl;
		cin >> department;

		cout << "What is the faculty's level?" << endl;
		cin >> level;

		newFac.setName(name);
		newFac.setid(id);
		newFac.setDep(department);
		newFac.setLevel(level);
		tree->insert(newFac);
		cout << newFac.getName() << " has been added to the database" << endl;
	}

	void optionTen(BST<Faculty> *tree, BST<Student> *sTree) {
		//delete a faculty given the id number
		int id = 0;
		cout << "What is the id of the faculty that you want to delete?" << endl;
		cin >> id;
		Faculty newFac(id);

		Faculty facToDelete = tree->search(newFac)->key;
		if (facToDelete != NULL) {
			//we need to check the students to see who had this faculty as an advisor
			resetAdvisorStudentsRecursive(facToDelete, sTree->getRoot());
			tree->deleteNode(facToDelete);
			cout << facToDelete.getName() << " has been removed from the database" << endl;
		}
		else {
			cout << "No faculty with this ID exists in the database" << endl;
			return;
		}
	}

	void optionEleven(BST<Faculty> *tree, BST<Student> *sTree){
		//change students advisor with ids
		int stuId = 0;
		int facId = 0;
		cout << "What is the id of the student?" << endl;
		cin >> stuId;
		cout << "What is the id of the faculty member>" << endl;
		cin >> facId;

		Student newStudent(stuId);
		newStudent.setid(stuId);
		Faculty newFac(facId);
		newFac.setid(facId);

		if (sTree->search(newStudent) != NULL){
			if (tree->search(newFac) != NULL) {
				sTree->search(newStudent)->key.setAdvisor(facId);
				cout << sTree->search(newStudent)->key.getName() << " now has advisor " << tree->search(newFac)->key.getName() << endl;
			}
			else {
				cout << "No faculty with this id exists" << endl;
				cout << "Cannot change advisor" << endl;
				return;
			}
		}
		else {
			cout << "No student with this id exists" << endl;
			cout << "Cannot change advisor" << endl;
			return;
		}

	}

	void optionTwelve(BST<Student> *sTree, BST<Faculty> *tree) {
		//remove advisee from a faculty member given the ids
		int stuId = 0;
		int facId = 0;
		cout << "What is the id of the student?" << endl;
		cin >> stuId;
		cout << "What is the id of the faculty?" << endl;
		cin >> facId;

		Student newStudent(stuId);
		Faculty newFac(facId);

		if (sTree->search(newStudent) != NULL) {
			sTree->search(newStudent)->key.setAdvisor(0);
			cout << sTree->search(newStudent)->key.getName() << " now no longer has now no longer has that faculty as an advisor" << endl;
		}
		else {
			cout << "No student with this id exists" << endl;
			cout << "Cannot remove advisee" << endl;
			return;
		}

	}

	//ROLLBACK would go here, but its a big function that may need its own class


	void printTreeToFileStudent(TreeNode<Student> *stuNode, ofstream &outputStream) {
		if (stuNode == NULL) {
			return;
		}

		//write to the file in the format of id,name,level,major,gpa,advisorid
		outputStream << stuNode->key.getid() << "," << stuNode->key.getName() << "," << stuNode->key.getLevel() << "," << stuNode->key.getMajor() << "," << stuNode->key.getGpa() << "," << stuNode->key.getAdvisor() << endl;

		printTreeToFileStudent(stuNode->left, outputStream);
		printTreeToFileStudent(stuNode->right, outputStream);
	}

	void printTreeToFileFaculty(TreeNode<Faculty> *facNode, ofstream &outputStream) {
		if (facNode == NULL) {
			return;
		}
		//write to the file in the format of id,name,level,major,gpa,advisorid
		outputStream << facNode->key.getid() << "," << facNode->key.getName() << "," << facNode->key.getLevel() << "," << facNode->key.getDep() << endl;

		printTreeToFileFaculty(facNode->left, outputStream);
		printTreeToFileFaculty(facNode->right, outputStream);
	}


private:

	void printStuTreeAll(TreeNode<Student> *node, BST<Student> *sTree) {
		if (node == NULL) {
			if (node != sTree->getRoot()) {
				return;

			}
			else {
				cout << "There are no students in the database" << endl;
				return;
			}
		}

		printStuTreeAll(node->left, sTree);
		cout << "Student Name: " << node->key.getName() << endl;
		cout << "Student ID: " << node->key.getid() << endl;
		cout << "Student Level: " << node->key.getLevel() << endl;
		cout << "Student Major: " << node->key.getMajor() << endl;
		cout << "Student Gpa: " << node->key.getGpa() << endl;
		cout << "Student Advisor ID: " << node->key.getAdvisor() << endl;
		cout << endl;
		printStuTreeAll(node->right, sTree);
	}


	void printFacTreeAll(TreeNode<Faculty> *node, BST<Student> *stuTree, BST<Faculty> *tree) {
		if (node == NULL) {
			if (node != tree->getRoot()) {
				return;

			}
			else {
				cout << "There is no faculty in the database" << endl;
				return;
			}
		}

		printFacTreeAll(node->left, stuTree, tree);
		cout << "Faculty Name: " << node->key.getName() << endl;
		cout << "Faculty ID: " << node->key.getid() << endl;
		cout << "Faculty Level: " << node->key.getLevel() << endl;
		cout << "Faculty Department: " << node->key.getDep() << endl;
		cout << "Faculty Advisees: " << endl;
		printAdvisorStudentsRecursive(node->key, stuTree->getRoot());
		cout << endl;
		printFacTreeAll(node->right, stuTree, tree);
	}


	void printAdvisorStudentsRecursive(Faculty fac, TreeNode<Student> *node) {
		if (node == NULL) {
			return;
		}

		if (node->key.getAdvisor() == fac.getid()) {
			cout << "   Student: " << node->key.getid() << endl;
		}

		printAdvisorStudentsRecursive(fac, node->left);
		printAdvisorStudentsRecursive(fac, node->right);
	}

	void resetAdvisorStudentsRecursive(Faculty fac, TreeNode<Student> *node) {
		if (node == NULL) {
			return;
		}

		if (node->key.getAdvisor() == fac.getid()) {
			node->key.setAdvisor(0);
		}

		resetAdvisorStudentsRecursive(fac, node->left);
		resetAdvisorStudentsRecursive(fac, node->right);
	}


	void printAdvisorStudentsRecursiveMoreInfo(Faculty fac, TreeNode<Student> *node) {
		if (node == NULL) {
			return;
		}

		if (node->key.getAdvisor() == fac.getid()) {
			cout << "   Student Name: " << node->key.getName() << endl;
			cout << "   Student ID: " << node->key.getid() << endl;
			cout << "   Student Level: " << node->key.getLevel() << endl;
			cout << "   Student Major: " << node->key.getMajor() << endl;
			cout << "   Student Gpa: " << node->key.getGpa() << endl;
			cout << "   Student Adivsor ID: " << node->key.getAdvisor() << endl;
			cout << endl;

		}
		printAdvisorStudentsRecursiveMoreInfo(fac, node->left);
		printAdvisorStudentsRecursiveMoreInfo(fac, node->right);
	}


	void printAllInfoOneStudent(TreeNode<Student> *node) {
		cout << "Student Name: " << node->key.getName() << endl;
		cout << "Student ID: " << node->key.getid() << endl;
		cout << "Student Level: " << node->key.getLevel() << endl;
		cout << "Student Major: " << node->key.getMajor() << endl;
		cout << "Student Gpa: " << node->key.getGpa() << endl;
		cout << "Student Advisor ID: " << node->key.getAdvisor() << endl;
		cout << endl;
	}

	void printAllInfoOneFaculty(TreeNode<Faculty> *node, BST<Student> *sTree) {
		cout << "Faculty Name: " << node->key.getName() << endl;
		cout << "Faculty ID: " << node->key.getid() << endl;
		cout << "Faculty Level: " << node->key.getLevel() << endl;
		cout << "Faculty Department: " << node->key.getDep() << endl;
		cout << "Faculty Advisees: " << endl;
		printAdvisorStudentsRecursive(node->key, sTree->getRoot());
		cout << endl;
	}

};
