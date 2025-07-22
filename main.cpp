#include "student.h"
#include <iostream>
#include <limits>
using namespace std;

int main(){
    int choice;
    mn:
    system("cls");
    cout<<"\tWelcome to Studnet Mangement System";
    cout<<"\n\t Menu";
    cout<<"\n1. Enter student details";
    cout<<"\n2. View student details";
    cout<<"\n3. Edit student marks";
    cout<<"\n4. Search a student";
    cout<<"\n5. exit";
    cout<<"\n\n Enter choice>>";
    while (!(cin>> choice)){
        cout<< "Invalid input! Enter a number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    switch(choice){
        case 1:
           enter_student_details();
           goto mn;

        case 2:
           show_student_details();
           goto mn;
        
        case 3:{
            string filename = select_existing_file();
            if(filename.empty()) break;
            edit_marks(filename);
            goto mn;
        }

        case 4:{
            string filenanme = select_existing_file();
            if(!filenanme.empty()){
                student::search_by_roll(filenanme);
            }
            goto mn;
        }

        case 5: 
           exit(0);

        default: 
           cout<<"\nINVALID CHOICE! \nTry again!\n";
           system("pause");
           goto mn;
        
    }
    return 0;
}