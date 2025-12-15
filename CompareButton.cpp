#include "CompareButton.h"

CompareButton::CompareButton(QPushButton* parent) : QPushButton(parent)
{
	compareButton = new QPushButton(this);
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
}