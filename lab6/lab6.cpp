#include <iostream>
#include <math.h>
#include <iomanip>

using namespace std;

void InitMeasurements(double list[]);
int CalcTrajectory(double distances[], double heights[], double angle, double velocity);
void PrintTrajectory(double distances[], double heights[], int num_intervals);
double MaxMeasurement(double list[], int num_intervals);

const int MAX_NUM_ELEMENTS = 100;
const int NUM_INTERVALS = 15;

int main(){

  double degrees;
  cout << "Enter the angle in degrees <15-75>: ";
  cin >> degrees;

  double radians;
  radians = (degrees * M_PI) / 180;

  double distances[MAX_NUM_ELEMENTS], heights[MAX_NUM_ELEMENTS];
  InitMeasurements(distances);
  InitMeasurements(heights);

  double velocity = 100.0;
  int num_intervals;

  num_intervals = CalcTrajectory(distances, heights, radians, velocity);
  PrintTrajectory(distances, heights, num_intervals);

  // system("pause");
  return 0;

}

void InitMeasurements(double list[]){

  for (int i = 0; i < MAX_NUM_ELEMENTS; i++){
    list[i] = 0.0;
  }

}

int CalcTrajectory(double distances[], double heights[], double angle, double velocity){

  int t = 0;
  for (int i = 1; i < NUM_INTERVALS; i++){
    t++;
    distances[i] = velocity * cos(angle) + distances[i-1];
    heights[i] = velocity * sin(angle) - (9.80665 * pow(t,2)) / 2 + heights[i-1];
    if (heights[i] < 0){
      break;
      t--;
    }
  }

  return t;

}

void PrintTrajectory(double distances[], double heights[], int num_intervals){

  for (int i = 0; i < num_intervals; i++){
    cout << setw(4) << i << fixed << setprecision(3) << setw(10) << distances[i] << setw(10) << heights[i] << endl;
  }

  double max_height;
  max_height = MaxMeasurement(heights, num_intervals);

  cout << "Maximum height: " << max_height << endl;

}

double MaxMeasurement(double heights[], int num_intervals){

  double max_height = 0;
  for (int i = 0; i < num_intervals; i++){
    if (heights[i] > max_height){
      max_height = heights[i];
    }
  }

  return max_height;

}
