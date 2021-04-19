#ifndef XML_OF_REPORT_H
#define XML_OF_REPORT_H

#include <QWidget>

#include <QApplication>
#include <QtXml>
#include "QtWidgets"
#include <QtPrintSupport>

class ReportGenerationInterface : public QWidget
{
    Q_OBJECT
public:
    explicit ReportGenerationInterface(QWidget *parent = 0);
    ~ReportGenerationInterface();
signals:
public slots:
};

class ReportGeneration : public QObject {
Q_OBJECT
private:
public:
    ReportGeneration(QObject* pobj = 0){};
    ~ReportGeneration();
    bool fIsCVEDuplicates(QStringList lstCVEDescription,QString strCVECount);
    QString countRecordInString (QStringList lst,int iCountRecord);
    QStringList fCVEDescription(QStringList lstNotTag);
    QStringList fCVEDescription2(QStringList lstNotTag);
    QStringList fCVEDescription3(QStringList lstNotTag);
    QStringList fTemplateReportCVENotDescriptionWithSwitch(QStringList lstNotTag);
    QStringList fTemplateReportCVENotDescription(QStringList lstNotTag);
    QString fReportGenerationResult(QString strFileXML);
    QString strReportGenerationResult;
signals:
public slots:
};

class MyThread : public QThread {
Q_OBJECT
public:
    void run()
    {}
signals:
};


#endif // XML_OF_REPORT_H
