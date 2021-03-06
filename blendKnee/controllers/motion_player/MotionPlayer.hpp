// Description:   Sample showing how to use a Webots motion on the real robotis-op2

#ifndef MOTION_PLAYER_HPP
#define MOTION_PLAYER_HPP

#define NMOTORS 20

#include <webots/Robot.hpp>

namespace managers {
  class RobotisOp2MotionManager;
}

namespace webots {
  class Motor;
  class PositionSensor;
  class Keyboard;
  //class Camera;
};


class MotionPlayer : public webots::Robot {
  public:
             MotionPlayer();
    virtual ~MotionPlayer();
    void     runExerciseOne();
    void     runExerciseTwo();
    void     runExerciseThree();
    void     textToSpeechGreeting();
    void     textToSpeechSecondExercise();
    void     textToSpeechThirdExercise();
    void     textToSpeechSad();
    void     textToSpeechHappy();
    void     textToSpeechSadEncouragement();
    void     textToSpeechHappyEncouragement();
    void     textToSpeechEnding();

  private:
    int      mTimeStep;

    void     myStep();
    void     wait(int ms);
    webots::Motor                   *mMotors[NMOTORS];
    webots::PositionSensor *mPositionSensors[NMOTORS];
    webots::Speaker *mSpeaker;
    webots::Keyboard *mKeyboard;
    managers::RobotisOp2MotionManager *mMotionManager;
};

#endif
