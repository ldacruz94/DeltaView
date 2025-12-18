#include "include/MainWindow.h"

#include <QVBoxLayout>
#include <QRegularExpression>
#include <QFileDialog>
#include <QMessageBox>


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
	connect(editorPanel, &EditorPanel::open_left_file_button_requested, this, &MainWindow::on_open_left_file);
	connect(editorPanel, &EditorPanel::open_right_file_button_requested, this, &MainWindow::on_open_right_file);
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

void MainWindow::on_open_left_file()
{
	const QString file_path = QFileDialog::getOpenFileName(
		this,
		"Open File",
		QString(),
		"Text Files (*.txt *.md *.log *.json *.xml *.yaml *.yml)"
	);

	if (file_path.isEmpty())
		return;

	QFile file(file_path);

	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		QMessageBox::warning(this, "Error",
			"Could not open file.");
		return;
	}

	QTextStream in(&file);
	in.setEncoding(QStringConverter::Utf8);

	editorPanel->set_left_text_edit_text(in.readAll());
}

void MainWindow::on_open_right_file()
{
	const QString file_path = QFileDialog::getOpenFileName(
		this,
		"Open File",
		QString(),
		"Text Files (*.txt *.md *.log *.json *.xml *.yaml *.yml)"
	);

	if (file_path.isEmpty())
		return;

	QFile file(file_path);

	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		QMessageBox::warning(this, "Error",
			"Could not open file.");
		return;
	}

	QTextStream in(&file);
	in.setEncoding(QStringConverter::Utf8);

	editorPanel->set_right_text_edit_text(in.readAll());
}