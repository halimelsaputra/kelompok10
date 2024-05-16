#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PANJANG_MAKSIMAL_USERNAME 50
#define PANJANG_MAKSIMAL_PAsSWORD 50
#define ITEM_MAKSIMAL 100
#define PANJANG_MAKSIMAL_NAMA 50
#define PANJANG_MAKSIMAL_EMAIL 50
#define PANJANG_MAKSIMAL_ALAMAT 50
#define FILE_USERNAME "users.txt"
#define FILE_BARANG "barang.txt"
#define FILE_MEMBER "member.txt"


// Struktur untuk menyimpan informasi pengguna
struct User {
    char username[PANJANG_MAKSIMAL_USERNAME
];
    char password[PANJANG_MAKSIMAL_PAsSWORD];
};

struct Member {
    char nama[PANJANG_MAKSIMAL_NAMA];
    char alamat[PANJANG_MAKSIMAL_ALAMAT
];
};

// Struktur untuk menyimpan informasi barang
typedef struct {
    char nama[PANJANG_MAKSIMAL_NAMA];
    int stock;
    float harga;
} Item;

// Struktur untuk menyimpan informasi anggota
typedef struct {
    char nama[PANJANG_MAKSIMAL_NAMA];
    char email[PANJANG_MAKSIMAL_EMAIL];
} Member;

// Fungsi untuk menampilkan daftar anggota
void displayMembers() {
    FILE *file = fopen("member.txt", "r");
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }

    struct Member member;
    printf("Daftar Anggota:\n");

    while (fscanf(file, "%[^,],%[^\n]\n", member.nama, member.alamat) != EOF) {
         printf("--------------------\n");
        printf("Nama: %s\n", member.nama);
        printf("Email: %s\n", member.alamat);
        printf("--------------------\n");
    }

    fclose(file);
}

// Fungsi untuk melakukan registrasi pengguna baru
void registerUser() {
    struct User user;
    
    printf("Username: ");
    fgets(user.username, sizeof(user.username), stdin);
    user.username[strcspn(user.username, "\n")] = '\0'; // Menghapus karakter newline (\n)
    
    printf("Password: ");
    fgets(user.password, sizeof(user.password), stdin);
    user.password[strcspn(user.password, "\n")] = '\0'; // Menghapus karakter newline (\n)
    
    FILE *file = fopen(FILE_USERNAME, "a");  // Membuka file untuk menulis data pengguna baru
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }
    
    // Menulis informasi pengguna ke dalam file
    fprintf(file, "%s,%s\n", user.username, user.password);
    fclose(file);
    
    printf("Registrasi berhasil!\n");
}

// Fungsi untuk melakukan login
int loginUser() {
    struct User user;
    
    printf("Username: ");
    fgets(user.username, sizeof(user.username), stdin);
    user.username[strcspn(user.username, "\n")] = '\0'; // Menghapus karakter newline (\n)
    
    printf("Password: ");
    fgets(user.password, sizeof(user.password), stdin);
    user.password[strcspn(user.password, "\n")] = '\0'; // Menghapus karakter newline (\n)
    
    FILE *file = fopen(FILE_USERNAME, "r");   // Membuka file untuk membaca data pengguna
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return 0;
    }
    
    char line[PANJANG_MAKSIMAL_USERNAME
 + PANJANG_MAKSIMAL_PAsSWORD + 2];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0'; // Menghapus karakter newline (\n)
        char *username = strtok(line, ",");
        char *password = strtok(NULL, ",");
        
        if (username != NULL && password != NULL) {
            if (strcmp(user.username, username) == 0 && strcmp(user.password, password) == 0) {
                fclose(file);
                return 1; // Login berhasil
            }
        }
    }
    
    fclose(file);
    return 0; // Login gagal
}

// Fungsi untuk menambahkan barang baru
void addItemToFile(Item barang) {
    FILE *file = fopen(FILE_BARANG, "a");
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }

    // Menulis informasi barang ke dalam file
    fprintf(file, "%s,%d,%.2f\n", barang.nama, barang.stock, barang.harga);
    fclose(file);

    printf("Barang dengan nama '%s', stok '%d', dan harga '%.2f' berhasil ditambahkan.\n", barang.nama, barang.stock, barang.harga);
}

void addItem() {
    Item barang;

    printf("Masukkan nama barang: ");
    fgets(barang.nama, sizeof(barang.nama), stdin);
    barang.nama[strcspn(barang.nama, "\n")] = '\0'; // Menghapus karakter newline (\n)

    printf("Masukkan stok barang: ");
    scanf("%d", &barang.stock);

    printf("Masukkan harga barang: ");
    scanf("%f", &barang.harga);
    getchar();  // Menghapus karakter newline (\n) setelah membaca angka

    addItemToFile(barang);
}

