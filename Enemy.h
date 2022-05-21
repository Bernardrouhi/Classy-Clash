#include "raylib.h"
#include "BaseCharacter.h"
#include "Character.h"

class Enemy : public BaseCharacter
{
public:
    Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture);
    virtual Vector2 getScreenPos() override;
    virtual void tick(float deltaTime) override;
    void setTarget(Character* character) { target = character; }

protected:
private:
    Character* target{};
};