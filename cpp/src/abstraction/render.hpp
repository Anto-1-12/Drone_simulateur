#ifndef RENDER
#define RENDER

class Render
{
public:

    Render() = default;
    virtual ~Render() = default;

    virtual void Init() = 0;
    virtual void Update() = 0;
    virtual void Clear() = 0;
    virtual bool IsOpen() = 0;
    virtual void Events() = 0;
};

#endif