#include "Report_Generation.h"
#include "Fun_Common.h"
#include <QtWidgets>
#include <QtConcurrent/QtConcurrent>

ReportGenerationInterface::ReportGenerationInterface(QWidget *parent) :
    QWidget(parent)
{
    gbCommon=new QGroupBox("&Формирование отчёта");

    gbOS=new QGroupBox("&ОС");
    rbAllHost=new  QRadioButton("&Все хосты");
    rbWind10Host=new  QRadioButton("&Только Windows 10");
    rbWind10Host->setChecked(true);

    gbLevelCVE=new QGroupBox("&Уровень критичности");
    cbCVECritical=new  QCheckBox("&Критичный");
    cbCVECritical->setChecked(true);
    cbCVEHigh=new  QCheckBox("&Высокий");
    cbCVEMiddle=new  QCheckBox("&Средний");
    cbCVELow=new  QCheckBox("&Низкий");

    gbDescriptionCVE=new QGroupBox("&Описание CVE");
    rbDescriptionAllHost=new QRadioButton("&Описание каждого хоста");
    rbAndReport=new QRadioButton("&В конце отчета");
    rbSeparateFile=new QRadioButton("&Отдельным файлом");
    rbNotGeneration=new QRadioButton("&Не формировать");
    rbNotGeneration->setChecked(true);

    pbReportGeneration=new QPushButton("&Сформировать отчёт");

    lblDirectory=new QLabel("Директория ");
    pbDirectory=new  QPushButton(QPixmap(":/fileopen.png"), "");
    leDirectory= new QLineEdit(QDir::current().absolutePath()+"/FileXML");

    VBLgbOS=new QVBoxLayout ;
    VBLgbOS->addWidget(rbAllHost);
    VBLgbOS->addWidget(rbWind10Host);
    VBLgbOS->addStretch();

    VBLgbLevelCVE=new QVBoxLayout;
    VBLgbLevelCVE->addWidget(cbCVECritical);
    VBLgbLevelCVE->addWidget(cbCVEHigh);
    VBLgbLevelCVE->addWidget(cbCVEMiddle);
    VBLgbLevelCVE->addWidget(cbCVELow);
    VBLgbLevelCVE->addStretch();

    VBLgbDescriptionCVE=new QVBoxLayout;
    VBLgbDescriptionCVE->addWidget(rbDescriptionAllHost);
    VBLgbDescriptionCVE->addWidget(rbAndReport);
    VBLgbDescriptionCVE->addWidget(rbSeparateFile);
    VBLgbDescriptionCVE->addWidget(rbNotGeneration);
    VBLgbDescriptionCVE->addStretch();

    HBLDirectory=new QHBoxLayout;
    HBLDirectory->addWidget(lblDirectory);
    HBLDirectory->addWidget(leDirectory);
    HBLDirectory->addWidget(pbDirectory);

    gbOS->setLayout(VBLgbOS);
    gbLevelCVE->setLayout(VBLgbLevelCVE);
    gbDescriptionCVE->setLayout(VBLgbDescriptionCVE);

    VBL1=new  QVBoxLayout;
    VBL1->addWidget(gbOS);
    VBL1->addWidget(gbLevelCVE);

    VBL2=new QVBoxLayout;
    VBL2->addWidget(gbDescriptionCVE);
    VBL2->addLayout(HBLDirectory);
    VBL2->addWidget(pbReportGeneration);

    HBLgbCommon=new QHBoxLayout;
    HBLgbCommon->addLayout(VBL1);
    HBLgbCommon->addLayout(VBL2);

    gbCommon->setLayout(HBLgbCommon);

    HBLResult=new QHBoxLayout;
    HBLResult->addWidget(gbCommon);

    this->setLayout(HBLResult);

    connect(pbReportGeneration, SIGNAL(clicked()),
            this,SLOT(slot_clicked_pbReportGeneration()));

    connect(pbDirectory, SIGNAL(clicked()),
            this,SLOT(slot_clicked_pbDirectory()));
}

