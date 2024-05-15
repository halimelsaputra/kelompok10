#include <stdio.h>

int main() {
    float total;
    float payment;
    float change;

    // Meminta total pembelian dari pengguna
    printf("Masukkan total pembelian: Rp");
    scanf("%f", &total);

    // Meminta pembayaran dari pengguna
    printf("Masukkan jumlah pembayaran: Rp");
    scanf("%f", &payment);

    // Menghitung kembalian
    change = payment - total;

    // Memeriksa apakah pembayaran cukup
    if (change >= 0) {
        printf("Terima kasih! Kembalian Anda: Rp%.2f\n", change);
    } else {
        printf("Maaf, pembayaran Anda tidak mencukupi.\n");
    }

    return 0;
}
