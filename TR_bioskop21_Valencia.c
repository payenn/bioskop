//valencia calista - 672023172
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <time.h>

#define MAX_ITEMS 10
#define MAX_NAME_LENGTH 50
#define MAX_PURCHASED_ITEMS 10

time_t rawtime;
struct tm *timeinfo;
char pembeli[MAX_NAME_LENGTH];
int barang, jumlah;
int exxt();

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Struktur untuk menyimpan detail pembelian item
struct PurchasedItem {
    int number;
    char name[MAX_NAME_LENGTH];
    int quantity;
    float totalHarga;
};

// Struktur untuk node Linked List pembeli
struct CustomerNode {
    char name[MAX_NAME_LENGTH];
    struct PurchasedItem purchasedItems[MAX_PURCHASED_ITEMS];
    int purchasedItemCount;
    float totalHarga;
    int isPaid;
    struct CustomerNode *next;
};

// Struktur untuk node Binary Tree tiket
struct TicketNode {
    int number;
    char name[MAX_NAME_LENGTH];
    int quantity;
    float totalHarga;
    struct TicketNode *left;
    struct TicketNode *right;
};

// Head untuk linked list pembeli
struct CustomerNode *customerHead = NULL;
// Root untuk binary tree tiket
struct TicketNode *ticketRoot = NULL;

struct Item {
    int number;
    char name[MAX_NAME_LENGTH];
    float price;
};

struct Item items[MAX_ITEMS] = {
    {1, "our season", 35000},
    {2, "exhuma", 40000},
    {3, "The little boy", 35000},
    {4, "Planet earth", 40000},
    {5, "Bumi manusia", 35000},
    {6, "The mother instinct", 35000},
    {7, "Mak lampir", 40000},
    {8, "The nun", 40000},
    {9, "Insidious", 40000},
    {10, "Dilan 1998", 35000}
};

void toUpperCase(char *str) {
    int i = 0;
    while (str[i] != '\0') {
        str[i] = toupper(str[i]);
        i++;
    }
}

int login();
int menu();
void displayMoviesAndInputBuyer();
void displayBuyerName();
void processPayment();
void displayPurchasedTickets();
void removePurchase();

int main() {
    login();
    return 0;
}

int login() {
    char username[20];
    char password[20];

    system("Color F0");
    system("cls");
    printf("\n");
    gotoxy(45, 1);
    printf("=========================================");
    gotoxy(45, 2);
    printf("||        Welcome To Bioskop 21 ^_^    ||");
    gotoxy(45, 3);
    printf("||    Silahkan Login Terlebih Dahulu   ||");
    gotoxy(45, 4);
    printf("=========================================");

    gotoxy(52, 6);
    printf("     Username: ");
    scanf("%19s", username);
    gotoxy(52, 8);
    printf("     Password: ");
    int i = 0;
    while (1) {
        char ch = _getch();
        if (ch == '\r') {
            break;
        } else if (ch == '\b') {
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        } else if (i < 19) {
            password[i] = ch;
            printf("*");
            i++;
        }
    }
    password[i] = '\0';

    printf("\n");

    if ((strcmp(username, "admin") == 0) && (strcmp(password, "admin") == 0)) {
        system("cls");
        int loading;
        gotoxy(52, 3);
        printf("Harap bersabar ini ujian....");
        gotoxy(33, 4);
        for (loading = 0; loading <= 60; loading++) {
            printf("%c", 254);
            Sleep(50);
        }
        menu();
    } else {
        gotoxy(33, 11);
        printf("===================================================================");
        gotoxy(33, 12);
        printf("!!!-------------------- Maaf akses ditolak ---------------------!!!");
        gotoxy(33, 13);
        printf("!!!--- Silahkan Masukkan Username atau Password dengan benar ---!!!");
        gotoxy(33, 14);
        printf("===================================================================");
        _getch();
        login();
    }
}

