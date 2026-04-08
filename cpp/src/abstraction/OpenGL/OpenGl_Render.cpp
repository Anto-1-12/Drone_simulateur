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

    glDeleteShader(vertexShader2D);
    glDeleteShader(fragmentShader2D);
    glDeleteProgram(shaderProgram2D);

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

    //recuperer le str/contenu des shader
    std::string vertexCode = readFile("assets/OpenGL/vertex.glsl");
    std::string fragmentCode = readFile("assets/OpenGL/fragment.glsl");

    std::string vertexCode2D = readFile("assets/OpenGL/vertex_2D.glsl");
    std::string fragmentCode2D = readFile("assets/OpenGL/fragment_2D.glsl");

    //envoyer dans des const char*
    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();

    const char* vertexSource2D = vertexCode2D.c_str();
    const char* fragmentSource2D = fragmentCode2D.c_str();


    //                               3D Compilation
    //-------------------------------------------------------------------------------

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

    // creation du shader 3D entier
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glLinkProgram(shaderProgram);

    //                               2D Compilation
    //-------------------------------------------------------------------------------

    // creation Vertex shader
    vertexShader2D = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader2D, 1, &vertexSource2D, NULL);
    glCompileShader(vertexShader2D);

    //verification compilation du shader
    int success_vertex2D;
    char infoLog_vertex2D[512];

    glGetShaderiv(vertexShader2D, GL_COMPILE_STATUS, &success_vertex2D);
    if (!success_vertex2D)
    {
        glGetShaderInfoLog(vertexShader2D, 512, NULL, infoLog_vertex2D);
        std::cout << "Vertex shader 2D error:\n" << infoLog_vertex2D << std::endl;
    }

    // creation Fragment shader
    fragmentShader2D = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader2D, 1, &fragmentSource2D, NULL);
    glCompileShader(fragmentShader2D);

    //verification compilation du shader
    int success_fragment2D;
    char infoLog_fragment2D[512];

    glGetShaderiv(fragmentShader2D, GL_COMPILE_STATUS, &success_fragment2D);
    if (!success_fragment2D)
    {
        glGetShaderInfoLog(fragmentShader2D, 512, NULL, infoLog_fragment2D);
        std::cout << "Fragment shader 2D error:\n" << infoLog_fragment2D << std::endl;
    }

    // creation du shader 2D entier
    shaderProgram2D = glCreateProgram();
    glAttachShader(shaderProgram2D, vertexShader2D);
    glAttachShader(shaderProgram2D, fragmentShader2D);

    glLinkProgram(shaderProgram2D);

    //---------------------------------------------------------------------------------

    //creation du modeLoc
    glUseProgram(shaderProgram);
    modelLoc = glGetUniformLocation(shaderProgram, "model");
    viewLoc = glGetUniformLocation(shaderProgram, "view");
    projLoc = glGetUniformLocation(shaderProgram, "projection");
    nearLoc = glGetUniformLocation(shaderProgram, "nearPlane");
    farLoc  = glGetUniformLocation(shaderProgram, "farPlane");

    view = glm::lookAt(
        glm::vec3(0.0f, 3.0f, 10.0f), // position caméra
        glm::vec3(0.0f, 0.0f, 0.0f), // cible -> vec direction
        glm::vec3(0.0f, 1.0f, 0.0f)  // up
    );

    projection = glm::perspective(
        glm::radians(45.0f), // FOV
        (float) size_screen.x / size_screen.y,     // aspect ratio
        0.1f,                // near
        100.0f               // far
    );

    projection_2D = glm::ortho(0.0f, (float) size_screen.x,(float) size_screen.y, 0.0f);

}

void OpenGLRenderer::Init()
{

}

