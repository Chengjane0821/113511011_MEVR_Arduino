# 課題報告：Advanced Task 2-3 External Interrupt vs Polling

- **學生姓名**：[程婕茵]
- **學生學號**：[113511011]
- **完成日期**：2026-9-24

---

### 1. 實驗目標

- 了解 External Interrupt（外部中斷）的基本概念與運作方式。
- 了解 Polling（輪詢）方式如何持續檢查按鍵狀態。
- 比較外部中斷與 Polling 在系統阻塞情況下的反應差異。
- 學習使用 `attachInterrupt()` 與 ISR（Interrupt Service Routine）處理按鍵事件。
- 練習使用 edge detection 偵測按鍵按下的狀態變化。
- 觀察 `delay()` 對一般程式流程與輸入反應速度的影響。

### 2. 設備與元件

- Arduino Uno 開發板 x 1
- USB Type-B 傳輸線 x 1
- 麵包板 x 1
- LED x 2
- 限流電阻 x 2
- 按鍵 x 2
- 杜邦線若干
- 個人電腦（已安裝 Arduino IDE）x 1

### 3. 操作說明與成果

1. **建立兩組按鍵與 LED 電路**：
   - Button A + LED A：使用 External Interrupt 控制 LED 狀態。
   - Button B + LED B：使用 Polling 方式控制 LED 狀態。

2. **Button A 外部中斷控制**：
   將 Button A 連接至 Arduino 支援外部中斷的腳位，並使用 `attachInterrupt()` 設定中斷事件。當偵測到按鍵事件時，Arduino 會執行對應的 ISR，切換 LED A 的亮滅狀態。

3. **Button B Polling 控制**：
   在 `loop()` 中持續使用 `digitalRead()` 讀取 Button B 的狀態，並利用 edge detection 判斷是否發生新的按下事件。偵測到按鍵由未按下變成按下時，切換 LED B 狀態。

4. **加入阻塞延遲**：
   在 `loop()` 最後加入 `delay(2000)`，模擬系統正在執行耗時工作或處於忙碌狀態。

5. **實驗觀察**：
   - Button A 使用 External Interrupt，即使程式正在 `delay(2000)`，按鍵事件仍能被偵測，LED A 可以快速反應。
   - Button B 使用 Polling，只有當程式回到 `loop()` 並再次執行 `digitalRead()` 時才能讀取按鍵，因此在 `delay(2000)` 期間可能無法即時反應，甚至可能漏掉短時間的按鍵輸入。

6. **實驗成果**：
   成功完成 External Interrupt 與 Polling 兩種按鍵控制方式，並透過加入 `delay(2000)` 清楚觀察兩者在系統阻塞狀態下的反應差異。

7. **操作影片**：
   請參閱同目錄下 `video/Task2-3.mp4` 之實際操作畫面。

### 4. 實驗原理

External Interrupt 是由外部事件主動觸發 CPU 執行指定的 ISR。當符合設定條件的訊號出現時，Arduino 會暫時中斷原本執行中的程式流程，先執行中斷服務函式，完成後再返回原本程式。

本實驗中，Button A 使用：

`attachInterrupt()`

將按鍵事件與 ISR 連結。當 Button A 發生指定狀態變化時，系統就會執行 ISR，切換 LED A 狀態。

Polling 則是由程式主動、反覆檢查輸入狀態。例如 Button B 必須在 `loop()` 中持續執行：

`digitalRead()`

才能知道按鍵是否被按下。

因此兩者的主要差異為：

- **External Interrupt**：事件發生時主動通知處理器，不需要一直檢查輸入。
- **Polling**：程式必須持續檢查輸入狀態，反應速度受到 `loop()` 執行週期影響。

當程式加入 `delay(2000)` 後，Polling 在這 2 秒內無法執行新的輸入檢查，因此反應會明顯變慢；External Interrupt 則仍可以在中斷條件發生時執行 ISR。

### 5. External Interrupt 與 Polling 比較

| 比較項目 | External Interrupt | Polling |
|---|---|---|
| 輸入偵測方式 | 事件發生時觸發 | 持續主動檢查 |
| 反應速度 | 較即時 | 依 `loop()` 執行速度而定 |
| 受 `delay()` 影響 | 較小 | 明顯受到影響 |
| 程式架構 | 需要 ISR 與中斷設定 | 邏輯較直觀 |
| 適合用途 | 即時性較高的事件 | 一般、非即時輸入 |

### 6. 機器人系統中的應用

在機器人系統中，如果需要處理具有即時性的事件，例如緊急停止、編碼器脈衝或重要感測器事件，External Interrupt 較適合，因為即使主程式正在執行其他工作，也能較即時處理事件。

Polling 則適合對即時性要求較低的輸入，例如一般按鍵狀態或週期性感測資料。

實際系統通常會依不同任務需求，同時使用 Interrupt 與 Polling，而不是只使用其中一種方式。

### 7. 實驗心得

本次實驗透過兩組按鍵與 LED，直接比較 External Interrupt 與 Polling 的差異。加入 `delay(2000)` 後，可以明顯看到 Polling 的反應受到主程式流程影響，而 External Interrupt 仍可以處理按鍵事件。

這次實驗讓我更了解中斷的用途，以及為什麼即時控制系統不能完全依賴 Polling。對於機器人或機電系統而言，選擇合適的事件處理方式會直接影響系統的反應速度與可靠性。