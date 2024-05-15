#include <stdio.h>
#include <string.h>

#define PANJANG_NAMA_MAKS 50

struct Barang {
    char nama[PANJANG_NAMA_MAKS];
    int jumlah;
    float harga;
};

// Fungsi untuk melihat daftar barang
void lihatDaftarBarang() {
    FILE *file = fopen("barang.txt", "r");
    if (file == NULL) {
        printf("Gagal membuka file barang.\n");
        return;
    }

    printf("Daftar Barang:\n");
    char buffer[255];
    while (fgets(buffer, sizeof(buffer), file)) {
        struct Barang barang;
        sscanf(buffer, "%[^,],%d,%f", barang.nama, &barang.jumlah, &barang.harga);
        printf("%s - Harga: %.2f - Stok: %d\n", barang.nama, barang.harga, barang.jumlah);
    }
    fclose(file);
}

int main() {
    int choice;

    do {
        printf("\nMenu:\n");
        printf("1. Lihat Daftar Barang\n");
        printf("2. Keluar\n");
        printf("Pilih menu: ");
        scanf("%d", &choice);
        getchar(); // Membersihkan newline dari buffer

        switch (choice) {
            case 1:
                lihatDaftarBarang();
                break;
            case 2:
                printf("Keluar dari program.\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (choice != 3);

    return 0;
}