int menu() {
    int pos = 1;
    int key;

    system("Color F0");
    do {
        system("cls");
        gotoxy(50, 1);
        printf("===================================");
        gotoxy(50, 2);
        printf("             BIOSKOP 21            ");
        gotoxy(50, 3);
        printf("===================================");

        gotoxy(45, 4);
        printf(pos == 1 ? "--> 1. Tampilkan film dan input pembeli\n" : "1. Tampilkan film dan input pembeli\n");
        gotoxy(45, 5);
        printf(pos == 2 ? "--> 2. Tampilkan nama pembeli\n" : "2. Tampilkan nama pembeli\n");
        gotoxy(45, 6);
        printf(pos == 3 ? "--> 3. Pembayaran\n" : "3. Pembayaran\n");
        gotoxy(45, 7);
        printf(pos == 4 ? "--> 4. Tampilkan daftar pembelian tiket\n" : "4. Tampilkan daftar pembelian tiket\n");
        gotoxy(45, 8);
        printf(pos == 5 ? "--> 5. Hapus pembelian\n" : "5. Hapus pembelian\n");
        gotoxy(45, 9);
        printf(pos == 6 ? "--> 6. EXIT\n" : "6. EXIT\n");

        key = _getch();
        if (key == 72) {
            pos--;
            if (pos < 1) pos = 6;
        } else if (key == 80) {
            pos++;
            if (pos > 6) pos = 1;
        }
    } while (key != '\r');

    switch (pos) {
        case 1: displayMoviesAndInputBuyer(); break;
        case 2: displayBuyerName(); break;
        case 3: processPayment(); break;
        case 4: displayPurchasedTickets(); break;
        case 5: removePurchase(); break;
        case 6: exxt(); break;
    }

    return 0;
}

// Fungsi untuk menambah pembeli ke linked list
void addCustomer(char *name) {
    struct CustomerNode *newNode = (struct CustomerNode*)malloc(sizeof(struct CustomerNode));
    strcpy(newNode->name, name);
    newNode->purchasedItemCount = 0;
    newNode->totalHarga = 0;
    newNode->isPaid = 0;
    newNode->next = customerHead;
    customerHead = newNode;
}

// Fungsi untuk mencetak daftar pembeli
void printCustomers(struct CustomerNode *node) {
    while (node != NULL) {
        printf("%s\n", node->name);
        node = node->next;
    }
}

// Fungsi untuk menambah tiket ke binary tree
struct TicketNode* insertTicket(struct TicketNode *root, int number, char *name, int quantity, float totalHarga) {
    if (root == NULL) {
        struct TicketNode *newNode = (struct TicketNode*)malloc(sizeof(struct TicketNode));
        newNode->number = number;
        strcpy(newNode->name, name);
        newNode->quantity = quantity;
        newNode->totalHarga = totalHarga;
        newNode->left = newNode->right = NULL;
        return newNode;
    }
    if (number < root->number) {
        root->left = insertTicket(root->left, number, name, quantity, totalHarga);
    } else {
        root->right = insertTicket(root->right, number, name, quantity, totalHarga);
    }
    return root;
}

// Fungsi untuk mencetak daftar tiket dalam binary tree
void printTickets(struct TicketNode *root) {
    if (root != NULL) {
        printTickets(root->left);
        printf("No: %d, Film: %s, Jumlah: %d, Total Harga: Rp %.2f\n", root->number, root->name, root->quantity, root->totalHarga);
        printTickets(root->right);
    }
}

