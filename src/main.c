#include "state.h"

int game_init(void);
void game_setup(void);
void game_update(void);
void game_render(void);
void game_run(void);
void game_quit(void);

struct State state;
GLuint create_shader(const char* vertex_shader, const char* fragment_shader);
GLuint shader_program;

int game_init(void) {
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    state.window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Minecraft", NULL, NULL);
    if (!state.window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(state.window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    shader_program = create_shader("shaders/box.vert", "shaders/box.frag");
    printf("Shader program ID: %d\n", shader_program);

    return 0;
}

void game_update(void) {
    if (glfwGetKey(state.window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(state.window, GLFW_TRUE);
    }

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glClear(GL_COLOR_BUFFER_BIT);
}

void game_render(void) {
    glUseProgram(shader_program);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void game_run(void) {
    while (!glfwWindowShouldClose(state.window)) {
        game_update();
        game_render();

        glfwSwapBuffers(state.window);
        glfwPollEvents();
    }
}

void game_quit(void) {
    glfwDestroyWindow(state.window);
    glfwTerminate();
}

int main(int argc, char *argv[]) {
    game_init();
    game_run();
    game_quit(); 
    return 0;
}
