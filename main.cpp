#include "mainwindow.h"
#include "weinberytoolbox.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("Weinbery");
    QCoreApplication::setApplicationName("WeinberyMulticouple");
    QString strKey = QCoreApplication::organizationName() + QCoreApplication::applicationName();
    QSharedMemory sharedMemory(strKey);
    if (!sharedMemory.create(512, QSharedMemory::ReadWrite))
    {
        QMessageBox::information(NULL, QStringLiteral("提示"), QStringLiteral("程序已运行！"));
        exit(0);
    }
    ///

    WeinberyToolBox::setStyle(":/images/black.qss");

    QApplication::setStyle(QStyleFactory::create("fusion"));

    MainWindow w;
    w.show();

    return a.exec();
}
