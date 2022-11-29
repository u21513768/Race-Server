
CMD:tp(playerid, params[]) // teleport to player //
{
    extract params -> new targetid;else
            return SendClientMessage(playerid, 0xFF66CCFF, "[USAGE]: /tp [Player ID]");

    
    new Float: x,
        Float: y,
        Float: z;

    GetPlayerPos(playerid, x, y, z);
    SetPlayerPos(playerid, x, y, z);

    return 1;
}

CMD:v(playerid, params[]) // Need To Fix Not Spawning Bikes Which Has Numeric In Their Name Like : NRG-500, FCR-900 etc
{
    extract params -> new string:model[30];
      return SendClientMessage(playerid, 0xFF66CCFF, "[USAGE]: /v [Car/Model]");
    
    new modelId = 0;
    
    if(isdigit(model) != 0)
        modelId = strval(model);
    else 
    {
        for(new i = 0, sizeArray = sizeof VehicleNames; i < sizeArray; i++)
        {
            if(strcmp(tolower(VehicleNames[i]), tolower(model)) == 0) //might be better?
            {
                modelId = i + 400;
                break;
            }      
        }

        if (modelId == 0)
            return SendClientMessage(playerid, 0xCCCC00, "[ERROR]: Invalid Vehicle Name");
    }

    if(400 > modelId || modelId > 611)
        return SendClientMessage(playerid, 0xCCCC00, "[ERROR]: Invalid Range Model ID");

    new 
        Float: x,
        Float: y,
        Float: z,
        Float: angle;

    GetPlayerPos(playerid, x, y, z);
    GetPlayerFacingAngle(playerid, angle);

    new vehicleId = CreateVehicle(modelId, x, y, z, angle, 0, 0, -1);
    PutPlayerInVehicle(playerid, vehicleId, 0);

    return 1;
}

CMD:myskin (playerid, params[]) // USAGE: /myskin <skin ID>,  /// Needs To Change Running Style of Other Skins Same As CJ Skin!
{
    extract params -> new skinid; else
        return SendClientMessage(playerid, 0xFF66CCFF, "[USAGE]: /myskin [Skin ID]");
    
    if(!(0 <= skinid <= 311))
        return SendClientMessage(playerid, 0xCCCC00, "[ERROR]: Invalid Skin ID");

    SetPlayerSkin(playerid, skinid);

    return 1;
}

//CMD:gw(playerid, params[]) // USAGE: /gw [playerID] [WeaponID] 
//{
    //extract params -> new weaponid, ammo;else
    //return SendClientMessage(playerid, 0xFF66CCFF, "[USAGE]: /gw [Weapon ID] [Ammo]");

    //if(!(1 <= weaponid <= 34))
    
    //SendClientMessage(playerid, -1, "[ERROR]: Weapon Id Range (1-34)");
    
    //GivePlayerWeapon(playerid, weaponid, ammo);

   // return 1;

//}

CMD:gc (playerid, params[]) // to give money other player
{
    extract params -> new targetid, money; else
        return SendClientMessage(playerid, 0xFF66CCFF,"[USAGE]: /gc [Player ID] [Amount]");
    
    if(!(0 <= money <= 99999999))
        return SendClientMessage(playerid, 0xCCCC00, "[ERROR]: Invalid Amount");

    GivePlayerMoney(targetid, money);
    SendClientMessage(targetid, 0xFF66CCFF, "[SUCCESS]: You Have Recieved Money!");

    return 1;
}

CMD:vr(playerid) // to repair your vehicle
{    
    if(IsPlayerInAnyVehicle(playerid))
    {
    new vehicleid = GetPlayerVehicleID(playerid);

    SetVehicleHealth(vehicleid, 1000);
    RepairVehicle(vehicleid);
    }
    return 1;
}

