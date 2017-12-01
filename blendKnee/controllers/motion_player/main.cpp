// Description:   Manage the entree point function

#include "MotionPlayer.hpp"

#include <cstdlib>

using namespace webots;

int main(int argc, char **argv)
{
  MotionPlayer *controller = new MotionPlayer();
  controller->textToSpeechGreeting();
  controller->runExerciseOne();
  controller->runExerciseTwo();
  controller->runExerciseThree();
  controller->textToSpeechEnding();
  delete controller;
  return EXIT_FAILURE;
  
}
