#include "Character.h"
#include "raymath.h"

Character::Character(int WinWidth, int WinHeight) :
    WinWidth(WinWidth), WinHeight(WinHeight)
{
    Width = (MyTexture.width / MaxFrames);
    Height = (MyTexture.height);
}

Vector2 Character::GetScreenPos()
{
    return Vector2{
    static_cast<float>(WinWidth) / 2.f - Scale * Width / 2.f,
    static_cast<float>(WinHeight) / 2.f - Scale * Height / 2.f
    };
}

void Character::Tick(float DeltaTime)
{
    if (!GetAlive()) return;

    if (IsKeyDown(KEY_W))
        Velocity.y -= 1.f;
    if (IsKeyDown(KEY_A))
        Velocity.x -= 1.f;
    if (IsKeyDown(KEY_S))
        Velocity.y += 1.f;
    if (IsKeyDown(KEY_D))
        Velocity.x += 1.f;

    BaseCharacter::Tick(DeltaTime);

    Vector2 Origin{};
    Vector2 Offset{};
    float Rotation{};

    if (RightLeft>0.f)
    {
        Origin = {0.f, Weapon.height * Scale};
        Offset = {35.f, 55.f};
        WeaponCollisionRec = {GetScreenPos().x + Offset.x,
        GetScreenPos().y + Offset.y - Weapon.height * Scale,
        Weapon.width * Scale,
        Weapon.height * Scale};
        Rotation = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? 35.f : 0.f;
    }
    else
    {
        Origin = {Weapon.width * Scale, Weapon.height * Scale};
        Offset = {25.f, 55.f};
        WeaponCollisionRec = {GetScreenPos().x + Offset.x - Weapon.height * Scale,
        GetScreenPos().y + Offset.y - Weapon.height * Scale,
        Weapon.width * Scale,
        Weapon.height * Scale};
        Rotation = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? -35.f : 0.f;
    } 

    //draw sword
    Rectangle Source{0.f, 0.f, static_cast<float>(Weapon.width) * RightLeft, static_cast<float>(Weapon.height)};
    Rectangle Dest{GetScreenPos().x + Offset.x, GetScreenPos().y + Offset.y, Weapon.width * Scale, Weapon.height * Scale};
    DrawTexturePro(Weapon, Source, Dest, Origin, Rotation, WHITE);
    
    /*DrawRectangleLines(
        WeaponCollisionRec.x, 
        WeaponCollisionRec.y, 
        WeaponCollisionRec.width, 
        WeaponCollisionRec.height, 
        RED
    );*/
}


void Character::TakeDamage(float Damage)
{
    Health-= Damage;
    if (Health <= 0.f)
    {
        SetAlive(false);
    }
}