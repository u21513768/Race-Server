#define NUMBER_OF_SYMBOLS_IN_SCALE      30
#define MAX_SPEED_VEHICLE               240
#define SPEED_MULTIPLIER                195

new 
    Text:Speedometer[MAX_PLAYERS][4],
    MaxScaleSpeedTextDraw[NUMBER_OF_SYMBOLS_IN_SCALE] = "IIIIIIIIIIIIIIIIIIIIIIIIIIIII", 
    SpeedTimer[MAX_PLAYERS];    // Array to store the ID of the timers



stock Float:GetSpeedVehicle(vehicleId)
{
	new 
		Float: x,
		Float: y,
		Float: z;
		
	GetVehicleVelocity(vehicleId, x, y, z);

	return VectorSize(x, y, z) * SPEED_MULTIPLIER;
}

forward TimerSpeedometer(playerid, vehicleId);
public TimerSpeedometer(playerid, vehicleId)
{
	new 
        Float:speed = GetSpeedVehicle(vehicleId),
        Float:percentSpeedOfMax = speed/MAX_SPEED_VEHICLE*100,
        indexSpeed = floatround(NUMBER_OF_SYMBOLS_IN_SCALE-(NUMBER_OF_SYMBOLS_IN_SCALE*(percentSpeedOfMax/100)));

    indexSpeed = 
        indexSpeed >= NUMBER_OF_SYMBOLS_IN_SCALE ? NUMBER_OF_SYMBOLS_IN_SCALE-1 :
        indexSpeed < 0 ? 0 : indexSpeed;

	new speedStr[4];
	valstr(speedStr, floatround(speed));

	TextDrawSetString(Speedometer[playerid][2], speedStr);
	TextDrawSetString(Speedometer[playerid][0], MaxScaleSpeedTextDraw[indexSpeed]);
}

stock CreateSpeedometerTextDraws(playerid)
{
    Speedometer[playerid][0] = TextDrawCreate(138.000000, 403.000000, ""); //30
    TextDrawBackgroundColor(Speedometer[playerid][0], 0x00000000);
    TextDrawFont(Speedometer[playerid][0], 1);
    TextDrawLetterSize(Speedometer[playerid][0], 0.479999, 1.499998);
    TextDrawColor(Speedometer[playerid][0], -1);
    TextDrawSetOutline(Speedometer[playerid][0], 1);
    TextDrawSetProportional(Speedometer[playerid][0], 1);

    Speedometer[playerid][1] = TextDrawCreate(138.000000, 403.000000, MaxScaleSpeedTextDraw); //30
    TextDrawBackgroundColor(Speedometer[playerid][1], 0x00000000);
    TextDrawFont(Speedometer[playerid][1], 1);
    TextDrawLetterSize(Speedometer[playerid][1], 0.479999, 1.499998);
    TextDrawColor(Speedometer[playerid][1], 0xFFFFFF33);
    TextDrawSetOutline(Speedometer[playerid][1], 1);
    TextDrawSetProportional(Speedometer[playerid][1], 1);

    Speedometer[playerid][2] = TextDrawCreate(145.000000, 388.000000, ""); //km
    TextDrawBackgroundColor(Speedometer[playerid][2], 0x000000FF);
    TextDrawFont(Speedometer[playerid][2], 2);
    TextDrawLetterSize(Speedometer[playerid][2], 0.479999, 1.499998);
    TextDrawColor(Speedometer[playerid][2], 0x4c75b7);
    TextDrawSetOutline(Speedometer[playerid][2], 1);
    TextDrawSetProportional(Speedometer[playerid][2], 1);
    TextDrawSetShadow(Speedometer[playerid][2], 0);
    
    Speedometer[playerid][3] = TextDrawCreate(190.000000, 388.000000, "Km/h"); //km
    TextDrawBackgroundColor(Speedometer[playerid][3], 0x000000FF);
    TextDrawFont(Speedometer[playerid][3], 2);
    TextDrawSetString(Speedometer[playerid][3], "Km/h");
    TextDrawLetterSize(Speedometer[playerid][3], 0.479999, 1.499998);
    TextDrawColor(Speedometer[playerid][3], 0x4c75b7);
    TextDrawSetOutline(Speedometer[playerid][3], 1);
    TextDrawSetProportional(Speedometer[playerid][3], 1);
    TextDrawSetShadow(Speedometer[playerid][3], 0);
}