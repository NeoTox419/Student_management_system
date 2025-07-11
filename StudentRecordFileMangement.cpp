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
            cout<<"\nName :"; cin>>name;
            cout<<"\nMarks :"; cin>>marks;
        }
        void store_values_inFile(){
            ofstream fout("students.csv", ios::app);
            if (fout.is_open()){
                fout<< roll_no <<","<<name<<","<<marks<<endl;
                fout.close();
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

}

void Case2(){

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

        case 2:

        case 3: 
           exit(0);

        default: 
           cout<<"\nINVALID CHOICE! \nTry again! press any key to continue...";
           getchar();
           goto mn;
        
    }
    return 0;
}
  