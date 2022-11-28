main() {}

new score; //added comment
new round_time;
new map_types;
new kills;
new PickupParachute;
new PickupArmour;
new PickupPills;
new PickupInformation;
new color;

score = 0;
round_time = 300;
kills = 0;
map_types = {
   "Car",
  "Air",
  "Sea",
  "Bikes",
  "theme park";
}

// Inludes //
#include <a_samp>
#include <Pawn.CMD>
#include <sscanf2>
#include "..\src\func"
#include "..\src\Speedometer"
#include "..\src\vars"

// Server Information //
#define SERVER_NAME "Cort Testing"
#define SERVER_GAMEMODE "racemod"

// forward //
forward SendMSG();

{
	print("\n----------------------------------");
	print(" Blank Gamemode by your name here");
	print("----------------------------------\n");
}

new RandomMSG[5][500] =
{   
	{"~ ~ [INFO]: Are You New Here? Check Out /rules /help."},
	{"~ ~ [CRBot]: If You Break Any Server Rule, You Are Gay."},
	{"~ ~ [CRBot]: Thanks for Playing On This Server,  Hope You're Enjoying."},
	{"~ ~ [CRBot]: If You Saw Someone Doing Cheating On The Server Kindly Use /report."},
	{"~ ~ [CRBot]: /anims To See Animations List"}
	
};

public OnGameModeInit()
{
	// Don't use these lines if it's a filterscript
	SetGameModeText("Race");
	AddPlayerClass(0, 1958.3783, 1343.1572, 15.3746, 269.1425, 0, 0, 0, 0, 0, 0);

	AllowAdminTeleport(1);
    // Other stuff
    //PickupParachute = CreatePickup(1310, 3, 1964.341, 1421.741, 75.696, 1);
	PickupArmour = CreatePickup(1242, 3, 1964.337, 1426.463, 75.699, 1);
	PickupInformation = CreatePickup(1239, 3, 1970.3909, 1423.9122, 76.1563, 1);
	PickupPills = CreatePickup(1241, 3, 1963.5049, 1420.9137, 76.1563, 1);
	SetTimer("SendMSG", 200000, true);
	return 1;
}
public SendMSG()
{
    new randMSG = random(sizeof(RandomMSG)); //calculates the size of RandomMSG (which is 3)
    SendClientMessageToAll(0xffa500, RandomMSG[randMSG]);
	
    return 1;
}
public OnGameModeExit()
{
	return 1;
}

public OnPlayerRequestClass(playerid, classid)
{
	SetPlayerPos(playerid, 1958.3783, 1343.1572, 15.3746);
	SetPlayerCameraPos(playerid, 1958.3783, 1343.1572, 15.3746);
	SetPlayerCameraLookAt(playerid, 1958.3783, 1343.1572, 15.3746);
	return 1;
}

public OnPlayerConnect(playerid)
{   
	new vehicleid = GetPlayerVehicleID(playerid);
    if(!IsPlayerInAnyVehicle(playerid))
	PutPlayerInVehicle(playerid, vehicleid, 0);	

	CreateSpeedometerTextDraws(playerid);

	SendClientMessage(playerid, 0xCC3366, "~ ~ [CRBot]: If You Are New Here Dont Forget To Check Out /rules /help");
	SendClientMessage(playerid, 0xFFFFFF, "~ ~ [SERVER]: You Succesfully Spawned!");
	
	new name[MAX_PLAYER_NAME + 1];                         // Name Color Could Be Specific According To Player Last Name Joined Color In Server.
    GetPlayerName(playerid, name, sizeof(name));
	GetPlayerColor(playerid);

    new string[MAX_PLAYER_NAME + 23 + 1];
    format(string, sizeof(string), "[SERVER]: %s has joined the server.", name);
    SendClientMessageToAll(0x7d4844AA, string);

	return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
	return 1;
}

public OnPlayerSpawn(playerid)
{   
	GivePlayerWeapon(playerid, 14, 0);
	return 1;
}

public OnPlayerDeath(playerid, killerid, reason)
{
   return 1;
}

public OnVehicleSpawn(vehicleid)
{
	return 1;
}

public OnVehicleDeath(vehicleid, killerid)
{
	return 1;
}

public OnPlayerText(playerid, text[])
{
	return 1;
}

public OnPlayerCommandText(playerid, cmdtext[])
{
	if (strcmp("/mycommand", cmdtext, true, 10) == 0)
	{
		
	}
	return 0;
}
public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	return 1;
}

public OnPlayerExitVehicle(playerid, vehicleid)
{
	return 1;
}

