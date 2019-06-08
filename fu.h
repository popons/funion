#ifndef FU_H
#define FU_H

struct bits {
    // 仮数部
    uint32_t coef : 23;
    // 指数部
    uint32_t expo : 8;
    // 符号部
    uint32_t sign : 1;
};

union fu {
    float f;
    uint32_t u;
    bits b;
public:
    fu print(const char* tag = "no-tag") {
        printf("%s: %d %d %d(0x%06x) %.30f\n", tag, b.sign, b.expo, b.coef, b.coef, f);
        return *this;
    }
    fu print2(const char* tag = "no-tag", FILE* fp = stdout) {
        fprintf(fp, "%s: u:0x%08x sign:%d expo:%d coef:%d(0x%06x) %.100f,%g\n", tag, u, b.sign, b.expo - 127, b.coef, b.coef, f, f);
        return *this;
    }
    static fu from_u(uint32_t u) {
        fu x;
        x.u = u;
        return x;
    }
    static fu from_bit(uint32_t sign, uint32_t expo, uint32_t coef) {
        fu x;
        x.b.coef = coef;
        x.b.expo = expo;
        x.b.sign = sign;
        return x;
    }
    static fu from_f(float u) {
        fu x;
        x.f = u;
        return x;
    }
    fu incl(void) {
        b.coef++;
        if (b.coef == 0) {
            b.expo++;
        }
        return *this;
    }
    fu decl(void) {
        b.coef--;
        if (b.coef == 0x7fffff) {
            b.expo--;
        }
        return *this;
    }
};

#endif
