#include <stdio.h>
#include <string.h>

#define PANJANG_NAMA_MAKS 50

struct Barang {
    char nama[PANJANG_NAMA_MAKS];
    int jumlah;
    float harga;
};

// Fungsi untuk mengurangi barang
void kurangiBarang() {
    char nama_barang[PANJANG_NAMA_MAKS];
    int jumlah;
    
    printf("Masukkan nama barang yang akan dikurangi stoknya: ");
    fgets(nama_barang, sizeof(nama_barang), stdin);
    nama_barang[strcspn(nama_barang, "\n")] = '\0';
    
    printf("Masukkan jumlah yang akan dikurangi: ");
    scanf("%d", &jumlah);
    getchar();

    FILE *file = fopen("barang.txt", "r");
    FILE *temp_file = fopen("temp.txt", "w");
    if (file == NULL || temp_file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }

    char buffer[255];
    int found = 0;
    while (fgets(buffer, sizeof(buffer), file)) {
        struct Barang barang;
        sscanf(buffer, "%[^,],%d,%f", barang.nama, &barang.jumlah, &barang.harga);
        
        if (strcmp(barang.nama, nama_barang) == 0) {
            barang.jumlah -= jumlah;
            if (barang.jumlah < 0) {
                barang.jumlah = 0; // Stok tidak boleh negatif
            }
            found = 1;
            printf("Stok barang berhasil dikurangi.\n");
        }
        fprintf(temp_file, "%s,%d,%.2f\n", barang.nama, barang.jumlah, barang.harga);
    }

    if (!found) {
        printf("Barang tidak ditemukan.\n");
    }

    fclose(file);
    fclose(temp_file);
    remove("barang.txt");
    rename("temp.txt", "barang.txt");
}

int main() {
    int choice;

    do {
        printf("\nMenu:\n");
        printf("1. Kurangi Stok Barang\n");
        printf("2. Keluar\n");
        printf("Pilih menu: ");
        scanf("%d", &choice);
        getchar(); // Membersihkan newline dari buffer

        switch (choice) {
            case 1:
                kurangiBarang();
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