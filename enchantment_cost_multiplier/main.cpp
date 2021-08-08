#include "obse/PluginAPI.h"
#include "obse/CommandTable.h"

#include "obse/GameAPI.h"

#include "obse/ParamInfos.h"
#include "obse/Script.h"
#include "obse/GameObjects.h"
#include <string>
#include "obse_common/SafeWrite.cpp"

float g_fEnchantmentCostMult = 1.f;
int g_iMinCost = 0;
int g_iMaxCost = 0;
bool g_bCapInfinite = false;
bool g_bReplaceGetEnchCost = true;
bool g_bHook5FFE23 = true;
bool g_bHook5471F7 = true;

IDebugLog		gLog("enchantment_cost_multiplier.log");
PluginHandle	g_pluginHandle = kPluginHandle_Invalid;

float __stdcall RescaleCost(float originalCost)
{
	float f = originalCost;

	if (g_fEnchantmentCostMult != 1)
	{
		f *= g_fEnchantmentCostMult;
		f = std::floorf(f);
	}

	// cap to min and max values
	if (g_iMinCost > 0)
	{
		if (originalCost > 0 || g_bCapInfinite)
		{
			f = std::fmax(f, g_iMinCost);
		}
	}
	if (g_iMaxCost > 0)
	{
		f = std::fmin(f, g_iMaxCost);
	}

	return f;
}

static const UInt32 kHook_5F4570 = 0x5F4570;
static const UInt32 kHook_5F4570_Return = 0x5F4576;

void __declspec(naked) Hook_5F4570()
{
	__asm {
		call edx

		sub esp, 4
		fstp dword ptr [esp]
		call RescaleCost

		fstp dword ptr [esp+20h]
		jmp kHook_5F4570_Return
	}
}

static const UInt32 kHook_60CB05 = 0x60CB05;
static const UInt32 kHook_60CB05_Return = 0x60CB0B;

void __declspec(naked) Hook_60CB05()
{
	__asm {
		call eax

		sub esp, 4
		fstp dword ptr[esp]
		call RescaleCost

		FSTP DWORD PTR SS : [ESP + 0x1C]
		jmp kHook_60CB05_Return
	}
}

static const UInt32 kHook_5FC8FA = 0x5FC8FA;
static const UInt32 kHook_5FC8FA_Return = 0x5FC900;

void __declspec(naked) Hook_5FC8FA()
{
	__asm {
		call edx

		sub esp, 4
		fstp dword ptr[esp]
		call RescaleCost

		fstp dword ptr [esp + 10h]
		jmp kHook_5FC8FA_Return
	}
}

static const UInt32 kHook_5B479F = 0x5B479F;
static const UInt32 kHook_5B479F_Return = 0x5B47A5;

void __declspec(naked) Hook_5B479F()
{
	__asm {
		call edx

		sub esp, 4
		fstp dword ptr[esp]
		call RescaleCost

		fstp dword ptr [esp + 1Ch]
		jmp kHook_5B479F_Return
	}
}

static const UInt32 kHook_5E496F = 0x5E496F;
static const UInt32 kHook_5E496F_Return = 0x5E4975;

void __declspec(naked) Hook_5E496F()
{
	__asm {
		call edx

		sub esp, 4
		fstp dword ptr[esp]
		call RescaleCost

		fstp dword ptr [esp + 0Ch]
		jmp kHook_5E496F_Return
	}
}

static const UInt32 kHook_5FFE23 = 0x5FFE23;
static const UInt32 kHook_5FFE23_Return = 0x5FFE29;

void __declspec(naked) Hook_5FFE23()
{
	__asm {
		call edx

		sub esp, 4
		fstp dword ptr[esp]
		call RescaleCost

		fcomp qword ptr [esp + 40h]
		jmp kHook_5FFE23_Return
	}
}

static const UInt32 kHook_5471F7 = 0x5471F7;
static const UInt32 kHook_5471F7_Return = 0x5471FD;

void __declspec(naked) Hook_5471F7()
{
	__asm {
		call edx

		sub esp, 4
		fstp dword ptr[esp]
		call RescaleCost

		fstp dword ptr [esp + 10h]
		jmp kHook_5471F7_Return
	}
}

static const UInt32 kHook_65768F = 0x65768F;
static const UInt32 kHook_65768F_Return = 0x657695;

void __declspec(naked) Hook_65768F()
{
	__asm {
		call eax

		sub esp, 4
		fstp dword ptr [esp]
		call RescaleCost

		fcomp qword ptr [esp + 14h]
		jmp kHook_65768F_Return
	}
}

static const UInt32 kHook_5E4788 = 0x5E4788;
static const UInt32 kHook_5E4788_Return = 0x5E478E;

void __declspec(naked) Hook_5E4788()
{
	__asm {
		call edx

		sub esp, 4
		fstp dword ptr [esp]
		call RescaleCost

		push ecx
		fstp dword ptr [esp]
		jmp kHook_5E4788_Return
	}
}

