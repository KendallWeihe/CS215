#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

//-----------------------------------------------------------------------------------------------------------
//											structs
//-----------------------------------------------------------------------------------------------------------
// struct for students and a gradebook
struct student {
  string fname;
  string lname;
  int student_id;
  double num_days_attended;
  vector<double> test_scores;
  vector<double> project_scores;
  double test_average;
  double project_average;
  double attendance_average;
  double grade_percentage;
  char letter_grade;
};

struct gradebook {
  string class_name;
  double num_students;
  double num_tests;
  double num_projects;
  double num_days;
  vector<double> possible_project_points;
};

//-----------------------------------------------------------------------------------------------------------
//											function declarations
//-----------------------------------------------------------------------------------------------------------
// function declarations
void print_logo();
void read_gradebook_headers(gradebook&, ifstream&);
void read_students(vector<student>&, gradebook&, ifstream&);
void print_menu();
void add_student(vector<student>&, gradebook&);
void drop_student(vector<student>&);
int find_student_index(vector<student>&);
void enter_class_grades(vector<student>&, gradebook&);
void enter_test_grades(vector<student>&, gradebook&);
void enter_project_grades(vector<student>&, gradebook&);
void enter_attendance_grades(vector<student>&, gradebook&);
void recalculate_grades(vector<student>&, gradebook&);
void print_class_report(vector<student>&, gradebook&);
char compute_letter_grade(float);
void view_student_record(vector<student>&, gradebook&);
void print_student_record(student&, gradebook&);
void save(string, vector<student>&, gradebook&);

//-----------------------------------------------------------------------------------------------------------
//											main
//-----------------------------------------------------------------------------------------------------------
// the main function of the program -- prints logo, reads text file, then allows the user to begin editing
int main(){

  print_logo(); // print the programs logo

  // read in the filename
  string filename;
  cout << "Enter grade file: ";
  cin >> filename;

  // declare gradebook and students structs
  gradebook gb;
  vector<student> students;

  // open and read files
  ifstream grade_file;
  grade_file.open(filename);
  read_gradebook_headers(gb, grade_file);
  read_students(students, gb, grade_file);
  grade_file.close(); // don't forget to close the file

  // begin editing file
  char user_input;
  while (user_input != 'Q'){ // loop until the user decides to quit
    print_menu();
    cin >> user_input;
    switch(user_input){ // switch statement that calls the functions based on user input
      case 'A': add_student(students, gb); break;
      case 'D': drop_student(students); break;
      case 'E': enter_class_grades(students, gb); break;
      case 'P': print_class_report(students, gb); break;
      case 'V': view_student_record(students, gb); break;
      case 'S': save(filename, students, gb); break;
      case 'X': user_input = 'Q'; save(filename, students, gb); break;
      default: cout << "Input not recognized"; break;
    }
  }

}

//-----------------------------------------------------------------------------------------------------------
//											print_logo
//-----------------------------------------------------------------------------------------------------------
// Print the programs logo
void print_logo(){
  cout << "+---------------------------+" << endl;
  cout << "|      GRADEBOOK DELUX      |" << endl;
  cout << "|       Kendall Weihe       |" << endl;
  cout << "+---------------------------+" << endl;
}

//-----------------------------------------------------------------------------------------------------------
//											print_menu
//-----------------------------------------------------------------------------------------------------------
// Print the main menu of the program
void print_menu(){
  // the menu options are defined in the specifications
  cout << "A – Add student" << endl;
  cout << "D – Drop student" << endl;
  cout << "E – Enter class grades" << endl;
  cout << "P – Print class report" << endl;
  cout << "V – View student record" << endl;
  cout << "S - Save" << endl;
  cout << "X – Exit" << endl;
}

//-----------------------------------------------------------------------------------------------------------
//											read_gradebook_headers
//-----------------------------------------------------------------------------------------------------------
// Read the first line (the headers) of the input test file
void read_gradebook_headers(gradebook &gb, ifstream &file){
  // read in headers -- defined in the specs
  file >> gb.class_name;
  file >> gb.num_students;
  file >> gb.num_tests;
  file >> gb.num_projects;
  file >> gb.num_days;

  double possible_points;
  for (int i = 0; i < gb.num_projects; i++){ // loop over the possible project points
    file >> possible_points;
    gb.possible_project_points.push_back(possible_points);
  }
}

