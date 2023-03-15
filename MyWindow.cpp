#include "MyWindow.h"
#include <QPainter>


MyWindow::MyWindow(QWidget* parent) : QMainWindow(parent) {

    paint = new mainwindow(this);
    paint->baseSize();
    init();
    resize(400, 400);
    setWindowTitle("SpiceEditor");

}


void MyWindow::init(){
    initActions();
    initProcess();
    initMainMenu();
    initToolBars();
    initStatusBar();
    initCentralWidget();
    initConsoleDock();


}
void MyWindow::slotProcessStarted()
{
    aRun->setEnabled(0);
    console->appendPlainText("");
    console->appendPlainText("ProcessStarted");
    console->appendPlainText("");
    //console->appendPlainText(process->arguments());

}
void MyWindow::slotProcessFinished(int exitCode, QProcess::ExitStatus exitStatus)
{

    aRun->setEnabled(1);
    console->appendPlainText("");
    console->appendPlainText("ProcessFinsished");
    if(exitCode==0)
        console->appendPlainText("OK");
    else
        console->appendPlainText("error");
    console->appendPlainText("");

}
void MyWindow::slotReadStandartOutput()
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("Windows-1251"));
    QString out = QString::fromLocal8Bit(process->readAllStandardOutput());
    console->appendPlainText(out.trimmed());
    console->verticalScrollBar()->setValue(console->verticalScrollBar()->maximum());
}
void MyWindow::initActions(){
    //Инициализируем действия
    aExit = new QAction(QPixmap(":/Resources/Exit.png"), "Exit", this);
    aOpen = new QAction(QPixmap(":/Resources/Open.png"), "Open", this);
    aSave = new QAction(QPixmap(":/Resources/Save.png"), "Save", this);
    aSaveAs = new QAction(QPixmap(":/Resources/SaveAs.png"), "SaveAs", this);
    aClear= new QAction(QPixmap(":/Resources/Clear.png"), "Clear", this);
    aRun= new QAction(QPixmap(":/Resources/Run.png"), "Run", this);
    aAbout = new QAction(QPixmap(":/Resources/Font.png"), "About", this);
    SetDir = new QAction("SetDirectory", this);
    //Соединяем действия со слотами
    connect(aExit, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(aOpen, SIGNAL(triggered()), SLOT(slotOpen()));
    connect(aSaveAs, SIGNAL(triggered()), SLOT(slotSaveAs()));
    connect(aSave, SIGNAL(triggered()), SLOT(slotSave()));
    connect(aClear, SIGNAL(triggered()), SLOT(slotClear()));
    connect(aAbout, SIGNAL(triggered()), SLOT(slotAbout()));
    connect(SetDir, SIGNAL(triggered()), SLOT(slotSetDirect()));
    QObject::connect(aRun, SIGNAL(triggered()), SLOT(slotRun()));

}

void MyWindow::initMainMenu(){
    //Инициализируем меню
    mFile = new QMenu("File", this);
    mProject = new QMenu("Project", this);
    mHelp = new QMenu("Help", this);
    //Заполняем меню
    mFile->addAction(aOpen);
    mFile->addAction(SetDir);
    mFile->addSeparator();
    mFile->addAction(aSave);
    mFile->addAction(aSaveAs);
    mFile->addAction(aClear);
    mFile->addAction(aExit);
    mProject->addAction(aRun);
    mHelp->addAction(aAbout);
    //Добавляем меню в панель меню
    menuBar()->addMenu(mFile);
    menuBar()->addMenu(mProject);
    menuBar()->addMenu(mHelp);

}

void MyWindow::initToolBars(){
    //Инициализируем тулбары
    tbFile = new QToolBar(this);

    //Заполняем тулбар
    tbFile->addAction(aOpen);
    tbFile->addSeparator();
    tbFile->addAction(aSave);
    tbFile->addAction(aSaveAs);
    tbFile->addAction(aClear);
    tbFile->addAction(aRun);
    tbFile->addAction(aExit);
    tbFile->addAction(aAbout);

    //Добавляем тулбар в панель тулбаров
    addToolBar(Qt::TopToolBarArea, tbFile);

}

void MyWindow::initCentralWidget(){
    //Инициализируем редактор
    editor = new Editor(0,this);

    //Устанавливаем в качестве центрального виджета
    setCentralWidget(editor);

}

void MyWindow::initStatusBar(){
    //Инициализируем статусную строку
    QStatusBar* bar = new QStatusBar(this);

    //Задаем начальное сообщение
    if (filepath.isEmpty())
    {
        bar->showMessage("Ready to work!");
    }
    else
    {
        bar->showMessage(filepath);
    }

    //Добавляем статусную строку
    setStatusBar(bar);

}
void MyWindow::initConsoleDock()
{

    consoleDock = new QDockWidget("Console", this);
    FileDir = new QDockWidget("CurrentDirectory", this);
    console = new Editor(1, consoleDock);
    TreeDir = new QTreeWidget();
    libItem2 = new QTreeWidgetItem(TreeDir);


    QDir dir;

    dir = QDir(PRO_FILE_PWD);


    QStringList CurrentDir = dir.entryList(QStringList()<< "*.sp",QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
    CurrentDir1 = dir.entryInfoList(QStringList()<< "*.sp",QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);

    QStringList headers;
    headers << "List";
    libItem2->setText(0, ("files:" + QString::number(CurrentDir.size())));

    QTreeWidgetItem* libItem1;
    foreach(auto i, CurrentDir){
    libItem1 = new QTreeWidgetItem(libItem2);
    libItem1->setText(0, i);
    }

    libItem2->setExpanded(true);

    TreeDir->setHeaderLabels(headers);
    TreeDir->setRootIsDecorated(0);
    FileDir->setWidget(TreeDir);


    consoleDock->setFeatures(QDockWidget::DockWidgetFeature(0));
    consoleDock->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);

    consoleDock->setWidget(console);



    addDockWidget(Qt::LeftDockWidgetArea,FileDir);
    addDockWidget(Qt::BottomDockWidgetArea,consoleDock);
    connect(TreeDir, &QTreeWidget::currentItemChanged, [=](QTreeWidgetItem* cur){if (!cur) return; int id = TreeDir->topLevelItem(0)->indexOfChild(cur); if (id >= 0) MyWindow::slotOpen(CurrentDir1[id].absoluteFilePath());});

}
void MyWindow::initProcess()
{
    process = new QProcess(this);

    process2 = new QProcess(this);

    QObject::connect(process,SIGNAL(started()),this,SLOT(slotProcessStarted()));
    QObject::connect(process,SIGNAL(finished(int,QProcess::ExitStatus)),this,SLOT(slotProcessFinished(int,QProcess::ExitStatus)));
    QObject::connect(process2, SIGNAL(started()), this, SLOT(slotProcessStarted()));
    QObject::connect(process2, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(slotProcessFinished(int, QProcess::ExitStatus)));

}
void MyWindow::slotOpen(){
    QString filename = QFileDialog::getOpenFileName(
        this,
        "Select",
        "",
        "All (*);; SPICE (*.sp)"
    );
    if (filename.isEmpty())
    {
        return;
    }
    filepath = filename;
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    editor->clear();
    editor->setPlainText(file.readAll());
    file.close();
    QStatusBar* bar = new QStatusBar(this);
    bar->showMessage(filepath);
    setStatusBar(bar);
}

void MyWindow::slotOpen(QString filename){

    filepath = filename;
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    editor->clear();
    editor->setPlainText(file.readAll());
    file.close();
    QStatusBar* bar = new QStatusBar(this);
    bar->showMessage(filepath);
    setStatusBar(bar);
}

void MyWindow::slotSetDirect()
{

    //paint->show();
    dirName = QFileDialog::getExistingDirectory(this,"Select");
    QDir dir;
    if (dirName.isEmpty())
        dir = QDir(PRO_FILE_PWD);
    else
        dir = QDir(dirName);
    QStringList CurrentDir = dir.entryList(QStringList()<< "*.sp",QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
    CurrentDir1 = dir.entryInfoList(QStringList()<< "*.sp",QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);

    QStringList headers;
    headers << "List";
    libItem2->setText(0, ("files:" + QString::number(CurrentDir.size())));

    QTreeWidgetItem* libItem1;
    foreach(auto i, CurrentDir){
    libItem1 = new QTreeWidgetItem(libItem2);
    libItem1->setText(0, i);
    }

    libItem2->setExpanded(true);

    TreeDir->setHeaderLabels(headers);
    TreeDir->setRootIsDecorated(0);
    FileDir->setWidget(TreeDir);
}

void MyWindow::slotSaveAs()
{
    QString filename;
    filename = QFileDialog::getSaveFileName();
    if (filename.isEmpty()) return;
    QFile file;
    file.setFileName(filename);
    if (!file.open(QIODevice::WriteOnly)) return;
    QTextStream out(&file);
    out << editor->toPlainText();
    file.close();
}
void MyWindow::slotSave()
{
    if (filepath.isEmpty())
    {
        QString filename;
        filename = QFileDialog::getSaveFileName();
        if (filename.isEmpty()) return;
        QFile file;
        file.setFileName(filename);
        if (!file.open(QIODevice::WriteOnly)) return;
        QTextStream out(&file);
        out << editor->toPlainText();
        file.close();
        filepath = filename;
    }
    else
    {
        QFile file;
        file.setFileName(filepath);
        if (!file.open(QIODevice::WriteOnly)) return;
        QTextStream out(&file);
        out << editor->toPlainText();
        file.close();

    }
}
void MyWindow::slotClear()
{
    editor->clear();

}
void MyWindow::slotRun()
{
    QStringList args;
    QString args1;
    args << "--input" << filepath;
    QMessageBox msgBox;
    paint->MapOfData.clear();
    process = new QProcess(this);

    QString pr = (QString(PRO_FILE_PWD) + "/Simulator/KRPO_Simulator.exe");
    process->setWorkingDirectory(QString(PRO_FILE_PWD) + "/Simulator");

    process->start(pr, args);

    args1 = filepath + ".psf";
    //process->waitForFinished(); //Ожидание завершения отработки симулятора
    paint->slotNewFile(args1);

    paint->show();
    process->setProcessChannelMode(QProcess::MergedChannels);
    //process2->setProcessChannelMode(QProcess::MergedChannels);

      QObject::connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(slotReadStandartOutput()));




}
void MyWindow::slotAbout()
{
    QMessageBox msgBox;
    msgBox.setText("Programm for modeling HPSICE");

    msgBox.setDefaultButton(QMessageBox::Ok);
    int res = msgBox.exec();
    if (res == QMessageBox::Ok)
        msgBox.close();
}

