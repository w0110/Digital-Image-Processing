# Project 2 - 基本影像處理功能-線性內插/黑白化/Average Filter

## Request

利用OpenCV寫出幾個簡單的影像處理功能：
* 讀取彩色照片(建議600*600以內)後，依序進行以下步驟：
* 讀取原始照片，輸出”以最近鄰(nearest neighbor)內插”長寬放大3倍後的結果並存成檔案(輸出1)
* 讀取原始照片，輸出”以線性(Linear)內插”長寬放大3倍後的結果並存成檔案(輸出2)
* 讀取原始照片，轉成黑白並輸出(輸出3)
* 對(輸出3)使用average filter並輸出結果(輸出4)
* 在(輸出4) 右下角加上屬於自己的簽名(利用圖檔)(輸出5)

## 影像內插 (Interpolation)

### 線性內插 (linear interpolation)：考慮最近4個點

![](https://i.imgur.com/qFL4x32.png)

* $\tfrac{Y - A}{l} = \tfrac{B - A}{L}$

![](https://i.imgur.com/gp3zqBB.png)

1. $\frac{i - A}{w} = \frac{B - A}{W}$
2. $\frac{j -  C}{w} = \frac{D - C}{W}$
3. $\frac{Y - i}{h} = \frac{j - i}{H}$

## 轉黑白(Gray Image)

[References](https://en.wikipedia.org/wiki/Grayscale)

$Y = 0.299R + 0.587G + 0.114B$

=>  `Y = 0.3 * R + 0.6 * G + 0.1 * B`

### Average Filter 

3 * 3 filter: 

![](https://i.imgur.com/IAVS20C.png)

=> $\frac{1}{9}$: 正歸化為1
## Code 

[Source.cpp](https://github.com/w0110/Digital-Image-Processing/blob/master/Project2/Project2/Source.cpp)

## Result
* 原始圖檔

![](x64/Debug/me.png)

* 原始簽名圖檔

![](x64/Debug/signature.png)

* 經nearest neighbor放大三倍後結果

![](x64/Debug/nearestNeighbor.jpg)

* 經linear interpolation放大三倍後結果

![](x64/Debug/linearInterpolation.jpg)

* 轉黑白後結果

![](x64/Debug/gray.jpg)

* 經average filter後結果

![](x64/Debug/average%20filter.jpg)

* 加上簽名後結果

![](x64/Debug/add%20my%20signature.jpg)

## Reflection

取值不一定要從原圖去對應到結果圖上，也可以從結果圖對應到原圖上取算值應為多少！！(e.g. Average Filter)

終於不用在那邊研究原本的那一點要怎麼拆成四個點(~￣▽￣)~