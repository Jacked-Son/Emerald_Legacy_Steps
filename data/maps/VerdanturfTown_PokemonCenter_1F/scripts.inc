.set LOCALID_NURSE, 1

VerdanturfTown_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, VerdanturfTown_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

VerdanturfTown_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_VERDANTURF_TOWN
	call Common_EventScript_UpdateBrineyLocation
	end

VerdanturfTown_PokemonCenter_1F_EventScript_Nurse::
    # Keep vanilla param for Common nurse script
    setvar VAR_0x800B, LOCALID_NURSE

    # If difficulty OFF → normal flow
    checkflag FLAG_POKECENTER_DIFF_MAIN
    goto_if FALSE, Verdanturf_DoHeal

    # Difficulty ON: block if this center is the last or previous used
    compare VAR_POKECENTER_LAST, 15      @ Verdanturf = 15
    goto_if_eq Verdanturf_Deny
    compare VAR_POKECENTER_PREV, 15
    goto_if_eq Verdanturf_Deny

Verdanturf_DoHeal:
    # Run the normal nurse behavior (handles lock/face/etc internally)
    call Common_EventScript_PkmnCenterNurse

    # Only record usage if a real heal completed
    checkflag FLAG_HEALING_DONE
    goto_if FALSE, Verdanturf_End

    # Shift the rotating history: PREV <- LAST, LAST <- this center ID
    copyvar VAR_POKECENTER_PREV, VAR_POKECENTER_LAST
    setvar VAR_POKECENTER_LAST, 15       @ Verdanturf = 15

Verdanturf_End:
    waitmessage
    waitbuttonpress
    release
    end

Verdanturf_Deny:
    # We didn’t call Common_..., so handle presentation here
    lock
    faceplayer
    msgbox gText_Nurse_CannotHeal, MSGBOX_DEFAULT
    release
    end

VerdanturfTown_PokemonCenter_1F_EventScript_Gentleman::
	msgbox VerdanturfTown_PokemonCenter_1F_Text_FaithInYourPokemon, MSGBOX_NPC
	end

VerdanturfTown_PokemonCenter_1F_EventScript_ExpertM::
	msgbox VerdanturfTown_PokemonCenter_1F_Text_VisitForBattleTent, MSGBOX_NPC
	end

VerdanturfTown_PokemonCenter_1F_Text_FaithInYourPokemon:
	.string "You can't consider yourself a real\n"
	.string "TRAINER if you don't have faith\l"
	.string "in your POKéMON.\p"
	.string "Only those people who can believe\n"
	.string "in their battling POKéMON can win\l"
	.string "through to the very end.$"

VerdanturfTown_PokemonCenter_1F_Text_VisitForBattleTent:
	.string "The reason why anyone would visit\n"
	.string "VERDANTURF…\p"
	.string "It's the BATTLE TENT. It goes without\n"
	.string "saying.\p"
	.string "Or is there somebody here that you\n"
	.string "came to see?$"

