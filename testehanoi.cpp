// programação teste para a torre de hanoi


#include <stdio.h>

// cada dupla de variavel é para um servo
int garraFecha = 0;
int alturaSobe = 180;
int baseEsq = 120;
int baseDir = 60;
int garraAbre = 90;
int alturaDesce = 0;


void pontoZero (){
    printf("Centralizando robo \n ");
}

void abrirGarra (){
printf("Abrindo garra \n");
}

void fecharGarra (){
printf("Fechando garra \n");
}

void subindoGarra (){
printf("Subindo garra \n");
}

void descendoGarra (){
printf("Descendo garra \n");
}

void girandoDbraco (){
printf("Girando para a direita o braco \n");
}

void girandoEbraco (){
printf("Girando para a esquerda o braco \n");
}
    
    int main (void){
        pontoZero();
        abrirGarra();

        return 0;
    }