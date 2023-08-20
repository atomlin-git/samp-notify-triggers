В OnGameModeInit<br><br>
<code>for(new i; i < sizeof(TRIGGERS); i++)
{
  TRIGGERS[i][nPickup] = CreateDynamicPickup(19300, 23, TRIGGERS[i][nPos][0], TRIGGERS[i][nPos][1], TRIGGERS[i][nPos][2], TRIGGERS[i][nVirtual], TRIGGERS[i][nInterior], -1);
}</code>
<br><br>
/triggerdebug - debug<br>
/createtriggerstext - создаст 3д текст на каждом из триггеров <br><br>

Видео-демонстрация:  https://youtu.be/scniSavpuAA