void OpenGLRenderer::Update()
{
    glUseProgram(shaderProgram);
    for (int i = 0; i < all_object.size(); i++)
    {
        glBindVertexArray(all_object[i].mesh->VAO);

        //passer les donner au shader pour transformer le model et l'envoyer dans l'espace
        //matrice pour tourner, bouger le model
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(computeModelMatrix(*all_object[i].transform)));

        //matrice pour avoir les infos de la camera
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        //matrice de projection
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));


        glDrawArrays(GL_TRIANGLES, 0, all_object[i].mesh->vertexCount);

        glUniform1f(nearLoc, 0.1f);
        glUniform1f(farLoc, 100.0f);
    }

    glUseProgram(shaderProgram2D);
    for (int a = 0; a < all_2D_object.size(); a++)
    {
        glBindVertexArray(all_2D_object[a].mesh->VAO);

        glm::mat4 model = computeModelMatrix(*all_2D_object[a].transform);

        glUniformMatrix4fv(glGetUniformLocation(shaderProgram2D, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram2D, "projection"), 1, GL_FALSE, glm::value_ptr(projection_2D));

        glDrawArrays(GL_TRIANGLES, 0, all_2D_object[a].mesh->vertexCount);
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

void OpenGLRenderer::AddMesh(std::string name, std::string path)
{

    //verifier si le nom n'et pas deja pris
    for (int i = 0; i < all_mesh.size();i++)
    {
        if (all_mesh[i].name == name)
        {
            std::cout << "nom de mesh deja pris, nom : " << name <<std::endl;
            return;
        }
    }

    //load l'obj
    std::vector<Vertex> vertices;
    if(!loadObjWithTiny(path, vertices)) {
        std::cout << "Failed to load OBJ\n";
        return;
    }

    Mesh mesh;

    mesh.name = name;

    mesh.vertexCount = vertices.size();

    //bind les VAO et VBO
    glGenVertexArrays(1, &mesh.VAO);
    glGenBuffers(1, &mesh.VBO);

    glBindVertexArray(mesh.VAO);

    //initialiser les VAO et VBO
    glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    //position et couleur
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
    glEnableVertexAttribArray(2);

    //unbind les buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    all_mesh.push_back(mesh);
}

void OpenGLRenderer::AddObject(std::string mesh_name, Transform& transform)
{
    bool is_init = false;
    for (int i = 0; i < all_mesh.size(); i++)
    {
        if (all_mesh[i].name == mesh_name)
        {
            all_object.push_back(Object{&all_mesh[i],&transform});
            is_init = true;
        }
    }

    if (!is_init)
    {
        std::cout<<"il n'y a pas de mesh de ce nom"<<std::endl;
    }
}

void OpenGLRenderer::Add2DObject(std::string mesh_name, Transform& transform)
{
    bool is_init = false;
    for (int i = 0; i < all_mesh.size(); i++)
    {
        if (all_mesh[i].name == mesh_name)
        {
            all_2D_object.push_back(Object{&all_mesh[i],&transform});
            is_init = true;
        }
    }

    if (!is_init)
    {
        std::cout<<"il n'y a pas de mesh de ce nom"<<std::endl;
    }
}

void OpenGLRenderer::SetView(glm::vec3 position, glm::vec3 vecDirection)
{
    view = glm::lookAt(
        position, // position caméra
        vecDirection, // cible -> vec direction
        glm::vec3(0.0f, 1.0f, 0.0f)  // up
    );
}

void OpenGLRenderer::ClearMesh()
{
    std::vector<Mesh>().swap(all_mesh);
}

void OpenGLRenderer::ClearObject()
{
    std::vector<Object>().swap(all_object);
}

void OpenGLRenderer::Clear2DObject()
{
    std::vector<Object>().swap(all_2D_object);
}

glm::vec2 OpenGLRenderer::getMousePos()
{
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    return glm::vec2(xpos,ypos);
}

bool OpenGLRenderer::IsMousePressed(int button)
{
    // si button == :
    // 0 == gauche
    // 1 == droite
    // 2 == molette
    if (glfwGetMouseButton(window, button) == GLFW_PRESS) {
    // clic gauche enfoncé
        return true; 
    }
    else
    {
        return false;
    }
}