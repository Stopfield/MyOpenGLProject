#include <iostream>
#include "glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>
#include <fstream>

std::string ShadersPath = "/home/thiago-fedora/Documentos/Learning/OpenGL/src/shaders";

std::string GetShaderSource(std::string NomeArquivo)
{
    std::ifstream File (NomeArquivo);
    std::string FileContent;
    std::string line;

    if (File.is_open())
    {
        std::cout << "Loading shader " << NomeArquivo << "\n";
        while (std::getline(File, line))
        {
            FileContent += line + "\n";
        }
    }
        
    File.close();

    return FileContent;
}

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

    // Código fonte do Vertex Shader, dá pra pegar de um arquivo também
    std::string VertexSource = GetShaderSource(ShadersPath + "/vertex.glsl");
    const char* vertexShaderSource = VertexSource.c_str();

    // Código fonte do Fragment Shader, dá pra pegar do arquivo
    std::string FragmentSource = GetShaderSource(ShadersPath + "/fragment.glsl");
    const char* FragmentShaderSource = FragmentSource.c_str();
    
    // São nossos vértices do triângulo. Lembre-se sempre de usar
    // os dados primitivos do OpenGL, não float
    GLfloat vertices[] = 
    {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f
    };

    /* Criando Shaders */

    // Cria um Vertex Shader
    GLuint VertexShader;
    VertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(VertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(VertexShader);

    // Mas antes disso, verificamos se deu tudo certo na compilação
    int success;
    char infoLog[512];
    glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(VertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }

    // Agora, vamos criar um FragmentShader, aquele que colore os pixels
    GLuint FragmentShader;
    FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(FragmentShader, 1, &FragmentShaderSource, NULL);
    glCompileShader(FragmentShader);

    glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(FragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }

    /* Criando ShaderProgram */

    // O Shader Program vai unir os shaders que a gente criou, ele diz
    // como a pipeline de renderizaçõa vai se comportar
    unsigned int ShaderProgram;

    // Cria um programa
    ShaderProgram = glCreateProgram();

    // Precisamos atracar os shaders que criamos com esse programa
    // Atracamos primeiro o VertexShader (ele vem primeiro)
    glAttachShader(ShaderProgram, VertexShader);
    
    // Depois o FragmentShader (vem por último)
    glAttachShader(ShaderProgram, FragmentShader);

    glLinkProgram(ShaderProgram);
    glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(ShaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
            << infoLog << std::endl;
    }

    /* Depois de Linkar pro programa, pode deletar */
    glDeleteShader(VertexShader);
    glDeleteShader(FragmentShader);

    /** Encontrando as variáveis do shader */
    GLint NumAtributos;
    glGetProgramiv(ShaderProgram, GL_ACTIVE_ATTRIBUTES, &NumAtributos);
    std::cout << "Atributos " << NumAtributos << std::endl;

    GLint MaxCharLengthName;
    glGetProgramiv(ShaderProgram, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &MaxCharLengthName);

    for (int i = 0; i < NumAtributos; i++)
    {
        char* charBuffer = (char*) malloc(sizeof(char) * MaxCharLengthName);
        int length, size;
        GLenum dataType;

        glGetActiveAttrib(ShaderProgram, i, MaxCharLengthName, &length, &size, &dataType, charBuffer);
        GLint varLocation = glGetAttribLocation(ShaderProgram, charBuffer);

        std::cout << "Atributo " << charBuffer << " está em " << varLocation << "\n";
    }

    GLint VertexColorLocation = glGetUniformLocation(ShaderProgram, "VertexColor");

    GLuint VAO;
    glGenVertexArrays(1, &VAO);

    GLuint VBO;
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLfloat Time = glfwGetTime();
    GLfloat GreenColor = sin(Time) / 2.0f + 0.5f;

    while (!glfwWindowShouldClose(MyWindow))
    {

        Time = glfwGetTime();
        GreenColor = sin(Time) / 2.0f + 0.5f;


        glUseProgram(ShaderProgram);
        glUniform4f(VertexColorLocation, 0.0f, GreenColor, 0.0f, 1.0f);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);


        glfwSwapBuffers(MyWindow);
        glfwPollEvents();
    }

    // Destroi glfw
    glfwTerminate();
    
    return 0;
}