CMD:cmds(playerid, params[]) // to see commands list
{
    extract params -> new text; else
    return SendClientMessage(playerid, 0xCC3366, "[SERVER]: /help, /rules, /anims, /tp, /v, /myskin, /gw, /gc, /vr, /myweather, /off, /nos, /hyd, /vc, /afk, /atk, /spec, /specoff, /changename");

    return 1;                                      
}

CMD:myweather(playerid, params[]) // to change your specific weather
{
    extract params -> new weather; else
        return SendClientMessage(playerid, 0xFF66CCFF, "[USAGE]: /myweather [Weather ID]");
    
    if(!(0 <= weather <= 101))
        return SendClientMessage(playerid, 0xCCCC00, "[ERROR]: Invalid Weather ID");
    
    SetPlayerWeather(playerid, weather);

    return SendClientMessage(playerid, 0xFF66CCFF, "[SUCCESS]: Your Weather Has Been Changed!");
}

CMD:rules(playerid, params[]) // /rules with messagebox
{
    ShowPlayerDialog(playerid, DialogRules, DIALOG_STYLE_MSGBOX, "Server Rules:", "{FFFFFF}#1. {1E90FF}Do NOT hack or cheat.{FFFFFF}\n#2. {1E90FF}Do NOT spam, flood or advertise.{FFFFFF}\n#3. {1E90FF}Do NOT troll or insult anybody.{FFFFFF}\n#4. {1E90FF}Do NOT use any mods which gives you advantage, if you use for a purpose inform to admin.{FFFFFF}\n#5. {1E90FF}Do NOT Provoke.{FFFFFF}\n#6. {1E90FF}Do NOT share any links. use pm for that.{FFFFFF}\n#7. {1E90FF}Do NOT block other racers in race.{FFFFFF}\n#8. {1E90FF}DO NOT Defame, Swear, Harass.{FFFFFF}\n#9. {1E90FF}DO NOT Ban Evade.", "Agree", "");
    SetTimer("Rules", 0, false);
}

CMD:help(playerid) // /help with DialogBox
{

    return ShowPlayerDialog(playerid, DialogHelp, DIALOG_STYLE_LIST, "What you want to know about", "Commands\nVehicle\nRaces\nCredits\nAbout", "OK", "Cancel");

}

CMD:off(playerid) // to change your car wheel into offroad wheel
{
    new vehicleid = GetPlayerVehicleID(playerid);

    AddVehicleComponent(vehicleid, 1025);

    if(IsPlayerInVehicle(playerid, vehicleid))
    {
        SendClientMessage(playerid, 0xFF66CCFF, "[SUCCESS]: Your Car Wheel Switched To Offroad Wheels!");
    }
    else
    {
        SendClientMessage(playerid, 0xCCCC00, "[ERROR]: You Must Be In A Vehicle.");
    }
    return 1;
}

CMD:nos(playerid) // to add a nos
{
    new vehicleid = GetPlayerVehicleID(playerid);

    AddVehicleComponent(vehicleid, 1010);

    if(IsPlayerInVehicle(playerid, vehicleid))
    {
        SendClientMessage(playerid, 0xFF66CCFF, "[SUCCESS]: Nos Added!");
    }
    else
    {
        SendClientMessage(playerid, 0xCCCC00, "[ERROR]: You Must Be In A Vehicle.");
    }
    
    return 1;
}

CMD:vc(playerid, params[]) // To Change Your Vehicle Color
{
    extract params -> new color1, color2; else
        return SendClientMessage(playerid, 0xFF66CCFF, "[USAGE]: /vc [First Color] [Second Color]");
      
    new vehicleid = GetPlayerVehicleID(playerid);

    ChangeVehicleColor(vehicleid, color1, color2);

    if(IsPlayerInVehicle(playerid, vehicleid))
        SendClientMessage(playerid, 0xFF66CCFF, "[SUCCESS]: Your Vehicle Color Has Been Changed!");

    return 1;

}