public OnPlayerStateChange(playerid, newstate, oldstate)
{
	if (newstate == PLAYER_STATE_DRIVER)
	{
		new vehicleid = GetPlayerVehicleID(playerid);

		SpeedTimer[playerid] = SetTimerEx("TimerSpeedometer", 200, 1, "dd", playerid, vehicleid);
		TextDrawShowForPlayer(playerid, Speedometer[playerid][0]);
		TextDrawShowForPlayer(playerid, Speedometer[playerid][1]);
		TextDrawShowForPlayer(playerid, Speedometer[playerid][2]);
		TextDrawShowForPlayer(playerid, Speedometer[playerid][3]);

	}
	if (newstate != PLAYER_STATE_DRIVER && oldstate == PLAYER_STATE_DRIVER)
	{
		new timerId = SpeedTimer[playerid];

		if (timerId)
		{
			TextDrawHideForPlayer(playerid, Speedometer[playerid][0]);
			TextDrawHideForPlayer(playerid, Speedometer[playerid][1]);
			TextDrawHideForPlayer(playerid, Speedometer[playerid][2]);
			TextDrawHideForPlayer(playerid, Speedometer[playerid][3]);
			SpeedTimer[playerid] = 0;
			KillTimer(timerId);
		}
	}

	return 1;
}

public OnPlayerEnterCheckpoint(playerid)
{
	return 1;
}

public OnPlayerLeaveCheckpoint(playerid)
{
	return 1;
}

public OnPlayerEnterRaceCheckpoint(playerid)
{
	return 1;
}

public OnPlayerLeaveRaceCheckpoint(playerid)
{
	return 1;
}

public OnRconCommand(cmd[])
{
	return 1;
}

public OnPlayerRequestSpawn(playerid)
{
	return 1;
}

public OnObjectMoved(objectid)
{
	return 1;
}

public OnPlayerObjectMoved(playerid, objectid)
{
	return 1;
}

public OnPlayerPickUpPickup(playerid, pickupid)
{
    
    if (pickupid == PickupArmour)
    {
        SetPlayerArmour(playerid, 100);
	}
	else if (pickupid == PickupParachute) // not working well
    {
		//AttachObjectToPlayer(1310, playerid, 1964.341, 1421.741, 75.696, 1964.341, 1421.741, 75.696);
	}
	else if (pickupid == PickupInformation)
	{
		AttachObjectToPlayer(1239, playerid, 1970.3909, 1423.9122, 76.1563, 1970.3909, 1423.9122, 76.1563);
		SendClientMessage(playerid, -1, "[INFO]: You Have Been Set To Afk. To Return Type /atk ");
		GivePlayerMoney(playerid, 1000);
		SendClientMessage(playerid, 0xFFFF00AA, "[SERVER]: You Got $1000 Dollars. Enjoy!");
	}
	else if (pickupid == PickupPills)
	{
		AttachObjectToPlayer(1241, playerid, 1963.5049, 1420.9137, 76.1563, 1963.5049, 1420.9137, 76.1563);
	}
	return 1;
}

public OnVehicleMod(playerid, vehicleid, componentid)
{
	return 1;
}

public OnVehiclePaintjob(playerid, vehicleid, paintjobid)
{
	return 1;
}

public OnVehicleRespray(playerid, vehicleid, color1, color2)
{
	return 1;
}

public OnPlayerSelectedMenuRow(playerid, row)
{
	return 1;
}

public OnPlayerExitedMenu(playerid)
{
	return 1;
}

public OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid)
{
	return 1;
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(newkeys == 1 || newkeys == 9 || newkeys == 33 && oldkeys != 1 || oldkeys != 9 || oldkeys != 33)

	AddVehicleComponent(GetPlayerVehicleID(playerid), 1010);
    
	if(newkeys == 512)
    
    RepairVehicle(GetPlayerVehicleID(playerid));
	return 1;
}
public OnRconLoginAttempt(ip[], password[], success)
{
	return 1;
}

public OnPlayerUpdate(playerid)
{
	return 1;
}

public OnPlayerStreamIn(playerid, forplayerid)
{
	return 1;
}

public OnPlayerStreamOut(playerid, forplayerid)
{
	return 1;
}

public OnVehicleStreamIn(vehicleid, forplayerid)
{
	return 1;
}

