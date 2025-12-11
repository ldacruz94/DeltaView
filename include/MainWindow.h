#pragma once

#include "ControlBar.h"
#include "EditorPanel.h"
#include "ResultsOutput.h"

#include <QWidget>


class MainWindow final : public QWidget
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget* parent = nullptr);

private slots:
	void onCompareClicked() const;

private:
	EditorPanel* editorPanel;
	ControlBar* controlBar{};
	ResultsOutput* output{};
};