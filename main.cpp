// Description:   Manage the entree point function

#include "MotionPlayer.hpp"

#include <cstdlib>

using namespace webots;

int main(int argc, char **argv)
{
  MotionPlayer *controller = new MotionPlayer();
  controller->run();
  delete controller;
  return EXIT_FAILURE;
  
}
