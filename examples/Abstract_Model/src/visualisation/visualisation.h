#ifndef __VISUALISATION_H
#define __VISUALISATION_H

#define SIMULATION_DELAY 10

// constants
const unsigned int WINDOW_WIDTH = 1600;
const unsigned int WINDOW_HEIGHT = 900;

//frustrum
const double NEAR_CLIP = 0.1;
const double FAR_CLIP = 100;

//Circle model fidelity
const int SPHERE_SLICES = 16;
const int SPHERE_STACKS = 16;
const double SPHERE_RADIUS = 0.020;

//Viewing Distance
const double VIEW_DISTANCE = 1.5;

//light position
GLfloat LIGHT_POSITION[] = {10.0f, 10.0f, 10.0f, 1.0f};

#endif __VISUALISATION_H