#pragma once

#define FPS 60

#define MAXLV 4

#define HEIGHT 640
#define WIDTH 1200

#define SCALE 0.1f
#define SCALED 40

#define MOBBORDER 80

#define STEP 10.f
#define PLAYERHP 100
#define PLAYERBULLETSPEED 15.f
#define PLAYERBULLETSIZE 5.f
#define PLAYERDMG 20
#define PLAYERAS 0.5f

#define BONUSCOUNT 4

#define MOBHP 80
#define MOBSPEED 7.f
#define MOBBULLETSPEED 8.f
#define MOBBULLETSIZE 7.f
#define MOBAS 1.f

#define MOBCOUNT 10

#define MELEEMOBDMG 3
#define RANGEMOBDMG 1

#define PICKUPSHP 25
#define PICKUPSDMG 10
#define PICKUPSAS 0.8f

#define PASSABLE 1
#define IMPASSABLE 0


#pragma region enums
enum PickupTypes
{
	HP = 0, DMG, AS
};

enum EnemyTypes
{
	Melee = 0, Ranged
};

enum BulletTypes
{
	Eb = 0, Pb
};

enum BlocksTypes
{
	Nothing = 0, Stone, Sand
};

#pragma endregion