/* simple driver to compile with compiled #YOCO program
   calls yocomain and prints returned value.
*/
#include <stdio.h>
int yocomain();

int main() {
    int n;
    printf("running yocomain...\n");
    n = yocomain();
    printf("eax = %d\n", n);
    return 0;
}
