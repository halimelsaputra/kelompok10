#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MEMBER 100
#define MAKS_NAMA_PANJANG 50
#define MAKS_EMAIL_PANJANG 50

// Struktur untuk menyimpan informasi member
typedef struct {
    char nama[MAKS_NAMA_PANJANG];
    char email[MAKS_EMAIL_PANJANG];
} Anggota;

// Fungsi untuk menambahkan member baru
void tambahAnggotaKeFile(Anggota anggota) {
    FILE *file = fopen("anggota.txt", "a");
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }

    // Menulis informasi member ke dalam file
    fprintf(file, "%s,%s\n", anggota.nama, anggota.email);
    fclose(file);

    printf("Member berhasil ditambahkan.\n", anggota.nama, anggota.email);
}

int main() {
    Anggota anggota;

    printf("Masukkan nama member: ");
    fgets(anggota.nama, sizeof(anggota.nama), stdin);
    anggota.nama[strcspn(anggota.nama, "\n")] = '\0'; // Menghapus karakter newline (\n)

    printf("Masukkan email member: ");
    fgets(anggota.email, sizeof(anggota.email), stdin);
    anggota.email[strcspn(anggota.email, "\n")] = '\0'; // Menghapus karakter newline (\n)

    tambahAnggotaKeFile(anggota);

    return 0;
}
