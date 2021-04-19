#ifndef FUN_COMMON_H
#define FUN_COMMON_H

#include <QtWidgets>

namespace fun_common
{
QString checkExistenceString(QStringList lstCheck,int numberString);

QStringList fDeleteTag(QString strfile);

QString fFileRead(QString strNameFile);

QString fFileWrite(QString strNameFile,QString strData,QString strIsWriteOnly);

QString fDecodeString(QString strCode );
}

#endif // FUN_COMMON_H
