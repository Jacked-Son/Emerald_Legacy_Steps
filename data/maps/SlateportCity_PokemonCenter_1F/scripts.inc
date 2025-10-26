.set LOCALID_NURSE, 1

SlateportCity_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SlateportCity_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

SlateportCity_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_SLATEPORT_CITY
	call Common_EventScript_UpdateBrineyLocation
	end

SlateportCity_PokemonCenter_1F_EventScript_Nurse::
    setvar VAR_0x800B, LOCALID_NURSE

    goto_if_unset FLAG_POKECENTER_DIFF_MAIN, Slateport_DoHeal

    compare VAR_POKECENTER_LAST, 13      @ Slateport = 13
    goto_if_eq Slateport_Deny
    compare VAR_POKECENTER_PREV, 13
    goto_if_eq Slateport_Deny

Slateport_DoHeal:
    call Common_EventScript_PkmnCenterNurse

    goto_if_unset FLAG_HEALING_DONE, Slateport_End

    copyvar VAR_POKECENTER_PREV, VAR_POKECENTER_LAST
    setvar VAR_POKECENTER_LAST, 13       @ Slateport = 13
	end

Slateport_End:
    end

Slateport_Deny:
    lock
    faceplayer
    msgbox gText_Nurse_CannotHeal, MSGBOX_DEFAULT
    release
    end

SlateportCity_PokemonCenter_1F_EventScript_Sailor::
	msgbox SlateportCity_PokemonCenter_1F_Text_RaiseDifferentTypesOfPokemon, MSGBOX_NPC
	end

SlateportCity_PokemonCenter_1F_EventScript_Woman::
	msgbox SlateportCity_PokemonCenter_1F_Text_TradedMonWithFriend, MSGBOX_NPC
	end

SlateportCity_PokemonCenter_1F_Text_RaiseDifferentTypesOfPokemon:
	.string "Want a tip for battling?\p"
	.string "I'd say it's raising different kinds\n"
	.string "of POKéMON in a balanced manner.\p"
	.string "It's no good to make just one\n"
	.string "POKéMON strong.\p"
	.string "If it has a type disadvantage,\n"
	.string "it might not stand a chance.$"

SlateportCity_PokemonCenter_1F_Text_TradedMonWithFriend:
	.string "I trade POKéMON with my friends.\p"
	.string "If a traded POKéMON is holding an\n"
	.string "item, it makes me twice as happy!$"

