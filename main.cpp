#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    // 1. Tenta abrir a webcam (índice 0)
    VideoCapture cap(0); 

    if (!cap.isOpened()) {
        cout << "ERRO: Webcam nao encontrada!" << endl;
        return -1;
    }

    cout << "Webcam aberta com o efeito Canny! Aperte ESC para sair." << endl;

    // Cria as janelas (opcional, mas bom para organizar)
    namedWindow("Sua Webcam Original", WINDOW_AUTOSIZE);
    namedWindow("Efeito Desenho (Canny)", WINDOW_AUTOSIZE);

    Mat frame, gray, blurred, edges;

    while (true) {
        // 2. Pega o quadro atual da camera
        cap >> frame;
        if (frame.empty()) break;

        // --- PASSO A PASSO DO EFEITO ---

        // 3. Converte para Tons de Cinza (o Canny so funciona assim)
        cvtColor(frame, gray, COLOR_BGR2GRAY);

        // 4. Aplica um Blur (borrão) suave para reduzir o ruído (chuvisco)
        // Isso ajuda o Canny a nao achar borda onde nao tem.
        GaussianBlur(gray, blurred, Size(3, 3), 1.5, 1.5);

        // 5. O MÁGICO: Canny Edge Detector
        // Os números 50 e 150 sao os limiares (thresholds). 
        // Se diminuir, acha MAIS bordas (fica mais poluído).
        // Se aumentar, acha MENOS bordas (so as mais fortes).
        Canny(blurred, edges, 50, 150);

        // --- MOSTRAR RESULTADOS ---

        imshow("Sua Webcam Original", frame);      // Mostra a original colorida
        imshow("Efeito Desenho (Canny)", edges);   // Mostra o desenho neon

        // 6. Espera 30ms e fecha se apertar ESC (tecla 27)
        if (waitKey(30) == 27) break;
    }

    return 0;
}