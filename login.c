#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PANJANG_USERNAME 50
#define MAX_PANJANG_PASSWORD 50

// Struktur untuk menyimpan informasi pengguna
struct Pengguna {
    char username[MAX_PANJANG_USERNAME];
    char password[MAX_PANJANG_PASSWORD];
};

// Fungsi untuk melakukan registrasi pengguna baru
void registrasiPengguna() {
    struct Pengguna pengguna;
    
    printf("Nama Pengguna: ");
    fgets(pengguna.username, sizeof(pengguna.username), stdin);
    pengguna.username[strcspn(pengguna.username, "\n")] = '\0'; // Menghapus karakter newline (\n)
    
    printf("Password: ");
    fgets(pengguna.password, sizeof(pengguna.password), stdin);
    pengguna.password[strcspn(pengguna.password, "\n")] = '\0'; // Menghapus karakter newline (\n)
    
    FILE *file = fopen("pengguna.txt", "a");  // Membuka file untuk menulis data pengguna baru
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }
    
    // Menulis informasi pengguna ke dalam file
    fprintf(file, "%s,%s\n", pengguna.username, pengguna.password);
    fclose(file);
    
    printf("Registrasi berhasil!\n");
}

// Fungsi untuk melakukan login
int loginPengguna() {
    struct Pengguna pengguna;
    
    printf("Nama Pengguna: ");
    fgets(pengguna.username, sizeof(pengguna.username), stdin);
    pengguna.username[strcspn(pengguna.username, "\n")] = '\0'; // Menghapus karakter newline (\n)
    
    printf("Password: ");
    fgets(pengguna.password, sizeof(pengguna.password), stdin);
    pengguna.password[strcspn(pengguna.password, "\n")] = '\0'; // Menghapus karakter newline (\n)
    
    FILE *file = fopen("pengguna.txt", "r");   // Membuka file untuk membaca data pengguna
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return 0;
    }
    
    char line[MAX_PANJANG_USERNAME + MAX_PANJANG_PASSWORD + 2];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0'; // Menghapus karakter newline (\n)
        char *username = strtok(line, ",");
        char *password = strtok(NULL, ",");
        
        if (username != NULL && password != NULL) {
            if (strcmp(pengguna.username, username) == 0 && strcmp(pengguna.password, password) == 0) {
                fclose(file);
                return 1; // Login berhasil
            }
        }
    }
    
    fclose(file);
    return 0; // Login gagal
}

int main() {
    int pilihan;
    
    do {
        printf("=== Sistem Kasir ===\n");
        printf("1. Registrasi\n");
        printf("2. Login\n");
        printf("3. Keluar\n");
        printf("Pilihan Anda: ");
        scanf("%d", &pilihan);
        getchar();  // Menghapus karakter newline (\n) setelah membaca angka
        
        switch (pilihan) {
            case 1:
                registrasiPengguna();
                break;
            case 2:
                if (loginPengguna()) {
                    printf("Login berhasil!\n");
                } else {
                    printf("Nama pengguna atau kata sandi salah. Login gagal.\n");
                }
                break;
            case 3:
                printf("Terima kasih!\n");
                break;
            default:
                printf("Pilihan tidak valid. Silakan pilih kembali.\n");
        }
        
        printf("\n");
    } while (pilihan != 3);
    
    return 0;
}
