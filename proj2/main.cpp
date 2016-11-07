#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

struct student {
  string fname;
  string lname;
  int student_id;
  int num_days_attended;
  vector<double> test_scores;
  vector<double> project_scores;
};

struct gradebook {
  string class_name;
  int num_students;
  int num_tests;
  int num_projects;
  int num_days;
  vector<int> possible_project_points;
};

void print_logo();
void read_gradebook_headers(gradebook&, ifstream&);
void read_students(vector<student>&, gradebook&, ifstream&);
void print_menu();
void add_student(vector<student>&, gradebook&);
void drop_student(vector<student>&);
int find_student_index(vector<student>&);
void enter_class_grades();
void print_class_report();
void view_student_record();
void save();

int main(){

  print_logo();

  string filename;
  cout << "Enter grade file: ";
  cin >> filename;

  gradebook gb;
  vector<student> students;
  ifstream grade_file;
  grade_file.open(filename);
  read_gradebook_headers(gb, grade_file);
  read_students(students, gb, grade_file);
  grade_file.close();

  char user_input;
  while (user_input != 'Q'){
    print_menu();
    cin >> user_input;
    switch(user_input){
      case 'A': add_student(students, gb); break;
      case 'D': drop_student(students); break;
      case 'E': enter_class_grades(); break;
      case 'P': print_class_report(); break;
      case 'V': view_student_record(); break;
      case 'S': save(); break;
      case 'X': user_input = 'Q'; break;
      default: cout << "Input not recognized"; break;
    }
  }

}

void print_logo(){
  cout << "+---------------------------+" << endl;
  cout << "|      GRADEBOOK DELUX      |" << endl;
  cout << "|       Kendall Weihe       |" << endl;
  cout << "+---------------------------+" << endl;
}

void read_gradebook_headers(gradebook &gb, ifstream &file){
  file >> gb.class_name;
  file >> gb.num_students;
  file >> gb.num_tests;
  file >> gb.num_projects;
  file >> gb.num_days;

  int temp;
  for (int i = 0; i < gb.num_projects; i++){
    file >> temp;
    gb.possible_project_points.push_back(temp);
  }
}

void read_students(vector<student> &students, gradebook &gb, ifstream &file){
  for (int i = 0; i < gb.num_students; i++){
    student temp_student;
    file >> temp_student.fname;
    file >> temp_student.lname;
    file >> temp_student.student_id;
    file >> temp_student.num_days_attended;
    double temp_score;
    for (int j = 0; j < gb.num_tests; j++){
      file >> temp_score;
      temp_student.test_scores.push_back(temp_score);
    }
    for (int j = 0; j < gb.num_projects; j++){
      file >> temp_score;
      temp_student.project_scores.push_back(temp_score);
    }
    students.push_back(temp_student);
  }
}

void print_menu(){
  cout << "A – Add student" << endl;
  cout << "D – Drop student" << endl;
  cout << "E – Enter class grades" << endl;
  cout << "P – Print class report" << endl;
  cout << "V – View student record" << endl;
  cout << "S - Save" << endl;
  cout << "X – Exit" << endl;
}

void add_student(vector<student> &students, gradebook &gb){
  student new_student;
  cout << "Enter First Name and Last Name: ";
  cin >> new_student.fname >> new_student.lname;
  cout << "Enter Student ID: ";
  cin >> new_student.student_id;
  cout << "Enter number of lecture days attended: ";
  cin >> new_student.num_days_attended;
  double temp_score;
  for (int i = 0; i < gb.num_tests; i++){
    cout << "Enter the score for test #" << i+1 << ": ";
    cin >> temp_score;
    new_student.test_scores.push_back(temp_score);
  }
  for (int i = 0; i < gb.num_projects; i++){
    cout << "Enter the score for project #" << i+1 << ": ";
    cin >> temp_score;
    new_student.project_scores.push_back(temp_score);
  }
  students.push_back(new_student);
}

void drop_student(vector<student> &students){
  int student_index;
  student_index = find_student_index(students);
  if (student_index > 0){
    students.erase(students.begin()+student_index);
  }
  else {
    cout << "The student was not found" << endl;
  }
}

int find_student_index(vector<student> &students){
  string fname, lname;
  cout << "Enter the students first and last name: ";
  cin >> fname >> lname;
  for (int i = 0; i < students.size(); i++){
    if (students[i].fname == fname && students[i].lname == lname){
      return i;
    }
  }
  return -1;
}

void enter_class_grades(){

}

void print_class_report(){

}

void view_student_record(){

}

void save(){

}
