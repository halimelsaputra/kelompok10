#include <stdio.h>
#include <stdlib.h>

#define PANJANG_MAKSIMAL_NAMA 50
#define PANJANG_MAKSIMAL_ALAMAT 100

struct Member {
    char name[PANJANG_MAKSIMAL_NAMA]; // Nama anggota
    char address[PANJANG_MAKSIMAL_ALAMAT]; // Alamat anggota
};

void displayMembers() {
    FILE *file = fopen("members.txt", "r"); // Membuka file anggota untuk dibaca
    if (file == NULL) { // Memeriksa apakah file berhasil dibuka
        printf("Gagal membuka file.\n");
        return;
    }

    struct Member member; // Membuat variabel untuk menyimpan data anggota

    printf("Daftar Anggota:\n");

    // Membaca data anggota dari file dan menampilkannya satu per satu
    while (fscanf(file, "%[^,],%[^\n]\n", member.name, member.address) != EOF) {
        printf("Nama: %s\n", member.name);
        printf("Alamat: %s\n", member.address);
        printf("--------------------\n");
    }

    fclose(file); // Menutup file setelah selesai membaca
}

int main() {
    displayMembers(); // Memanggil fungsi untuk menampilkan daftar anggota

    return 0;
}
