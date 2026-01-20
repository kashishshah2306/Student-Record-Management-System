#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
using namespace std;

//node structure to store the information of the student
struct Student{
    int rollNumber;
    string name;
    float marks;
    Student* next;
};

//class to manage the linked list of student records
class StudentRecordSystem{
private:
    Student* head;
public:
    StudentRecordSystem(){
        head = NULL;
    }

//Destructor
    ~StudentRecordSystem(){
        Student* current = head;
        Student* next;
        while (current != NULL){
            next = current->next;
            delete current;
            current = next;
        }
    }

//To Insert a new student record
    void insertRecord(){
        Student* newStudent = new Student();
        
        cout << "\n--- Insert New Student Record ---\n";
        cout << "Enter Roll Number: "<<endl;
        cin >> newStudent->rollNumber;
        
        //if roll number already exists
        if (searchByRollNumber(newStudent->rollNumber) != NULL){
            cout << "Error: Roll number already exists!\n";
            delete newStudent;
            return;
        }
        
//clear input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter Name: "<<endl;
        getline(cin, newStudent->name);
        cout << "Enter Marks: "<<endl;
        cin >> newStudent->marks;
        
        newStudent->next = NULL;
        
//insert at the beginning
        if (head == NULL){
            head = newStudent;
        } else {
            newStudent->next = head;
            head = newStudent;
        }
        
        cout << "\nRecord inserted successfully!\n";
    }

//display all student records
    void displayAllRecords(){
        if (head == NULL){
            cout << "\nNo records to display. Database is empty.\n";
            return;
        }
        
        cout << "\n--- All Student Records ---\n";
        cout << setw(15) << left << "Roll Number" 
             << setw(25) << left << "Name" 
             << setw(10) << left << "Marks" << endl;
        cout << string(50, '-') << endl;
        
        Student* current = head;
        while (current != NULL){
            cout << setw(15) << left << current->rollNumber
                 << setw(25) << left << current->name
                 << setw(10) << left << fixed << setprecision(2) << current->marks << endl;
            current = current->next;
        }
        cout << endl;
    }

//search for a student by roll number
    Student* searchByRollNumber(int roll){
        Student* current = head;
        while (current != NULL) {
            if (current->rollNumber == roll){
                return current;
            }
            current = current->next;
        }
        return NULL;
    }

//search and display student record
    void searchRecord(){
        int roll;
        cout << "\n--- Search Student Record ---\n";
        cout << "Enter Roll Number to search: ";
        cin >> roll;
        
        Student* student = searchByRollNumber(roll);
        
        if (student != NULL){
            cout << "\nRecord Found!\n";
            cout << string(50, '-') << endl;
            cout << "Roll Number: " << student->rollNumber << endl;
            cout << "Name: " << student->name << endl;
            cout << "Marks: " << fixed << setprecision(2) << student->marks << endl;
            cout << string(50, '-') << endl;
        } else {
            cout << "\nRecord not found with Roll Number: " << roll << endl;
        }
    }

//delete a student record by roll number
    void deleteRecord(){
        if (head == NULL){
            cout << "\nNo records to delete. Database is empty.\n";
            return;
        }
        
        int roll;
        cout << "\n--- Delete Student Record ---\n";
        cout << "Enter Roll Number to delete: ";
        cin >> roll;
        
        Student* current = head;
        Student* previous = NULL;
        
//searching for the node to delete
        while (current != NULL && current->rollNumber != roll){
            previous = current;
            current = current->next;
        }
        
        if (current == NULL){
            cout << "\nRecord not found with Roll Number: " << roll << endl;
            return;
        }
        
//delete the node
        if (previous == NULL){
            // Deleting the head node
            head = current->next;
        } else {
            previous->next = current->next;
        }
        
        cout << "\nRecord of " << current->name << " (Roll Number: " 
             << current->rollNumber << ") deleted successfully!\n";
        delete current;
    }
//total number of records
    int countRecords(){
        int count = 0;
        Student* current = head;
        while (current != NULL){
            count++;
            current = current->next;
        }
        return count;
    }
};

//displaying menu
void displayMenu(){
    cout << "\n========================================\n";
    cout << "  STUDENT RECORD MANAGEMENT SYSTEM\n";
    cout << "========================================\n";
    cout << "1. Insert New Record\n";
    cout << "2. Display All Records\n";
    cout << "3. Search Record by Roll Number\n";
    cout << "4. Delete Record\n";
    cout << "5. Display Total Records\n";
    cout << "6. Exit\n";
    cout << "========================================\n";
    cout << "Enter your choice: ";
}

int main(){
    StudentRecordSystem system;
    int choice;
    
    cout << "\n*** Welcome to Student Record Management System ***\n";
    
    do{
        displayMenu();
        cin >> choice;
        
        switch (choice){
            case 1:
                system.insertRecord();
                break;
            case 2:
                system.displayAllRecords();
                break;
            case 3:
                system.searchRecord();
                break;
            case 4:
                system.deleteRecord();
                break;
            case 5:
                cout << "\nTotal Records in Database: " << system.countRecords() << endl;
                break;
            case 6:
                cout << "\nThank you for using Student Record Management System!\n";
                cout << "Exiting program...\n\n";
                break;
            default:
                cout << "\nInvalid choice! Please enter a number between 1 and 6.\n";
        }
        
    } 
    while (choice != 6);
    
    return 0;
}
