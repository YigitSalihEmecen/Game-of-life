#include <stdio.h>
#include <stdlib.h>
#include <time.h>



void generate_field(int s1, int s2, int a[s1][s2])
{
    for(int i=0; i<s1; i++)
        for(int j=0; j<s2; j++)

            if (rand() % 10 < 5)
                a[i][j] = 1;
            else
                a[i][j] = 0;
}
void print_field(int s1, int s2, int a[s1][s2]){
    for(int i=0; i<s1; i++){
        for(int j=0; j<s2; j++)
            printf("%d ", a[i][j]);
        printf("\n");
    }
}
int count_neighbours(int i, int j, int s1, int s2, int a[s1][s2])
{
    int sum = 0;

    //sum += a[i][j];

    if(i != 0 ){
        sum += a[i-1][j]; // error if i==0
    }

    if (i != s1-1){
        sum += a[i+1][j]; // error if i==s1-1
    }

    if (j != 0){
        sum += a[i][j-1]; // error if j==0
    }

    if (j != s2-1){
        sum += a[i][j+1]; // error if j==s2-1
    }

    if (i != 0){
        if(j != 0){
            sum += a[i-1][j-1];
        }
    }
    if (i != 0){
        if(j != s2-1){
            sum += a[i-1][j+1];
        }
    }
    if (i != s1-1){
        if(j != 0){
            sum += a[i+1][j-1];
        }
    }
    if (i != s1-1){
        if(j != s2-1){
            sum += a[i+1][j+1];
        }
    }
    return sum;
}
void assign_neighbour_count(int s1, int s2, int a[s1][s2], int b[s1][s2])
{
    for (int i = 0; i < s1; i++) {
        for (int j = 0; j < s2; j++) {
            b[i][j] = count_neighbours(i, j, s1, s2, a);
        }
    }
}
void calculate_what_happens_and_assign(int s1, int s2, int a[s1][s2], int b[s1][s2]){
    for (int i = 0; i < s1; i++) {
        for (int j = 0; j < s2; j++) {
            if (a[i][j] == 0){
                if (b[i][j] == 3){
                    a[i][j] = 1;
                }
            }
            if (a[i][j] == 1){
                if (b[i][j] <= 1){
                    a[i][j] = 0;
                }
                else if(b[i][j] >= 4){
                    a[i][j] = 0;
                }
            }

        }
    }
}
void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 200 * number_of_seconds;

    // Storing start time
    clock_t start_time = clock();

    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds)
        ;
}

int main(){
    srand(time(0));

    int size_1=30, size_2=30;
    int a[size_1][size_2];
    int b[size_1][size_2];
    int mines;
    int gen = 100;

    generate_field(size_1, size_2, a);
    printf("---------------\nstarting point(gen-0)\n---------------\n");
    print_field(size_1, size_2, a);


    for(int i = 0; i < gen; i++){
        system("cls");
        printf("---------------\ngen-%d\n---------------\n", i+1);
        assign_neighbour_count(size_1, size_2, a, b);
        calculate_what_happens_and_assign(size_1, size_2, a, b);
        print_field(size_1, size_2, a);
        delay(1);
    }


    return 0;
}