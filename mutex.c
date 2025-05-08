#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <termios.h>
#include <stdbool.h>

pthread_mutex_t mutex;
bool validate = true;

char rua1[4][2] = {{' ', ' '}, {' ', ' '}, {' ', ' '}, {' ', ' '}};
char rua2[4][2] = {{' ', ' '}, {' ', ' '}, {' ', ' '}, {' ', ' '}};
char compartilhado[1][2] = {{' ', ' '}};
int start1 = 0, start2 = 0;
int i = 3;
int j = 3;
int k = 3;
int l = 3;

void *transito(){
    int i = 0;
    while (1)
    {
        system("clear");
        if (validate)
        {
            printf("\n\n");
            printf("               rua 1\n");
            printf("             +      +\n");
            printf("             |  %c%c  |\n", rua1[0][0], rua1[0][1]);
            printf("             +------+\n");
            printf("             |  %c%c  |\n", rua1[1][0], rua1[1][1]);
            printf("      +--+---+\033[32m------\033[39m+---+--+\n");
            printf("rua 4 %c%c | %c%c\033[31m|\033[39m  %c%c  |%c%c | %c%c  rua 2\n", rua2[0][0], rua2[0][1], rua2[1][0], rua2[1][1], compartilhado[0][0], compartilhado[0][1], rua2[2][0], rua2[2][1], rua2[3][0], rua2[3][1]);
            printf("      +--+---+------+---+--+\n");
            printf("             |  %c%c  |\n", rua1[2][0], rua1[2][1]);
            printf("             +------+\n");
            printf("             |  %c%c  |\n", rua1[3][0], rua1[3][1]);
            printf("             +      +\n");
            printf("               rua 3\n\n\n");
        }
        else
        {
            printf("\n\n");
            printf("               rua 1\n");
            printf("             +      +\n");
            printf("             |  %c%c  |\n", rua1[0][0], rua1[0][1]);
            printf("             +------+\n");
            printf("             |  %c%c  |\n", rua1[1][0], rua1[1][1]);
            printf("      +--+---+\033[31m------\033[39m+---+--+\n");
            printf("rua 4 %c%c | %c%c\033[32m|\033[39m  %c%c  |%c%c | %c%c  rua 2\n", rua2[0][0], rua2[0][1], rua2[1][0], rua2[1][1], compartilhado[0][0], compartilhado[0][1], rua2[2][0], rua2[2][1], rua2[3][0], rua2[3][1]);
            printf("      +--+---+------+---+--+\n");
            printf("             |  %c%c  |\n", rua1[2][0], rua1[2][1]);
            printf("             +------+\n");
            printf("             |  %c%c  |\n", rua1[3][0], rua1[3][1]);
            printf("             +      +\n");
            printf("               rua 3\n\n\n");
        }

        while(start1 == 0){
            start1 = (rand() % 4) + 1;
            if(start1 == start2){
                start1 = 0;
            }
        }

        while(start2 == 0){
            start2 = (rand() % 4) + 1;
            if(start1 == start2){
                start2 = 0;
            }
        }
        

        usleep(299000);
    }
}

void *transito1(){
    while (1)
    {
        pthread_mutex_lock(&mutex);

        if (start1 == 1 || start2 == 1)
        {
            if (i == 1 && compartilhado[0][1] == ' '){
                validate = true;
            }
            
            if (rua1[3][1] == '1'){
                rua1[3][0] = rua1[3][1] = ' ';
                if (start1 == 1)
                {
                    start1 = 0;
                }
                if (start2 == 1)
                {
                    start2 = 0;
                }
            }else if((i==3 && ((rua1[0][1] != ' ' && rua1[0][1] != '1') || (rua1[1][1] != ' ' && rua1[1][1] != '1') || (compartilhado[0][1] != ' ' && compartilhado[0][1] != '1'))) || (i == 1 && ((rua1[2][1] != ' ' && rua1[2][1] != '1') || (rua1[3][1] != ' ' && rua1[3][1] != '1') || (compartilhado[0][1] != ' ' && compartilhado[0][1] != '1')))) {

            }else if (i == 1 && compartilhado[0][0] == ' ')
            {
                rua1[i][0] = rua1[i][1] = ' ';
                compartilhado[0][0] = 'C';
                compartilhado[0][1] = '1';
            }
            else if (compartilhado[0][1] == '1')
            {
                compartilhado[0][0] = compartilhado[0][1] = ' ';
                i++;
                i %= 4;
                rua1[i][0] = 'C';
                rua1[i][1] = '1';
            }
            else
            {
                rua1[i][0] = rua1[i][1] = ' ';
                i++;
                i %= 4;
                rua1[i][0] = 'C';
                rua1[i][1] = '1';
            }
        }
        pthread_mutex_unlock(&mutex);
        usleep(600000);
    }
}

void *transito2(){
    while (1)
    {
        pthread_mutex_lock(&mutex);
        
        if (start1 == 2 || start2 == 2)
        {
            if (j == 1 && compartilhado[0][1] == ' '){
                validate = false;
            }
            
            if (rua2[3][1] == '2')
            {
                rua2[3][0] = rua2[3][1] = ' ';
                if (start1 == 2)
                {
                    start1 = 0;
                }
                if (start2 == 2)
                {
                    start2 = 0;
                }
            }else if((j==3 && ((rua2[0][1] != ' ' && rua2[0][1] != '2') || (rua2[1][1] != ' ' && rua2[1][1] != '2') || (compartilhado[0][1] != ' ' && compartilhado[0][1] != '2'))) || (j == 1 && ((rua2[2][1] != ' ' && rua2[2][1] != '2') || (rua2[3][1] != ' ' && rua2[3][1] != '2') || (compartilhado[0][1] != ' ' && compartilhado[0][1] != '2')))) {

            }else if (j == 1 && compartilhado[0][0] == ' ')
            {
                rua2[j][0] = rua2[j][1] = ' ';
                compartilhado[0][0] = 'C';
                compartilhado[0][1] = '2';
            }
            else if (compartilhado[0][1] == '2')
            {
                compartilhado[0][0] = compartilhado[0][1] = ' ';
                j++;
                j %= 4;
                rua2[j][0] = 'C';
                rua2[j][1] = '2';
            }
            else
            {
                rua2[j][0] = rua2[j][1] = ' ';
                j++;
                j %= 4;
                rua2[j][0] = 'C';
                rua2[j][1] = '2';
            }
        }
        pthread_mutex_unlock(&mutex);
        usleep(600000);
    }
}

