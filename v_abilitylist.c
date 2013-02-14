#include "g_local.h"

void enableAbility (edict_t *ent, int index, int level, int max_level, int general);
void disableAbilities (edict_t *ent);
void setHardMax(edict_t *ent, int index);

#define INCREASED_SOFTMAX 20
#define DEFAULT_SOFTMAX 15
#define GENERAL_SOFTMAX 8

typedef struct 
{
	int index;
	int start;
	int softmax;
	int general;
}abildefinition_t;

typedef abildefinition_t* AbilList;

abildefinition_t GENERAL_abil[] = {
	{ VITALITY          , 0 , 10                , 1  },
	{ MAX_AMMO          , 0 , 10                , 1  },
	{ POWER_REGEN       , 0 , 8                 , 1  },
	{ WORLD_RESIST      , 0 , 1                 , 1  },
	{ AMMO_REGEN        , 0 , 10                , 1  },
	{ REGENERATION      , 0 , 5                 , 1  },
	{ STRENGTH          , 0 , 5                 , 1  },
	{ HASTE             , 0 , 5                 , 1  },
	{ RESISTANCE        , 0 , 5                 , 1  },
	{ SHELL_RESIST      , 0 , 1                 , 1  },
	{ BULLET_RESIST     , 0 , 1                 , 1  },
	{ SPLASH_RESIST     , 0 , 1                 , 1  },
	{ PIERCING_RESIST   , 0 , 1                 , 1  },
	{ ENERGY_RESIST     , 0 , 1                 , 1  },
	{ SCANNER           , 0 , 1                 , 1  },
	{-1, 0, 0, 0} // Guardian (Add skills above this)
};

abildefinition_t SOLDIER_abil[] = {
	{ STRENGTH          , 0 , INCREASED_SOFTMAX , 0  },
	{ RESISTANCE        , 0 , DEFAULT_SOFTMAX   , 0  },
	{ HA_PICKUP         , 0 , DEFAULT_SOFTMAX   , 0  },
	{ NAPALM            , 0 , DEFAULT_SOFTMAX   , 0  },
	{ SPIKE_GRENADE     , 0 , DEFAULT_SOFTMAX   , 0  },
	{ EMP               , 0 , DEFAULT_SOFTMAX   , 0  },
	{ MIRV              , 0 , DEFAULT_SOFTMAX   , 0  },
	{ CREATE_QUAD       , 0 , 1                 , 0  },
	{ CREATE_INVIN      , 0 , 1                 , 0  },
	{ GRAPPLE_HOOK      , 3 , 3                 , 0  },
	{-1, 0, 0, 0} // Guardian (Add skills above this)
};

abildefinition_t KNIGHT_abil[] = { // KNIGHT
	{ ARMOR_UPGRADE     , 0 , 10                , 0  },
	{ REGENERATION      , 0 , DEFAULT_SOFTMAX   , 0  },
	{ POWER_SHIELD      , 0 , DEFAULT_SOFTMAX   , 0  },
	{ ARMOR_REGEN       , 0 , DEFAULT_SOFTMAX   , 0  },
	{ EXPLODING_ARMOR   , 0 , DEFAULT_SOFTMAX   , 0  },
	{ BEAM              , 0 , INCREASED_SOFTMAX , 0  },
	{ PLASMA_BOLT       , 0 , DEFAULT_SOFTMAX   , 0  },
	{ SHIELD            , 1 , 1                 , 0  },
	{ BOOST_SPELL       , 1 , 1                 , 0  },
	{-1, 0, 0, 0} // Guardian (Add skills above this)
};

abildefinition_t VAMPIRE_abil[] = { // VAMPIRE
	{ VAMPIRE           , 0 , DEFAULT_SOFTMAX   , 0  },
	{ GHOST             , 0 , DEFAULT_SOFTMAX   , 0  },
	{ LIFE_DRAIN        , 0 , DEFAULT_SOFTMAX   , 0  },
	{ FLESH_EATER       , 0 , DEFAULT_SOFTMAX   , 0  },
	{ CORPSE_EXPLODE    , 0 , DEFAULT_SOFTMAX   , 0  },
	{ MIND_ABSORB       , 0 , DEFAULT_SOFTMAX   , 0  },
	{ AMMO_STEAL        , 0 , DEFAULT_SOFTMAX   , 0  },
	{ CLOAK             , 1 , 10                , 0  },
	{-1, 0, 0, 0} // Guardian (Add skills above this)
};