//-----------------------------------------------------------------------------------------------------------
//										  read_students
//-----------------------------------------------------------------------------------------------------------
// Read the student information from the text file -- make use of header info from read_gradebook_headers
void read_students(vector<student> &students, gradebook &gb, ifstream &file){
  for (int i = 0; i < gb.num_students; i++){ // loop over all the students in the text file
    student new_student;
    // begin reading student info
    file >> new_student.fname;
    file >> new_student.lname;
    file >> new_student.student_id;
    file >> new_student.num_days_attended;

    // read test scores
    double temp_score, test_scores = 0.0;
    if (gb.num_tests == 0){
      test_scores = 1;
    }
    else {
      for (int j = 0; j < gb.num_tests; j++){
        file >> temp_score;
        test_scores += (temp_score / 100);
        new_student.test_scores.push_back(temp_score);
      }
      test_scores = test_scores / gb.num_tests;
    }

    // read the project scores
    double project_scores = 0.0;
    if (gb.num_projects == 0){
      project_scores = 1;
    }
    else {
      for (int j = 0; j < gb.num_projects; j++){
        file >> temp_score;
        project_scores += (temp_score / gb.possible_project_points[j]);
        new_student.project_scores.push_back(temp_score);
      }
      project_scores = project_scores / gb.num_projects;
    }

    // calculate attendance and grade averages
    double overall_grade, attendance_score;
    attendance_score = new_student.num_days_attended / gb.num_days;
    new_student.test_average = test_scores;
    new_student.project_average = project_scores;
    new_student.attendance_average = attendance_score;
    overall_grade = (0.5 * test_scores) + (0.4 * project_scores) + (0.1 * attendance_score); // weighted averages
    new_student.grade_percentage = overall_grade;
    new_student.letter_grade = compute_letter_grade(overall_grade * 100); // compute the letter grade
    students.push_back(new_student); // add the student to the students vector
  }
}

//-----------------------------------------------------------------------------------------------------------
//											compute_letter_grade
//-----------------------------------------------------------------------------------------------------------
// returns the letter grade given a grade percentage
char compute_letter_grade(float p) { // function taken from the program provided on the website
	if (p >= 90) return 'A';
	if (p >= 80) return 'B';
	if (p >= 70) return 'C';
	if (p >= 80) return 'D';
	return 'E';
}

//-----------------------------------------------------------------------------------------------------------
//											add_student
//-----------------------------------------------------------------------------------------------------------
// add a new student to the gradebook
void add_student(vector<student> &students, gradebook &gb){
  student new_student; // declare a new student

  // begin reading student information
  cout << "Enter First Name and Last Name: ";
  cin >> new_student.fname >> new_student.lname;
  cout << "Enter Student ID: ";
  cin >> new_student.student_id;
  cout << "Enter number of lecture days attended: ";
  cin >> new_student.num_days_attended;

  // read test scores
  double temp_score, test_scores = 0;
  if (gb.num_tests == 0){
    test_scores = 1;
  }
  else {
    for (int i = 0; i < gb.num_tests; i++){
      cout << "Enter the score for test #" << i+1 << ": ";
      cin >> temp_score;
      test_scores += temp_score / 100;
      new_student.test_scores.push_back(temp_score);
    }
    test_scores = test_scores / gb.num_tests;
  }

  // read project scores
  double project_scores = 0;
  if (gb.num_projects == 0){
    project_scores = 1;
  }
  else {
    for (int i = 0; i < gb.num_projects; i++){
      cout << "Enter the score for project #" << i+1 << ": ";
      cin >> temp_score;
      project_scores += temp_score / gb.possible_project_points[i];
      new_student.project_scores.push_back(temp_score);
    }
    project_scores = project_scores / gb.num_projects;
  }

  // calculate averages
  double overall_grade, attendance_score;
  new_student.test_average = test_scores;
  new_student.project_average = project_scores;
  new_student.attendance_average = new_student.num_days_attended / gb.num_days;
  overall_grade = (0.5 * new_student.test_average) + (0.4 * new_student.project_average) + (0.1 * new_student.attendance_average);
  new_student.grade_percentage = overall_grade;
  new_student.letter_grade = compute_letter_grade(overall_grade * 100); // compute letter grade
  students.push_back(new_student);
  gb.num_students = gb.num_students+1;
}

//-----------------------------------------------------------------------------------------------------------
//											drop_student
//-----------------------------------------------------------------------------------------------------------
// drop a student from the gradebook
void drop_student(vector<student> &students){
  int student_index;
  student_index = find_student_index(students); // find the student index
  if (student_index > -1){ // check if the student exists
    students.erase(students.begin()+student_index); // erase the student from the students vector
  }
  else {
    cout << "The student was not found" << endl;
  }
}

//-----------------------------------------------------------------------------------------------------------
//											find_student_index
//-----------------------------------------------------------------------------------------------------------
// search for a student and return the index
int find_student_index(vector<student> &students){
  string fname, lname;
  cout << "Enter the students first and last name: ";
  cin >> fname >> lname;
  for (int i = 0; i < students.size(); i++){ // loop over all students
    if (students[i].fname == fname && students[i].lname == lname){ // case where the student is found
      return i;
    }
  }
  return -1; // case where the student was not found
}

