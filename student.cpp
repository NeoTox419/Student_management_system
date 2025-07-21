#include "student.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <string>
#include <cctype>
#include <limits>
#include <filesystem>
using namespace std;
namespace fs = filesystem;

bool student::rollNumberExists(int roll,const string& filename){
    ifstream file(filename);
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

void student::input_values(const string& filename){
    cout<<"\nEnter values as follow:";
    
    // Roll number: validate positive integer
    while (true){
        cout<<"\nRoll_no.: ";
        if ( cin >> roll_no && roll_no > 0){
            if (!rollNumberExists(roll_no,filename))
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

void student::store_values_inFile(const string& filename){
    ofstream fout(filename, ios::app);
    if (fout.is_open()){
        fout<< roll_no <<","<<name<<","<<marks<<endl;
        fout.close();
        cout<<"\nValues stored in file successfully\n";
    } else {
        cout<<"\nError opening file!";
    }
}

void student::show_values_fromFile(const string& filename){
    ifstream fin(filename);
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

void enter_student_details(){
    int choice;

    system("cls");
    cout<<"\n1. Single Entry";
    cout<<"\n2. Multiple Entry";
    cout<<"\n3. Back to Menu";
    cout<<"\n\n>>"; cin>>choice;

    switch(choice){
        case 1:{
            string filename = create_or_select_file(); //allows creating or using existing file
            if (filename.empty()) break;

            student s;
            s.input_values(filename);
            s.store_values_inFile(filename);
            break;
        }

        case 2:{
            string filename = create_or_select_file(); //allows creating or using existing file
            if (filename.empty()) break;

            int n;
            cout<<"\nEnter the number students: ";
            cin>>n;
            vector<student> s(n);

            for(int i=0; i<n; i++){
                cout<<"\n--Student "<<i+1<<" --";
                s[i].input_values(filename);
                s[i].store_values_inFile(filename);
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
    string filename = select_existing_file();
    if(filename.empty()) return;

    student::show_values_fromFile(filename);
    system("pause");
}

void edit_marks(const string& filename) {
    string line;
    int roll_input, new_marks;
    bool found = false;

    ifstream fin(filename);
    if (!fin) {
        cout << "\nNo student records found! "<<filename<<" does not exist.\n";
        system("pause");
        return;
    }

    cout << "\nEnter roll number to edit marks: ";
    while (!(cin >> roll_input)) {
        cout << "Invalid input! Please enter a valid roll number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    ofstream temp("data/temp.csv");
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
        remove(filename.c_str());
        rename("data/temp.csv", filename.c_str());
        cout << "\nMarks updated successfully!\n";
    } else {
        remove("data/temp.csv");
        cout << "\nStudent with Roll No. " << roll_input << " not found.\n";
    }

    system("pause");
}

std::string create_or_select_file(){
    string filename;
    cout << "\n1. Create New File";
    cout << "\n2. Use Existing File";
    cout << "\nEnter your choice: ";

    int choice;
    while (!(cin >> choice) || (choice != 1 && choice != 2)) {
        cout << "Invalid input! Enter 1 or 2: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cin.ignore();

    if (choice == 1) {
        cout << "Enter new filename (without .csv): ";
        getline(cin, filename);
        filename += ".csv";
    } else {
        vector<string> csv_files;
        for (const auto& entry : fs::directory_iterator("data")) {
            if (entry.path().extension() == ".csv") {
                csv_files.push_back(entry.path().filename().string());
            }
        }

        if (csv_files.empty()) {
            cout << "No CSV files found. Please create a new file instead.\n";
            return create_or_select_file(); // restart selection
        }

        cout << "\nAvailable .csv files:\n";
        for (size_t i = 0; i < csv_files.size(); ++i) {
            cout << i + 1 << ". " << csv_files[i] << endl;
        }

        int file_choice;
        cout << "Select a file by number: ";
        while (!(cin >> file_choice) || file_choice < 1 || file_choice > csv_files.size()) {
            cout << "Invalid choice! Enter a number between 1 and " << csv_files.size() << ": ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        filename = csv_files[file_choice - 1];
        cin.ignore();
    }

    return filename = "data/" + filename;
}

std::string select_existing_file(){
    vector<string> csv_files;

    for (const auto& entry : fs::directory_iterator("data")) {
        if (entry.path().extension() == ".csv") {
            csv_files.push_back(entry.path().filename().string());
        }
    }

    if (csv_files.empty()) {
        cout << "\nNo student data found. Please add students first.\n";
        return "";
    }

    cout << "\nAvailable data files:\n";
    for (size_t i = 0; i < csv_files.size(); ++i) {
        cout << i + 1 << ". " << csv_files[i] << endl;
    }

    int choice;
    cout << "Select a file by number: ";
    while (!(cin >> choice) || choice < 1 || choice > csv_files.size()) {
        cout << "Invalid choice! Try again: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cin.ignore();
    return "data/" + csv_files[choice - 1];
}