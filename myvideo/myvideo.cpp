//myvideo.cpp
//
 
 // Este archivo abrirá el archivo de video dado y pasará la imagen a ORB-SLAM2 para su posicionamiento
 
 // necesita opencv
#include <opencv2/opencv.hpp>
 
 // Interfaz del sistema ORB-SLAM
#include "System.h"
 
#include <string>
#include <chrono>   // for time stamp
#include <iostream>
 
using namespace std;
 //using namespace std int main|
 // Archivo de parámetros y archivo de diccionario
 // Si la ruta en su sistema es diferente, modifíquela
string parameterFile = "/home/yerson/Dev/ORB_SLAM2/Examples/Monocular/TUM1.yaml";
string vocFile = "/home/yerson/Dev/ORB_SLAM2/Vocabulary/ORBvoc.txt";
 
 // archivo de vídeo
string videoFile = "/home/yerson/Dev/ORB_SLAM2/Examples/myvideo/myvideo.mp4";
 
int main(int argc, char **argv) {
 
         // Declarar el sistema ORB-SLAM2
    ORB_SLAM2::System SLAM(vocFile, parameterFile, ORB_SLAM2::System::MONOCULAR, true);
 
         // Obtener imagen de video
    cv::VideoCapture cap(-1);    // change to 1 if you want to use USB camera.
    //cv::VideoCapture cap(videoFile);
         // Registrar el tiempo del sistema
    auto start = chrono::system_clock::now();
 
    while (1) {
        cv::Mat frame;
                 cap >> frame; // leer datos de la cámara
        if ( frame.data == nullptr )
            break;
 
        // rescale because image is too large
        cv::Mat frame_resized;
        cv::resize(frame, frame_resized, cv::Size(640,360));
 
        auto now = chrono::system_clock::now();
        auto timestamp = chrono::duration_cast<chrono::milliseconds>(now - start);
        SLAM.TrackMonocular(frame_resized, double(timestamp.count())/1000.0);
        //cv::waitKey(30);
    }
 
    SLAM.Shutdown();
    return 0;
}
