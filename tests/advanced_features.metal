bool forwardDeclaredFunction(int a, int3 b);

fragment void testAdvancedFeatures() {
    bool a = forwardDeclaredFunction(1, int3(1, 2, 3));
}

bool forwardDeclaredFunction(int a, int3 b) {
    return (a == b.x || a == b.y || a == b.z);
}
