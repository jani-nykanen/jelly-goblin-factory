#include <stdio.h>

// Generates a test save file
int main(int argc, char** argv) {

    const int MAX = 45;

    FILE* f = fopen("save.dat", "wb");
    int i = 0;
    unsigned char b;
    for(; i < MAX; ++ i) {
        
        b = (i == 0 || i == MAX-1) ? 0 : 2;
        fwrite(&b, 1, 1, f);
    }
    fclose(f);
    return 0;

}
