#include "include/MainWindow.h"

#include <QVBoxLayout>
#include <QRegularExpression>

MainWindow::MainWindow(QWidget* parent) : QWidget(parent) {
	setWindowTitle("DeltaView");

	controlBar = new ControlBar(this);
	editorPanel = new EditorPanel(this);
	output = new ResultsOutput(this);
	engine = new DiffEngine();

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

	const QString leftText = editorPanel->getLeftEditText();
	const QString rightText = editorPanel->getRightEditText();

	std::vector<Token> leftTokens = engine->tokenizeWords(leftText);
	std::vector<Token> rightTokens = engine->tokenizeWords(rightText);

	std::vector<std::vector<int>> lcsTable = engine->buildLcsTable(leftTokens, rightTokens);

	std::vector<Op> operations = engine->backtrackOps(leftTokens, rightTokens, lcsTable);

	editorPanel->applyDiffHighlights(leftTokens, rightTokens, operations);

	output->displayResults(editorPanel->getTotalInsertions(), editorPanel->getTotalDeletions());
}

void MainWindow::onClearClicked() const 
{
	output->hideResults();
	output->clearResults();
	editorPanel->clearAll();
}