CMD:changename(playerid, params[]) // to change your name
{
    return ShowPlayerDialog(playerid, DialogChangeName, DIALOG_STYLE_INPUT, "ChangeName", "Enter Your New Name", "Change", "Cancel");
    
}

CMD:admins(playerid) // needs to fix 
{
    //return ShowPlayerDialog(playerid, DialogRules, DIALOG_STYLE_MSGBOX, "Online Admins", "", "Agree", ""); // Not finished yet
    int OnlineAdmins[];
    char AdminsTemp[] = "";
    char Admins[] = "";
    int counter = 0;
    for(int i = 0; i < numPlayers; i++) 
    {
        if(IsPlayerAdmin(i)) //checks which players are admins
        {
            //OnlineAdmins[counter] = i;
            //counter++;
            strcat(Admins, GetPlayerName(i)); //adds the name of the admin to a list
            strcat(Admins, ", "); //separates players by ", "
        }
    }

    for(int j = 0; j < strlen(AdminsTemp)-2; j++) //removes ", " from the end of the string
    {
        Admins[j] = AdminsTemp[j];
    }

    return ShowPlayerDialog(playerid, DialogRules, DIALOG_STYLE_MSGBOX, "Online Admins", Admins, "Okay", ""); //displays the list to the player
}

CMD:hyd(playerid) // To Add Hydraulics in Car
{
    new vehicleid= GetPlayerVehicleID(playerid);
  
    AddVehicleComponent(vehicleid, 1087);

    if(IsPlayerInVehicle(playerid, vehicleid))
    {
        return SendClientMessage(playerid, 0xFF66CCFF, "[SUCCESS]: Hydraulics Added!");
    }
    else
    {
        SendClientMessage(playerid, 0xCCCC00, "[ERROR]: You Must Be In A Vehicle.");
    }
    return 1;
}
CMD:afk(playerid, params[]) // to afk yourself
{
    extract params -> new color1, worldid, angle, range; else

    SetPlayerVirtualWorld(playerid, 1);
    SetPlayerColor(playerid, -1);
    SetPlayerPos(playerid, 1965.658, 1423.990, 75.904);
    SetPlayerFacingAngle(playerid, 270);
    SetPlayerHealth(playerid, 100000);
    SendClientMessage(playerid, -1, " You Are In AFK Mode Now.");
    
    
    return 1;
}
CMD:atk(playerid, params[]) // to back in default world
{
    extract params -> new world, weaponid, ammo; else

    SetPlayerVirtualWorld(playerid, 0);
    SetPlayerPos(playerid, 2023.530, 1342.935, 10.546);
    SetPlayerFacingAngle(playerid, 270);
    SetPlayerColor(playerid, 0xFFD700);
    SetPlayerHealth(playerid, 100);
    AttachObjectToPlayer(1310, 0, 1.5, 0.5, 0.0, 0.0, 1.5, 2);

    SendClientMessage(playerid, 0x708090, "[SUCCESS]: Welcome Back!");

    return 1;
}
CMD:namecolor(playerid, color, params[]) // not chaning name colors //could make it that the user enters a color and then it changes according to color using switch cases
{
    //use switch cases with numerical values for colour, similar to discord color bot
   return ShowPlayerDialog(playerid, DialogNameColor, DIALOG_STYLE_INPUT, "Change Name Color", "\n{FFFFFF}FF0000 {FF0000}YourName ~ For Red\n{FFFFFF}00FF00 {00FF00}Yourname ~ For Green\n{FFFFFF}FFFF00 {FFFF00}YourName ~ For Yellow", "OK", "Cancel");

}

//need to save position to file or to db, if positions for that player exist, overwrite
CMD:s(playerid, params[]) // not working well 
{
    
    //new vehicleid = GetPlayerVehicleID(playerid); //what if not in vehicle? might need to nest in if statement
    int vehicleid;
    new 
        Float: x,
        Float: y,
        Float: z;

    if(IsPlayerInAnyVehicle(playerid))
    {
        vehicleid = GetPlayerVehicleID(playerid);
        SetVehiclePos(vehicleid, x, y, z);
        PutPlayerInVehicle(playerid, vehicleid, 0);
        SendClientMessage(playerid, -1, "Your Position Saved");
    }
    else //set player in position without vehicle
    {
        GetPlayerPos
    }
    return 1;
}

