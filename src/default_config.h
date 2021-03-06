#pragma once
const char default_config[]
= R"(# GTA Vice City Rainbomizer Configuration #

###########################################
# Script Vehicles Randomizer
ScriptVehiclesRandomizer = true

# Allow certain side missions to be activated by any vehicle

OffroadMissions = true # (Trial by Dirt (bikes only), Test Track (cars only), PCJ Playground, Cone Crazy)
RCMissions = true # (RC Raider Pickup, RC Bandit Race, RC Baron Race)
ChopperCheckpoints = true # (Will only be activated by helicopters)
PizzaBoy = true # (Activate and use any vehicle for pizza boy)

###########################################
# RC Vehicles Randomizer
RandomizeRCVehicles = true

# Experimental - this feature may cause crashes, softlocks or possibly lag
# It is currently known that you are unable to re-enter RC vehicles once exited

AllowPlayerToDriveRCVehicles = false

###########################################
# Parked Vehicles Randomizer
ParkedVehiclesRandomizer = true

###########################################
# Colour Randomizer

RandomizeVehicleColours = true
RandomizeHUDColours = true
RandomizeMarkerColours = true

RandomizePickupColours = true
RandomizeLazerScopeColour = true
RandomizeExplosionColours = true

# If both below are false with HUD colours enabled, they will be normal random colours

RainbowHUDColours = false
VibrantStaticHUDColours = false

###########################################
# Traffic Randomizer
TrafficRandomizer = true

# Randomizes police vehicles which intercept you on some roads
RandomizeScriptedCopCars = true

RandomizeRoadblocks = true

# Additional vehicles
DeadDodo = true
AirTrain = true

###########################################
# Weapon Randomizer
WeaponRandomizer = true

# Randomizes the weapons differently to reduce the chances of peds being given melee weapons

ReduceMeleeWeapons = false

# Allows peds to be given the missile - WARNING: When dropped this flashes heavily, may effect certain
# people with epilepsy or sensitivity

AllowRocketMissile = false

# Tear gas can sometimes cause lag when used by peds
AllowTearGas = true

###########################################
# Pickups Randomizer

# Randomizes weapons, health, armour, adrenaline, bribe stars and mission pickups
# This feature is safe to use, though pickups are saved to the save file
 
PickupsRandomizer = true

# Randomizes the weapons dropped by dead peds
RandomizePedWeaponDrops = true

# Allowed pickup types
Weapons = true
Health = true
Armour = true
Adrenaline = true
Bribes = true
Cellphone = true
Briefcase = true
Keycard = true

###########################################
# Clothes Randomizer
ClothesRandomizer = true

###########################################
# Voice Line Randomizer
VoiceLineRandomizer = true

# Matches the subtitles to the randomized voice line
MatchSubtitles = true

# Phonecall ringtones will loop the same sound over being re-randomized
LoopPhoneRingtone = true

###########################################
# Autosave
Autosave = true
Slot = 8)";