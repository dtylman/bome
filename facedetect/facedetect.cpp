#include "opencv2/objdetect.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

//Rect cropBy(const Rect& rect, float factor) {
//    int w =  rect.width * factor / 2;
//    int h =  rect.height * factor  / 2 ;
//    return Rect(rect.x+w,rect.y+h,rect.width-w, rect.height-h);
//}

void detectAndDraw(Mat& img, CascadeClassifier& cascade, double scale, bool tryflip) {
    double t = 0;
    vector<Rect> faces, faces2;
    const static Scalar colors[] = {
        Scalar(255, 0, 0),
        Scalar(255, 128, 0),
        Scalar(255, 255, 0),
        Scalar(0, 255, 0),
        Scalar(0, 128, 255),
        Scalar(0, 255, 255),
        Scalar(0, 0, 255),
        Scalar(255, 0, 255)
    };
    Mat gray, smallImg;

    cvtColor(img, gray, COLOR_BGR2GRAY);
    double fx = 1 / scale;
    resize(gray, smallImg, Size(), fx, fx, INTER_LINEAR);
    equalizeHist(smallImg, smallImg);

    t = (double) getTickCount();
    cascade.detectMultiScale(smallImg, faces,1.1, 2, 0
    //|CASCADE_FIND_BIGGEST_OBJECT
            //|CASCADE_DO_ROUGH_SEARCH
            | CASCADE_SCALE_IMAGE,
            Size(30, 30));
    if (tryflip) {
        flip(smallImg, smallImg, 1);
        cascade.detectMultiScale(smallImg, faces2,
                1.1, 2, 0
                //|CASCADE_FIND_BIGGEST_OBJECT
                //|CASCADE_DO_ROUGH_SEARCH
                | CASCADE_SCALE_IMAGE,
                Size(30, 30));
        for (vector<Rect>::const_iterator r = faces2.begin(); r != faces2.end(); ++r) {
            faces.push_back(Rect(smallImg.cols - r->x - r->width, r->y, r->width, r->height));
        }
    }
    t = (double) getTickCount() - t;
    printf("detection time = %g ms\n", t * 1000 / getTickFrequency());
    for (size_t i = 0; i < faces.size(); i++) {
        Mat faceImage = img(faces[i]);
        std::stringstream outName;
        outName << "face" << i << ".jpg";
        std::cout << outName.str() << std::endl;
        imwrite(outName.str().c_str(), faceImage);
    }
}

int main(int argc, const char** argv) {
    double scale = 1;
    CascadeClassifier cascade;
    if (!cascade.load("haarcascade_frontalface_alt.xml")) {
        cerr << "ERROR: Could not load classifier cascade" << endl;
        return -1;
    }

    while (true) {
        string fileName;
        std::getline(std::cin, fileName);
        Mat image = imread(fileName, 1);
        if (!image.empty()) {
            detectAndDraw(image, cascade, scale, false);
        }    
    }
    return 0;
}
