// Dosya Adı : parser.h
// Ad Soyad Numara 1 : Zeyneb Taflan - 453208
// Ad Soyad Numara 2 : Şevval Karagöz - 453188

#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>


typedef struct {
    char       command[20];
    long long  args[4];
    int        arg_count;
    char       result[100];
    int        is_error;
} CommandRecord;

/* Tek bir komut metnini ayrıştırıp CommandRecord'a çevirir. */
CommandRecord parse_command(const char *command_str);

/* Dosyayı satır satır okur, içindeki tüm komutları records dizisine doldurur.
   Geriye işlenen komut sayısını döndürür. */
int  read_commands_from_file(const char *filename, CommandRecord **records);

/* Sonuçları belirtilen biçimde çıkış dosyasına yazar. */
void write_results_to_file(const char *filename, CommandRecord *records, int count);

#endif
