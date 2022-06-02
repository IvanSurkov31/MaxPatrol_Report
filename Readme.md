# Программа MaxPatrol_Report

Создает отчет из XML файла программы MaxPatrol (парсинг XML файла программы MaxPatrol). Написано на C++/Qt5.12

## Инструкция:

1. Формируем отчет в MaxPatrol в XML формате.
2. С помощью программы kfk разбиваем файл XML-MaxPatrol на части (< 20 000 КБ один файл).
3. Сохраняем файлы kfk в отдельную папку (FileXML).
3. Запускаем MaxPatrol_Report.exe и нажимаем «Сформировать отчет».
4. Файл ReportMaxPatrol.txt переводим в pdf формат – отчёт готов.

![](./image/MaxPatrol_Report.jpg)


