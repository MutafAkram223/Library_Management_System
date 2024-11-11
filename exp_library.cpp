#include<iostream>
#include<conio.h>
#include<stdlib.h>
using namespace std;

// ------------------ Prototypes
void mainHeader();
char adminMenu();
void clearScreen();
string loginMenu();
void addStudent();
void viewAllStudents();
void addStudentIntoArray(string name, float balance);
void addUser(string name, string pass, string role);
void viewStudentBalances();
void addBook();
void editBook();
void viewBooksStatus();
void viewBalance(string username);
void depositBalance(string username);
void issueBook(string username);
char studentMenu();
int findStudentIndex(string username);
int findBookIndex(string id);

// ------------------ Constants
const int MAX_RECORDS = 20;
const int MAX_BOOKS = 50;

// ------------------ Data Structures
string usernameA[MAX_RECORDS];
string passwordsA[MAX_RECORDS];
string rolesA[MAX_RECORDS];
int userCount = 0;

string student_name[MAX_RECORDS];
float student_balance[MAX_RECORDS];
string student_issuedBook[MAX_RECORDS];
int entry_count = 0;

string bookID[MAX_BOOKS];
string bookName[MAX_BOOKS];
string bookStatus[MAX_BOOKS]; // "Available" or "Issued"
int bookCount = 0;

string username;

// Main function
int main() {
    addUser("admin", "123", "ADMIN");

    string who = " ";
    while (true) {
        who = loginMenu();
        if (who == "ADMIN") {
            char option = ' ';
            while (true) {
                system("cls");
                option = adminMenu();
                if (option == '1') { // Add User
                    cout << "Enter username: ";
                    string username;
                    cin >> username;

                    cout << "Enter password: ";
                    string pass;
                    cin >> pass;

                    cout << "Enter role (ADMIN/STUDENT): ";
                    string role;
                    cin >> role;

                    addUser(username, pass, role);

                } else if (option == '2') { // Add Student
                    addStudent();

                } else if (option == '3') { // Add Books
                    addBook();

                } else if (option == '4') { // Edit Books
                    editBook();

                } else if (option == '5') { // View Books Status
                    viewBooksStatus();

                } else if (option == '6') { // View Enrolled Students
                    viewAllStudents();

                } else if (option == '7') { // View Student Balance
                    viewStudentBalances();

                } else if (option == '8') { // Logout
                    break;

                } else {
                    cout << "You Chose Wrong option " << endl;
                }
                clearScreen();
            } // end of admin while loop

        } else if (who == "STUDENT") {
            char studentOption = ' ';
            while (true) {
                system("cls");
                studentOption = studentMenu();
                if (studentOption == '1') { // View Balance
                    viewBalance(username);

                } else if (studentOption == '2') { // Deposit Balance
                    depositBalance(username);

                } else if (studentOption == '3') { // Issue Book
                    issueBook(username);

                } else if (studentOption == '4') { // Logout
                    break;

                } else {
                    cout << "Wrong selection! Try again";
                }
                clearScreen();
            } // end of student menu while loop

        } else if (who == "EXIT") {
            cout << "Choose correct option" << endl;
        } else {
            cout << "You entered wrong option " << endl;
        }
        clearScreen();
    } // end of while

    return 0;
} // end of main function

// Function definitions
void mainHeader() {
    cout << "----------------------------------------------" << endl;
    cout << "---          Library Management System     ---" << endl;
    cout << "----------------------------------------------" << endl;
}

string loginMenu() {
    mainHeader();
    cout << "Enter username: ";
    cin >> username;

    cout << "Enter password: ";
    string pass;
    cin >> pass;

    for (int i = 0; i < userCount; i++) {
        if (usernameA[i] == username && passwordsA[i] == pass) {
            return rolesA[i];
        }
    }
    cout << "Invalid username or password." << endl;
    return "EXIT";
}

char adminMenu() {
    mainHeader();
    cout << "Admin Main Menu > " << endl;
    cout << "1- Add User " << endl;
    cout << "2- Add Student" << endl;
    cout << "3- Add Books" << endl;
    cout << "4- Edit Books" << endl;
    cout << "5- View Books Status" << endl;
    cout << "6- View Enrolled Students" << endl;
    cout << "7- View Student Balance" << endl;
    cout << "8- Logout " << endl;
    cout << "Choose Your Option: ";
    char option;
    cin >> option;
    return option;
}

char studentMenu() {
    mainHeader();
    cout << "Student Main Menu > " << endl;
    cout << "1- View Balance " << endl;
    cout << "2- Deposit Balance " << endl;
    cout << "3- Issue Book " << endl;
    cout << "4- Logout " << endl;
    cout << "Choose Your Option: ";
    char option;
    cin >> option;
    return option;
}

void clearScreen() {
    cout << "Press any key to continue " << endl;
    getch();
    system("CLS");
}

