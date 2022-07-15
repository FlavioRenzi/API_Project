#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#define MAX_CHAR_LENGHT 13
#define STARTNODE 0

//#define DEBUG

unsigned int d;
unsigned int k;

int decreasing = 1;

unsigned int myAtoiTok(char **input);

int gets(char input[]);

void worstAdd(unsigned long topK[k][2], unsigned int id, unsigned long weight);

void circularAdd(unsigned long topK[k][2], unsigned int id, unsigned long weight);

void printTopK(unsigned long topK[k][2],unsigned int maxId);

void getMatrix(unsigned int matrix[d][d]);

void printMatrix(unsigned int matrix[d][d]);

unsigned long calcWeight(unsigned int matrix[d][d]);




int main() {


    //inital setup of d and k
    //d = dimension of matrix
    //k = number of graph in set

    //printf("insert d k\n");
    char input[(d*MAX_CHAR_LENGHT)+6];
    gets(input);
    d = atoi(strtok(input, " "));
    k = atoi(strtok(NULL, "\n"));
    //printf("d: %d, k: %d\n",d,k);


    //[k][0] = graph id
    //[k][1] = graph weight
    unsigned long topK[k][2];
    unsigned int matrix[d][d];
    unsigned int newId = 0;
    unsigned long oldWeight=ULLONG_MAX;
    unsigned long weight;
    while(gets(input)!=1){
        if (input[0]=='A'){
            getMatrix(matrix);
            weight = calcWeight(matrix);
            if(decreasing){
                if(oldWeight <= weight){
                    decreasing = 0;
                    if (newId<k){
                        int i;
                        for (i=newId;i<k;i++){
                            topK[i][1]= ULONG_MAX;
                        }
                    }
                    worstAdd(topK, newId,weight);
                }else{
                    circularAdd(topK, newId,weight);
                    oldWeight = weight;
                }
            }else{
                worstAdd(topK, newId,weight);
            }
            newId++;
        }else if(input[0]=='T'){
            printTopK(topK,newId);
            printf("\n");
        }
        #ifdef DEBUG
        else if(input[0]=='E'){
            break;
        }
        #endif
    }


    return 0;
}

void worstAdd(unsigned long topK[k][2], unsigned int id, unsigned long weight) {
    int x,y=0;
    for(x=1;x<=id && x<k;x++){
        if(topK[x][1]== ULONG_MAX){
            topK[x][0]=id;
            topK[x][1]=weight;
            return;
        }else if(topK[y][1] < topK[x][1]){
            y = x;
        }
    }if(topK[y][1]>weight){
        topK[y][0]=id;
        topK[y][1]=weight;
    }

}
void circularAdd(unsigned long topK[k][2], unsigned int id, unsigned long weight) {
    topK[(id)%k][0] = id;
    topK[(id)%k][1] = weight;
}




void getMatrix(unsigned int matrix[d][d]) {
    int y;
    char input[(d * MAX_CHAR_LENGHT) + 4];
    unsigned int num;
    for(y=0;y<d;y++) {
        gets(input);
        int x;
        char*array=input;

        for (x = 0; x < d; x++) {
            num = myAtoiTok(&array);
            if (num==0){
                matrix[y][x] = UINT_MAX;
            }else{
                matrix[y][x] = num;
            }
        }
    }
    #ifdef DEBUG
    printMatrix(matrix);
    #endif
}

void printMatrix(unsigned int matrix[d][d]) {
    int x,y;
    for(y=0;y<d;y++){
        for(x=0;x<d;x++){
            printf("%d, ",matrix[y][x]);
        }
        printf("\n");
    }
}

void printTopK(unsigned long topK[k][2],unsigned int maxId) {
    unsigned int x = 0;
    if(k<=maxId){
        x=k;
    }else if(maxId>0){
        x=maxId;
    }else{
        return;
    }
    char string[k*MAX_CHAR_LENGHT];

    unsigned int i;
    int pos = 0;
    unsigned int current = topK[0][0];
    if (current == 0){
        string[pos++] = '0';
    }else {
        while (current != 0) {
            unsigned int rem = current % 10;
            string[pos++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
            current = current / 10;
        }
        //reverse
        unsigned int j;
        char temp;
        for (j = 0; j < pos/2; j++){
            temp = string[j];
            string[j] = string[pos-j-1];
            string[pos-j-1]=temp;
        }
    }

    unsigned int oldPos;
    for(i=1;i<x;i++){
        string[pos++] = ' ';
        oldPos = pos;
        current = topK[i][0];
        if (current == 0){
            string[pos++] = '0';
        }else {
            while (current != 0) {
                unsigned int rem = current % 10;
                string[pos++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
                current = current / 10;
            }


            //reverse
            unsigned int j;
            char temp;
            for (j = 0; j < (pos - oldPos) / 2; j++) {
                temp = string[j + oldPos];
                string[j + oldPos] = string[pos - j - 1];
                string[pos - j - 1] = temp;
            }
        }
    }
    string[pos] = '\0';
    printf("%s",string);

}



unsigned long calcWeight(unsigned int matrix[d][d]){
    unsigned long  distance[d], pred[d];
    unsigned long visited[d], count, mindistance, nextnode = 0, i,j;

    j=0;
    for(i=0;i<d;i++){
        if(matrix[STARTNODE][i]==0){
            j++;
        }
    }
    if (j==d){
        return 0;
    }



    pred[0]=STARTNODE;
    pred[0]=pred[0];
    for(i=0;i< d;i++){
        distance[i]=matrix[STARTNODE][i];
        pred[i]=STARTNODE;
        visited[i]=0;
    }
    distance[STARTNODE]=0;
    visited[STARTNODE]=1;
    count=1;
    while(count < d-1){
        mindistance=UINT_MAX;
        for(i=0;i < d;i++)
            if(distance[i] < mindistance&&!visited[i])
            {
                mindistance=distance[i];
                nextnode=i;
            }
        visited[nextnode]=1;
        for(i=0;i < d;i++)
            if(!visited[i])
                if((unsigned long)mindistance+matrix[nextnode][i] < distance[i])
                {
                    distance[i]=mindistance+matrix[nextnode][i];
                    pred[i]=nextnode;
                }
        count++;
    }
    unsigned int sum = 0;
    for(i=1;i < d;i++){
        #ifdef DEBUG
        printf("\nDistance of %d = %d", i, distance[i]);
        printf("\nPath = %d", i);
        j=i;
        do
        {
            j=pred[j];
            printf(" <-%d", j);
        }
        while(j!=STARTNODE);
        #endif
        if(distance[i]!=UINT_MAX){
            sum += distance[i];
        }
    }
    return sum;
}

int gets(char input[]) {
    int x =0;
    char ch;
    while(1) {
        ch = getchar_unlocked();
        input[x++] = ch;
        if (ch == EOF) {
            return 1;
        } else if (ch == '\n'){
            input[x] = '\0';
            return 0;
        }
    }
}

unsigned int myAtoiTok(char **input){
    unsigned int x =0;
    unsigned int i;
    for (i = 0; (*input)[i+1] != '\0' && (*input)[i] != ','; ++i)
        x = x * 10 + (*input)[i] - '0';
    *input = &((*input)[i+1]);
    return x;
}
