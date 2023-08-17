enum TRIGGERS_ENUM
{
    Float:nPos[3],
	nNotif[64],
	nKey,
	nVirtual,
	nInterior,
	nPickup
}

new TRIGGERS[2][TRIGGERS_ENUM] =
{
	{{1751.5178, -2048.2554, 20.1879}, "Ïîãîâîðèòü ñ ïåðñîíàæåì", 1024, 0, 0},
	{{1744.1252, -2048.0156, 20.6215}, "Çàãðóçèòü ãðóç â ìàøèíó", 1024, 0, 0}
};

new PlayerText:TRIGGER_NOTIFY_TD[MAX_PLAYERS][3];

new PLAYER_TRIGGER_TIMER[MAX_PLAYERS];
new PLAYER_TRIGGER_ID[MAX_PLAYERS];
new PLAYER_TRIGGER_DEBUG[MAX_PLAYERS];

stock GET_KEY_NAME(ID)
{
	new KEY_NAME[8];
	switch(ID)
	{
		case 0: KEY_NAME = "None";
		case 1: KEY_NAME = "CTRL";
		case 2: KEY_NAME = "H / C";
		case 4: KEY_NAME = "ËÊÌ";
		case 8: KEY_NAME = "SPACE";
		case 16: KEY_NAME = "ENTER";
		case 32: KEY_NAME = "SHIFT";
		case 64: KEY_NAME = "E";
		case 128: KEY_NAME = "ÏÊÌ";
		case 256: KEY_NAME = "Q";
		case 320: KEY_NAME = "2";
		case 512: KEY_NAME = "2";
		case 1024: KEY_NAME = "ALT";
		case 2048: KEY_NAME = "NUM-8";
		case 4096: KEY_NAME = "NUM-2";
		case 8192: KEY_NAME = "NUM-4";
		case 16384: KEY_NAME = "NUM-6";
		case 65536: KEY_NAME = "Y";
		case 131072: KEY_NAME = "N";
		case 262144: KEY_NAME = "H";
	}
	return KEY_NAME;
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(GetPlayerState(playerid) == 9 || GetPlayerState(playerid) == 7) return 1;
	if(PLAYER_TRIGGER_ID[playerid] == -1) return 1;
	
	new tId = PLAYER_TRIGGER_ID[playerid];

	if(PLAYER_TRIGGER_DEBUG[playerid]) SEND_DEBUG_MESSAGE(playerid, 0xFF0000FF, "KEY_IN_TRIGGER: %d | KEY_IN_PUBLIC: %d | TRIGGER_ID: %d", TRIGGERS[tId][nKey], newkeys, tId);

	if(!IsPlayerInRangeOfPoint(playerid, 5.0, TRIGGERS[tId][nPos][0], TRIGGERS[tId][nPos][1], TRIGGERS[tId][nPos][2])) return 1;
	if(GetPlayerVirtualWorld(playerid) != TRIGGERS[tId][nVirtual]) return 1;
	if(GetPlayerInterior(playerid) != TRIGGERS[tId][nInterior]) return 1;
	if(TRIGGERS[tId][nKey] != newkeys) return 1;

	switch(tId)
	{
		case 0:
		{
			SendClientMessage(playerid, -1, "Îõõ.. Ïðèâåò!");
		}

		case 1:
		{
			SendClientMessage(playerid, -1, "Âû çàãóçèëè ÷òî-òî â ìàøèíó!");
		}

		default: SendClientMessage(playerid, 0xFF0000FF, "Ïðîèçîøëà îøèáêà! Ñîîáùèòå ðàçðàáîò÷èêàì ïðîåêòà");
	}

	return _OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
}

public OnPlayerPickUpDynamicPickup(playerid, pickupid)
{
    if(GetPlayerState(playerid) == 9 || GetPlayerState(playerid) == 7) return 1;

	for(new i; i < sizeof(TRIGGERS); i++)
	{
		if(!IsValidPickup(TRIGGERS[i][nPickup])) return 1;

		if(TRIGGERS[i][nPickup] == pickupid)
		{
			if(PLAYER_TRIGGER_DEBUG[playerid]) SEND_DEBUG_MESSAGE(playerid, 0xFF0000FF, "TRIGGER_ID: %d | TRIGGER_KEY: %d | %d, %d - VW, INT", i, TRIGGERS[i][nKey], TRIGGERS[i][nVirtual], TRIGGERS[i][nInterior]);

			if(GetPlayerVirtualWorld(playerid) != TRIGGERS[i][nVirtual]) return 1;
			if(GetPlayerInterior(playerid) != TRIGGERS[i][nInterior]) return 1;
			if(!IsPlayerInRangeOfPoint(playerid, 15.0, TRIGGERS[i][nPos][0], TRIGGERS[i][nPos][1], TRIGGERS[i][nPos][2])) return 1;
			if(PLAYER_TRIGGER_ID[playerid] != -1) return 1;

			ActionNotifyTrigger(playerid, 0);

			new tempNotify[64];
			format(tempNotify, 64, "%s", FixText(TRIGGERS[i][nNotif]));
			PlayerTextDrawSetString(playerid, TRIGGER_NOTIFY_TD[playerid][1], tempNotify);

			new tempNotifyKey[41];
			format(tempNotifyKey, 41, "Äëÿ âçàèìîäåéñòâèÿ - èñïîëüçóéòå %s", GET_KEY_NAME(TRIGGERS[i][nKey]));
			PlayerTextDrawSetString(playerid, TRIGGER_NOTIFY_TD[playerid][2], FixText(tempNotifyKey));

			ActionNotifyTrigger(playerid, 1);

			PLAYER_TRIGGER_ID[playerid] = i;
			PLAYER_TRIGGER_TIMER[playerid] = SetTimerEx("TRIGGER_TIMER", 1000, 1, "d", playerid);

			break;
		}
	}

	return _OnPlayerPickUpDynamicPickup(playerid, pickupid);
}

