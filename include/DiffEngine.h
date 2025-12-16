#pragma once

#include <vector>
#include <string>
#include <include/Token.h>
#include <include/Op.h>

class QString;

class DiffEngine
{

public:
	explicit DiffEngine();
	std::vector<Token> tokenizeWords(const QString& s) const;
	std::vector<std::vector<int>> buildLcsTable(
		const std::vector<Token>& A,
		const std::vector<Token>& B) const;
	std::vector<Op> backtrackOps(
		const std::vector<Token>& A,
		const std::vector<Token>& B,
		const std::vector<std::vector<int>>& table
	);
};

