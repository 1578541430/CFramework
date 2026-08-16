#pragma once

// by Unispect and UC
namespace offset
{
	// Base
	constexpr auto dwGameObjectManager = 0x1CF93E0;
	constexpr auto dwAllCamera = 0x1BF8BC0;

	// EFT.GameWorld
	constexpr auto ExfilController = 0x30; // exfiltrationControllerClass
	constexpr auto LootList = 0x118; // LootList
	constexpr auto RegisteredPlayers = 0x140; // RegisteredPlayers
	constexpr auto MainPlayer = 0x1A8; // MainPlayer
	constexpr auto GrenadeList = 0x200; // Grenades

	// EFT.Player
	namespace Player
	{
		constexpr auto pPlayerBody = 0xC0;
		constexpr auto pWeaponAnimation = 0x1E0;
		constexpr auto pProfile = 0x618;
		constexpr auto pPhysics = 0x630;
		constexpr auto pHealthController = 0x660;

		/* - SPT 3.11.x
		constexpr auto pProfile = 0x600;
		constexpr auto pPhysics = 0x610;
		constexpr auto pHealthController = 0x640; 
		*/

		//EFT.MovementContext
	}

	// EFT.Profile
	namespace Profile
	{
		constexpr auto Id = 0x10; // str
		constexpr auto AccountId = 0x18; // str
		constexpr auto pInfoClass = 0x40; // pointer
	}

	// EFT.Profile->InfoClass
	namespace InfoClass
	{
		constexpr auto Nickname = 0x10; // str
		constexpr auto MainProfileNickname = 0x20; // str
		constexpr auto GroupId = 0x28; // str
		constexpr auto TeamId = 0x30; // str
		constexpr auto profileInfoSettingsClass = 0x48; // pointer
		constexpr auto eplayerSide_0 = 0x88; // int
		constexpr auto RegistrationDate = 0x8C; // int
		constexpr auto Type = 0x90; // int
	}

	/*
	constexpr auto Nickname = 0x10; // str
	constexpr auto EntryPoint = 0x18; // str
	constexpr auto MainProfileNickname = 0x20; // str
	constexpr auto MGroupId = 0x28; // str
	constexpr auto TeamId = 0x30; // str
	constexpr auto profileInfoSettingsClass = 0x50; // pointer
	constexpr auto eplayerSide_0 = 0x90; // int
	constexpr auto RegistrationDate = 0x94; // int
	constexpr auto Type = 0x98; // int
	*/

	// EFT.Animations.ProceduralWeaponAnimation
	namespace WeaponAnimations
	{
		constexpr auto Breath = 0x30;
		constexpr auto isAiming = 0x1C5;
	}

	// .BasePhysicalClass
	namespace Physics
	{
		constexpr auto Stamina = 0x38;
		constexpr auto HandsStamina = 0x40;
		constexpr auto Oxygen = 0x40;
		constexpr auto FallDamageMultiplier = 0xBC;
		constexpr auto OxygenRestoreRate = 0xD4;
	}

	namespace HealthController
	{
		constexpr auto HealthValue_0 = 0x38;  // Energy / Hydration
		constexpr auto HealthValue_1 = 0x40;  // Energy / Hydration
		constexpr auto FallSafeHeight = 0x178; // 防摔死
	}

	// ValueStruct 内部
	namespace ValueStruct
	{
		constexpr auto Current = 0x0;
		constexpr auto Maximum = 0x4;
	}
}