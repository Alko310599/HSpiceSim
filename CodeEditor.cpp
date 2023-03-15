#include "CodeEditor.h"

CodeEditor::CodeEditor(bool isConsole, QWidget* parent) : QPlainTextEdit(parent){
	isConsoleWidget = isConsole;
	setParent(parent);
	setLineWrapMode(QPlainTextEdit::NoWrap);
	setFont(QFont("Courier"));
	if (!isConsole){
		lineNumberArea = new LineNumberArea(this);
		connect(this, SIGNAL(blockCountChanged(qint32)), this, SLOT(slotUpdateLineNumberAreaWidth(qint32)));
		connect(this, SIGNAL(updateRequest(QRect, qint32)), this, SLOT(slotUpdateLineNumberArea(QRect, qint32)));
		connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(slotHighlightCurrentLine()));
		slotUpdateLineNumberAreaWidth(0);
	}
	else{
		setReadOnly(1);
	}

	setShortcutEnabled(1);

	connect(this, SIGNAL(textChanged()), this, SLOT(slotOnTextChanged()));
}
CodeEditor::~CodeEditor(){

}
qint32 CodeEditor::lineNumberAreaWidth(){
	qint32 digits = 1;
	qint32 max = qMax(1, blockCount());
	while (max >= 10){
		max /= 10;
		++digits;
	}
	
    qint32 space = 3 + fontMetrics().maxWidth() * digits;

	return space;
}
void CodeEditor::clearExtraSelections(){
	extraSelections.clear();
}
void CodeEditor::slotUpdateLineNumberAreaWidth(qint32){
	setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}
void CodeEditor::slotUpdateLineNumberArea(const QRect &rect, qint32 dy){
	if (dy){
		lineNumberArea->scroll(0, dy);
	}
	else{
		lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());
	}
	if (rect.contains(viewport()->rect()))
		slotUpdateLineNumberAreaWidth(0);
}
void CodeEditor::resizeEvent(QResizeEvent* ev){
	QPlainTextEdit::resizeEvent(ev);

	if (!isConsoleWidget){
		QRect cr = contentsRect();
		lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
	}
}
void CodeEditor::slotHighlightCurrentLine(){
	QList<QTextEdit::ExtraSelection> tmpExtraSelections = extraSelections;
	if (!isReadOnly()){
		QTextEdit::ExtraSelection selection;
		QColor lineColor = QColor(Qt::yellow).lighter(180);
		selection.format.setBackground(lineColor);
		selection.format.setProperty(QTextFormat::FullWidthSelection, true);
		selection.cursor = textCursor();
		selection.cursor.clearSelection();
		tmpExtraSelections.prepend(selection);
	}
	setExtraSelections(tmpExtraSelections);
}
void CodeEditor::lineNumberAreaPaintEvent(QPaintEvent* ev){
	QPainter painter(lineNumberArea);
	painter.fillRect(ev->rect(), QColor(Qt::gray).lighter(150));

	QTextBlock block = firstVisibleBlock();
	qint32 blockNumber = block.blockNumber();
	qint32 top = (qint32)blockBoundingGeometry(block).translated(contentOffset()).top();
	qint32 bot = top + (qint32)blockBoundingRect(block).height();

	while (block.isValid() && top <= ev->rect().bottom()){
		if (block.isVisible() && bot >= ev->rect().top()){
			QString num = QString::number(blockNumber + 1);
			painter.setPen(QColor(100, 100, 100));
			painter.setFont(font());
			painter.drawText(0, top, lineNumberArea->width(), fontMetrics().height(), Qt::AlignRight, num);
		}
		block = block.next();
		top = bot;
		bot = top + (qint32)blockBoundingRect(block).height();
		++blockNumber;
	}
}
void CodeEditor::slotOnTextChanged(){
	document()->setModified(1);
}

