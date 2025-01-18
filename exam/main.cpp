#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;
class Student {
private:
	string name;
	string group;
	double averageMark;
	string dateOfBirth;
public:
	Student(string fromFile) {
		auto a = find(fromFile.begin(), fromFile.end(), ';');
		if (a != fromFile.end()) {
			string name(fromFile.begin(), a);
			this->name = name;
			auto b = find(a + 1, fromFile.end(), ';');
			if (b != fromFile.end()) {
				string group(a + 1, b);
				this->group = group;
				a = find(b + 1, fromFile.end(), ';');
				if (a != fromFile.end()) {
					string averageMark(b + 1, a);
					this->averageMark = stod(averageMark);
					b = find(a + 1, fromFile.end(), ';');
					if (b != fromFile.end()) {
						string dateOfBirth(a + 1, b);
						this->dateOfBirth = dateOfBirth;
					}
				}
			}
		}
	}

	string getName() const { return name; }
	string getGroup() const { return group; }
	double getAverageMark() const { return averageMark; }
	string getDateOfBirth() const { return dateOfBirth; }
	void setAverageMark(double averageMark) { this->averageMark = averageMark; }

	void printStudent() const {
		cout << "Name: " << name << endl
			<< "Group: " << group << endl
			<< "Average mark: " << averageMark << endl
			<< "Date of birth: " << dateOfBirth << endl << endl;
	}
};



void addStudent(vector<Student>& students, Student student) {
	students.push_back(student);
}

Student* findStudent(vector<Student>& students, string& name) {
	auto it = find_if(students.begin(), students.end(), [&name](const Student& student) {return student.getName() == name;});
	if (it != students.end()) {
		return &*it;
	}
	else {
		cout << "Student is not found" << endl;
		return nullptr;
	}
}

void editAverageMark(vector<Student>& students, string& name, double newAverageMark) {
	Student* student = findStudent(students, name);

	if (student != nullptr) {
		student->setAverageMark(newAverageMark);
		cout << "Average mark edited to " << newAverageMark << endl;
	}
}

void removeStudent(vector<Student>& students, string& name) {
	auto it = find_if(students.begin(), students.end(), [&name](const Student& student) {return student.getName() == name;}); 
	if (it != students.end()) {
		students.erase(it); 
	} 
	else { 
		cout << "Student is not found" << endl;
	}
}

void printAllStudents(vector<Student>& students) {
	for_each(students.begin(), students.end(), [](const Student& student) {student.printStudent();});
}

void filterByGroup(vector<Student>& students, string& group) {
	for_each(students.begin(), students.end(), [group](const Student& student) {if (student.getGroup() == group) student.printStudent();});
}

void saveToFile(vector<Student> students, string& filepath) {
	ofstream file(filepath);
	if (!file.is_open()) {
		cout << "file is not open" << endl;
		return;
	}
	for_each(students.begin(), students.end(), [&file](const Student& student) {
		file << student.getName() << ';'
			<< student.getGroup() << ';'
			<< student.getAverageMark() << ';'
			<< student.getDateOfBirth() << ';' << endl;
		});
}
int main() {
	vector<Student> students;
	string filepath = "students.txt";
	
	ifstream file(filepath);

	if (!file.is_open()) {
		cout << "file is not open" << endl;
		return 0;
	}
	string line;
	while (getline(file, line)) {
		if (!line.empty()) {
			students.push_back(Student(line));
		}
	}
	file.close();
	string studentData1 = "Gubka Bob;Group1;3.8;01-01-2000;";
	string studentData2 = "Patrik;Group2;4.1;02-02-2001;";

	addStudent(students, Student(studentData1));
	addStudent(students, Student(studentData2));

	cout << "All students:" << endl;
	printAllStudents(students);

	string nameToEdit = "Gubka Bob";
	editAverageMark(students, nameToEdit, 4.0);
	cout << "All students after editing average mark:" << endl;
	printAllStudents(students);

	string groupToFilter = "Group1";
	cout << "Students in " << groupToFilter << ":" << endl;
	filterByGroup(students, groupToFilter);

	string nameToRemove = "Maks";
	removeStudent(students, nameToRemove);
	cout << "All students after removal:" << endl;

	printAllStudents(students);

	saveToFile(students, filepath);
	return 0;
}