#pragma once

#include <QWidget>
#include <QTextEdit>
#include <include/Token.h>
#include <include/Op.h>

class QPlainTextEdit;
class QSplitter;
class QVBoxLayout;

class EditorPanel : public QWidget
{
	Q_OBJECT

public:
	int totalDeletions;
	int totalInsertions;

	explicit EditorPanel(QWidget* parent = nullptr);
	QString getRightEditText() const;
	QString getLeftEditText() const;
	void clearAll();
	void applyDiffHighlights(const std::vector<Token>& A, const std::vector<Token>& B, const std::vector<Op>& ops);
	int getTotalDeletions() const { return totalDeletions; }
	int getTotalInsertions() const { return totalInsertions; }
	void setTotalDeletions(int d) { totalDeletions = d; }
	void setTotalInsertions(int i) { totalInsertions = i; }

	static QTextEdit::ExtraSelection makeSelection(QPlainTextEdit* edit, int start, int length, const QColor& bgColor);

private:
	QSplitter* splitter{};
	QPlainTextEdit* rightTextEdit{};
	QPlainTextEdit* leftTextEdit{};
	QVBoxLayout* layout{};
};

