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
