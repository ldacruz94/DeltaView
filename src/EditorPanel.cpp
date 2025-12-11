#include "include/EditorPanel.h"

#include <QSplitter>
#include <QPlainTextEdit>
#include <QVBoxLayout>

EditorPanel::EditorPanel(QWidget* parent) : QWidget(parent) 
{
	splitter = new QSplitter(this);

	leftTextEdit = new QPlainTextEdit(splitter);
	rightTextEdit = new QPlainTextEdit(splitter);

	splitter->addWidget(leftTextEdit);
	splitter->addWidget(rightTextEdit);

	layout = new QVBoxLayout(this);
	layout->setContentsMargins(0, 0, 0, 0);
	layout->setSpacing(0);
	layout->addWidget(splitter);
}

QString EditorPanel::getRightEditText() const {
	return rightTextEdit->toPlainText();
}

QString EditorPanel::getLeftEditText() const {
	return leftTextEdit->toPlainText();
}