//need to load position from file or db
CMD:l(playerid, params[]) // not working well //
{
    new vehicleid = GetPlayerVehicleID(playerid);

    
    new Float: x,
        Float: y,
        Float: z;
 
    if(IsPlayerInAnyVehicle(playerid))
    {
    GetVehiclePos(vehicleid, x, y, z);
    PutPlayerInVehicle(playerid, vehicleid, 0);
    SendClientMessage(playerid, -1, "Your Last Position loaded");
    }
    return 1;
}
CMD:flip(playerid, params[]) // to flip your car
{
    new vehicleid;
    new Float:angle;
    vehicleid = GetPlayerVehicleID(playerid);
    GetVehicleZAngle(vehicleid, angle);
    SetVehicleZAngle(vehicleid, angle);
    RepairVehicle(vehicleid);
    return 1;
}
CMD:spec(playerid, params[])
{
    extract params -> new targetid, vehicleid;else

    if (!IsPlayerConnected(playerid))
    {
        printf("Player ID %i is not connected!", playerid);
    }
    else
    {
        TogglePlayerSpectating(playerid, 1);
        PlayerSpectatePlayer(targetid, targetid, SPECTATE_MODE_NORMAL);
        PlayerSpectateVehicle(targetid, vehicleid, SPECTATE_MODE_NORMAL);
    }
}
CMD:specoff(playerid, params[])
{
    extract params -> new targetid, vehicleid;else

    TogglePlayerSpectating(playerid, 0);
    PlayerSpectatePlayer(playerid, targetid, SPECTATE_MODE_NORMAL);
    PlayerSpectateVehicle(playerid, vehicleid, SPECTATE_MODE_NORMAL);
}
/////////////////////////    Animations For Players    //////////////////////////
CMD:anims(playerid) // To Show Anims List
{
    return SendClientMessage(playerid, 0xCC3366, "[SERVER]: /smoke, /sit, /scratchballs, /wave");
}

CMD:animclear(playerid) // To Stop Animations
{
    ClearAnimations(playerid);
    return 1;
}

CMD:smoke(playerid)
{
    ApplyAnimation(playerid, "SMOKING", "M_smklean_loop", 4.1, 1, 1, 0, 0, 0, 2);
    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_SMOKE_CIGGY);
    return 1;
}

CMD:sit(playerid)
{
    ApplyAnimation(playerid, "BEACH", "SitnWait_loop_W", 4.1, 1, 1, 0, 0, 0, 1);
    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_SITTING );
    return 1;
}

CMD:scratchballs(playerid)
{
    ApplyAnimation(playerid, "MISC", "Scratchballs_01", 4.1, 1, 1, 0, 0, 0, 1);
    return 1;
}

CMD:wave(playerid)
{
    ApplyAnimation(playerid, "ON_LOOKERS", "wave_loop", 4.1, 0, 1, 0, 0, 0, 1);
    return 1;
}

///////////////////////// Server Moderators Commands //////////////////////////
CMD:mcmds(playerid) // working
{
   if(!IsPlayerAdmin(playerid))
      return SendClientMessage(playerid, -1, "[ERROR]: You Are Not Logged In As Admin");

   return ShowPlayerDialog(playerid, DialogMcmds, DIALOG_STYLE_MSGBOX, "Moderator Commands", "{FFFFFF}\t\t\t\t\t\t\t\tUSAGE: {1E90FF}\n\n/getin = Enter In Other Player Car As Passenger. \t\t\t/getin [Player ID]\n/jetpack = To Spawn A Jetpack.\t\t\t\t\t/jetpack\n/freeze = To Freeze A Player.\t\t\t\t\t/freeze [Player ID]\n/unfreeze = To Unfreeze A Player.\t\t\t\t/unfreeze [Player ID]\n/cc = To Clear A Mainchat.\t\t\t\t\t/cc\n/heal = To Heal A Player.\t\t\t\t\t\t/heal [Player ID] [Health]\n/gpw = To Give A Weapon To Player.\t\t\t\t/gpw [Player ID] [Weapon ID] [Ammo]\n/armour = To Give Armour To Player.\t\t\t\t/armour [Player ID] [Armour]", "Cancel", ""); 
}

