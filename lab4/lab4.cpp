#include <iostream>
#include <ctype.h>

using namespace std;

int main(){

  // TODO
    // loop until user enters x or f
    //   print input options
    //   input user option
    //   switch statement
    //     if x
    //       exit program
    //     else if f
    //       subtotal
    //       tax
    //       total
    //       input change tendered
    //       compute change
    //       system pause
    //     else
    //       add to subtotal
            // print current subtotal

  bool user_quit = false;
  double subtotal = 0;
  while (!user_quit){

    // print input options
    cout << "H - Hot Dog            $2.50" << endl;
    cout << "D - Deluxe Hot Dog     $3.50" << endl;
    cout << "S - Small Drink        $1.50" << endl;
    cout << "L - Large Drink        $2.25" << endl;
    cout << "F - Finish Order" << endl;
    cout << "X - Exit Program" << endl;
    cout << "Enter Option ==> " << "\n\n";

    char input_option;
    cin >> input_option;

    if (islower(input_option)){
      input_option = toupper(input_option);
      // cout << "you entered a lower case";
    }

    switch (input_option){
      case 'H':
        subtotal += 2.5;
        break;
      case 'D':
        subtotal += 3.5;
        break;
      case 'S':
        subtotal += 1.5;
        break;
      case 'L':
        subtotal += 2.25;
        break;
      case 'F':
        // user completed order
        double tax, total;
        tax = subtotal * 0.06;
        total = subtotal + tax;
        cout << "Subtotal =         " << subtotal << endl;
        cout << "Tax =              " << tax << endl;
        cout << "Total =            " << total << endl;
        double cash_tendered;
        cout << "Cash tendered:     ";
        cin >> cash_tendered;
        double change;
        change = cash_tendered - total;
        cout << "Change =           " << change << "\n\n";
        // system pause
        subtotal = 0;
        break;
      case 'X':
        // user exits program
        user_quit = true;
        // system pause
        break;
      default:
        cout << "Invalid input... try again" << endl;
    }

    // system pause

  }

}
