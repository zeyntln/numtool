# Dosya Adı : Makefile
# Ad Soyad Numara 1 : Zeyneb Taflan - 453208
# Ad Soyad Numara 2 : Şevval Karagöz - 453188


CC      = gcc
CFLAGS  = -Wall -Wextra -O2
TARGET  = numtool
OBJS    = main.o parser.o math_utils.o

# Varsayilan hedef
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

# Her .c icin .o uretme kuralı
main.o: main.c parser.h math_utils.h
	$(CC) $(CFLAGS) -c main.c

parser.o: parser.c parser.h
	$(CC) $(CFLAGS) -c parser.c

math_utils.o: math_utils.c math_utils.h
	$(CC) $(CFLAGS) -c math_utils.c

# Temizlik 
.PHONY: clean
clean:
	rm -f $(TARGET) $(OBJS)