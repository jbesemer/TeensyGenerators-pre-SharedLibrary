#include "Config.h"

struct NameIdPair {
	const char* Name;
	int Id;

	NameIdPair(int id, const char* name) {
		Id = id;
		Name = name;
	}
};
