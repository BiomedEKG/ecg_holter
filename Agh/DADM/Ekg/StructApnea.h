
#pragma once
//sturtura pczechowujaca dane o wczytanej probce PCA
struct probkaPCA {
    float PC1;
    float PC2;
    float PC3;
    float PC4;
    float PC5;
    float PC6;
    float PC7;
    float PC8;
    float PC9;
    float PC10;
    float PC11;
    char typ;
};


struct probkaWczytana {
    float srednia;
    float odchylenie;
    float NN50_1;
    float NN50_2;
    float pNN50_1;
    float pNN50_2;
    float SDSD;
    float RMSSD;
    float mediana;
    float IQR;
    float MAD;
    char typ;
};

