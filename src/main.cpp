#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

void resize_window(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // These 2 lines are just so I can set the window size to be the size of the monitor in glfwCreateWindow
    GLFWmonitor* monitor { glfwGetPrimaryMonitor() };
    const GLFWvidmode* mode { glfwGetVideoMode(monitor) };

    GLFWwindow* window { glfwCreateWindow(mode->width, mode->height, "One-Particle System", NULL, NULL) };
    if (window == NULL)
    {
        std::cout << "Failed to create window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Query and load all OpenGL extensions allowed by your drivers
    // Allows us to access features/extensions not in the core OpenGL specification
    if(glewInit() != GLEW_OK)
    {
        glfwDestroyWindow(window);
        glfwTerminate();
        throw std::runtime_error("Glew initialization failed");
    }
    
    glViewport(0, 0, mode->width, mode->height);
    glfwSetFramebufferSizeCallback(window, resize_window);

    glClearColor(1.0f, 0.0f, 0.0f, 1.0f); // Set background color to red

    while (!glfwWindowShouldClose(window)) 
    {
        processInput(window);

        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void resize_window(GLFWwindow* window, int width, int height)
{
    (void)window; // This just gets rid of the unused parameter warning
    glViewport(0, 0, width, height);
}
