#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QMessageBox>
#include <QLabel>
#include <QDockWidget>
#include <QListWidget>
#include <QTreeView>
#include <QTableView>
#include <QComboBox>
#include <QMdiArea>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QDirModel>
#include <QIcon>
#include <QDir>
#include <QFileInfo>
#include <QDesktopServices>
#include <QDateTime>
#include <QProcess>
#include <QSplitter>
#include <QProgressBar>
#include "weinberysubwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_action_StartOrStop_triggered();

    void on_action_ExitApplication_triggered();

    void on_action_NewProject_triggered();

private:
    void createStatusBar();
    void createDockWindows();

private:
    QProgressBar *progressBar;
    QLabel *statusInfo;
    Ui::MainWindow *ui;
    QMdiArea *mdiArea;
    QComboBox *comboWorkspace;
    QListWidget *listWidget;
    QListWidget *logWidget;
    QTableView* tableView;
    QStringList comboDirList;
    QString strCurrentWorkspace;
    QDirModel *dirModel;
    QSplitter *splitter;
    QTreeView *treeView;
};

#endif // MAINWINDOW_H
