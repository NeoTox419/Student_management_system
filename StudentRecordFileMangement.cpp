#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

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
            cout<<"\nRoll_no.:"; cin>>roll_no;
            cout<<"\nName :";
            getline(cin >> ws, name);
            cout<<"\nMarks :"; cin>>marks;
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
    student s;
    s.input_values();
    s.store_values_inFile();
    system("pause");
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
    cin>>choice;

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
  