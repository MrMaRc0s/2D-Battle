#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H

#include "raylib.h"

class BaseCharacter
{
public:
    BaseCharacter();
    Vector2 GetWorldPos() { return WorldPos; }
    virtual void Tick(float DeltaTime);
    void UndoMovement();
    Rectangle GetCollision();
    virtual Vector2 GetScreenPos() = 0;
    bool GetAlive(){ return bAlive; }
    void SetAlive(bool bIsAlive) { bAlive = bIsAlive; }


protected:
    Texture2D MyTexture = LoadTexture("characters/knight_idle_spritesheet.png");
    Texture2D Idle = LoadTexture("characters/knight_idle_spritesheet.png");
    Texture2D Run = LoadTexture("characters/knight_run_spritesheet.png");
    Vector2 ScreenPos{};
    Vector2 WorldPos{};
    float RunningTime = 0.f;
    int Frame = 1;
    // 1: Right, -1: Left
    float RightLeft = 1.f;
    float Speed = 4.f;
    int MaxFrames = 6;
    float UpdateTime = 1.f / 12.f;
    float Scale = 4.f;
    float Width{};
    float Height{};
    Vector2 WorldPosLastFrame{};
    Vector2 Velocity{};

private:
    bool bAlive = true;
};

#endif