
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

char num[32] ,go [2];
int base;
bool reapat() {
    char r;
    printf("Do you want to repeat or exit (y/n): ");
    scanf(" %c", &r);
    switch (r) {
        case 'y': case 'Y':return true;
        case 'n': case 'N':return false;
        default: printf("\033[1;31m Invalid choice. Please enter 'y' for yes or 'n' for no.\033[0m\n");
        return reapat(); }
}

int Digits_Number_In_Intger(char Digit) {//from char to integer
    switch (Digit) {
        case '0': return 0;
        case '1': return 1;
        case '2': return 2;
        case '3': return 3;
        case '4': return 4;
        case '5': return 5;
        case '6': return 6;
        case '7': return 7;
        case '8': return 8;
        case '9': return 9;
        case 'A': case 'a': return 10;
        case 'B': case 'b': return 11;
        case 'C': case 'c': return 12;
        case 'D': case 'd': return 13;
        case 'E': case 'e': return 14;
        case 'F': case 'f': return 15;
        default: return 666;}
}

int to_10() { 
    int sum = 0;
    int p = 0;
    for (int i = strlen(num) - 1; i >= 0; i--) {
        sum +=(int) Digits_Number_In_Intger(num[i]) * pow(base, p);
        p++;
    }
    return sum;
}
char* from_10_to_x(int base) {
    int num_form = to_10();
    static char sum[32] = ""; 
    int p = 0;
    char* DigitsInHex[] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F" };
    if (num_form == 0) {
        sum[p++] = '0';
        sum[p] = '\0';
        return sum;
    } while (num_form > 0) {
        strcpy(&sum[p++], DigitsInHex[num_form % base]); 
        num_form /= base;
    }
    sum[p] = '\0';
    strrev(sum);  
    return sum;
}

int read_base() {
    system("cls");
    char b[10];
    printf("\033[1;32m===========================================\033[0m\n");
	printf("\033[1;32m                      Base                 \n\033[0m");
    printf("\033[1;32m===========================================\033[0m\n");
    printf("\033[1;32m          [1] Base 2  .                  \033[0m  \n");
    printf("\033[1;32m          [2] Base 3  .                  \033[0m  \n");
    printf("\033[1;32m          [3] Base 4  .                  \033[0m  \n");
    printf("\033[1;32m          [4] Base 5  .                  \033[0m  \n");
    printf("\033[1;32m          [5] Base 6  .                  \033[0m  \n");
    printf("\033[1;32m          [6] Base 7  .                  \033[0m  \n");
    printf("\033[1;32m          [7] Base 8  .                  \033[0m  \n");
    printf("\033[1;32m          [8] Base 9  .                  \033[0m  \n");
    printf("\033[1;32m          [9] Base 10 .                  \033[0m  \n");
    printf("\033[1;32m          [10] Base 11 .                 \033[0m  \n");
    printf("\033[1;32m          [11] Base 12 .                 \033[0m  \n");
    printf("\033[1;32m          [12] Base 13 .                 \033[0m  \n");
    printf("\033[1;32m          [13] Base 14 .                 \033[0m  \n");
    printf("\033[1;32m          [14] Base 15 .                 \033[0m  \n");
    printf("\033[1;32m          [15] Base 16 .                 \033[0m  \n");
	printf("\033[1;32m===========================================\033[0m\n");
    do {
        printf("please Enter one of this bases (2,3,4,5,6,7,8,9,10,11,12,13,14,15,16): ");
        scanf("%s", &b);
    } while (!(strcmp(b,"2")==0 || strcmp(b,"8")==0  || strcmp(b,"3")==0  ||strcmp(b,"4")==0||strcmp(b,"5")==0 || strcmp(b,"6")==0  || strcmp(b,"7")==0  ||strcmp(b,"9")==0  || strcmp(b,"10")==0 || strcmp(b,"11")==0 || strcmp(b,"12")==0 || strcmp(b,"13")==0 || strcmp(b,"14")==0 || strcmp(b,"15")==0||strcmp(b,"16")==0  )); 
    base =atoi(b) ;
    return base;
}

