#ifndef FUN_COMMON_H
#define FUN_COMMON_H

#include <QtWidgets>

namespace fun_common
{

QString checkExistenceString(QStringList lstCheck,int numberString)
{
    QString str="";
    if(lstCheck.count()>numberString)
        str=lstCheck[numberString];
    return str;
}

QStringList fDeleteTag(QString strfile)
{
    QStringList lst,lst22,lst33;
    QString str;
    QStringList lstXML=strfile.split("><");
    QList<QString>::iterator it=lstXML.begin();
    for(;it!=lstXML.end();++it)
    {
        str= *it;
        lst=str.split(">");
        lst22<<checkExistenceString(lst,1);
    }
    lst.clear();
    QList<QString>::iterator it22=lst22.begin();
    for(;it22!=lst22.end();++it22)
    {
        str= *it22;
        lst33=str.split("<",QString::SkipEmptyParts);
        if(checkExistenceString(lst33,0)!="")
            lst<<checkExistenceString(lst33,0);
    }
    return lst;
}

QString fFileRead(QString strNameFile,QWidget *parent)
{
    QString str;
    QFile file(strNameFile);
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(parent, QString::fromUtf8("Ошибка"), QString::fromUtf8("Ошибка открытия файла"));
        return str="Ошибка";
    }
    file.close();

    if(file.open(QIODevice::ReadOnly)){
        QTextStream stream(&file);
        str=stream.readAll();
        file.close();
        if (stream.status()!=QTextStream::Ok){
            QMessageBox::critical(parent, QString::fromUtf8("Ошибка"), QString::fromUtf8("Ошибка записи с файла"));
            return str="Ошибка";
        }
    }
    return str;
}

void fFileWrite(QString strNameFile,QString strData,QString strIsWriteOnly){
    QFile file(strNameFile);
    file.remove();
    if(strIsWriteOnly=="WriteOnly")
    {
        if(file.open(QIODevice::WriteOnly)){
            QTextStream stream(&file);
            stream<<strData;
            file.close();
            if (stream.status()!=QTextStream::Ok){
                qDebug()<<"Ошибка записи файла";
            }
        }
    }
    else if(strIsWriteOnly=="Truncate")
    {
        if(file.open(QIODevice::Truncate)){
            QTextStream stream(&file);
            stream<<strData;
            file.close();
            if (stream.status()!=QTextStream::Ok){
                qDebug()<<"Ошибка записи файла";
            }
        }
    }
    else if(strIsWriteOnly=="Append")
    {
        if(file.open(QIODevice::Append)){
            QTextStream stream(&file);
            stream<<strData;
            file.close();
            if (stream.status()!=QTextStream::Ok){
                qDebug()<<"Ошибка записи файла";
            }
        }
    }
}

//получение описания CVE
//QStringList fCVEDescription(QStringList lstNotTag )
//{
//    QRegExp regIP("(10\\.50\\.)");
//    QRegExp regCVE("(CVE)");
//    QStringList lstTemplateReport;
//    QStringList lstCVE;
//    QString str1="Начало Отсчета";
//    lstTemplateReport<<str1;
//    QString strCVE;
//    int i=0; //счетчик подсчет количества CVE в строке
//    foreach (QString str, lstNotTag) {
//        if(regCVE.indexIn(str)==0){
//            //формируем строки по 7 записей CVE
//            if(lstCVE.count()!=0){
//            foreach (str1, lstCVE) {
//                i++;
//                strCVE+=str1+"; ";
//                if(i==7){
//                    strCVE+="\n";
//                    i=0;
//                }
//            }
//            }
//           ////////////////////////////////////
//            lstTemplateReport<<str;
//            lstTemplateReport<<strCVE;
//            lstCVE.clear();
//            strCVE.clear();
//        }
//        else if(regCVE.indexIn(str)==0){
//            lstCVE<<str;
//        }
//    }
//    lstTemplateReport<<"Конец отсчета ";
//    qDebug()<<"Конец отчета500";
//    return lstTemplateReport;
//}

