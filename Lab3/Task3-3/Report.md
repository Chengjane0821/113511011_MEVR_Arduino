# 課題報告：Advanced Task 3-3 HC-05 Wireless LED Control

- **學生姓名**：[程婕茵]
- **學生學號**：[113511011]
- **完成日期**：2026-10-01

---

### 1. 實驗目標

- 學習使用 HC-05 Bluetooth 模組進行無線通訊。
- 將 Advanced Task 3-2 的 Serial Communication 改為 Bluetooth Communication。
- 使用 C# Host PC App 傳送控制命令至 Arduino。
- 讓 Arduino 透過 HC-05 接收資料並控制 LED 亮滅。
- 了解 Arduino、HC-05 與 PC 端程式之間的無線通訊架構。

### 2. 設備與軟體

- Arduino Uno 開發板 x 1
- HC-05 Bluetooth 模組 x 1
- LED x 1
- 限流電阻 x 1
- 麵包板 x 1
- 杜邦線若干
- 個人電腦 x 1
- Arduino IDE
- Visual Studio
- C# 開發環境

### 3. 操作說明與成果

1. **HC-05 與 Arduino 連接**：
   將 HC-05 的電源與通訊腳位連接至 Arduino，建立 UART 通訊。

2. **Bluetooth 模組設定**：
   完成 HC-05 的配對與通訊設定，使電腦能透過 Bluetooth COM Port 與 HC-05 建立連線。

3. **Arduino 程式設定**：
   Arduino 持續接收由 HC-05 傳來的資料，並根據收到的控制命令改變 LED 的輸出狀態。

4. **C# Host App 設定**：
   沿用 Advanced Task 3-2 的 GUI 控制程式，將原本使用的 USB Serial COM Port 改成 HC-05 所對應的 Bluetooth COM Port。

5. **LED 控制**：
   當使用者在 C# GUI 中按下控制按鈕時，PC 端會透過 Bluetooth 傳送命令給 HC-05，再由 Arduino 接收並控制 LED：
   - 接收到開啟命令時，LED 亮起。
   - 接收到關閉命令時，LED 熄滅。

6. **實驗成果**：
   成功以 HC-05 建立 PC 與 Arduino 之間的無線通訊，並可透過 C# GUI 遠端控制 LED 的亮滅，完成 Bluetooth LED Control。

7. **操作影片**：
   請參閱同目錄下 `video/Task3-3.mp4` 之實際操作畫面。

### 4. 系統架構

本實驗的整體通訊流程如下：

`C# GUI → Bluetooth COM Port → HC-05 → Arduino → LED`

C# 程式負責產生控制命令，Windows 透過 Bluetooth COM Port 傳送資料至 HC-05，HC-05 再利用 UART 與 Arduino 通訊。

Arduino 接收到命令後，根據資料內容控制 LED 開啟或關閉。

與 Advanced Task 3-2 相比，主要差別在於：

- Task 3-2 使用 USB Serial Communication。
- Task 3-3 使用 HC-05 Bluetooth Communication。

因此，PC 端與 Arduino 端的基本控制邏輯相近，主要需要修改的是通訊介面與 COM Port 設定。

### 5. Bluetooth Communication 原理

HC-05 是一種 Bluetooth Serial 模組，可將 Bluetooth 無線通訊轉換成 UART Serial Communication。

在 PC 端與 HC-05 配對後，Windows 會建立一個 Bluetooth COM Port。C# 程式即可像一般 Serial Port 一樣，透過此 COM Port 傳送資料。

HC-05 收到 Bluetooth 資料後，會透過 UART 將資料傳送給 Arduino。

因此整個資料流可以表示為：

`PC → Bluetooth → HC-05 → UART → Arduino`

Arduino 不需要直接處理 Bluetooth 協定，而只需要接收 HC-05 所輸出的 UART 資料。

### 6. 實驗注意事項

- Arduino 與 HC-05 的 TX / RX 腳位必須正確交叉連接。
- HC-05 與 Arduino 的通訊鮑率必須一致。
- 電腦端 C# 程式必須選擇正確的 Bluetooth COM Port。
- 若配對成功但沒有反應，需確認 HC-05 的通訊設定與 baud rate 是否正確。
- Arduino 與 HC-05 的邏輯電壓不同，接線時需注意電壓匹配。
- LED 必須串接限流電阻，避免過大電流造成損壞。

### 7. 實驗心得

本次實驗是在 Advanced Task 3-2 的基礎上，將原本的 USB 有線 Serial Communication 改成 Bluetooth 無線通訊。

透過 HC-05 模組，我了解了 PC 端可以利用 Bluetooth COM Port 與 Arduino 進行通訊，而 Arduino 端仍然可以使用 UART 的方式接收資料。

成功完成 LED 無線控制後，我更清楚理解了「通訊介面可以改變，但控制邏輯可以延續使用」的概念。這也讓我了解，在實際的機電整合系統中，可以透過更換不同通訊方式，讓原本的控制架構具備更高的彈性與無線化能力。