void to_base() {
    system("cls");
    printf("\033[1;32m===========================================\033[0m\n");
	printf("\033[1;32m                 new  Base                 \033[0m\n");
    printf("\033[1;32m===========================================\033[0m\n");
    do{
    printf("Enter your new base (2 or 3 or 4 or 5 or 6 or 7 or 8 or 9 or 10 or 11 or 12 or 13 or 14 or 15 or 16): ");
    scanf("%s",&go);
    } while (!(strcmp(go,"2")==0 || strcmp(go,"8")==0  || strcmp(go,"3")==0  ||strcmp(go,"4")==0||strcmp(go,"5")==0 || strcmp(go,"6")==0  || strcmp(go,"7")==0  ||strcmp(go,"9")==0  || strcmp(go,"10")==0 || strcmp(go,"11")==0 || strcmp(go,"12")==0 || strcmp(go,"13")==0 || strcmp(go,"14")==0 || strcmp(go,"15")==0 ||strcmp(go,"16")==0  ));
    int go_to=atoi(go);
    
    switch (go_to) {
        case 10:printf("The number in base 10 is : %d\n", to_10());
            break;
        default:printf("The number in base %d is :%s\n",go_to,from_10_to_x(go_to));
            break;}
}

bool IsExit_Digits_In_Base_X(char Digit, short Base) {
    switch (Base) {
        case 16:
            return ((Digit >= '0' && Digit <= '9') || (Digit >= 'A' && Digit <= 'F') || (Digit >= 'a' && Digit <= 'f'));
        case 15:
            return ((Digit >= '0' && Digit <= '9') || (Digit >= 'A' && Digit <= 'E') || (Digit >= 'a' && Digit <= 'e')); 
        case 14:
            return ((Digit >= '0' && Digit <= '9') || (Digit >= 'A' && Digit <= 'D') || (Digit >= 'a' && Digit <= 'd')); 
        case 13:
            return ((Digit >= '0' && Digit <= '9') || (Digit >= 'A' && Digit <= 'C') || (Digit >= 'a' && Digit <= 'c'));  
        case 12:
            return ((Digit >= '0' && Digit <= '9') || (Digit >= 'A' && Digit <= 'B') || (Digit >= 'a' && Digit <= 'b'));
        case 11:
            return ((Digit >= '0' && Digit <= '9') || (Digit == 'A') || (Digit == 'a'));
        case 10:
            return (Digit >= '0' && Digit <= '9');
        case 9:
            return (Digit >= '0' && Digit <= '8');
        case 8:
            return (Digit >= '0' && Digit <= '7');
        case 7:
            return (Digit >= '0' && Digit <= '6');
        case 6:
            return (Digit >= '0' && Digit <= '5');
        case 5:
            return (Digit >= '0' && Digit <= '4');
         case 4:
            return (Digit >= '0' && Digit <= '3');
        case 3:
            return (Digit >= '0' && Digit <= '2');  
        case 2:
            return (Digit == '0' || Digit == '1'); 
        default:
            return false;}
}

bool dejet(int base) {
    for (int i = 0; i < strlen(num); i++) {//digit par digit
        if (!IsExit_Digits_In_Base_X(num[i], base)) {
            return false;}
    }
    return true;
}

void read()
{   system("cls");//clear the terminal
    do{
        read_base();
        do{
            printf("please Enter a number in base %d: ", base);
            scanf("%s",&num);
            if (to_10()<0)//if the  number is  big
            {
                printf("\033[1;31myour number is very big!!!!!\033[0m\n");
            }        
        } while (!dejet(base) ||  to_10()<0); //firver number is ixit in the base and not big
        to_base();
    } while (reapat());
}