CMD:jetpack(playerid, params[]) // to spawn jetpack
{ 
    extract params -> new player:targetid = 0xFFFF; else
        return 1;

    if (!IsPlayerAdmin(playerid))
        return SendClientMessage(playerid, -1, "[ERROR]: You Are Not Logged In As Admin");

    if (targetid == INVALID_PLAYER_ID)
    {
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USEJETPACK);
        SendClientMessage(playerid, 0x5e7072, "[SUCCESS]: You Have Jetpack Now!");
    }
    else
    {
        SetPlayerSpecialAction(targetid, SPECIAL_ACTION_USEJETPACK);
        SendClientMessage(targetid, 0x5e7072, "[SUCCESS]: You Were Given Jetpack!");
    }
    
    return 1;
}

CMD:kick(playerid, params[]) // to kick players
{
    if (!IsPlayerAdmin(playerid))
        return SendClientMessage(playerid, -1, "[ERROR]: You Are Not Logged In As Admin");
      
    extract params -> new player:targetid; else
        return SendClientMessage(playerid, 0x730f1a, "[USAGE]: /kick [playerid]");

    return SetTimerEx("DelayKick", 1000, false, "i", targetid); 
}

CMD:freeze(playerid, params[]) // to freeze player
{
    if(!IsPlayerAdmin(playerid))
        return SendClientMessage(playerid, -1, "[ERROR]: You Are Not Logged In As Admin");
    
    extract params -> new player: targetid; else
        return SendClientMessage(playerid, 0x730f1a, "[USAGE]: /freeze [Player ID]");

    if (targetid == INVALID_PLAYER_ID)
        targetid = playerid;
    
    TogglePlayerControllable(targetid, 0);
    SendClientMessage(targetid, 0x5e7072, "[SUCCESS]: You Are Freezed By Admin!");
    
    return 1;
}

CMD:unfreeze(playerid, params[]) // to unfreeze player
{
    
    if(!IsPlayerAdmin(playerid))
        return SendClientMessage(playerid, -1, "[ERROR]: You Are Not Logged In As Admin");
    
    extract params -> new player: targetid; else
       return SendClientMessage(playerid, 0x730f1a, "[USAGE]: /unfreeze [Player ID]");
      
    if (targetid == INVALID_PLAYER_ID)
        targetid = playerid;
    
    TogglePlayerControllable(targetid, 1);  
    SendClientMessage(targetid, 0x5e7072, "[SUCCESS]: You Are Now Unfreeze By Admin!"); // FOR YOURSELF

    return 1;
}

CMD:cc(playerid) // to clear chat 
{
	// this for clear chat all player
	if(!IsPlayerAdmin(playerid))
        return 1;

	for(new i; i < 25; i++) 
        SendClientMessageToAll(-1,"");
        
	return 1;
}
CMD:heal(playerid, params[]) // to heal player aswell as yourself
{
    if(!IsPlayerAdmin(playerid))
    return SendClientMessage(playerid, -1, "[ERROR]: You Are Not Logged In As Admin");

    extract params -> new player:targetid, health; else
    return SendClientMessage(playerid, 0x730f1a, "[USAGE]: /heal [Player ID] [Health]");

    SetPlayerHealth(targetid, health);
    SendClientMessage(targetid, 0x5e7072, "[SUCCESS]: Your Health Has Been Refilled!"); 
    SendClientMessage(playerid, 0x5e7072, "[SUCCESS]: You Reffiled His Health!"); 
    
    return 1;
}

