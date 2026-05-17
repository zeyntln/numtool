// Dosya Adı : parser.c
// Ad Soyad Numara 1 : Zeyneb Taflan - 453208
// Ad Soyad Numara 2 : Şevval Karagöz - 453188


#include "parser.h"
#include "math_utils.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LEN     1024
#define INITIAL_CAPACITY 10

/* String'in başındaki ve sonundaki boşlukları siler. */
static void trim_whitespace(char *str) {
    int i = 0, j;
    while (isspace((unsigned char)str[i])) i++;
    j = 0;
    while (str[i]) {
        str[j++] = str[i++];
    }
    str[j] = '\0';

    i = strlen(str) - 1;
    while (i >= 0 && isspace((unsigned char)str[i])) str[i--] = '\0';
}

/* Satırın yorum (#) veya tamamen boşluk olup olmadığını kontrol eder.
   String'e dokunmadan, sadece pointer ilerleterek bakıyoruz. */
static int is_comment_or_empty(const char *line) {
    while (isspace((unsigned char)*line)) line++;
    return *line == '\0' || *line == '#';
}

// kaydı hata olarak işaretler ve mesajı yazar. */
static void set_error(CommandRecord *r, const char *msg) {
    r->is_error = 1;
    strncpy(r->result, msg, sizeof(r->result) - 1);
    r->result[sizeof(r->result) - 1] = '\0';
}

CommandRecord parse_command(const char *command_str) {
    CommandRecord record = {0};
    record.is_error  = 0;
    record.arg_count = 0;

    
    // sscanf ile komutu ve en fazla 3 parametreyi tek seferde oku.
    // n   : kaç alan başarıyla okunduğunu döndürür
    char cmd_name[32] = {0};
    long long a1 = 0, a2 = 0, a3 = 0;
    int n = sscanf(command_str, "%31s %lld %lld %lld",
                   cmd_name, &a1, &a2, &a3);

    // Komut adı bile okunamadıysa hata
    if (n < 1) {
        strcpy(record.command, "UNKNOWN");
        set_error(&record, "ERROR_INVALID_INPUT");
        return record;
    }

    // Komut adını kayda yaz
    strncpy(record.command, cmd_name, sizeof(record.command) - 1);
    record.command[sizeof(record.command) - 1] = '\0';

    //GCD A B 
    if (strcmp(cmd_name, "GCD") == 0) {
        // Komut + 2 parametre = en az 3 alan okunmuş olmalı
        if (n < 3) {
            set_error(&record, "ERROR_INVALID_INPUT");
            return record;
        }

        record.args[0]   = a1;
        record.args[1]   = a2;
        record.arg_count = 2;

        //negatif veya sıfır kabul edilmiyor
        if (a1 <= 0 || a2 <= 0) {
            set_error(&record, "ERROR_INVALID_INPUT");
            return record;
        }

        long long g = gcd(a1, a2);
        snprintf(record.result, sizeof(record.result), "%lld", g);
    }

    //POW Taban Üs Mod
    else if (strcmp(cmd_name, "POW") == 0) {
        // Komut + 3 parametre = en az 4 alan okunmuş olmalı
        if (n < 4) {
            set_error(&record, "ERROR_INVALID_INPUT");
            return record;
        }

        record.args[0]   = a1;  // base
        record.args[1]   = a2;  // exp
        record.args[2]   = a3;  // mod
        record.arg_count = 3;

        // Negatif üs veya geçersiz mod red
        if (a2 < 0 || a3 <= 0) {
            set_error(&record, "ERROR_INVALID_INPUT");
            return record;
        }

        long long r = binary_pow(a1, a2, a3);
        snprintf(record.result, sizeof(record.result), "%lld", r);
    }

    //PRIME N 
    else if (strcmp(cmd_name, "PRIME") == 0) {
        if (n < 2) {
            set_error(&record, "ERROR_INVALID_INPUT");
            return record;
        }

        record.args[0]   = a1;
        record.arg_count = 1;

        // N < 2 reddedilmeli
        if (a1 < 2) {
            set_error(&record, "ERROR_INVALID_INPUT");
            return record;
        }

        strcpy(record.result, is_prime(a1) ? "YES" : "NO");
    }

    //INV A B
    else if (strcmp(cmd_name, "INV") == 0) {
        if (n < 3) {
            set_error(&record, "ERROR_INVALID_INPUT");
            return record;
        }

        record.args[0]   = a1;
        record.args[1]   = a2;
        record.arg_count = 2;

        if (a2 <= 0) {
            set_error(&record, "ERROR_INVALID_INPUT");
            return record;
        }

        long long inv = mod_inverse(a1, a2);
        if (inv == -1) {
            set_error(&record, "ERROR_NO_INVERSE");
            return record;
        }
        snprintf(record.result, sizeof(record.result), "%lld", inv);
    }

    //PHI N 
    else if (strcmp(cmd_name, "PHI") == 0) {
        if (n < 2) {
            set_error(&record, "ERROR_INVALID_INPUT");
            return record;
        }

        record.args[0]   = a1;
        record.arg_count = 1;

        // N < 1 reddedilmeli
        if (a1 < 1) {
            set_error(&record, "ERROR_INVALID_INPUT");
            return record;
        }

        long long phi = euler_phi(a1);
        snprintf(record.result, sizeof(record.result), "%lld", phi);
    }

    //CHECK A B 
    else if (strcmp(cmd_name, "CHECK") == 0) {
        if (n < 3) {
            set_error(&record, "ERROR_INVALID_INPUT");
            return record;
        }

        record.args[0]   = a1;
        record.args[1]   = a2;
        record.arg_count = 2;

        if (a2 <= 0) {
            set_error(&record, "ERROR_INVALID_INPUT");
            return record;
        }

        long long inv = mod_inverse(a1, a2);
        if (inv == -1) {
            set_error(&record, "ERROR_NO_INVERSE");
            return record;
        }

        // Modüler ters doğrulaması: (a * inv) % m == 1 mi?
        long long check = (a1 * inv) % a2;
        if (check == 1) {
            strcpy(record.result, "CORRECT");
        } else {
            set_error(&record, "FAILED");
        }
    }

    // Bilinmeyen komut
    else {
        set_error(&record, "ERROR_INVALID_INPUT");
    }

    return record;
}