void *transito3(){
    while (1)
    {
        pthread_mutex_lock(&mutex);
        
        if (start1 == 3 || start2 == 3)
        {
            if (k == 1 && compartilhado[0][1] == ' '){
                validate = false;
            }
        
            if (rua2[0][1] == '3')
            {
                rua2[0][0] = rua2[0][1] = ' ';
                if (start1 == 3)
                {
                    start1 = 0;
                }
                if (start2 == 3)
                {
                    start2 = 0;
                }
            }else if((k == 1 && ((rua2[1][1] != ' ' && rua2[1][1] != '3') || (rua2[0][1] != ' ' && rua2[0][1] != '3'))) || ((k == 3 || k == 0 || k == 1) && ((rua1[2][1] != ' ' && rua1[2][1] != '3') || (rua1[3][1] != ' ' && rua1[3][1] != '3') || (compartilhado[0][1] != ' ' && compartilhado[0][1] != '3')))){

            }else if (k == 1 && compartilhado[0][0] == ' ')
            {
                rua1[2][0] = rua1[2][1] = ' ';
                compartilhado[0][0] = 'C';
                compartilhado[0][1] = '3';
            }
            else if (compartilhado[0][1] == '3')
            {
                compartilhado[0][0] = compartilhado[0][1] = ' ';
                k++;
                k %= 4;
                rua2[1][0] = 'C';
                rua2[1][1] = '3';
            }
            else
            {
                if(k == 3){
                    k++;
                    k%=4;
                    rua1[3][0] = 'C';
                    rua1[3][1] = '3';
                }else if(k == 0){
                    rua1[3][0] = rua1[3][1] = ' ';
                    k++;
                    k%=4;
                    rua1[2][0] = 'C';
                    rua1[2][1] = '3';
                }else if(k == 2){
                    rua2[1][0] = rua2[1][1] = ' ';
                    k++;
                    k%=4;
                    rua2[0][0] = 'C';
                    rua2[0][1] = '3';
                }
            }
        }
        pthread_mutex_unlock(&mutex);
        
        usleep(600000);

    }
}

void *transito4(){
    while (1)
    {
        pthread_mutex_lock(&mutex);

        if (start1 == 4 || start2 == 4)
        {
            if (l == 1 && compartilhado[0][1] == ' '){
                validate = true;
            }
        
            if (rua1[0][1] == '4')
            {
                rua1[0][0] = rua1[0][1] = ' ';
                if (start1 == 4)
                {
                    start1 = 0;
                }
                if (start2 == 4)
                {
                    start2 = 0;
                }
            }else if((l == 1 && ((rua1[1][1] != ' ' && rua1[1][1] != '4') || (rua1[0][1] != ' ' && rua1[0][1] != '4'))) || ((l == 3 || l == 0 || l == 1) && ((rua2[2][1] != ' ' && rua2[2][1] != '4') || (rua2[3][1] != ' ' && rua2[3][1] != '4') || (compartilhado[0][1] != ' ' && compartilhado[0][1] != '4')))){

            }else if (l == 1 && compartilhado[0][0] == ' ')
            {
                rua2[2][0] = rua2[2][1] = ' ';
                compartilhado[0][0] = 'C';
                compartilhado[0][1] = '4';
            }
            else if (compartilhado[0][1] == '4')
            {
                compartilhado[0][0] = compartilhado[0][1] = ' ';
                l++;
                l %= 4;
                rua1[1][0] = 'C';
                rua1[1][1] = '4';
            }
            else
            {
                if(l == 3){
                    l++;
                    l%=4;
                    rua2[3][0] = 'C';
                    rua2[3][1] = '4';
                }else if(l == 0){
                    rua2[3][0] = rua2[3][1] = ' ';
                    l++;
                    l%=4;
                    rua2[2][0] = 'C';
                    rua2[2][1] = '4';
                }else if(l == 2){
                    rua1[1][0] = rua1[1][1] = ' ';
                    l++;
                    l%=4;
                    rua1[0][0] = 'C';
                    rua1[0][1] = '4';
                }
            }
        }
        pthread_mutex_unlock(&mutex);
        usleep(600000);
    }
}

int main()
{
    pthread_mutex_init(&mutex, NULL);
    system("clear");
    pthread_t t0;
    pthread_t c1, c2, c3, c4;

    pthread_create(&c1, NULL, transito1, NULL);
    pthread_create(&c2, NULL, transito2, NULL);
    pthread_create(&c3, NULL, transito3, NULL);
    pthread_create(&c4, NULL, transito4, NULL);
    pthread_create(&t0, NULL, transito, NULL);

    pthread_join(t0, NULL);
    pthread_join(c1, NULL);
    pthread_join(c2, NULL);
    pthread_join(c3, NULL);
    pthread_join(c4, NULL);

    pthread_mutex_destroy(&mutex);
    return 0;
}
