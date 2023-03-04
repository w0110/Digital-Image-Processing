#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <cmath>
using namespace cv;
using namespace std;

#define PI 3.1415926
#define THETA 360
#define threshold 110

int main() {
    Mat src, image, signature;

    // Read the file
    src = imread("building.png", IMREAD_COLOR);
    // src = imread("test.jpg", IMREAD_COLOR);
    signature = imread("signature.png", IMREAD_COLOR);

    if (src.empty()) { // Check for invalid input
        cout << "Could not open or find the image" << endl;
        return -1;
    }

    // Transform Image to Gray Level
    cvtColor(src, image, COLOR_BGR2GRAY);

    // use Gaussian Blur to reduce image noise
    Mat image_blurred_with_3x3_kernel;
    GaussianBlur(image, image_blurred_with_3x3_kernel, Size(3, 3), 0);

    // use Canny edge detection to detedt the edges
    Mat canny;
    Canny(image_blurred_with_3x3_kernel, canny, 100, 200);

    // Hough Transform
    double rho;
    const int rhoMax = sqrt(pow(image.cols, 2) + pow(image.rows, 2));
    vector<vector<int>> votes(2 * rhoMax, vector<int>(THETA, 0));

    // 1. vote
    for (int i = 0; i < image.rows; i++) {
        for (int j = 0; j < image.cols; j++) {
            // not an edge
            if (canny.at<uchar>(i, j) == 0) {
                continue;
            }

            // randomly reduce node
            srand((unsigned)time(NULL));
            int r = rand();
            if (r < 0.3) {
                // reduce point
                continue;
            }

            // voting
            for (int theta = 0; theta < THETA; theta++) {
                rho = round(j * cos(theta * PI / 180) + i * sin(theta * PI / 180)) + rhoMax;
                votes[rho][theta]++;
            }
        }
    }

    // draw the voteing result
    Mat votesResult = Mat::zeros(rhoMax * 2, THETA, CV_8UC1);
    for (int i = 0; i < rhoMax * 2; i++) {
        for (int j = 0; j < THETA; j++) {
            votesResult.at<uchar>(i, j) = votes[i][j];
        }
    }

    // draw line
    Mat houghLine = src.clone();
    Point p1, p2;

    for (int i = 0; i < votes.size(); i++) {
        for (int j = 0; j < votes[0].size(); j++) {
            if (votes[i][j] > threshold) {

                double r = i - rhoMax;
                int theta = j;
                Point p1, p2;
                int x0 = cvRound(r * cos(theta * PI / 180));
                int y0 = cvRound(r * sin(theta * PI / 180));

                p1.x = cvRound(x0 + rhoMax * (-sin(theta * PI / 180)));
                p1.y = cvRound(y0 + rhoMax * (cos(theta * PI / 180)));
                p2.x = cvRound(x0 - rhoMax * (-sin(theta * PI / 180)));
                p2.y = cvRound(y0 - rhoMax * (cos(theta * PI / 180)));

                line(houghLine, p1, p2, Scalar(255, 255, 0), 2, LINE_AA);
            }
        }
    }

    // Add signature
    Mat addSignature = houghLine.clone();

    for (int i = 0; i < signature.rows; i++) {
        for (int j = 0; j < signature.cols; j++) {
            if (signature.at<Vec3b>(i, j)[0] == 0 && signature.at<Vec3b>(i, j)[1] == 0 && signature.at<Vec3b>(i, j)[2] == 0) {
                int l = image.rows - signature.rows - 10;
                int h = image.cols - signature.cols - 10;

                addSignature.at<Vec3b>(l + i, h + j)[0] = 0;
                addSignature.at<Vec3b>(l + i, h + j)[1] = 255;
                addSignature.at<Vec3b>(l + i, h + j)[2] = 255;
            }
        }
    }

    // output
    namedWindow("Source image", WINDOW_AUTOSIZE);
    imshow("Source image", src);
    namedWindow("Source name", WINDOW_AUTOSIZE);
    imshow("Source name", signature);
    namedWindow("Canny", WINDOW_AUTOSIZE);
    imshow("Canny", canny);
    namedWindow("votesResult", WINDOW_AUTOSIZE);
    imshow("votesResult", votesResult);
    namedWindow("houghLine", WINDOW_AUTOSIZE);
    imshow("houghLine", houghLine);
    namedWindow("addSignature", WINDOW_AUTOSIZE);
    imshow("addSignature", addSignature);

    waitKey(0); // Wait for a keystroke in the window
    destroyAllWindows(); // Close all windows
    return 0;
}
