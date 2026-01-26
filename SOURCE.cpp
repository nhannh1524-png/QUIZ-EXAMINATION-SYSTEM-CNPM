#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <sstream>

using namespace std;

set<int> idCheck;
map<string, string> AccountData;
map<string, string> StudentAccountData;
map<string, string> TeacherAccountData;
vector<string> quizList;

bool checkUserName(string name);
bool checkUserYOB(int yearOfBirth);
bool employeeNumberCheck(string number);
void nameNormalization(string& name);


class Quiz {
private:
	string QuizID, Title, Description, QuizPassword;
	int TimeLimit;
public:
	Quiz() {};
	Quiz(string QuizID, string Title, string Description, string QuizPassword, int TimeLimit) {
		this->QuizID = QuizID;
		this->Title = Title;
		this->Description = Description;
		this->QuizPassword = QuizPassword;
		this->TimeLimit = TimeLimit;
	}
	void addQuestion() {
		/////code//////
	}
	void RemoveQuestion() {
		/////code//////
	}
	void setTimeLimit() {
		/////code//////
	}
};
int main()
{
	srand(time(NULL));
	cout << "================================================" << endl;
	cout << "	   QUIZ EXAMINATION SYSTEM " << endl;
	cout << "================================================" << endl;
	cout << "Enter the following information to create an account: " << endl;
	cout << "1.ID : " << endl;
	cout << "2.Name : " << endl;
	cout << "3.Email : " << endl;
	cout << "4.Password : " << endl;
	cout << "5.Year Of Birth : " << endl;
	cout << "6.Select T to register as a Teacher " << endl;
	cout << "  Select S to register as a Student " << endl;
	cout << "  Press ""1"" to confirm information and log in " << endl;
	cout << "  Press ""2"" to log in" << endl;
	cout << "  Press ""3"" to exit " << endl;
	cout << "================================================" << endl;
	cout << endl;
	string ch;
	cout << "Choice : ";
	getline(cin, ch);
	while (ch != "T" && ch != "S" && ch != "t" && ch != "s") {
		cout << "Invalid input, please enter again : ";
		getline(cin, ch);
	}
	if (ch == "T" || ch == "t") {
		Teacher teacher;
		cin >> teacher;
		TeacherAccountData.insert({ teacher.getEmail(), teacher.getPassword() });
		teacher.printInformation();
	}
	else if (ch == "S" || ch == "s") {
		Student student;
		cin >> student;
		StudentAccountData.insert({ student.getEmail(), student.getPassword() });
		student.printInformation();
	}
	else {
		cout << "Exit successfully !" << endl;
	}
	cout << endl;
	cout << endl;
	cout << "================================================" << endl;
	cout << "        Login to your account " << endl;
	cout << "        Email : " << endl;
	cout << "        Password : " << endl;
	cout << "        Press ""E"" to login" << endl;
	cout << "================================================" << endl;
	string email, password;
	cout << "Email : ";
	getline(cin, email);
	cout << "Password : ";
	getline(cin, password);
	if (AccountData.find(email) != AccountData.end() && AccountData[email] == password) {
		if (StudentAccountData.find(email) != StudentAccountData.end() && StudentAccountData[email] == password
			&& TeacherAccountData.find(email) == TeacherAccountData.end()) {
			cout << "Login Successfully ! " << endl;
		}
		else if (TeacherAccountData.find(email) != TeacherAccountData.end() && TeacherAccountData[email] == password
			&& StudentAccountData.find(email) == StudentAccountData.end()) {
			cout << "Login Successfully ! " << endl;
		}
	}
}



void dateOfBirthNormalization(string& birth) {
	if (birth[0] == '/') {
		birth = "0" + birth;
	}
	if (birth[3] == '/') {
		birth.insert(0, "3");
	}
}
bool checkUserName(string name) {
	for (char c : name) {
		if (!isalpha(c) && c != ' ') {
			return false;
		}
	}
	return true;
}
bool checkUserYOB(int yearOfBirth) {
	if (yearOfBirth < 1900 || yearOfBirth > 2026) {
		return false;
	}
	return true;
}
bool employeeNumberCheck(string number) {
	for (int i = 0; i < number.size(); i++) {
		if (!isdigit(number[i])) {
			return false;
		}
	}
	return true;
}
void nameNormalization(string& name) {
	stringstream ss(name);
	string token;
	vector<string> words;
	while (ss >> token) {
		words.push_back(token);
	}
	name = "";
	for (int i = 0; i < words.size(); i++) {
		words[i][0] = toupper(words[i][0]);
		for (int j = 1; j < words[i].size(); j++) {
			words[i][j] = tolower(words[i][j]);
		}
		name += words[i];
		if (i != words.size() - 1) {
			name += " ";
		}
	}
}