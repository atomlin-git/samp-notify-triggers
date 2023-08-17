Удобная и практичная система уведомлений на местах нажатия клавиш

Для удобного использования в своём моде, рекомендую установить include-помощник для дебага - https://github.com/atomlin-git/pawn_portfolio_debugmessages <br><br>
<b>Если вы не хотите использовать include-помощник для дебага, удалите все упоминания SEND_DEBUG_MESS и SEND_DEBUG_MESSAGE из include, иначе он не скомпилируется</b><br><br>
<b>Так же, в include используется stock FixText, которого в вашем моде вероятнее всего нет, это локализатор текста в текстдраве</b><br><br>

После установки в своём моде, вам потребуется в OnGameModeInit вставить следующий код:
<code>
for(new i; i < sizeof(TRIGGERS); i++)
{
  TRIGGERS[i][nPickup] = CreateDynamicPickup(19300, 23, TRIGGERS[i][nPos][0], TRIGGERS[i][nPos][1], TRIGGERS[i][nPos][2], TRIGGERS[i][nVirtual], TRIGGERS[i][nInterior], -1);
}
</code>

В include встроены две дебаг-команды: <br>
/triggerdebug - будет выводить сообщения, связанные с ваши и триггерами <br>
/createtriggerstext - создаст 3д текст на каждом из триггеров <br><br>

Видео-демонстрация:  
