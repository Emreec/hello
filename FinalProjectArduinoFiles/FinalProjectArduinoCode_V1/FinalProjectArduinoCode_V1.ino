#include <AccelStepper.h>
#include <SCServo.h>
///////////////////////////////////////STEPPER MOTORS/////////////////////////////////////
// Define the pins connected to the drivers
#define DIR_PIN 2
#define STEP_PIN 3
#define ENABLE_PIN 8

#define DIR_PIN2 4
#define STEP_PIN2 5
#define ENABLE_PIN2 9

// Define the maximum speed and acceleration of the stepper motors
#define MAX_SPEED 50000
#define ACCELERATION 1000
#define ACCELERATION2 50000

// Define the number of steps needed to move the motor one revolution
#define STEPS_PER_REV 200

// Create a new AccelStepper objects
AccelStepper stepper1(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);
AccelStepper stepper2(AccelStepper::DRIVER, STEP_PIN2, DIR_PIN2);

bool runOnce = true;
///////////////////////////////////////STEPPER MOTORS/////////////////////////////////////
///////////////////////////////////////SERVO MOTORS/////////////////////////////////////
SMS_STS st;
// the uart used to control servos.
// GPIO 18 - S_RXD, GPIO 19 - S_TXD, as default.
#define S_RXD 18
#define S_TXD 19
int modbusarray[5] =  {0,1,0,0,0};

///////////////////////////////////////SERVO MOTORS/////////////////////////////////////
  float firstShelfX = 0;
  float firstShelfY = 19;
  float upFirstShelfX = 0;
  float upFirstShelfY = 19;

  
  float secondShelfX = 15;
  float secondShelfY = 19;
  float upSecondShelfX = 15;
  float upSecondShelfY = 19;

  float thirdShelfX = 28;
  float thirdShelfY = 19;
  float uThirdShelfX = 28;
  float uThirdShelfY = 19;


  float fourthShelfX = 1.3;
  float fourthShelfY = 4;
  float uFourthShelfX = 1.3;
  float uFourthShelfY = 4;

  float fifthShelfX = 13;
  float fifthShelfY = 2;
  float uFifthShelfX = 13;
  float uFifthShelfY = 6;

  float sixthShelfX = 28;
  float sixthShelfY = 4;
  float uSixthShelfX = 28;
  float uSixthShelfY = 4;

  float uFirstShelfX = 46.8;
  float uFirstShelfY = 19;

  float uSecondShelfX = 62;
  float uSecondShelfY = 19;

  float upsideMovement = 6.5;

  float dropMedX = 62; 
  float dropMedY = 4;

 




void setup() {
  ///////////////////////////////////////STEPPER MOTORS/////////////////////////////////////
  // Set the enable pins as outputs
  pinMode(ENABLE_PIN, OUTPUT);
  pinMode(ENABLE_PIN2, OUTPUT);

  // Enable the drivers
  digitalWrite(ENABLE_PIN, LOW);
  digitalWrite(ENABLE_PIN2, LOW);

  // Set the maximum speed and acceleration of the stepper motors
  stepper1.setMaxSpeed(MAX_SPEED);
  stepper1.setAcceleration(ACCELERATION);

  stepper2.setMaxSpeed(MAX_SPEED);
  stepper2.setAcceleration(ACCELERATION2);
  ///////////////////////////////////////STEPPER MOTORS/////////////////////////////////////
  ///////////////////////////////////////SERVO MOTORS/////////////////////////////////////
  Serial.begin(115200);
  //Servo1
  Serial1.begin(1000000);
  st.pSerial = &Serial1;
  ///////////////////////////////////////SERVO MOTORS/////////////////////////////////////
  

//Stepper1 == X motor 
//Stepper2 == Y motor


//[0] == whether the operation is loading or unloading

}

void getMed(float shelfPosX , float shelfPosY){

  
    stepper1.move(shelfPosX * STEPS_PER_REV);
    while(stepper1.distanceToGo()!=0){
      stepper1.run();
    }
    stepper2.move(shelfPosY * STEPS_PER_REV);
    while(stepper2.distanceToGo()!=0){
      stepper2.run();
    }
    st.WritePosEx(1,23000, 9999, 9999); // ID , position , speed , acceleration // position will be decided //
    delay(9000);
    //instant movement of y motor
    stepper2.move(upsideMovement * STEPS_PER_REV);
    while(stepper2.distanceToGo()!=0){
      stepper2.run();
    }
    stepper2.move(-upsideMovement * STEPS_PER_REV);
    while(stepper2.distanceToGo()!=0){
      stepper2.run();
    }
    st.WritePosEx(1,0, 9999, 9999);
    delay(5000);
    runOnce = false;
  }


void dropMed(float shelfNo ,float shelfPosX ,float  shelfPosY){

  st.WritePosEx(1,0, 9999, 9999); //get the hand back
  delay(5000);
  
  stepper1.move((dropMedX - shelfPosX) * STEPS_PER_REV);
  while(stepper1.distanceToGo()!=0){
    stepper1.run();
    }
  stepper2.move((dropMedY - shelfPosY) * STEPS_PER_REV);
  while(stepper2.distanceToGo()!=0){
    stepper2.run();
  }
  st.WritePosEx(1, 23000, 9999, 9999);
  st.WritePosEx(3, 30000, 9999, 9999);
  delay(500);
  st.WritePosEx(3, 0, 9999, 9999);
  st.WritePosEx(1, -30000, 9999, 9999);
}
void goHome(){
  stepper1.move((-19) * STEPS_PER_REV);
  while(stepper1.distanceToGo()!=0){
    stepper1.run();
  }
  stepper2.move((-62) * STEPS_PER_REV);
  while(stepper2.distanceToGo()!=0){
    stepper2.run();
  }
  }

