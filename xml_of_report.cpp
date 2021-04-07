#include "xml_of_report.h"
#include "Fun_Common.h"
#include "Fun_Template.h"
#include <QtWidgets>
#include <QtConcurrent/QtConcurrent>

XML_of_Report::XML_of_Report(QWidget *parent) :
    QWidget(parent)
{

    QStringList lstFilesXML;
    lstFilesXML<<"generated17804.xml.kk0<<generated17804.xml.kk1"<<"generated17804.xml.kk2"
                 <<"generated17804.xml.kk3"<<"generated17804.xml.kk4"<<"generated17804.xml.kk5"
                   <<"generated17804.xml.kk6"<<"generated17804.xml.kk7"<<"generated17804.xml.kk8"
                     <<"generated17804.xml.kk9";
    //fun_common::fReportGeneration(lstNotTag);

    //QList<int> ints = QtConcurrent::blockingMapped<QList<int> >(beginIterator, endIterator, fn);

    QStringList lstResult= QtConcurrent::blockingMapped<QStringList>(lstFilesXML,fun_common::fReportGeneration);

  //  QFuture<QString> future =QtConcurrent::blockingMapped(lstFilesXML.begin(),lstFilesXML.end(),fun_common::fReportGeneration);
   //     future.waitForFinished();
      //  QString str1=future.result();
      //  qDebug()<<str1;

}

