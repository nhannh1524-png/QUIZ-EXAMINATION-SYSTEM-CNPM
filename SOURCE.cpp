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

struct Question {
    string text;
    string A, B, C, D;
    string correctAnswer;
};

class Quiz; 
    map<string, Quiz> globalQuizMap;

class Quiz {
private:
	string QuizID, Title, Description, QuizPassword;
	int TimeLimit;
	public:
    vector<Question> questions;
    bool isPublished = false;

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
    Question q;
    cout << "Question content: "; getline(cin, q.text);
    cout << "Answer A: "; getline(cin, q.A);
    cout << "Answer B: "; getline(cin, q.B);
    cout << "Answer C: "; getline(cin, q.C);
    cout << "Answer D: "; getline(cin, q.D);
    cout << "Correct answer (A/B/C/D): "; getline(cin, q.correctAnswer);
    if (!q.correctAnswer.empty()) q.correctAnswer[0] = toupper(q.correctAnswer[0]);
    questions.push_back(q);
    cout << "Question added successfully!" << endl;
}

void RemoveQuestion() {
    if (questions.empty()) {
        cout << "There are no questions yet." << endl;
        return;
    }
    int idx;
    cout << "Enter the question number to delete (1-" << questions.size() << "): ";
    cin >> idx;
    if (idx >= 1 && idx <= questions.size()) {
        questions.erase(questions.begin() + idx - 1);
        cout << "Deleted successfully!" << endl;
    }
    cin.ignore();
}


    void setTimeLimitVal(int limit) { this->TimeLimit = limit; }
    string getID() { return QuizID; }
    string getPass() { return QuizPassword; }
};

class User {
private:
	long long id;
	int yearOfBirth;
	string name, email, password;
public:
	User() {};
	User(long long id, int yearOfBirth, string name, string email, string password) {
		this->id = id;
		this->yearOfBirth = yearOfBirth;
		this->name = name;
		this->email = email;
		this->password = password;
	}
	friend istream& operator >> (istream& in, User& x) {
		cout << "1.ID : ";
		string idtmp;
		getline(in, idtmp);
		while (!employeeNumberCheck(idtmp)) {
			cout << "Invalid ID, please enter again :";
			getline(in, idtmp);
		}
		x.id = stoll(idtmp);
		cout << "2.Name : ";
		getline(in, x.name);
		while (checkUserName(x.name) == false) {
			cout << "Invalid name. Please enter again: ";
			getline(in, x.name);
		}
		nameNormalization(x.name);
		cout << "3. Email : ";
		getline(in, x.email);
		cout << "4. Password : ";
		getline(in, x.password);
		cout << "5. Year Of Birth : ";
		in >> x.yearOfBirth;
		while (checkUserYOB(x.yearOfBirth) == false) {
			cout << "Invalid year of birth. Please enter again: ";
			in >> x.yearOfBirth;
		}
		in.ignore();
		idCheck.insert(x.id);
		AccountData.insert({ x.email, x.password });
		return in;
	}
	void printInformation() {
		cout << "ID: " << id << endl;
		cout << "Name: " << name << endl;
		cout << "Email: " << email << endl;
		cout << "Password: " << password << endl;
		cout << "Year Of Birth: " << yearOfBirth << endl;
	}
	long long getID() {
		return id;
	}
	int getYearOfBirth() {
		return yearOfBirth;
	}
	string getName() {
		return name;
	}
	string getEmail() {
		return email;
	}
	string getPassword() {
		return password;
	}
	void setID(long long id) {
		this->id = id;
	}
	void setYearOfBirth(int yearOfBirth) {
		this->yearOfBirth = yearOfBirth;
	}
	void setName(string name) {
		this->name = name;
	}
	void setEmail(string email) {
		this->email = email;
	}
	void setPassword(string password) {
		this->password = password;
	}
	void login(string email, string password) {
		if (AccountData.find(email) != AccountData.end() && AccountData[email] == password) {
			cout << "Login successful !" << endl;
		}
		else if (AccountData.find(email) == AccountData.end()) {
			cout << "Email not found !" << endl;
		}
		else {
			cout << "Incorrect password !" << endl;
		}
	}
	void logout() {
		cout << "Logout successful !" << endl;
	}
};

