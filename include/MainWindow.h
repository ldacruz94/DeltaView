#pragma once

#include "ControlBar.h"
#include "EditorPanel.h"
#include "ResultsOutput.h"
#include "DiffEngine.h"

#include <QWidget>


class MainWindow final : public QWidget
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget* parent = nullptr);

private slots:
	void onCompareClicked() const;
	void onClearClicked() const;
	void on_open_left_file();
	void on_open_right_file();

private:
	EditorPanel* editorPanel;
	ControlBar* controlBar{};
	ResultsOutput* output{};
	DiffEngine* engine{};
};