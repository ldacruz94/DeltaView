#include "include/ResultsOutput.h"

#include <QHBoxLayout>
#include <QPlainTextEdit>
#include <QWidget>

ResultsOutput::ResultsOutput(QWidget* parent) : QWidget(parent)
{
	output = new QPlainTextEdit(parent);
	output->setReadOnly(true);
	this->hide();

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

void ResultsOutput::displayResults()
{
	this->show();
}

void ResultsOutput::setText(const QString& text)
{
	output->setPlainText(text);
}