void displayMoviesAndInputBuyer() {
    struct CustomerNode *currentCustomer;
    char nomor1;
    int j = 1;

    system("cls");
    printf("|-------------------------------------------------------------------------------------------------|\n");
    printf("|=================================== DAFTAR FILM BIOSKOP 21 ======================================|\n");
    printf("|-------------------------------------------------------------------------------------------------|\n");
    printf("|          No.          |                       Film                    |                   Harga Satuan                   |\n");
    printf("==============================================================================================================================\n");

    for (int i = 0; i < MAX_ITEMS; i++) {
        printf("|         %2d            | %-16s                                | Rp %.0f                                          |\n", items[i].number, items[i].name, items[i].price);
    }
    printf("==============================================================================================================================\n");

    printf("Mohon masukan Nama Pembeli: ");
    getchar();
    fgets(pembeli, sizeof(pembeli), stdin);
    pembeli[strcspn(pembeli, "\n")] = 0; // Remove newline character
    addCustomer(pembeli); // Tambahkan pembeli ke linked list

    currentCustomer = customerHead;

    do {
        printf("Silahkan masukkan barang ke - %d (1-10) dan 0 untuk batal: ", j);
        if (scanf("%d", &barang) != 1 || barang < 0 || barang > 10) {
            fflush(stdin);
            continue;
        }
        if (barang == 0) {
            menu();
            return;
        }

        printf("Masukkan jumlah barang yang anda ingin beli: ");
        scanf("%d", &jumlah);
        fflush(stdin);
        if (jumlah < 1) continue;

        currentCustomer->purchasedItems[currentCustomer->purchasedItemCount].number = items[barang - 1].number;
        strcpy(currentCustomer->purchasedItems[currentCustomer->purchasedItemCount].name, items[barang - 1].name);
        currentCustomer->purchasedItems[currentCustomer->purchasedItemCount].quantity = jumlah;
        currentCustomer->purchasedItems[currentCustomer->purchasedItemCount].totalHarga = items[barang - 1].price * jumlah;
        currentCustomer->totalHarga += items[barang - 1].price * jumlah;
        currentCustomer->purchasedItemCount++;

        // Tambahkan tiket ke binary tree
        ticketRoot = insertTicket(ticketRoot, items[barang - 1].number, items[barang - 1].name, jumlah, items[barang - 1].price * jumlah);

        j++;

        printf("Apakah ada pesanan lagi (y/t)? ");
        scanf(" %c", &nomor1);
    } while (nomor1 == 'y' || nomor1 == 'Y');

    menu();
}

void displayBuyerName() {
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    system("cls");
    printf("~");
    printf("\n|                          DAFTAR NAMA PEMBELI                        |");
    printf("\n~");
    printf("\t\t\t\t\t\t %02d/%02d/%d\n", timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900);
    printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t %02d:%02d:%02d", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

    if (customerHead == NULL) {
        printf("\n\nBelum ada nama pembeli yang ditambahkan.\n");
        printf("Mohon masukkan data dulu pada menu Daftar Film ^_^\n\n\n");
    } else {
        printf("\n\nNama Pembeli:\n");
        printCustomers(customerHead);
    }

    printf("Tekan tombol apa saja untuk kembali ke menu utama...");
    _getch();
    menu();
}

void processPayment() {
    struct CustomerNode *currentCustomer;
    char statusPembayaran;
    int pembelianCount = 1;

    system("cls");
    printf("Proses pembayaran...\n");

    currentCustomer = customerHead;
    if (currentCustomer == NULL) {
        printf("Belum ada pembeli yang ditambahkan.\n");
    } else {
        while (currentCustomer != NULL) {
            printf("\nPembeli %d: %s\n", pembelianCount, currentCustomer->name);
            printf("Total harga: Rp %.2f\n", currentCustomer->totalHarga);
            printf("Detail Pembelian:\n");
            for (int i = 0; i < currentCustomer->purchasedItemCount; i++) {
                printf("  - Kode Film: %d, Nama Film: %s, Jumlah: %d, Total Harga: Rp %.2f\n",
                       currentCustomer->purchasedItems[i].number,
                       currentCustomer->purchasedItems[i].name,
                       currentCustomer->purchasedItems[i].quantity,
                       currentCustomer->purchasedItems[i].totalHarga);
            }
            printf("Apakah pembeli sudah membayar? (y/t): ");
            scanf(" %c", &statusPembayaran);
            if (statusPembayaran == 'y' || statusPembayaran == 'Y') {
                currentCustomer->isPaid = 1;
                printf("Status pembayaran: Sudah dibayar\n");
            } else {
                currentCustomer->isPaid = 0;
                printf("Status pembayaran: Belum dibayar\n");
            }
            pembelianCount++;
            currentCustomer = currentCustomer->next;
        }
    }

    printf("\nProses pembayaran selesai.\n");
    printf("Tekan tombol apa saja untuk kembali ke menu utama...");
    _getch();
    menu();
}