static const UInt32 kHook_5ED5F6  = 0x5ED5F6;
static const UInt32 kHook_5ED5F6_Return = 0x5ED5FC;

void __declspec(naked) Hook_5ED5F6()
{
	__asm {
		call edx

		sub esp, 4
		fstp dword ptr [esp]
		call RescaleCost

		fcomp qword ptr [esp + 08h]
		jmp kHook_5ED5F6_Return
	}
}

static const UInt32 kHook_612B6F = 0x612B6F;
static const UInt32 kHook_612B6F_Return = 0x612B75;

void __declspec(naked) Hook_612B6F()
{
	__asm {
		call eax

		sub esp, 4
		fstp dword ptr[esp]
		call RescaleCost

		fcomp qword ptr[esp + 18h]
		jmp kHook_612B6F_Return
	}
}

static const UInt32 kHook_612B98 = 0x612B98;
static const UInt32 kHook_612B98_Return = 0x612B9E;

void __declspec(naked) Hook_612B98()
{
	__asm {
		call eax

		sub esp, 4
		fstp dword ptr[esp]
		call RescaleCost

		fcomp qword ptr[esp + 18h]
		jmp kHook_612B98_Return
	}
}

void HookEnchantMult()
{	
	//WriteRelJump(kHook_5FC8FA, (UInt32)&Hook_5FC8FA); // apply spell cost
	//WriteRelJump(kHook_5F4570, (UInt32)&Hook_5F4570); // checks if you have enough magicka to cast a spell
	
	WriteRelJump(kHook_5E4788, (UInt32)&Hook_5E4788); // apply enchantment cost - melee
	WriteRelJump(kHook_5E496F, (UInt32)&Hook_5E496F); // apply enchantment cost - staff
	WriteRelJump(kHook_60CB05, (UInt32)&Hook_60CB05); // apply enchantment cost - bow
	
	WriteRelJump(kHook_65768F, (UInt32)&Hook_65768F); // fcomp, melee vfx
	WriteRelJump(kHook_5ED5F6, (UInt32)&Hook_5ED5F6); // fcomp, staff vfx
	
	WriteRelJump(kHook_5B479F, (UInt32)&Hook_5B479F); // displayed uses in inventory	

	_MESSAGE("Hooked");

	if (g_bHook5FFE23)
	{
		WriteRelJump(kHook_5FFE23, (UInt32)&Hook_5FFE23); // fcomp, no clue - called in melee
		_MESSAGE("	Also hooked 5FFE23");
	}

	if (g_bHook5471F7)
	{
		WriteRelJump(kHook_5471F7, (UInt32)&Hook_5471F7); // no clue - staff?
		_MESSAGE("	Also hooked 5471F7");
	}

	if (g_fEnchantmentCostMult != 1)
	{
		_MESSAGE("Enchantment Cost Mult: %f", g_fEnchantmentCostMult);
		_MESSAGE("	...which means that uses are multiplied by %f", 1.0f / g_fEnchantmentCostMult);
	}
	if (g_iMinCost > 0)
	{
		_MESSAGE("Min enchantment cost: %i", g_iMinCost);
		if (g_bCapInfinite)
		{
			_MESSAGE("	Capping cost of originally infinite enchantments as well");
		}
	}
	if (g_iMaxCost > 0)
	{
		_MESSAGE("Max enchantment cost: %i", g_iMaxCost);
	}
}

enum
{
	kMagic_ItemType = 0,
	kMagic_EffectCount,
	kMagic_IsAutoCalc,
	kMagic_EffectCode = 50,
	kMagic_EffectMagnitude,
	kMagic_EffectArea,
	kMagic_EffectDuration,
	kMagic_EffectRange,
	kMagic_EffectActorValue,
	kMagic_EffectIsScripted,
	kMagic_EffectScript = 75,
	kMagic_EffectScriptVisualEffect,
	kMagic_EffectScriptSchool,
	kMagic_EffectScriptHostile,
	kMagic_EffectScriptName,
	kMagic_SpellType = 100,
	kMagic_SpellMagickaCost,
	kMagic_SpellMasteryLevel,
	kMagic_SpellSchool,
	kMagic_SpellExplodes,
	kMagic_EnchantmentType = 150,
	kMagic_EnchantmentCharge,
	kMagic_EnchantmentCost,
};

static bool GetEnchantmentItemValueMOD(EnchantmentItem* enchantItem, UInt32 valueType, double* result)
{
	if (!enchantItem || !result) return true;

	switch (valueType)
	{
	case kMagic_EnchantmentType:
	{
		*result = enchantItem->enchantType;
		break;
	}

	case kMagic_EnchantmentCharge:
	{
		*result = enchantItem->charge;
		break;
	}

	case kMagic_EnchantmentCost:
	{
		if (!enchantItem->IsAutoCalc())
		{
			*result = enchantItem->cost;
		}
		else
		{
			*result = enchantItem->magicItem.list.GetMagickaCost();
		}
		*result = RescaleCost(*result); // rescale 
		break;
	}
	default:
		break;
	}
	return true;
}

