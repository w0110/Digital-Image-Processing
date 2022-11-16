#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include<opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace cv;
using namespace std;

int main() {
    
    Mat image;
    Mat his = Mat::zeros(512, 512, CV_8UC1);
    Mat mCumu = Mat::zeros(512, 512, CV_8UC1);
    Mat after = Mat::zeros(512, 512, CV_8UC1);

    int total = 0;

    /* !!!!! GRAY ONE !!!!!*/
    // Read the file

    //image = imread("lena.jpg", IMREAD_GRAYSCALE);
    image = imread("TPE101.png", IMREAD_GRAYSCALE);
    Mat histogramEqualization = Mat::zeros(image.rows, image.cols, CV_8UC1);

    if (image.empty()) { // Check for invalid input 
        cout << "Could not open or find the image" << endl;
        return -1;
    }

    // count histogram
    int count[256] = { 0 };

    for (int i = 0; i < image.rows; i++) {
        for (int j = 0; j < image.cols; j++) {
            count[image.at<uchar>(i, j)]++;
        }
    }

    // count cumulative 
    int cumu[256] = { 0 };

    for (int i = 0; i < 256; i++) {
        total = total + count[i];
        cumu[i] = total;
    }

    for (int i = 0; i < 256; i++) {
        line(his, Point(i * 2, 513), Point(i * 2, 513 - count[i] * 0.01), Scalar(255, 255, 255), 1, LINE_4);
        line(his, Point(i * 2 + 1, 513), Point(i * 2 + 1, 513 - count[i] * 0.01), Scalar(255, 255, 255), 1, LINE_4);
        line(mCumu, Point(i * 2, 513), Point(i * 2, 513 - cumu[i] * 0.00065), Scalar(255, 255, 255), 1, LINE_4);
        line(mCumu, Point(i * 2 + 1, 513), Point(i * 2 + 1, 513 - cumu[i] * 0.00065), Scalar(255, 255, 255), 1, LINE_4);
    }

    // do Histogram Equalization
    for (int i = 0; i < 256; i++) {
        double ppp = cumu[i] * 256 / total;

        line(after, Point(ppp * 2, 513), Point(ppp * 2, 513 - count[i] * 0.01), Scalar(255, 255, 255), 1, LINE_4);
        line(after, Point(ppp * 2 + 1, 513), Point(ppp * 2 + 1, 513 - count[i] * 0.01), Scalar(255, 255, 255), 1, LINE_4);
    }

    for (int i = 0; i < image.rows; i++) {
        for (int j = 0; j < image.cols; j++) {
            histogramEqualization.at<uchar>(i, j) = cumu[image.at<uchar>(i, j)] * 256 / total;
        }
    }

    /* ~~~~~ COLOR ONE ~~~~~*/
    Mat cImage;

    // read image
    //cImage = imread("lena.jpg");
    cImage = imread("TPE101.png");
    if (cImage.empty()) { // Check for invalid input 
        cout << "Could not open or find the image" << endl;
        return -1;
    }

    namedWindow("Original color window", WINDOW_AUTOSIZE);
    imshow("Original color window", cImage);

    // count histogram
    int cCount[3][256] = { 0 };

    for (int i = 0; i < cImage.rows; i++) {
        for (int j = 0; j < cImage.cols; j++) {
            cCount[0][cImage.at<Vec3b>(i, j)[0]]++;
            cCount[1][cImage.at<Vec3b>(i, j)[1]]++;
            cCount[2][cImage.at<Vec3b>(i, j)[2]]++;
        }
    }

    // count cumulative 
    int cCumu[3][256] = { 0 };
    int red = 0, green = 0, blue = 0;

    for (int i = 0; i < 256; i++) {
        blue = blue + cCount[0][i];
        cCumu[0][i] = blue;
        green = green + cCount[1][i];
        cCumu[1][i] = green;
        red = red + cCount[2][i];
        cCumu[2][i] = red;
    }

    Mat redHis = Mat::zeros(512, 512, CV_8UC1);
    Mat greenHis = Mat::zeros(512, 512, CV_8UC1);
    Mat blueHis = Mat::zeros(512, 512, CV_8UC1);
    Mat redAfter = Mat::zeros(512, 512, CV_8UC1);
    Mat greenAfter = Mat::zeros(512, 512, CV_8UC1);
    Mat blueAfter = Mat::zeros(512, 512, CV_8UC1);

    //Mat redAfter, greenAfter, blueAfter;
    Mat cHistogramEqualization;
    cHistogramEqualization.create(cImage.rows, cImage.cols, CV_8UC3);

    for (int i = 0; i < 256; i++) {
        line(blueHis, Point(i * 2, 513), Point(i * 2, 513 - cCount[0][i] * 0.01), Scalar(255, 255, 255), 1, LINE_4);
        line(blueHis, Point(i * 2 + 1, 513), Point(i * 2 + 1, 513 - cCount[0][i] * 0.01), Scalar(255, 255, 255), 1, LINE_4);
        line(greenHis, Point(i * 2, 513), Point(i * 2, 513 - cCount[1][i] * 0.01), Scalar(255, 255, 255), 1, LINE_4);
        line(greenHis, Point(i * 2 + 1, 513), Point(i * 2 + 1, 513 - cCount[1][i] * 0.01), Scalar(255, 255, 255), 1, LINE_4);
        line(redHis, Point(i * 2, 513), Point(i * 2, 513 - cCount[2][i] * 0.01), Scalar(255, 255, 255), 1, LINE_4);
        line(redHis, Point(i * 2 + 1, 513), Point(i * 2 + 1, 513 - cCount[2][i] * 0.01), Scalar(255, 255, 255), 1, LINE_4);
    }

    namedWindow("red count", WINDOW_AUTOSIZE);
    imshow("red count", redHis);
    namedWindow("green count", WINDOW_AUTOSIZE);
    imshow("green count", greenHis);
    namedWindow("blue count", WINDOW_AUTOSIZE);
    imshow("blue count", blueHis);

    // do Histogram Equalization
    for (int i = 0; i < 256; i++) {
        double r = cCumu[2][i] * 256 / red;
        double g = cCumu[1][i] * 256 / green;
        double b = cCumu[0][i] * 256 / blue;
        line(redAfter, Point(r * 2, 513), Point(r * 2, 513 - cCount[2][i] * 0.01), Scalar(255, 255, 255), 1, LINE_4);
        line(redAfter, Point(r * 2 + 1, 513), Point(r * 2 + 1, 513 - cCount[2][i] * 0.01), Scalar(255, 255, 255), 1, LINE_4);
        line(greenAfter, Point(g * 2, 513), Point(g * 2, 513 - cCount[1][i] * 0.01), Scalar(255, 255, 255), 1, LINE_4);
        line(greenAfter, Point(g * 2 + 1, 513), Point(g * 2 + 1, 513 - cCount[1][i] * 0.01), Scalar(255, 255, 255), 1, LINE_4);
        line(blueAfter, Point(b * 2, 513), Point(b * 2, 513 - cCount[0][i] * 0.01), Scalar(255, 255, 255), 1, LINE_4);
        line(blueAfter, Point(b * 2 + 1, 513), Point(b * 2 + 1, 513 - cCount[0][i] * 0.01), Scalar(255, 255, 255), 1, LINE_4);
    }

    namedWindow("red after", WINDOW_AUTOSIZE);
    imshow("red after", redAfter);
    namedWindow("green after", WINDOW_AUTOSIZE);
    imshow("green after", greenAfter);
    namedWindow("blue after", WINDOW_AUTOSIZE);
    imshow("blue after", blueAfter);

    for (int i = 0; i < cImage.rows; i++) {
        for (int j = 0; j < cImage.cols; j++) {
            cHistogramEqualization.at<Vec3b>(i, j)[0] = cCumu[0][cImage.at<Vec3b>(i, j)[0]] * 256 / blue;
            cHistogramEqualization.at<Vec3b>(i, j)[1] = cCumu[1][cImage.at<Vec3b>(i, j)[1]] * 256 / green;
            cHistogramEqualization.at<Vec3b>(i, j)[2] = cCumu[2][cImage.at<Vec3b>(i, j)[2]] * 256 / red;
        }
    }
    namedWindow("color histogramEqualization", WINDOW_AUTOSIZE);
    imshow("color histogramEqualization", cHistogramEqualization);

    // output 
    namedWindow("Original window", WINDOW_AUTOSIZE);
    imshow("Original window", image);
    namedWindow("count", WINDOW_AUTOSIZE);
    imshow("count", his);
    namedWindow("cumu", WINDOW_AUTOSIZE);
    imshow("cumu", mCumu);
    namedWindow("histogramEqualization", WINDOW_AUTOSIZE);
    imshow("histogramEqualization", histogramEqualization);
    namedWindow("after", WINDOW_AUTOSIZE);
    imshow("after", after);

    waitKey(0);
    destroyAllWindows();
    return 0;
}
