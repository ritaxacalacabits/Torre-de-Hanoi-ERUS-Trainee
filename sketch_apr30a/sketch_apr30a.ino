#include <Servo.h>

// int vai guardar o ângulo. todos valores aqui sao ficticios
int garraFecha = 0;
int alturaSobe = 180;
int baseEsq = 120;
int baseDir = 60;
int baseCen = 90;
int garraAbre = 90;
int alturaDesce = 0;


//servo que vai representar o motor físico

Servo servoGarra, servoOmbro, servoBase, servoCotovelo;

//write e attach sao funçoes. write manda algo e attach sinaliza local.

void pontoZero (){
servoCotovelo.write(alturaDesce);
servoGarra.write(garraFecha);
servoBase.write(baseCen);
servoOmbro.write(alturaDesce);

}

void abrirGarra (){
servoGarra.write(garraAbre); // manda o angulo la pro motor
}

void fecharGarra (){
servoGarra.write(garraFecha);
}

void subindoGarra (){
servoOmbro.write(alturaSobe);
servoCotovelo.write(alturaSobe);

}

void descendoGarra (){
servoOmbro.write(alturaDesce);
servoCotovelo.write(alturaDesce);
}


void girarPara (int angulo){
    servoBase.write(angulo);
}

void hanoi (int n, int origem, int destino, int auxiliar){
    if (n == 1){
        girarPara(origem);
        descendoGarra();
        fecharGarra();
        subindoGarra();
        girarPara(destino);
        descendoGarra();
        abrirGarra();
        subindoGarra();

    } else {
        hanoi (n-1, origem, auxiliar, destino);
        girarPara(origem);
        descendoGarra();
        fecharGarra();
        subindoGarra();
        girarPara(destino);
        descendoGarra();
        abrirGarra();
        subindoGarra();

        hanoi(n-1, auxiliar, destino, origem);

    }
}


void setup() {

  
        servoGarra.attach(9); // pino 9 do arduino (so coisa arbitraria ate aqui)
        servoCotovelo.attach (3);
        servoOmbro.attach (5);
        servoBase.attach (6);
    
        pontoZero();
        

        hanoi (3, baseEsq, baseDir, baseCen);
  
    }
 



void loop() {
 

}
