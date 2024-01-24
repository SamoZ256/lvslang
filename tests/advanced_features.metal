bool forwardDeclaredFunction(int a, int3 b);

struct FragmentOut {
    float4 outColor [[color(0)]];
};

fragment struct FragmentOut testAdvancedFeatures() {
    bool a = forwardDeclaredFunction(1, int3(1, 2, 3));

    struct FragmentOut fragmentOut;

    return fragmentOut;
}

bool forwardDeclaredFunction(int a, int3 b) {
    return (a == b.x || a == b.y || a == b.z);
}