void kurangiBarang() {
    char nama_barang[PANJANG_MAKSIMAL_NAMA];
    int jumlah;
    
    printf("Masukkan nama barang yang akan dikurangi stoknya: ");
    fgets(nama_barang, sizeof(nama_barang), stdin);
    nama_barang[strcspn(nama_barang, "\n")] = '\0';
    
    printf("Masukkan jumlah yang akan dikurangi: ");
    scanf("%d", &jumlah);
    getchar();

    FILE *file = fopen(FILE_BARANG, "r");
    FILE *temp_file = fopen("temp.txt", "w");
    if (file == NULL || temp_file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }

    char buffer[255];
    int found = 0;
    while (fgets(buffer, sizeof(buffer), file)) {
        Item barang;
        sscanf(buffer, "%[^,],%d,%f", barang.nama, &barang.stock, &barang.harga);
        
        if (strcmp(barang.nama, nama_barang) == 0) {
            barang.stock -= jumlah;
            if (barang.stock < 0) {
                barang.stock = 0; // Stok tidak boleh negatif
            }
            found = 1;
            printf("Stok barang berhasil dikurangi.\n");
        }
        fprintf(temp_file, "%s,%d,%.2f\n", barang.nama, barang.stock, barang.harga);
    }

    if (!found) {
        printf("Barang tidak ditemukan.\n");
    }

    fclose(file);
    fclose(temp_file);
    remove(FILE_BARANG);
    rename("temp.txt", FILE_BARANG);
}

void lihatDaftarBarang() {
    FILE *file = fopen(FILE_BARANG, "r");
    if (file == NULL) {
        printf("Gagal membuka file barang.\n");
        return;
    }

    printf("Daftar Barang:\n");
    char buffer[255];
    while (fgets(buffer, sizeof(buffer), file)) {
        Item barang;
        sscanf(buffer, "%[^,],%d,%f", barang.nama, &barang.stock, &barang.harga);
        printf("%s - Harga: %.2f - Stok: %d\n", barang.nama, barang.harga, barang.stock);
    }
    fclose(file);
}

// Fungsi untuk pembayaran dan menghitung kembalian
void pembayaran() {
    float total;
    float pembayaran;
    float kembalian;

    // Meminta total pembelian dari pengguna
    printf("Masukkan total pembelian: Rp");
    scanf("%f", &total);

    // Meminta pembayaran dari pengguna
    printf("Masukkan jumlah pembayaran: Rp");
    scanf("%f", &pembayaran);

    // Menghitung kembalian
    kembalian = pembayaran - total;

    // Memeriksa apakah pembayaran cukup
    if (kembalian >= 0) {
        printf("Terima kasih! Kembalian Anda: Rp%.2f\n", kembalian);
    } else {
        printf("Maaf, pembayaran Anda tidak mencukupi.\n");
    }
}

// Fungsi untuk menambahkan anggota baru
void addMemberToFile(Member member) {
    FILE *file = fopen(FILE_MEMBER, "a");
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }

    // Menulis informasi anggota ke dalam file
    fprintf(file, "%s,%s\n", member.nama, member.email);
    fclose(file);

    printf("Member dengan nama '%s' dan email '%s' berhasil ditambahkan.\n", member.nama, member.email);
}

void addMember() {
    Member member;

    printf("Masukkan nama member: ");
    fgets(member.nama, sizeof(member.nama), stdin);
    member.nama[strcspn(member.nama, "\n")] = '\0'; // Menghapus karakter newline (\n)

    printf("Masukkan email member: ");
    fgets(member.email, sizeof(member.email), stdin);
    member.email[strcspn(member.email, "\n")] = '\0'; // Menghapus karakter newline (\n)

    addMemberToFile(member);
}

int main() {
    int choice;
    
    do {
        printf("=== Sistem Kasir ===\n");
        printf("1. Registrasi\n");
        printf("2. Login\n");
        printf("3. Tambah Barang\n");
        printf("4. Kurangi Stok Barang\n");
        printf("5. Lihat Daftar Barang\n");
        printf("6. Pembayaran\n");
        printf("7. Tambah Anggota\n");
        printf("8. Lihat Anggota\n");
        printf("9. Keluar\n");
        printf("Pilihan Anda: ");
        scanf("%d", &choice);
        getchar();  // Menghapus karakter newline (\n) setelah membaca angka
        
        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                if (loginUser()) {
                    printf("Login berhasil!\n");
                } else {
                    printf("Username atau password salah. Login gagal.\n");
                }
                break;
            case 3:
                addItem();
                break;
            case 4:
                kurangiBarang();
                break;
            case 5:
                lihatDaftarBarang();
                break;
            case 6:
                pembayaran();
                break;
            case 7:
                addMember();
                break;
            case 8:
                displayMembers();
                break;
            case 9:
                printf("Terima kasih!\n");
                break;
            default:
                printf("Pilihan tidak valid. Silakan pilih kembali.\n");
        }
        
        printf("\n");
    } while (choice != 9);
    
    return 0;
}