public OnVehicleStreamOut(vehicleid, forplayerid)
{
	return 1;
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
     switch(dialogid)
     {
          case DialogChangeName:
           {
               if(response)
                {
					  if(!(0 < strlen(inputtext) <= 24)) return SendClientMessage(playerid, 0xCCCC00, "[ERROR]: Name Must Be In Between 0-30 Characters");
                      SetPlayerName(playerid, inputtext);
                      SendClientMessage(playerid, 0xFF66CCFF, "[SUCCESS]: You Have Changed Your Name");
                      return 1;               
                }
                else
                {
                      return SendClientMessage(playerid, 0xFF66CCFF, "[CANCELLED]: You Have Cancelled To Change Your Name!");
                }
           
		   }
		   case  DialogHelp:
		   {  
				switch(listitem)
				{
					case 0:
					{
						return ShowPlayerDialog(playerid, DialogHelp, DIALOG_STYLE_MSGBOX, "Commands", "{1E90FF}/tp = Teleport To A Other Player.\n/v = To Spawn Your Vehicle.\n/myskin = To Change Your Skin.\n/gw = To Get A Weapon For Yourself.\n/gc = To Send Money.\n/vr = Repair A Vehicle.\n/myweather = To Change Your Specific Weather.\n/rules = To Check Server Rules.\n/off(road) = Offroad Wheel.\n/vc = Change Your Vehicle Color.\n/nos = Add A Nos.\n/changename = To Change Your Name.\n/afk = To Join Afk Mode.\n/atk = To Back In A Default World.\n/flip = To Flip Your Car.\n/spec = To Spectate A Player.\n/specoff = To Back In A World From Spectate.", "OK", "");
					}
					case 1:
					{
                        return ShowPlayerDialog(playerid, DialogHelp, DIALOG_STYLE_MSGBOX, "About Vehicles", "{1E90FF}You can found vehicles on streets or you can spawn it by yourself.", "OK", "");
					}
					case 2:
					{
                        return ShowPlayerDialog(playerid, DialogHelp, DIALOG_STYLE_MSGBOX, "About Races", "{1E90FF}We made this server especially for racings cause it is our first priority and we will try to give you best experience of races.{FFFFFF}\n\n\nRaces:\n\n{1E90FF}Races are in rotation so in few mints it will be loaded after the previous ones ends so be patient for it and please do not disturb admins for keep loading your races.{FFFFFF}\n\n\nHow To Join Race:\n\n{1E90FF}You can join race by type /race if there will be any race.{FFFFFF}\n\n\nCan We Create Our Races:\n\n{1E90FF}Yes, you can by /br to enter build race mode and submit into Race Submissions but do not disturb to check your races everytime to admins, they will check by theirself.   ", "OK", "");
					}
					case 3:
					{
						return ShowPlayerDialog(playerid, DialogHelp, DIALOG_STYLE_MSGBOX, "Credits", "{FFFFFF}Some Players Name Who Helped Me In Making This Server:\n\n\n{1E90FF}Cortless,Danny", "OK", "");
					}
					case 4:
					{
						return ShowPlayerDialog(playerid, DialogHelp, DIALOG_STYLE_MSGBOX, "About Server", "{1E90FF}Hi, hope you guys are enjoying this server. I started to make this server in my mind since 1 years ago but for not getting enough time because of study to make it practically so it's had been keeping late. \nI had decided to make this server only for Racings and with some friendly, respectful and fun community which i think it's getting true. We are always here to serves you best experience for to spend your time here.\nAfter 1 year my friend Diviasys joined me which was actually good for me and server, after all he has more experience of scripting than me which makes this server to complete.{FFFFFF}\n\n\n\n                                                                                     ***THANKS FOR ALL OF YOU AND EVERY MEMBER WHO SUPPORTS THIS SERVER AND MAKE IT ALIVE***", "OK", "");
					}
					
				}
		    }
     
	 }
	 
	 switch(dialogid) // not changing name color
     {
          case DialogNameColor:
           {
               if(response)
                {
					if(!(0 < strlen(inputtext) <= 50)) return SendClientMessage(playerid, 0xCCCC00, "[ERROR]: HTML Code Must Be Correct");
                    SetPlayerColor(playerid, color);
                    SendClientMessage(playerid, 0xFF66CCFF, "[SUCCESS]: You Have Changed Your NameColor");
                    return 1;               
                }
                else
                {
                      return SendClientMessage(playerid, 0xFF66CCFF, "[CANCELLED]: You Have Cancelled To Change Your NameColor!");
                }
		   					
		    }
		     case DialogRules: // not working well this function shouldn't be repeated 
			{
				if(response)
				{
					SendClientMessage(playerid, 0xFF66CCFF, "[SERVER]: Thanks For Agreeing With The Server Rules");
					SendClientMessage(playerid, 0xFFFF00AA, "[SERVER]: You Got $10000 Dollars");
                    GivePlayerMoney(playerid, 10000);

				}
				else
				{
					return SendClientMessage(playerid, 0xCCCC00, "[ERROR]: You Already Agreed The Server Rules. Thanks");
				}

		   }

	 } 
     return 1;      
}

public OnPlayerClickPlayer(playerid, clickedplayerid, source)
{
	return 1;
}
public OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ)
{
    SetPlayerPosFindZ(playerid, fX, fY, fZ);
    return 1;
}

#include "..\src\cmds"