#pragma once

#include <QWidget>

class QPlainTextEdit;
class QSplitter;
class QVBoxLayout;

class EditorPanel : public QWidget
{
	Q_OBJECT

public:
	explicit EditorPanel(QWidget* parent = nullptr);
	QString getRightEditText() const;
	QString getLeftEditText() const;

private:
	QSplitter* splitter{};
	QPlainTextEdit* rightTextEdit{};
	QPlainTextEdit* leftTextEdit{};
	QVBoxLayout* layout{};
};

