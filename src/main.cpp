#include <iostream>
#include "glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>
#include <fstream>
#include "Shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <filesystem>

std::string ShadersPath = "/home/thiago-fedora/Documentos/Learning/OpenGL/src/shaders";
std::string TexturePath = "/home/thiago-fedora/Documentos/Learning/OpenGL/src/wall.jpg";

int main()
{   
    
    // Cria o objeto da janela
    GLFWwindow* MyWindow;

    // Inicia o Framework
    if (!glfwInit())
    {
        return 1;
    }

    // Cria o objeto da janela
    MyWindow = glfwCreateWindow(500, 500, "Janela", NULL, NULL);

    // Torna a janela o contexto atual da máquina de estados
    glfwMakeContextCurrent(MyWindow);

    // Faz com que o GLAD procure todas as funções do openGL
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout << "OpenGL não abriu!" << std::endl;
        glfwTerminate();
        return 1;
    }

    
    // São nossos vértices do triângulo. Lembre-se sempre de usar
    // os dados primitivos do OpenGL, não float
    GLfloat vertices[] = 
    {
        // Coord            // Color          // Texture
        -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
         0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f
    };

    GLfloat texCoords[] =
    {
        0.0f, 0.0f,
        0.5f, 1.0f,
        1.0f, 0.0f
    };

    /* Texture related stuff */
    int width, height, numChannels;
    unsigned char* data = stbi_load(TexturePath.c_str(), &width, &height, &numChannels, 0);

    if (data)
    {
        std::cout << "Wall.jpg loaded successfully!\n";
        std::cout << "Path: " << TexturePath << std::endl;
    }
    else
    {
        std::cout << "Error loading Texture!\n";
        std::cout << "Path: " << TexturePath << std::endl;
        std::cout << stbi_failure_reason() << std::endl;
    }

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // x, y, z => s, t, r
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

    // Texture filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                GL_UNSIGNED_BYTE, data);

    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    /* End of texture stuff */

    Shader MyShader (ShadersPath + "/vertex.vert.glsl", ShadersPath + "/fragment.frag.glsl");

    /** Encontrando as variáveis do shader */
    GLint NumAtributos;
    glGetProgramiv(MyShader.ProgramID, GL_ACTIVE_ATTRIBUTES, &NumAtributos);
    std::cout << "Atributos " << NumAtributos << std::endl;

    GLint MaxCharLengthName;
    glGetProgramiv(MyShader.ProgramID, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &MaxCharLengthName);

    for (int i = 0; i < NumAtributos; i++)
    {
        char* charBuffer = (char*) malloc(sizeof(char) * MaxCharLengthName);
        int length, size;
        GLenum dataType;

        glGetActiveAttrib(MyShader.ProgramID, i, MaxCharLengthName, &length, &size, &dataType, charBuffer);
        GLint varLocation = glGetAttribLocation(MyShader.ProgramID, charBuffer);

        std::cout << "Atributo " << charBuffer << " está em " << varLocation << "\n";
    }

    GLint Scale = glGetUniformLocation(MyShader.ProgramID, "scale");
    std::cout << "Scale: " << Scale << std::endl;

    GLint Rotation = glGetUniformLocation(MyShader.ProgramID, "rotate");
    std::cout << "Rotation: " << Rotation << std::endl;

    GLuint VAO;
    glGenVertexArrays(1, &VAO);

    GLuint VBO;
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (void*)(3 * sizeof(GL_FLOAT)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (void*)(6 * sizeof(GL_FLOAT)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLfloat Time = glfwGetTime();
    GLfloat GreenColor = sin(Time) / 2.0f + 0.5f;

    while (!glfwWindowShouldClose(MyWindow))
    {

        glClear(GL_COLOR_BUFFER_BIT);

        glBindTexture(GL_TEXTURE_2D, texture);
        
        MyShader.use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);


        glfwSwapBuffers(MyWindow);
        glfwPollEvents();
    }

    // Destroi glfw
    glfwTerminate();
    
    return 0;
}