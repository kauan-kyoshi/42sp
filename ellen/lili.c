#include <stdio.h>

#ifdef _WIN32
    #include <windows.h>
    #define PAUSA(ms) Sleep(ms)
#else
    #include <unistd.h>
    #define PAUSA(ms) usleep(ms * 1000)
#endif

int main() {
    float x, y;

    printf("\033[1;31m");

    y = 1.5f;
    while (y > -1.5f) {
        x = -1.5f;
        while (x < 1.5f) {
            float z = x * x + y * y - 1;

            if (z * z * z - x * x * y * y * y <= 0.0f) {
                printf("*");
            } else {
                printf(" ");
            }

            fflush(stdout);

            PAUSA(1);

            x += 0.05f;
        }
        printf("\n");
        y -= 0.1f;
    }

    printf("\033[0m");

    printf("\n      =====================================");
    printf("\n      SISTEMA OPERACIONAL INVADIDO PELO AMOR!");
    printf("\n      Voce faz meu processador acelerar!");
    printf("\n      =====================================\n");

    return 0;
}