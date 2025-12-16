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
	void displayResults(int insertions, int deletions);

private:
	QPlainTextEdit* output{};
	QHBoxLayout* layout{};
};

