/* Code to simulate rolling three six-sided dice (D6)
 * User first types in seed value
 * Use seed value as argument to srand()
 * Call roll_three to generate three integers, 1-6
 * Print result "%d %d %d "
 * If triple, print "Triple!\n"
 * If it is not a triple but it is a dobule, print "Double!\n"
 * Otherwise print "\n"
 */


#include "dice.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    printf("Enter Seed:\n");
    int seed;
    scanf("%d", &seed);
    srand(seed);
    int one;
    int two;
    int three;
    roll_three(&one, &two, &three);
    printf("%d %d %d ", one, two, three);

    if(one==two && one==three)
    {
        printf("Triple!\n");
    }
    else if (one==two || one==three || two==three)
    {
        printf("Double!\n");
    }
    return 0;
}