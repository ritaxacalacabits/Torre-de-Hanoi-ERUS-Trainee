#include <Servo.h>

//servo que vai representar o motor físico

class BracoRobo {
    private: 
    Servo servoGarra, servoOmbro, servoBase, servoCotovelo;

    int garraFecha = 0;
    int alturaSobe = 180;
    int baseEsq = 120;
    int baseDir = 60;
    int baseCen = 90;
    int garraAbre = 90;
    int alturaDesce = 0;

    void moverDisco(int origem, int destino){
        girarPara(origem);
        descendoGarra();
        fecharGarra();
        subindoGarra();
        girarPara(destino);
        descendoGarra();
        abrirGarra();
        subindoGarra();
    }

    

    public:
    
    void iniciar(int pinoGarra, int pinoCotovelo, int pinoOmbro, int pinoBase){
        servoGarra.attach(pinoGarra); // pino 9 do arduino (so coisa arbitraria ate aqui)
        servoCotovelo.attach (pinoCotovelo);
        servoOmbro.attach (pinoOmbro);
        servoBase.attach (pinoBase);
        pontoZero();
         hanoi (3, baseEsq, baseDir, baseCen);

    }
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
            moverDisco(origem,destino);

        } else {
            hanoi (n-1, origem, auxiliar, destino);
            moverDisco(origem,destino);
            hanoi(n-1, auxiliar, destino, origem);

        }
    }

};

BracoRobo braco; // instancia global

//write e attach sao funçoes. write manda algo e attach sinaliza local.

void setup() {
braco.iniciar(9,3,5,6); 
    }
 
void loop() {
 

}
