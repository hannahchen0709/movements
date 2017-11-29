#include "MotionPlayer.hpp"
#include <webots/LED.hpp>
#include <webots/Motor.hpp>
#include <webots/PositionSensor.hpp>
#include <RobotisOp2MotionManager.hpp>
#include <webots/utils/Motion.hpp>
#include <webots/Speaker.hpp>
#include <webots/Keyboard.hpp>
#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;
using namespace managers;
using namespace webots;

static const char *motorNames[NMOTORS] = {
  "ShoulderR" /*ID1 */, "ShoulderL" /*ID2 */, "ArmUpperR" /*ID3 */, "ArmUpperL" /*ID4 */,
  "ArmLowerR" /*ID5 */, "ArmLowerL" /*ID6 */, "PelvYR"    /*ID7 */, "PelvYL"    /*ID8 */,
  "PelvR"     /*ID9 */, "PelvL"     /*ID10*/, "LegUpperR" /*ID11*/, "LegUpperL" /*ID12*/,
  "LegLowerR" /*ID13*/, "LegLowerL" /*ID14*/, "AnkleR"    /*ID15*/, "AnkleL"    /*ID16*/,
  "FootR"     /*ID17*/, "FootL"     /*ID18*/, "Neck"      /*ID19*/, "Head"      /*ID20*/
};

//Constructor
MotionPlayer::MotionPlayer():
    Robot()
{
  //Get time step
  mTimeStep = getBasicTimeStep();
 
  getLED("HeadLed")->set(0xFF0000);
  getLED("EyeLed")->set(0x00FF00);
  mSpeaker = getSpeaker("Speaker");
  mSpeaker->setLanguage("en-US");
  
  for (int i=0; i<NMOTORS; i++) {
   mMotors[i] = getMotor(motorNames[i]);
   string sensorName = motorNames[i];
   sensorName.push_back('S');
   mPositionSensors[i] = getPositionSensor(sensorName);
   mPositionSensors[i]->enable(mTimeStep);
  }
  mKeyboard = getKeyboard();
  mKeyboard->enable(mTimeStep);
  
  mMotionManager = new RobotisOp2MotionManager(this);
}

//Destructor
MotionPlayer::~MotionPlayer() {
}

//Step function
void MotionPlayer::myStep() {
  int ret = step(mTimeStep);
  if (ret == -1)
    exit(EXIT_SUCCESS);
}

//Wait function
void MotionPlayer::wait(int ms) {
  double startTime = getTime();
  double s = (double) ms / 1000.0;
  while (s + startTime >= getTime())
    myStep();
}

// function containing the main feedback loop
void MotionPlayer::run() {

  cout << "-------MotionPlayer example of ROBOTIS OP2-------" << endl;
  cout << "This example plays a Webots motion file" << endl;

  // step
  myStep();
  
   
    bool motionOneFlag = false;
    bool motionTwoFlag = false;
    bool motionThreeFlag = false;
    
    Motion motion_1("hand_extend.motion");
    motion_1.setLoop(true);
    Motion motion_2("hand_high.motion");
    motion_2.setLoop(true);
    while(true){
        switch(mKeyboard->getKey()) {
        case 81 ://Q key
          cout<<"q key press"<<endl;
          motion_1.stop();
          motion_2.stop();
          motionThreeFlag = true;
          break;
        case 87 ://W key
          cout<<"w key press"<<endl;
          motionThreeFlag = false;
          break;
        case Keyboard::UP :
          //cout<<"pressed up key"<<endl;
          motion_2.stop();
          motionTwoFlag = false;
          motionThreeFlag = false;
          motion_1.play();
          motionOneFlag = true;
          break;
        case Keyboard::DOWN :
          //cout<<"pressed down key"<<endl;
          motion_1.stop();
          motionOneFlag = false;
          break;
        case Keyboard::RIGHT :
          //cout<<"pressed right key"<<endl;
          motion_2.stop();
          motionTwoFlag = false;
          break;
        case Keyboard::LEFT :
          //cout<<"pressed left key"<<endl;
          motion_1.stop();
          motionOneFlag = false;
          motionThreeFlag = false;
          motion_2.play();
          motionTwoFlag = true;
          break;
      }
    if (motionThreeFlag){
      mMotionManager->playPage(1);
      wait(1000);
      mMotionManager->playPage(15);
      //motionThreeFlag = false;
      cout<<"finsh"<<endl;
    }
      myStep();
    }
    /*
  while (true){
      // play the hello motion
    mMotionManager->playPage(1); // init position
    wait(1000);
    mMotionManager->playPage(15);
  }*/
}

void MotionPlayer::textToSpeech() {

  myStep();
  
    cout<<mSpeaker->getLanguage()<<endl;
    //mSpeaker->playSound(mSpeaker,mSpeaker,"eric.wav",1.0,1.0,0,true);
    mSpeaker->speak("hello hello hello hello hello hello hello hello hello hellohello hello hello hello hello ",1.0);
//    while(true){
//     myStep();
//    }
/*   
    string text = "how are you";
    string mLanguage = "en";
    fprintf(stderr, "Speaker: Saying \"%s\" ...\n", text.c_str());
    char *buffer = (char *)malloc(strlen(text.c_str())+3);
    sprintf(buffer, "\"%s\"", text.c_str());
    execl("/Users/hannah/Downloads/espeak-1.45.04-OSX/espeak-1.45.04/speak", "espeak", buffer, "-v", mLanguage.c_str(), (char *)NULL);
    //free(buffer);
*/  

}
