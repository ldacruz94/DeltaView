#pragma once

#include <QWidget>

class QPlainTextEdit;
class QHBoxLayout;

class ResultsOutput : public QWidget 
{
	Q_OBJECT

public:
	explicit ResultsOutput(QWidget* parent = nullptr);
	void clearResults();
	void hideResults();
	void displayResults();
	void setText(const QString& text);

private:
	QPlainTextEdit* output{};
	QHBoxLayout* layout{};
};

