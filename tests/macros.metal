#define INTEGER1 1
#define INTEGER2 2
#define INVERT(x) (0 - x)
#define ADD(x, y) (x + y)

fragment void fragmentMain() {
    int a = abs(ADD(INTEGER1, INVERT(INTEGER2)));
}
