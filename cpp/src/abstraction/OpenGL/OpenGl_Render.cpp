#include "OpenGl_Render.hpp"

OpenGLRenderer::OpenGLRenderer(int width,int height): 
    Render(),
    size_screen(glm::ivec2(width,height))
{
    InitWindow();
}

OpenGLRenderer::~OpenGLRenderer()
{
    //supression des shader
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteProgram(shaderProgram);

    //supression des mesh -> VAO et VBO
    for(auto& mesh : all_mesh)
    {
        glDeleteVertexArrays(1, &mesh.VAO);
        glDeleteBuffers(1, &mesh.VBO);
    }

    //desinitialiser glfw
    glfwDestroyWindow(window);
    glfwTerminate();
}

void OpenGLRenderer::InitWindow()
{
    //initialiser la fenetre
    if (!glfwInit())
        std::cout << "GLFW init failed\n";

    window = glfwCreateWindow(size_screen.x, size_screen.y, "OpenGL", NULL, NULL);
    glfwMakeContextCurrent(window);
    
    if(!window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        std::cout << "GLAD init failed\n";
    
    //activer la profondeur
    glEnable(GL_DEPTH_TEST);

    //clear color = noire
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    std::string vertexCode = readFile("assets/OpenGL/vertex.glsl");
    std::string fragmentCode = readFile("assets/OpenGL/fragment.glsl");

    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();

    // creation Vertex shader
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    //verification compilation du shader
    int success_vertex;
    char infoLog_vertex[512];

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success_vertex);
    if (!success_vertex)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog_vertex);
        std::cout << "Vertex shader error:\n" << infoLog_vertex << std::endl;
    }

    // creation Fragment shader
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    //verification compilation du shader
    int success_fragment;
    char infoLog_fragment[512];

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success_fragment);
    if (!success_fragment)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog_fragment);
        std::cout << "Fragment shader error:\n" << infoLog_fragment << std::endl;
    }

    // creation du shader entier
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glLinkProgram(shaderProgram);

    //creation du modeLoc
    glUseProgram(shaderProgram);
    modelLoc = glGetUniformLocation(shaderProgram, "model");
}

void OpenGLRenderer::Init()
{

}

void OpenGLRenderer::Update()
{
    
    for (int i = 0; i < all_object.size(); i++)
    {
        glBindVertexArray(all_object[i].mesh->VAO);

        //passer les donner au shader pour transformer le model et l'envoyer dans l'espace
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(all_object[i].transform));

        glDrawArrays(GL_TRIANGLES, 0, all_object[i].mesh->vertexCount);
    }

    glfwSwapBuffers(window);
}

void OpenGLRenderer::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool OpenGLRenderer::IsOpen()
{
    return !glfwWindowShouldClose(window);
}

void OpenGLRenderer::Events()
{
    glfwPollEvents();
}

void OpenGLRenderer::AddMesh()
{
    Mesh mesh;

    mesh.name = "triangle";

    float vertices[] = {
        // positions
         0.0f,  0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f
    };

    mesh.vertexCount = 3;

    //bind les VAO et VBO
    glGenVertexArrays(1, &mesh.VAO);
    glGenBuffers(1, &mesh.VBO);

    glBindVertexArray(mesh.VAO);

    //initialiser les VAO et VBO
    glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //position et couleur gpas capté
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //unbind les buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    all_mesh.push_back(mesh);
}

void OpenGLRenderer::AddObject()
{   
    std::string name_mesh = "triangle";

    for (int i = 0; i < all_mesh.size(); i++)
    {
        if (all_mesh[i].name == name_mesh)
        {
            all_object.push_back(Object{&all_mesh[i],glm::mat4(1.0f)});
        }
    }
}