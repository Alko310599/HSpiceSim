#ifndef EDITOR_H
#define EDITOR_H

#include "CodeEditor.h"



class Highlighter;



//Класс пользовательского редактора
class Editor : public CodeEditor
{
    Q_OBJECT

    Highlighter* highlighter = NULL; //Объект класса подсветки

public:
    Editor(bool isConsole = 0, QWidget* parent = NULL); //Конструктор
    Highlighter* getHightlighter() { return highlighter; }

};



//Класс подсветки синтаксиса
class Highlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    Highlighter(QTextDocument* parent = 0); //Конструктор
    QList<QRegularExpression> rules;
    QList<QTextCharFormat> formats;

    void addHighlightningRule(QRegularExpression pattern, QTextCharFormat format); //Метод добавления правил подсветки
    void highlightBlock(const QString &text); //Метод для реализации подсветки текстового блока

};

#endif //EDITOR_H
