#include "Weapons.h"

std::vector<int> Weapons::WeaponGroups[8] =
{
	{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 34, 36}, // Melee
	{12, 13, 14, 15, 16}, // Projectiles
	{17, 18}, // Pistols
	{19, 20, 21}, // Shotguns
	{22, 23, 24, 25}, // Submachine guns
	{26, 27}, // Assault rifles
	{28, 29}, // Sniper rifles
	{30, 31, 32, 33, 35} // Heavy weapons
};
int __fastcall Weapons::GiveRandomizedWeapon(CPed* ped, void* edx, eWeaponType weapon, int ammo, bool likeUnused)
{
	if (ped->IsPlayer() || ped->m_nModelIndex == -1)
	{
		ped->GiveWeapon((eWeaponType)weapon, ammo, likeUnused);
		return weapon;
	}

	int newWeapon = GetRandomWeapon();

	int weaponModel = CWeaponInfo::GetWeaponInfo((eWeaponType)newWeapon)->m_nModelId;

	// Load the weapon model before setting it
	if (!IsModelLoaded(weaponModel))
		LoadModel(weaponModel);

	int origSlot = CWeaponInfo::GetWeaponInfo((eWeaponType)weapon)->m_WeaponSlot;
	int newSlot = CWeaponInfo::GetWeaponInfo((eWeaponType)newWeapon)->m_WeaponSlot;

	CWeaponInfo::GetWeaponInfo((eWeaponType)newWeapon)->m_WeaponSlot = origSlot;

	ped->GiveWeapon((eWeaponType)newWeapon, ammo, likeUnused);
	ped->m_nActiveWeaponSlot = origSlot;

	CWeaponInfo::GetWeaponInfo((eWeaponType)newWeapon)->m_WeaponSlot = newSlot;
	return newWeapon;
}
void __fastcall Weapons::SetCurrentWeapon(CPed* ped, void* edx, eWeaponType weapon)
{
	int newSlot = CWeaponInfo::GetWeaponInfo(weapon)->m_WeaponSlot;

	// Player and cop models
	if (ped->m_nModelIndex > -2 && ped->m_nModelIndex < 5)
	{
		// The Shootist + Shooting Range Fix
		if (GetThreadName() == std::string("bank2") || GetThreadName() == std::string("shoot"))
		{
			if (ped->IsPlayer() && weapon == 3)
			{
				ped->SetCurrentWeapon(CWeaponInfo::GetWeaponInfo((eWeaponType)17)->m_WeaponSlot);
				return;
			}
		}
		ped->SetCurrentWeapon(newSlot);
		return;
	}
	ped->SetCurrentWeapon(ped->m_nActiveWeaponSlot);
}
int Weapons::GetRandomWeapon()
{
	int weapon = 0;
	if (Config::weapons.ReduceMeleeWeaponsEnabled)
	{
		int weaponGroup = RandomNumber(0, 7);
		while ((weapon = WeaponGroups[weaponGroup][RandomNumber(0, WeaponGroups[weaponGroup].size() - 1)], IsBlacklistedWeapon(weapon)));

		return weapon;
	}
	while ((weapon = RandomNumber(1, 36), IsBlacklistedWeapon(weapon)));
	return weapon;
}
bool Weapons::IsBlacklistedWeapon(int weaponID)
{
	switch (weaponID)
	{
	case 16:
		if (Config::weapons.RocketEnabled)
			return false;
		return true;
	case 14:
		if (Config::weapons.tearGasEnabled)
			return false;
		return true;
	case 13:
	case 35:
		return true;
	}
	return false;
}
void Weapons::FixPedsWithRPG(CProjectileInfo* projectile)
{
	if (projectile->ms_apProjectile[0].pSource)
	{
		projectile->Update();
		return;
	}
	projectile->RemoveAllProjectiles();
}
void Weapons::Initialise()
{
	if (Config::weapons.Enabled)
	{
		// CPed::GiveWeapon
		for (int addr : {0x406CC7, 0x429A34, 0x429CE5, 0x431C54, 0x452251,
			0x4BED62, 0x4ED773, 0x4EF6F9, 0x4EF79D, 0x4FFCCA, 0x4FFD66,
			0x50EE54, 0x50F24B, 0x5B897A, 0x5B89CE, 0x5D49B3, 0x60336B, 0x60343B,
			0x603F64, 0x630090})
			plugin::patch::RedirectCall(addr, GiveRandomizedWeapon);

		// CPed::SetCurrentWeapon
		for (int addr : {0x4440D5, 0x45241A, 0x452440, 0x4EB761, 0x452259,
			0x4EC234, 0x4EC2DB, 0x4ED63D, 0x4ED7DD, 0x4ED84E, 0x4ED8C8, 0x4EF461, 
			0x4EF7A5, 0x4F5AF3, 0x4FF688, 0x4FF70A, 0x4FF769, 0x4FF8F4, 0x50F254,
			0x51C841, 0x51C85B, 0x520B30, 0x534472, 0x53B70B, 0x53B9C8, 0x5D49D3,
			0x603493, 0x603FBC, 0x6300BB})
			plugin::patch::RedirectCall(addr, SetCurrentWeapon);

		plugin::patch::RedirectCall(0x5D4DBA, FixPedsWithRPG);

		/* Used for getting current thread.
		Currently only used for weapon randomizer */
		plugin::patch::RedirectCall(0x608C27, Functions::StartMission);
	}
}