abildefinition_t NECROMANCER_abil[] = { // NECROMANCER
	{ MONSTER_SUMMON    , 0 , INCREASED_SOFTMAX , 0  },
	{ HELLSPAWN         , 0 , INCREASED_SOFTMAX , 0  },
	{ PLAGUE            , 0 , DEFAULT_SOFTMAX   , 0  },
	{ AMP_DAMAGE        , 0 , DEFAULT_SOFTMAX   , 0  },
	{ CRIPPLE           , 0 , DEFAULT_SOFTMAX   , 0  },
	{ CURSE             , 0 , DEFAULT_SOFTMAX   , 0  },
	{ WEAKEN            , 0 , DEFAULT_SOFTMAX   , 0  },
	{ CONVERSION        , 0 , DEFAULT_SOFTMAX   , 0  },
	{ JETPACK           , 1 , 1                 , 0  },
	{-1, 0, 0, 0} // Guardian (Add skills above this)
};

abildefinition_t ENGINEER_abil[] = { // ENGINEER
	{ PROXY             , 0 , DEFAULT_SOFTMAX   , 0  },
	{ BUILD_SENTRY      , 0 , INCREASED_SOFTMAX , 0  },
	{ SUPPLY_STATION    , 0 , DEFAULT_SOFTMAX   , 0  },
	{ BUILD_LASER       , 0 , DEFAULT_SOFTMAX   , 0  },
	{ MAGMINE           , 0 , INCREASED_SOFTMAX , 0  },
	{ CALTROPS          , 0 , DEFAULT_SOFTMAX   , 0  },
	{ AUTOCANNON        , 0 , DEFAULT_SOFTMAX   , 0  },
	{ DETECTOR          , 0 , DEFAULT_SOFTMAX   , 0  },
	{ DECOY             , 0 , DEFAULT_SOFTMAX   , 0  },
	{ ANTIGRAV          , 1 , 1                 , 0  },
	{-1, 0, 0, 0} // Guardian (Add skills above this)
};

abildefinition_t MAGE_abil[] = { // MAGE
	{ MAGICBOLT         , 0 , DEFAULT_SOFTMAX   , 0  },
	{ NOVA              , 0 , DEFAULT_SOFTMAX   , 0  },
	{ BOMB_SPELL        , 0 , DEFAULT_SOFTMAX   , 0  },
	{ FORCE_WALL        , 0 , DEFAULT_SOFTMAX   , 0  },
	{ LIGHTNING         , 0 , DEFAULT_SOFTMAX   , 0  },
	{ METEOR            , 0 , DEFAULT_SOFTMAX   , 0  },
	{ FIREBALL          , 0 , DEFAULT_SOFTMAX   , 0  },
	{ LIGHTNING_STORM   , 0 , DEFAULT_SOFTMAX   , 0  },
	{ TELEPORT          , 1 , 1                 , 0  },
	{-1, 0, 0, 0} // Guardian (Add skills above this)
};

abildefinition_t CLERIC_abil[] = { // CLERIC
	{ SALVATION         , 0 , DEFAULT_SOFTMAX   , 0  },
	{ HEALING           , 0 , DEFAULT_SOFTMAX   , 0  },
	{ BLESS             , 0 , DEFAULT_SOFTMAX   , 0  },
	{ YIN               , 0 , DEFAULT_SOFTMAX   , 0  },
	{ YANG              , 0 , DEFAULT_SOFTMAX   , 0  },
	{ HAMMER            , 0 , DEFAULT_SOFTMAX   , 0  },
	{ DEFLECT           , 0 , DEFAULT_SOFTMAX   , 0  },
	{ LOWER_RESIST      , 0 , DEFAULT_SOFTMAX   , 0  },
	{ DOUBLE_JUMP       , 1 , 1                 , 0  },
	{-1, 0, 0, 0} // Guardian (Add skills above this)
};

