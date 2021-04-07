#ifndef FUN_TEMPLATE_H
#define FUN_TEMPLATE_H

#include <QtWidgets>

namespace fun_tempate
{
bool fIsCVEDuplicates(QStringList lstCVEDescription,QString strCVECount);

// Количество записей в строке
QString countRecordInString (QStringList lst,int iCountRecord)
{
    QString strText;
    QString str;
    int i=0; //счетчик подсчет количества элементов в lst
    if(lst.count()!=0){
        foreach (str, lst) {
            i++;
            strText+=str+"; ";
            if(i==iCountRecord){
                strText+="\n";
                i=0;
            }
        }
    }
    return strText;
}

//получение описания CVE способ 1 (удаляем дубликаты strCVECountDescription функцией lstCVEDescription.removeDuplicates() )
QStringList fCVEDescription(QStringList lstNotTag )
{
    QRegExp regCVE("((CVE-[0-9]{4}))");
    QRegExp regIdentifier("(([0-9]{6}))");
    QStringList lstCVEDescription;
    QString strIdentifier;
    int i=0;//подсчет CVE до 2
    QString strCVEDescription;
    foreach (QString str, lstNotTag) {
        if(regCVE.indexIn(str)==0){
            i++;
            // strCVEDescription+=strIdentifier+"\n";
        }
        else if(str=="Доступна информация")
            i=0;
        //        else
        //            strIdentifier=str;
        if(i==1){
            if(regIdentifier.indexIn(str)!=0)
                strCVEDescription+=str+"\n";
        }
        if(i==2){
            strCVEDescription="---"+strCVEDescription+"---";
            lstCVEDescription<<strCVEDescription;
            strCVEDescription.clear();
            strCVEDescription+=str+"\n";
            i=1;
        }
    }
    qDebug()<<"Конец отчета23";
    lstCVEDescription.removeDuplicates();
    return  lstCVEDescription;
}

//получение описания CVE(более простой чем первый, но дубликаты не удаляет) способ 2
QStringList fCVEDescription2(QStringList lstNotTag )
{
    QRegExp regCVE("((CVE-[0-9]{4}))");
    QRegExp regIdentifier("(([0-9]{6}))");
    QStringList lstCVEDescription;
    QStringList lstOneCVE;
    QString strIdentifier;
    int i=0;//подсчет CVE до 2
    bool flagCVE=false;
    QString strCVEDescription;
    foreach (QString str, lstNotTag) {
        if(regCVE.indexIn(str)==0){

            flagCVE=true;
            // strCVEDescription+=strIdentifier+"\n";
        }
        if(str=="Доступна информация")
            flagCVE=false;

        if( flagCVE==true)
            lstCVEDescription<<str;
    }
    qDebug()<<"Конец отчета77";
    // lstCVEDescription.removeDuplicates();
    return  lstCVEDescription;
}

//получение описания CVE (без дубликатов) способ 3 ()
QStringList fCVEDescription3(QStringList lstNotTag )
{
    QRegExp regCVE("((CVE-[0-9]{4}))");
    QStringList lstCVEDescription;
    QStringList lstOneCVE;
    QString strCVE;
    int i=0;//подсчет CVE до 2
    bool flagCVEDuplicates=false;
    QString strCVEDescription;
    foreach (QString str, lstNotTag) {
        if(regCVE.indexIn(str)==0){
            i++;
            strCVE=str;
            // strCVEDescription+=strIdentifier+"\n";
        }
        else if(str=="Доступна информация")
            i=0;

        if(i==1)
            lstOneCVE<<str;
        if(i==2){
            flagCVEDuplicates=fIsCVEDuplicates(lstCVEDescription,strCVE);
            if(flagCVEDuplicates==false)
                lstCVEDescription<<lstOneCVE;
            lstOneCVE.clear();
            lstOneCVE<<strCVE;
            i=1;
        }
    }
    qDebug()<<"Конец отчета00";
    //  lstCVEDescription.removeDuplicates();
    return  lstCVEDescription;
}

bool fIsCVEDuplicates(QStringList lstCVEDescription,QString strCVE)
{
    bool flagCVEDuplicates=false;
    QList<QString>::iterator it =
            qFind(lstCVEDescription.begin(),lstCVEDescription.end(),strCVE);
    if(it!=lstCVEDescription.end())
        flagCVEDuplicates=true;
    return flagCVEDuplicates;
}

//Шаблон(без описания CVE) - IP без описание CVE с выбором: уровня и ОС хоста
//1. Красиво оформить
QStringList fTemplateReportCVENotDescriptionWithSwitch(QStringList lstNotTag )
{
    QRegExp regIP("(10\\.50\\.)");
    QRegExp regCVE("(CVE)");
    QString strOS="Windows 10";
    QRegExp regOS("("+strOS+")");
    QRegExp regCVECritical("(Критический)");
    QRegExp regCVEHigh("(Высокий)");
    QRegExp regCVEMiddle("(Средний)");
    QRegExp regCVELow("(Низкий)");

    QStringList lstCVECritical;lstCVECritical<<"Критический уровень"<<"\n";
    QStringList lstCVEHigh;lstCVEHigh<<"Высокий уровень"<<"\n";
    QStringList lstCVEMiddle;lstCVEMiddle<<"\n"<<"Средний уровень"<<"\n";
    QStringList lstCVELow;lstCVELow<<"\n"<<"Низкий уровень"<<"\n";

    QStringList lstTemplateReport;
    QStringList lstIP;
    QStringList lstCVE;

    QString str1="Начало Отсчета";
    lstTemplateReport<<str1;

    QString strCVE;//
    QString strCVECount;//строка содержет 6 CVE
    QString strIP;// Содержет IP

    bool flagOS10=false;
    int iIp=0;//подсчет IP

    foreach (QString str, lstNotTag) {
        if(regIP.indexIn(str)==0){
            iIp++;
            lstCVECritical.removeDuplicates();
            lstCVEHigh.removeDuplicates();
            lstCVEMiddle.removeDuplicates();
            lstCVELow.removeDuplicates();

            lstCVE<<lstCVECritical;

            //формируем строки по 5 записей CVE
            strCVECount=countRecordInString(lstCVE,6);
            lstIP<<"IP Адрес"<<strIP;//текуйщий Ip
            lstIP<<strCVECount;
            strIP=str;//следующий Ip
        }
        else if(regCVE.indexIn(str)==0){
            strCVE=str;
        }
        else if(regCVECritical.indexIn(str)==0)
            lstCVECritical<<strCVE;
        else if(regCVEHigh.indexIn(str)==0)
            lstCVEHigh<<strCVE;
        else if(regCVEMiddle.indexIn(str)==0)
            lstCVEMiddle<<strCVE;
        else if(regCVELow.indexIn(str)==0)
            lstCVELow<<strCVE;

        else if(regOS.indexIn(str)>=0){
            flagOS10=true;
        }
        if(iIp==2){
            if(flagOS10==true){
                lstTemplateReport<<lstIP;
            }
            iIp=1;
            flagOS10=false;
            lstCVE.clear();
            lstIP.clear();
            strCVECount.clear();
        }
    }
    lstTemplateReport<<"Конец отсчета ";
    qDebug()<<"Конец отчета0";
    return lstTemplateReport;
}

//Шаблон(без описания) - IP CVE(баг- последний IP не записывает)
QStringList fTemplateReportCVENotDescription(QStringList lstNotTag )
{
    QRegExp regIP("(10\\.50\\.)");
    QRegExp regCVE("(CVE)");
    QStringList lstTemplateReport;
    QStringList lstIP;
    QStringList lstCVE;
    QString strIP;
    QString str1="Начало Отчета";
    lstTemplateReport<<str1;
    QString strCVE;
    foreach (QString str, lstNotTag) {
        if(regIP.indexIn(str)==0){

            lstCVE.removeDuplicates();
            //формируем строки по 5 записей CVE
            strCVE=countRecordInString(lstCVE,6);
            lstTemplateReport<<strCVE;
            lstTemplateReport<<"IP Адрес"<<strIP;
            lstCVE.clear();
            strCVE.clear();
            strIP=str;
        }
        else if(regCVE.indexIn(str)==0){
            lstCVE<<str;
        }
    }
    lstTemplateReport<<"Конец отсчета ";
    qDebug()<<"Конец отчета500";
    return lstTemplateReport;
}

//Шаблон(Полное описание) - IP CVE Описание
/*QStringList fTemplateReportCVENotDescription(QStringList lstNotTag )
        {
            QRegExp regIP("(10\\.50\\.)");
            QRegExp regCVE("(CVE)");
            QRegExp regVulnerabilityLevel("(уровень)");
            QStringList lstTemplateReport;
            QStringList lstCVE;
            QString str1="Начало Отсчета";
            lstTemplateReport<<str1;
            bool flagVulnerability=false;
            bool flagIP=false;
            QString strCVE;
            int i=0; //счетчик подсчет количества CVE в строке
            int x=0;
            foreach (QString str, lstNotTag) {
                if(regIP.indexIn(str)==0){
                    //формируем строки по 7 записей CVE
                 strCVE=countRecordInString(lstCVE,icountCVE);
                   ////////////////////////////////////
                    lstTemplateReport<<"IP Адрес"<<"--"<<str<<"--"<<"\n";
                    lstTemplateReport<<strCVE;
                    lstCVE.clear();
                    strCVE.clear();

                }
                else if(regCVE.indexIn(str)==0){
                    lstCVE<<str;
                }
                //код для формирования полного отчета
                //        else if(regVulnerabilityLevel.indexIn(str)>0){
                //            lstTemplateReport<<str;
                //            flagVulnerability=true;
                //        }
                //        else if(flagVulnerability==true){
                //            lstTemplateReport<<str;
                //            if(str=="-"){
                //                flagVulnerability=false;
                //            }
                //        }
            }
            lstTemplateReport<<"Конец отсчета ";
            qDebug()<<"Конец отчета500";
            return lstTemplateReport;
        }
        */
}

#endif // FUN_TEMPLATE_H
