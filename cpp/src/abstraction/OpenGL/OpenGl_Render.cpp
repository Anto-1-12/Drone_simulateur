#include "OpenGl_Render.hpp"

OpenGLRenderer::OpenGLRenderer(int width,int height): 
    Render(),
    size_screen(glm::ivec2(width,height))
{
    InitWindow();
}

OpenGLRenderer::~OpenGLRenderer()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

void OpenGLRenderer::InitWindow()
{
    glfwInit();
    window = glfwCreateWindow(size_screen.x, size_screen.y, "OpenGL", NULL, NULL);
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glEnable(GL_DEPTH_TEST);
}

void OpenGLRenderer::Init()
{

}

void OpenGLRenderer::Update()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);

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

    glGenVertexArrays(1, &mesh.VAO);
    glGenBuffers(1, &mesh.VBO);

    glBindVertexArray(mesh.VAO);

    glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    all_mesh.push_back(mesh);
}

void OpenGLRenderer::AddObject()
{   
    std::string name_mesh = "triangle";

    Mesh mesh;
    for (int i = 0; i < all_mesh.size(); i++)
    {
        if (all_mesh[i].name == name_mesh)
        {
            mesh = all_mesh[i];
        }
    }

    all_object.push_back(Object{&mesh,glm::mat4()});
}