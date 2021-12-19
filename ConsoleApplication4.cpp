#include <iostream>
#include <fstream>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/stitching.hpp"

using namespace std;
using namespace cv;

Stitcher::Mode mode = Stitcher::PANORAMA;

vector<Mat> imgs;

int main(int argc, char* argv[]) {
    for (int i = 1; i < argc; ++i) {

        Mat img = imread(argv[i]);

        if (img.empty()){
            cout << "Can't read image'" << argv[i] << "'\n";
            return -1;
        }
        imgs.push_back(img);
    }

    Mat pano;
    Ptr<Stitcher> stitcher = Stitcher::create(mode);

    Stitcher::Status status = stitcher->stitch(imgs, pano);

    if (status != Stitcher::OK) {
        cout << "Can't stitch images\n";
        return -1;
    }

    imwrite("result.jpg", pano);
    imshow("Result", pano);
    waitKey(0);

    return 0;
}
