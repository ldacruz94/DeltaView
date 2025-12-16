#include "include/DiffEngine.h"
#include <include/Token.h>
#include <include/Op.h>

#include <QRegularExpression>
#include <vector>

DiffEngine::DiffEngine() {}

std::vector<Token> DiffEngine::tokenizeWords(const QString& s) const {
	std::vector<Token> out;
	QRegularExpression re(R"(\S+)");
	auto it = re.globalMatch(s);
	while (it.hasNext())
	{
		auto m = it.next();
		out.push_back(Token{ m.captured(0), 
			static_cast<int>(m.capturedStart(0)), 
			static_cast<int>(m.capturedLength(0)) 
		});
	}

	return out;
}

static bool tokenEqual(const Token& a, const Token& b) {
	return a.text == b.text;
}

std::vector<std::vector<int>> DiffEngine::buildLcsTable(const std::vector<Token>& A, const std::vector<Token>& B) const {
	const int n = static_cast<int>(A.size());
	const int m = static_cast<int>(B.size());

	std::vector<std::vector<int>> table(n + 1, std::vector<int>(m + 1, 0));

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (tokenEqual(A[i - 1], B[j - 1])) {
				table[i][j] = table[i - 1][j - 1] + 1;
			}
			else {
				table[i][j] = std::max(table[i - 1][j], table[i][j - 1]);
			}
		}
	}

	return table;
}

std::vector<Op> DiffEngine::backtrackOps(
	const std::vector<Token>& A, 
	const std::vector<Token>& B,
	const std::vector<std::vector<int>>& table) {

	int i = static_cast<int>(A.size());
	int j = static_cast<int>(B.size());

	std::vector<Op> ops;
	ops.reserve(i + j); // allocating memory here to optimze the vector's capacity a bit

	while (i > 0 || j > 0) {
		if (i > 0 && j > 0 && A[i - 1].text == B[j - 1].text) {
			ops.push_back(Op{ OpType::Keep, i - 1, j - 1 });
			--i; --j;
		}
		else if (i > 0 && (j == 0 || table[i - 1][j] >= table[i][j - 1])) {
			ops.push_back(Op{ OpType::Delete, i - 1,  -1 });
			--i;
		}
		else {
			ops.push_back(Op{ OpType::Insert, -1, j - 1 });
			--j;
		}
	}

	std::reverse(ops.begin(), ops.end());
	return ops;
}

