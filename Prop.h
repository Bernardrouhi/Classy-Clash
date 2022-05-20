#include "raylib.h"

class Prop
{
public:
    Prop(Vector2 pos, Texture2D tex);
    void Render(Vector2 knightPos);
    Vector2 getWorldPos() { return worldPos;}
    void destroy();
    Rectangle getCollisionRec(Vector2 knightPos);

private:
    Vector2 worldPos{};
    Texture2D texture{};
    float scale{4.f};
};