#include "student.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <string>
#include <cctype>
#include <limits>
using namespace std;

bool student::rollNumberExists(int roll){
    ifstream file("students.csv");
    if (!file.is_open()) return false;

    string line;
    while (getline(file,line)){
        stringstream ss(line);
        string rollStr;
        getline(ss, rollStr,','); //geting role number from line

        try{
            int existingRoll = stoi(rollStr);
            if (existingRoll == roll)
               return true;
        } catch (...){
            continue; 
        }
    }
    return false;
}

void student::input_values(){
    cout<<"\nEnter values as follow:";
    
    // Roll number: validate positive integer
    while (true){
        cout<<"\nRoll_no.: ";
        if ( cin >> roll_no && roll_no > 0){
            if (!rollNumberExists(roll_no))
               break;
            else 
               cout<< "Roll number already exists. Enter a different one.\n";
        }
        else {
            cout<< "Invalid roll number. Please enter a positie integer. \n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
        
    // Name: validate alphabetic with spaces
    while (true){
        cout<<"\nName: ";
        getline(cin >> ws, name);

        if(!name.empty() && all_of(name.begin(), name.end(), [](char c){
            return isalpha(c) || isspace(c);
        })) {
            break;
        } else {
            cout<< "Invalid name. Use letters and space only. \n";
        }
    }

    // Marks: validate float between 0 and 100
    while(true) {
        cout<< "\nMarks: ";
        if (cin >> marks && marks >= 0 && marks <= 100)
           break;
        else {
            cout<< "Invalid marks. Enter a number between 0 and 100.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
        }
    }
}

void student::store_values_inFile(){
    ofstream fout("students.csv", ios::app);
    if (fout.is_open()){
        fout<< roll_no <<","<<name<<","<<marks<<endl;
        fout.close();
        cout<<"\nValues stored in file successfully\n";
    } else {
        cout<<"\nError opening file!";
    }
}

void student::show_values_fromFile(){
    ifstream fin("students.csv");
    if (fin.is_open()){
        string line;
        cout << "\nStored Student Records:\n";
        cout << "---------------------------\n";
        while (getline(fin, line)) {
            stringstream ss(line);
            string rollStr, name, marksStr;
            getline(ss, rollStr, ',');
            getline(ss, name, ',');
            getline(ss, marksStr, ',');
            
            int roll = stoi(rollStr);
            float marks = stof(marksStr);
            cout << "Roll No: " << roll << "\tName: " << name << "\tMarks: " << marks << endl;
        }
        fin.close();
    }
    else {
        cout<<"\nError opening file!";
    }
}

void enter_student_details(){
    int choice;

    system("cls");
    cout<<"\n1. Single Entry";
    cout<<"\n2. Multiple Entry";
    cout<<"\n3. Back to Menu";
    cout<<"\n\n>>"; cin>>choice;

    switch(choice){
        case 1:{
            student s;
            s.input_values();
            s.store_values_inFile();
            break;
        }

        case 2:{
            int n;
            cout<<"\nEnter the number students: ";
            cin>>n;
            vector<student> s(n);

            for(int i=0; i<n; i++){
                cout<<"\n--Student "<<i+1<<" --";
                s[i].input_values();
                s[i].store_values_inFile();
            }

            break;
        }
        
        case 3:{
            return;
        }

        default:
           cout<<"Invalid option. Try again!!";
    }
    return;
}

void show_student_details(){
    student::show_values_fromFile();
    system("pause");
}

void edit_marks() {
    string line;
    int roll_input, new_marks;
    bool found = false;

    ifstream fin("students.csv");
    if (!fin) {
        cout << "\nNo student records found! 'students.csv' does not exist.\n";
        system("pause");
        return;
    }

    cout << "\nEnter roll number to edit marks: ";
    while (!(cin >> roll_input)) {
        cout << "Invalid input! Please enter a valid roll number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    ofstream temp("temp.csv");
    if (!temp) {
        cout << "\nError creating temporary file!\n";
        fin.close();
        system("pause");
        return;
    }

    while (getline(fin, line)) {
        stringstream ss(line);
        string r_str, n_str, m_str;
        getline(ss, r_str, ',');
        getline(ss, n_str, ',');
        getline(ss, m_str, ',');

        int file_roll = stoi(r_str);
        if (file_roll == roll_input) {
            found = true;
            cout << "\nCurrent Marks: " << m_str;
            cout << "\nEnter new marks: ";
            while (true) {
                if (cin >> new_marks && new_marks >= 0 && new_marks <= 100)
                    break;
                cout << "Invalid input! Enter numeric marks between 0 and 100: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            temp << file_roll << "," << n_str << "," << new_marks << endl;
        } else {
            temp << line << endl;
        }
    }

    fin.close();
    temp.close();

    if (found) {
        remove("students.csv");
        rename("temp.csv", "students.csv");
        cout << "\nMarks updated successfully!\n";
    } else {
        remove("temp.csv");
        cout << "\nStudent with Roll No. " << roll_input << " not found.\n";
    }

    system("pause");
}
