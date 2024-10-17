#include "raylib.h"
#include "BaseCharacter.h"

class Character;

class Enemy : public BaseCharacter
{
public:
    Enemy(Vector2 Spawn, Texture2D IdleTexture, Texture2D RunTexture);
    virtual void Tick(float DeltaTime) override;
    void SetTarget(Character* Knight) { Target = Knight; }
    virtual Vector2 GetScreenPos() override;

private:
    Character* Target;
    float Damage = 10.f;
    float radius = 25.f;

};