bool Cmd_GetEnchantmentCostMOD_Execute(COMMAND_ARGS)
{
	*result = 0;
	MagicItem* magicItem = NULL;
	if (!ExtractArgs(paramInfo, arg1, opcodeOffsetPtr, thisObj, arg3, scriptObj, eventList, &magicItem)) return true;

	EnchantmentItem* enchantmentItem = (EnchantmentItem*)Oblivion_DynamicCast(magicItem, 0, RTTI_MagicItem, RTTI_EnchantmentItem, 0);
	if (enchantmentItem)
	{
		return GetEnchantmentItemValueMOD(enchantmentItem, kMagic_EnchantmentCost, result);
	}

	return true;
}

DEFINE_COMMAND_PLUGIN(GetEnchantmentCostMOD, , 0, 1, kParams_OneMagicItem);

bool Replace(OBSECommandTableInterface* commandTableInterface, UInt32 opcodeToReplace, CommandInfo* replaceWith)
{
	const CommandInfo* constCommand = commandTableInterface->GetByOpcode(opcodeToReplace);
	if (constCommand)
	{
		CommandInfo* command = const_cast<CommandInfo*>(constCommand); // forgive me for I have sinned
		*command = *replaceWith;
		command->opcode = opcodeToReplace;
		return true;
	}
	return false;
}

extern "C" {

bool OBSEPlugin_Query(const OBSEInterface * obse, PluginInfo * info)
{
	_MESSAGE("Plugin query...");

	// fill out the info structure
	info->infoVersion = PluginInfo::kInfoVersion;
	info->name = "enchantment_cost_multiplier";
	info->version = 1;

	// version checks
	if(!obse->isEditor)
	{
		if(obse->obseVersion < OBSE_VERSION_INTEGER)
		{
			_ERROR("	OBSE version too old (got %08X expected at least %08X)", obse->obseVersion, OBSE_VERSION_INTEGER);
			return false;
		}

#if OBLIVION
		if(obse->oblivionVersion != OBLIVION_VERSION)
		{
			_ERROR("	Incorrect Oblivion version (got %08X need %08X)", obse->oblivionVersion, OBLIVION_VERSION);
			return false;
		}
#endif
	}
	else
	{
		_MESSAGE("	Not loading in editor");
		// don't load in editor
		return false;
	}

	// version checks pass
	_MESSAGE("	Plugin query passed");
	return true;
}

bool OBSEPlugin_Load(const OBSEInterface * obse)
{
	_MESSAGE("Enchantment Cost Multiplier version %u", 1);

	g_pluginHandle = obse->GetPluginHandle();

	//obse->SetOpcodeBase(0x28A8); // no need, not adding a new command

	char iniDir[MAX_PATH];

	GetModuleFileName(GetModuleHandle(NULL), iniDir, MAX_PATH);
	strcpy((char*)(strrchr(iniDir, '\\') + 1), "Data\\OBSE\\Plugins\\enchantment_cost_multiplier.ini");
	_MESSAGE("Loading settings from %s", iniDir);

	char enchantmentCostMultFloatBuffer[0x40];
	GetPrivateProfileString("Main", "fEnchantmentCostMult", "1.0000", enchantmentCostMultFloatBuffer, 0x3F, iniDir);
	g_fEnchantmentCostMult = atof(enchantmentCostMultFloatBuffer);
	if (g_fEnchantmentCostMult < 0)
	{
		g_fEnchantmentCostMult = 0;
	}

	g_iMinCost = GetPrivateProfileInt("Main", "iMinCost", 0, iniDir);
	g_iMaxCost = GetPrivateProfileInt("Main", "iMaxCost", 0, iniDir);
	g_bCapInfinite = GetPrivateProfileInt("Main", "bCapInfinite", 0, iniDir);
	g_bReplaceGetEnchCost = GetPrivateProfileInt("Main", "bReplaceGetEnchCost", 1, iniDir);

	g_bHook5FFE23 = GetPrivateProfileInt("Experimental", "bHook5FFE23", 0, iniDir);
	g_bHook5471F7 = GetPrivateProfileInt("Experimental", "bHook5471F7", 0, iniDir);

	if (g_fEnchantmentCostMult == 1 && g_iMinCost <= 0 && g_iMaxCost <= 0)
	{
		_MESSAGE("Not hooking because there's nothing to change!");
		return false;
	}
	
	HookEnchantMult();

	if (g_bReplaceGetEnchCost)
	{
		OBSECommandTableInterface* cmdIntfc = (OBSECommandTableInterface*)obse->QueryInterface(kInterface_CommandTable);
		if (cmdIntfc)
		{
			const CommandInfo* command = cmdIntfc->GetByName("GetEnchantmentCost");
			Replace(cmdIntfc, command->opcode, &kCommandInfo_GetEnchantmentCostMOD);
			_MESSAGE("Replaced OBSE command GetEnchantmentCost");
		}
	}

	return true;
}

};
