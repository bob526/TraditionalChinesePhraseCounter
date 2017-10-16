# 正體中文詞彙計數
## Traditional Chinese Phrase Counter

## 簡介
一個可以數文章中中文字詞的出現數量的程式。本程式讀取完文章以後，會直接跳3個byte，去讀取下一個中文字，
跑完所有的句子以後，會在標準輸出上印出統計資料，並且最常出現的字詞排序在最上方。這裡所定義的「字詞」，
指的是長度介於二到七個中文字的詞彙。  
編譯要求：C++11  
使用到的東西：unordered_map和ngram  
文章要求：UTF-8的中文文章

## 潛在Bug
中英文混雜的情況下，計算的數量會出錯，這是因為讀取文字的時候，都是直接跳3個byte，但是當文章中英文混雜的時候，
英文只佔了1 byte，所以會出錯。

## 手動字典檔前處理
1. 請先去[教育部國語辭典公眾授權網][1]手動下載《重編國語辭典 修訂本》的「資料下載」的東西。 
2. 開啟下載好的xls檔案
3. 只留下「直行C」，其他的手動刪除
4. 轉存為csv格式的檔案
第一個切出來的csv檔案，其內容應該如下：
```
字詞名
八
扒
叭
巴
吧
芭
疤
羓
粑
笆
豝
鈀
捌
拔
茇
胈
軷
菝
跋
.
.
.
```
**開頭的「字詞名」會被程式處理掉，所以沒關係**

## 準備你的中文文獻
### 如果你有自己的文章
則直接使用該文章作為輸入文章即可，記得要確保文章是**UTF-8編碼**
### 本範例使用之測試文章
測試文章來自維基百科。  
1. 請先到 [中文維基百科資料庫下載頁][2]
2. 依據你的需求選擇適當的備份資料（確保是xml即可）
3. 請下載由attardi所做的 [wikiextractor][3] （這是GitHub連結）  
如果是在Linux上工作，建議就直接在命令列下git指令即可：  
`git clone https://github.com/attardi/wikiextractor.git`
4. 使用 [wikiextractor][3] 把維基百科的備份檔轉為純文字  
命令列指令：  
`python WikiExtractor.py -o OutputDirName InputWikiXmlFile`

## 編譯本程式
本程式有makefile，所以可以直接在命令列打下指令`make`  
以下列出makefile的內容：  
```
all: create_dict.cpp article_analysis.cpp
	g++ -Wall -Wextra -std=c++11 -o create_dict.run create_dict.cpp
	g++ -Wall -Wextra -std=c++11 -o article_analize.run article_analysis.cpp

create_dict.cpp: create_dict.cpp
	g++ -Wall -Wextra -std=c++11 -o create_dict.run create_dict.cpp

article_analysis.cpp: article_analysis.cpp
	g++ -Wall -Wextra -std=c++11 -o article_analize.run article_analysis.cpp
```

## 使用本程式
### create_dict.run - 產生字典檔的程式
**如果你已經有自己的字典檔，則無須使用本程式**  
*會有這個程式，是為了把《重編國語辭典 修訂本》的「資料下載」的東西整合成為單一一個csv字典檔*
本程式會擷取長度二到七個字的中文詞，避免出現單字計算的問題。
#### 參數格式、解釋
```
./create_dict.run InputPhraseFile OutputDictionaryFile [rewrite]
./create_dict.run InputPhraseFile OutputDictionaryFile [append]
Default is rewrite mode
```
#### InputPhraseFile
從《重編國語辭典 修訂本》的「資料下載」中分出來的csv檔案，以下是我的分割檔的大小和命名，大小應該會差不多，但名稱可以隨便取。
```
-rw-rw-r-- 1 nari nari 508K 10月  1 09:55 dict_revised_2015_20160523_1.csv
-rw-rw-r-- 1 nari nari 552K 10月  1 11:29 dict_revised_2015_20160523_2.csv
-rw-rw-r-- 1 nari nari 437K 10月  1 11:38 dict_revised_2015_20160523_3.csv
```
#### OutputDictionaryFile
輸出的字詞檔的名稱。副檔名不拘，只要能夠讓程式能夠讀取即可。
#### rewrite
預設的模式，會把OutputDictionaryFile覆蓋過去，常用於測試的時候。
#### append
當要把兩個字典檔處理好的東西串接在一起時使用。
#### 使用範例
```
./create_dict.run dict_revised_2015_20160523_1.csv mydictionary.csv 
# Next command
./create_dict.run dict_revised_2015_20160523_2.csv mydictionary.csv append
# Next command
./create_dict.run dict_revised_2015_20160523_3.csv mydictionary.csv append
```
這樣跑完以後，`mydictionary.csv`就會有《重編國語辭典 修訂本》裡面的字詞。

