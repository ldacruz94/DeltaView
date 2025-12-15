#include "include/MainWindow.h"
#include "include/ControlBar.h"
#include "include/EditorPanel.h"
#include "include/ResultsOutput.h"

#include <QVBoxLayout>
#include <QRegularExpression>

MainWindow::MainWindow(QWidget* parent) : QWidget(parent) {
	setWindowTitle("DeltaView");

	controlBar = new ControlBar(this);
	editorPanel = new EditorPanel(this);
	output = new ResultsOutput(this);

	auto* layout = new QVBoxLayout(this);
	layout->addWidget(controlBar);
	layout->addWidget(editorPanel);
	layout->addWidget(output);

	connect(controlBar, &ControlBar::compareRequested, this, &MainWindow::onCompareClicked);
	connect(controlBar, &ControlBar::clearRequested, this, &MainWindow::onClearClicked);
}

void MainWindow::onCompareClicked() const 
{
	output->hideResults();
	output->clearResults();

	const QStringList leftLines = editorPanel->getLeftEditText().split("\n");
	const QStringList rightLines = editorPanel->getRightEditText().split("\n");

	std::vector<QString> diffWords;
	bool bothSidesEqual = true;

	const int lineCount = std::min(leftLines.size(), rightLines.size());

	for (int i = 0; i < lineCount; ++i) 
	{
		if (leftLines[i] != rightLines[i])
		{
			QStringList leftSplitterWords = leftLines[i].split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
			QStringList rightSplitterWords = rightLines[i].split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);

			for (const auto& rightWord : rightSplitterWords) 
			{
				bool found = false;
				for (const auto& leftWord : leftSplitterWords)
				{
					if (leftWord == rightWord) 
					{
						found = true;
						break;
					}
				}
				if (!found)
				{
					bothSidesEqual = false;
					diffWords.push_back(rightWord);
				}
			}
		}
	}

	for (const auto& word : diffWords) 
	{
		qDebug() << word;
	}

	if (bothSidesEqual)
	{
		output->setText("Both sides are EQUAL");
	}
	else
	{
		QString text = "Both sides are NOT EQUAL\n\nDifferent words:\n";
		for (const auto& w : diffWords)
		{
			text += w + "\n";
		}
		output->setText(text);
	}

	output->displayResults();
}

void MainWindow::onClearClicked() const 
{
	output->hideResults();
	output->clearResults();
	editorPanel->clearAll();
}