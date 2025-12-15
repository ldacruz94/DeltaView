#include "include/ControlBar.h"

#include <QPushButton>
#include <QHBoxLayout>

ControlBar::ControlBar(QWidget* parent) : QWidget(parent) {
	setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

	compareButton = new QPushButton("Compare", this);
	compareButton->setFixedWidth(100);
	compareButton->setCursor(Qt::PointingHandCursor);
	compareButton->setStyleSheet(
		"QPushButton {"
		"	background-color: #3EAf52;"
		"	color: white;"
		"	border-radius: 5px;"
		"	padding: 6px 12px;"
		"}"
		"QPushButton:hover {"
		"	background-color: #6FB97C;"
		"}"
	);

	clearButton = new QPushButton("Clear", this);
	clearButton->setFixedWidth(100);
	clearButton->setCursor(Qt::PointingHandCursor);
	clearButton->setStyleSheet(
		"QPushButton {"
		"	background-color: #6e788a;"
		"	color: white;"
		"	border-radius: 5px;"
		"	padding: 6px 12px;"
		"}"
		"QPushButton:hover {"
		"	background-color: #9ba4b3;"
		"}"
	);

	controlBarLayout = new QHBoxLayout(this);
	controlBarLayout->addStretch();
	controlBarLayout->addWidget(clearButton);
	controlBarLayout->addWidget(compareButton);

	controlBarLayout->setContentsMargins(0, 0, 0, 0);
	controlBarLayout->setSpacing(10);

	connect(compareButton, &QPushButton::clicked, this, &ControlBar::compareRequested);
	connect(clearButton, &QPushButton::clicked, this, &ControlBar::clearRequested);
}