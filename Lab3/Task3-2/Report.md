# 課題報告：Advanced Task 3-2 LED Control with Serial Communication

- **學生姓名**：[程婕茵]
- **學生學號**：[113511011]
- **完成日期**：2026-10-01

---

### 1. 實驗目標

- 學習 Arduino 與電腦之間的 UART Serial Communication。
- 使用 C# 建立電腦端 GUI 控制介面。
- 透過序列埠由 PC 傳送控制命令至 Arduino。
- 使用 Arduino 接收 Serial 資料並控制 LED 開關。
- 了解電腦端應用程式與 Arduino firmware 之間的基本通訊架構。

### 2. 設備與軟體

- Arduino Uno 開發板 x 1
- USB Type-B 傳輸線 x 1
- LED x 1
- 限流電阻 x 1
- 麵包板 x 1
- 杜邦線若干
- 個人電腦 x 1
- Arduino IDE
- Visual Studio
- C# 開發環境

### 3. 操作說明與成果

1. **Arduino 電路連接**：
   將 LED 與限流電阻連接至 Arduino 的數位輸出腳位，並完成基本 LED 控制電路。

2. **Arduino Serial 初始化**：
   在 Arduino 程式的 `setup()` 中使用：

   `Serial.begin(9600);`

   設定序列通訊鮑率為 9600 baud。

3. **Arduino 接收資料**：
   在 `loop()` 中持續檢查序列埠是否有新的資料，並讀取由電腦端傳送過來的控制命令。

4. **C# GUI 建立**：
   使用 Visual Studio 建立 C# 電腦端控制程式，設計 LED 控制介面，例如提供 `ON` 與 `OFF` 按鈕。

5. **傳送控制命令**：
   當使用者按下 GUI 中的按鈕時，C# 程式透過指定的 COM Port 傳送對應的控制資料給 Arduino。

6. **LED 控制**：
   Arduino 接收到指定命令後，依照收到的資料執行對應動作：
   - 接收到開啟命令時，LED 亮起。
   - 接收到關閉命令時，LED 熄滅。

7. **實驗成果**：
   成功由 C# GUI 透過 USB Serial Communication 將控制命令傳送至 Arduino，並即時控制 LED 的亮滅，完成 PC 與 Arduino 之間的基本通訊與控制。

8. **操作影片**：
   請參閱同目錄下 `video/Task3-2.mp4` 之實際操作畫面。

### 4. 系統架構

本實驗可分成兩個主要部分：

**Host PC App（C#）**
- 建立 GUI。
- 開啟指定 COM Port。
- 當使用者按下按鈕時傳送控制資料。

**Arduino Firmware**
- 使用 `Serial.begin(9600)` 初始化 UART。
- 持續監聽序列埠資料。
- 根據接收到的命令控制 LED。

整體資料流程如下：

`C# GUI → Serial Port → USB → Arduino → LED`

使用者在電腦端操作 GUI 後，C# 程式將控制命令經由序列埠傳送至 Arduino，Arduino 解析收到的資料後再控制 LED 的輸出狀態。

### 5. Serial Communication 原理

UART 是常見的非同步序列通訊方式，資料會依照設定好的 Baud Rate 逐位元傳輸。

本實驗中，Arduino 使用：

`Serial.begin(9600);`

代表 Arduino 與電腦端程式皆需要使用相同的 9600 baud 設定。

C# 程式透過 Windows 的 COM Port 與 Arduino 建立連線。當按下 GUI 中的按鈕時，電腦端會將字元或字串傳送給 Arduino。

Arduino 收到資料後，可透過 Serial 相關函式判斷是否有資料並讀取內容，再根據命令控制 LED。

因此，本實驗的核心是：

`使用者操作 GUI → C# 傳送資料 → Arduino 接收資料 → 控制 LED`

### 6. 實驗注意事項

- C# 與 Arduino 的 Baud Rate 必須設定一致。
- C# 程式使用的 COM Port 必須與 Arduino 實際連接的 COM Port 相同。
- 執行 C# 程式前，應避免 Arduino IDE 的 Serial Monitor 同時占用同一個 COM Port。
- 如果無法連線，應先確認 COM Port 是否正確、是否被其他程式占用。
- LED 必須串接限流電阻，避免電流過大造成損壞。

### 7. 實驗心得

本次實驗與前幾次只在 Arduino 端執行程式的方式不同，這次加入了電腦端 C# 應用程式，讓 Arduino 可以接收來自 PC 的控制命令。

透過建立 GUI 並利用 Serial Communication 控制 LED，我了解了電腦端程式與微控制器之間的基本通訊方式，也更清楚 Host Program 與 Arduino Firmware 各自負責的功能。

這次實驗也讓我熟悉 COM Port 與 Baud Rate 的概念，並了解在實際系統開發中，可以透過電腦端介面來控制硬體裝置，作為之後無線通訊與更複雜機電系統整合的基礎。