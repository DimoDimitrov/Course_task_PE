#include <iostream>
#include <fstream>
#include <string>
#include <new>
using namespace std;

// ============= Utility functions ===================

bool containsDigit(string str) {
    for (char c : str) {
        if (isdigit(static_cast<unsigned char>(c))) {
            return true;
        }
    }
    return false;
}


bool completelyNumeric(string str){
    for (int i = 0; i < str.length(); i++){
        if (!isdigit(static_cast<unsigned char>(str[i]))){
            return false;
        }
    }
    return !str.empty();
}

// ============= Classes ===================

class Student {
    private:
        string name;
        string facNum;
        int group;
        int course;

    public:
        Student(string name, string facNum, int group, int course){
            if (validateData(name, facNum, group, course)){
                this->name = name;
                this->facNum = facNum;
                this->group = group;
                this->course = course;
            } else {
                cout << "The student was not registered because the data was not valid." << endl;
                return;
            }
        }

        Student(){
            cout << "Registering new student initiated." << endl;
            
            string tempName, tempFacNum;
            int tempGroup, tempCourse;
            cout << "Enter the student's name: ";
            cin >> tempName;
            cout << "Enter the student's faculty number: ";
            cin >> tempFacNum;
            cout << "Enter the student's gorup: ";
            cin >> tempGroup;
            cout << "Enter the student's course: ";
            cin >> tempCourse;
            
            if (validateData(tempName, tempFacNum, tempGroup, tempCourse)){
                this->name = tempName;
                this->facNum = tempFacNum;
                this->group = tempGroup;
                this->course = tempCourse;
            } else {
                cout << "The student was not registered because the data was not valid." << endl;
                this->name = "";
                this->facNum = "";
                this->group = 0;
                this->course = 0;
                return;
            }
        }

        string getName() const { return name; }
        string getFacNum() const { return facNum; }
        int getGroup() const { return group; }
        int getCourse() const { return course; }

        
        bool validateData(string name, string facNum, int group, int course) {
            if (!(name.length() > 3 && name.length() < 60) || containsDigit(name)) {
                cout << "Invalid name — must be 4–59 characters and contain no digits.\n";
                return false;
            }
            if (!(facNum.length() == 9 && completelyNumeric(facNum))) {
                cout << "Invalid faculty number — must be exactly 9 digits.\n";
                return false;
            }
            if (!(group >= 30 && group <= 50)) {
                cout << "Invalid group — must be between 30 and 50.\n";
                return false;
            }
            if (!(course >= 1 && course <= 4)) {
                cout << "Invalid course — must be between 1 and 4.\n";
                return false;
            }
            return true;
        }


        // void print() {
        //     if (getName() != ""){
        //         cout << "Name: " << getName() << "\nFaculty No: " << getFacNum() << "\nGroup: " << getGroup() << "\nCourse: " << getCourse() << endl;
        //     } else {
        //         cout << "The student record is empty." << endl;
        //     }
        // }

    virtual void print() = 0;

    virtual ~Student(){cout << "Deleting Student " << getName() << ". With fac id - " << getFacNum() << endl;}
};

class StudentGrades : public Student{
    private:
        double* grades; 
        int gradeCount; 

    public:
        StudentGrades(string name, string facNum, int group, int course) : Student(name, facNum, group, course){
            this->gradeCount = course * 5;         
            this->grades = new double[gradeCount];
            double tempGrade;
            bool correctGradeFlag = true;

            cout << "Enter " << gradeCount << " grades for " << getName() << ":\n";
            for (int i = 0; i < gradeCount; ++i) {
                cout << "Grade " << i + 1 << ": ";
                cin >> tempGrade;
                while (correctGradeFlag){
                    if (tempGrade >= 2.0 && tempGrade <= 6.0){
                        grades[i] = tempGrade;
                        correctGradeFlag = false;
                    } else {
                        cout << "Invalid grade! Please enter a number between 2 and 6.\n";
                        cin.clear();
                        cin.ignore(10000, '\n');
                        //Breaks when the grade is valid.
                    }
                }
                correctGradeFlag = true;
            }
            cout << "All grades for " << getName() << " recorded successfully!" << endl;
        }

