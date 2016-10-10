#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// function declarations
void AddClassNumbers(int &num_tests, int &num_projects, int &num_attendance);
int AddNumber(string prompt, int lower_bound, int upper_bound);
double GetTestAverage(int num_tests);
double GetProjectAverage(int num_projects);
double GetAttendanceScore(int num_attendance);
double CalcPercentage(double test_average, double project_average, double attendance_average);
char GetLetterGrade(double overall_score);
void PrintStudent(string fname, string lname, double test_average, double project_average, double attendance_average, double overall_score, char letter_grade);

int main(){

  int num_tests, num_projects, num_attendance;
  AddClassNumbers(num_tests, num_projects, num_attendance);

  double class_sum, highest_average = 0.0, lowest_average = 100.0;
  int num_students = 1;
  string fname, lname;
  cout << "Enter the students name: ";
  cin >> fname >> lname;
  while (fname != "exit" && lname != "now"){

    double test_average, project_average, attendance_average, overall_score;
    char letter_grade;
    test_average = GetTestAverage(num_tests);
    project_average = GetProjectAverage(num_projects);
    attendance_average = GetAttendanceScore(num_attendance) * 100;
    overall_score = CalcPercentage(test_average, project_average, attendance_average);
    letter_grade = GetLetterGrade(overall_score);
    PrintStudent(fname, lname, test_average, project_average, attendance_average, overall_score, letter_grade);

    if (overall_score > highest_average){
      highest_average = overall_score;
    }
    else if (overall_score < lowest_average){
      lowest_average = overall_score;
    }

    num_students++;
    cout << "Enter the students name: ";
    cin >> fname >> lname;
  }

  double class_average = class_sum / num_students;
  cout << "The class average:         " << fixed << setprecision(1) << class_average << endl;
  cout << "Highest final score:       " << fixed << setprecision(1) << highest_average << endl;
  cout << "Lowest final score:        " << fixed << setprecision(1) << lowest_average << endl;

  // system("pause");
  return 0;

}

void AddClassNumbers(int &num_tests, int &num_projects, int &num_attendance){

  string num_tests_str = "Enter the number of tests: ", num_projects_str = "Enter the number of projects: ", num_attendance_str = "Enter the total number of days: ";

  num_tests = AddNumber(num_tests_str, 1, 50);
  num_projects = AddNumber(num_projects_str, 1, 50);
  num_attendance = AddNumber(num_attendance_str, 1, 50);

}

int AddNumber(string prompt, int lower_bound, int upper_bound){

  cout << prompt;
  int number;
  cin >> number;
  while (number < lower_bound || number > upper_bound){
    cout << "Invalid input\n";
    cout << prompt;
    cin >> number;
  }

  return number;

}

double GetTestAverage(int num_tests){

  double test_sum = 0;
  for (int i = 0; i < num_tests; i++){
    test_sum += AddNumber("Enter Test " + to_string(i+1) + "     ", 0, 100);
  }

  return test_sum / num_tests;

}

double GetProjectAverage(int num_projects){

  double project_sum = 0;
  for (int i = 0; i < num_projects; i++){
    project_sum +=  AddNumber("Enter Project " + to_string(i+1) + "     ", 0, 100);
  }

  return project_sum / num_projects;

}

double GetAttendanceScore(int num_attendance){

  double days_attended = AddNumber("Enter Days Attended: ", 0, num_attendance);
  return days_attended / num_attendance;

}

double CalcPercentage(double test_average, double project_average, double attendance_average){

  return (0.4 * test_average) + (0.5 * project_average) + (0.1 * attendance_average);

}

char GetLetterGrade(double overall_score){

  if (overall_score < 100 && overall_score >= 90)
    return 'A';
  else if (overall_score < 90 && overall_score >= 80)
    return 'B';
  else if (overall_score < 80 && overall_score >= 70)
    return 'C';
  else if (overall_score < 70 && overall_score >= 60)
    return 'D';
  else if (overall_score < 60)
    return 'F';
  else {
    cout << "Your overall score was over the limit, something went wrong\n";
    return -1;
  }

}

void PrintStudent(string fname, string lname, double test_average, double project_average, double attendance_average, double overall_score, char letter_grade){

  cout << "\n\n";
  cout << "Name:                  " << fname << " " << lname << endl;
  cout << "Test average:          " << fixed << setprecision(1) << test_average << " %" << endl;
  cout << "Project average:       " << fixed << setprecision(1) << project_average << " %" << endl;
  cout << "Attendance:            " << fixed << setprecision(1) << attendance_average << " %" << endl;
  cout << "Overall Average:       " << fixed << setprecision(1) << overall_score << " %" << endl;
  cout << "Grade:                 " << letter_grade << endl;
  cout << "\n\n";

}
