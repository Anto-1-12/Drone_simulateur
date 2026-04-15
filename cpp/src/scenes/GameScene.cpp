#include "GameScene.hpp"

GameScene::GameScene() :
    Scene(),
    scneneToChange("Menu"),
    wantToChange(false),
    is_init(false)
{
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        std::cerr << "Erreur socket\n";
        return;
    }

    sockaddr_in server;
    memset(&server, 0, sizeof(server));

    server.sin_family = AF_INET;
    server.sin_port = htons(5000); // même port que Python
    inet_pton(AF_INET, "192.168.88.177", &server.sin_addr); // IP du serveur Python

    if (connect(sock, (sockaddr*)&server, sizeof(server)) < 0) {
        std::cerr << "Erreur de connexion\n";
    } else {
        std::cout << "Connecté au serveur\n";
    }
}
    //"169.254.40.10"
    //"127.0.0.1" -> local
    //"192.168.88.177"
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

        cube.position = glm::vec3(-4,-3,0);
        cube.rotation = glm::vec3(0,0,0);
        cube.scale = glm::vec3(2.5,2.5,2.5);
        window.AddMesh("test","assets/models/tourEiffel.obj","assets/textures/texture.png");
        window.AddObject("test",cube);

        drone.position = glm::vec3(0,0,0);
        drone.rotation = glm::vec3(0,0,0);
        drone.scale = glm::vec3(0.05,0.05,0.05);

        window.AddMesh("drone","assets/models/drone.obj","assets/textures/texture.png");
        window.AddObject("drone",drone);
        
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
        if (cmd == "sync_drone_pos")
        {
            drone.position.x = j["x"];
            drone.position.y = j["y"];
            drone.position.z = j["z"];
        }
    }
}