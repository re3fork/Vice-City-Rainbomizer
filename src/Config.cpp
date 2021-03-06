#include "Config.h"

const std::string ConfigName = "Rainbomizer.cfg";

/* Annoyingly messy initialisers */
Config::ScriptedVehiclesRandomizer Config::script;
Config::RCVehiclesRandomizer Config::rc;
Config::TrafficRandomizer Config::traffic;
Config::WeaponRandomizer Config::weapons;
Config::ColourRandomizer Config::colours;
Config::VoiceLineRandomizer Config::voice;
Config::Autosave Config::autosave;
Config::ParkedVehiclesRandomizer Config::parked;
Config::PickupsRandomizer Config::pickups;
Config::ClothesRandomizer Config::clothes;

void ReadConfigBool(const std::string& key, const std::string& data, bool& value)
{
	if (data.find(key) != std::string::npos)
		value = data.find("true") != std::string::npos;
}
void ReadConfigInt(const std::string& key, const std::string& data, int& value)
{
	if (data.find(key) != std::string::npos)
	{
		std::stringstream stream;
		stream << data;

		std::string str;
		int val;

		while (!stream.eof())
		{
			stream >> str;
			if (std::stringstream(str) >> val)
			{
				value = val;
				break;
			}
		}
	}
}
void Config::ScriptedVehiclesRandomizer::Read(const std::string& line)
{
	ReadConfigBool("ScriptVehiclesRandomizer", line, Enabled);

	ReadConfigBool("OffroadMissions", line, offroadEnabled);
	ReadConfigBool("RCMissions", line, rcEnabled);
	ReadConfigBool("ChopperCheckpoints", line, chopperCheckpointEnabled);
	ReadConfigBool("PizzaBoy", line, pizzaBoyEnabled);
}
void Config::RCVehiclesRandomizer::Read(const std::string& line)
{
	ReadConfigBool("RandomizeRCVehicles", line, Enabled);
	ReadConfigBool("AllowPlayerToDriveRCVehicles", line, DriveRCVehiclesEnabled);
}
void Config::ParkedVehiclesRandomizer::Read(const std::string& line)
{
	ReadConfigBool("ParkedVehiclesRandomizer", line, Enabled);
}
void Config::ColourRandomizer::Read(const std::string& line)
{
	ReadConfigBool("RandomizeVehicleColours", line, vehicleEnabled);
	ReadConfigBool("RandomizeHUDColours", line, textEnabled);
	ReadConfigBool("RandomizeMarkerColours", line, markersEnabled);

	ReadConfigBool("RandomizePickupColours", line, pickupsEnabled);
	ReadConfigBool("RandomizeLazerScopeColour", line, lazerScopeEnabled);
	ReadConfigBool("RandomizeExplosionColours", line, explosionsEnabled);

	ReadConfigBool("RainbowHUDColours", line, rainbowTextEnabled);
	ReadConfigBool("VibrantStaticHUDColours", line, vibrantOnlyEnabled);
}
void Config::TrafficRandomizer::Read(const std::string& line)
{
	ReadConfigBool("TrafficRandomizer", line, Enabled);
	ReadConfigBool("RandomizeScriptedCopCars", line, scriptedCopCarsEnabled);
	ReadConfigBool("RandomizeRoadblocks", line, roadblocksEnabled);

	ReadConfigBool("DeadDodo", line, deadDodo);
	ReadConfigBool("AirTrain", line, airTrain);
}
void Config::WeaponRandomizer::Read(const std::string& line)
{
	ReadConfigBool("WeaponRandomizer", line, Enabled);
	ReadConfigBool("ReduceMeleeWeapons", line, ReduceMeleeWeaponsEnabled);
	ReadConfigBool("AllowRocketMissile", line, RocketEnabled);
	ReadConfigBool("AllowTearGas", line, tearGasEnabled);
}
void Config::PickupsRandomizer::Read(const std::string& line)
{
	ReadConfigBool("PickupsRandomizer", line, Enabled);
	ReadConfigBool("RandomizePedWeaponDrops", line, randomizePedDrops);

	ReadConfigBool("Weapons", line, weapons);
	ReadConfigBool("Health", line, health);
	ReadConfigBool("Armour", line, armour);
	ReadConfigBool("Adrenaline", line, adrenaline);
	ReadConfigBool("Bribes", line, bribes);
	ReadConfigBool("Cellphone", line, cellphone);
	ReadConfigBool("Briefcase", line, briefcase);
	ReadConfigBool("Keycard", line, keycard);
}
void Config::ClothesRandomizer::Read(const std::string& line)
{
	ReadConfigBool("ClothesRandomizer", line, Enabled);
}
void Config::VoiceLineRandomizer::Read(const std::string& line)
{
	ReadConfigBool("VoiceLineRandomizer", line, Enabled);
	ReadConfigBool("MatchSubtitles", line, MatchSubtitles);
	ReadConfigBool("LoopPhoneRingtone", line, loopEnabled);
}
void Config::Autosave::Read(const std::string& line)
{
	ReadConfigBool("Autosave", line, Enabled);
	ReadConfigInt("Slot", line, slot);

	if (slot < 1 || slot > 8)
		slot = 8;
}
void Config::WriteConfig()
{
	std::ofstream config;
	config.open(ConfigName);
	config << default_config;
	config.close();
}
void Config::Initialise()
{
	if (!std::filesystem::exists(ConfigName))
		WriteConfig();

	std::ifstream config;
	config.open(ConfigName);

	for (std::string str; std::getline(config, str); )
	{
		script.Read(str);
		rc.Read(str);
		parked.Read(str);
		traffic.Read(str);
		weapons.Read(str);
		colours.Read(str);
		autosave.Read(str);
		voice.Read(str);
		pickups.Read(str);
		clothes.Read(str);
	}
}