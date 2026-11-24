//Vinicius Di Petta RA: 10769577

#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char palavra[50];
    int frequencia;
} Palavra;


int buscaBinaria(Palavra dicionario[], char palavra[], int inicio, int fim)
{
    if (inicio > fim)
    {
        return -1;
    }

    int meio = (inicio + fim) / 2;
    int comparacao = strcmp(palavra, dicionario[meio].palavra);

    if (comparacao == 0)
    {
        return meio;
    }
    else if (comparacao < 0)
    {
        return buscaBinaria(dicionario, palavra, inicio, meio - 1);
    }
    else
    {
        return buscaBinaria(dicionario, palavra, meio + 1, fim);
    }
}

int ehStopWord(char palavra[], char stopWords[][50], int qtdStopWords) {

    for (int j = 0; j < qtdStopWords; j++) {
        if (strcmp(palavra, stopWords[j]) == 0) {
            return 1;
        }
    }

    return 0;
}

void inserirOrdem(Palavra dicionario[], char palavra[], int *qtdPalavras)
{
    int i = *qtdPalavras - 1;

    while (i >= 0 && strcmp(palavra, dicionario[i].palavra) < 0)
    {
        dicionario[i + 1] = dicionario[i];
        i--;
    }
    strcpy(dicionario[i + 1].palavra, palavra);

    dicionario[i + 1].frequencia = 1;

    (*qtdPalavras)++;
}

int main() {

    Palavra dicionario[1000];

    char stopWords[4][50] = {
        "the",
        "in",
        "to",
        "a"
    };

    int qtdPalavras = 0;
    int qtdStopWords = 4;

    FILE *arquivo;

    arquivo = fopen("texto.txt", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo!");
        return 1;
    }

    char c;
    char palavra[50];
    int i = 0;

    while ((c = fgetc(arquivo)) != EOF) {

        if (isalpha((unsigned char)c)) {
            palavra[i] = tolower((unsigned char)c);
            i++;
        }
        else {

            if (i > 0) {
                palavra[i] = '\0';

                if (!ehStopWord(palavra, stopWords, qtdStopWords)) {
                    int posicao = buscaBinaria(dicionario, palavra, 0, qtdPalavras - 1);

                    if (posicao == -1)
                    {
                        inserirOrdem(dicionario, palavra, &qtdPalavras);
                    }
                    else
                    {
                        dicionario[posicao].frequencia++;
                    }
                }

                i = 0;
            }
        }
    }

    if (i > 0) {
        palavra[i] = '\0';

        if (!ehStopWord(palavra, stopWords, qtdStopWords)) {
            int posicao = buscaBinaria(dicionario, palavra, 0, qtdPalavras - 1);

                if (posicao == -1)
                {
                    inserirOrdem(dicionario, palavra, &qtdPalavras);
                }
                else
                {
                    dicionario[posicao].frequencia++;
                }
        }
    }

    for (int j = 0; j < qtdPalavras; j++)
    {
        printf("%s, %d\n", dicionario[j].palavra, dicionario[j].frequencia);
    }
    printf("total de palavras diferentes no dicionario = %d\n", qtdPalavras);

    fclose(arquivo);

    return 0;
}