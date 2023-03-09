# Install OpenCV

## Prerequisite

### Download Visual Studio 
* 官網：[https://visualstudio.microsoft.com/zh-hant/downloads/](https://visualstudio.microsoft.com/zh-hant/downloads/)

* 2017 / 2019 / 2022

### Download OpenCV

* 官網：[https://opencv.org/releases/](https://opencv.org/releases/)
* 下載4.6.0
![](https://i.imgur.com/ad4Ng0u.png)
* 解壓縮並依習慣放到C:\或D:\

## Visual Studio setting

* 打開Visual Studio 2017/2019並開啟新專案
* 確認處於x64模式(將x86改成x64)
* ![](https://i.imgur.com/DqEVCyO.png)
* 選擇 專案->屬性

### 組態屬性->C/C++->一般->其他Include目錄

* 加入OpenCV所在資料夾\include\
![](https://i.imgur.com/ZrJX03s.png)

### 組態屬性->連結器->一般->其他程式庫目錄 

* 加入OpenCV所在資料夾\build\x64\vc15\lib
![](https://i.imgur.com/HdhEO8T.png)

### 組態屬性->連結器->輸入->其他相依性 

* 加入OpenCV所需要之library
    * 4.0後改叫做world: 包山包海
    * opencv_world(版本)(debug/release).lib
    * opencv_world460d.lib表示4.60版，debug版本的lib
![](https://i.imgur.com/KErQbjp.png)

### Runtime error: 少了dll檔??
* 到`\opencv\build\x64\vc15\bin`裡
* 複製`opencv_world460d.dll`
* 到專案資料夾`\Project\x64\Debug`貼上

![](https://i.imgur.com/xQHz7Kl.png)
