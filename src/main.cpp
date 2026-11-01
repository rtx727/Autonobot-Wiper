/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       yunhao, tao, matt, richard                                                     */
/*    Created:      10/31/2026, 8:25:58 PM                                    */
/*    Description:  IQ2 project                                               */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

using namespace vex;
using namespace std;

// A global instance of vex::brain used for printing to the IQ2 brain screen
vex::brain       Brain;

// define your global instances of motors and other devices here
motor RM(PORT12, bool(reverse));
motor LM(PORT7, bool(forward));
bumper BUMPER(PORT3);
distance DISTANCE(PORT1);
motor_group motors(RM, LM);
controller CONTROLLER;



//Function decalarations

//Params: Velocity, heading
//Purpose: Drives forward using gyro sensor
//Outputs: None
void driveHeading(float velocity, float heading);

//Params: Velocity, heading
//Purpose: Turns gyro sensor
//Outputs: None
void turnHeading(float velocity, float heading);











int main() {
	
    Brain.Screen.printAt( 2, 30, "Hello IQ2" );
   
    while(1) {
        
        // Allow other tasks to run
        this_thread::sleep_for(10);
    }
}

//Function definitions

//Yunhao
void turnHeading(float velocity, float heading){ //Add PID
float error{};
}


//Riley
void driveHeading(float velocity, float heading){}



//Richard



//Matt