### article_analize.run - 分析文章中文字詞出現次數的程式
**主要的程式，單執行緒，比較花時間**
#### 參數格式、解釋
```
./article_analize.run YourArticle
```
#### YourArticle
你想要計算字詞出現次數的文章，要是UTF-8編碼。
#### 使用範例
```
./article_analize.run article1.txt 
```
#### 花費時間測試
##### 系統資訊
OS: Ubuntu 16.04  
CPU: Intel Xeon E3-1231v3  
RAM: 8G  
##### article1.txt 97MB
||第一次測試|第二次測試|第三次測試|第四次測試|第五次測試|
|---|---|---|---|---|---|
|**時間**|35.530 s|35.349 s|35.223 s|34.073 s|44.797 s|
##### article2.txt 97MB
||第一次測試|第二次測試|第三次測試|第四次測試|第五次測試|
|---|---|---|---|---|---|
|**時間**|33.897 s|34.148 s|33.811 s|33.615 s|35.053 s|
##### article3.txt 95MB
||第一次測試|第二次測試|第三次測試|第四次測試|第五次測試|
|---|---|---|---|---|---|
|**時間**|33.300 s|33.085 s|33.442 s|32.972 s|33.103 s|
##### full_article.txt 288MB
||第一次測試|第二次測試|第三次測試|第四次測試|第五次測試|
|---|---|---|---|---|---|
|**時間**|1 m 41.606 s|1 m 41.212 s|1 m 42.189 s|1 m 41.557 s|1 m 41.878 s|

## 網頁界面
### 伺服器需求
**PHP**
### 使用技術
HTML  
CSS    
AJAX(Native version)(Not JQuery version)  
PHP
### 界面介紹 
![ㄧ開始的界面][4]
#### 左上方文字區域
為不可修改的文字區域，本來是想要嘗試看看能不能使用者自己輸入文字、文章，作為參數傳過去，不過我卡在要怎麼把寫在HTML裡面的文字，傳給php後，再讓php儲存成檔案，因為我的C++程式，是吃純文字檔案的。
![範例文章出現在左上角][5]
#### 右上方文字區域
為可修改的文字區域，不過修改了也沒有什麼效果。這個區塊的文字區域是拿來顯示文章詞彙的統計結果。沒有實做特效。
#### 下方選項區域
有選項可以讓使用者選擇輸入的文章。選擇以後，會在左上方的文字區域顯示出來(按下去以後，即時更新，更新的速度會依據伺服器負擔，使用者的網速而不同)。再下面一區，是送出的按鈕，按下去就會把選項中的文章(左上角文字區域裡面的內容)，送給伺服器裡面的C++執行檔去跑，最後會把結果輸出在右上角的文字區域中。
#### 限制
由於使用者體驗和回饋性有很大的關聯，如果把網頁界面的輸入文章，放上上面做計時的97MB的文章，會卡很久，所以網頁界面的輸入文章，是1MB的小檔案，可以比較迅速的有回應。
#### 完整跑完的樣子
![完整跑完程式][6]


[1]: http://resources.publicense.moe.edu.tw/index.html "教育部國語辭典公眾授權網"
[2]: https://dumps.wikimedia.org/zhwiki/ "中文維基百科資料庫下載-選擇時間的頁面"
[3]: https://github.com/attardi/wikiextractor "把維基百科的文獻轉成純文字的工具"
[4]: https://i.imgur.com/Ds3avLd.png
[5]: https://i.imgur.com/9fiHYxX.png
[6]: https://i.imgur.com/ekL7m9T.png
