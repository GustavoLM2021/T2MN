#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>



typedef struct {
    float N;
    float R;
    float S;
    float F;
    float D;
    float cs;
    float cf;
}nivel;
nivel niveis[16];
int courseLen=0;
int hell=0;

void init(int N,float arrV[],int arrSI[],int arrSF[]){
    for (int i = 0; i <16; i++) {
        niveis[i].N=0;
        niveis[i].R=0;
        niveis[i].S=0;
        niveis[i].F=0;
        niveis[i].D=0;
    }
    niveis[0].S=N;
    niveis[1].N=N;
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
    for (int i = 0; i <= courseLen *2; ++i) {
        //printf("S:%i N:%i R:%i S:%i F:%i D:%i CS:%f CF:%f\n",i,niveis[i].N,niveis[i].R,niveis[i].S,niveis[i].F,niveis[i].D,niveis[i].cs,niveis[i].cf);
    }

}
void matricula(){

for (int i =1; i<=courseLen; i++ ){
    printf("IND:%i N:%f R:%f S:%f F:%f D:%f CS:%f CF:%f\n",i,niveis[i].N,niveis[i].R,niveis[i].S,niveis[i].F,niveis[i].D,niveis[i].cs,niveis[i].cf);
    niveis[i].N=niveis[i-1].S;
    niveis[i].R=niveis[i].F;
    hell+=niveis[i].D;
}
niveis[courseLen+1].N=niveis[courseLen].S;
}
float estudo(){
    for (int i =1; i<=courseLen; i++ ){
        float batch=niveis[i].N+niveis[i].R;
        niveis[i].S=(niveis[i].cs*batch);
        niveis[i].F=(niveis[i].cf*batch);
        niveis[i].D=niveis[i].N+niveis[i].R-niveis[i].S+niveis[i].F;
    }
    return niveis[courseLen].S;
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
    int top=0;
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
                    top=val;
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
    int c=0;
    float arrVal[(count)];
    //int c2=0;
    read=getline(&line, &len, fp);
    while ((read = getline(&line, &len, fp)) != -1) {
            char *p = line;
            for (int j = 0; j < read; ++j) {
                if (isdigit(line[j]) && line[j - 1] != '_') {
                   float  fc=atof(&line[j]);
                   //printf ("%f\n",fc);
                   arrVal[c]=fc;
                   break;
                }
            }
            int i;
            for (i = 0; i < read; ++i) {
                if(isdigit(line[i]) && line[i - 1] == '_' ){
                    int tmp=atoi(&line[i]);
                    //printf("%i\n",tmp);
                    arrSemI[c]=tmp;
                    break;
                }
            }
            i++;
        for (; i < read; ++i) {
            if(isdigit(line[i]) && line[i - 1] == '_' || line[i]=='D'){
                int tmp=atoi(&line[i]);
                //printf("%i\n",tmp);
                arrSemF[c]=tmp;
                break;
            }
        }
        c++;
    }
    //printf("TOP:%i\n",top);
    for (int i = 0; i < (count); i+=2) {
        //printf("S%i S%i\n",arrSemI[i],arrSemF[i]);
    }
    for (int i = 0; i < (count); i++) {
        //printf("V%f\n",arrVal[i]);
    }
    courseLen = count/2;
    init(top,arrVal,arrSemI,arrSemF);

    fclose(fp);
    if (line)
        free(line);
    float prev=0;
    float actual=0;
    float diff=0;
    int x=0;
    float est=0;
    while (true){
        x++;
        matricula();
        actual=estudo();
        //printf("%f\n",actual);
        diff=actual-prev;
        //printf("ACT:%f PREV:%f\n",actual,prev);
        //printf("I:%i %f\n",x,diff);
        prev=actual;
        if(diff<0.01 && diff!=0){
            //printf("%f\n",diff);
            //printf("%i",x);
            break;
        }

    }
    for (int i = 0; i < courseLen; ++i) {
        est+=niveis[i].N+niveis[i].R;
    }
    printf("Diplomados:%f\n",niveis[courseLen+1].N);
    printf("Total na universidade: %f\n",est);
//    printf("Diplomados:%i\n",(int)niveis[courseLen].S);
//    printf("Total na universidade: %i\n",(int)est);


    exit(EXIT_SUCCESS);
}
