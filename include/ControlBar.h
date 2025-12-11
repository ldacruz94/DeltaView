#pragma once

#include <QWidget>

class QHBoxLayout;
class QPushButton;

class ControlBar : public QWidget
{
	Q_OBJECT

public:
	explicit ControlBar(QWidget* parent = nullptr);

	signals:
		void compareRequested();

private:
	QHBoxLayout* controlBarLayout{};
	QPushButton* compareButton{};
};