void uploadOperation(int uShelfNo ,float  uShelfPosX , float uShelfPosY){
    if (uShelfNo == 1){
      Serial.println(uShelfPosX);
      Serial.println(uShelfPosY);
      Serial.println(uFirstShelfY);
      Serial.println(uFirstShelfX);

          stepper2.move((uShelfPosY-uFirstShelfY) * STEPS_PER_REV);
        while(stepper2.distanceToGo()!=0){
          stepper2.run();
        }
        stepper1.move((uShelfPosX-uFirstShelfX) * STEPS_PER_REV);
        while(stepper1.distanceToGo()!=0){
          stepper1.run();
        }
        delay(2000);
        st.WritePosEx(1,23000, 9999, 9999);// send the hand forward
        delay(5000);
        st.WritePosEx(3,22000 ,9999 ,9999); //send the tonque forward
        delay(20000);
        
        stepper2.move(-uShelfPosY * STEPS_PER_REV);
        while(stepper2.distanceToGo()!=0){
          stepper2.run();
        }
        st.WritePosEx(1,0, 9999, 9999); 
        st.WritePosEx(3,-28000 ,9999 ,9999);
        delay(5000);
        stepper1.move(-uShelfPosX * STEPS_PER_REV);
        while(stepper1.distanceToGo()!=0){
          stepper1.run();
          }
    }
    else if(uShelfNo == 2){
          stepper1.move(uShelfPosY * STEPS_PER_REV);
        while(stepper1.distanceToGo()!=0){
          stepper1.run();
        }
        stepper2.move(uShelfPosX * STEPS_PER_REV);
        while(stepper2.distanceToGo()!=0){
          stepper2.run();
        }
        delay(500);
        st.WritePosEx(1,23000, 9999, 9999);// send the hand forward
        delay(500);
        st.WritePosEx(3,30000 ,9999 ,9999); //send the tonque forward
        delay(20000);
        
        stepper1.move(-uShelfPosY * STEPS_PER_REV);
        while(stepper1.distanceToGo()!=0){
          stepper1.run();
        }
        st.WritePosEx(1,-5000, 9999, 9999); 
        st.WritePosEx(3,-30000 ,9999 ,9999);
        delay(5000);
        stepper2.move(-uShelfPosY * STEPS_PER_REV);
        while(stepper2.distanceToGo()!=0){
          stepper2.run();
        }
    }
}
    



void loop() {
  float   shelfPosX; 
  float  shelfPosY;
  float  shelfNo ;
  float  uShelfPosX;    
  float  uShelfPosY;
  float uShelfNo;
  if(runOnce == true){
    Serial.println("240");
    delay(1000);
    //For unloading operations 
    //1st shelf
    if(modbusarray[0] == 0){
      Serial.println("245");
      if(modbusarray[1] == 1){
        float shelfPosX = firstShelfX;
        float  shelfPosY = firstShelfY;
        float  shelfNo = 1;
        
      }
      else if(modbusarray[1] == 2){
        float  shelfPosX = secondShelfX;
        float  shelfPosY = secondShelfY;
        float  shelfNo = 2;
        
      }
      else if(modbusarray[1] == 3){
        float  shelfPosx = thirdShelfX;
        float  shelfPosY = thirdShelfY;
        float  shelfNo = 3;
        
      }
      else if(modbusarray[1] == 4){
        float  shelfPosx = fourthShelfX;
        float  shelfPosY = fourthShelfY;
        float  shelfNo = 4;
       
      }
      else if(modbusarray[1] == 5){
        float  shelfPosx = fifthShelfX;
        float  shelfPosY = fifthShelfY;
        float shelfNo = 5;
        
      }
      else if(modbusarray[1] == 6){
        float  shelfPosx = sixthShelfX;
        float  shelfPosY = sixthShelfY;
        float shelfNo = 6;
        
      }
      getMed(shelfPosX ,  shelfPosY);
      dropMed( shelfNo ,  shelfPosX , shelfPosY);
      goHome();
      runOnce = false;
    } 
    else if (modbusarray[0] == 1){ // yükleme rafında ilaç var
          Serial.print("285");
          if(modbusarray[1] == 1){
            Serial.print("287");
            shelfPosX = uFirstShelfX;
            shelfPosY = uFirstShelfY;
            shelfNo = 1;
            
          }
          else if(modbusarray[1] == 2){

            shelfPosX = uSecondShelfX;
           shelfPosY = uSecondShelfY;
            shelfNo = 2;
            
          }
          Serial.println(shelfPosX);
          Serial.println(shelfPosY);
          getMed(shelfPosX , shelfPosY);

          if(modbusarray[2] == 1){
           uShelfPosX = upFirstShelfX;
             uShelfPosY = upFirstShelfY;
              
          }
          else if(modbusarray[2] == 2){
          uShelfPosX = upSecondShelfX;
              uShelfPosY = upSecondShelfY;
            
          }
          else if(modbusarray[2] == 3){
           uShelfPosX = uThirdShelfX;
             uShelfPosY = uThirdShelfY;
            
          }
          else if(modbusarray[2] == 4){
           uShelfPosX = uFourthShelfX;
            uShelfPosY = uFourthShelfY;
            
          }
          else if(modbusarray[2] == 5){
            uShelfPosX= uFifthShelfX;
             uShelfPosY = uFifthShelfY;
            
            Serial.println("329") ;
          }
          else if(modbusarray[2] == 6){
             uShelfPosX = uSixthShelfX;
             uShelfPosY = uSixthShelfY;
            
          }
          Serial.println(shelfNo );
          Serial.println(uShelfPosX);
          uploadOperation( shelfNo ,  uShelfPosX , uShelfPosY);
          runOnce=false;
          
          
    
    
    

    }
  }
}
  



  
  

