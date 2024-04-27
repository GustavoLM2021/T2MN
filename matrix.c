#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

int courseLen=0;

typedef struct {
    float cs;
    float cf;
}nivel;
nivel niveis[16];

void makematrix(float n,int arrSI[],int arrSF[],float arrV[]){
    float matrix[courseLen+1][courseLen+1];

    for (int i = 0; i < courseLen*2; i++) {
        //printf("%i %i %i %f\n",i,arrSI[i],arrSF[i],arrV[i]);
        if(arrSI[i]==arrSF[i]){
            niveis[arrSI[i]].cf=arrV[i];
            //printf("%i %i %f\n",i,arrSI[i],niveis[arrSI[i]].cf);
        }
        else {
            niveis[arrSI[i]].cs=arrV[i];
            //  printf("%i %i %f\n",i,arrSI[i],niveis[arrSI[i]].cs);
        }
    }
    for (int i = 0; i <= courseLen; i++) {
        //printf("S:%i CS:%f CF:%f\n",i,niveis[i].cs,niveis[i].cf);
    }
    for (int i = 0; i <= courseLen+1; i++) {
        for (int j = 0; j <= courseLen + 1; j++) {
            matrix[i][j]=0;
        }
    }
    matrix[1][courseLen+1]=n*-1;
    for (int i = 1; i < courseLen+1; i++) {
        matrix[i][i]=niveis[i].cf-1;
        matrix[i][i-1]=niveis[i-1].cs;
        //printf("M=%f M2=%f \n",matrix[i][i],matrix[i][i-1]);
    }
    for (int i = 1; i < courseLen+1; i++) {
        //printf("MI:%i\n",i);
        for (int j = 1; j <= courseLen+1; j++) {
            if(matrix[i][j]==0){

            }
            //printf("MJ:%f ",matrix[i][j]);
        }
        //printf("\n");
    }
    float ratio;
    float x[courseLen+1];
    for(int i=1;i<=courseLen;i++)
    {
        if(matrix[i][i] == 0.0)
        {
            printf("Mathematical Error!");
            exit(0);
        }
        for(int j=i+1;j<=courseLen;j++)
        {
            ratio = matrix[j][i]/matrix[i][i];

            for(int k=1;k<=courseLen+1;k++)
            {
                matrix[j][k] = matrix[j][k] - ratio*matrix[i][k];
            }
        }
    }
    x[courseLen] = matrix[courseLen][courseLen+1]/matrix[courseLen][courseLen];
    for(int i=courseLen-1;i>=1;i--)
    {
        x[i] = matrix[i][courseLen+1];
        for(int j=i+1;j<courseLen;j++)
        {
            x[i] = x[i] - matrix[i][j]*x[j];
        }
        x[i] = x[i]/matrix[i][i];
    }
    for(int i=1;i<=courseLen;i++)
    {
        //printf("x[%d] = %0.3f\n",i, x[i]);
    }
    float csf=x[courseLen]*niveis[courseLen].cs;
    printf("Numero de Diplomados :%i\n",(int)csf);
    float sum=0;
    for (int i = 1; i <= courseLen; ++i) {
        sum+=x[i];
    }
    printf("Numero ainda no Universidade:%i\n",(int)sum);
}

int main(int argc, char **argv) {
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(argv[1], "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);
    int count = 0;
    int inner = 0;
    int top = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
        if (read == 21) {
            //printf("%s", line);
            char *p = line;
            for (int i = 0; i < read; ++i) {
                if (isdigit(line[i]) && line[i - 1] != '_') {
                    //printf("[%c]",line[i]);
                    //primeiro valor do topo
                    long val = strtol(&line[i], &p, 10);
                    //printf("%ld",val);
                    top = val;
                    break;
                }
            }

        }
        count++;
    }

    fclose(fp);
    if (line)
        free(line);

    fp = fopen(argv[1], "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);
    count--;
    int arrSemI[(count)];
    int arrSemF[(count)];
    int c = 0;
    float arrVal[(count)];
    //int c2=0;
    read = getline(&line, &len, fp);
    while ((read = getline(&line, &len, fp)) != -1) {
        char *p = line;
        for (int j = 0; j < read; ++j) {
            if (isdigit(line[j]) && line[j - 1] == ' ') {
                float fc = atof(&line[j]);
                //printf ("%f\n",fc);
                arrVal[c] = fc;
                break;
            }
        }
        int i;
        for (i = 0; i < read; ++i) {
            if (isdigit(line[i]) && line[i - 1] == '_') {
                int tmp = atoi(&line[i]);
                //printf("%i\n",tmp);
                arrSemI[c] = tmp;
                break;
            }
        }
        i++;
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
    courseLen=count/2;
    makematrix(top,arrSemI,arrSemF,arrVal);



}