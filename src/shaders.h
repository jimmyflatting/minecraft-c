#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glad/glad.h>

char* read_file(const char* filepath) {
    FILE* file = fopen(filepath, "r");
    if (!file) {
        printf("ERROR::SHADER::FILE_NOT_FOUND: %s\n", filepath);
        return NULL;
    }

    // Get the length of the file
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Allocate memory for the file content
    char* content = (char*)malloc(length + 1);
    if (!content) {
        printf("ERROR::SHADER::MEMORY_ALLOCATION_FAILED\n");
        fclose(file);
        return NULL;
    }

    // Read the file into the content
    fread(content, 1, length, file);
    content[length] = '\0'; // Null-terminate the string

    fclose(file);
    return content;
}

GLuint create_shader(const char* vertex_shader_path, const char* fragment_shader_path) {
    char* vertex_shader_source = read_file(vertex_shader_path);
    if (!vertex_shader_source) {
        return 0; // Return 0 if vertex shader could not be read
    }

    GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
    // Cast the pointer correctly
    glShaderSource(vertex_shader_id, 1, (const GLchar **)&vertex_shader_source, NULL);
    glCompileShader(vertex_shader_id);

    GLint success;
    glGetShaderiv(vertex_shader_id, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar info_log[512];
        glGetShaderInfoLog(vertex_shader_id, 512, NULL, info_log);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s\n", info_log);
    }

    free(vertex_shader_source); // Free the allocated memory for the vertex shader source

    char* fragment_shader_source = read_file(fragment_shader_path);
    if (!fragment_shader_source) {
        return 0; // Return 0 if fragment shader could not be read
    }

    GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
    // Cast the pointer correctly
    glShaderSource(fragment_shader_id, 1, (const GLchar **)&fragment_shader_source, NULL);
    glCompileShader(fragment_shader_id);

    glGetShaderiv(fragment_shader_id, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar info_log[512];
        glGetShaderInfoLog(fragment_shader_id, 512, NULL, info_log);
        printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s\n", info_log);
    }

    free(fragment_shader_source); // Free the allocated memory for the fragment shader source

    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader_id);
    glAttachShader(shader_program, fragment_shader_id);
    glLinkProgram(shader_program);

    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success) {
        GLchar info_log[512];
        glGetProgramInfoLog(shader_program, 512, NULL, info_log);
        printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s\n", info_log);
    }

    glDeleteShader(vertex_shader_id);
    glDeleteShader(fragment_shader_id);

    return shader_program; // Return the shader program ID
}
