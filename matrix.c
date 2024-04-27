#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

int courseLen = 0;
//estrutura para botar os coeficientes de sucesso e falha
typedef struct {
    float cs;
    float cf;
} nivel;
nivel niveis[16];

void makematrix(float n, int arrSI[], int arrSF[], float arrV[]) {
    //cria a matriz
    float matrix[courseLen + 1][courseLen + 1];
    //preenche os coeficientes da estrutura
    for (int i = 0; i < courseLen * 2; i++) {

        //quando o semestres forem identicos coeficiente de falha desse semestre
        //caso diferentes coeficiente de sucesso do semestre
        if (arrSI[i] == arrSF[i]) {
            niveis[arrSI[i]].cf = arrV[i];
        } else {
            niveis[arrSI[i]].cs = arrV[i];
        }
    }
    //preenche a matriz com zeros
    for (int i = 0; i <= courseLen + 1; i++) {
        for (int j = 0; j <= courseLen + 1; j++) {
            matrix[i][j] = 0;
        }
    }
    //valor inserido na primeira linha e ultima coluna da matriz
    matrix[1][courseLen + 1] = n * -1;
    //preenchendo a matriz com os valores das equacoes
    for (int i = 1; i < courseLen + 1; i++) {
        matrix[i][i] = niveis[i].cf - 1;
        matrix[i][i - 1] = niveis[i - 1].cs;
    }
    //mostrar matriz
    for (int i = 1; i < courseLen + 1; i++) {
        //printf("MI:%i\n",i);
        for (int j = 1; j <= courseLen + 1; j++) {
            if (matrix[i][j] == 0) {

            }
            //printf("MJ:%f ",matrix[i][j]);
        }
        //printf("\n");
    }
    //metodo gaussiano
    float ratio;
    float x[courseLen + 1];
    for (int i = 1; i <= courseLen; i++) {
        if (matrix[i][i] == 0.0) {
            printf("error");
            exit(0);
        }
        //zerando os valores
        for (int j = i + 1; j <= courseLen; j++) {
            ratio = matrix[j][i] / matrix[i][i];

            for (int k = 1; k <= courseLen + 1; k++) {
                matrix[j][k] = matrix[j][k] - ratio * matrix[i][k];
            }
        }
    }
    //back substitution
    x[courseLen] = matrix[courseLen][courseLen + 1] / matrix[courseLen][courseLen];
    for (int i = courseLen - 1; i >= 1; i--) {
        x[i] = matrix[i][courseLen + 1];
        for (int j = i + 1; j < courseLen; j++) {
            x[i] = x[i] - matrix[i][j] * x[j];
        }
        x[i] = x[i] / matrix[i][i];
    }

    float csf = x[courseLen] * niveis[courseLen].cs;
    printf("Numero de Diplomados :%i\n", (int) csf);
    float sum = 0;
    for (int i = 1; i <= courseLen; ++i) {
        sum += x[i];
    }
    printf("Numero ainda na Universidade:%i\n", (int) sum);
}

int main(int argc, char **argv) {
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(argv[1], "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);
    //contador de linhas
    int count = 0;
    int inner = 0;
    int top = 0;
    //lendo a primeira linha
    if ((read = getline(&line, &len, fp)) != -1) {
        char *p = line;
        for (int i = 0; i < read; ++i) {
            if (isdigit(line[i]) && line[i - 1] != '_') {
                //primeiro valor do topo
                long val = strtol(&line[i], &p, 10);
                top = val;
                break;
            }
        }
        count++;
    }
    //le o arquivo ate chegar ao numero de linhas (apos primeira linha)
    while ((read = getline(&line, &len, fp)) != -1) {
        count++;
    }

    fclose(fp);
    if (line)
        free(line);
    //se o contador for zero erro
    if (count == 0) {
        exit(EXIT_FAILURE);
    }
    fp = fopen(argv[1], "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);
    count--;
    //count utilizado para dimensionar os arrays de semestres e dos coeficientes
    int arrSemI[(count)];
    int arrSemF[(count)];
    float arrVal[(count)];
    int c = 0;
    //int c2=0;
    read = getline(&line, &len, fp);
    while ((read = getline(&line, &len, fp)) != -1) {
        char *p = line;
        //pegando o coeficiente dos semestres
        for (int j = 0; j < read; ++j) {
            if (isdigit(line[j]) && line[j - 1] == ' ') {
                float fc = atof(&line[j]);
                //printf ("%f\n",fc);
                arrVal[c] = fc;
                break;
            }
        }
        int i;
        //pega o semestre do lado esquerdo da linha
        for (i = 0; i < read; ++i) {
            if (isdigit(line[i]) && line[i - 1] == '_') {
                int tmp = atoi(&line[i]);
                //printf("%i\n",tmp);
                arrSemI[c] = tmp;
                break;
            }
        }
        i++;
        //pega o semestre do lado direito da linha
        for (; i < read; ++i) {
            if (isdigit(line[i]) && line[i - 1] == '_' || line[i] == 'D') {
                int tmp = atoi(&line[i]);
                //printf("%i\n",tmp);
                arrSemF[c] = tmp;
                break;
            }
        }
        c++;
    }
    //tamanho do curso
    courseLen = count / 2;
    makematrix(top, arrSemI, arrSemF, arrVal);


}