        StudentGrades(string name, string facNum, int group, int course, double* gradesArray, int gradeCount) : Student(name, facNum, group, course) {
            this->gradeCount = gradeCount;
            this->grades = new double[gradeCount];
            for (int i = 0; i < gradeCount; ++i)
                this->grades[i] = gradesArray[i];
        }

        StudentGrades() : Student() {
            if (getFacNum().empty()) {
                this->gradeCount = 0;
                this->grades = nullptr;
                return;
            }
            
            this->gradeCount = getCourse() * 5;

            this->grades = new double[gradeCount];

            cout << "Now enter " << gradeCount << " grades for " << getName() << ":\n";

            for (int i = 0; i < gradeCount; ++i) {
                double tempGrade;
                while (true) {
                    cout << "Grade " << i + 1 << ": ";
                    cin >> tempGrade;

                    if (tempGrade >= 2.0 && tempGrade <= 6.0) {
                        grades[i] = tempGrade;
                        break;
                    } else {
                        cout << " Invalid grade! Please enter a number between 2 and 6.\n";
                        cin.clear();
                        cin.ignore(10000, '\n');
                    }
                }
            }
            cout << "All grades for " << getName() << " recorded successfully!" << endl;
        }

        StudentGrades(const StudentGrades& other) : Student(other.getName(), other.getFacNum(), other.getGroup(), other.getCourse()) {
            this->gradeCount = other.gradeCount;
            this->grades = new double[gradeCount];
            for (int i = 0; i < gradeCount; ++i)
                this->grades[i] = other.grades[i];
        }

        StudentGrades& operator=(const StudentGrades& other) {
            if (this != &other) {
                StudentGrades temp(other);
                swap(this->grades, temp.grades);
                swap(this->gradeCount, temp.gradeCount);
            }
            return *this;
        }

        ~StudentGrades() {
            if (grades != nullptr) {
                delete[] grades;
                cout << "Grades deleted for " << getName() << endl;
            }
        }

        int getGradeCount() const { return gradeCount; }
        double getGrade(int index) const { return grades[index]; }

        double average() {
            double sum = 0;
            for (int i = 0; i < gradeCount; ++i)
                sum += grades[i];
            return sum / gradeCount;
        }

        void print() override{
            cout << "Name: " << getName() << "\nFaculty No: " << getFacNum() << "\nGroup: " << getGroup() << "\nCourse: " << getCourse() << "\nGrades: ";
            for (int i = 0; i < gradeCount; ++i)
                cout << grades[i] << " ";
            cout << "\nAverage: " << average() << "\n" << endl;
        }

        friend ostream& operator<<(ostream& os, StudentGrades& s);
        friend void loadStudentsFromFile(StudentGrades* &students, int &count, const string& filename);
};

ostream& operator<<(ostream& os, StudentGrades& s) {
    os << "Name: " << s.getName()
       << " | Faculty No: " << s.getFacNum()
       << " | Group: " << s.getGroup()
       << " | Course: " << s.getCourse()
       << "\nGrades: ";

    for (int i = 0; i < s.gradeCount; ++i)
        os << s.grades[i] << " ";

    os << "\nAverage: " << s.average() << "\n";
    return os;
}

// int studentsSize = 1;
// Student *students = new Student[studentsSize];

int studentGradesSize = 0;
StudentGrades* studentsG = nullptr;

double calcGroupMaxAvg(int group, StudentGrades *students){
    int grMembers=0;
    double maxAverage = 0;

    for(int i = 0; i < studentGradesSize; i++){
        if (students[i].getGroup() == group) {
            maxAverage += students[i].average();
            grMembers++;
        }
    }

    cout << "The members of the gorups are : " << grMembers << " and the max average grade is: " << maxAverage << endl;
    return maxAverage;
}

void printStudent(string facNum, StudentGrades *students){
    for(int i = 0; i < studentGradesSize; i++){
        if(students[i].getFacNum() == facNum){
            students[i].print();
        }
    }
}

