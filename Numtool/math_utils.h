// Dosya Adı : math_utils.h
// Ad Soyad Numara 1 : Zeyneb Taflan - 453208
// Ad Soyad Numara 2 : Şevval Karagöz - 453188


#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#include <stdint.h>

long long gcd(long long a, long long b);

long long extended_gcd(long long a, long long b, long long *x, long long *y);

long long mod_inverse(long long a, long long m);

long long binary_pow(long long base, long long exp, long long mod);

int is_prime(long long n);

long long euler_phi(long long n);

#endif