int read_commands_from_file(const char *filename, CommandRecord **records) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "HATA: Giriş dosyası açılamıyor '%s'\n", filename);
        *records = NULL;
        return 0;
    }

    int count = 0;
    int capacity = INITIAL_CAPACITY;

    //INITIAL_CAPACITY kadar yer ayır
    *records = (CommandRecord *)malloc(capacity * sizeof(CommandRecord));
    if (!*records) {
        fprintf(stderr, "HATA: Bellek ayırma başarısız\n");
        fclose(fp);
        return 0;
    }

    char line[MAX_LINE_LEN];
    while (fgets(line, sizeof(line), fp)) {
        // Sondaki yeni satır karakterini sil
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }

        // Yorum veya boş satırsa atla
        if (is_comment_or_empty(line)) {
            continue;
        }

    //Aynı satırdaki komutları ';' ile böl.
        char line_copy[MAX_LINE_LEN];
        strncpy(line_copy, line, sizeof(line_copy) - 1);
        line_copy[sizeof(line_copy) - 1] = '\0';

        char *saveptr = NULL;
        char *cmd_str = strtok_r(line_copy, ";", &saveptr);

        while (cmd_str) {
            trim_whitespace(cmd_str);

            if (strlen(cmd_str) > 0 && cmd_str[0] != '#') {
                // Dizi doluysa kapasiteyi iki katına çıkar
                if (count >= capacity) {
                    capacity *= 2;
                    CommandRecord *tmp = (CommandRecord *)realloc(
                        *records, capacity * sizeof(CommandRecord));
                    if (!tmp) {
                        fprintf(stderr, "HATA: Bellek yeniden ayırma başarısız\n");
                        free(*records);
                        *records = NULL;
                        fclose(fp);
                        return count;
                    }
                    *records = tmp;
                }

                //komut ayrıştırılıp diziye eklenir
                (*records)[count] = parse_command(cmd_str);
                count++;
            }

            cmd_str = strtok_r(NULL, ";", &saveptr);
        }
    }

    fclose(fp);
    return count;
}

void write_results_to_file(const char *filename, CommandRecord *records, int count) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        fprintf(stderr, "HATA: Çıkış dosyası açılamıyor '%s'\n", filename);
        return;
    }


    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s", records[i].command);
        for (int j = 0; j < records[i].arg_count; j++) {
            fprintf(fp, " %lld", records[i].args[j]);
        }
        fprintf(fp, " -> %s\n", records[i].result);
    }

    fclose(fp);
}
