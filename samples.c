#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char* argv[]) {
    if (argc != 4) { //checkar se o user escreveu os 3 argumentos no terminal
        printf("Please enter correct arguments.\n");
        return 1;
    }

    char* file_name = argv[1]; //nome do ficheiro
    int number_samples =  atoi(argv[2]); //numero de samples
    int sample_size = atoi(argv[3]); //numero de caracteres em cada sample
    char buffer[sample_size+1]; //criar string temporaria para podermos chamar o fread() depois
    memset(buffer, '\0', sizeof(buffer));
    srandom(time(0)); //definir semente da geração de numeros aleatorios
    FILE* file = fopen(file_name, "r"); //abrir ficheiro
    if (file == NULL) { //checkar se o ficheiro foi aberto
        printf("Error opening file.\n");
        exit(1);
    }
    fseek(file, -sample_size, SEEK_END); //apontar para o fim do ficheiro menos o tamanho da sample para prevenir que uma sample comece no ultimo caracter do ficheiro
    long number_chars_in_file = ftell(file); //guardar o numero de caracteres para poder usar como resto na geração de um número aleatório que seja menor que o numero de caracteres do ficheiro

    for (int i = 0; i < number_samples; i++) {
        long r = random()%(number_chars_in_file+1); //numero random (0 < r < number_chars_in_file)
        fseek(file, r, SEEK_SET); //apontar para um caracter aleatorio do ficheiro
        fread(buffer, sample_size, 1, file); //ler sample
        printf(">%s<\n", buffer); //escrever sample no terminal
        memset(buffer, '\0', sizeof(buffer));
    }

    fclose(file); //fechar ficheiro

    return 0;
}