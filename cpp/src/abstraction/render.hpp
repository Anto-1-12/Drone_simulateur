#ifndef RENDER
#define RENDER

class Render
{
public:

    Render() = default;
    virtual ~Render() = default;

    virtual void InitWindow() = 0;
    virtual void Init() = 0;
    virtual void Update() = 0;
    virtual void Clear() = 0;
    virtual bool IsOpen() = 0;
    virtual void Events() = 0;
    virtual void AddMesh(std::string name, std::string path) = 0;
    virtual void AddObject() = 0;
};

#endif