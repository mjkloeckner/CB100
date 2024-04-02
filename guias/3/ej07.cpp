// https://en.wikipedia.org/wiki/Tower_of_Hanoi

#include <iostream>

// Gives the steps to follow in order to move all the disks from src to dst
void move_stack(int disks, int src, int dst, int tmp)
{
    // Base case, move one disk from src to dst
    if(disks == 1) {
        printf("%d -> %d\n", src, dst);
        return;
    }

    // Move every disk except the biggest one to the tmp peg
    move_stack(disks - 1, src, tmp, dst);

    // Move the biggest one to the dst peg
    move_stack(1, src, dst, tmp);

    // Move all the disks on the tmp peg to the dst one
    move_stack(disks - 1, tmp, dst, src);
    return;
}

int main (void) {
    // Move 3 disks from first peg to third peg
    // using the second peg as temporary
    move_stack(3, 1, 3, 2);

    return 0;
}
