// Dosya Adı : math_utils.c
// Ad Soyad Numara 1 : Zeyneb Taflan - 453208
// Ad Soyad Numara 2 : Şevval Karagöz - 453188


#include "math_utils.h"

// gcd fonksiyonu, iki sayının en büyük ortak bölenini hesaplar. 
// Euclid algoritması kullanılarak iteratif olarak hesaplanır.
long long gcd(long long a, long long b) {
    a = (a < 0) ? -a : a;
    b = (b < 0) ? -b : b;
    
    
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// extended_gcd fonksiyonu, iki sayının genişletilmiş euclid algoritması ile en büyük ortak bölenini ve katsayılarını hesaplar.
long long extended_gcd(long long a, long long b, long long *x, long long *y) {
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }
    
    long long x1, y1;
    long long g = extended_gcd(b, a % b, &x1, &y1);
    
    *x = y1;
    *y = x1 - (a / b) * y1;
    
    return g;
}

// mod_inverse fonksiyonu, bir sayının modüler tersini hesaplar.
long long mod_inverse(long long a, long long m) {
    long long x, y;
    long long g = extended_gcd(a, m, &x, &y);
    
    if (g != 1) {
        return -1;
    }
    
    x = (x % m + m) % m;
    return x;
}

// binary_pow fonksiyonu, bir sayının kuvvetini modüler aritmetik ile hesaplar.
long long binary_pow(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    
    if (base < 0) {
        base = (base % mod + mod) % mod;
    }
    
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    
    return result;
}

// is_prime fonksiyonu, bir sayının asal olup olmadığını kontrol eder.
int is_prime(long long n) {
    if (n <= 1) return 0;
    if (n == 2 || n == 3) return 1;
    if (n % 2 == 0 || n % 3 == 0) return 0;
    
    for (long long i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return 0;
        }
    }
    return 1;
}

// euler_phi fonksiyonu, bir sayının euler phi fonksiyonunun değerini hesaplar.
long long euler_phi(long long n) {
    long long result = n;
    
    for (long long p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            while (n % p == 0) {
                n /= p;
            }
            result = result - (result / p);
        }
    }
    
    if (n > 1) {
        result = result - (result / n);
    }
    
    return result;
}
