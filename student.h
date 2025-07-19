#ifndef STUDENT_H
#define STUDENT_H

#include<string>

class student{
    private:
       int roll_no;
       std::string name;
       float marks;
    
    public:
       student(){
          roll_no=0;
          name="";
          marks=0;
       }

       static bool rollNumberExists(int roll);
       void input_values();
       void store_values_inFile();
       static void show_values_fromFile();
};

void enter_student_details();
void show_student_details();
void edit_marks();

#endif
