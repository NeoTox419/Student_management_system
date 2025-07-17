#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cctype>
#include <limits>
#include <algorithm>
using namespace std;

bool rollNumberExists(int roll){
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

class student{
    private:
        int roll_no;
        string name;
        float marks;
    public:
        student(){
            roll_no=0;
            name="";
            marks=0;
        }

        void input_values(){
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

        void store_values_inFile(){
            ofstream fout("students.csv", ios::app);
            if (fout.is_open()){
                fout<< roll_no <<","<<name<<","<<marks<<endl;
                fout.close();
                cout<<"\nValues stored in file successfully\n";
            } else {
                cout<<"\nError opening file!";
            }
        }
        
        static void show_values_fromFile(){
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
};

void Case1(){
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

void Case2(){
    student::show_values_fromFile();
    system("pause");
}

int main(){
    int choice;
    mn:
    system("cls");
    cout<<"\tWelcome to Studnet Mangement System";
    cout<<"\n\t Menu";
    cout<<"\n1. Enter student details";
    cout<<"\n2. View student details";
    cout<<"\n3. exit";
    cout<<"\n\n Enter choice>>";
    while (!(cin>> choice)){
        cout<< "Invalid input! Enter a number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    switch(choice){
        case 1:
           Case1();
           goto mn;

        case 2:
           Case2();
           goto mn;

        case 3: 
           exit(0);

        default: 
           cout<<"\nINVALID CHOICE! \nTry again!\n";
           system("pause");
           goto mn;
        
    }
    return 0;
}
  