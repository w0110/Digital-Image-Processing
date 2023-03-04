# Project4 - Canny Edge Detection / Hough Transform

## Canny Edge Detection

* 開始前先做Gaussian Blur! (模糊化濾掉高頻/雜訊/細節)
* 計算梯度用Sobel/Pewitt/Scharr(注意梯度包含量值和方向性)、M值計算用平方和開根號或是絕對值都可以
* Non-Maximum Suppression 只分成四個方向(上下、左右、正45度、負45度)，只保留同方向上連續點中的最大值。不要去砍到不連續的地方喔!
* 雙門檻值可以自己訂，建議高低門檻為2:1或3:1。

## Hough Transform

* 可以隨機減少點的數量以加快計算速度。(會形成線的點，在畫面中一定超級多)
* 投票的時候記得附近ϴρ都要投，不要只投給剛剛好的ϴρ。(取樣問題/誤差問題)

## Request

* 利用OpenCV寫出上課教的邊緣偵測: Canny Edge Detection 與 線段偵測: Hough Transform
* 在輸出的圖片右下角加上屬於自己的簽名(利用圖檔)

![](https://i.imgur.com/6ffAYX9.png)

### 嚴禁抄襲

### Canny Edge Detection: 50%
(優惠：使用OpenCV函數 20分)

* 計算M(x,y) 
* Non-Maximum Suppression
* 雙門檻和連通成份連接斷掉的邊界

### Hough Transform: 70%
(優惠：使用OpenCV函數 20分)

* 將 xy 座標影像轉換至ϴρ 座標並繪出
* 完成Hough Transform畫出線段圖

### 去背簽名檔: 10%

## Code

[Source.cpp](https://github.com/w0110/Digital-Image-Processing/blob/master/Project4/Project4/Source.cpp)

## Result

### 1st: Using [building.png](https://github.com/w0110/Digital-Image-Processing/blob/master/Project4/x64/Debug/building.png)

* 原始圖檔

![](https://i.imgur.com/zuiWZ0e.png)

* 原始簽名圖檔

![](https://i.imgur.com/51mYAEM.png)

* Canny Edge Detection

![](https://i.imgur.com/vPMWF3J.png)

* Hough Transform

![](https://i.imgur.com/EJMVSYW.png)

* 加上簽名後結果

![](https://i.imgur.com/dCAs4NN.png)

* Vote result

![](https://i.imgur.com/267zS09.png)

### 2nd: Using [test.jpg](https://github.com/w0110/Digital-Image-Processing/blob/master/Project4/x64/Debug/test.jpg) (Demo 時老師給的測資)

* 原始圖檔

![](https://i.imgur.com/jNyBz1N.png)

* 原始簽名圖檔

![](https://i.imgur.com/qyUdPga.png)

* Canny Edge Detection

![](https://i.imgur.com/FOUiB7z.png)

* Hough Transform

![](https://i.imgur.com/UJyxx8D.png)

* 加上簽名後結果

![](https://i.imgur.com/NiEPG65.png)

* Vote result

![](https://i.imgur.com/TbToHMb.png)

## Reflection

這次的作業好難啊啊啊啊啊~~
原本兩個都想實做練習，但根本做不出來ＱＱ
最後時間不足只能實做出Hough Transform

中間由xy轉rho theta就卡了好幾天，後面好不容易成功要畫線的時候又卡了好幾天，最後發現是自己在耍蠢，弧度跟角度分不清＝＝