void addUser(string name, string pass, string role) {
    if (userCount >= MAX_RECORDS) {
        cout << "Cannot add more users. Maximum capacity reached." << endl;
        return;
    }
    usernameA[userCount] = name;
    passwordsA[userCount] = pass;
    rolesA[userCount] = role;
    userCount++;
    cout << "User added successfully!" << endl;
}

void addStudent() {
    string name;
    cout << "Enter student name: ";
    cin >> name;

    cout << "Enter initial balance: ";
    float balance;
    cin >> balance;

    addStudentIntoArray(name, balance);
    addUser(name, "123", "STUDENT"); // Default password for new students

    cout << "Student added successfully!" << endl;
}

void addStudentIntoArray(string name, float balance) {
    if (entry_count >= MAX_RECORDS) {
        cout << "Cannot add more students. Maximum capacity reached." << endl;
        return;
    }
    student_name[entry_count] = name;
    student_balance[entry_count] = balance;
    student_issuedBook[entry_count] = "";
    entry_count++;
}

void viewAllStudents() {
    cout << "Name\tBalance\tIssued Book" << endl;
    for (int i = 0; i < entry_count; i++) {
        cout << student_name[i] << "\t" << student_balance[i] << "\t" << student_issuedBook[i] << endl;
    }
}

void viewStudentBalances() {
    cout << "Name\tBalance" << endl;
    for (int i = 0; i < entry_count; i++) {
        cout << student_name[i] << "\t" << student_balance[i] << endl;
    }
}

void addBook() {
    if (bookCount >= MAX_BOOKS) {
        cout << "Cannot add more books. Maximum capacity reached." << endl;
        return;
    }
    cout << "Enter Book ID: ";
    string id;
    cin >> id;

    cout << "Enter Book Name: ";
    string name;
    cin.ignore(); // To consume any leftover newline character
    getline(cin, name);

    bookID[bookCount] = id;
    bookName[bookCount] = name;
    bookStatus[bookCount] = "Available";
    bookCount++;

    cout << "Book added successfully!" << endl;
}

void editBook() {
    cout << "Enter Book ID to edit: ";
    string id;
    cin >> id;
    int index = findBookIndex(id);
    if (index == -1) {
        cout << "Book not found." << endl;
        return;
    }

    cout << "Enter new Book Name: ";
    string name;
    cin.ignore();
    getline(cin, name);

    bookName[index] = name;
    cout << "Book updated successfully!" << endl;
}

void viewBooksStatus() {
    cout << "Book ID\tBook Name\tStatus" << endl;
    for (int i = 0; i < bookCount; i++) {
        cout << bookID[i] << "\t" << bookName[i] << "\t" << bookStatus[i] << endl;
    }
}

void viewBalance(string username) {
    int index = findStudentIndex(username);
    if (index == -1) {
        cout << "Student not found." << endl;
        return;
    }
    cout << "Your balance is: " << student_balance[index] << endl;
}

void depositBalance(string username) {
    int index = findStudentIndex(username);
    if (index == -1) {
        cout << "Student not found." << endl;
        return;
    }
    cout << "Enter amount to deposit: ";
    float amount;
    cin >> amount;
    if (amount < 0) {
        cout << "Invalid amount." << endl;
        return;
    }
    student_balance[index] += amount;
    cout << "Amount deposited successfully. New balance: " << student_balance[index] << endl;
}

void issueBook(string username) {
    int studentIndex = findStudentIndex(username);
    if (studentIndex == -1) {
        cout << "Student not found." << endl;
        return;
    }
    if (student_issuedBook[studentIndex] != "") {
        cout << "You have already issued a book: " << student_issuedBook[studentIndex] << endl;
        return;
    }
    cout << "Available books: " << endl;
    for (int i = 0; i < bookCount; i++) {
        if (bookStatus[i] == "Available") {
            cout << bookID[i] << "\t" << bookName[i] << endl;
        }
    }
    cout << "Enter Book ID to issue: ";
    string id;
    cin >> id;
    int bookIndex = findBookIndex(id);
    if (bookIndex == -1 || bookStatus[bookIndex] != "Available") {
        cout << "Book not found or not available." << endl;
        return;
    }
    // Assume issuing a book costs some amount, e.g., $10
    float issueCost = 10.0;
    if (student_balance[studentIndex] < issueCost) {
        cout << "Insufficient balance to issue book. Please deposit funds." << endl;
        return;
    }
    student_balance[studentIndex] -= issueCost;
    student_issuedBook[studentIndex] = bookID[bookIndex];
    bookStatus[bookIndex] = "Issued";
    cout << "Book issued successfully. Remaining balance: " << student_balance[studentIndex] << endl;
}

int findStudentIndex(string username) {
    for (int i = 0; i < entry_count; i++) {
        if (student_name[i] == username) {
            return i;
        }
    }
    return -1;
}

int findBookIndex(string id) {
    for (int i = 0; i < bookCount; i++) {
        if (bookID[i] == id) {
            return i;
        }
    }
    return -1;
}
