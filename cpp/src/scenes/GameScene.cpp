#include "GameScene.hpp"

GameScene::GameScene(): 
    Scene(),
    scneneToChange("Menu"),
    wantToChange(false),
    is_init(false),
    sock(socket(AF_INET, SOCK_STREAM, 0))
{
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        std::cerr << "Erreur socket\n";
        return;
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(5000);
    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);

    if (connect(sock, (sockaddr*)&server, sizeof(server)) < 0) {
        std::cerr << "Erreur de connexion\n";
    }
}

GameScene::~GameScene()
{
    closesocket(sock);
    WSACleanup();
}

void GameScene::draw(Render& window)
{
    if (is_init == false)
    {

        window.ClearMesh();
        window.ClearObject();
        window.Clear2DObject();

        cube.position = glm::vec3(0,-3.3,0);
        cube.rotation = glm::vec3(0,0,0);
        cube.scale = glm::vec3(2.5,2.5,2.5);
        window.AddMesh("test","assets/models/tourEiffel.obj","assets/textures/texture.png");
        window.AddObject("test",cube);
        is_init = true;
    }
}

void GameScene::event()
{
    
}

void GameScene::update(float dt,Render& window)
{
    cube.rotation.y += 20 * dt;
    //65 = Q
    //87 = Z
    if (window.IsKeyPressed(87))
    {
        sendMessage(R"({"cmd":"avancer"})");
    }

    sync();

}

bool GameScene::wantToChangeScene()
{
    return wantToChange;
}

std::string GameScene::getSceneChangeType()
{
    return scneneToChange;
}

void GameScene::sendMessage(std::string command)
{
    command += "\n";
    send(sock, command.c_str(), command.size(), 0);
}

void GameScene::sync()
{
    char buffer[1024] = {0};
    int bytes = recv(sock, buffer, 1024, 0);

    if (bytes > 0)
    {
        std::string data(buffer);
        json j = json::parse(data);
        std::string cmd = j["cmd"];
        int x = j["x"];
        int y = j["y"];
        int z = j["z"];
    }
}