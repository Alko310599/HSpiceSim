
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#pragma once
#include <QPainter>
#include <QWidget>
#include <QFrame>
#include <QMainWindow>
#include <QMap>
#include <QTextStream>
#include <QFileDialog>
#include <QDebug>
#include <QRegularExpression>
#include <QGridLayout>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <math.h>

class mainwindow: public QWidget
{

public:
    QWidget* parent;
    mainwindow(QWidget* parent = 0);
    ~mainwindow();


    void createScene();
    double move_coord(double check);
    double max_x();
    double min_y();
    double max_y();

    void paintEvent(QPaintEvent *event);

    QMap<QString,QVector<double>*> MapOfData;
private:

    QMenu* fileMenu;
    QAction* loadFile;
    QAction* quitAction;
    QPainter* painter;
    QRect rect;
public slots:
void slotNewFile(QString path);
void slotQuit();
};

#endif // MAINWINDOW_H
