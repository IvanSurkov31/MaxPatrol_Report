#include "maxpatrol_report.h"
#include <QApplication>
#include "Report_Generation.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
  //  MaxPatrol_Report w;
    ReportGenerationInterface r;
    r.show();
   // w.show();
    return a.exec();
}
