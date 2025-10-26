.set LOCALID_NURSE, 1

PacifidlogTown_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, PacifidlogTown_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

PacifidlogTown_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_PACIFIDLOG_TOWN
	end

PacifidlogTown_PokemonCenter_1F_EventScript_Nurse::
    setvar VAR_0x800B, LOCALID_NURSE

    goto_if_unset FLAG_POKECENTER_DIFF_MAIN, Pacifidlog_DoHeal

    compare VAR_POKECENTER_LAST, 10      @ Pacifidlog = 10
    goto_if_eq Pacifidlog_Deny
    compare VAR_POKECENTER_PREV, 10
    goto_if_eq Pacifidlog_Deny

Pacifidlog_DoHeal:
    call Common_EventScript_PkmnCenterNurse

    goto_if_unset FLAG_HEALING_DONE, Pacifidlog_End

    copyvar VAR_POKECENTER_PREV, VAR_POKECENTER_LAST
    setvar VAR_POKECENTER_LAST, 10       @ Pacifidlog = 10
	end

Pacifidlog_End:
    end

Pacifidlog_Deny:
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

