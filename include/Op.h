#pragma once

enum class OpType { Keep, Delete, Insert };

struct Op {
	OpType type;
	int leftIndex;
	int rightIndex;
};

