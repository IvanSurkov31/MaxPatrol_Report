#include "maxpatrol_report.h"
#include "Fun_Common.h"
#include "Report_Generation.h"
#include <QtWidgets>


MaxPatrol_Report::MaxPatrol_Report(QWidget *parent)
    : QMainWindow(parent)
{
    QString strReportGenerationResult;
    QStringList lstFilesXML;
    lstFilesXML<<"generated17804.xml.kk0"<<"generated17804.xml.kk1"<<"generated17804.xml.kk2"
              <<"generated17804.xml.kk3" <<"generated17804.xml.kk4" <<"generated17804.xml.kk5"
                 <<"generated17804.xml.kk6" <<"generated17804.xml.kk7" <<"generated17804.xml.kk8";

    QList<ReportGeneration*> lstclReportGeneration;
    QString strErrorFile;

    foreach(QString strFilesXML,lstFilesXML)
    {
    ReportGeneration *clReportGeneration= new ReportGeneration;
    MyThread* thread=new MyThread;

    thread->start();

    clReportGeneration->moveToThread(thread);

    strErrorFile=clReportGeneration->fReportGenerationResult(strFilesXML);
    lstclReportGeneration<<clReportGeneration;

    }

foreach(ReportGeneration* clReportGeneration,lstclReportGeneration){
    strReportGenerationResult+=clReportGeneration->strReportGenerationResult;

}
QString strError;
    if(fun_common::fFileWrite("ReportMaxPatrol.txt", strReportGenerationResult,"Append")=="error writing file")
        strError=="error writing file";
}

MaxPatrol_Report::~MaxPatrol_Report(){
}
