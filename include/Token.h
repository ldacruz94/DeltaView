#pragma once

#include <QString>

struct Token 
{
	QString text;
	int start; // this is where I'll keep the starting index of the original QString
	int length;
};