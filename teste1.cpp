#include <opencv2/opencv.hpp> //pacote que traz as funções
#include <iostream> // para que o codgio fale no terminal
#include <windows.h>


using namespace cv;
using namespace std;

//cout << "texto"; no lugar do printf("texto");.
//cin >> variavel; no lugar do scanf("%d", &variavel);.

// ao inves de int, usase mat para guardar uma matriz de pixels e VideoCapture
//que representa a webcam



int main (void){
    //como são classes, devem começar com letras maiusculas.
    VideoCapture cap(0); // Crie uma variável chamada 'cap' que é uma câmera e conecte na câmera 0 (webcam)".
    Mat frame; // como declarar um int x;, mas frame vai guardar a imagem.
    Mat frameCinza, frameBlur, frameEdges, frameHSV, frameInRange;
    vector <vector<Point>> contornos;
    Point2f centro; 
    float raio;
    int contadorFecha = 0;

    HANDLE serial = CreateFileA("COM3", GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0,0);
    // handle variavel do windows que representa uma conexão com algum recurso
    //createFileA é um afunção que abre uma  conexão

while(true){

     cap >> frame;

     if (frame.empty()){
        cout << "Erro: Nao consegui capturar a imagem!"<< endl;
        break;}

    cvtColor(frame, frameHSV, COLOR_BGR2HSV);
    cvtColor(frame, frameCinza, COLOR_BGR2GRAY);
    GaussianBlur(frameCinza, frameBlur, Size (7,7), 1.5);
    Canny(frameBlur, frameEdges, 100, 200);
   
    inRange ( frameHSV, Scalar(0,20,70), Scalar (20,255,255), frameInRange);
    findContours(frameInRange, contornos, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    int maiorIndice = -1; //guarda a posição do maior contorno na lista
    float maiorArea = 0; // guarda o tamanho do maior contorno encontrado até agora

    for (int i = 0; i < contornos.size(); i++){
        float area = contourArea(contornos[i]); //calcula a área do contorno na posição i
        if (area > maiorArea){ // se essa área for maior que a maior até agora
            maiorArea= area; // atualiza a maior area
            maiorIndice = i; // guarda a posicao desse contorno
        }
    }

  if (maiorIndice >= 0) {
    drawContours(frame, contornos, maiorIndice, Scalar(0,255,0), 3);
    minEnclosingCircle(contornos[maiorIndice], centro, raio);
    
    if (maiorArea < 29000) {
        contadorFecha++;
    } else {
        contadorFecha = 0;
    }

    DWORD enviado;
    if (contadorFecha >= 5) {
        putText(frame, "Garra fecha", centro, FONT_HERSHEY_SIMPLEX, 1, Scalar(0,0,255), 3);
        WriteFile(serial, "F", 1, &enviado, NULL);
    } else {
        putText(frame, "Garra abre", centro, FONT_HERSHEY_SIMPLEX, 1, Scalar(0,255,0), 3);
        WriteFile(serial, "A", 1, &enviado, NULL);
    }
}


    //findContours: varre o frameEdges e agrupa pixels brancos conectados em formas
    // RETR_EXTERNAL: pega só contornos externos
    // CHAIN_APPROX_SIMPLE: guarda só os pontos essenciais de cada forma
    // cout imprimi texto no terminal
    // imshow imprimi uma imagem em uma janela grafica


    imshow("Original", frame);
    imshow("Processada", frameCinza);
    imshow("Blur", frameBlur);
    imshow("Contorno", frameEdges);
    imshow("Pele", frameInRange);

    if (waitKey(30) >=0) break;}

return 0;
}
