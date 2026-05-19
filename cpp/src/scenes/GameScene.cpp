#include "GameScene.hpp"

GameScene::GameScene() :
    Scene(),
    scneneToChange("Menu"),
    wantToChange(false),
    is_init(false),
    pitch(0.0f),
    yawn(0.0f)
{

    //Lancement du server

    system("start assets\\python\\venv\\Scripts\\python.exe assets\\python\\main.py");
    std::this_thread::sleep_for(std::chrono::seconds(5));

    //Conection au server

    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        std::cerr << "Erreur socket\n";
        return;
    }

    u_long mode = 1; // 1 = non-bloquant
    ioctlsocket(sock, FIONBIO, &mode);

    sockaddr_in server;
    memset(&server, 0, sizeof(server));

    //"169.254.40.10"
    //"127.0.0.1" -> local
    //"192.168.88.177"
    server.sin_family = AF_INET;
    server.sin_port = htons(5000); // même port que Python
    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr); // IP du serveur Python

    bool connected = false;

    while (!connected)
    {
        int result = connect(sock, (sockaddr*)&server, sizeof(server));

        if (result == 0){
            connected = true;
            std::cout << "Connecté au serveur\n";
            break;
        }else {
            int err = WSAGetLastError();

            if (err == WSAEISCONN) {
                connected = true;
            }
    }

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
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
        window.Clear2DObject();
        window.ClearObject();
        window.ClearMesh();

        cube.position = glm::vec3(-4,0,0);
        cube.rotation = glm::vec3(0,0,0);
        cube.scale = glm::vec3(2.5,2.5,2.5);
        window.AddMesh("test","assets/models/tourEiffel.obj","assets/textures/texture.png");
        window.AddObject("test",cube);

        drone.position = glm::vec3(0,0,0);
        drone.rotation = glm::vec3(0,0,0);
        drone.scale = glm::vec3(0.05,0.05,0.05);
        window.AddMesh("drone","assets/models/drone.obj","assets/textures/tkt.png");
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

    //-----------------------------------------------
    //            update send to serv
    //65 = Q
    //87 = Z
    if (window.IsKeyPressed(87))
    {
        sendMessage(R"({"cmd":"avancer"})");
    }
    if (window.IsKeyPressed(65))
    {
        sendMessage(R"({"cmd":"gauche"})");
    }
    if (window.IsKeyPressed(83))
    {
        sendMessage(R"({"cmd":"reculer"})");
    }
    if (window.IsKeyPressed(68))
    {
        sendMessage(R"({"cmd":"droite"})");
    }

    //-----------------------------------------------
    //                   client
    // -> UP
    if (window.IsKeyPressed(265))
    {
        pitch -= 150 * dt;
    }
    // -> DOWN
    if (window.IsKeyPressed(264))
    {
        pitch += 150 * dt;
    }
    // -> LEFT
    if (window.IsKeyPressed(263))
    {
        yawn -= 150 * dt;
    }
    // -> RIGHT
    if (window.IsKeyPressed(262))
    {
        yawn += 150 * dt;
    }
    //-----------------------------------------------
    //         update reception from serv
    sync();


    glm::vec3 vec_dir = glm::vec3(cos(glm::radians(yawn)) * cos(glm::radians(pitch)),sin(glm::radians(pitch)),sin(glm::radians(yawn)) * cos(glm::radians(pitch)));
    window.SetView(drone.position+(vec_dir*3.0f),-vec_dir);

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
        std::string data(buffer, bytes);
        buffer_accum += data;

        size_t pos;

        while ((pos = buffer_accum.find('\n')) != std::string::npos) {
            std::string line = buffer_accum.substr(0, pos);
            buffer_accum.erase(0, pos + 1);


            if (line.empty()) continue;

            try {
                json j = json::parse(line);
                
                std::string cmd = j["cmd"];
                if (cmd == "sync_drone_pos")
                {
                    drone.position.x = j["x"];
                    drone.position.y = j["y"];
                    drone.position.z = j["z"];
                }
                else
                {
                    std::cout<<cmd<<std::endl;
                }
            }
            catch (const std::exception& e) {
                std::cerr << "Parse error: " << e.what() << std::endl;
            }
        }
    }
}