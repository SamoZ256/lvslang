#include <metal_stdlib>
using namespace metal;

fragment void fragmentMain() {
	int a = abs((1 + (0 - 2)));
}

int myAbs(int x) {
	if ((x < 0)) return (0 - x) else return x;
}