forward TRIGGER_TIMER(playerid);
public TRIGGER_TIMER(playerid)
{
	new tId = PLAYER_TRIGGER_ID[playerid];
	if(!IsPlayerInRangeOfPoint(playerid, 5.0, TRIGGERS[tId][nPos][0], TRIGGERS[tId][nPos][1], TRIGGERS[tId][nPos][2]) || GetPlayerInterior(playerid) != TRIGGERS[tId][nInterior] || GetPlayerVirtualWorld(playerid) != TRIGGERS[tId][nVirtual])
	{
		if(PLAYER_TRIGGER_DEBUG[playerid]) SEND_DEBUG_MESS(playerid, 0xFF0000FF, "Kill PLAYER_TRIGGER_TIMER");
		KillTimer(PLAYER_TRIGGER_TIMER[playerid]);
		PLAYER_TRIGGER_TIMER[playerid] = -1;
		PLAYER_TRIGGER_ID[playerid] = -1;
		ActionNotifyTrigger(playerid, 2);
		return 1;
	}

	if(PLAYER_TRIGGER_DEBUG[playerid]) SEND_DEBUG_MESS(playerid, 0xFF0000FF, "TRIGGER_TIMER");

	return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
	if(PLAYER_TRIGGER_TIMER[playerid]) KillTimer(PLAYER_TRIGGER_TIMER[playerid]);
	ActionNotifyTrigger(playerid, 3);
	return _OnPlayerDisconnect(playerid, reason);
}

public OnPlayerConnect(playerid)
{
	PLAYER_TRIGGER_DEBUG[playerid] = 0;
	PLAYER_TRIGGER_ID[playerid] = -1;
	PLAYER_TRIGGER_TIMER[playerid] = -1;
	return _OnPlayerConnect(playerid);
}

