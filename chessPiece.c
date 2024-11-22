#include <stdio.h>
#define chess_piece 6


int main(void)
{
    int correct_chess[chess_piece] = {1, 1, 2, 2, 2, 8};
    int white_chess[chess_piece];

    for(int i = 0; i < chess_piece; i++)scanf("%d", &white_chess[i]);

    for(int i = 0; i < chess_piece; i++)
        printf("%d ",correct_chess[i] - white_chess[i]);
    printf("\n");
    return 0;
}