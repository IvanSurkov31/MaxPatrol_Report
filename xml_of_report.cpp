#include "xml_of_report.h"
#include "Fun_Common.h"
#include "Fun_Template.h"
#include <QtWidgets>

//1. Считать данные с XML файла +
//2. Удалить теги +
//3. Разобраться с кадеровкой +
//4. Сформировать отчет по шаблону +
//5. Разбираемся с файлом XML()
//5.1 Разбить файл (сделали с помощью стороней программы. Возможно сделать
// через командною строку) +-
//6. Формируем шаблон
//6.1 Записать в конец файла все уязвимости +
//6.2 Удалить дубликаты списка уязвимостей +
//6.3 Отфильтровать уязвимости оп критичности++(оформить записи красиво)
//6.4 Отфильтровать хосты по ОС+
//8. Каждый разбитый файл редактируем по шаблону и сохраняем в один файл
//8.1 Почитать многопоточность. Попробовать записывать файлы потоками
//9. Рисуем интерфейс (интерфейс будет отдельным классом)

XML_of_Report::XML_of_Report(QWidget *parent) :
    QWidget(parent)
{
    //считали файл xml
    QString strFileReportXML=fun_common::fFileRead("generated17804.xml.kk0",this);
    //декодировали данные
    strFileReportXML=fun_common::fDecodeString(strFileReportXML);
    //удалили тэги
    QStringList lstNotTag=fun_common::fDeleteTag(strFileReportXML);
    QString strNotTag;
    foreach (QString str, lstNotTag) {
        strNotTag+=str+"\n";
    }
    //записали в файл textdok.txt данные без тэгов
    fun_common::fFileWrite("textdok.txt",strNotTag,"WriteOnly");
    //  QString strNotTagFromFile=functions::fFileRead("textdok.txt",this);
    //формируем отчет по шаблону
    QStringList lstTemplateReport=fun_tempate::fCVEDescription(lstNotTag);
    QString strTemplateReport;
    foreach (QString str, lstTemplateReport) {
        strTemplateReport+=str+"\n";
    }
    // записываем отчет по шаблону в файл ReportMaxPatrol.txt
    fun_common::fFileWrite("ReportMaxPatrol.txt",strTemplateReport,"WriteOnly");
}
