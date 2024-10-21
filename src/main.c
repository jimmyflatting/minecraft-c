#include "state.h"
#include <stdio.h>
#include "GLFW/glfw3.h"
#include "ecs.h"

int print_hello_world(void) {
    printf("Hello World\n");
    return 0;
}


int main(int argc, const char * argv[]) {
    if (!glfwInit()) {
        return -1;
    }
    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    print_hello_world();
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
