###### В OnGameModeInit<br><br>
```PAWN 
for(new i; i < sizeof(TRIGGERS); i++)
{
	switch(TRIGGERS[i][nState])
	{
		case 1: TRIGGERS[i][nPickup] = CreateDynamicPickup(18087, 23, TRIGGERS[i][nPos][0], TRIGGERS[i][nPos][1], TRIGGERS[i][nPos][2], TRIGGERS[i][nVirtual], TRIGGERS[i][nInterior], -1);
		case 2..9: TRIGGERS[i][nSphere] = CreateDynamicSphere(TRIGGERS[i][nPos][0], TRIGGERS[i][nPos][1], TRIGGERS[i][nPos][2], 5.0, TRIGGERS[i][nVirtual], TRIGGERS[i][nInterior]); 
	}
}
```

<br><br>

###### /triggerdebug - debug<br>
###### /createtriggerstext - создаст 3д текст на каждом из триггеров <br><br>

###### Видео-демонстрация:  https://youtu.be/scniSavpuAA
