.set LOCALID_NURSE, 1

DewfordTown_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, DewfordTown_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

DewfordTown_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_DEWFORD_TOWN
	call Common_EventScript_UpdateBrineyLocation
	end

DewfordTown_PokemonCenter_1F_EventScript_Nurse::
    setvar VAR_0x800B, LOCALID_NURSE

    checkflag FLAG_POKECENTER_DIFF_MAIN
    goto_if FALSE, Dewford_DoHeal

    compare VAR_POKECENTER_LAST, 1      @ Dewford = 1
    goto_if_eq Dewford_Deny
    compare VAR_POKECENTER_PREV, 1
    goto_if_eq Dewford_Deny

Dewford_DoHeal:
    call Common_EventScript_PkmnCenterNurse

    checkflag FLAG_HEALING_DONE
    goto_if FALSE, Dewford_End

    copyvar VAR_POKECENTER_PREV, VAR_POKECENTER_LAST
    setvar VAR_POKECENTER_LAST, 1       @ Dewford = 1

Dewford_End:
    waitmessage
    waitbuttonpress
    release
    end

Dewford_Deny:
    lock
    faceplayer
    msgbox gText_Nurse_CannotHeal, MSGBOX_DEFAULT
    release
    end


DewfordTown_PokemonCenter_1F_EventScript_PokefanF::
	msgbox DewfordTown_PokemonCenter_1F_Text_StoneCavern, MSGBOX_NPC
	end

DewfordTown_PokemonCenter_1F_EventScript_Man::
	msgbox DewfordTown_PokemonCenter_1F_Text_FaintedMonCanUseHM, MSGBOX_NPC
	end

DewfordTown_PokemonCenter_1F_Text_StoneCavern:
	.string "There's a stone cavern at the edge\n"
	.string "of town.\p"
	.string "I've heard you can find rare stones\n"
	.string "there.$"

DewfordTown_PokemonCenter_1F_Text_FaintedMonCanUseHM:
	.string "Even if a POKéMON faints and can't\n"
	.string "battle, it can still use a move learned\l"
	.string "from a HIDDEN MACHINE (HM).$"

