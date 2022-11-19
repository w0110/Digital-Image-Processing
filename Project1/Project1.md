# Project 1 - 基本影像處理

## 讀取影像 imread

```cpp=
Mat image;
image = imread(argv[1], IMREAD_COLOR);
```
將影像讀進cv::Mat陣列內
IMREAD_COLOR表示以彩色圖片讀取 Try: 改成IMREAD_GRAYSCALE

## 寫入影像 imwrite

```cpp=
imwrite("test.jpg", image);
```
將image內容存到test.jpg中

## 開啟新影像

### 方法一

用constructor
```cpp=
Mat outImage1(Size(320,240),CV_8UC3);
```

### 方法二

用create函數
```cpp=
Mat outImage2;
outImage2.create(500, 500, CV_8UC3);
```

後面放的是(長,寬)
CV_8UC3 表示開啟的圖檔為8bit Unsigned, Channel=3

## 寫入圖檔

### 方法一

```cpp=
Image.at<Vec3b>(j,i)[0] = 255;
```

將(i,j)這個pixel(注意ij順序!)的第0個channel值設成255

### 方法二

```cpp=
Image.data[(j * 500 + i) * 3 + 0] = 0;
```

直接取image資料部分，當成陣列處理

## 快速寫入

使用memory copy

```cpp=
unsigned short array[500][100][3] = { 0 };
memcpy(&(outImage3.data[(100 * 500 + 0) * 3]), array, sizeof(array));
```

直接把指定記憶體複製過去
注意長寬 & 資料大小!!

## 複製圖片

### 真正複製

```cpp=
Mat outImage3 = outImage2.clone();
```
用.clone()才是真正複製內容

### 指向同一記憶體位置

```cpp=
Mat outImage3 = outImage2;
```
Mat是一個class，所以如果用= 只會把address複製過去
->outImage3跟outImage2其實指向同一個記憶體區塊(同一張圖)

## Request 

1. 讀取一張自己的自拍照，並輸入一個範圍(x,y,w,h)
2. 將影像中從(x,y)開始，到(x+w,y+h)範圍的影像挖出來，輸出到另外一張圖上

Ex: 讀取自拍照，並輸入327 124 241 117
![](https://i.imgur.com/E39mBDH.png)

## Code

[Source.cpp](https://github.com/w0110/Digital-Image-Processing/blob/master/Project1/Project1/Source.cpp)

## Result

## Reflection
Visual Studio 好難裝ಠ_ಠ
裝完還一堆路徑要加 (心好累¬_¬