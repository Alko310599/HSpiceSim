#ifndef MY_WINDOW_H
#define MY_WINDOW_H
#include "CodeEditor.h"
#include "Editor.h"
//Заголовочные файлы
#include <QDockWidget>
#include <QtWidgets>
#include <QtCore>
#include <QtGui>
#include <iostream>
#include <QTextCodec>
#include <QTreeWidget>
#include <QWidget>
#include <mainwindow.h>
#include <QProcess>
//#include "paint.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

//Класс для описания главного окна
class MyWindow : public QMainWindow {
    Q_OBJECT

private:
    mainwindow* paint;
    Ui::MainWindow *ui;
    //Меню и действия
    QMenu*		mFile;				//Меню "File"
    QMenu* mProject;
    QMenu* mHelp;
    QAction* aAbout;
    QAction* aOpen;			//Действие открытия файла "Open"
    QAction* SetDir;
    QAction* aSave;
    QAction* aSaveAs;
    QAction* aExit;			//Действие выхода из программы "Exit"
    QAction* aClear;
    QAction* aRun;
    //Панели инструментов (тулбары)
    QToolBar*	tbFile;				//Тулбар "File"
    QProcess *process;
    QProcess *process2;
    //Редактор
    Editor*	editor;				//Редактор
    QDockWidget* consoleDock;
    QDockWidget* FileDir;
    Editor* console;
    QTreeWidget* ed;
    QTreeWidget *TreeDir;
    QString filepath;
    QString dirName;

    QTreeWidgetItem* libItem2;
    QFileInfoList CurrentDir1;

public:

    //Конструкторы
    MyWindow(QWidget* parent = NULL);

    //Методы инициализации
    void init();					//Общий метод инициализации
    void initActions();				//Инициализация действий
    void initMainMenu();			//Инициализация меню
    void initToolBars();			//Инициализация тулбаров
    void initStatusBar();			//Инициализация статусной строки
    void initCentralWidget();		//Инициализация центрального виджета
    void initConsoleDock();
    void initProcess();
//Слоты
public slots:
    void slotOpen();				//Слот открытия файла
    void slotOpen(QString filename);
    void slotSetDirect();
    void slotSaveAs();
    void slotClear();
    void slotRun();
    void slotProcessStarted();
    void slotProcessFinished(int exitCode,QProcess::ExitStatus exitStatus);
    void slotReadStandartOutput();
    void slotSave();
    void slotAbout();
};

#endif // MY_WINDOW_H
