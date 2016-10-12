/*
  Author: Kendall Weihe
  Assignment: CS215 Fall 2016 Project 1
  Purpose: Program a gradebook software -- allows user to enter student grades, and then display averages and final grades
  Psuedocode:
    - print logo
    - call AddClassNumbers()
    - loop until user enters "exit now"
      - call GetTestAverage()
        - which calls AskNumber() x-times
      - call GetProjectAverage
        - which calls AskNumber() x-times
      - call GetAttendanceScore()
        - which calls AskNumber() x-times
      - calculate grade percetages
      - print student results
    - print the statistics for the entire class
      - overall average
      - highest score
      - lowest score
*/

// compiler directives
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// function declarations
void PrintLogo();
int AskNumber(string prompt, int lower_bound, int upper_bound);
void AddClassNumbers(int &num_tests, int &num_projects, int &num_attendance);
double GetTestAverage(int num_tests);
double GetProjectAverage(int num_projects);
double GetAttendanceScore(int num_attendance);
double CalcPercentage(double test_average, double project_average, double attendance_average);
char GetLetterGrade(double overall_score);
void PrintStudent(string fname, string lname, double test_average, double project_average, double attendance_average, double overall_score, char letter_grade);

/*
  function: main()
  purpose: execute psuedocode outlines above
*/
int main(){

  PrintLogo(); // print the program logo

  int num_tests, num_projects, num_attendance;
  AddClassNumbers(num_tests, num_projects, num_attendance); // add class numbers -- pass values by reference

  double class_sum = 0, highest_average = 0.0, lowest_average = 100.0;
  int num_students = 0;
  string fname, lname;
  cout << "Enter the students name: ";
  cin >> fname >> lname; // read in first student name
  while (fname != "exit" && lname != "now"){ // loop until user enters "exit now"

    double test_average, project_average, attendance_average, overall_score;
    char letter_grade;

    // get all the averages
    test_average = GetTestAverage(num_tests);
    project_average = GetProjectAverage(num_projects);
    attendance_average = GetAttendanceScore(num_attendance) * 100;

    // calculate overall scores and letter grade
    overall_score = CalcPercentage(test_average, project_average, attendance_average);
    letter_grade = GetLetterGrade(overall_score);

    // print student results
    PrintStudent(fname, lname, test_average, project_average, attendance_average, overall_score, letter_grade);

    // king-of-the-hill --> keep track of highest and lowest overall scores
    if (overall_score > highest_average){
      highest_average = overall_score;
    }
    else if (overall_score < lowest_average){
      lowest_average = overall_score;
    }

    class_sum += overall_score; // class_sum used to calculate the class average
    num_students++; // num_students used to calculate the class average
    cout << "Enter the students name: ";
    cin >> fname >> lname; // read in next student name
  }

  double class_average = class_sum / num_students; // calculate class average

  // print class results
  cout << "The class average:         " << fixed << setprecision(1) << class_average << endl;
  cout << "Highest final score:       " << fixed << setprecision(1) << highest_average << endl;
  cout << "Lowest final score:        " << fixed << setprecision(1) << lowest_average << endl;

  // system("pause");
  return 0;

}

/*
  function: PrintLogo()
  purpose: print the program logo
  notes: void function -- no return value
*/
void PrintLogo(){
  cout << "-------------------------------------------\n";
  cout << "|                                         |\n";
  cout << "|     Welcome to the Gradebook Program!   |\n";
  cout << "|       Developed by: Kendall Weihe       |\n";
  cout << "|                                         |\n";
  cout << "-------------------------------------------\n";
}

/*
  function: AskNumber()
  purpose: ask the user to input a numeric value and check that it is within the defined range
  note: return value is double so that test scores can have decimal places
*/
int AskNumber(string prompt, int lower_bound, int upper_bound){

  cout << prompt; // print prompt parameter
  double number;
  cin >> number;
  while (number < lower_bound || number > upper_bound){ // loop until the user enters a valid value
    cout << "Invalid input. Enter a number between " << lower_bound << " and " << upper_bound << "\n"; // print error statement
    cout << prompt;
    cin >> number; // re-read in value
  }

  return number;

}

/*
  function: AddClassNumbers()
  purpose: add number of tests, projects, and days of attendance
*/
void AddClassNumbers(int &num_tests, int &num_projects, int &num_attendance){

  // prompt statements
  string num_tests_str = "Enter the number of tests: ", num_projects_str = "Enter the number of projects: ", num_attendance_str = "Enter the total number of days: ";

  // values
  num_tests = AskNumber(num_tests_str, 1, 50);
  num_projects = AskNumber(num_projects_str, 1, 50);
  num_attendance = AskNumber(num_attendance_str, 1, 50);

}

/*
  function: GetTestAverage()
  purpose: compute the average test score
*/
double GetTestAverage(int num_tests){

  double test_sum = 0;
  for (int i = 0; i < num_tests; i++){ // loop number-of-tests times
    test_sum += AskNumber("Enter Test " + to_string(i+1) + "     ", 0, 100); // make sure test scores are within a valid range [0,100]
  }

  return test_sum / num_tests; // return average

}

/*
  function: GetProjectAverage()
  purpose: compute the average project grade
*/
double GetProjectAverage(int num_projects){

  double project_sum = 0;
  for (int i = 0; i < num_projects; i++){ // loop number-of-projects times
    project_sum +=  AskNumber("Enter Project " + to_string(i+1) + "     ", 0, 100); // invoke AskNumber() to get value and add it to overall score sum
  }

  return project_sum / num_projects; // return average

}

/*
  function: GetAttendanceScore()
  purpose: compute the students attendance score
*/
double GetAttendanceScore(int num_attendance){

  double days_attended = AskNumber("Enter Days Attended: ", 0, num_attendance); // get number of days attended
  return days_attended / num_attendance; // return score -- note: this is a value between 0-1 so it will have to be multiplied by 100 in main()

}

/*
  function: CalcPercentage()
  prupose: compute overall grade percentage for student
*/
double CalcPercentage(double test_average, double project_average, double attendance_average){

  return (0.4 * test_average) + (0.5 * project_average) + (0.1 * attendance_average); // include weight values

}

/*
  function: GetLetterGrade()
  purpose: return the letter grade based on students overall grade percentage
*/
char GetLetterGrade(double overall_score){

  if (overall_score < 100 && overall_score >= 90) // [90,100] == A
    return 'A';
  else if (overall_score < 90 && overall_score >= 80)
    return 'B';
  else if (overall_score < 80 && overall_score >= 70)
    return 'C';
  else if (overall_score < 70 && overall_score >= 60)
    return 'D';
  else if (overall_score < 60)
    return 'F';
  else { // check for invalid grade number -- error testing
    cout << "Your overall score was over the limit, something went wrong\n";
    return -1;
  }

}

/*
  function: PrintStudent()
  purpose: print all information collected and computed about students grades
*/
void PrintStudent(string fname, string lname, double test_average, double project_average, double attendance_average, double overall_score, char letter_grade){
  cout << "\n\n";
  cout << "Name:                  " << fname << " " << lname << endl;
  cout << "Test average:          " << fixed << setprecision(1) << test_average << " %" << endl; // set the precision to one decomal place
  cout << "Project average:       " << fixed << setprecision(1) << project_average << " %" << endl;
  cout << "Attendance:            " << fixed << setprecision(1) << attendance_average << " %" << endl;
  cout << "Overall Average:       " << fixed << setprecision(1) << overall_score << " %" << endl;
  cout << "Grade:                 " << letter_grade << endl;
  cout << "\n\n";
}
