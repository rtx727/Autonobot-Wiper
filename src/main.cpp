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
vex::brain Brain;

// define your global instances of motors and other devices here
motor RM(PORT12, bool(reverse));
motor LM(PORT7, bool(forward));
bumper BUMPER(PORT3);
distance DISTANCE(PORT1);
motor_group motors(RM, LM);
controller CONTROLLER;
inertial BrainInertial = inertial();


//Structs
struct PIDcontroller{
    float Kp;
    float Ki;
    float Kd;
    float error;
    float previousError;
    float integral;
    float output;

    //Constructor - sets up K values
    PIDcontroller(float Kp, float Ki, float Kd){
        Kp = Kp;
        Ki = Kp;
        Kd = Kd;
        error = 0;
        previousError = 0;
        integral = 0; //Tracks accumulated error if not responsive enough
        output = 0;
    }

    //PID calculation function
    //Params: target and current position
    //Output: Positive output for motorspeed in percentage
    float calculatePID(float error){
        // Take in error
        this->error = error;

        // Porportional Term
        float porportionalTerm = this->error * this->Kp;

        // Integral Term
        // Add the error to the integral
        this->integral = this->integral + this->error;
        float integralTerm = this->integral * this->Ki;

        //Derivative Term
        float derivative = this->error - this->previousError;
        float derivativeTerm = derivative * this-> Kd;
        this->previousError = this->error;

        //Make output term
        this->output = fabs(porportionalTerm + integralTerm +  derivativeTerm);

        //Max motor speed is 100%
        if (this->output > 100){
            this->output = 100;
        }

        return this->output; //outputs motor speed
    }

};






//Function decalarations

//Calibrate all sensors
void calibrateSensors();



//Params: Velocity, heading
//Purpose: Drives forward using gyro sensor 
//Outputs: None
//Maybe use PID controller to subtract output from one wheel and add to another?
void driveHeading(float velocity, float heading);

//Params: Heading (+ or -)
//Purpose: Turns gyro sensor, assumes current heading is zero
//Outputs: None
void turnHeading(float targetHeading);






//Test functions
void testPIDTurning(){
    turnHeading(90);
}







int main() {
	calibrateSensors();
    Brain.Screen.printAt( 2, 30, "Hello IQ2" );
    //Tests
    testPIDTurning();

   
    Brain.programStop();
}

//Function definitions

//Yunhao
void calibrateSensors(){
    Brain.Screen.printAt( 2, 50, "Calibrating Sensors" );
    BrainInertial.calibrate();
    while(BrainInertial.isCalibrating()){} //Allow time for calibration
    BrainInertial.resetRotation();
    Brain.Screen.printAt( 2, 70, "Calibration Complete" );
    Brain.Screen.clearScreen();
}

void turnHeading(float targetHeading){
    //Set current heading to 0;
    BrainInertial.resetRotation();
    float error = targetHeading; //Initial error is just heading
    float acceptableError = 2; //degrees
    float currentHeading = 0;
    float motorSpeed = 0; //In percentage

    //Construct PID controller object
    float Kp = 0.2;
    float Ki = 0.1;
    float Kd = 0.0;
    PIDcontroller turnPID = PIDcontroller(Kp, Ki, Kd);

    //Perform movement until error is acceptable
    while(abs(error) > acceptableError){
        //continuously find current heading and error
        currentHeading = BrainInertial.rotation(degrees);
        error = targetHeading - currentHeading;

        //Determine which direction to turn
        if (error > 0){ //right turn
            motorSpeed = turnPID.calculatePID(error); //Pass in error to PIDcontroller to get output
            RM.spin(reverse, motorSpeed, percent);
            LM.spin(forward, motorSpeed, percent);
        }
        else{ //left turn
            motorSpeed = turnPID.calculatePID(error); //Pass in error to PIDcontroller to get output
            RM.spin(forward, motorSpeed, percent);
            LM.spin(reverse, motorSpeed, percent);
        }
    }
    return; 
}




//Riley
void driveHeading(float velocity, float heading){}



//Richard



//Matt