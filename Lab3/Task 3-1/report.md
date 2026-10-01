# 課題報告：Advanced Task 3-1 Timer Interrupt vs Blocking Delay

- **學生姓名**：[程婕茵]
- **學生學號**：[113511011]
- **完成日期**：2026-10-01

---

### 1. 實驗目標

- 學習使用 TimerOne library 建立週期性 Timer Interrupt。
- 了解 ISR（Interrupt Service Routine）的基本運作方式。
- 比較 Timer Interrupt 與 Blocking Delay 在按鍵反應速度上的差異。
- 觀察 `delay()` 對主程式執行與輸入偵測的影響。
- 了解 Timer Interrupt 在即時控制系統與機器人系統中的應用。

### 2. 設備與元件

- Arduino Uno 開發板 x 1
- USB Type-B 傳輸線 x 1
- 麵包板 x 1
- LED x 2
- 限流電阻 x 2
- 按鍵 x 2
- 杜邦線若干
- 個人電腦（已安裝 Arduino IDE）x 1
- TimerOne Library

### 3. 操作說明與成果

1. **建立兩組按鍵與 LED 電路**：
   - Button A + LED A：使用 Timer Interrupt 控制。
   - Button B + LED B：使用一般 `loop()` 搭配 Blocking Delay 控制。

2. **Timer Interrupt 設定**：
   使用 TimerOne library 設定週期性 Timer Interrupt，每隔 **50 ms** 觸發一次 ISR。

3. **Button A 控制**：
   在 Timer Interrupt 的 ISR 中讀取 Button A 的狀態，並立即更新 LED A，因此按鍵狀態可以固定週期被檢查。

4. **Button B 控制**：
   在 `loop()` 中使用 `digitalRead()` 讀取 Button B 的狀態，再控制 LED B 的亮滅。

5. **加入 Blocking Delay**：
   在 `loop()` 的最後加入 `delay(1000)`，使主程式每次執行後暫停 1 秒，用來模擬系統被阻塞的情況。

6. **實驗觀察**：
   - Button A 使用 Timer Interrupt，每 50 ms 都會由 ISR 檢查一次，因此即使主程式受到 `delay(1000)` 阻塞，LED A 仍能較快速反應按鍵輸入。
   - Button B 必須等待 `loop()` 再次執行才能重新讀取，因此按鍵反應明顯受到 1 秒 delay 影響。
   - 若 Button B 按下時間很短，也可能因為剛好發生在 delay 期間而無法即時被偵測。

7. **實驗成果**：
   成功完成 Timer Interrupt 與 Blocking Delay 的比較，可以明顯觀察到 Timer Interrupt 的反應速度與即時性較佳，而使用 Blocking Delay 的程式則容易受到主程式執行時間影響。

8. **操作影片**：
   請參閱同目錄下 `video/Task3-1.mp4` 之實際操作畫面。

### 4. 實驗原理

Timer Interrupt 是利用硬體計時器，在設定的固定時間到達時自動產生中斷事件。

本實驗使用 TimerOne library 設定 Timer1，使其每隔 50 ms 觸發一次 ISR。當中斷發生時，Arduino 會暫時停止目前主程式的執行，先執行 ISR，完成後再返回原本程式。

因此 Button A 的處理流程為：

**Timer 每 50 ms 觸發 → 執行 ISR → 讀取 Button A → 更新 LED A**

另一方面，Button B 採用一般的主程式流程：

**執行 loop() → 讀取 Button B → 更新 LED B → delay(1000)**

由於 `delay(1000)` 會暫停主程式 1 秒，因此在這段時間內，Button B 的狀態不會被重新讀取，造成反應延遲。

### 5. Timer Interrupt 與 Blocking Delay 比較

| 比較項目 | Timer Interrupt | Blocking Delay |
|---|---|---|
| 執行方式 | 固定時間自動觸發 ISR | 主程式依序執行 |
| 按鍵檢查頻率 | 每 50 ms | 約每 1 秒以上 |
| 即時性 | 較高 | 較低 |
| 受 `delay()` 影響 | 較小 | 明顯受到影響 |
| 是否阻塞主程式 | 否 | 是 |
| 適合用途 | 即時控制、週期性任務 | 簡單且對時間不敏感的程式 |

### 6. 機器人系統中的應用

對機器人系統而言，Timer Interrupt 通常適合需要固定週期執行的工作，例如：

- 馬達控制
- 感測器定時取樣
- 控制器更新
- 編碼器資料處理
- 週期性狀態更新

相較之下，若大量使用 `delay()`，主程式會被阻塞，使系統無法即時處理其他工作，因此不適合需要快速反應或同時執行多個任務的系統。

在實際機器人系統中，較常使用 Timer Interrupt 或 non-blocking 的程式設計方式處理重要的週期性工作。

### 7. 實驗心得

本次實驗讓我實際比較 Timer Interrupt 與 Blocking Delay 對系統反應速度的影響。

當程式加入 `delay(1000)` 後，可以明顯看到使用一般 `loop()` 控制的 Button B 反應較慢，而由 Timer Interrupt 控制的 Button A 仍能維持固定週期檢查，因此反應較即時。

透過這次實驗，我更了解中斷與主程式之間的關係，也理解為什麼在機器人或即時控制系統中，不應過度使用 Blocking Delay，而應利用 Timer Interrupt 或其他 non-blocking 方法提高系統反應能力。