#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
using namespace std;
using namespace cv;

int** generateMat(const char* imagepath, int height, int width) {
    int** mat = new int* [height];
    for (int i = 0; i < height; i++)
        mat[i] = new int[width];

    Mat img = imread(imagepath);
    if (img.empty()) {
        cout << "Image is not successfully loaded!\n";
        return mat;
    }
    imshow("Image", img);

    int x = img.cols - 2 - (height - 1) - 12 * height - (height / 5 - 1),
        y = img.rows - 2 - (width - 1) - 12 * width - (width / 5 - 1) - 10;

    for (int x0 = x + 1, j0 = 0; j0 < width; x0 += 13, j0++)
        mat[0][j0] = ((int)img.at<Vec3b>(Point(x0, y + 1))[0] < 2) ? 1 : -1;

    for (int y0 = y + 1, i0 = 0; i0 < height; y0 += 13, i0++)
        mat[i0][0] = ((int)img.at<Vec3b>(Point(x + 1, y0))[0] < 2) ? 1 : -1;

    for (int j = 1; j < width; j++)
        for (int i = 1; i < height; i++)
            mat[i][j] = ((int)img.at<Vec3b>(Point(x + j * 13 + j / 5, y + i * 13 + i / 5))[0] < 2) ? 1 : -1;

    return mat;
}

int main()
{
    int height = 10, width = 10;
    int** matrix = generateMat("C:\\Users\\lasjp\\Downloads\\korablik3_12_1_1p.png", height, width);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
            if (matrix[i][j] == 1)
                cout << "+ ";
            else if (matrix[i][j] == -1)
                cout << "- ";
            else
                cout << matrix[i][j] << ' ';
        cout << endl;
    }
    return 0;
}