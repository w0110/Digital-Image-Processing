#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <cmath>
using namespace cv;
using namespace std;

int main() {
    Mat image;
    Mat signature;

    // Read the file
    image = imread("GJ.jpg", IMREAD_COLOR);
    //signature = imread("signature.png", IMREAD_GRAYSCALE);
    if (image.empty()) { // Check for invalid input 
        cout << "Could not open or find the image" << endl;
        return -1;
    }

    // output1: nearest neighbor
    /*Mat nearestNeighbor;
    nearestNeighbor.create(image.rows * 3, image.cols * 3, CV_8UC3);

    for (int i = 0; i < image.rows; i++) {
        for (int j = 0; j < image.cols; j++) {
            for (int k = 0; k < 3; k++) {
                for (int m = 0; m < 3; m++) {
                    nearestNeighbor.at<Vec3b>((i*3 + k), (j*3 + m))[0] = image.at<Vec3b>(i, j)[0];
                    nearestNeighbor.at<Vec3b>((i*3 + k), (j*3 + m))[1] = image.at<Vec3b>(i, j)[1];
                    nearestNeighbor.at<Vec3b>((i*3 + k), (j*3 + m))[2] = image.at<Vec3b>(i, j)[2];
                }
            }
        }
    }
    imwrite("nearestNeighbor.jpg", nearestNeighbor);


    // output2: linear interpolation
    Mat linearInterpolation;
    linearInterpolation.create(image.rows * 3, image.cols * 3, CV_8UC3);
    Mat tmp1;
    tmp1.create(image.rows + 1, image.cols + 1, CV_8UC3);

    // to zero(right and bottom)
    for (int i = 0; i < image.rows + 1; i++) {
        for (int j = 0; j < image.cols + 1; j++) {
            if (j == (image.cols) || i == (image.rows)) {
                tmp1.at<Vec3b>(i, j) = 0;
            }
            else {
                tmp1.at<Vec3b>(i, j) = image.at<Vec3b>(i, j);
            }
        }
    }

    // do linear interpolation
    for (double i = 0; i < linearInterpolation.rows; i++) {
        for (double j = 0; j < linearInterpolation.cols; j++) {
            linearInterpolation.at<Vec3b>(i, j) = ((tmp1.at<Vec3b>(ceil(i / 3), ceil(j / 3)) - tmp1.at<Vec3b>(floor(i / 3), floor(j / 3))) 
                                                  * sqrt(pow(i / 3 - floor(i / 3), 2) + pow(j / 3 - floor(j / 3), 2)) 
                                                  / sqrt(pow(ceil(i / 3) - floor(i / 3), 2) + pow(ceil(j / 3) - floor(j / 3), 2))) 
                                                  + tmp1.at<Vec3b>(floor(i / 3), floor(j / 3));
        }
    }
    imwrite("linearInterpolation.jpg", linearInterpolation);*/


    // output3: gray image
    Mat gray;
    gray.create(image.rows, image.cols, CV_8UC1);

    for (int i = 0; i < image.rows; i++) {
        for (int j = 0; j < image.cols; j++) {
            // gray = b * 0.1 +  g * 0.6 + r * 0.3
            gray.at<uchar>(i, j) = image.at<Vec3b>(i, j)[0] * 0.1 + image.at<Vec3b>(i, j)[1] * 0.6 + image.at<Vec3b>(i, j)[2] * 0.3;
            if (gray.at<uchar>(i, j) > 135) {
                gray.at<uchar>(i, j) = 255;
            }
            else {
                gray.at<uchar>(i, j) = 0;
            }
        }
    }
    imwrite("GJGray.jpg", gray);

    // output4: 3 X 3 average filter (using output3)
    Mat averageFilter;
    Mat tmp;
    tmp.create(gray.rows + 2, gray.cols + 2, CV_8UC1);
    averageFilter.create(gray.rows, gray.cols, CV_8UC1);

    // to zero
    for (int i = 0; i < gray.rows + 2; i++) {
        for (int j = 0; j < gray.cols + 2; j++) {
            if (j == 0 || j == (gray.cols + 1) || i == 0 || i == (gray.rows + 1)) {
                tmp.at<uchar>(i, j) = 0;
            }
            else {
                tmp.at<uchar>(i, j) = gray.at<uchar>(i - 1, j - 1);
            }
        }
    }

    // using 3 X 3 average filter
    for (int i = 1; i <= gray.rows; i++) {
        for (int j = 1; j <= gray.cols; j++) {
            averageFilter.at<uchar>(i - 1, j - 1) = (tmp.at<uchar>(i - 1, j - 1) + tmp.at<uchar>(i - 1, j) + tmp.at<uchar>(i - 1, j + 1) +
                tmp.at<uchar>(i, j - 1) + tmp.at<uchar>(i, j) + tmp.at<uchar>(i, j + 1) +
                tmp.at<uchar>(i + 1, j - 1) + tmp.at<uchar>(i + 1, j) + tmp.at<uchar>(i + 1, j + 1)) / 9;
        }
    }
    imwrite("GJaverage filter.jpg", averageFilter);


    // output5: add my signature (using output4)
    //Mat addSignature;
    //addSignature.create(image.rows, image.cols, CV_8UC1);
    //for (int i = 0; i < image.rows; i++) {
    //    for (int j = 0; j < image.cols; j++) {
    //        if (i >= image.rows - signature.rows && i < image.rows && j >= image.cols - signature.cols && j < image.cols && signature.at<uchar>(i - image.rows + signature.rows, j - image.cols + signature.cols) == 0) {
    //            addSignature.at<uchar>(i, j) = signature.at<uchar>(i - image.rows + signature.rows, j - image.cols + signature.cols);
    //        }
    //        else {
    //            addSignature.at<uchar>(i, j) = averageFilter.at<uchar>(i, j);;
    //        }
    //        
    //    }
    //}
    //imwrite("add my signature.jpg", addSignature);


     // output
    namedWindow("Original window", WINDOW_AUTOSIZE);
    imshow("Original window", image);
    //namedWindow("Original signature window", WINDOW_AUTOSIZE);
    //imshow("Original signature window", signature);
    //namedWindow("Nearest Neighbor output window", WINDOW_AUTOSIZE);
    //imshow("Nearest Neighbor output window", nearestNeighbor);
    //namedWindow("Linear Interpolation output window", WINDOW_AUTOSIZE); 
    //imshow("Linear Interpolation output window", linearInterpolation);
    namedWindow("Gray Image output window", WINDOW_AUTOSIZE);
    imshow("Gray Image output window", gray);
    namedWindow("Average Filter output window", WINDOW_AUTOSIZE);
    imshow("Average Filter output window", averageFilter);
    //namedWindow("Add Signature output window", WINDOW_AUTOSIZE);     
    //imshow("Add Signature output window", addSignature);

    waitKey(0); 
    destroyAllWindows(); 
    return 0;
}
