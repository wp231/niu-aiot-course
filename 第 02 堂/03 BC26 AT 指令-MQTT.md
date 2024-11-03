# BC26 AT 指令 MQTT

- [建立連接](#%E5%BB%BA%E7%AB%8B%E9%80%A3%E6%8E%A5)
	- [開啟 MQTT 連接](#%E9%96%8B%E5%95%9F-mqtt-%E9%80%A3%E6%8E%A5)
	- [連線 MQTT 伺服器](#%E9%80%A3%E7%B7%9A-mqtt-%E4%BC%BA%E6%9C%8D%E5%99%A8)
- [MQTT 訂閱和發布](#mqtt-%E8%A8%82%E9%96%B1%E5%92%8C%E7%99%BC%E5%B8%83)
	- [訂閱](#%E8%A8%82%E9%96%B1)
		- [訂閱主題](#%E8%A8%82%E9%96%B1%E4%B8%BB%E9%A1%8C)
		- [取消訂閱](#%E5%8F%96%E6%B6%88%E8%A8%82%E9%96%B1)
	- [發布](#%E7%99%BC%E5%B8%83)
- [斷開連接](#%E6%96%B7%E9%96%8B%E9%80%A3%E6%8E%A5)
	- [關閉 MQTT 連接](#%E9%97%9C%E9%96%89-mqtt-%E9%80%A3%E6%8E%A5)
	- [關閉網路連接](#%E9%97%9C%E9%96%89%E7%B6%B2%E8%B7%AF%E9%80%A3%E6%8E%A5)
- [範例](#%E7%AF%84%E4%BE%8B)
- [其他](#%E5%85%B6%E4%BB%96)


## 建立連接

### 開啟 MQTT 連接

此指令用來開啟 MQTT 客戶端的網路連線。執行該指令時，會設定 MQTT 伺服器的 IP 地址或域名，以及通訊端口。此過程是建立 TCP/IP 層級的連接，但尚未與 MQTT 伺服器建立具備協議層級的通訊。

- `AT+QMTOPEN=<TCP_connectID>,"<host_name>",<port>`
    - `<TCP_connectID>`: 連接識別碼 (0-5)
    - `<host_name>`: 伺服器 IP 位址或域名
    - `<port>`: 伺服器 Port

- 返回值: `+QMTOPEN: <TCP_connectID>,<result>`
    - `<result>`: 連接結果
        - `-1`: 連接失敗
        - `0`: 連接成功

### 連線 MQTT 伺服器

在成功開啟網路後，該指令用來向 MQTT 伺服器請求連接。此時是進行協議層級的連線，並需提供 `clientID`，以及可選的 `username` 和 `password` 以進行驗證。

- `AT+QMTCONN=<TCP_connectID>,"<clientID>","[username]","[password]"`
    - `<TCP_connectID>`: 連接識別碼 (0-5)
    - `<clientID>`: 客戶端識別碼
    - `[username]`: 用戶名
    - `[password]`: 密碼
- 返回值: `+QMTCONN: <TCP_connectID>,<result>,[ret_code]`
    - `<result>`: 連接結果
        - `0`: 資料包發送成功，伺服器正確回應 ACK
        - `1`: 資料包重新發送，伺服器未回應 ACK
        - `2`: 資料包發送失敗
    - `[ret_code]`: 連接結果
        - `0`: 連接接受
        - `1`: 連接拒絕: 不可接受的協議版本
        - `2`: 連接拒絕: 識別碼拒絕
        - `3`: 連接拒絕: 伺服器不可用
        - `4`: 連接拒絕: 用戶名或密碼錯誤
        - `5`: 連接拒絕: 未授權

## MQTT 訂閱和發布

### 訂閱

#### 訂閱主題

當 MQTT 客戶端與伺服器建立連接後，可以使用此指令訂閱一個或多個主題。當有訊息發布到訂閱的主題時，伺服器會將訊息推送給客戶端。

- `AT+QMTSUB=<TCP_connectID>,<msgID>,"<topic1>",<QoS1>,["<topic2>",<QoS2>,...,"<topicN>",<QoSN>]`
    - `<TCP_connectID>`: 連接識別碼 (0-5)
    - `<msgID>`: 訊息識別碼 (1-65535)
    - `<topic>`: 訂閱主題
    - `<QoS>`: 訂閱的 QoS 等級
- 返回值: `+QMTSUB: <TCP_connectID>,<msgID>,<result>,[value]`
    - `<result>`: 訂閱結果
        - `0`: 資料包發送成功，伺服器正確回應 ACK
        - `1`: 資料包重新發送，伺服器未回應 ACK
        - `2`: 資料包發送失敗
    - `[value]`: 訂閱結果
        - `0`: 如果 `<result>` 為 0，則為授權的 QoS 等級，值為 128 表示訂閱被伺服器拒絕
        - `1`: 如果 `<result>` 為 1，表示資料包重發次數
        - `2`: 如果 `<result>` 為 2，則不會出現
- 訂閱返回內容: `+QMTRECV: <TCP_connectID>,<msgID>,<topic>,<payload>`
    - `<msgID>`: 訊息識別碼
    - `<topic>`: 訂閱主題
    - `<payload>`: 訊息內容

#### 取消訂閱

當不再需要訂閱某個主題時，可以使用此指令取消訂閱。

- `AT+QMTUNS=<TCP_connectID>,<msgID>,"<topic1>",["<topic2>",...,"<topicN>"]`
    - `<TCP_connectID>`: 連接識別碼 (0-5)
    - `<msgID>`: 訊息識別碼
    - `<topic>`: 取消訂閱的主題

### 發布

此指令用來向指定主題發布訊息。

- `AT+QMTPUB=<TCP_connectID>,<msgID>,<qos>,<retain>,"<topic>","<msg>"`: 直接發布訊息
    - `<TCP_connectID>`: 連接識別碼 (0-5)
    - `<msgID>`: 訊息識別碼
    - `<QoS>`: QoS 等級
        - `0`：最多送一次 (不確認傳遞，可能丟失)。
        - `1`：最少送一次 (至少一次確認傳遞，可能重複)。
        - `2`：只送一次 (確保一次且只一次送達)。
    - `<retain>`: 保留訊息選項，用於決定伺服器在將訊息送到當前訂閱者後是否保留此訊息
        - `0`：不保留
        - `1`：保留
    - `<topic>`: 發布主題
    - `<msg>`: 訊息內容
- `AT+QMTPUB=<TCP_connectID>,<msgID>,<qos>,<retain>,"<topic>"`: 接收 UART 輸入發布訊息
    - 執行後模組會返回 `>` 提示符號，此時可以輸入訊息內容
    - 輸入完畢後按 `Ctrl+Z` 送出，或按 `ESC` 取消

## 斷開連接

### 關閉 MQTT 連接

當不再需要 MQTT 連接時，可以使用此指令關閉連接。

- `AT+QMTCLOSE=<TCP_connectID>`
    - `<TCP_connectID>`: 連接識別碼 (0-5)

### 關閉網路連接

當不再需要網路連接時，可以使用此指令關閉網路。

- `AT+QMTDISC=<TCP_connectID>`
    - `<TCP_connectID>`: 連接識別碼 (0-5)

## 範例

```shell
# 開啟 MQTT 連接
18:13:18.620 -> AT+QMTOPEN=0,"quiz.us.kg",2000
18:13:18.620 -> OK
18:13:19.944 -> 
18:13:19.944 -> +QMTOPEN: 0,0
# 連線 MQTT 伺服器
18:13:37.906 -> AT+QMTCONN=0,"DSI2598plus","USERNAME","PASSWORD"
18:13:37.906 -> OK
18:13:38.678 -> 
18:13:38.678 -> +QMTCONN: 0,0,0
# 訂閱主題
18:13:49.176 -> AT+QMTSUB=0,1,"value",2
18:13:49.176 -> OK
18:13:51.000 -> 
18:13:51.000 -> +QMTSUB: 0,1,0,2
# 發布訊息
18:13:59.752 -> AT+QMTPUB=0,1,1,0,"value","123"
18:13:59.752 -> OK
18:14:00.607 -> 
18:14:00.607 -> +QMTPUB: 0,1,0
# 訂閱返回
18:14:00.607 -> +QMTRECV: 0,1,"value","123"
18:14:00.607 -> 
# 中斷連接
18:14:16.552 -> AT+QMTDISC=0
18:14:16.599 -> OK
18:14:16.599 -> 
18:14:16.599 -> +QMTDISC: 0,0
```

## 其他

- 關閉省電和休眠模式，避免接收不到訊息

```shell
# 關閉 PSM 省電模式
18:22:58.207 -> AT+CPSMS=0
18:22:58.251 -> OK
# 關閉 eDRX
18:23:22.462 -> AT+QEDRXCFG=0
18:23:22.504 -> OK
# 關閉休眠模式
18:23:26.520 -> AT+QSCLK=0
18:23:26.520 -> OK
```