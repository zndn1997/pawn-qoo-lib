/****************************************************
				Fade Camera Function
					Version: v2.0
					Made by: Qoo
****************************************************/

#if defined _FadeFunc_included
	#endinput
#endif
#define _FadeFunc_included
#pragma library fadefunc

// FadeCamera �Լ��� timeToFade ���� 0.02���� ��ȿ�մϴ�.

/*���� ����:
v1.0: ���� ������
v1.5: ����ȭ �� �ڵ� ���� ���
v2.0:
	1. timeToFade�� ���� ���� ����
	2. timeToFade���� ���� ��� �ʿ� �̻����� ���� ������Ʈ�� �̷����
		�� �ּ� 62.5���������� �����ϰ� timeToFade���� 5.0�� �����ʹ� ������ ���� ���缭 �ð��� ����
*/

// ����: FadeCamera(�÷��̾�ID, Fade ����(true = ȭ���� �Ⱦ���, false = ȭ���� ������), �ҿ� �ð�(�Ҽ����̸�, 1.0�� 1000ms �� 1����.), red (0~255), green (0~255), blue(0~255));

//***************************************************
static fadeScreenColor[MAX_PLAYERS];
static fadeScreenCount[MAX_PLAYERS];
static fadeScreenType[MAX_PLAYERS];
static fadeScreenTimer[MAX_PLAYERS];
static fadeScreenSpeed[MAX_PLAYERS];
static fadeScreenTime[MAX_PLAYERS];

static Text: fadeScreen[MAX_PLAYERS];
//***************************************************

//***************************************************
forward FadeCameraCore(playerid);
//***************************************************

//***************************************************
stock FadeCamera(playerid, fadeIn, Float: timeToFade = 1.0, red = 0, green = 0, blue = 0)
{
	if(IsPlayerConnected(playerid) == 0 || IsPlayerNPC(playerid)) return 0;
	if(fadeScreenType[playerid] == fadeIn) return 0;
	fadeScreenType[playerid] = fadeIn;
	if(fadeIn == 0) fadeScreenColor[playerid] = RGBToHex(red, green, blue);
	else fadeScreenColor[playerid] += 255;
	if(timeToFade <= 0)
	{
		fadeScreenCount[playerid] = 0;
		if(fadeIn) TextDrawHideForPlayer(playerid, fadeScreen[playerid]);
		else
		{
			TextDrawBoxColor(fadeScreen[playerid], fadeScreenColor[playerid] + 255);
			TextDrawShowForPlayer(playerid, fadeScreen[playerid]);
		}
	}
	else
	{
		new oldTime = fadeScreenTime[playerid];
		fadeScreenSpeed[playerid] = floatround(4.25 / timeToFade, floatround_floor);
		if(fadeScreenSpeed[playerid] <= 1)
		{
			if (fadeScreenSpeed[playerid] != 1) fadeScreenSpeed[playerid] = 1;
			fadeScreenTime[playerid] = floatround(1000 * timeToFade / 255, floatround_floor);
		}
		else fadeScreenTime[playerid] = 16;
		if(fadeScreenTimer[playerid] != 0 && fadeScreenTime[playerid] != oldTime)
		{
			KillTimer(fadeScreenTimer[playerid]);
			fadeScreenTimer[playerid] = 0;
		}
		if(fadeScreenTimer[playerid] == 0) fadeScreenTimer[playerid] = SetTimerEx("FadeCameraCore", fadeScreenTime[playerid], 1, "i", playerid);
	}
	return 1;
}

static RGBToHex(red, green, blue)
{
	return (red << 24) | (green << 16) | (blue << 8);
}
//***************************************************

//***************************************************
public FadeCameraCore(playerid)
{
	new Text: tText = fadeScreen[playerid];
	if(fadeScreenCount[playerid] == 0) TextDrawBoxColor(tText, fadeScreenColor[playerid]);
	else
	{
		if(fadeScreenType[playerid] == 0) TextDrawBoxColor(tText, fadeScreenColor[playerid] + fadeScreenCount[playerid]);
		else TextDrawBoxColor(tText, fadeScreenColor[playerid] - fadeScreenCount[playerid]);
	}
	TextDrawShowForPlayer(playerid, tText);
	if((fadeScreenCount[playerid] += fadeScreenSpeed[playerid]) > 255)
	{
		if(fadeScreenType[playerid]) TextDrawHideForPlayer(playerid, tText);
		else
		{
			fadeScreenCount[playerid] = 255;
			TextDrawBoxColor(tText, fadeScreenColor[playerid] + 255);
		}
		fadeScreenCount[playerid] = 0;
		if(fadeScreenTimer[playerid] != 0)
		{
			KillTimer(fadeScreenTimer[playerid]);
			fadeScreenTimer[playerid] = 0;
		}
	}
}
//***************************************************

//***************************************************
public OnPlayerConnect(playerid)
{
	if(IsPlayerNPC(playerid) == 0)
	{
		fadeScreen[playerid] = TextDrawCreate(1.000000,1.000000,"_");
		TextDrawUseBox(fadeScreen[playerid],1);
		TextDrawTextSize(fadeScreen[playerid],639.000000,0.000000);
		TextDrawAlignment(fadeScreen[playerid],0);
		TextDrawFont(fadeScreen[playerid],3);
		TextDrawLetterSize(fadeScreen[playerid],1.000000,50.000000);
		TextDrawBoxColor(fadeScreen[playerid], 0x000000FF);
		TextDrawShowForPlayer(playerid, fadeScreen[playerid]);
	}
	
	fadeScreenColor[playerid] = 0;
	fadeScreenCount[playerid] = 0;
	fadeScreenType[playerid] = 0;
	fadeScreenSpeed[playerid] = 0;
	fadeScreenTime[playerid] = 0;

	#if defined FADE_OnPlayerConnect
		return FADE_OnPlayerConnect(playerid);
	#else
		return 1;
	#endif
}

#if defined FADE_OnPlayerConnect
	forward FADE_OnPlayerConnect(playerid);
#endif
#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect FADE_OnPlayerConnect

public OnPlayerDisconnect(playerid, reason)
{
	TextDrawDestroy(fadeScreen[playerid]);
	KillTimer(fadeScreenTimer[playerid]);
	fadeScreenTimer[playerid] = 0;
	#if defined FADE_OnPlayerDisconnect
		return FADE_OnPlayerDisconnect(playerid, reason);
	#else
		return 1;
	#endif
}

#if defined FADE_OnPlayerDisconnect
	forward FADE_OnPlayerDisconnect(playerid, reason);
#endif
#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect FADE_OnPlayerDisconnect
//***************************************************