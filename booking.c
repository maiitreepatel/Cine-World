#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node
{
    char row_no;
    int seat_no, pin;
    char book;
    struct node *next, *prev;
} node;

node *hn = NULL;

void create()
{
    node *nn, *cn;
    int j = 1;
    int k;
    char c = 'A';
    do
    {
        int i = 1;
        do
        {
            nn = (node *)malloc(sizeof(node));
            nn->next = nn->prev = NULL;
            nn->row_no = c;
            nn->seat_no = i;
            nn->pin = k;
            nn->book = 'a';
            if (hn == NULL)
            {
                hn = nn;
                nn->next = nn->prev = hn;
            }
            else
            {
                cn = hn;
                while (cn->next != hn)
                    cn = cn->next;
                cn->next = nn;
                nn->prev = cn;
                nn->next = hn;
                hn->prev = nn;
            }
            i++;
        } while (i <= 7);
        j++;
        c++;
    } while (j <= 10);
}

void display()
{
    node *cn;
    cn = hn;
    printf("--------------------------------------------------------------------------------\n");
    printf("|                                  Platinum                                    |\n");
    do
    {
        if ((cn->prev)->row_no != cn->row_no)
            printf("| ");
        printf("%c%d", cn->row_no, cn->seat_no);
        if (cn->book == 'a')
            printf(" [AVL]   ");
        else
            printf(" [BKD]   ");
        if ((cn->next)->row_no != cn->row_no)
            printf("|\n");
        if (cn->row_no == 'C' && cn->seat_no == 7)
        {
            printf("--------------------------------------------------------------------------------\n");
            printf("|                                  Gold                                        |\n");
        }
        if (cn->row_no == 'H' && cn->seat_no == 7)
        {
            printf("--------------------------------------------------------------------------------\n");
            printf("|                                 Silver                                       |\n");
        }
        cn = cn->next;
    } while (cn != hn);
    printf("%c%d", cn->row_no, cn->seat_no);
    if (cn->book == 'a')
        printf(" [AVL]   ");
    else
        printf(" [BKD]   ");
    printf("|\n");
    printf("--------------------------------------------------------------------------------\n\n");
    printf("PLATINUM-> 750                 GOLD-> 600                     SILVER->450\n");
}

void display1(node *tmp[20], int n)
{
    if (n != 1)
    {
        printf("------------------------------------------------------------------\n");
        printf("THANK YOU!\nYOU HAVE SUCCESFULLY BOOKED THE SEATS\n");
        for (int i = 1; i < n; i++)
            printf("%c%d    PIN : %d\n", tmp[i]->row_no, tmp[i]->seat_no, tmp[i]->pin);
        printf("!!!!!!!!KEEP PIN SAFELY!!!!!!!!!!!\n");
        printf("PINS ARE REQUIRED AT THE TIME OF CANCELATION OF SEATS\n");
        printf("------------------------------------------------------------------\n");
    }
}

void book_seat()
{
    node *cn, *temp[20];
    int n, z, flag;
    char row;
    int seat;
    char ch;
    do
    {
        z = 1;
        printf("\nEnter No Of Tickets you Want To Buy: ");
        scanf("%d", &n);
        printf("\nEnter Seat Number(s):   \n");
        for (int i = 1; i <= n; i++)
        {
            printf("SEAT NO.%d = ", i);
            scanf(" %c%d", &row, &seat);
            cn = hn;
            if (row >= 'A' && row <= 'E')
            {
                do
                {
                    if (cn->row_no == row && cn->seat_no == seat)
                    {
                        if (cn->book == 'a')
                        {
                            cn->book = 'b';
                            cn->pin = 1000 + rand() % 9000;
                            temp[z] = cn;
                            z++;
                        }
                        else
                        {
                            printf("INVALID CHOICE!\n");
                            printf("%c%d Seat is already reserved \n", cn->row_no, cn->seat_no);
                            i--;
                        }
                    }
                    cn = cn->next;
                } while (cn != hn);
            }
            else
            {
                do
                {
                    if (cn->row_no == row && cn->seat_no == seat)
                    {
                        if (cn->book == 'a')
                        {
                            cn->book = 'b';
                            cn->pin = 1000 + rand() % 9000;
                            temp[z] = cn;
                            z++;
                        }
                        else
                        {
                            printf("INVALID CHOICE!\n");
                            printf("%c%d Seat is already reserved\n", cn->row_no, cn->seat_no);
                            i--;
                        }
                    }
                    cn = cn->prev;
                } while (cn != hn);
            }
        }
        display1(temp, z);
        int totalAmount = 0;
        for (int i = 1; i < z; i++)
        {
            switch (temp[i]->row_no)
            {
                case 'A':
                case 'B':
                case 'C':
                    totalAmount += 750;
                    break;
                case 'D':
                case 'E':
                case 'F':
                    totalAmount += 600;
                    break;
                case 'G':
                case 'H':
                case 'I':
                case 'J':
                    totalAmount += 450;
                    break;
            }
        }
        printf("\nTotal Amount: %d\n", totalAmount);
        printf("\n\nPRESS 1 To check Seat Status\n");
        printf("PRESS 2 To book more seat(s)\n");
        printf("PRESS 3 To Exit BOOKING PORTAL\n");
        printf("Enter your choice: ");
        scanf(" %c", &ch);
        if (ch == '1')
            display();
    } while (ch == '2');
}

