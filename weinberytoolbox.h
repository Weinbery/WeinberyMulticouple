#ifndef WEINBERYTOOLBOX_H
#define WEINBERYTOOLBOX_H

#include <QFile>
#include <QTranslator>
#include <QMessageBox>
#include <QApplication>
#include <QSharedMemory>
#include <QStyleFactory>

/// WeinberyToolBox
class WeinberyToolBox
{
public:
    static void setStyle(const QString &strFile)
    {
        QFile stylefile(strFile);
        stylefile.open(QFile::ReadOnly);
        qApp->setStyleSheet(stylefile.readAll());
        stylefile.close();
    }

    static void translateChinese()
    {
        QTranslator *translator = new QTranslator(qApp);
        translator->load(":/qss/qt_zh_CN.qm");
        qApp->installTranslator(translator);
    }
};

#endif // WEINBERYTOOLBOX_H
