#include <climits>
#include <math.h>


unsigned long long count_factorial(unsigned char x) {
    if (x == 0 || x == 1) {
        return 1;
    } else if (x == 2) {
        return 2;
    }
    return x * count_factorial(x-1);
}

unsigned char get_accuracy_in_factorial(unsigned char x) {
    double accuracy = pow(10, -x);
    for (unsigned char x = 1; x <= CHAR_MAX; ++x) {
        if (1.0 / count_factorial(x) < accuracy) {
            return x;
        }
    }
    return CHAR_MAX;
}

double count_e_to_n(unsigned char n) {
    // 只能用迭代了
    double res = 0;
    for (int i = 0; i <= n; ++i) {
        res += 1.0 / count_factorial(i);
    }
    return res;
}
