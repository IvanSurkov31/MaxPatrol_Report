#ifndef MAXPATROL_REPORT_H
#define MAXPATROL_REPORT_H
#include "Report_Generation.h"
#include <QMainWindow>

//#include "Report_Generation.h"

class MaxPatrol_Report : public QMainWindow
{
    Q_OBJECT

public:
    MaxPatrol_Report(QWidget *parent = 0);
    ~MaxPatrol_Report();

    QMenu*  menuAbout;
    ReportGenerationInterface* clReportGenerationInterface;
public slots:
    void slot_clicked_menuAbout(bool flag);
};

#endif // MAXPATROL_REPORT_H
