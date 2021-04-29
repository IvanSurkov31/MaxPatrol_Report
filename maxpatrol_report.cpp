#include "maxpatrol_report.h"
#include "Fun_Common.h"
#include "Report_Generation.h"
#include <QtWidgets>


MaxPatrol_Report::MaxPatrol_Report(QWidget *parent)
    : QMainWindow(parent)
{
    QAction* About=new QAction("About",0);
    About->setText("&About");

    menuAbout=new QMenu("&Help");
    menuAbout->addAction(About);
    this->menuBar()->addMenu(menuAbout);

    clReportGenerationInterface=new ReportGenerationInterface;
    this->setCentralWidget(clReportGenerationInterface);
    this->setFixedSize(600,500);
    this->setFont(QFont("Times",11));

    connect(About,SIGNAL(triggered(bool)),this,SLOT(slot_clicked_menuAbout(bool)));
}

void MaxPatrol_Report::slot_clicked_menuAbout(bool flag)
{
    qDebug()<<"ee";
    QLabel* lbl_help=new QLabel("    АО ОЭМК им А.А. Угарова» \r\n    Отдел информационной безопасности\r\n    2021.");
    lbl_help->setFixedSize(415,200);
    lbl_help->setFont(QFont("Times",12));
    lbl_help->show();
    lbl_help->setWindowTitle("About");
}

MaxPatrol_Report::~MaxPatrol_Report(){
}
