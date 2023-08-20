В OnGameModeInit<br>
<code>for(new i; i < sizeof(TRIGGERS); i++)
{
  TRIGGERS[i][nPickup] = CreateDynamicPickup(19300, 23, TRIGGERS[i][nPos][0], TRIGGERS[i][nPos][1], TRIGGERS[i][nPos][2], TRIGGERS[i][nVirtual], TRIGGERS[i][nInterior], -1);
}</code>
<br>
В include встроены две дебаг-команды: <br>
/triggerdebug - будет выводить сообщения, связанные с ваши и триггерами <br>
/createtriggerstext - создаст 3д текст на каждом из триггеров <br><br>

Видео-демонстрация:  https://youtu.be/scniSavpuAA
