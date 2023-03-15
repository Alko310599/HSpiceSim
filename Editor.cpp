#include "Editor.h"

Editor::Editor(bool isConsole, QWidget* parent) : CodeEditor(isConsole, parent){
    highlighter = new Highlighter(this->document());
}

Highlighter::Highlighter(QTextDocument* parent) : QSyntaxHighlighter(parent){
    QRegularExpression expr("\\b(warning)\\b", QRegularExpression::CaseInsensitiveOption);
    QTextCharFormat format;            //Создаем форматирование текста
    format.setForeground(              //Устанавливаем цвет текста
        QColor(Qt::yellow).lighter(130)
    );
    addHighlightningRule(expr, format);
    QRegularExpression expr1("\\b(R|L|C|X|D|V|I)\\w*\\b", QRegularExpression::CaseInsensitiveOption);// \\b(double|bool)\\b     ------------!!!!!(R|L|C|X|D|V|I)\w*
    QTextCharFormat format1;            //Создаем форматирование текста
    format1.setForeground(              //Устанавливаем цвет текста
        QColor(Qt::blue).lighter(130)
    );
    addHighlightningRule(expr1, format1);
    QRegularExpression expr2("\\B(\\.\\w*)");// \\b(double|bool)\\b
    QTextCharFormat format2;            //Создаем форматирование текста
    format2.setForeground(              //Устанавливаем цвет текста
        QColor(Qt::darkMagenta).lighter(130)
    );
    addHighlightningRule(expr2, format2);

    QRegularExpression commentExpr("\\*.*");
    QTextCharFormat commentFormat;
    commentFormat.setForeground(QColor(Qt::green));
    addHighlightningRule(commentExpr, commentFormat);
    QRegularExpression commentExpr1("\\b(OK)\\b", QRegularExpression::CaseInsensitiveOption);
    addHighlightningRule(commentExpr1, commentFormat);
    QRegularExpression expr3("\\b(error)\\b", QRegularExpression::CaseInsensitiveOption);
    QTextCharFormat format3;            //Создаем форматирование текста
    format3.setForeground(              //Устанавливаем цвет текста
        QColor(Qt::red).lighter(130)
    );
    addHighlightningRule(expr3, format3);
}
void Highlighter::addHighlightningRule(QRegularExpression pattern, QTextCharFormat format){
    rules.push_back(pattern);
    formats.push_back(format);
}
void Highlighter::highlightBlock(const QString &text){
    for (int i = 0; i < rules.size(); i++)
    {
        QRegularExpression expr = rules.at(i);
        QTextCharFormat format = formats.at(i);
        {
            QRegularExpressionMatch match = expr.match(text); //Ищем вхождение
            while (match.hasMatch()) {                          //Пока вхождение есть
                setFormat(match.capturedStart(),              //Устанавливаем формат для
                    match.capturedLength(), format);    //    найденного вхождения
                match = expr.match(text, match.capturedEnd());//Ищем следующее вхождение
            }
        }
    }
}