class Teacher : public User {
private:
	int employeeNumber;
	string department, degree;
public:
	Teacher() {};
	Teacher(long long id, int yearOfBirth, string name, string email, string password, int employeeNumber, string department, string degree)
		: User(id, yearOfBirth, name, email, password) {
		this->employeeNumber = employeeNumber;
		this->department = department;
		this->degree = degree;
	}
	friend istream& operator >> (istream& in, Teacher& x) {
		in >> static_cast<User&>(x);
		cout << "1. Employee Number : ";
		string tmp;
		getline(in, tmp);
		while (!employeeNumberCheck(tmp)) {
			cout << "Employee Number Invalid, please enter again : ";
			getline(in, tmp);
		}
		x.employeeNumber = stoi(tmp);
		cout << "2. Degree : ";
		getline(in, x.degree);
		cout << "3. Department : ";
		getline(in, x.department);
		return in;
	}
	void printInformation() {
		cout << "ID: " << getID() << endl;
		cout << "Name: " << getName() << endl;
		cout << "Email: " << getEmail() << endl;
		cout << "Password: " << getPassword() << endl;
		cout << "Year Of Birth: " << getYearOfBirth() << endl;
		cout << "Employee Number : " << employeeNumber << endl;
		cout << "Degree : " << degree << endl;
		cout << "Department : " << department << endl;
	}
	void setDegree(string degree) {
		this->degree = degree;
	}
	void setEmployeeNumber(int employeeNumber) {
		this->employeeNumber = employeeNumber;
	}
	void setDepartment(string department) {
		this->department = department;
	}
	void makeQuiz(string title, string description) {
        string qid, pass; int time;
        cout << "Enter Quiz ID: "; getline(cin, qid);
        cout << "Enter quiz password: "; getline(cin, pass);
        cout << "Enter time limit (minutes): "; cin >> time; cin.ignore();
        
        Quiz newQuiz(qid, title, description, pass, time);
        char choice;
        do {
            newQuiz.addQuestion();
            cout << "Continue adding questions? (Y/N): "; cin >> choice; cin.ignore();
        } while (toupper(choice) == 'Y');

        newQuiz.isPublished = true; 
        globalQuizMap[qid] = newQuiz;
        quizList.push_back(qid);
        cout << "Quiz created and published!" << endl;
    }
};

    void deleteQuiz(string quizID) {
        if (globalQuizMap.erase(quizID)) cout << "Deleted quiz " << quizID << endl;
        else cout << "ID not found!" << endl;
    }

    void setTimeLimit(string quizID, int timeLimit) {
        if (globalQuizMap.count(quizID)) {
            globalQuizMap[quizID].setTimeLimitVal(timeLimit);
            cout << "Time limit updated." << endl;
        }
    }

    void gradeAttempt() {
        cout << "System automatically grades multiple-choice questions." << endl;
    }

class Student : public User {
private:
	int studentNumber, year;
	string major, studentAnswer;
	
	map<int, string> answers; 
    double lastScore = -1;

public:
	Student() {};
	Student(long long id, int yearOfBirth, string name, string email, string password, int studentNumber, string major,
		int year) : User(id, yearOfBirth, name, email, password) {
		this->studentNumber = studentNumber;
		this->major = major;
		this->year = year;
	}
	friend istream& operator >> (istream& in, Student& x) {
		in >> static_cast<User&>(x);
		cout << "Student Number : ";
		string tmp;
		getline(in, tmp);
		while (!employeeNumberCheck(tmp)) {
			cout << "Invalid Student Number, please enter again : ";
			getline(in, tmp);
		}
		x.studentNumber = stoi(tmp);
		cout << "Major (if exist, if don't, type ""nothing"" ";
		getline(in, x.major);
		cout << " Year : ";
		in >> x.year;
		while (checkUserYOB(x.year) == false) {
			cout << "Year invalid, please enter again : ";
			cin >> x.year;
		}
		in.ignore();
		return in;
	}
	void printInformation() {
		cout << "ID: " << getID() << endl;
		cout << "Name: " << getName() << endl;
		cout << "Email: " << getEmail() << endl;
		cout << "Password: " << getPassword() << endl;
		cout << "Year Of Birth: " << getYearOfBirth() << endl;
		cout << "Student Number : " << studentNumber << endl;
		cout << "Major : " << major << endl;
		cout << "Year : " << year;
	}

	void SaveAnswer() {
        int qIdx; string ans;
        cout << "Question number: "; cin >> qIdx;
        cout << "Your answer: "; cin >> ans;
        if(!ans.empty()) ans[0] = toupper(ans[0]);
        answers[qIdx - 1] = ans;
        cout << "Saved temporarily." << endl;
    }

    void SummitAttempt() {
        string qid;
        cout << "Enter Quiz ID to submit: "; cin.ignore(); getline(cin, qid);
        if (globalQuizMap.find(qid) == globalQuizMap.end()) return;

        Quiz &q = globalQuizMap[qid];
        int correct = 0;
        for (int i = 0; i < q.questions.size(); i++) {
            if (answers[i] == q.questions[i].correctAnswer) correct++;
        }
        lastScore = (double)correct / q.questions.size() * 10.0;
        cout << "Submitted! Your score: " << lastScore << endl;
    }

    void ViewResult() {
        if (lastScore == -1) cout << "You have no results yet." << endl;
        else cout << "Latest result: " << lastScore << "/10.0" << endl;
    }
};
class Admin : public User {
private:
	string BackupID;
public:
	Admin() {};
	Admin(long long id, int yearOfBirth, string name, string email, string password, string BackupID)
		: User(id, yearOfBirth, name, email, password) {
		this->BackupID = BackupID;
	}
	void RestoreData(string backupID) {
        cout << "Restoring data from backup: " << backupID << "..." << endl;
        cout << "Restoration completed!" << endl;
    }
    void BackupData() {
        string bID = "BK_" + to_string(time(0));
        this->BackupID = bID;
        cout << "System backup created. Backup ID: " << bID << endl;
    }
	void logout() {
		cout << "Logout successful !" << endl;
	}
};
class Result {
private:
	string resultID;
public:
	Result() {};
	Result(string resultID) {
		this->resultID = resultID;
	}
	double CalculatePercentage(double score, double maxScore) {
        if (maxScore == 0) return 0;
        return (score / maxScore) * 100.0;
    }
    double CalculateGrade(double totalScore) {
        return totalScore; 
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