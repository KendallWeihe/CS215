// ----------------------------------------------------
//         Trajectory Calculator
// ----------------------------------------------------
// Author:   Kendall Weihe
// Course:   CS215 Fall 2016
// Date:     October 18th, 2016
//
// This program computes the trajectory of an object launched
// at 100m/s -- the user is able to define the angle


#include <iostream>
#include <math.h>
#include <iomanip>

using namespace std;

// function declarations
void InitMeasurements(double list[]);
int CalcTrajectory(double distances[], double heights[], double angle, double velocity);
void PrintTrajectory(double distances[], double heights[], int num_intervals);
double MaxMeasurement(double list[]);

const int MAX_NUM_ELEMENTS = 100;
const int NUM_INTERVALS = 15;

// -------------------------------------------------------
//      main()
// -------------------------------------------------------
// Arguments:
//   None
// Returns:
//   0 if successful
// -------------------------------------------------------
int main(){

  // read user input for degrees
  double degrees;
  cout << "Enter the angle in degrees <15-75>: ";
  cin >> degrees;

  // convert degrees to radians -- math functions
  double radians;
  radians = (degrees * M_PI) / 180;

  // initialize distances and heights arrays
  double distances[MAX_NUM_ELEMENTS], heights[MAX_NUM_ELEMENTS];
  InitMeasurements(distances);
  InitMeasurements(heights);

  double velocity = 100.0;
  int num_intervals;

  // calculate and print trajectory data
  num_intervals = CalcTrajectory(distances, heights, radians, velocity);
  PrintTrajectory(distances, heights, num_intervals);

  // system("pause");
  return 0;

}

// -------------------------------------------------------
//     InitMeasurements()
// -------------------------------------------------------
// Arguments:
//   - a list of doubles
// Returns:
//   - nothing -- list is passed by reference
// -------------------------------------------------------
void InitMeasurements(double list[]){

  for (int i = 0; i < MAX_NUM_ELEMENTS; i++){
    list[i] = 0.0;
  }

}

// -------------------------------------------------------
//     CalcTrajectory()
// -------------------------------------------------------
// Arguments:
//   - list of doubles for distances
//   - list of doubles for heights
//   - angle in radians
//   - velocity in m/s
// Returns:
//   - number of time intervals
// -------------------------------------------------------
int CalcTrajectory(double distances[], double heights[], double angle, double velocity){

  double t = 0;
  for (int i = 1; i < NUM_INTERVALS; i++){
    t++;
    distances[i] = velocity * cos(angle) + distances[i-1]; // compute distance
    heights[i] = velocity * sin(angle) - (9.80665 * pow(t,2) * 0.5) + heights[i-1]; // compute height
    if (heights[i] < 0){ // if the height has reached the ground, then break
      break;
      t--;
    }
  }

  return t; // return the number of time intervals

}

// -------------------------------------------------------
//     PrintTrajectory()
// -------------------------------------------------------
// Arguments:
//   - list of doubles for distances
//   - list of doubles for heights
// Returns:
//   - nothing
// -------------------------------------------------------
void PrintTrajectory(double distances[], double heights[], int num_intervals){

  // print distance and heigh for each interval
  for (int i = 0; i < num_intervals; i++){
    cout << setw(4) << i << fixed << setprecision(3) << setw(10) << distances[i] << setw(10) << heights[i] << endl;
  }

  // find max height
  double max_height;
  max_height = MaxMeasurement(heights);

  // print max height
  cout << "Maximum height: " << max_height << endl;

}

// -------------------------------------------------------
//     MaxMeasurement()
// -------------------------------------------------------
// Arguments:
//   - list of doubles for heights
// Returns:
//   - maximum height
// -------------------------------------------------------
double MaxMeasurement(double heights[]){

  double max_height = 0;
  for (int i = 0; i < NUM_INTERVALS; i++){
    if (heights[i] > max_height){ // king of the hill
      max_height = heights[i];
    }
  }

  return max_height;

}
