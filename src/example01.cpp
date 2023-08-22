#include <iostream>
#include "glad.h"
#include <GLFW/glfw3.h>

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
    const char* vertexShaderSource = "#version 400 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
            "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";

    // Código fonte do Fragment Shader, dá pra pegar do arquivo
    const char* FragmentShaderSource = "#version 400 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
            "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\0";

    // São nossos vértices do triângulo. Lembre-se sempre de usar
    // os dados primitivos do OpenGL, não float
    GLfloat vertices[] = 
    {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f
    };

    GLfloat Triforce[] =
    {
        0.0f, 0.5f, 0.0f,
        -0.25f, 0.0f, 0.0f,
        0.25f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f 
    };

    GLfloat Retangulo[] =
    {
        -0.5f,  0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f
    };

    GLuint indices[] =
    {
        0, 3, 1,
        1, 2, 3
    };

        // 2d vertices
    GLfloat Vertices2D[] = 
    {
        -0.5f, 0.5f,
        0.5f, 0.5f,
        0.5f, -0.5f,
        -0.5f, -0.5f,
        -0.5f, 0.5f
    };

    /* Criando Shaders */

    // Cria um Vertex Shader
    GLuint VertexShader;

    // A função glCreateShader retorna um ID para o shader que eu quero
    // Ela pode receber diversos tipos de shader
    VertexShader = glCreateShader(GL_VERTEX_SHADER);

    // Define o código fonte do Shader
    // Passamos o ID do objeto, mais umas configurações pra ele entender
    // as strings
    glShaderSource(VertexShader, 1, &vertexShaderSource, NULL);

    // No final, compilamos, afinal, o computador precisa entender
    glCompileShader(VertexShader);

    // Mas antes disso, verificamos se deu tudo certo na compilação
    int success;
    char infoLog[512];

    // Essa função retorna um parâmetro de tal shader e armazena em uma variável
    // Passamos o ID do Objeto shader, qual o parâmetro queremos dele e onde
    // esse parâmetro vai ser salvo.
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

    // Por fim, linkamos os shaders e vemos se eles são compativeis
    glLinkProgram(ShaderProgram);

    // Do mesmo jeito dos Shaders, usamos essa função para pegar um
    // atributo de um determinado programa
    // Passamos o ID do programa, qual parâmetro queremos e para onde
    // o parâmetro vai
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

    /* Agora os VBO VAO etc*/
    GLuint VAO[1], VBO[1], EBO;

    /* SEMPRE CRIE O VAO PRIMEIRO DO QUE O VBO! */
    // O VAO é uma Array que vai conter os VBOS. Por isso, Vertex Array
    // A função cria somente 1 VAO, é normal ter mais, por isso a função
    // tem essa opção. No final, a função gera o ID do VAO na variável
    glGenVertexArrays(1, VAO);

    // Os VBOs que vão conter os dados de fato. Eles são buffers porque
    // podem armazenar várias coisas sobre os vértices.
    // Tem que ser depois do VAO, pq estamos criando ele dentro do VAO
    // Aqui pedimos para criar só um VBO e colocá-lo na variável
    glGenBuffers(1, VBO);

    glGenBuffers(1, &EBO);
    
    // Aqui damos Bind em um Vertex Array
    glBindVertexArray(VAO[0]);

    /** NOTA 
     * Um Bind é quando alteramos em que estado a máquina de estados
     * se encontra. Quando damos um bind em determinado VAO, isso significa
     * que vamos alterá-lo agora com outras funções. Lembre-se disso.
    */

    // Damos bind de um VBO a um VAO, nesse caso, um array buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);

    // Aqui, vamos especificar os dados do Buffer dentro do Array Buffer
    // ou seja, do VAO. Nesse caso, como só há um, usamos esta função. Mas,
    // Se houvessem mais de um VBO atrelados a ele, utilizariamos a função
    // glNamedBufferData que especificaria qual VBO aplicar
    // Aqui damos os dados pro VBO atrelado ao VAO, o tamanho dos dados, os dados
    // e o seu tipo de uso
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices2D), Vertices2D, GL_STATIC_DRAW);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(Triforce), Triforce, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Retangulo), Retangulo, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Tem algo a ver com os shaders que vem. No caso, ele diz que no índice zero,
    // existem três valores do tipo float, sem arredondamento, com tamanho tal. No
    // final, o casting estranho fica pra depois

    /** NOTA - O QUE É UM VERTEX ATTRIBUTE
     * Um vertex attribute é um dado que passa pelo shader, uma variável
     * de entrada para o shader que tem dados para cada vértice
    */

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*) 0);
    // glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*) 0);
    // Para usarmos o ponteiro criado na função acima, precisamos habilitá-lo.
    // Esta função habilita no VAO com bind para utilizar o índice zero
    glEnableVertexAttribArray(0);

    // Desacoplamos o VBO do contexto, mas fica salvo no VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Desacomplamos o VAO do contexto
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


    while (!glfwWindowShouldClose(MyWindow))
    {

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Aqui indicamos que vamos usar o Shader Program nesse contexxto
        glUseProgram(ShaderProgram);

        // Damos bind no VAO que contém aquel VBO
        glBindVertexArray(VAO[0]);

        // Utiliza a array que temos no VAO para desenhar uma primitiva
        // Indica qual primitiva, onde o array começa e onde termina
        // glDrawArrays(GL_LINE_LOOP, 0, 4);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // Troca os buffers, pra atualizar a tela
        // Um fica se alterando e o outro mostrando
        glfwSwapBuffers(MyWindow);

        // Calcula todos os eventos
        glfwPollEvents();
    }

    // Deleta todos os buffers, passando quantidade e onde eles estão
    // Lembre-se, pode haver mais de um
    glDeleteBuffers(1, VBO);
    glDeleteVertexArrays(1, VAO);
    glDeleteBuffers(1, &EBO);

    // Deleta o Shader program
    glDeleteProgram(ShaderProgram);

    // Destroi glfw
    glfwTerminate();
    
    return 0;
}