//Шаблон(без описания) - IP CVE
QStringList fTemplateReportCVENotDescription(QStringList lstNotTag )
{
    QRegExp regIP("(10\\.50\\.)");
    QRegExp regCVE("(CVE)");
    QStringList lstTemplateReport;
    QStringList lstCVE;
    QString str1="Начало Отсчета";
    lstTemplateReport<<str1;
    QString strCVE;
    bool flagCVE=true;
    int i=0; //счетчик подсчет количества CVE в строке
    foreach (QString str, lstNotTag) {
        if(regIP.indexIn(str)==0){
            //формируем строки по 7 записей CVE
            if(lstCVE.count()!=0){
            foreach (str1, lstCVE) {
                i++;
                strCVE+=str1+"; ";
                if(i==5){
                    strCVE+="\n";
                    i=0;
                }
            }
            }
           ////////////////////////////////////
            lstTemplateReport<<"IP Адрес"<<"--"<<str<<"--"<<"\n";
            lstTemplateReport<<strCVE;
            lstCVE.clear();
            strCVE.clear();

        }

      //  код для формирования полного отчета
//                else if(regVulnerabilityLevel.indexIn(str)>0){
//                    lstTemplateReport<<str;
//                    flagVulnerability=true;
//                }
//                else if(flagVulnerability==true){
//                    lstTemplateReport<<str;
//                    if(str=="-"){
//                        flagVulnerability=false;
//                    }
//                }

        else if(regCVE.indexIn(str)==0){
            lstCVE<<str;
        }
    }
    lstTemplateReport<<"Конец отсчета ";
    qDebug()<<"Конец отчета500";
    return lstTemplateReport;
}

//Шаблон(Полное описание) - IP CVE Описание
//QStringList fTemplateReportCVENotDescription(QStringList lstNotTag )
//{
//    QRegExp regIP("(10\\.50\\.)");
//    QRegExp regCVE("(CVE)");
//    QRegExp regVulnerabilityLevel("(уровень)");
//    QStringList lstTemplateReport;
//    QStringList lstCVE;
//    QString str1="Начало Отсчета";
//    lstTemplateReport<<str1;
//    bool flagVulnerability=false;
//    bool flagIP=false;
//    QString strCVE;
//    int i=0; //счетчик подсчет количества CVE в строке
//    int x=0;
//    foreach (QString str, lstNotTag) {
//        if(regIP.indexIn(str)==0){
//            //формируем строки по 7 записей CVE
//            if(lstCVE.count()!=0){
//            foreach (str1, lstCVE) {
//                i++;
//                strCVE+=str1+"; ";
//                if(i==7){
//                    strCVE+="\n";
//                    i=0;
//                }
//            }
//            }
//           ////////////////////////////////////
//            lstTemplateReport<<"IP Адрес"<<"--"<<str<<"--"<<"\n";
//            lstTemplateReport<<strCVE;
//            lstCVE.clear();
//            strCVE.clear();

//        }
//        else if(regCVE.indexIn(str)==0){
//            lstCVE<<str;
//        }
//        //код для формирования полного отчета
//        //        else if(regVulnerabilityLevel.indexIn(str)>0){
//        //            lstTemplateReport<<str;
//        //            flagVulnerability=true;
//        //        }
//        //        else if(flagVulnerability==true){
//        //            lstTemplateReport<<str;
//        //            if(str=="-"){
//        //                flagVulnerability=false;
//        //            }
//        //        }
//    }
//    lstTemplateReport<<"Конец отсчета ";
//    qDebug()<<"Конец отчета500";
//    return lstTemplateReport;
//}

//меняем кодировку QString
QString fDecodeString(QString strCode )
{
    QByteArray encodedString =strCode.toLocal8Bit() ;
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QString strDecode = codec->toUnicode(encodedString);

    return strDecode;
}
}

#endif // FUN_COMMON_H