CMD:armour(playerid, params[]) // to give armour player aswell as yourself
{
    if(!IsPlayerAdmin(playerid))
        return SendClientMessage(playerid, -1, "[ERROR]: You Are Not Logged In As Admin");

    extract params -> new player:targetid, armour; else
        return SendClientMessage(playerid, 0x730f1a, "[USAGE]: /armour [Player ID] [Armour]");

    SetPlayerArmour(targetid, armour);
    SendClientMessage(targetid, 0x5e7072, "[SUCCESS]: Your Armour Has Been Refilled!"); 
    SendClientMessage(playerid, 0x5e7072, "[SUCCESS]: You Reffiled His Armour!"); 

    return 1;

}
CMD:gpw(playerid, params[]) // to give weapon to player 
{
    if(!IsPlayerAdmin(playerid))
        return SendClientMessage(playerid, -1, "[ERROR]: You Are Not Logged In As Admin");
    
    extract params -> new targetid, weaponid, ammo; else
        return SendClientMessage(playerid, 0x730f1a, "[USAGE]: /gpw [Player ID] [Weapon ID] [Ammo]");
    
    if(!(1 <= weaponid <= 46))
        return SendClientMessage(playerid, -1, "[ERROR]: Weapon Id Range (1-46)");

    if(!(1 <= ammo <= 1000))
        return SendClientMessage(playerid, -1, "[ERROR]: Ammo Range (1-1000)");

    GivePlayerWeapon(targetid, weaponid, ammo);

    SendClientMessage(targetid, 0x5e7072, "[SUCCESS]: You Were Given a Weapon");
    SendClientMessage(playerid, 0x5e7072, "[SUCCESS]: You Gave Weapon To Player");
    
    return 1;
}
CMD:getin(playerid, userid params[]) // to getin target vehicle as passenger // need to implement
{
    //commented out for test
    /*if(!IsPlayerAdmin(playerid))
    return SendClientMessage(playerid, -1, "[ERROR]: You Are Not Logged In As Admin");
    
    extract params -> new targetid, seatid; //if this is part of if statement, can't be after return
    else //has to come directly after the if statement
    return SendClientMessage(playerid, 0x730f1a, "[USAGE]: /getin [Player ID]");
    { //what are brackets for?
    if(!IsPlayerConnected(targetid))
    return SendClientMessage(playerid, -1, "[ERROR]: Player Is Not Connected");
    }

    new vehicleid = GetPlayerVehicleID(playerid);

    if(!IsPlayerInAnyVehicle(playerid))
    {
    return SendClientMessage(playerid, -1, "[ERROR]: Player Is Not In Any Vehicle");
    }
    else
    {
        new //not being used
           Float: x,
           Float: y,
           Float: z;

        PutPlayerInVehicle(playerid, vehicleid, 1);
        GetVehiclePos(vehicleid, x, y, z); //why?

        SendClientMessage(targetid, -1, "Admin Teleported In Your Car");
        return 1;
    }*/

    if(!IsPlayerAdmin(userid))
    return SendClientMessage(userid, -1, "[ERROR]: You Are Not Logged In As Admin");
    
    extract params -> new targetid, seatid;

    if(!IsPlayerConnected(playerid))
    return SendClientMessage(userid, -1, "[ERROR]: Player Is Not Connected");
    
    new vehicleid = GetPlayerVehicleID(playerid);

    if(!IsPlayerInAnyVehicle(playerid))
    return SendClientMessage(userid, -1, "[ERROR]: Player Is Not In Any Vehicle");
    
    PutPlayerInVehicle(userid, vehicleid, 1);

    SendClientMessage(playerid, -1, "Admin Teleported In Your Car");
    return 1;
}