//-----------------------------------------------------------------------------------------------------------
//											enter_class_grades
//-----------------------------------------------------------------------------------------------------------
// enter new class grades -- could be tests, projects, or attendance
void enter_class_grades(vector<student> &students, gradebook &gb){
  cout << "Enter Test, Project, or Attendance data? (T/P/A): ";
  char user_input;
  cin >> user_input; // read user option
  switch (user_input) { // call function based on what user inputs
    case 'T': enter_test_grades(students, gb); break;
    case 'P': enter_project_grades(students, gb); break;
    case 'A': enter_attendance_grades(students, gb); break;
    default: cout << "Input not recognized\n"; break;
  }
}

//-----------------------------------------------------------------------------------------------------------
//											enter_test_grades
//-----------------------------------------------------------------------------------------------------------
// enter a new test grades -- called by enter_class_grades
void enter_test_grades(vector<student> &students, gradebook &gb){
  cout << "Enter scores for Test " << gb.num_tests+1 << endl;
  gb.num_tests = gb.num_tests+1; // increment the number of tests
  double temp_test_grade;
  for (int i = 0; i < students.size(); i++){ // loop over all students
    cout << students[i].lname << ", " << students[i].fname << "     ";
    cin >> temp_test_grade; // read in new test scores for each individual student
    students[i].test_scores.push_back(temp_test_grade); // add the new test score
  }
  cout << endl;
  recalculate_grades(students, gb); // recalculate the new overall grade
}

//-----------------------------------------------------------------------------------------------------------
//											enter_project_grades
//-----------------------------------------------------------------------------------------------------------
// enter a new project grades -- called by enter_class_grades
void enter_project_grades(vector<student> &students, gradebook &gb){
  gb.num_projects = gb.num_projects+1; // increment the number of projects
  cout << "Enter possible number of points for Project " << gb.num_projects+1 << ": ";
  double possible_project_points;
  cin >> possible_project_points; // read in the possible number of points for the new project
  gb.possible_project_points.push_back(possible_project_points); // add the possible number of points to the gradebook
  double temp_project_score;
  for (int i = 0; i < students.size(); i++){ // iterate over all the students
    cout << students[i].lname << ", " << students[i].fname << "     ";
    cin >> temp_project_score; // read in each individual students test score
    students[i].project_scores.push_back(temp_project_score); // add the new test score to the student record
  }
  cout << endl;
  recalculate_grades(students, gb); // recalculate the new grades
}

//-----------------------------------------------------------------------------------------------------------
//											enter_attendance_grades
//-----------------------------------------------------------------------------------------------------------
// enter a new attendance for class and each student
void enter_attendance_grades(vector<student> &students, gradebook &gb){
  cout << "Enter 0=Absent or 1=Present for each student:\n";
  gb.num_days = gb.num_days+1; // increment the number of lecture days
  int temp_attendance_score;
  for (int i = 0; i < students.size(); i++){ // iterate over all students
    cout << students[i].lname << ", " << students[i].fname << "     ";
    cin >> temp_attendance_score; // read in each individual attendance -- whether or not they attended the new day
    students[i].num_days_attended = students[i].num_days_attended + temp_attendance_score;
  }
  cout << endl;
  recalculate_grades(students, gb); // recalculate the new grade
}

//-----------------------------------------------------------------------------------------------------------
//											recalculate_grades
//-----------------------------------------------------------------------------------------------------------
// recalculate_grades individual student grades adter entering a new grade (enter_class_grades)
void recalculate_grades(vector<student> &students, gradebook &gb){
  for (int i = 0; i < students.size(); i++){ // iterate over all students
    // calculate the new test scores
    double temp_score = 0;
    for (int j = 0; j < gb.num_tests; j++){
      temp_score += students[i].test_scores[j] / 100;
    }
    students[i].test_average = temp_score / gb.num_tests;

    // calculate the new project scores
    temp_score = 0;
    for (int j = 0; j < gb.num_projects; j++){
      temp_score += students[i].project_scores[j] / gb.possible_project_points[j];
    }

    // calculate the new grade averages
    students[i].project_average = temp_score / gb.num_projects;
    students[i].attendance_average = students[i].num_days_attended / gb.num_days;
    students[i].grade_percentage = (0.5 * students[i].test_average) + (0.4 * students[i].project_average) + (0.1 * students[i].attendance_average);
    students[i].letter_grade = compute_letter_grade(students[i].grade_percentage * 100);
  }
}