void saveStudentsToFile(StudentGrades* students, int count, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: could not open file for writing.\n";
        return;
    }

    for (int i = 0; i < count; ++i) {
        file << students[i].getName() << " "
             << students[i].getFacNum() << " "
             << students[i].getGroup() << " "
             << students[i].getCourse() << " ";

        int gradeCount = students[i].getGradeCount();
        for (int g = 0; g < gradeCount; ++g)
            file << students[i].getGrade(g) << " ";
        file << "\n";
    }

    file.close();
    cout << "Students successfully saved to " << filename << "\n";
}

void loadStudentsFromFile(StudentGrades* &students, int &count, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: could not open file for reading.\n";
        return;
    }

    count = 0;
    string line;
    while (getline(file, line)) count++;
    file.clear();
    file.seekg(0, ios::beg);

    if (students != nullptr) {
        for (int i = 0; i < count; ++i)
            students[i].~StudentGrades();
        delete[] reinterpret_cast<char*>(students);
    }

    char* rawMemory = new char[sizeof(StudentGrades) * count];
    students = reinterpret_cast<StudentGrades*>(rawMemory);

    for (int i = 0; i < count; ++i) {
        string name, facNum;
        int group, course;
        file >> name >> facNum >> group >> course;

        int gradeCount = course * 5;
        double* tempGrades = new double[gradeCount];
        for (int g = 0; g < gradeCount; ++g)
            file >> tempGrades[g];

        new (students + i) StudentGrades(name, facNum, group, course, tempGrades, gradeCount);
        delete[] tempGrades;
    }

    file.close();
    cout << "Students loaded from " << filename << "\n";
}

// ============================ ADDITIONAL FUNCTIONALITIES ============================

void addStudent(StudentGrades* &students, int &count) {
    cout << "\n--- Add New Student ---\n";
    
    StudentGrades newStudent;
    
    if (newStudent.getFacNum().empty()) {
        cout << "Student was not added due to invalid data.\n";
        return;
    }
    
    char* rawMemory = new char[sizeof(StudentGrades) * (count + 1)];
    StudentGrades* newArr = reinterpret_cast<StudentGrades*>(rawMemory);
    
    for (int i = 0; i < count; ++i)
        new (newArr + i) StudentGrades(students[i]);
    
    new (newArr + count) StudentGrades(newStudent);
    
    if (students != nullptr) {
        for (int i = 0; i < count; ++i)
            students[i].~StudentGrades();
        delete[] reinterpret_cast<char*>(students);
    }
    
    students = newArr;
    count++;

    cout << "Added student: " << students[count - 1].getFacNum() << endl;
    cout << "Student added successfully!\n";
}

void deleteStudent(StudentGrades* &students, int &count, const string& facNum) {
    int index = -1;
    for (int i = 0; i < count; ++i) {
        if (students[i].getFacNum() == facNum) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "No student found with faculty number " << facNum << ".\n";
        return;
    }

    char confirm;
    cout << "Confirm deletion of " << students[index].getName() << " (y/n): ";
    cin >> confirm;
    if (confirm != 'y' && confirm != 'Y') return;

    char* rawMemory = new char[sizeof(StudentGrades) * (count - 1)];
    StudentGrades* newArr = reinterpret_cast<StudentGrades*>(rawMemory);
    
    for (int i = 0, j = 0; i < count; ++i)
        if (i != index) new (newArr + j++) StudentGrades(students[i]);

    for (int i = 0; i < count; ++i)
        students[i].~StudentGrades();
    delete[] reinterpret_cast<char*>(students);
    
    students = newArr;
    count--;

    ofstream log("actions.log", ios::app);
    log << "Deleted student: " << facNum << endl;
    log.close();

    cout << "Student deleted successfully!\n";
}

void sortStudentsByAverage(StudentGrades* students, int count) {
    for (int i = 0; i < count - 1; ++i) {
        for (int j = i + 1; j < count; ++j) {
            if (students[i].average() < students[j].average()) {
                swap(students[i], students[j]);
            }
        }
    }

    cout << "\n=== Sorted by Average (Descending) ===\n";
    for (int i = 0; i < count; ++i)
        cout << students[i] << endl;
}

