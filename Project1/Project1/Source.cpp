#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main() {
    Mat image;
    int x, y;
    int w, h;

    // Read the file
    image = imread("anya.jpg", IMREAD_COLOR);
    if (image.empty()) { // Check for invalid input 
        cout << "Could not open or find the image" << std::endl;
        return -1;
    }

    // Read value
    cout << "長寬為" << image.cols << ", " << image.rows << endl;
    cout << "請輸入要擷取的範圍起始點(x, y): " << endl;
    cin >> y >> x;
    cout << "請輸入要擷取的範圍起長寬(h, w): " << endl;
    cin >> h >> w;

    //用函式(練習)
    //Rect rect(x, y, w, h);  
    //Mat temp(image, rect);

    Mat output;
    output.create(w, h, CV_8UC3);
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            output.at<Vec3b>(i, j)[0] = image.at<Vec3b>(x + i, y + j)[0];
            output.at<Vec3b>(i, j)[1] = image.at<Vec3b>(x + i, y + j)[1];
            output.at<Vec3b>(i, j)[2] = image.at<Vec3b>(x + i, y + j)[2];
        }
    }

    // output
    namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.
    imshow("Display window", image); // Show our image inside it.
    namedWindow("Output window", WINDOW_AUTOSIZE);
    imshow("Output window", output);

    waitKey(0); // Wait for a keystroke in the window
    destroyAllWindows(); // Close all windows
    return 0;
}
