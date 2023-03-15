#include "mainwindow.h"
#include <QPainter>

#define x0 2*lyam
#define x1 (this->width()-2*lyam)
#define y0 (3*lyam)
#define y1 (this->height() - (2*lyam))
#define w1 (this->width() - (4*lyam))
#define h1 (this->height() - (5*lyam))


mainwindow::mainwindow(QWidget* _parent)
{
parent = _parent;
}


void mainwindow::paintEvent(QPaintEvent *event) {
QPainter p1(this);
const int lyam = 30;

p1.drawPixmap(0,0,this->width(),this->height(), QPixmap(QString(PRO_FILE_PWD) + "/Resources/fon1.jpg"));

// ***Установка цвета***
QPen Rect(QColor(0, 0, 0) , 5,Qt::SolidLine,Qt::RoundCap);
QPen Green(QColor(0, 255, 110) , 3, Qt::SolidLine);
QPen Red(QColor(255, 0, 10) , 3, Qt::SolidLine);
QPen Blue(QColor(15, 15, 255) , 3, Qt::SolidLine);
QPen Purple(QColor(155, 70, 215) , 3, Qt::SolidLine);
//***********
double x_max = max_x();
double y_min = min_y();
double y_max = max_y();
double ratio_x = double( w1 )/x_max;
double ratio_y = double( h1 )/(5.0-y_min);
double check_move_coord = (5.0-y_min)/5.0;
p1.setPen(Rect);
p1.drawRect(x0,y0,w1,h1);
// Отрисовка осей
if(!MapOfData.empty()){
    p1.drawText(x1,    y1+20,QString::number(x_max));
    p1.drawText(x1/4*3,y1+20,QString::number(x_max/4*3));
    p1.drawText(x1/4*2,y1+20,QString::number(x_max/4*2));
    p1.drawText(x1/4,  y1+20,QString::number(x_max/4));
if(check_move_coord == 1.0){
    p1.drawText(x0-40,y1,QString::number(y_min));
    p1.drawText(x0-40,y1/5*4,QString::number(y_max/4));
    p1.drawText(x0-40,y1/5*3,QString::number(y_max/4*2));
    p1.drawText(x0-40,y1/5*2,QString::number(y_max/4*3));
    p1.drawText(x0-40,y1/5,QString::number(y_max));
}
else{
    double step = (-y_min + y_max)/5;
    p1.drawText(x0-40,(y1 - (y_min*ratio_y)) - int(ceil(h1 - h1/check_move_coord)),QString::number(y_min));
    p1.drawText(x0-40,((y1 - ((y_min+step)*ratio_y)) - int(ceil(h1 - h1/check_move_coord))),QString::number(y_min+step));
    p1.drawText(x0-40,((y1 - ((y_min+step*2)*ratio_y)) - int(ceil(h1 - h1/check_move_coord))),QString::number(y_min+step*2));
    p1.drawText(x0-40,((y1 - ((y_min+step*3)*ratio_y)) - int(ceil(h1 - h1/check_move_coord))),QString::number(y_min+step*3));
    p1.drawText(x0-40,((y1 - ((y_min+step*4)*ratio_y)) - int(ceil(h1 - h1/check_move_coord))),QString::number(y_min+step*4));
    p1.drawText(x0-40,((y1 - (y_max*ratio_y)) - int(ceil(h1 - h1/check_move_coord))),QString::number(y_max));
}


}
// Отрисовка графика
if(!MapOfData.empty())
    for(int i = 0; i < MapOfData["Time"][0].size()-2;i++){
        if(check_move_coord == 1.0){
            p1.setPen(Red);
            p1.drawLine(int(MapOfData["Time"][0][i]*ratio_x)+x0, (y1 - int(MapOfData["V"][0][i]*ratio_y)), int(MapOfData["Time"][0][i+1]*ratio_x)+x0, (y1 - int(MapOfData["V"][0][i+1]*ratio_y)) );
            p1.setPen(Green);
            p1.drawLine(int(MapOfData["Time"][0][i]*ratio_x)+x0, (y1 - int(MapOfData["0"][0][i]*ratio_y)), int(MapOfData["Time"][0][i+1]*ratio_x)+x0, (y1 - int(MapOfData["0"][0][i+1]*ratio_y)) );
            p1.setPen(Blue);
            p1.drawLine(int(MapOfData["Time"][0][i]*ratio_x)+x0, (y1 - int(MapOfData["2"][0][i]*ratio_y)), int(MapOfData["Time"][0][i+1]*ratio_x)+x0, (y1 - int(MapOfData["2"][0][i+1]*ratio_y)) );
            if(MapOfData.find("3") != MapOfData.end()){
                p1.setPen(Purple);
                p1.drawLine(int(MapOfData["Time"][0][i]*ratio_x)+x0, (y1 - int(MapOfData["3"][0][i]*ratio_y)), int(MapOfData["Time"][0][i+1]*ratio_x)+x0, (y1 - int(MapOfData["3"][0][i+1]*ratio_y)) );
            }
            else continue;
            }
         else{
            p1.setPen(Red);
            p1.drawLine(int(MapOfData["Time"][0][i]*ratio_x)+x0,(y1 - int(MapOfData["V"][0][i]*ratio_y)) - int(ceil(h1 - h1/check_move_coord)), int(MapOfData["Time"][0][i+1]*ratio_x)+x0,(y1 - int(MapOfData["V"][0][i+1]*ratio_y))- int(ceil(h1- h1/check_move_coord)) );
            p1.setPen(Green);
            p1.drawLine(int(MapOfData["Time"][0][i]*ratio_x)+x0,(y1 - int(MapOfData["0"][0][i]*ratio_y)) - int(ceil(h1 - h1/check_move_coord)), int(MapOfData["Time"][0][i+1]*ratio_x)+x0,(y1 - int(MapOfData["0"][0][i+1]*ratio_y))- int(ceil(h1-h1/check_move_coord)) );
            p1.setPen(Blue);
            p1.drawLine(int(MapOfData["Time"][0][i]*ratio_x)+x0,(y1 - int(MapOfData["2"][0][i]*ratio_y)) - int(ceil(h1 - h1/check_move_coord)), int(MapOfData["Time"][0][i+1]*ratio_x)+x0,(y1 - int(MapOfData["2"][0][i+1]*ratio_y))- int(ceil( h1 - h1/check_move_coord)) );
            if(MapOfData.find("3") != MapOfData.end()){
                p1.setPen(Purple);
                p1.drawLine(int(MapOfData["Time"][0][i]*ratio_x)+x0,(y1 - int(MapOfData["3"][0][i]*ratio_y)) - int(ceil(h1 - h1/check_move_coord)), int(MapOfData["Time"][0][i+1]*ratio_x)+x0,(y1 - int(MapOfData["3"][0][i+1]*ratio_y))- int(ceil(h1 -  h1/check_move_coord)) );
            }
            else continue;
         }
   }

}

