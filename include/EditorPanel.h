#pragma once

#include <QPlainTextEdit>
#include <QTextEdit>
#include <include/Token.h>
#include <include/Op.h>

class QPlainTextEdit;
class QSplitter;
class QVBoxLayout;
class QPushButton;

class EditorPanel : public QWidget
{
	Q_OBJECT

public:
	explicit EditorPanel(QWidget* parent = nullptr);
	QString getRightEditText() const;
	QString getLeftEditText() const;
	void clearAll() const;
	void applyDiffHighlights(const std::vector<Token>& A, const std::vector<Token>& B, const std::vector<Op>& ops);
	int getTotalDeletions() const { return total_deletions_; }
	int getTotalInsertions() const { return total_insertions_; }
	void setTotalDeletions(int d) { total_deletions_ = d; }
	void setTotalInsertions(int i) { total_insertions_ = i; }
	void set_left_text_edit_text(const QString& text) const { leftTextEdit->setPlainText(text); }
	void set_right_text_edit_text(const QString& text) const { rightTextEdit->setPlainText(text); }

	static QTextEdit::ExtraSelection makeSelection(QPlainTextEdit* edit, int start, int length, const QColor& bgColor);

	signals:
		void open_left_file_button_requested();
		void open_right_file_button_requested();

private:
	int total_deletions_;
	int total_insertions_;

	QSplitter* splitter{};
	QPlainTextEdit* rightTextEdit{};
	QPlainTextEdit* leftTextEdit{};
	QVBoxLayout* layout{};
	QPushButton* left_open_file_button_{};
	QPushButton* right_open_file_button_{};
};
