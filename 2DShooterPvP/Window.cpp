#include "Window.h"
#include "Game.h"

void APIENTRY glDebugCallback(GLenum source, GLenum mType, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

Window::Window(const int width, const int height, const char* title, bool vsync) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_Window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (m_Window == NULL) {
        printf("Failed to Create Window :-(");
        glfwTerminate();
    }
    glfwSwapInterval(vsync);
    glfwMakeContextCurrent(m_Window);
    glfwSetFramebufferSizeCallback(m_Window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) printf("Failed to initialize GLAD :-(");

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(glDebugCallback, nullptr);

    glEnable(GL_DEPTH_TEST);
}

Window::~Window() {
    glfwTerminate();
}

void  APIENTRY glDebugCallback(GLenum source, GLenum mType, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
    std::string src;
    switch (source) {
    case GL_DEBUG_SOURCE_API:
        src = "Windows";
        break;
    case GL_DEBUG_SOURCE_SHADER_COMPILER:
        src = "Shader Compiler";
        break;
    case GL_DEBUG_SOURCE_THIRD_PARTY:
        src = "Third Party";
        break;
    case GL_DEBUG_SOURCE_APPLICATION:
        src = "Application";
        break;
    case GL_DEBUG_SOURCE_OTHER:
        src = "Other";
        break;
    }

    std::string type;
    switch (mType) {
    case GL_DEBUG_TYPE_ERROR:
        type = "Error";
        break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
        type = "Deprecated Behavior";
        break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
        type = "Undefined Behavior";
        break;
    case GL_DEBUG_TYPE_PORTABILITY:
        type = "Portability Error";
        break;
    case GL_DEBUG_TYPE_PERFORMANCE:
        type = "Performance Error";
        break;
    case GL_DEBUG_TYPE_OTHER:
        type = "Other Message";
        break;
    }

    switch (severity) {
    case GL_DEBUG_SEVERITY_NOTIFICATION:
        spdlog::trace("GL NOTIFICATION - {} {}: {}", src, type, message);
        break;
    case GL_DEBUG_SEVERITY_LOW:
        spdlog::warn("GL LOW - {} {}: {}", src, type, message);
        break;
    case GL_DEBUG_SEVERITY_MEDIUM:
        spdlog::error("GL MEDIUM - {} {}: {}", src, type, message);
        break;
    case GL_DEBUG_SEVERITY_HIGH:
        spdlog::critical("GL HIGH - {} {}: {}", src, type, message);
        break;
    }
    return;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}