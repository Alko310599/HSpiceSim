QT       += core gui
QT += core
QT += core5compat
QT += widgets


DEFINES += PRO_FILE_PWD=$$sprintf("\"\\\"%1\\\"\"", $$_PRO_FILE_PWD_)
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    CodeEditor.cpp \
    Editor.cpp \
    main.cpp \
    MyWindow.cpp \
    mainwindow.cpp

HEADERS += \
    CodeEditor.h \
    Editor.h \
    MyWindow.h \
    mainwindow.h


INCLUDEPATH += HSpiceSim





# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target



RESOURCES += \
    HSpiceSim.qrc


#DISTFILES +=

