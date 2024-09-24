# BC26 AT 指令

- [物聯網連線架構](#%E7%89%A9%E8%81%AF%E7%B6%B2%E9%80%A3%E7%B7%9A%E6%9E%B6%E6%A7%8B)
	- [流程](#%E6%B5%81%E7%A8%8B)
- [AT 指令](#at-%E6%8C%87%E4%BB%A4)
	- [語法](#%E8%AA%9E%E6%B3%95)
	- [設備設定](#%E8%A8%AD%E5%82%99%E8%A8%AD%E5%AE%9A)
		- [設定控制](#%E8%A8%AD%E5%AE%9A%E6%8E%A7%E5%88%B6)
			- [保存設定](#%E4%BF%9D%E5%AD%98%E8%A8%AD%E5%AE%9A)
			- [重置設定](#%E9%87%8D%E7%BD%AE%E8%A8%AD%E5%AE%9A)
			- [恢復設定](#%E6%81%A2%E5%BE%A9%E8%A8%AD%E5%AE%9A)
		- [回顯輸入指令](#%E5%9B%9E%E9%A1%AF%E8%BC%B8%E5%85%A5%E6%8C%87%E4%BB%A4)
		- [設定波特率](#%E8%A8%AD%E5%AE%9A%E6%B3%A2%E7%89%B9%E7%8E%87)
		- [模組功能狀態](#%E6%A8%A1%E7%B5%84%E5%8A%9F%E8%83%BD%E7%8B%80%E6%85%8B)
		- [重新啟動](#%E9%87%8D%E6%96%B0%E5%95%9F%E5%8B%95)
	- [網路設定](#%E7%B6%B2%E8%B7%AF%E8%A8%AD%E5%AE%9A)
		- [PDN 和 APN](#pdn-%E5%92%8C-apn)
			- [一般指令](#%E4%B8%80%E8%88%AC%E6%8C%87%E4%BB%A4)
			- [Quectel 專有](#quectel-%E5%B0%88%E6%9C%89)
		- [頻段](#%E9%A0%BB%E6%AE%B5)
		- [設定範例](#%E8%A8%AD%E5%AE%9A%E7%AF%84%E4%BE%8B)
	- [網路狀態查詢](#%E7%B6%B2%E8%B7%AF%E7%8B%80%E6%85%8B%E6%9F%A5%E8%A9%A2)
		- [PDP 上下文狀態](#pdp-%E4%B8%8A%E4%B8%8B%E6%96%87%E7%8B%80%E6%85%8B)
		- [網路註冊狀態](#%E7%B6%B2%E8%B7%AF%E8%A8%BB%E5%86%8A%E7%8B%80%E6%85%8B)
		- [查詢訊號狀態](#%E6%9F%A5%E8%A9%A2%E8%A8%8A%E8%99%9F%E7%8B%80%E6%85%8B)
		- [查詢 IP 地址](#%E6%9F%A5%E8%A9%A2-ip-%E5%9C%B0%E5%9D%80)
		- [PING 測試](#ping-%E6%B8%AC%E8%A9%A6)
	- [網路連接](#%E7%B6%B2%E8%B7%AF%E9%80%A3%E6%8E%A5)
		- [建立連接](#%E5%BB%BA%E7%AB%8B%E9%80%A3%E6%8E%A5)
		- [連接狀態](#%E9%80%A3%E6%8E%A5%E7%8B%80%E6%85%8B)
		- [傳送資料](#%E5%82%B3%E9%80%81%E8%B3%87%E6%96%99)
		- [接收資料](#%E6%8E%A5%E6%94%B6%E8%B3%87%E6%96%99)
		- [中斷連接](#%E4%B8%AD%E6%96%B7%E9%80%A3%E6%8E%A5)
- [參考資料](#%E5%8F%83%E8%80%83%E8%B3%87%E6%96%99)



## 物聯網連線架構

![](attachment/Pasted%20image%2020240922030008.png)

1. **UE（User Equipment，設備）**

	- **UE** 是指終端設備，這裡特指 **NB-IoT** 設備，它是物聯網設備的物理硬件部分，通過 **NB-IoT SIM 卡** 連接到網路。
	- **NB-IoT** 是一種低功耗、廣覆蓋的物聯網技術，適合用於簡單的傳感器、計量設備等，這些設備通過 **NB-IoT SIM 卡** 與網路進行通訊。

2. **APN（Access Point Name，接入點名稱）**

	- **APN** 是設備連接到公共數據網路（PDN）的入口。它決定了設備應該連接到哪個數據網路（例如互聯網或物聯網專用網路）。
	- 在這個例子中，APN 是指一個專用的物聯網網路，允許設備連接到特定的 PDN 以傳輸數據。

3. **PS 附著（Packet Switched Attach，分組交換附著）**

	- **PS 附著** 是設備註冊到核心網路的過程。當設備上電或啟動時，它會通過 PS 附著將自己連接到 4G 核心網（EPC）。
	- 在此過程中，設備會與核心網路交換身份驗證信息，並獲取初步的網路連接權限。

4. **PDP 上下文（Packet Data Protocol Context，分組數據協議上下文）**

	- **PDP 上下文** 是一個邏輯實體，它管理設備與核心網路之間的數據通訊會話。
	- 當 NB-IoT 設備發起數據通訊時，它會啟動一個 PDP 上下文，這樣設備就能通過這個會話與核心網路中的 PGW 進行數據傳輸。
	- PDP 上下文會定義設備的 IP 地址、數據會話的類型（例如 IPv4 或 IPv6）和通訊參數。

5. **PGW（Packet Data Network Gateway，分組數據網關）**

	- **PGW** 是核心網路（EPC）中的一部分，它負責設備與外部數據網路（PDN）的連接。
	- **PGW** 會驗證 **APN**，並確保設備有權連接到指定的 PDN。它同時負責為設備分配 IP 地址，並確保設備能夠與外部網路（如互聯網或企業內部網路）進行數據通訊。

6. **EPC（Evolved Packet Core，演進分組核心網路）**

	- **EPC** 是 4G 核心網的組成部分，負責數據路由和管理。它包括多個功能節點，如 PGW、SGW（Serving Gateway）等，支持設備的移動性和數據傳輸。
	- 在圖中，EPC 是設備進入數據網路的核心部分。

7. **PDN（Public Data Network，公共數據網路）**

	- **PDN** 是指公共或專用數據網路，例如互聯網、企業內部網路或物聯網服務平台。
	- **PDN** 是設備最終連接的網路，通過 PGW，設備可以向 PDN 進行數據傳輸，這裡可能是將數據上傳到雲端，或者從遠程伺服器接收指令。

### 流程

- **PS 附著**：NB-IoT 設備通過分組交換附著流程連接到核心網（EPC）。
- **PDP 上下文激活**：設備啟動一個 PDP 上下文，與核心網進行會話。
- **APN 檢驗與連接**：核心網的 PGW 檢查設備的 APN，並確定設備應該連接到的 PDN。
- **數據連接**：設備與指定的 PDN 進行數據傳輸，PGW 會負責路由和 IP 分配。

## AT 指令

### 語法

- 基本語法
	- `AT<指令>[參數]`
	- `AT&<指令>[參數]`
- 擴充語法
	- `AT+<指令>`: 執行指令
	- `AT+<指令>?`: 查看指令的當前設定
	- `AT+<指令>=?`: 查看指令的可用參數
	- `AT+<指令>=<參數 1, 參數 2 ...>`: 執行指令參數

### 設備設定

#### 設定控制

##### 保存設定

- `AT&W`: 保存當前設置到模塊的 NVRAM（非易失性存儲），重啟後仍保留這些設置

##### 重置設定

- `AT&F`: 恢復出廠設置，將模塊的參數恢復為默認值

##### 恢復設定

- `ATZ`: 恢復到模塊的默認設置，類似 `AT&F`，但 `ATZ` 通常會使用上次保存的設置，而不是出廠設置


#### 回顯輸入指令

- `ATE0`: 關閉
```py
17:35:04.937 -> ATE0
17:35:04.937 -> OK
17:35:06.923 -> 
17:35:06.923 -> OK
```
- `ATE1`: 開啟
```py
17:36:22.184 -> ATE1
17:36:22.184 -> OK
17:36:23.781 -> AT
17:36:23.781 -> OK
```

#### 設定波特率

- `AT+IPR?`: 查看當前設定波特率
- `AT+IPR=?`: 查看可設定的波特率
- `AT+IPR=<波特率>`: 設定波特率

#### 模組功能狀態

- `AT+CFUN?`: 查詢模組功能狀態
	- 返回值: `+CGATT: <fun>`
		- `<fun>`: 0 為功能未完全開啟, 1 功能完全開啟

#### 重新啟動

- `AT+QRST=1`: 立即重啟模塊（仍然保持網路連接）

### 網路設定

#### PDN 和 APN

##### 一般指令

- `AT+CGACT=<state>,<cid>`: 啟動或停用特定的 PDP 上下文
- `AT+CGAPNRC=<cid>`: APN 的速率控制
- `AT+CGDCONT=<cid>`: 定義 PDP 上下文的參數，例如接入點名稱（APN）和 IP 地址類型
- 參數
	- `<state>`: 0 禁用, 1 啟用
	- `<cid>`: 指定 PDP 上下文 ID

##### Quectel 專有

- `AT+QGACT=<op>,<cid>`: 設定啟用 APN
	- `AT+QGACT=1,1,"apn","internet.iot"`
- `AT+QCGDEFCONT=<PDP_type>,[APN],[user_name],[password]`: 設定預設註冊 APN
	- `AT+QCGDEFCONT="IP","internet.iot"`
- 參數
	- `<op>`: 0 禁用, 1 啟用
	- `<PDP_type>`
		- `"IP"`：適用於傳統的 IPv4 網路傳輸
		- `"IPV6"`：用於下一代 IPv6 網路，地址空間更大
		- `"IPV4V6"`：支援雙棧，即 IPv4 和 IPv6 都可使用
		- `"Non-IP"`：用於非 IP 協定的數據傳輸，常見於某些物聯網場景
	- `<cid>`: 指定 PDP 上下文的 ID
	- `[APN]`: 接入點 APN

#### 頻段

- `AT+QBAND=?`: 當前設備可用頻段
- `AT+QBAND?`: 當前使用頻段
- `AT+QBAND=<band_number>,<band>`: 設定頻段
	- `<band_number>`: 模組使用哪種頻段組合模式
	- `<band>`: 模組運行的具體頻段
		- `1`：2100 MHz
		- `3`：1800 MHz
		- `5`：850 MHz
		- `8`：900 MHz

#### 設定範例

[中華電信](https://www.cht.com.tw/home/enterprise/products-services/mobile/data/678)官方說明

- APN: `internet.iot`
	![](attachment/Clip_2024-09-22_16-42-25.png)
- 頻段設定: Band 8
	![](attachment/Clip_2024-09-22_16-42-57.png)

```py
AT+QBAND=1,8						# 設定頻段
AT+QGACT=1,1,"apn","internet.iot"	# 設定啟用 APN
AT+QCGDEFCONT="IP","internet.iot"	# 設定預設註冊 APN
AT+QRST=1							# 重新啟動
```

### 網路狀態查詢

#### PDP 上下文狀態

- `AT+CGATT?`
	- 返回值: `+CGATT: <state>`
		- `<state>`: 0 停用, 1 啟用

#### 網路註冊狀態

- `AT+CEREG?`: 查詢網路註冊狀態
	- 返回值: `+CEREG: <n>,<stat>`
- `AT+CEREG=<n>`
- 參數
	- `<n>`: 用來設定你想要的行為
		- `0`: 完全不回報網路註冊狀態
		- `1`: 只回報註冊狀態 (已註冊或未註冊)
		- `2`: 回報註冊狀態和網路位置資訊 (例如小區 ID 和追蹤區域碼)
		- `3`: 除了註冊狀態和位置資訊外，還回報網路註冊失敗的原因
		- `4` 和 `5`: 當設備進入低功耗模式 (PSM) 時，回報更多與節電相關的資訊
	- `<stat>`: 設備當前網路註冊狀態
		- `0`: 未註冊，也沒有搜尋網路
		- `1`: 已註冊，使用的是本地網路 (例如你的手機連接到你家的行動運營商)
		- `2`: 未註冊，但正在搜尋網路
		- `3`: 註冊被拒絕
		- `4`: 未知 (例如在 E-UTRAN 覆蓋範圍之外)
		- `5`: 已註冊，並且是在漫遊網路上

#### 查詢訊號狀態

- `AT+CSQ`: 簡易查詢訊號狀態
	- 返回值: `+CSQ: <rssi>,<ber>`
		- `<rssi>`: 表示接收到的訊號強度，範圍從 0 到 31，數值越高表示訊號越強。
			- `0`: 表示接收到的訊號低於 -113 dBm，或信號非常弱
			- `31`: 表示接收到的訊號強度大於 -51 dBm，或信號非常強
			- `99`: 表示訊號未知或無法檢測到
		- `<ber>`: 表示在接收過程中位元錯誤的比例，範圍從 0 到 7，數字越小，表示錯誤率越低，訊號質量越好。
			- `0`: 表示錯誤率最低，即訊號質量最好
			- `99`: 表示無法檢測到錯誤率
- `AT+CESQ`: 詳細查詢訊號狀態
	- 返回值: `+CESQ: <rxlev>,<ber>,<rscp>,<ecno>,<rsrq>,<rsrp>`
		- `<rxlev>`: 接收到的訊號強度，數值越大越好
		- `<ber>`: 通道的位錯誤率，數值越小越好
		- `<rscp>`: 指接收的訊號碼功率，數值越大越好
		- `<ecno>`: 單位晶片的能量對比噪聲比，數值越小越好
		- `<rsrq>`: 接收質量，數值越大越好
		- `<rsrp>`: 接收功率，數值越大越好

#### 查詢 IP 地址

- `AT+QIPADDR`: 查詢用戶設備當前的 IP 地址
- `AT+CGPADDR=<cid>`: 可以查詢單個或所有激活的 PDP 上的 IP 地址
	- `<cid>`: 查看特定 PDP 上的 IP 地址，未指定時查詢所有 PDP 的 IP 地址

#### PING 測試

- `AT+QPING=<contextID>,<host>`: Ping 主機
	`AT+QPING=1,8.8.8.8`

### 網路連接

#### 建立連接

- `AT+QIOPEN=<contextID>,<connectID>,<service_type>,<IP_address/domain_name>,<remote_port>`
	- `<contextID>`: 指定模組使用哪個 PDP 上下文連接進行數據傳輸
	- `<connectID>`: 標示當前連接的索引，可同時建立多個連接
	- `<service_type>`: `"TCP"` 建立 TCP 連接、`"UDP"`  建立 UDP 連接
	- `<IP_address>/<domain_name>`: 連接遠端伺服器的 IP 或域名
	- `<remote_port>`: 遠端伺服器端口號

#### 連接狀態

- `AT+QISTATE?`: 查詢所有連接的狀態
- `AT+QISTATE=0,<contextID>`: 查詢指定 PDP 上下文內的所有連接狀態
- `AT+QISTATE=1,<connectID>`: 查詢指定連接的狀態
- 返回值: `+QISTATE: <connectID>,<service_type>,<IP_address/domain_name>,<remote_port>,<local_port>,<socket_state>,<contextID>,<access_mode>`
	- `<connectID>`: 連接索引
	- `<service_type>`: 連接類型
		- `"TCP"`: TCP 連接
		- `"UDP"`: UDP 連接
	- `<IP_address/domain_name>`: 遠端伺服器 IP 或域名
	- `<remote_port>`: 遠端伺服器端口號
	- `<local_port>`: 本地端口號
	- `<socket_state>`: 連接狀態
		- `0`: "Initial", 初始狀態，尚未建立連接
		- `1`: "Connecting", 正在連接中
		- `2`: "Connected", 已成功建立連接
		- `3`: "Closing", 連接正在關閉
		- `4`: "Remote Closing", 遠端伺服器正在關閉連接
	- `<contextID>`: PDP 上下文 ID
	- `<access_mode>`: 數據訪問模式
		- `0`: Buffer access mode（緩衝訪問模式）數據先存儲在模組的緩衝區中，然後由主機逐步讀取。這種模式下，數據不會直接推送，而是需要主機自己調用命令來讀取數據。
		- `1`: Direct push mode（直接推送模式）數據會直接推送給主機，而不經過緩衝區。接收到的數據會立即通過 URC（未經請求的結果代碼）形式推送給主機。

#### 傳送資料

- `AT+QISEND=<connectID>,<data_length>,"<data>"`: 直接發送資料
	- `<connectID>`: 指定要使用的連接索引
	- `<data_length>`: 要發送資料 `<data>` 的長度
	- `<data>`: 要發送的資料

- `AT+QISEND=<connectID>`: 變長資料發送
	- 執行後模組會返回 `>`，此時可以輸入資料
	- 輸入完畢後按 `Ctrl+Z` 送出，或按 `ESC` 取消

> 當接收到來自遠端的資料時，模組會返回
> `+QIURC: "recv",<connectID>,<data_length><CR><LF><data>`

#### 接收資料

- `AT+QIRD=<connectID>,<data_length>`: 讀取資料
	- `<connectID>`: 指定要使用的連接索引
	- `<data_length>`: 要讀取的資料長度

#### 中斷連接

- `AT+QICLOSE=<connectID>`: 中斷指定的連接
	- `<connectID>`: 指定中斷的連接索引

## 參考資料

- [EPC核心网_百度百科](https://baike.baidu.com/item/EPC%E6%A0%B8%E5%BF%83%E7%B6%B2)
- [What is PDP, and Attach in GPRS - Mobile Packet Core Basic Concepts](https://mobilepacketcore.com/pdp-attach/)
- [LTE基本架构 - 思否学否 - 博客园](https://www.cnblogs.com/yz123/p/11943232.html)
- [4G EPS 中的 PDN Connection - 云物互联 - 博客园](https://www.cnblogs.com/jmilkfan-fanguiju/p/12789777.html)
- [最大限度延长蜂窝物联网的电池寿命：对 eDRX、PSM 和 AS-RAI 的分析 - Nordic Semiconductor中文官网](https://www.nordicsemi.cn/news/maximizing-battery-lifetime-in-cellular-iot-an-analysis-of-edrx-psm-and-as-rai/)