void ReportGenerationInterface::slot_clicked_pbDirectory()
{
    QString str = QFileDialog::getExistingDirectory(0,
                                                    "Выбор директории",
                                                    leDirectory->text()
                                                    );
    if (!str.isEmpty()) {
        leDirectory->setText(str);
    }
    const QDir& dir=str;
    QStringList lst;lst<<"*";
    this->lstFilesXML=dir.entryList(lst, QDir::Files);
}
void ReportGenerationInterface::slot_clicked_pbReportGeneration()
{
    QString strReportGenerationResult;

    setting Setting;
    Setting.flagOSWind10Host=this->rbWind10Host->isChecked();
    Setting.flagCVECritical=this->cbCVECritical->isChecked();
    Setting.flagCVEHigh=this->cbCVEHigh->isChecked();
    Setting.flagCVELow=this->cbCVELow->isChecked();
    Setting.flagCVEMiddle=this->cbCVEMiddle->isChecked();

    if(this->rbNotGeneration->isChecked()==true)
        Setting.strReport="NotGeneration";
    else if(this->rbDescriptionAllHost->isChecked()==true)
        Setting.strReport="DescriptionAllHost";
    else if(this->rbSeparateFile->isChecked()==true)
        Setting.strReport="SeparateFile";
    else
        Setting.strReport="AndReport";

    const QDir& dir=this->leDirectory->text();
    QStringList lst;lst<<"*";
    this->lstFilesXML=dir.entryList(lst, QDir::Files);

    QList<ReportGeneration*> lstclReportGeneration;
    QString strErrorFile;

    //    selectOSCVEReport selectButton;

    //    selectButton.strOS=this->rbAllHost->isChecked();

    foreach(QString strFilesXML,lstFilesXML)
    {
        strFilesXML=leDirectory->text()+"/"+strFilesXML;
        ReportGeneration *clReportGeneration= new ReportGeneration;
        MyThread* thread=new MyThread;
        thread->start();
        clReportGeneration->moveToThread(thread);
        strErrorFile=clReportGeneration->fReportGenerationResult(strFilesXML,Setting);
        lstclReportGeneration<<clReportGeneration;
    }
    foreach(ReportGeneration* clReportGeneration,lstclReportGeneration){
        strReportGenerationResult+=clReportGeneration->strReportGenerationResult;
    }

    QString strError;
    if(fun_common::fFileWrite("ReportMaxPatrol.txt", strReportGenerationResult,"WriteOnly")=="error writing file")
    {
        strError="error writing file";
        qDebug()<<strError;
    }
}

ReportGenerationInterface::~ReportGenerationInterface(){
}

// Количество записей в строке
QString ReportGeneration::countRecordInString (QStringList lst,int iCountRecord)
{
    QString strText;
    QString str;
    int i=0; //счетчик подсчет количества элементов в lst
    if(lst.count()!=0){
        foreach (str, lst) {
            i++;
            strText+=str+" ";
            if(i==iCountRecord){
                strText+="\n";
                i=0;
            }
        }
    }
    return strText;
}

//получение описания CVE способ 1 (удаляем дубликаты strCVECountDescription функцией lstCVEDescription.removeDuplicates() )
QStringList ReportGeneration::fCVEDescription(QStringList lstNotTag )
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
QStringList ReportGeneration::fCVEDescription2(QStringList lstNotTag )
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

bool ReportGeneration::fIsCVEDuplicates(QStringList lstCVEDescription,QString strCVE)
{
    bool flagCVEDuplicates=false;
    QList<QString>::iterator it =
            qFind(lstCVEDescription.begin(),lstCVEDescription.end(),strCVE);
    if(it!=lstCVEDescription.end())
        flagCVEDuplicates=true;
    return flagCVEDuplicates;
}

//получение описания CVE (без дубликатов) способ 3 ()
QStringList ReportGeneration::fCVEDescription3(QStringList lstNotTag )
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