abildefinition_t POLTERGEIST_abil[] = { // POLTERGEIST
	{ BERSERK           , 1 , INCREASED_SOFTMAX , 0  },
	{ CACODEMON         , 1 , INCREASED_SOFTMAX , 0  },
	{ BLOOD_SUCKER      , 1 , INCREASED_SOFTMAX , 0  },
	{ BRAIN             , 1 , INCREASED_SOFTMAX , 0  },
	{ FLYER             , 1 , INCREASED_SOFTMAX , 0  },
	{ MUTANT            , 1 , INCREASED_SOFTMAX , 0  },
	{ TANK              , 1 , INCREASED_SOFTMAX , 0  },
	{ MEDIC             , 1 , INCREASED_SOFTMAX , 0  },
	{ GHOST             , 99, 99                , 0  },
	{ MORPH_MASTERY     , 1 , 1                 , 0  },
	{ MONSTER_SUMMON    , 0 , 1                 , 0  },
	{-1, 0, 0, 0} // Guardian (Add skills above this)
};

abildefinition_t SHAMAN_abil[] = { // SHAMAN
	{ FIRE_TOTEM        , 0 , INCREASED_SOFTMAX , 0  },
	{ WATER_TOTEM       , 0 , INCREASED_SOFTMAX , 0  },
	{ AIR_TOTEM         , 0 , INCREASED_SOFTMAX , 0  },
	{ EARTH_TOTEM       , 0 , INCREASED_SOFTMAX , 0  },
	{ DARK_TOTEM        , 0 , INCREASED_SOFTMAX , 0  },
	{ NATURE_TOTEM      , 0 , INCREASED_SOFTMAX , 0  },
	{ FURY              , 0 , DEFAULT_SOFTMAX   , 0  },
	{ HASTE             , 0 , 5                 , 0  },
	{ SUPER_SPEED       , 1 , 1                 , 0  },
	{ TOTEM_MASTERY     , 1 , 1                 , 0  },
	{-1, 0, 0, 0} // Guardian (Add skills above this)
};

abildefinition_t ALIEN_abil[] = { // ALIEN
	{ SPIKER            , 0 , DEFAULT_SOFTMAX   , 0  },
	{ OBSTACLE          , 0 , DEFAULT_SOFTMAX   , 0  },
	{ GASSER            , 0 , DEFAULT_SOFTMAX   , 0  },
	{ HEALER            , 0 , DEFAULT_SOFTMAX   , 0  },
	{ SPORE             , 0 , DEFAULT_SOFTMAX   , 0  },
	{ ACID              , 0 , DEFAULT_SOFTMAX   , 0  },
	{ SPIKE             , 0 , DEFAULT_SOFTMAX   , 0  },
	{ COCOON            , 0 , DEFAULT_SOFTMAX   , 0  },
	{ BLACKHOLE         , 1 , 1                 , 0  },
	{-1, 0, 0, 0} // Guardian (Add skills above this)
};

abildefinition_t WEAPONMASTER_abil[] = {
	{-1, 0, 0, 0} // Guardian (Add skills above this)
};

abildefinition_t KAMIKAZE_abil[] = { // KAMIKAZE
	{ SELFDESTRUCT      , 0 , DEFAULT_SOFTMAX   , 0  },
	{ HA_PICKUP         , 1 , DEFAULT_SOFTMAX   , 0  },
	{ PROXY             , 0 , DEFAULT_SOFTMAX   , 0  },
	{ CREATE_INVIN      , 0 , 1                 , 0  },
	{ AMNESIA           , 0 , DEFAULT_SOFTMAX   , 0  },
	{ MAGMINE           , 0 , DEFAULT_SOFTMAX   , 0  },
	{ FLASH             , 1 , 1                 , 0  },
	{ BOOST_SPELL       , 1 , 1                 , 0  },
	{-1, 0, 0, 0} // Guardian (Add skills above this)
};

AbilList ablist [] = 
{
	GENERAL_abil,
	SOLDIER_abil,
	POLTERGEIST_abil,
	VAMPIRE_abil,
	MAGE_abil,
	ENGINEER_abil,
	KNIGHT_abil,
	CLERIC_abil,
	NECROMANCER_abil,
	SHAMAN_abil,
	ALIEN_abil,
	WEAPONMASTER_abil,
	KAMIKAZE_abil
};


