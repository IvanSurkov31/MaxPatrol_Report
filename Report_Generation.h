#ifndef XML_OF_REPORT_H
#define XML_OF_REPORT_H

#include <QWidget>

#include <QApplication>
#include <QtXml>
#include "QtWidgets"
#include <QtPrintSupport>
#include <QDir>

class ReportGenerationInterface : public QWidget
{
    Q_OBJECT
private:

QStringList lstFilesXML;

QGroupBox* gbCommon;
QGroupBox* gbOS;
QRadioButton* rbAllHost;
QRadioButton* rbWind10Host;

QGroupBox* gbLevelCVE;
QCheckBox* cbCVECritical;
QCheckBox* cbCVEHigh;
QCheckBox* cbCVEMiddle;
QCheckBox* cbCVELow;

QGroupBox* gbDescriptionCVE;
QRadioButton* rbDescriptionAllHost;
QRadioButton* rbAndReport;
QRadioButton* rbSeparateFile;
QRadioButton* rbNotGeneration;

QPushButton* pbReportGeneration;

QLabel* lblDirectory;
QPushButton* pbDirectory;
QLineEdit* leDirectory;

QHBoxLayout* HBLDirectory;
QVBoxLayout* VBLgbOS;
QVBoxLayout* VBLgbLevelCVE;
QVBoxLayout* VBLgbDescriptionCVE;
QVBoxLayout* VBL1;
QVBoxLayout* VBL2;
QHBoxLayout* HBLgbCommon;
QHBoxLayout* HBLResult;

public:
    explicit ReportGenerationInterface(QWidget *parent = 0);
    ~ReportGenerationInterface();
signals:
public slots:

void slot_clicked_pbReportGeneration();
void slot_clicked_pbDirectory();
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