//Шаблон(без описания CVE) - IP без описание CVE с выбором: уровня и ОС хоста
//1. Красиво оформить
QStringList ReportGeneration::fTemplateReportCVENotDescriptionWithSwitch(QStringList lstNotTag,setting Setting)
{
    QRegExp regIP("(10\\.50\\.)");
    QRegExp regCVE("(CVE)");
    QString strOS="Windows 10";
    QRegExp regOS("("+strOS+")");
    QRegExp regCVEHigh("(Высокий)");
    QRegExp regCVEMiddle("(Средний)");
    QRegExp regCVECritical("(Критический)");
    QRegExp regCVELow("(Низкий)");

    QStringList lstCVECritical;;
    QStringList lstCVEHigh;;
    QStringList lstCVEMiddle;;
    QStringList lstCVELow;;

    QStringList lstTemplateReport;
    QStringList lstIP;
    QStringList lstCVE;

    QString strCVE;//
    QString strRecordCVE;//строка содержет 3 CVE
    QString strIP;// Содержет IP
    QString strCountCVE;

    bool flagOS10=false;
    int iIp=0;//подсчет IP

    foreach (QString str, lstNotTag) {
        if(regIP.indexIn(str)==0){
            iIp++;
            lstCVECritical.removeDuplicates();
            lstCVEHigh.removeDuplicates();
            lstCVEMiddle.removeDuplicates();
            lstCVELow.removeDuplicates();

            strCountCVE=QString::number(lstCVECritical.count()-2);
            lstCVE<<"\n"<<"Критичный уровень:"<<"Количество уязвимостей: "<<strCountCVE<<"\n"<<countRecordInString(lstCVECritical,3);

            if(Setting.flagCVEHigh==true){
                strCountCVE=QString::number(lstCVEHigh.count()-2);
                lstCVE<<"\n"<<"Высокий уровень:"<<"Количество уязвимостей: "<<strCountCVE<<"\n"<<countRecordInString(lstCVEHigh,3);
            }
            if(Setting.flagCVEMiddle==true){
                strCountCVE=QString::number(lstCVEMiddle.count()-2);
                lstCVE<<"\n"<<"Средний уровень:"<<"Количество уязвимостей: "<<strCountCVE<<"\n"<<countRecordInString(lstCVEMiddle,3);
            }
            if(Setting.flagCVELow==true){
                strCountCVE=QString::number(lstCVELow.count()-2);
                lstCVE<<"\n"<<"Низкий уровень:"<<"Количество уязвимостей: "<<strCountCVE<<"\n"<<countRecordInString(lstCVELow,3);
            }
            //формируем строки по 3 записей CVE
            //strRecordCVE=countRecordInString(lstCVE,3);
            lstIP<<"IP Адрес"<<strIP;//текуйщий Ip
            lstIP<<lstCVE;
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
            strRecordCVE.clear();
        }
    }
    qDebug()<<"Конец отчета0";
    return lstTemplateReport;
}

//Шаблон(без описания) - IP CVE(баг- последний IP не записывает)
QStringList ReportGeneration::fTemplateReportCVENotDescription(QStringList lstNotTag )
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

QString ReportGeneration::fReportGenerationResult(QString strFileXML,setting Setting)
{
    QString strError="false";
    //считали файл xml
    QString strFileReportXML=fun_common::fFileRead(strFileXML);
    if(strFileReportXML=="error file"){
        strError="error file III";
        qDebug()<<strError;
        return strError;
    }
    //декодировали данные
    strFileReportXML=fun_common::fDecodeString(strFileReportXML);
    //удалили тэги
    QStringList lstNotTag=fun_common::fDeleteTag(strFileReportXML);
    QString strNotTag;
    foreach (QString str, lstNotTag) {
        strNotTag+=str+"\n";
    }
    //записали в файл textdok.txt данные без тэгов
    if(fun_common::fFileWrite("textdok.txt",strNotTag,"WriteOnly")=="error file"){
        strError="error file";
        qDebug()<<strError;
        return strError;
    }
    //формируем отчет по шаблону
    QStringList lstTemplateReport;
    //lstTemplateReport<<strFileXML;
    lstTemplateReport<<fTemplateReportCVENotDescriptionWithSwitch(lstNotTag,Setting);
    QString strTemplateReport;
    foreach (QString str, lstTemplateReport) {
        strTemplateReport+=str+"\n";
    }
    this->strReportGenerationResult=strTemplateReport;
    return strError;
}

ReportGeneration::~ReportGeneration(){
}

