#include "include/ResultsOutput.h"

#include <QHBoxLayout>
#include <QPlainTextEdit>
#include <QWidget>

ResultsOutput::ResultsOutput(QWidget* parent) : QWidget(parent)
{
	output = new QPlainTextEdit(this);
	output->setReadOnly(true);
	this->hide();
    this->setMaximumHeight(140);

	layout = new QHBoxLayout(this);
	layout->addWidget(output);
}

void ResultsOutput::hideResults()
{
	this->hide();
}

void ResultsOutput::clearResults()
{
	output->clear();
}

void ResultsOutput::displayResults(int insertions, int deletions)
{
    output->clear();
    this->show();

    QTextCursor cursor(output->document());

    QTextCharFormat resultsHeaderFormat;
    resultsHeaderFormat.setFontWeight(QFont::Bold);
    cursor.setCharFormat(resultsHeaderFormat);
    cursor.insertText(QString("---RESULTS OUTPUT---\n\n"));

    QTextCharFormat insertFormat;
    insertFormat.setForeground(QColor(0, 160, 0));
    insertFormat.setFontWeight(QFont::Bold);

    cursor.setCharFormat(insertFormat);
    cursor.insertText(QString("+ Insertions: %1\n").arg(insertions));

    QTextCharFormat deleteFormat;
    deleteFormat.setForeground(QColor(180, 0, 0));
    deleteFormat.setFontWeight(QFont::Bold);

    cursor.setCharFormat(deleteFormat);
    cursor.insertText(QString("- Deletions: %1\n").arg(deletions));
}