void cancel()
{
    char row, ch;
    int seat, pin;
    node *cn;
    printf("SEAT CANCELLATION\n");
    do
    {
        ch = 'a';
        cn = hn;
        printf("SEAT NUMBER: ");
        scanf(" %c%d", &row, &seat);
        printf("PIN: ");
        scanf("%d", &pin);
        if (row >= 'A' && row <= 'E')
        {
            do
            {
                if (cn->row_no == row && cn->seat_no == seat && cn->pin == pin)
                {
                    printf("Are you sure you want to cancel the seat (y/n) ");
                    char c;
                    scanf(" %c", &c);
                    if (c == 'y' || c == 'Y')
                    {
                        printf("SEAT CANCELLED SUCCESSFULLY!\n");
                        cn->book = 'a';
                    }
                }
                else if (cn->row_no == row && cn->seat_no == seat && cn->pin != pin)
                {
                    printf("INVALID SEAT NUMBER AND PIN COMBINATION!!!!\n");
                }
                cn = cn->next;
            } while (cn != hn);
        }
        else
        {
            do
            {
                if (cn->row_no == row && cn->seat_no == seat && cn->pin == pin)
                {
                    printf("Are you sure you want to cancel the seat (y/n) ");
                    char c;
                    scanf(" %c", &c);
                    if (c == 'y' || c == 'Y')
                    {
                        printf("SEAT CANCELLED SUCCESSFULLY!\n");
                        cn->book = 'a';
                    }
                }
                else if (cn->row_no == row && cn->seat_no == seat && cn->pin != pin)
                {
                    printf("INVALID SEAT NUMBER\n");
                }
                cn = cn->next;
            } while (cn != hn);
        }
        printf("\n\nPRESS 1 To Check Seat Status\n");
        printf("PRESS 2 To Cancel More Tickets\n");
        printf("PRESS 3 To Exit CANCELATION PORTAL\n");
        printf("\n Enter your choice: ");
        scanf(" %c", &ch);
        if (ch == '1')
            display();
    } while (ch == '2');
}

int main()
{
    int ch;
    char c;
    printf("                              CINE-WORLD\n");
    printf("Choose the timing you desire:\n");
    printf("1- 10:00 AM\t 2- 01:00 PM\t 3- 04:00 PM\t 4- 07:00 PM\t\n");
    printf("Enter your choice: ");
    scanf("%d", &ch);
    switch (ch)
    {
        case 1:
        case 2:
        case 3:
        case 4:
            break;
        default:
            printf("INVALID TIMING\n");
            exit(0);
    }
    create();
    do
    {
        printf("1. DISPLAY SEATS\n2. BOOK SEATS\n3. CANCEL SEATS\n4. EXIT\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);
        switch (ch)
        {
            case 1:
                display();
                break;
            case 2:
                book_seat();
                break;
            case 3:
                cancel();
                break;
            case 4:
                printf("EXITING...");
                break;
            default:
                printf("INVALID CHOICE\n");
        }
    } while (ch != 4);
    return 0;
}
this is the code. this is a dsa project how do i include this in my resume
