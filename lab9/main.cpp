/*
  Author: Kendall Weihe
  Assignment: CS215 Fall 2016 lab 9
  Description:
    - read in a text file filled with baseball players, their number of hits, and their total number of at bats
    - output a file with their name and batting average
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

// function prototypes
void print_logo();
void read_player_stats(ifstream&, vector<string>&, vector<double>&, vector<double>&);
void calculate_batting_averages(ofstream&, vector<string>&, vector<double>&, vector<double>&);

// --------------------------------------------------------------------------------------------
//         main()
// --------------------------------------------------------------------------------------------
// the main flow of control of the program -- invoke functions to complete program description
int main(){

  print_logo(); // print the program logo

  // read the input and output file names
  string input_filename, output_filename;
  cout << "Enter the name of the input file: ";
  cin >> input_filename;

  // vectors to hold player information
  vector<string> player_names;
  vector<double> num_hits;
  vector<double> num_at_bats;

  // input file
  ifstream in_file;
  in_file.open(input_filename); // open
  if (!in_file.is_open()){
    cout << "Could not open the input file\n";
    return 0;
  }
  read_player_stats(in_file, player_names, num_hits, num_at_bats); // read the file data
  in_file.close(); // close

  // output file
  cout << "Enter the name of the output file: ";
  cin >> output_filename;
  ofstream out_file;
  out_file.open(output_filename); // open file
  if (!out_file.is_open()){
    cout << "Could not open the output file\n";
    return 0;
  }
  calculate_batting_averages(out_file, player_names, num_hits, num_at_bats); // calculate batting average and output to file
  out_file.close(); // close the file

  // system("pause");
  return 0;

}

// --------------------------------------------------------------------------------------------
        // print_logo()
// --------------------------------------------------------------------------------------------
// print the program logo
void print_logo(){
  cout << "+----------------------------+" << endl;
  cout << "| Batting average calculator |" << endl;
  cout << "|      Kendall Weihe         |" << endl;
  cout << "+----------------------------+" << endl;
}

// --------------------------------------------------------------------------------------------
        // read_player_stats()
// --------------------------------------------------------------------------------------------
// read in the player statistics and place data in vectors passed by reference
void read_player_stats(ifstream &in_file, vector<string> &player_names, vector<double> &num_hits, vector<double> &num_at_bats){
    int num_players;
    in_file >> num_players; // read in the number of players -- placed on first line

    // temporary variables to read into from the input stream
    string temp_name;
    double temp_num_hits, temp_num_at_bats;
    for (int i = 0; i < num_players; i++){ // iterate over all the players
      in_file >> temp_name; // read in data
      player_names.push_back(temp_name); // append to vector
      in_file >> temp_num_at_bats;
      num_at_bats.push_back(temp_num_at_bats);
      in_file >> temp_num_hits;
      num_hits.push_back(temp_num_hits);
    }
}

// --------------------------------------------------------------------------------------------
        // calculate_batting_averages()
// --------------------------------------------------------------------------------------------
// calculate each players batting average and write it to output file
void calculate_batting_averages(ofstream &out_file, vector<string> &player_names, vector<double> &num_hits, vector<double> &num_at_bats){
  double batting_average;
  for (int i = 0; i < player_names.size(); i++){ // iterate over entire team
    if (num_at_bats[i] == 0){
        out_file << player_names[i] << " 0\n"; // write to file
    }
    else {
      batting_average = num_hits[i] / num_at_bats[i]; // compute batting average
      out_file << player_names[i] << " " << batting_average << endl; // write to file
    }
  }
  out_file << "EOF 0.0"; // write the Sentinel line at the end of the file
}