stock ActionNotifyTrigger(playerid, action)
{
	//0 - create, 1 - show, 2 - hide, 3 - destroy
	if(!IsPlayerConnected(playerid)) return 1;
	switch(action)
	{
		case 0:
		{
			TRIGGER_NOTIFY_TD[playerid][0] = CreatePlayerTextDraw(playerid, 254.0000, 365.8816, "Box");
			PlayerTextDrawLetterSize(playerid, TRIGGER_NOTIFY_TD[playerid][0], 0.0000, 4.1666);
			PlayerTextDrawTextSize(playerid, TRIGGER_NOTIFY_TD[playerid][0], 389.0000, 0.0000);
			PlayerTextDrawAlignment(playerid, TRIGGER_NOTIFY_TD[playerid][0], 1);
			PlayerTextDrawColor(playerid, TRIGGER_NOTIFY_TD[playerid][0], -1);
			PlayerTextDrawUseBox(playerid, TRIGGER_NOTIFY_TD[playerid][0], 1);
			PlayerTextDrawBoxColor(playerid, TRIGGER_NOTIFY_TD[playerid][0], 255);
			PlayerTextDrawBackgroundColor(playerid, TRIGGER_NOTIFY_TD[playerid][0], 255);
			PlayerTextDrawFont(playerid, TRIGGER_NOTIFY_TD[playerid][0], 1);
			PlayerTextDrawSetProportional(playerid, TRIGGER_NOTIFY_TD[playerid][0], 1);
			PlayerTextDrawSetShadow(playerid, TRIGGER_NOTIFY_TD[playerid][0], 0);

			TRIGGER_NOTIFY_TD[playerid][1] = CreatePlayerTextDraw(playerid, 320.0003, 366.7109, "Œo™o¢opœ¦©_c_£epco®a›e¯");
			PlayerTextDrawLetterSize(playerid, TRIGGER_NOTIFY_TD[playerid][1], 0.1510, 1.0441);
			PlayerTextDrawAlignment(playerid, TRIGGER_NOTIFY_TD[playerid][1], 2);
			PlayerTextDrawColor(playerid, TRIGGER_NOTIFY_TD[playerid][1], -1061109505);
			PlayerTextDrawBackgroundColor(playerid, TRIGGER_NOTIFY_TD[playerid][1], 255);
			PlayerTextDrawFont(playerid, TRIGGER_NOTIFY_TD[playerid][1], 2);
			PlayerTextDrawSetProportional(playerid, TRIGGER_NOTIFY_TD[playerid][1], 1);
			PlayerTextDrawSetShadow(playerid, TRIGGER_NOTIFY_TD[playerid][1], 0);

			TRIGGER_NOTIFY_TD[playerid][2] = CreatePlayerTextDraw(playerid, 323.0003, 392.4294, "ƒž¬_¢Ÿaœ¯ošec¦¢œ¬_-_œc£ož©Ÿy¦e_ALT");
			PlayerTextDrawLetterSize(playerid, TRIGGER_NOTIFY_TD[playerid][2], 0.1380, 0.8325);
			PlayerTextDrawAlignment(playerid, TRIGGER_NOTIFY_TD[playerid][2], 2);
			PlayerTextDrawColor(playerid, TRIGGER_NOTIFY_TD[playerid][2], -1061109505);
			PlayerTextDrawBackgroundColor(playerid, TRIGGER_NOTIFY_TD[playerid][2], 255);
			PlayerTextDrawFont(playerid, TRIGGER_NOTIFY_TD[playerid][2], 2);
			PlayerTextDrawSetProportional(playerid, TRIGGER_NOTIFY_TD[playerid][2], 1);
			PlayerTextDrawSetShadow(playerid, TRIGGER_NOTIFY_TD[playerid][2], 0);
		}
		case 1:
		{
			PlayerTextDrawShow(playerid, TRIGGER_NOTIFY_TD[playerid][0]);
			PlayerTextDrawShow(playerid, TRIGGER_NOTIFY_TD[playerid][1]);
			PlayerTextDrawShow(playerid, TRIGGER_NOTIFY_TD[playerid][2]);
		}
		case 2:
		{
			PlayerTextDrawHide(playerid, TRIGGER_NOTIFY_TD[playerid][0]);
			PlayerTextDrawHide(playerid, TRIGGER_NOTIFY_TD[playerid][1]);
			PlayerTextDrawHide(playerid, TRIGGER_NOTIFY_TD[playerid][2]);
		}
		case 3:
		{
			PlayerTextDrawDestroy(playerid, TRIGGER_NOTIFY_TD[playerid][0]);
			PlayerTextDrawDestroy(playerid, TRIGGER_NOTIFY_TD[playerid][1]);
			PlayerTextDrawDestroy(playerid, TRIGGER_NOTIFY_TD[playerid][2]);
		}
	}

	return 1;
}

CMD:createtriggerstext(playerid)
{
	for(new i; i < sizeof(TRIGGERS); i++)
	{
		CreatePlayer3DTextLabel(playerid, TRIGGERS[i][nNotif], -1, TRIGGERS[i][nPos][0], TRIGGERS[i][nPos][1], TRIGGERS[i][nPos][2], 10.0);
	}
	return 1;
}

CMD:triggerdebug(playerid)
{
	PLAYER_TRIGGER_DEBUG[playerid] = !PLAYER_TRIGGER_DEBUG[playerid];
	SEND_DEBUG_MESSAGE(playerid, 0xFF0000FF, "PLAYER_TRIGGER_DEBUG: %d", PLAYER_TRIGGER_DEBUG[playerid]);
	return 1;
}

/////////////////////////////////////////////////////////////////

#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif

#define OnPlayerDisconnect _OnPlayerDisconnect
#if defined _OnPlayerDisconnect
	forward _OnPlayerDisconnect(playerid, reason);
#endif

#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif

#define OnPlayerConnect _OnPlayerConnect
#if defined _OnPlayerConnect
	forward _OnPlayerConnect(playerid);
#endif

#if defined __OnPlayerPickUpDynamicPickup
	#undef OnPlayerPickUpDynamicPickup
#else
	#define __OnPlayerPickUpDynamicPickup
#endif

#define OnPlayerPickUpDynamicPickup _OnPlayerPickUpDynamicPickup
#if defined _OnPlayerPickUpDynamicPickup
	forward _OnPlayerPickUpDynamicPickup(playerid, pickupid);
#endif

#if defined _ALS_OnPlayerKeyStateChange
	#undef OnPlayerKeyStateChange
#else
	#define _ALS_OnPlayerKeyStateChange
#endif

#define OnPlayerKeyStateChange _OnPlayerKeyStateChange
#if defined _OnPlayerKeyStateChange
	forward _OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
#endif
