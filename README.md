# NIU AIoT Course

本儲存庫為 NIU AIoT 課程的內容，旨在提供學生開發 AIoT 應用的知識與技能。

## 教材內容大綱

### 1. AT 指令基本講解與實踐
- 了解 AT 指令的基本架構
- 介紹核心網與 NB-IoT 連線架構
- 介紹 HTTP 協定與 POST 請求
- 進行 Request 請求，實作 AT 指令練習與 STM32 程式開發

### 2. MQTT 協定與實際應用
- MQTT 協定介紹與自行伺服器架設
- 透過 Oracle VPS 伺服器建置 FRP 服務，實現內網穿透
- 使用溫溼度感測器進行 MQTT 伺服器互動與數據上傳

### 3. 硬體維修與 DSI2598+ 功耗控制
- Bootloader 韌體與 PCB 硬體維修講解，透過原理圖與 PCB 進行維修排查
- NB-IoT 協定的工作模式與節能策略（DRX、eDRX、PSM、Idle 模式）
- STM32 單晶片的功耗控制實踐

### 4. IoT 專用協議 CoAP 和 LwM2M
- TCP/IP 網路架構解釋
- CoAP 協議介紹與封包格式說明，從封包層面進行抓包分析
- LwM2M 協定介紹與伺服器建置架構，包括 Client、Bootstrap Server、Server：
  - Client 資源架構
  - Bootstrap Server 工作流程
  - 透過抓包分析 CoAP 協定在 Client 與 Server 互動時的底層運作

### 5. Node-Red 可視化數據管理
- 安裝與語言設定
- 安裝與設定 Dashboard
- Dashboard 結構概述與元件配置
- 建立溫度監測儀表板並顯示數據
- 訂閱 MQTT 主題並將數據視覺化
