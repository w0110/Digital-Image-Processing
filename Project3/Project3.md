# Project3 - Histogram & Histogram Equalization

## Histogram 直方圖

* 將影像上的強度值統計的結果
![](https://i.imgur.com/DC3oo86.png)
![](https://i.imgur.com/AzSsZwb.png)
* 彩色影像直方圖
![](https://i.imgur.com/AhJg8Ij.jpg)

### 步驟

1. 讀取輸入影像(彩色 or 黑白)
2. 統計其顏色的分布(0-255)，如果是彩色圖則會有三個頻道(BGR)
3. 根據每個顏色強度的比例，繪製出直方圖(512*512, 或者自訂大小)

## Histogram Equalization 直方圖均化

當影像強度其中在某一區(偏亮/偏暗)時我們希望讓畫面中的顏色強度較平均，較可看出細節

Q：如何讓直方圖上每個強度的像素數量盡可能相等？

![](https://i.imgur.com/IPxNzTS.png)

A：找到一個好的對應函數，使直方圖接近一直線
先計算強度累積分布圖
一個好的直方圖分布->顏色平均分布在[0,255]->強度累積會成一直線
根據累積圖調整強度，使強度累積圖趨近成一直線

![](https://i.imgur.com/D5Zc1Z1.png)

:::info
Hint: 不可能做到完全直線，但盡可能讓每個不同強度的出現機率在每個位置均等
(考慮某個範圍內的強度數量)
:::

### 步驟

1. 累加每個強度出現的次數，得到強度累積分布表
2. 根據強度累積分布表，建立顏色的對照表
3. 調整強度的值使得顏色盡可能平均分布(累積分布表趨近於一直線)

## Request

### 功能 - 讀取任意影像，繪製出：

* 黑白影像直方圖
* 黑白影像直方圖均化
* 彩色影像直方圖(三張)
* 彩色影像直方圖分別均化並合併出結果

### 不可以使用現成的calHist和equalizeHist函數!!!

* 拿來debug確認結果倒是可以!
* 嚴禁抄襲!  (包含網路資源)

## Code

[Source.cpp](https://github.com/w0110/Digital-Image-Processing/blob/master/Project3/Project3/Source.cpp)

## Result

### 1st: using [lena.jpg](https://github.com/w0110/Digital-Image-Processing/blob/master/Project3/x64/Debug/lena.jpg)

| 黑白原圖 | 彩色原圖 | 
|---|---|
|![](https://i.imgur.com/Ek4s4EZ.png)|![](https://i.imgur.com/xJXEjW7.png)|
| 黑白影像合併結果 | 彩色影像合併結果 |
|![](https://i.imgur.com/dvAZflK.png)|![](https://i.imgur.com/tPR6how.png)|
| 黑白影像直方圖 | 黑白影像直方圖均化 |
|![](https://i.imgur.com/FeWpyat.png)|![](https://i.imgur.com/P4wd4Ir.png)|
| 彩色影像直方圖 R | 彩色影像直方圖分別均化 R |
|![](https://i.imgur.com/AX8foMF.png)|![](https://i.imgur.com/C7bQg55.png)|
| 彩色影像直方圖 G | 彩色影像直方圖分別均化 G |
|![](https://i.imgur.com/h0UTn20.png)|![](https://i.imgur.com/ZKlyW2B.png)|
| 彩色影像直方圖 B | 彩色影像直方圖分別均化 B |
|![](https://i.imgur.com/6mhhQxJ.png)|![](https://i.imgur.com/lRred5C.png)|

### 2nd: using [TPE101.png](https://github.com/w0110/Digital-Image-Processing/blob/master/Project3/x64/Debug/TPE101.png)

| 黑白原圖 | 彩色原圖 | 
|---|---|
|![](https://i.imgur.com/Yejds4s.png)|![](https://i.imgur.com/07knADb.png)|
| 黑白影像合併結果 | 彩色影像合併結果 |
|![](https://i.imgur.com/ZbpvArs.png)|![](https://i.imgur.com/5vj2d6Q.png)|
| 黑白影像直方圖 | 黑白影像直方圖均化 |
|![](https://i.imgur.com/7Jhbrqa.png)|![](https://i.imgur.com/6brCVzv.png)|
| 彩色影像直方圖 R | 彩色影像直方圖分別均化 R |
|![](https://i.imgur.com/6TtI4HR.png)|![](https://i.imgur.com/LE969rz.png)|
| 彩色影像直方圖 G | 彩色影像直方圖分別均化 G |
|![](https://i.imgur.com/ec7fTCG.png)|![](https://i.imgur.com/yAMTzOu.png)|
| 彩色影像直方圖 B | 彩色影像直方圖分別均化 B |
|![](https://i.imgur.com/IwGhtI8.png)|![](https://i.imgur.com/b7zUQO0.png)|

## Reflection

一開始因為不是很懂均一化什麼研究了好久，但後來發現他就是把每一種強度值移動移動一下而已！！(´⊙ω⊙\`)

BTW 雖然說對RGB通道做均一化色調會改變，但我覺得它的結果其實滿美的(๑¯∀¯๑)