void AssignAbilities(edict_t *ent)
{
	abildefinition_t *first = ablist[0];

	disableAbilities(ent);

	// enable general skills
	while (first->index != -1)
	{
		//gi.dprintf("enabled ability %s\n", GetAbilityString(first->index));
		enableAbility(ent, first->index, first->start, first->softmax, first->general);
		first++;
	}

	// enable all skills (weaponmaster/ab or generalabmode is on)
	if (ent->myskills.class_num == CLASS_WEAPONMASTER || generalabmode->value)
	{
		int i;
		for (i = 0; i < CLASS_MAX; i++)
		{
			first = ablist[i+1];
			while (first->index != -1)
			{
				int real_max = first->softmax;
				
				if (first->softmax > 10) // a 15 softmax? dump down to 8
					real_max = 8;

				enableAbility(ent, first->index, 0, first->softmax, 1);
				first++;
			}
		}
	}

	// enable class skills
	if (ent->myskills.class_num != CLASS_WEAPONMASTER)
	{
		first = ablist[ent->myskills.class_num];
		while (first->index != -1)
		{
			//gi.dprintf("enabled ability %s\n", GetAbilityString(first->index));
			enableAbility(ent, first->index, first->start, first->softmax, first->general);
			first++;
		}
	}
}

void setHardMax(edict_t *ent, int index)
{
	switch(index)
	{
		//Skills that max at level 1
		case ID:
		case WORLD_RESIST:
		case BULLET_RESIST:
		case SHELL_RESIST:
		case ENERGY_RESIST:
		case PIERCING_RESIST:
		case SPLASH_RESIST:
		//case FREEZE_SPELL:
		case CLOAK:
		case CREATE_QUAD:
		case CREATE_INVIN:
		case BOOST_SPELL:
		case SUPER_SPEED:
		case ANTIGRAV:
		case WEAPON_KNOCK:
		case TELEPORT:
		case JETPACK:
		case SHIELD:
			ent->myskills.abilities[index].hard_max = 1; break;

			// Special cases for the non-general ability mode.

		case REGENERATION:
			if (!generalabmode->value)
			{
				if (ent->myskills.abilities[index].general_skill)
					ent->myskills.abilities[index].hard_max = 15;
				break;
			}
		case HASTE:
		case AMMO_REGEN:
			ent->myskills.abilities[index].hard_max = 5;
			break;
		case STRENGTH:
		case RESISTANCE:
			if (!generalabmode->value)
			{
				if (ent->myskills.abilities[index].general_skill && 
					!ent->myskills.class_num == CLASS_SOLDIER)
				{					
					ent->myskills.abilities[index].hard_max = 15;
					
				}
				else
				{
					ent->myskills.abilities[index].hard_max = 30;					
				}	
				break;			
			}

		//Everything else
		default:
			if (GetAbilityUpgradeCost(index) < 2)
			{
				if (!generalabmode->value)
				{
					if (ent->myskills.class_num == CLASS_WEAPONMASTER)
					{
						ent->myskills.abilities[index].hard_max = ent->myskills.abilities[index].max_level * 2; break;
					}
					else
					{
						ent->myskills.abilities[index].hard_max = ent->myskills.abilities[index].max_level * 4; break;
					}
					
				}else
					ent->myskills.abilities[index].hard_max = ent->myskills.abilities[index].max_level * 1.5; break;
			}
			else 
				ent->myskills.abilities[index].hard_max = 1; break;
	}	
}

void enableAbility (edict_t *ent, int index, int level, int max_level, int general)
{
	ent->myskills.abilities[index].disable = false;

	// we can pass this function -1 if we don't want to alter these variables
	if (max_level != -1)
		ent->myskills.abilities[index].max_level = max_level;

	if (level != -1)
	{
		ent->myskills.abilities[index].level = level;
		ent->myskills.abilities[index].current_level = level;
	}

	ent->myskills.abilities[index].general_skill = general;
	setHardMax(ent, index);
}

void disableAbilities (edict_t *ent)
{
	int i;

	for (i=0; i<MAX_ABILITIES; ++i)
	{
		ent->myskills.abilities[i].disable = true;
		ent->myskills.abilities[i].hidden = false;
	}
}