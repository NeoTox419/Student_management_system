#ifndef STUDENT_H
#define STUDENT_H

#include<string>
using namespace std;

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

       static bool rollNumberExists(int roll,const string& filename);
       void input_values(const string& filename);
       void store_values_inFile(const string& filename);
       static void show_values_fromFile(const string& filename);
       static void sort_file_by_roll(const string& filename);
       static void search_by_roll(const string& filename);
};

void enter_student_details();
void show_student_details();
void edit_marks(const string& filename);
std::string create_or_select_file();
std::string select_existing_file();

#endif
