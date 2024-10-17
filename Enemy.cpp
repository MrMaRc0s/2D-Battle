#include "Enemy.h"
#include "Character.h"
#include "raymath.h"

Enemy::Enemy(Vector2 Spawn, Texture2D IdleTexture, Texture2D RunTexture)
{
    WorldPos = Spawn;
    MyTexture = IdleTexture;
    Idle = IdleTexture;
    Run = RunTexture;
    Width = (MyTexture.width / MaxFrames);
    Height = (MyTexture.height);
    Speed = 3.5f;
}

Vector2 Enemy::GetScreenPos()
{
    return Vector2Subtract(WorldPos, Target->GetWorldPos());
}

void Enemy::Tick(float DeltaTime)
{
    if (!GetAlive()) return;
    Velocity = Vector2Subtract(Target->GetScreenPos(), GetScreenPos());
    if (Vector2Length(Velocity) <= radius) Velocity = {};
    BaseCharacter::Tick(DeltaTime);
    if(CheckCollisionRecs(Target->GetCollision(), GetCollision()))
    {
        Target->TakeDamage(Damage * DeltaTime);
    }
}