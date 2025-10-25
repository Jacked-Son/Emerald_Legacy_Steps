.set LOCALID_NURSE, 1

PacifidlogTown_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, PacifidlogTown_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

PacifidlogTown_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_PACIFIDLOG_TOWN
	end

PacifidlogTown_PokemonCenter_1F_EventScript_Nurse::
    # Keep vanilla param for Common nurse script
    setvar VAR_0x800B, LOCALID_NURSE

    # If difficulty OFF → normal flow
    checkflag FLAG_POKECENTER_DIFF_MAIN
    goto_if FALSE, Pacifidlog_DoHeal

    # Difficulty ON: block if this center is the last or previous used
    compare VAR_POKECENTER_LAST, 10      @ Pacifidlog = 10
    goto_if_eq Pacifidlog_Deny
    compare VAR_POKECENTER_PREV, 10
    goto_if_eq Pacifidlog_Deny

Pacifidlog_DoHeal:
    # Run the normal nurse behavior (handles lock/face/etc internally)
    call Common_EventScript_PkmnCenterNurse

    # Only record usage if a real heal completed
    checkflag FLAG_HEALING_DONE
    goto_if FALSE, Pacifidlog_End

    # Shift the rotating history: PREV <- LAST, LAST <- this center ID
    copyvar VAR_POKECENTER_PREV, VAR_POKECENTER_LAST
    setvar VAR_POKECENTER_LAST, 10       @ Pacifidlog = 10

Pacifidlog_End:
    waitmessage
    waitbuttonpress
    release
    end

Pacifidlog_Deny:
    # We didn’t call Common_..., so handle presentation here
    lock
    faceplayer
    msgbox gText_Nurse_CannotHeal, MSGBOX_DEFAULT
    release
    end

PacifidlogTown_PokemonCenter_1F_EventScript_Girl::
	msgbox PacifidlogTown_PokemonCenter_1F_Text_WhatColorTrainerCard, MSGBOX_NPC
	end

PacifidlogTown_PokemonCenter_1F_EventScript_Woman::
	msgbox PacifidlogTown_PokemonCenter_1F_Text_OnColonyOfCorsola, MSGBOX_NPC
	end

PacifidlogTown_PokemonCenter_1F_EventScript_OldMan::
	msgbox PacifidlogTown_PokemonCenter_1F_Text_AncestorsLivedOnBoats, MSGBOX_NPC
	end

PacifidlogTown_PokemonCenter_1F_Text_WhatColorTrainerCard:
	.string "What color is your TRAINER CARD?\n"
	.string "Mine's copper!$"

PacifidlogTown_PokemonCenter_1F_Text_OnColonyOfCorsola:
	.string "PACIFIDLOG TOWN floats on top of\n"
	.string "a colony of CORSOLA.\p"
	.string "If I told you that, would you believe\n"
	.string "me?$"

PacifidlogTown_PokemonCenter_1F_Text_AncestorsLivedOnBoats:
	.string "The ancestors of the people in\n"
	.string "PACIFIDLOG were said to have been\l"
	.string "born on boats and then lived and died \l"
	.string "aboard them.\p"
	.string "I understand that they lived that way\n"
	.string "because they were searching for\l"
	.string "something.$"

