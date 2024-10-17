#include "BaseCharacter.h"
#include "raymath.h"

BaseCharacter::BaseCharacter()
{

}

void BaseCharacter::UndoMovement()
{
    WorldPos = WorldPosLastFrame;
}

Rectangle BaseCharacter::GetCollision()
{
    return Rectangle{
        GetScreenPos().x,
        GetScreenPos().y,
        Width * Scale,
        Height * Scale    
    };
}

void BaseCharacter::Tick(float DeltaTime)
{
    WorldPosLastFrame = WorldPos;

    // Update Animation
    RunningTime += DeltaTime;
    if (RunningTime >= UpdateTime)
    {
        RunningTime = 0.f;
        Frame++;
        if (Frame > MaxFrames) Frame = 0;
    }

    if (Vector2Length(Velocity) != 0.f)
    {
        WorldPos = Vector2Add( WorldPos, Vector2Scale(Vector2Normalize(Velocity), Speed));
        Velocity.x < 0.f ? RightLeft = -1.f : RightLeft = 1.f;
        MyTexture = Run;
    }
    else MyTexture = Idle;
    Velocity={};

    Rectangle KnightSource{Frame * Width, 0.f, RightLeft * Width, Height};
    Rectangle KnightDest{GetScreenPos().x, GetScreenPos().y, Scale * Width, Scale * Height};
    DrawTexturePro(MyTexture, KnightSource, KnightDest, Vector2{}, 0.f, WHITE);
}