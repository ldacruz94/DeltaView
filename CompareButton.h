#pragma once

#include <QPushButton>
#include <string>

class CompareButton : QPushButton
{

public:
	explicit CompareButton(QPushButton* parent = nullptr);

private:
	std::string name = "Compare";
};

