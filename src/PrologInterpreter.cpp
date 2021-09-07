#include <stdio.h>
#include "./include/LexicalAnalyzer.hpp"

int main() {
	LexicalAnalyzer a("and not");
	if (a.getSymbol() != Symbol::AND) {
		printf("Error");
		return -1;
	}
	if (a.getSymbol() != Symbol::NOT) {
		printf("Error");
		return -1;
	}
	printf("DONE");
	return 0;
};
