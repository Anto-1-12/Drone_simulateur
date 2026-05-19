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

    system("start assets\\python\\venv\\Scripts\\python.exe assets\\python\\main.py N");
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
    
    bool debug = false;
    if (window.IsKeyPressed(73))
    {
        debug = true;
        std::cout<<std::endl;
        std::cout<<"-----------------"<<std::endl;
        std::cout<<std::endl;
        std::cout<<"send to serv"<<std::endl;
    }

    //-----------------------------------------------
    //            update send to serv
    //A
    if (window.IsKeyPressed(81))
    {
        sendMessage(R"({"cmd":"rollgauche"})");
        if(debug){
            std::cout<<R"({"cmd":"rollgauche"})"<<std::endl;
        }
    }
    //E
    if (window.IsKeyPressed(69))
    {
        sendMessage(R"({"cmd":"rolldroite"})");
        if(debug){
            std::cout<<R"({"cmd":"rolldroite"})"<<std::endl;
        }
    }
    //87 = Z
    if (window.IsKeyPressed(87))
    {
        sendMessage(R"({"cmd":"avancer"})");
        if(debug){
            std::cout<<R"({"cmd":"avancer"})"<<std::endl;
        }
    }
    //65 = Q
    if (window.IsKeyPressed(65))
    {
        sendMessage(R"({"cmd":"tourneràgauche"})");
        if(debug){
            std::cout<<R"({"cmd":"tourneràgauche"})"<<std::endl;
        }
    }
    //S
    if (window.IsKeyPressed(83))
    {
        sendMessage(R"({"cmd":"reculer"})");
        if(debug){
            std::cout<<R"({"cmd":"reculer"})"<<std::endl;
        }
    }
    //D
    if (window.IsKeyPressed(68))
    {
        sendMessage(R"({"cmd":"tourneràdroite"})");
        if(debug){
            std::cout<<R"({"cmd":"tourneràdroite"})"<<std::endl;
        }
    }
    //R
    if (window.IsKeyPressed(82) && !is_R_pressed)
    {
        sendMessage(R"({"cmd":"augmenter puissance moteur"})");
        is_R_pressed = true;
        if(debug){
            std::cout<<R"({"cmd":"augmenter puissance moteur"})"<<std::endl;
        }
    }
    else if(!window.IsKeyPressed(82) && is_R_pressed)
    {
        is_R_pressed = false;
    }
    //F
    if (window.IsKeyPressed(70) && !is_F_pressed)
    {
        sendMessage(R"({"cmd":"diminuer puissance moteur"})");
        is_F_pressed = true;
        if(debug){
            std::cout<<R"({"cmd":"diminuer puissance moteur"})"<<std::endl;
        }
    }
    else if(!window.IsKeyPressed(70) && is_F_pressed)
    {
        is_F_pressed = false;
    }
    //H
    if (window.IsKeyPressed(72) && !is_H_pressed)
    {
        sendMessage(R"({"cmd":"hover"})");
        is_H_pressed = true;
        if(debug){
            std::cout<<R"({"cmd":"hover"})"<<std::endl;
        }
    }
    else if(!window.IsKeyPressed(72) && is_H_pressed)
    {
        is_H_pressed = false;
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
    sync(debug);

    //-----------------------------------------------
    //               cam pos + angle
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

void GameScene::sync(bool debug)
{   
    if(debug)
    {
        std::cout<<"get from serv"<<std::endl;
    }
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
                    if(debug)
                    {
                        std::cout<<j<<std::endl;
                    }
                }
                else if (cmd == "sync_drone_ang")
                {
                    drone.rotation.x = j["x"];
                    drone.rotation.y = j["y"];
                    drone.rotation.z = j["z"];
                    if(debug)
                    {
                        std::cout<<j<<std::endl;
                    }
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