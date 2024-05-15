#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MEMBERS 100
#define MAX_NAME_LENGTH 50
#define MAX_EMAIL_LENGTH 50

// Struktur untuk menyimpan informasi anggota
typedef struct {
    char name[MAX_NAME_LENGTH];
    char email[MAX_EMAIL_LENGTH];
} Member;

// Fungsi untuk menambahkan anggota baru
void addMemberToFile(Member member) {
    FILE *file = fopen("members.txt", "a");
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }

    // Menulis informasi anggota ke dalam file
    fprintf(file, "%s,%s\n", member.name, member.email);
    fclose(file);

    printf("Anggota baru dengan nama '%s' dan email '%s' berhasil ditambahkan.\n", member.name, member.email);
}

int main() {
    Member member;

    printf("Masukkan nama anggota baru: ");
    fgets(member.name, sizeof(member.name), stdin);
    member.name[strcspn(member.name, "\n")] = '\0'; // Menghapus karakter newline (\n)

    printf("Masukkan email anggota baru: ");
    fgets(member.email, sizeof(member.email), stdin);
    member.email[strcspn(member.email, "\n")] = '\0'; // Menghapus karakter newline (\n)

    addMemberToFile(member);

    return 0;
}
