#define INTEGER1 1
#define INTEGER2 2
#define INVERT(x) (0 - x)
#define ADD(x, y) (x + y)

#define NO_ABS
#undef NO_ABS

fragment void fragmentMain() {
#ifdef NO_ABS
    int a = ADD(INTEGER1, INVERT(INTEGER2));
#else
    int a = abs(ADD(INTEGER1, INVERT(INTEGER2)));
#endif
}

#define NO_ABS

#ifdef NO_ABS
int myAbs(int x) {
    if (x < 0)
        return 0 - x;
    else
        return x;
}
#endif
