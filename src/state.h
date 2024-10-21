#ifndef STATE_H
#define STATE_H

#define GL_SILENCE_DEPRECATION

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define MAX_ENTITIES 10000
#define MOUSESPEED = 5
#define PLAYERSPEED = 10

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

// internal libs
#include <stdio.h>
#include "shaders.h"

// extern libs
#include "cglm/cglm.h"

struct State {
    GLFWwindow* window;
    size_t ticks;
};

extern struct State state;

#endif
