#include "Game.h"

#include <stb_image.h>

Game::Game(const int width, const int height, const char* title, bool vsync) 
	: Window(width, height, title, vsync)
{
	//just a light wrapper around window class
}

void Game::InitGameData() {
    //set custom cursor
    int width, height, numChannels;
    const char* cursorSrc = "C:/Users/varun/Pictures/Saved Pictures/Crosshair0.png";
    unsigned char* imgData = stbi_load(cursorSrc, &width, &height, &numChannels, 4);
    GLFWimage cursorImg;
    cursorImg.height = height;
    cursorImg.width = width;
    cursorImg.pixels = imgData;
    GLFWcursor* cursor = glfwCreateCursor(&cursorImg, 0, 0);
    if (cursor == NULL) {
        cout << "Loading Custom Cursor Failed!" << endl;
    }
    glfwSetCursor(getWindowPtr(), cursor);
    stbi_image_free(imgData);

    Shader* program = new Shader();
    program->compileShader("D:/CDEV/2DShooterPvP/2DShooterPvP/2DShooterPvP/Quad.shader");
    program->Use();
    program->setUniformMatrix4("projection", glm::ortho(0.0f, 1920.0f, 1080.0f, 0.0f, -1.0f, 1.0f));

    const char* texSrc = "C:/Users/varun/Pictures/Saved Pictures/RubberTexture.jpg";
    GameObject* object =  new GameObject(0, texSrc, GL_FALSE, glm::vec3(500.0f, 800.0f, 0.0f), glm::vec2(1000.0f, 100.0f), program);
    m_Objects.push_back(object);

    GameObject* gun = new GameObject(0, texSrc, GL_FALSE, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(100.0f, 33.0f), program);
    
    m_Player = new Player(0, texSrc, GL_FALSE, glm::vec3(910.0f, 0.0f, 0.0f), glm::vec2(100.0f,100.0f), program, gun);
    glfwSetWindowUserPointer(getWindowPtr(), (void*)this->m_Player);
    glfwSetKeyCallback(getWindowPtr(), [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        Player* player = (Player*)glfwGetWindowUserPointer(window);
        player->HandleKeyInput(window, key, scancode, action, mods);
    });
    glfwSetMouseButtonCallback(getWindowPtr(), [](GLFWwindow* window, int button, int action, int mods) {
        Player* player = (Player*)glfwGetWindowUserPointer(window);
        player->HandleMouseInput(window, button, action, mods);
    });
}

void Game::RunMainGameLoop() {
    GLFWwindow* windowPtr = getWindowPtr();

    float flPreviousTime = 0;
    float flCurrentTime = glfwGetTime();
    while (!glfwWindowShouldClose(windowPtr))
    {
        // clear window
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        flPreviousTime = flCurrentTime;
        flCurrentTime = glfwGetTime();

        float dt = flCurrentTime - flPreviousTime;

        //collisions
        for (GameObject* object : m_Objects) {
            m_Player->CheckCollision(object, 2.5f);
            for (GameObject* projectile : m_Player->m_Projectiles) {
                projectile->CheckCollision(object, 2.5f);
            }
        }

        //render
        for (GameObject* object : m_Objects) {
            object->Render(dt);
        }
        m_Player->Render(dt, windowPtr);
      
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(windowPtr);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
}