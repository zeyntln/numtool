// Dosya Adı : main.c
// Ad Soyad Numara 1 : Zeyneb Taflan - 453208
// Ad Soyad Numara 2 : Şevval Karagöz - 453188


#include <stdio.h>
#include <stdlib.h>
#include "parser.h"


// argc: komut satırından gelen argüman sayısı
// argv: argümanların kendisi (argv[0] program adı, argv[1] giriş, argv[2] çıkış)
int main(int argc, char *argv[]) {

    // Argüman sayısı tam olarak 3 olmalı (program adı + giriş + çıkış)
    if (argc != 3) {
        fprintf(stderr, "Kullanım: %s <giriş_dosyası> <çıkış_dosyası>\n", argv[0]);
        fprintf(stderr, "Örnek: %s girdiler.txt sonuc.txt\n", argv[0]);
        return 1;
    }


    const char *input_file  = argv[1];
    const char *output_file = argv[2];


    // read_commands_from_file bu pointer'ı malloc ile dolduracak
    CommandRecord *records = NULL;

    // Giriş dosyasını oku, komutları ayrıştır ve records dizisine yerleştir
    int command_count = read_commands_from_file(input_file, &records);


    if (command_count == 0 && records == NULL) {
        fprintf(stderr, "HATA: Giriş dosyası okunamadı\n");
        return 1;
    }

    // Ayrıştırılmış tüm komutların sonuçlarını çıkış dosyasına yaz
    write_results_to_file(output_file, records, command_count);


    free(records);


    return 0;
}
