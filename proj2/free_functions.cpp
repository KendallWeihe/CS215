/*
** Project 2: free functions. Feel free to modify, use or not use as you wish.
**
** Note 2 structions are used:
** - student: contains data on one student, including lists of project and test scores
** - courseData: contains data on the entire course, including a list of project possible scores (int array)
*/


//-----------------------------------------------------------------------------------------------------------
//											printClass
//-----------------------------------------------------------------------------------------------------------
// Given Course Data and a list of students, print a report of the entire class.
void printClass(courseData & c, student stud[]) {
	int i, j, ndxTopStudent;

	// print report "header" lines
	cout << "------------------------------------------------------------------------------\n";
	cout << c.courseName << "   " << c.numStudents << " students   " << c.numTests << " tests   "
		<< c.numLectures << " lectures   " << c.numProjects << " projects (";

	if (c.numProjects > 0)					// if there is at least one project
		cout << c.projPoss[0];				// print its points possible
	for (i = 1; i < c.numProjects; i++)		// for each project beginning with the second
		cout << ", " << c.projPoss[i];		// print a comma/space then the points possible
	cout << ")\n";							// close the parenthesis and end the line
	cout << "------------------------------------------------------------------------------\n";

	// print column header line
	cout << "NAME               LG  PERC  TAvg  PAvg  AAvg  Att  ";
	for (i = 0; i < c.numTests; i++)		// for each test, print a column header
		cout << "T" << (i + 1) << "  ";
	for (i = 0; i < c.numProjects; i++)		// for each project, print a column header
		cout << "P" << (i + 1) << "  ";
	cout << endl;							// end the column header line

	// print each student record
	for (int i = 0; i < c.numStudents; i++) {
		cout << setw(20) << left << (stud[i].lastName + ", " + stud[i].firstName)
			<< setw(3) << stud[i].letterGrade
			<< fixed << setprecision(1) << right
			<< setw(4) << stud[i].percentage
			<< setw(6) << stud[i].testAvg
			<< setw(6) << stud[i].projAvg
			<< setw(6) << stud[i].attAvg
			<< setw(4) << stud[i].numAttended << " ";

		// print tests and projects
		for (j = 0; j < c.numTests; j++)
			cout << setw(4) << stud[i].test[j];
		for (j = 0; j < c.numProjects; j++)
			cout << setw(4) << stud[i].proj[j];
		cout << endl;
	}
	cout << endl;

	// print class average and name of top student
	if (c.numStudents > 0) {
		ndxTopStudent = findTopStudent(c, stud);
		cout << "Class Average: " << getClassAvg(c, stud) << endl;
		cout << "Top Student:   " << stud[ndxTopStudent].lastName << ", " << c.stud[ndxTopStudent].firstName << endl << endl;
	}
} // printClass()

//-----------------------------------------------------------------------------------------------------------
//										printStudent
//-----------------------------------------------------------------------------------------------------------
void printStudent(student s, courseData & c) {
	int i;
	cout << fixed << setprecision(1);
	cout << "Student:     " << s.firstName << " " << s.lastName << " (" << s.id << ")" << endl;
	cout << "Attendance:  Average=" << s.attAvg << "  " << s.numAttended << "/" << c.numLectures << endl;
	cout << "Tests:       Average=" << s.testAvg;
	for (i = 0; i < c.numTests; i++)
		cout << "  T" << (i + 1) << "=" << s.test[i];
	cout << "\nProjects:    Average=" << s.projAvg;
	for (i = 0; i < c.numProjects; i++)
		cout << "  P" << (i + 1) << "=" << s.proj[i] << "/" << c.projPoss[i];
	cout << "\nOverall:     Percent=" << s.percentage << "  Grade=" << s.letterGrade << endl << endl;
} // printStudent()


//-----------------------------------------------------------------------------------------------------------
//										letterGrade
//-----------------------------------------------------------------------------------------------------------
// Given the overall percentage, return the letter grade based on the 10 point scale.
char letterGrade(float p) {
	if (p >= 90) return 'A';
	if (p >= 80) return 'B';
	if (p >= 70) return 'C';
	if (p >= 80) return 'D';
	return 'E';
} // letterGrade()

//-----------------------------------------------------------------------------------------------------------
//                                   askEnterChoice
//-----------------------------------------------------------------------------------------------------------
char askEnterChoice() {
	char choice = ' ';

	cout << "Enter Test, Project or Attendance scores? (T/P/A): ";
	cin >> choice;
	choice = toupper(choice);
	while (choice != 'T' && choice != 'P' && choice != 'A') {
		cout << "Invalid entry. Please enter T, P or A!\n";
		cout << "Enter Test, Project or Attendance scores? (T/P/A): ";
		cin >> choice;
		choice = toupper(choice);
	}
	return choice;
} // askEnterChoice()
