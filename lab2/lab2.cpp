/*
  Author: Kendall Weihe
  Assignment: CS215 Fall 2016 Lab2
  Requirements:
    -- Input 8-bit binary number
    -- Check if 8-bits
      -- If not 8-bits output error message and return 1
    -- Check if binary number
      -- If not binary number output error message and return 1
    -- Convert to decimal number and print to terminal
  Psuedocode:
    -- Input into string
    -- Compute string length from <string> library str.size()
    -- Check for string length -- should be 8
    -- Loop over each digit from least-significant-bit to most-significant-bit
    -- Check if digit is not binary -- if not output error and return 1
    -- Multiply digit by 2^i -- the binary place value and add to decimal_value
    -- Output converted value and return 0 
*/

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int main(){

  string binary_input;
  cout << "Enter an 8-bit binary number... ";
  cin >> binary_input;

  int string_length = binary_input.size();

  // uncomment below line to verify input length
  // cout << "The length of your input is... " << string_length << endl;

  if (string_length != 8){
    cout << "That is not an 8-digit value!\n\n";
    return 1;
  }
  else {

      int decimal_value = 0, binary_digit;
      for (int i = string_length-1; i > -1; i--){
        binary_digit = stoi(binary_input.substr(i,1));
        if (binary_digit != 0 && binary_digit != 1){
          cout << "This is not a binary number!\n\n";
          return 1;
        }
        decimal_value += pow(2,string_length-1-i) * binary_digit;
        // uncomment the below lines to verify digit value and the decimal value as it is computed
        // cout << "Digit place [" << string_length-1-i << "] = " << binary_digit << endl;
        // cout << "Decimal value = " << decimal_value << endl;
      }

      cout << "Converted to decimal: " << decimal_value << "\n" << endl;
      return 0;

  }


}