void searchByKeyword(StudentGrades* students, int count) {
    cout << "Enter keyword to search by name: ";
    string keyword;
    cin >> keyword;
    bool found = false;

    ofstream out("search_results.txt");
    for (int i = 0; i < count; ++i) {
        if (students[i].getName().find(keyword) != string::npos) {
            cout << students[i] << endl;
            out << students[i] << endl;
            found = true;
        }
    }
    out.close();

    if (!found) cout << "No students found with that keyword.\n";
    else cout << "Results saved to search_results.txt\n";
}

void groupStatistics(StudentGrades* students, int count) {
    int targetGroup;
    cout << "Enter group number: ";
    cin >> targetGroup;

    int memberCount = 0;
    double sum = 0;

    for (int i = 0; i < count; ++i) {
        if (students[i].getGroup() == targetGroup) {
            sum += students[i].average();
            memberCount++;
        }
    }

    if (memberCount == 0) {
        cout << "No students in group " << targetGroup << ".\n";
        return;
    }

    double avg = sum / memberCount;
    cout << "Group " << targetGroup << " has " << memberCount 
         << " students with an average of " << avg << ".\n";

    ofstream out("group_stats.txt");
    out << "Group " << targetGroup << ": count=" << memberCount 
        << ", average=" << avg << endl;
    out.close();
    cout << "Statistics written to group_stats.txt\n";
}


void fullReport(StudentGrades* students, int count) {
    int courseCount[5] = {0};
    int excellent = 0;

    for (int i = 0; i < count; ++i) {
        int c = students[i].getCourse();
        if (c >= 1 && c <= 4)
            courseCount[c]++;
        if (students[i].average() > 5.5)
            excellent++;
    }

    ofstream report("full_report.txt");
    report << "=== Full Report ===\n";
    for (int i = 1; i <= 4; ++i)
        report << "Course " << i << ": " << courseCount[i] << " students\n";
    report << "Excellent students (>5.50): " << excellent << endl;
    report.close();

    cout << "Full report saved to full_report.txt\n";
}


int main() {
    // cout << "\n=== STEP 1: Register Students ===\n";
    // for (int i = 0; i < studentGradesSize; ++i) {
    //     cout << "\n--- Registering student " << i + 1 << " ---\n";
    //     studentsG[i] = StudentGrades();
    // }

    bool running = true;
    while (running) {
        cout << "\n=== MENU ===\n";
        cout << "1. Print all students\n";
        cout << "2. Save to file\n";
        cout << "3. Load from file\n";
        cout << "4. Search by faculty number\n";
        cout << "5. Calculate max group average\n";
        cout << "6. Add new student\n";
        cout << "7. Delete student\n";
        cout << "8. Sort by average\n";
        cout << "9. Search by name keyword\n";
        cout << "10. Group statistics\n";
        cout << "11. Generate full report\n";
        cout << "12. Exit\n";
        cout << "Choose option: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                for (int i = 0; i < studentGradesSize; ++i)
                    cout << studentsG[i] << endl;
                break;
            case 2: {
                string filename;
                cout << "Enter filename to save: ";
                cin >> filename;
                saveStudentsToFile(studentsG, studentGradesSize, filename);
                break;
            }
            case 3: {
                string filename;
                cout << "Enter filename to load: ";
                cin >> filename;
                loadStudentsFromFile(studentsG, studentGradesSize, filename);
                break;
            }
            case 4: {
                string searchFac;
                cout << "Enter faculty number: ";
                cin >> searchFac;
                printStudent(searchFac, studentsG);
                break;
            }
            case 5: {
                int groupNumber;
                cout << "Enter group number: ";
                cin >> groupNumber;
                calcGroupMaxAvg(groupNumber, studentsG);
                break;
            }
            case 6:
                addStudent(studentsG, studentGradesSize);
                break;
            case 7: {
                string fac;
                cout << "Enter faculty number to delete: ";
                cin >> fac;
                deleteStudent(studentsG, studentGradesSize, fac);
                break;
            }
            case 8:
                sortStudentsByAverage(studentsG, studentGradesSize);
                break;
            case 9:
                searchByKeyword(studentsG, studentGradesSize);
                break;
            case 10:
                groupStatistics(studentsG, studentGradesSize);
                break;
            case 11:
                fullReport(studentsG, studentGradesSize);
                break;
            case 12:
                running = false;
                break;
            default:
                cout << "Invalid option.\n";
        }
    }

    if (studentsG != nullptr) {
        for (int i = 0; i < studentGradesSize; ++i)
            studentsG[i].~StudentGrades();
        delete[] reinterpret_cast<char*>(studentsG);
    }
    cout << "Program terminated.\n";
    return 0;
}

