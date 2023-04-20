#pragma once
#include <string>
#include <unordered_map>
#include "CMath.h"
#define COLOUR(x) x/255
extern CRITICAL_SECTION m_critical;

struct CLootEntry
{
	std::string name;
	uint16_t type;
	int32_t price;
	bool IsPresent;
	bool IsSelected;
};

class CBulletTraictory
{
public:
	uintptr_t TrajectoryInfo; //0x0030 
	char pad_0x0038[0x54]; //0x0038
	float AmmoLifeTime; //0x008C 
	__int32 FragmentIndex; //0x0090 
	float RandomSeed; //0x0094 
	float ArmorDamage; //0x0098 
	Vector3 MasterOrigin; //0x009C 
	Vector3 Direction; //0x00A8 
	float InitialSpeed; //0x00B4 
	float Speed; //0x00B8 
	float DamageDegradationCoefficient; //0x00BC 
	float Damage; //0x00C0 
	char pad_0x00C4[0x4]; //0x00C4
	float BulletMassGram; //0x00C8 
	float BulletDiameterMilimeters; //0x00CC 
	char pad_0x00D0[0x18]; //0x00D0
	float TimeSinceShot; //0x00E8 
	Vector3 StartPosition; //0x00EC 
	Vector3 StartVelocity; //0x00F8 
}; //Size=0x0104

extern std::unordered_map<std::string, CLootEntry> LootItems;

struct DataTransform
{
	uintptr_t TransformArray;
	uintptr_t TransformIndices;
};

struct CTransform
{
	uintptr_t TransformArray;
	uintptr_t TransformIndices;
	std::vector<int> IndiceArray;
	int index;
};

struct ThreadLocalPlayers
{
	uintptr_t CamraBase;
	uintptr_t LocalPlayer;
};

struct ObjectThreadInfo
{
	Vector3 LocationLoot;
	std::string Name;
};

struct ObjectThreadPlayer
{
	uintptr_t Player;
	uintptr_t Profile;
	uintptr_t Settings;
	uintptr_t NamePointer;
	uintptr_t NameWeapon;
	uintptr_t HealthController;
	std::vector<CTransform> PlayerBone;
	bool IsScav;
	//std::vector<uintptr_t> PlayerBone;
};

struct ExitThreadInfo
{
	uintptr_t Instance;
	Vector3 Position;
	int32_t Status;
	std::string Name;
};

struct CheatGlobalData
{
	uintptr_t GameObjManager;
	uintptr_t GameCameraArray;
	uintptr_t CameraBase;
	uintptr_t LocalPlayer;
	uintptr_t LocalWeapon;
	uintptr_t VisorEffect;
	uintptr_t NightVision;
	uintptr_t ThermalVision;
	uintptr_t MovementContext;
	uintptr_t Physical;
	uintptr_t SpeedHackData;
	uintptr_t ShootData;
	std::vector<ObjectThreadPlayer> ThreadInfoPlayer;
	std::vector<ObjectThreadInfo> ThreadInfoLoot;
	std::vector<ExitThreadInfo> ThreadInfoExit;
};

class CClintWorld
{
public:
	uintptr_t ExitPointList; //0x0018 
	char pad_0x0020[0x10]; //0x0020
	uintptr_t GameDateTime; //0x0030 
	char pad_0x0038[0x40]; //0x0038
	uintptr_t BallisticsCalculator; //0x0078 
	uintptr_t LootList; //0x0080 
	char pad_0x0088[0x10]; //0x0088
	uintptr_t AllLoot; //0x0098 
	uintptr_t RegisteredPlayersList; //0x00A0 
}; //Size=0x00C0
//[A0] RegisteredPlayers : System.Collections.Generic.List<Player>

class GameObjectManager
{
public:
	char pad_0x0000[0x8]; //0x0000
	uintptr_t m_pLastTaggedObject; //0x0000 
	uintptr_t m_pFirstTaggedObject; //0x0008 
	char pad_0x0018[0x8]; //0x0018
	uintptr_t m_pLastActiveObject; //0x0010 
	uintptr_t m_pFirstActiveObject; //0x0018 
}; //Size=0x0020

class GameObjManager
{
public:
	char pad_0x0000[0x8]; //0x0000
	ULONG64 lastObject; //0x0008 
	ULONG64 listObject; //0x0010 
	char pad_0x0018[0x8]; //0x0018
	ULONG64 lastActivObject; //0x0020 
	ULONG64 activeObject; //0x0028 
}; //Size=0x0040

struct UString
{
	char Buffer[256];
};

struct BaseObject
{
	ULONG64 prevObjectLink; //0x0000
	ULONG64 nextObjectLink; //0x0008
	ULONG64 objectLink; //0x0010
};

class UnityList
{
public:
	char pad_0x0000[0x10]; //0x0000
	ULONG64 List; //0x0010 
	int32_t Count; //0x0018 
}; //Size=0x0040

struct UCamerasArray
{
	uintptr_t List;
	int32_t Count;
};

struct HealthComp
{
	float Health;
	float MaxHealth;
};

class CLootInfo
{
public:
	uintptr_t Description; //0x0020 
	char pad_0x0028[0x28]; //0x0028
	uintptr_t _id; //0x0050 
}; //Size=0x0840


extern CheatGlobalData* SDKGlobalData;

VOID ColectThreadData();
VOID MiscThreadData();
VOID DrawinThread();
VOID AimThreadData();
VOID MemThread();