bool forwardDeclaredFunction(int a, int3 b);

void testAdvancedFeatures();

void_Output _testAdvancedFeatures() {
	// Entry point call
	testAdvancedFeatures();
}

void testAdvancedFeatures() {
	bool a = forwardDeclaredFunction(1, int3(1, 2, 3));
}

bool forwardDeclaredFunction(int a, int3 b) {
	return (((a == b.x) || (a == b.y)) || (a == b.z));
}

