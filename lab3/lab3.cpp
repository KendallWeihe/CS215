#include <iostream>
#include <iomanip>

using namespace std;

int main(){

  cout << fixed;
  cout << setprecision(2);
  cout << "-------------------------------------------------------" << endl;
  cout << setw(40);
  cout << "Weekly Payroll Calculator\n";
  cout << "-------------------------------------------------------" << endl;

  cout << "Hourly or Salaried employee? <H/S>:   ";
  char type_of_employee;
  cin >> right >> type_of_employee;

  double salary, hourly_wage, num_hours, gross, federal_tax, state_tax, net_pay;
  int w2_witholding;
  if (type_of_employee == 'S' || type_of_employee == 's'){

    cout << "Enter annual salary:                  ";
    cin >> salary;

    cout << "Enter W2 witholding <0,1,2,3...>      ";
    cin >> w2_witholding;

    gross = salary / 52;

  }
  else {

    cout << "Enter hourly wage:                    ";
    cin >> hourly_wage;

    cout << "Enter hours worked:                   ";
    cin >> num_hours;

    cout << "Enter W2 witholding <0,1,2,3...>      ";
    cin >> w2_witholding;

    if (num_hours > 40){
      gross = (40 * hourly_wage) + ((num_hours - 40) * hourly_wage * 1.5);
    }
    else{
      gross = (40 * hourly_wage);
    }

  }

  if (w2_witholding <= 0){
    federal_tax = 0.25 * gross;
  }
  else if (w2_witholding == 1){
    federal_tax = 0.22 * gross;
  }
  else if (w2_witholding == 2){
    federal_tax = 0.2 * gross;
  }
  else {
    federal_tax = 0.18 * gross;
  }

  state_tax = 0.06 * gross;
  net_pay = gross - federal_tax - state_tax;

  cout << "-------------------------------------------------------" << endl;
  cout << setw(30);
  cout << "Pay Stub\n";
  cout << "-------------------------------------------------------" << endl;

  cout << "Gross:         $           ";
  cout.width(17);
  cout << gross << endl;
  cout << "Federal Tax:   $           ";
  cout.width(17);
  cout << federal_tax << endl;
  cout << "State Tax:     $           ";
  cout.width(17);
  cout << state_tax << endl;
  cout << "Net Pay:       $           ";
  cout.width(17);
  cout << net_pay << endl;
  cout << "-------------------------------------------------------" << endl;

}

// setw example
// #include <iostream>
// #include <iomanip>
// using namespace std;
//
// int main () {
//   cout << setw (10);
//   cout << 77 << endl;
//   return 0;
// }
