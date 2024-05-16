#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BARANG 100
#define MAX_PANJANG_NAMA 50
#define NAMA_FILE "barang.txt"

// Struktur untuk menyimpan informasi barang
typedef struct {
    char nama[MAX_PANJANG_NAMA];
    int stok;
    float harga;
} Barang;

// Fungsi untuk menambahkan barang baru
void tambahBarangKeFile(Barang barang) {
    FILE *file = fopen(NAMA_FILE, "a");
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }

    // Menulis informasi barang ke dalam file
    fprintf(file, "%s,%d,%.2f\n", barang.nama, barang.stok, barang.harga);
    fclose(file);

    printf("Barang dengan nama '%s', stok '%d', dan harga '%.2f' berhasil ditambahkan.\n", barang.nama, barang.stok, barang.harga);
}

int main() {
    Barang barang;

    printf("Masukkan nama barang: ");
    fgets(barang.nama, sizeof(barang.nama), stdin);
    barang.nama[strcspn(barang.nama, "\n")] = '\0'; // Menghapus karakter newline (\n)

    printf("Masukkan stok barang: ");
    scanf("%d", &barang.stok);

    printf("Masukkan harga barang: ");
    scanf("%f", &barang.harga);

    tambahBarangKeFile(barang);

    return 0;
}