//-----------------------------------------------------------------------------------------------------------
//											print_class_report
//-----------------------------------------------------------------------------------------------------------
// print the entire class report
void print_class_report(vector<student> &students, gradebook &gb){
  // print the header info
  cout << "-----------------------------------------------------------------------------" << endl;
  cout << gb.class_name << "    " << gb.num_students << " students    " << gb.num_tests << " tests    " << gb.num_days << " lectures    " << gb.num_projects << " projects (";
  for (int i = 0; i < gb.possible_project_points.size(); i++){
    if (i == gb.possible_project_points.size()-1){
      cout << gb.possible_project_points[i] << ")";
    }
    else {
      cout << gb.possible_project_points[i] << " ";
    }
  }
  cout << endl;
  cout << "-----------------------------------------------------------------------------" << endl;
  cout << "NAME               LG  PERC  TAvg  PAvg  AAvg   Att     ";
  for (int i = 0; i < gb.num_tests; i++){ // print each test column header
    cout << "T" << i << "    ";
  }
  for (int i = 0; i < gb.num_projects; i++){ // print each project column header
    cout << "P" << i << "    ";
  }
  cout << endl;

  // print each student record
  for (int i = 0; i < students.size(); i++) {
    cout << setw(20) << left << (students[i].lname + ", " + students[i].fname)
      << setw(3) << students[i].letter_grade
      << fixed << setprecision(1) << right
      << setw(4) << setprecision(1) <<  students[i].grade_percentage * 100
      << setw(6) << setprecision(1) << students[i].test_average * 100
      << setw(6) << setprecision(1) << students[i].project_average * 100
      << setw(6) << setprecision(1) << students[i].attendance_average * 100
      << setw(6) << students[i].num_days_attended << " ";

    // print tests and projects
    for (int j = 0; j < gb.num_tests; j++)
      cout << setw(6) << students[i].test_scores[j];
    for (int j = 0; j < gb.num_projects; j++)
      cout << setw(6) << students[i].project_scores[j];
    cout << endl;
  }
  cout << endl;
}

//-----------------------------------------------------------------------------------------------------------
//											view_student_record
//-----------------------------------------------------------------------------------------------------------
// view individual student record -- finds student then calls print_student_record
void view_student_record(vector<student> &students, gradebook &gb){
  int student_index;
  student_index = find_student_index(students); // find the student in the students vector
  if (student_index > -1){ // check if the student exists
    print_student_record(students[student_index], gb); // call function to print the students record
  }
  else {
    cout << "Student not found\n"; // case where the student was not found
  }
}

//-----------------------------------------------------------------------------------------------------------
//											print_student_record
//-----------------------------------------------------------------------------------------------------------
// print individual student record
void print_student_record(student &s, gradebook &gb){
  cout << fixed << setprecision(1);
  cout << "Student:     " << s.fname << " " << s.lname << " (" << s.student_id << ")" << endl; // print the student info
  cout << "Attendance:  Average=" << s.attendance_average << "  " << s.num_days_attended << "/" << gb.num_days << endl; // print the students attendance record
  cout << "Tests:       Average=" << s.test_average; // print the students test average
  for (int i = 0; i < gb.num_tests; i++) // print each test score
    cout << "  T" << (i + 1) << "=" << s.test_scores[i];
  cout << "\nProjects:    Average=" << s.project_average; // print the project average
  for (int i = 0; i < gb.num_projects; i++) // print each project score -- with the possible number of points
    cout << "  P" << (i + 1) << "=" << s.project_scores[i] << "/" << gb.possible_project_points[i];
  cout << "\nOverall:     Percent=" << s.grade_percentage << "  Grade=" << s.letter_grade << endl << endl;
}

//-----------------------------------------------------------------------------------------------------------
//											save
//-----------------------------------------------------------------------------------------------------------
// save the document back to the same text file
void save(string filename, vector<student> &students, gradebook &gb){
  // open the file
  ofstream grade_file;
  grade_file.open(filename);

  // begin writing the file -- first header info
  grade_file << gb.class_name << " " << gb.num_students << " " << gb.num_tests << " " << gb.num_projects << " " << gb.num_days << endl;
  for (int i = 0; i < gb.num_projects; i++){ // write the number of possible project points
    grade_file << gb.possible_project_points[i] << " ";
  }
  grade_file << endl;

  for (int i = 0; i < students.size(); i++){ // begin writing each student
    grade_file << students[i].fname << " " << students[i].lname << " " << students[i].student_id << " " << students[i].num_days_attended << endl;
    for (int j = 0; j < gb.num_tests; j++){ // write the students test scores
      grade_file << students[i].test_scores[j] << " ";
    }
    grade_file << endl;
    for (int j = 0; j < gb.num_projects; j++){ // write the projects test scores
      grade_file << students[i].project_scores[j] << " ";
    }
    grade_file << endl;
  }
  grade_file.close();
}
