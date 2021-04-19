#include "Fun_Common.h"

#include "Report_Generation.h"
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
    QString str;
    QStringList lstXML=strfile.split("><");
    QStringList lst,lst22,lst33;
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

QString fFileRead(QString strNameFile)
{
    QString strError;
    QString str;
    QFile file(strNameFile);
    if(!file.open(QIODevice::ReadOnly))
    {
       // QMessageBox::critical(parent, QString::fromUtf8("Ошибка"), QString::fromUtf8("Ошибка открытия файла"));
        strError="error file";
        return strError;
    }
    file.close();

    if(file.open(QIODevice::ReadOnly)){
        QTextStream stream(&file);
        str=stream.readAll();
        file.close();
        if (stream.status()!=QTextStream::Ok){
        //    QMessageBox::critical(parent, QString::fromUtf8("Ошибка"), QString::fromUtf8("Ошибка записи с файла"));
            strError="error file";
            return strError;
        }
    }
    return str;
}

QString fFileWrite(QString strNameFile,QString strData,QString strIsWriteOnly)
{
    QString strError;
    QString str;
    QFile file(strNameFile);
    //file.remove();
    if(strIsWriteOnly=="WriteOnly")
    {
        if(file.open(QIODevice::WriteOnly)){
            QTextStream stream(&file);
            stream<<strData;
            file.close();
            if (stream.status()!=QTextStream::Ok){
          //      QMessageBox::critical(parent, QString::fromUtf8("Ошибка"), QString::fromUtf8("Ошибка записи с файла"));
                strError="error file";
                return strError;
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
          //      QMessageBox::critical(parent, QString::fromUtf8("Ошибка"), QString::fromUtf8("Ошибка записи с файла"));
                strError="error file";
                return strError;
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
            //  QMessageBox::critical(parent, QString::fromUtf8("Ошибка"), QString::fromUtf8("Ошибка записи с файла"));
                strError="error file";
                return strError;
            }
        }
    }
}

QString fDecodeString(QString strCode )
{
    QByteArray encodedString =strCode.toLocal8Bit() ;
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QString strDecode = codec->toUnicode(encodedString);

    return strDecode;
}

}