void displayPurchasedTickets() {
    system("cls");
    printf("Daftar pembelian tiket:\n");

    if (ticketRoot == NULL) {
        printf("Belum ada tiket yang dibeli.\n");
    } else {
        printTickets(ticketRoot);
    }

    printf("Tekan tombol apa saja untuk kembali ke menu utama...");
    _getch();
    menu();
}


// Deklarasi fungsi (definisikan implementasinya di tempat lain)
struct TicketNode* deleteTicket(struct TicketNode* root, int number);
void deleteCustomerPurchase(struct CustomerNode* customer, int number);



void removePurchase() {
    char name[MAX_NAME_LENGTH];
    int ticketNumber;
    struct CustomerNode *currentCustomer;

    system("cls");

    printf("Hapus Pembelian\n");
    printf("Masukkan nama pembeli: ");
    fgets(name, MAX_NAME_LENGTH, stdin);
    name[strcspn(name, "\n")] = '\0';
    toUpperCase(name);

    currentCustomer = customerHead;

    while (currentCustomer != NULL && strcmp(currentCustomer->name, name) != 0) {
        currentCustomer = currentCustomer->next;
    }

    if (currentCustomer != NULL) {
        printf("Masukkan nomor tiket yang akan dihapus: ");
        scanf("%d", &ticketNumber);

        ticketRoot = deleteTicket(ticketRoot, ticketNumber);

        deleteCustomerPurchase(currentCustomer, ticketNumber);

        printf("Pembelian berhasil dihapus.\n");
    } else {
        printf("Nama pembeli tidak ditemukan.\n");
    }

    _getch();
    menu();
}

void deleteCustomerPurchase(struct CustomerNode* customer, int number) {
    for (int i = 0; i < customer->purchasedItemCount; i++) {
        if (customer->purchasedItems[i].number == number) {
            customer->totalHarga -= customer->purchasedItems[i].totalHarga;

            for (int j = i; j < customer->purchasedItemCount - 1; j++) {
                customer->purchasedItems[j] = customer->purchasedItems[j + 1];
            }

            customer->purchasedItemCount--;
            break;
        }
    }
}

struct TicketNode* deleteTicket(struct TicketNode* root, int number) {
    if (root == NULL) {
        return root;
    }

    if (number < root->number) {
        root->left = deleteTicket(root->left, number);
    } else if (number > root->number) {
        root->right = deleteTicket(root->right, number);
    } else {
        if (root->left == NULL) {
            struct TicketNode *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct TicketNode *temp = root->left;
            free(root);
            return temp;
        }

        struct TicketNode* temp = root->right;
        while (temp && temp->left != NULL) {
            temp = temp->left;
        }

        root->number = temp->number;
        strcpy(root->name, temp->name);
        root->quantity = temp->quantity;
        root->totalHarga = temp->totalHarga;
        root->right = deleteTicket(root->right, temp->number);
    }

    return root;
}


int exxt(){
	int totalProgress = 100;
    int barLength = 50;
    int i, j;

	system("cls");
	system("Color 04");
	gotoxy(62, 13);
    printf("LOADING\n");

    for (i = 0; i <= totalProgress; i++){
        int progressLength = (int)((i / (float)totalProgress) * barLength);

		gotoxy(40, 15);
        printf(" ");
        for (j = 0; j < barLength; j++){
            if(j < progressLength){
                printf("%c", 219);
            }
			else{
                printf(" ");
            }
        }
        printf("  %d%%\r", (int)((i / (float)totalProgress) * 100));
        fflush(stdout);

        usleep(100000);
    }
    gotoxy(40, 17);
	printf("TERIMA KASIH TELAH BERBELANJA DI BIOSKOP 21 ^_^");

	Sleep(5000);
	printf("\r");

    exit(0);
}