#ifndef CODE_EDITOR_H
#define CODE_EDITOR_H

#include <QtGui>
#include <QtWidgets>
#include <QtCore>

class LineNumberArea;

class CodeEditor : public QPlainTextEdit
{
	Q_OBJECT

    //Объявление переменных
private:
	LineNumberArea* lineNumberArea;
	QList<QTextEdit::ExtraSelection> extraSelections;

public:
	bool isConsoleWidget;

    //Объявление функций
public:
	CodeEditor(bool isConsole = 0, QWidget* parent = 0);
	~CodeEditor();

public:
	void			lineNumberAreaPaintEvent(QPaintEvent* ev);
	qint32			lineNumberAreaWidth();
	void			clearExtraSelections();

private:
	void resizeEvent(QResizeEvent* ev);

    //Объявление слотов
private slots:
	void			slotUpdateLineNumberAreaWidth(qint32 newBlockCount);
	void			slotHighlightCurrentLine();
	void			slotUpdateLineNumberArea(const QRect &, qint32);
	void			slotOnTextChanged();
};

class LineNumberArea : public QWidget
{
	Q_OBJECT

private:
	CodeEditor* codeEditor;

public:
	LineNumberArea(CodeEditor* editor) : QWidget(editor){
		codeEditor = editor;
	}
	QSize sizeHint() const Q_DECL_OVERRIDE{
		return QSize(codeEditor->lineNumberAreaWidth(), 0);
	}

protected:
	void paintEvent(QPaintEvent* ev) Q_DECL_OVERRIDE {
		codeEditor->lineNumberAreaPaintEvent(ev);
	}

};

#endif //CODE_EDITOR_H