/*
================================================================================
                    ДОКУМЕНТАЦИЯ НА ПРОГРАМАТА
================================================================================

ОПИСАНИЕ НА ПРОГРАМАТА:
----------------------
Тази програма представлява система за управление на студенти и техните оценки.
Програмата позволява добавяне, изтриване, търсене, сортиране и статистика
на студенти с техните оценки. Използва обектно-ориентирано програмиране с
наследяване, виртуални функции, динамична памет и файлово управление.

================================================================================
                            СТРУКТУРА НА КОДА
================================================================================

1. БИБЛИОТЕКИ И ПРОСТРАНСТВА ОТ ИМЕНА:
--------------------------------------
#include <iostream>   - За входно/изходни операции (cin, cout, cerr)
#include <fstream>    - За работа с файлове (ifstream, ofstream)
#include <string>      - За работа със символни низове
#include <new>         - За placement new оператор (конструиране на обекти в предварително заделена памет)

using namespace std;  - Използва стандартното пространство от имена за по-кратък код

================================================================================

2. ПОМОЩНИ ФУНКЦИИ (UTILITY FUNCTIONS):
---------------------------------------

bool containsDigit(string str)
    Цел: Проверява дали низът съдържа цифри
    Параметри: str - низът за проверка
    Връща: true ако има цифри, false иначе
    Използване: Валидация на имена - имената не трябва да съдържат цифри

bool completelyNumeric(string str)
    Цел: Проверява дали низът съдържа САМО цифри
    Параметри: str - низът за проверка
    Връща: true ако всички символи са цифри, false иначе
    Използване: Валидация на факултетен номер - трябва да е само цифри

================================================================================

3. КЛАС Student (БАЗОВ КЛАС):
----------------------------

ОПИСАНИЕ:
---------
Базов абстрактен клас, който съдържа основната информация за студент:
- Име (name)
- Факултетен номер (facNum)
- Група (group)
- Курс (course)

ЧЛЕНОВЕ ДАННИ (private):
-----------------------
string name      - Име на студента (4-59 символа, без цифри)
string facNum    - Факултетен номер (точно 9 цифри)
int group        - Номер на групата (30-50)
int course       - Курс (1-4)

КОНСТРУКТОРИ:
-------------

1. Student(string name, string facNum, int group, int course)
   - Параметризиран конструктор
   - Валидира данните преди да ги присвои
   - Ако валидацията не успее, извежда съобщение и не записва данните

2. Student()
   - Конструктор по подразбиране
   - Пита потребителя за данните интерактивно
   - Валидира въведените данни
   - При невалидни данни, инициализира членовете с празни/нулеви стойности

МЕТОДИ (public):
---------------

Getter методи (const - не променят обекта):
- string getName() const     - Връща името
- string getFacNum() const    - Връща факултетния номер
- int getGroup() const        - Връща групата
- int getCourse() const       - Връща курса

bool validateData(string name, string facNum, int group, int course)
   - Валидира всички данни според правилата:
     * Име: 4-59 символа, без цифри
     * Факултетен номер: точно 9 цифри
     * Група: между 30 и 50
     * Курс: между 1 и 4
   - Извежда съобщение за грешка при невалидни данни
   - Връща true при валидни данни, false иначе

ВИРТУАЛНИ ФУНКЦИИ:
------------------
virtual void print() = 0;
   - Чисто виртуална функция (абстрактен метод)
   - Трябва да се имплементира в производния клас
   - Прави класа абстрактен - не може да се създават обекти от Student

virtual ~Student()
   - Виртуален деструктор
   - Извежда съобщение при изтриване на обект
   - Виртуалният деструктор е важен за правилно изтриване при наследяване

================================================================================

4. КЛАС StudentGrades (ПРОИЗВОДЕН КЛАС):
---------------------------------------

ОПИСАНИЕ:
---------
Производен клас от Student, който добавя функционалност за управление на оценки.
Съдържа динамичен масив от оценки и методи за работа с тях.

ЧЛЕНОВЕ ДАННИ (private):
-----------------------
double* grades    - Указател към динамичен масив от оценки
int gradeCount    - Брой на оценките (курс * 5)

КОНСТРУКТОРИ:
-------------

1. StudentGrades(string name, string facNum, int group, int course)
   - Параметризиран конструктор
   - Извиква конструктора на базовия клас Student
   - Създава масив за оценки (брой = курс * 5)
   - Пита потребителя за всяка оценка интерактивно
   - Валидира всяка оценка (трябва да е между 2.0 и 6.0)

2. StudentGrades(string name, string facNum, int group, int course, 
                 double* gradesArray, int gradeCount)
   - Конструктор за зареждане от файл
   - Приема готов масив от оценки
   - Не пита потребителя за вход
   - Използва се при четене от файл

3. StudentGrades()
   - Конструктор по подразбиране
   - Извиква конструктора по подразбиране на Student
   - Проверява дали данните са валидни (чрез getFacNum().empty())
   - Ако данните не са валидни, не създава масив от оценки
   - Ако данните са валидни, създава масив и пита за оценки

КОПИРАЩИ ФУНКЦИИ (RULE OF THREE):
---------------------------------

1. StudentGrades(const StudentGrades& other) - Копиращ конструктор
   - Създава дълбоко копие на обекта
   - Копира всички данни от базовия клас
   - Създава НОВ масив от оценки и копира всички стойности
   - Важно: Без това, при копиране ще се споделя един и същ масив (shallow copy)
   - Това би довело до двойно изтриване и корупция на данни

2. StudentGrades& operator=(const StudentGrades& other) - Оператор за присвояване
   - Използва "copy-and-swap" идиома
   - Създава временен обект с копиращ конструктор
   - Разменя указателите (swap)
   - Временният обект се изтрива автоматично
   - Осигурява exception safety

ВАЖНОСТ НА КОПИРАЩИТЕ ФУНКЦИИ:
------------------------------
Класът управлява динамична памет (double* grades). Без правилни копиращи функции:
- При копиране ще се споделя един и същ масив
- При изтриване ще се опита двойно изтриване (crash)
- Промяна в едно копие ще промени и другото

ДЕСТРУКТОР:
-----------
~StudentGrades()
   - Изтрива динамично заделения масив от оценки
   - Проверява дали указателят не е nullptr преди изтриване
   - Извежда съобщение при изтриване

МЕТОДИ:
-------

int getGradeCount() const
   - Връща броя на оценките

double getGrade(int index) const
   - Връща оценката на даден индекс

double average()
   - Изчислява средната оценка
   - Сумира всички оценки и дели на броя им

void print() override
   - Имплементира виртуалната функция print() от базовия клас
   - Извежда всички данни за студента и неговите оценки
   - Извежда и средната оценка

ПРИЯТЕЛСКИ ФУНКЦИИ (friend):
----------------------------
friend ostream& operator<<(ostream& os, StudentGrades& s)
   - Предефинира оператора << за извеждане
   - Позволява използване: cout << student
   - Има достъп до private членовете (grades, gradeCount)

friend void loadStudentsFromFile(...)
   - Позволява на функцията да достъпва private членовете
   - Необходимо за директно конструиране в масив

================================================================================

5. ГЛОБАЛНИ ПРОМЕНЛИВИ:
-----------------------

int studentGradesSize = 0;
   - Съхранява текущия брой студенти в системата

StudentGrades* studentsG = nullptr;
   - Указател към динамичен масив от студенти
   - nullptr означава, че няма заделена памет

================================================================================

6. ОСНОВНИ ФУНКЦИИ:
------------------

double calcGroupMaxAvg(int group, StudentGrades *students)
   Цел: Изчислява средната оценка на всички студенти в дадена група
   Параметри:
     - group: номерът на групата
     - students: масив от студенти
   Връща: Сумата от средните оценки (името е малко объркващо)
   Извежда: Брой членове и сумата от средните

void printStudent(string facNum, StudentGrades *students)
   Цел: Извежда информация за студент по факултетен номер
   Параметри:
     - facNum: факултетният номер за търсене
     - students: масив от студенти
   Действие: Търси и извежда първия студент с този номер

void saveStudentsToFile(StudentGrades* students, int count, const string& filename)
   Цел: Записва всички студенти във файл
   Параметри:
     - students: масив от студенти
     - count: брой студенти
     - filename: име на файла
   Формат на файла:
     Име ФакултетенНомер Група Курс Оценка1 Оценка2 ... ОценкаN
   За всеки студент се записва един ред

void loadStudentsFromFile(StudentGrades* &students, int &count, const string& filename)
   Цел: Зарежда студенти от файл
   Параметри:
     - students: референция към указател (може да се промени)
     - count: референция към брояч (може да се промени)
     - filename: име на файла
   Важно: Използва placement new за да избегне извикване на конструктор по подразбиране
   - Първо брои редовете във файла
   - Заделя сурова памет (char*)
   - Конструира обекти директно в паметта с placement new
   - Изтрива стария масив правилно (ако съществува)

================================================================================

7. ДОПЪЛНИТЕЛНИ ФУНКЦИОНАЛНОСТИ:
--------------------------------

void addStudent(StudentGrades* &students, int &count)
   Цел: Добавя нов студент в системата
   Алгоритъм:
     1. Създава нов студент (пита за данни)
     2. Проверява дали данните са валидни
     3. Заделя нова памет за масив с размер count+1
     4. Копира старите студенти с placement new
     5. Добавя новия студент
     6. Изтрива стария масив
     7. Обновява указателя и брояча
   
   Важно: Използва raw memory allocation за да избегне извикване на 
          конструктор по подразбиране за всички елементи

void deleteStudent(StudentGrades* &students, int &count, const string& facNum)
   Цел: Изтрива студент по факултетен номер
   Алгоритъм:
     1. Търси студента в масива
     2. Пита за потвърждение
     3. Създава нов масив с размер count-1
     4. Копира всички студенти освен изтривания
     5. Изтрива стария масив
     6. Записва действието в лог файл (actions.log)

void sortStudentsByAverage(StudentGrades* students, int count)
   Цел: Сортира студентите по средна оценка (низходящо)
   Алгоритъм: Selection sort (най-простата сортировка)
   - Сравнява средните оценки
   - Разменя обектите с swap() (използва копиращи функции)

void searchByKeyword(StudentGrades* students, int count)
   Цел: Търси студенти по ключова дума в името
   Алгоритъм:
     - Пита за ключова дума
     - Използва find() за търсене в името
     - Извежда резултатите на екран и във файл (search_results.txt)

void groupStatistics(StudentGrades* students, int count)
   Цел: Изчислява статистика за дадена група
   Изчислява:
     - Брой студенти в групата
     - Средна оценка на групата
   Записва резултата в group_stats.txt

void fullReport(StudentGrades* students, int count)
   Цел: Генерира пълен отчет за всички студенти
   Съдържа:
     - Брой студенти по курсове (1-4)
     - Брой отличници (средна оценка > 5.50)
   Записва в full_report.txt

================================================================================

8. ФУНКЦИЯ main():
------------------

СТРУКТУРА:
----------
Програмата работи с меню-базиран интерфейс. Потребителят избира опция от менюто
и програмата изпълнява съответната функция.

ОПЦИИ В МЕНЮТО:
---------------
1.  Print all students        - Извежда всички студенти
2.  Save to file             - Записва студентите във файл
3.  Load from file           - Зарежда студенти от файл
4.  Search by faculty number - Търси по факултетен номер
5.  Calculate max group avg  - Изчислява средна за група
6.  Add new student          - Добавя нов студент
7.  Delete student           - Изтрива студент
8.  Sort by average          - Сортира по средна оценка
9.  Search by name keyword   - Търси по име
10. Group statistics         - Статистика за група
11. Generate full report    - Пълен отчет
12. Exit                    - Изход

ЦИКЪЛ:
------
while (running) - Програмата работи докато running е true
При избор на опция 12, running става false и цикълът приключва

ОСВОБОЖДАВАНЕ НА ПАМЕТ:
---------------------
Преди изход, програмата правилно изтрива всички обекти:
1. Извиква деструктора за всеки студент
2. Освобождава заделената памет

================================================================================

9. ВАЖНИ КОНЦЕПЦИИ И ТЕХНИКИ:
-----------------------------

PLACEMENT NEW:
--------------
Използва се за конструиране на обекти в предварително заделена памет.
Синтаксис: new (адрес) Тип(параметри)

Причини за използване:
- new[] винаги извиква конструктор по подразбиране за всички елементи
- Искаме да контролираме кога и как се конструират обектите
- Избягваме ненужни извиквания на конструктори

Пример:
char* memory = new char[sizeof(StudentGrades) * 10];
StudentGrades* arr = reinterpret_cast<StudentGrades*>(memory);
new (arr + 0) StudentGrades(...);  // Конструира само първия

RULE OF THREE:
--------------
Ако класът управлява динамична памет, трябва да дефинира:
1. Деструктор
2. Копиращ конструктор
3. Оператор за присвояване

Без тези, компилаторът генерира версии по подразбиране, които правят
shallow copy (копират само указателите), което води до проблеми.

НАСЛЕДЯВАНЕ:
-----------
StudentGrades наследява Student:
- Има достъп до public и protected членовете на Student
- Може да предефинира виртуални функции (override)
- Виртуалният деструктор осигурява правилно изтриване

ВИРТУАЛНИ ФУНКЦИИ:
-----------------
virtual void print() = 0; - Чисто виртуална функция
- Класът става абстрактен
- Не може да се създават обекти от Student
- Трябва да се имплементира в производния клас

virtual ~Student() - Виртуален деструктор
- Важен за правилно изтриване при наследяване
- Осигурява извикване на деструктора на производния клас

DEEP COPY vs SHALLOW COPY:
--------------------------
Shallow copy (плитко копие):
- Копира само указателя, не и данните
- Два обекта сочат към един и същ масив
- Проблеми при изтриване и промяна

Deep copy (дълбоко копие):
- Копира данните
- Всеки обект има собствен масив
- Безопасно при изтриване и промяна

Нашата имплементация използва deep copy в копиращите функции.

УПРАВЛЕНИЕ НА ПАМЕТТА:
--------------------
Всички масиви се управляват ръчно:
- new[] / delete[] за обикновени масиви
- new / delete за единични обекти
- Raw memory + placement new за контрол над конструкторите
- Винаги проверяваме за nullptr преди изтриване

ВАЛИДАЦИЯ НА ДАННИ:
------------------
Всички входни данни се валидират:
- Име: 4-59 символа, без цифри
- Факултетен номер: точно 9 цифри
- Група: 30-50
- Курс: 1-4
- Оценки: 2.0-6.0

При невалидни данни, операцията се прекратява.

ФАЙЛОВО УПРАВЛЕНИЕ:
------------------
Програмата работи с няколко типа файлове:
- students.txt - Основен файл за студенти
- search_results.txt - Резултати от търсене
- group_stats.txt - Статистика за група
- full_report.txt - Пълен отчет
- actions.log - Лог на действията (изтривания)

================================================================================

10. ПРИМЕРИ ЗА ИЗПОЛЗВАНЕ:
--------------------------

ДОБАВЯНЕ НА СТУДЕНТ:
------------------
1. Изберете опция 6 от менюто
2. Въведете данните за студента
3. Въведете оценките (брой = курс * 5)
4. Студентът се добавя автоматично

ЗАРЕЖДАНЕ ОТ ФАЙЛ:
-----------------
1. Подгответе файл students.txt с формат:
   Име ФакултетенНомер Група Курс Оценка1 Оценка2 ... ОценкаN
2. Изберете опция 3
3. Въведете името на файла
4. Студентите се зареждат автоматично

СОРТИРАНЕ:
---------
1. Изберете опция 8
2. Студентите се сортират по средна оценка (най-високите първи)
3. Резултатът се извежда на екран

ТЪРСЕНЕ:
--------
Опция 4: Търсене по факултетен номер
Опция 9: Търсене по име (ключова дума)

================================================================================
КРАЙ НА ДОКУМЕНТАЦИЯТА
================================================================================
*/
