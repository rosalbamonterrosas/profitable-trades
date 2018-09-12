/*
 * tradingstocks.c
 * author     : Rosalba Monterrosas
 * ticker     : LULU
 * date       : July 4, 2018
 * description: Application that determines when the most profitable trade will occur for a stock at any point during a month.
 */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 31

void banner();
void readPrices(double* pPrices,char* fileName, int* pricesSize);
double getMinPrice(double* pStockPrices, int size);
double getMaxPrice(double* pStockPrices, int size);
void profitableTrades(double* pPrices, int pricesSize, double* pProfits, int* profitsSize);
void save(double* pProfits,int profitsSize,char* fileName2);
void print(double* pProfits,int profitsSize);

//Banner
void banner(){
    printf("Welcome to the Profitable Trades Application\n");
    printf("********************************************\n");
}

//Reading prices.txt into an array
void readPrices(double* pPrices,char* fileName, int* pricesSize){
    FILE* pFile=0;
    pFile=fopen(fileName,"r");
    if(pFile==NULL){
        printf("File did not open for reading.\n");
        exit(0);
    }
    while(fscanf(pFile,"%lf",&pPrices[*pricesSize])>0){
        (*pricesSize)++;
    }
    if(pFile) fclose(pFile);
}

//Finding minimum closing price of an array
double getMinPrice(double* pStockPrices, int size){
    int i;
    double dMinPrice=pStockPrices[0];
    for(i=0;i<size;i++){
        if(dMinPrice>pStockPrices[i]){
            dMinPrice=pStockPrices[i];
        }
    }
    //printf("Min Price= %.2lf\n",dMinPrice);
    return dMinPrice;

}

//Finding maximum closing price of an array
double getMaxPrice(double* pStockPrices, int size){
    int i;
    double dMaxPrice=pStockPrices[0];
    for(i=0;i<size;i++){
        if(dMaxPrice<pStockPrices[i]){
            dMaxPrice=pStockPrices[i];
        }
    }
    //printf("Max Price= %.2lf\n",dMaxPrice);
    return dMaxPrice;

}

//Storing all possible profits in profits array
void profitableTrades(double* pPrices, int pricesSize, double* pProfits, int* profitsSize){
    int i;
    double dMaxPrice;
    int j=0;

    for(i=(pricesSize-1);i>0;i--){
        dMaxPrice=getMaxPrice(pPrices, i);
        pProfits[j]=dMaxPrice-pPrices[i];
        if(pProfits[j]>0){
            j++;
        }

    }
    *profitsSize = j;
//    for(j=0;j<(*profitsSize);j++){
//        printf("Profits[%d]=%lf\n",j,pProfits[j]);
//    }
}

//Save the Profits array in a file
void save(double* pProfits,int profitsSize,char* fileName2){
    int i;
    FILE* pFile=0;
    pFile=fopen(fileName2,"w");
    if(pFile==NULL){
        printf("File did not open for writing.\n");
        exit(0);
    }
    for(i=0;i<profitsSize;i++){
        fprintf(pFile,"Profits[%d]=%.2lf\n",i,pProfits[i]);
    }
    if(pFile) fclose(pFile);
}


//Print the Profits array
void print(double* pProfits,int profitsSize){
    int i;
    double dMaxPrice;
    dMaxPrice=getMaxPrice(pProfits,profitsSize);
    for(i=0;i<profitsSize;i++){
        printf("Profits[%d]=%.2lf\n",i,pProfits[i]);
    }
    printf("Maximum Profit = %.2lf\n",dMaxPrice);
}

//Test function
void test(){
    double prices[MAX_SIZE];
    char* fileName="prices.txt";
    char* fileName2="profits.txt";
//    int i;
    int pricesSize=0;
    int profitsSize=0;
    double profits[MAX_SIZE];

    banner();
    readPrices(prices,fileName,&pricesSize);
//    for(i=0;i<pricesSize;i++){
//        printf("%.2lf\n",prices[i]);
//    }
    getMinPrice(prices, pricesSize);
    getMaxPrice(prices, pricesSize);
    profitableTrades(prices, pricesSize, profits, &profitsSize);
    save(profits,profitsSize,fileName2);
    getMaxPrice(profits, profitsSize);
    print(profits,profitsSize);
}

int main() {
    test();
    return 0;
}
