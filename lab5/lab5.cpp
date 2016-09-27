/*
  Author: Kendall Weihe
  CS215 Fall 2016, Dr. Kevin Joiner
  Assignment: Lab 5
  Purpose:
    - Learn how to invoke functions
    - Learn how to pass variables to functions by reference or by pointer
    - Learn function types
  Psuedocode:
    - Print program logo
    - Ask user to enter numerator and denominator
      - Denominator cannot be zero
    - Compute decimal value
    - Print decimal value
    - Print the fraction in the form "n/d"
*/

#include <iostream>

using namespace std;

void PrintLogo();
void AskFraction(double &numerator, double &denominator);
double DecimalValue(double numerator, double denominator);
void PrintFraction(double numerator, double denominator);

int main() {

  PrintLogo();
  double numerator, denominator;
  AskFraction(numerator, denominator);
  double decimal_value;
  decimal_value = DecimalValue(numerator, denominator);
  cout << "The decimal value is " << decimal_value << endl;
  PrintFraction(numerator, denominator);

  // system("pause");

}

void PrintLogo(){

  cout << "+-----------------------------+" << endl;
  cout << "|        FRACTION FUNCTION    |" << endl;
  cout << "|        Kendall Weihe        |" << endl;
  cout << "+-----------------------------+" << endl;

}

void AskFraction(double &numerator, double &denominator){

  cout << "Enter the numerator: ";
  cin >> numerator;
  while (1){
    cout << "Enter the denominator: ";
    cin >> denominator;
    if (denominator == 0){
      cout << "Cannot enter a denominator equal to zero, please try again" << endl;
    }
    else {
      break;
    }
  }

}

double DecimalValue(double numerator, double denominator){

  return numerator / denominator;

}

void PrintFraction(double numerator, double denominator){

  cout << "Fraction: " << numerator << "/" << denominator << endl;

}
