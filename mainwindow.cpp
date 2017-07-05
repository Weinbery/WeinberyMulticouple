#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPlainTextEdit>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mdiArea(new QMdiArea)
{
    ui->setupUi(this);
    setWindowTitle(tr("Weinbery Multicouple V0.01"));
    setWindowIcon(QIcon(tr(":/images/WeinberyMulticouple.png")));

    createStatusBar();
    progressBar = new QProgressBar;
    progressBar->setMinimum(0);
    progressBar->setMaximum(0);
    progressBar->setMaximumWidth(150);
    progressBar->setMaximumHeight(18);
    progressBar->setValue(24);
    ui->statusBar->addPermanentWidget(progressBar);
    statusInfo = new QLabel(tr("物理内存：743MB，虚拟内存：1406MB"));
    statusInfo->setMinimumSize(250, 20); // 设置标签最小大小
    statusInfo->setFrameShape(QFrame::Panel); // 设置标签形状
    statusInfo->setFrameShadow(QFrame::Sunken); // 设置标签阴影 Raised Plain Sunken
    ui->statusBar->addPermanentWidget(statusInfo);
    createDockWindows();

    mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdiArea->setViewMode(QMdiArea::TabbedView);
    mdiArea->setTabPosition(QTabWidget::North);
    mdiArea->setTabsClosable(true);
    mdiArea->setTabsMovable(true);

    setCentralWidget(mdiArea);

    comboWorkspace = new QComboBox();
    comboWorkspace->setEditable(true);
    comboWorkspace->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    comboWorkspace->setMinimumWidth(360);
    QStringList comboDirList;
    comboDirList << "D:/Qt" << "E:/Project";
    comboWorkspace->addItems(comboDirList);
    //connect(comboWorkspace, SIGNAL(currentTextChanged(QString)), this, SLOT(on_comboWorkspace_currentTextChanged(QString)));
    ui->workspaceToolBar->addWidget(comboWorkspace);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("就绪"));
}

void MainWindow::createDockWindows()
{
    //setDockNestingEnabled(true);
    //splitter = new QSplitter;
    //splitter->setOrientation (Qt::Horizontal); // Vertical
    //
    QDockWidget* modelView = new QDockWidget(tr("模型视图"), this);
    modelView->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetClosable);
    modelView->setAllowedAreas(Qt::AllDockWidgetAreas);
    treeView = new QTreeView(modelView);
    modelView->setWidget(treeView);
    addDockWidget(Qt::LeftDockWidgetArea, modelView);

    QDockWidget *logView = new QDockWidget(tr("消息"), this);
    logView->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetClosable);
    logView->setAllowedAreas(Qt::BottomDockWidgetArea | Qt::RightDockWidgetArea);
    logWidget = new QListWidget(logView);
    logView->setWidget(logWidget);
    addDockWidget(Qt::BottomDockWidgetArea, logView);
    //
    QDockWidget *resultView = new QDockWidget(tr("结果"), this);
    resultView->setAllowedAreas(Qt::BottomDockWidgetArea | Qt::RightDockWidgetArea);
    QListWidget *resultWidget = new QListWidget(resultView);
    resultView->setWidget(resultWidget);
    addDockWidget(Qt::BottomDockWidgetArea, resultView);
    tabifyDockWidget(logView, resultView); // 此句为实现标签页的关键，意为将ur放置到sr处形成标签页
    //
    QDockWidget* fileView = new QDockWidget(tr("文件视图"), this);
    listWidget = new QListWidget(fileView);
    fileView->setWidget(listWidget);
    addDockWidget(Qt::LeftDockWidgetArea, fileView);
    tabifyDockWidget(modelView, fileView);
    //
    QDockWidget* propertyWidget = new QDockWidget(tr("属性视图"), this);
    tableView = new QTableView();
    propertyWidget->setWidget(tableView);
    addDockWidget(Qt::RightDockWidgetArea, propertyWidget);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton closeButton;
    closeButton = QMessageBox::question(this,
                                        tr("退出程序"),
                                        tr("确认退出程序？"),
                                        QMessageBox::Yes | QMessageBox::No);

    if (closeButton == QMessageBox::No)
    {
        event->ignore();  // 忽略退出信号，程序继续运行
    }
    else if (closeButton == QMessageBox::Yes)
    {
        event->accept();  // 接受退出信号，程序退出
    }
}

void MainWindow::on_action_StartOrStop_triggered()
{
    static int nCount = 1;
    //:/images/start.png  :/images/stop.png
    if (nCount % 2 == 0)
    {
        ui->action_StartOrStop->setIcon(QIcon(tr(":/images/start.png")));
        ui->action_StartOrStop->setText(tr("开始(&S)"));
    }
    else
    {
        ui->action_StartOrStop->setIcon(QIcon(tr(":/images/stop.png")));
        ui->action_StartOrStop->setText(tr("停止(&S)"));
    }
    nCount++;
}

void MainWindow::on_action_ExitApplication_triggered()
{
    close();
}

void MainWindow::on_action_NewProject_triggered()
{
    QPlainTextEdit *plaint = new QPlainTextEdit;
    plaint->setBackgroundRole(QPalette::Dark);
    WeinberySubWindow *subWindow = new WeinberySubWindow();
    subWindow->setWidget(plaint);
    subWindow->setSubWindowType(WeinberySubWindow::swGraphic);
    //subWindow->setWindowIcon(QIcon(tr(":/images/PCIeController.png")));
    subWindow->setAttribute(Qt::WA_DeleteOnClose);
    //subWindow->resize(480, 320);
    mdiArea->addSubWindow(subWindow);
    subWindow->show();
}
