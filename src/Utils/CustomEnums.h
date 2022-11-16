#pragma once

class CustomEnums
{
public:
    enum Entity
    {
        Bullet,
        Rock,
        Enemy,
        Rocket
    };

    enum Spawn
    {
        Top,
        Bottom,
        Right,
        Left
    };

    enum EnemyT
    {
        Regular,
        SpaceBane,
        WarVet
    };

    enum BulletT
    {
        RegularB,
        Rifle,
        Kaboom
    };
};