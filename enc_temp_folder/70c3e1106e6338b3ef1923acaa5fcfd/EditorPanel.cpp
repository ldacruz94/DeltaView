#include "include/EditorPanel.h"

#include <QSplitter>
#include <QPlainTextEdit>
#include <QVBoxLayout>
#include <QLabel>

EditorPanel::EditorPanel(QWidget* parent) : QWidget(parent) 
{
	splitter = new QSplitter(Qt::Horizontal, this);

	// --- Left side (Original) ---
	auto* leftContainer = new QWidget(splitter);
	auto* leftLayout = new QVBoxLayout(leftContainer);
	leftLayout->setContentsMargins(4, 4, 4, 4);
	leftLayout->setSpacing(4);

	auto* leftLabel = new QLabel("Original", leftContainer);
	leftLabel->setStyleSheet("font-weight: bold;");

	leftTextEdit = new QPlainTextEdit(leftContainer);

	leftLayout->addWidget(leftLabel);
	leftLayout->addWidget(leftTextEdit);

	// --- Right side (Modified) ---
	auto* rightContainer = new QWidget(splitter);
	auto* rightLayout = new QVBoxLayout(rightContainer);
	rightLayout->setContentsMargins(4, 4, 4, 4);
	rightLayout->setSpacing(4);

	auto* rightLabel = new QLabel("Modified", rightContainer);
	rightLabel->setStyleSheet("font-weight: bold;");

	rightTextEdit = new QPlainTextEdit(rightContainer);

	rightLayout->addWidget(rightLabel);
	rightLayout->addWidget(rightTextEdit);

	// Add containers to splitter
	splitter->addWidget(leftContainer);
	splitter->addWidget(rightContainer);
	splitter->setStretchFactor(0, 1);
	splitter->setStretchFactor(1, 1);

	// Main layout
	layout = new QVBoxLayout(this);
	layout->setContentsMargins(0, 0, 0, 0);
	layout->setSpacing(0);
	layout->addWidget(splitter);
}

QString EditorPanel::getRightEditText() const 
{
	return rightTextEdit->toPlainText();
}

QString EditorPanel::getLeftEditText() const 
{
	return leftTextEdit->toPlainText();
}

void EditorPanel::clearAll() 
{
	rightTextEdit->clear();
	leftTextEdit->clear();
	rightTextEdit->setExtraSelections({});
	leftTextEdit->setExtraSelections({});
}

QTextEdit::ExtraSelection EditorPanel::makeSelection(QPlainTextEdit* edit, int start, int length, const QColor& bgColor) 
{
	QTextCursor cursor(edit->document());
	cursor.setPosition(start);
	cursor.setPosition(start + length, QTextCursor::KeepAnchor);

	QTextEdit::ExtraSelection selection;
	selection.cursor = cursor;

	QTextCharFormat format;
	format.setBackground(bgColor);
	format.setForeground(Qt::black);
	selection.format = format;

	return selection;
}

void EditorPanel::applyDiffHighlights(const std::vector<Token>& A, const std::vector<Token>& B, const std::vector<Op>& ops)
{
	QList<QTextEdit::ExtraSelection> leftSel;
	QList<QTextEdit::ExtraSelection> rightSel;

	const QColor deleteRed(255, 180, 180);
	const QColor insertGreen(180, 255, 180);

	for (const auto& op : ops) {
		if (op.type == OpType::Delete && op.leftIndex >= 0) {
			const auto& t = A[op.leftIndex];
			leftSel.push_back(makeSelection(leftTextEdit, t.start, t.length, deleteRed));
		}
		else if (op.type == OpType::Insert && op.rightIndex >= 0) {
			const auto& t = B[op.rightIndex];
			rightSel.push_back(makeSelection(rightTextEdit, t.start, t.length, insertGreen));
		}
	}

	setTotalDeletions(leftSel.size());
	setTotalInsertions(rightSel.size());

	leftTextEdit->setExtraSelections(leftSel);
	rightTextEdit->setExtraSelections(rightSel);
}