double mainwindow::max_x(){
    if(!MapOfData.empty()){
        double max_x = 0;
        for(int i = 0; i < MapOfData["Time"][0].size()-1;i++){
            if(MapOfData["Time"][0][i] > max_x)
                max_x = MapOfData["Time"][0][i];
        }
        return max_x;
    }
    else return 0;
}

double mainwindow::max_y(){
    if(!MapOfData.empty()){
            double max_x = 0;
            for(int i = 0; i < MapOfData["V"][0].size()-1;i++){
                if(MapOfData["V"][0][i] > max_x)
                    max_x = MapOfData["V"][0][i];
                if(MapOfData["0"][0][i] > max_x)
                    max_x = MapOfData["0"][0][i];
                if(MapOfData["2"][0][i] > max_x)
                    max_x = MapOfData["2"][0][i];
                if(MapOfData.find("3") != MapOfData.end()){
                    if(MapOfData["3"][0][i] > max_x)
                        max_x = MapOfData["3"][0][i];
                }
                else continue;
            }
            return max_x;
        }
        else return 0;
}

double mainwindow::min_y(){
    if(!MapOfData.empty()){
            double min_x = 0;
            for(int i = 0; i < MapOfData["V"][0].size()-1;i++){
                if(MapOfData["V"][0][i] < min_x)
                    min_x = MapOfData["V"][0][i];
                if(MapOfData["0"][0][i] < min_x)
                    min_x = MapOfData["0"][0][i];
                if(MapOfData["2"][0][i] < min_x)
                    min_x = MapOfData["2"][0][i];
                if(MapOfData.find("3") != MapOfData.end()){
                    if(MapOfData["3"][0][i] < min_x)
                        min_x = MapOfData["3"][0][i];
                }
                else continue;
            }
            return min_x;
        }
        else return 0;
}

mainwindow::~mainwindow()
{
    MapOfData.clear();

}

void mainwindow::slotNewFile(QString path){
    MapOfData.clear();
    //QString path;
    //path = QFileDialog::getOpenFileName(this, "Select", "", "file (*.psf)");
    QFile file(path);
    enum state_case{CreateMap,Time,Group,};
    int amount;
    state_case st = CreateMap;
    QStringList list;
    if (!file.open(QIODevice::ReadOnly)) return;
        while (!file.atEnd()) {
            QString line = file.readLine().simplified();
            switch(st){
                case CreateMap:
                if(line.contains("Group",  Qt::CaseInsensitive)){
                    list = line.split(u' ');
                    amount = list[2].toInt();
                    for(int i=0; i < amount; ++i){
                        line = file.readLine().replace(char('"'), char(' '));
                        list = line.simplified().split(u' ');
                        if(i == 0){
                            QVector<double>* vec = new QVector<double>;
                            MapOfData.insert("V", vec);
                        }
                        else{
                            QVector<double>* vec = new QVector<double>;
                            MapOfData.insert(list[0], vec);
                        }
                    }

                QVector<double>* vec = new QVector<double>;
                MapOfData.insert("Time", vec);
                st = Time;
                }
                break;
                list = line.replace(QString(""), QString("")).replace(QString(")"), QString("")).split(u' ');
                case Time:
                if(line.contains("time",  Qt::CaseInsensitive)){
                    list = line.split(u' ');
                    MapOfData["Time"]->push_back(list[1].toDouble());
                    //qDebug() << MapOfData["Time"];
                    st = Group;
                }
                break;
                case Group:
                if(line.contains("group",  Qt::CaseInsensitive)){
                    line = file.readLine().simplified();
                    list = line.split(u' ');
                    MapOfData["V"]->push_back(list[0].toDouble());
                    QMap<QString,QVector<double>*>::const_iterator i = MapOfData.constBegin();
                    while (i != MapOfData.constEnd()) {
                        if(i.key() == "Time")
                            break;
                        line = file.readLine().simplified();
                        list = line.split(u' ');
                        i.value()->push_back(list[0].toDouble());
                        ++i;
                    }
                    st = Time;
                }
                default: break;
            }
        }
       /* Print Map
        qDebug() << MapOfData["V"][0];
        qDebug() << MapOfData["Time"][0];
        qDebug() << MapOfData["0"][0];
        qDebug() << MapOfData["2"][0];
        //qDebug() << MapOfData["3"][0];
*/
}

void mainwindow::slotQuit(){
   close();
}
