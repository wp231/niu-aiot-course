# Node-Red

- [安裝](#%E5%AE%89%E8%A3%9D)
- [修改語言](#%E4%BF%AE%E6%94%B9%E8%AA%9E%E8%A8%80)
- [安裝 Dashboard](#%E5%AE%89%E8%A3%9D-dashboard)
- [創建 Dashboard 物件](#%E5%89%B5%E5%BB%BA-dashboard-%E7%89%A9%E4%BB%B6)
- [Dashboard 結構說明](#dashboard-%E7%B5%90%E6%A7%8B%E8%AA%AA%E6%98%8E)
- [模擬溫度顯示儀表盤](#%E6%A8%A1%E6%93%AC%E6%BA%AB%E5%BA%A6%E9%A1%AF%E7%A4%BA%E5%84%80%E8%A1%A8%E7%9B%A4)
- [訂閱 MQTT 主題並顯示](#%E8%A8%82%E9%96%B1-mqtt-%E4%B8%BB%E9%A1%8C%E4%B8%A6%E9%A1%AF%E7%A4%BA)


本次實作將使用 Node-Red 作為 IoT 裝置的監控與控制中心，透過 `node-red-dashboard` 這個套件，可以快速建立一個簡易的監控介面。

## 安裝

- 安裝 Docker

    ```bash
    sudo apt install docker.io -y
    ```

- 運行 Node-Red 的 Docker 容器

    ```bash
    sudo docker run -d -p 1880:1880 -v node_red_data:/data --name mynodered nodered/node-red
    ```

- 瀏覽器打開 `http://localhost:1880` 即可看到 Node-Red 的編輯器

    ![](../attachment/Clip_2024-12-07_17-20-15.png)

## 修改語言

- 進入設定
    ![](../attachment/Clip_2024-12-07_17-21-27.png)

- 設定預言為**繁體中文**
    ![](../attachment/Clip_2024-12-07_17-22-10.png)

- 重新整理網頁，即可看到語言已經變更
    ![](../attachment/Clip_2024-12-07_17-22-42.png)

## 安裝 Dashboard

- 點選右上角的三條線，進入**節點管理**
    ![](../attachment/Clip_2024-12-07_17-24-25.png)

- 搜所 `node-red-dashboard` 並安裝
    ![](../attachment/Clip_2024-12-07_17-25-38.png)

- 點擊安裝
	![](../attachment/Clip_2024-12-07_17-26-28.png)

## 創建 Dashboard 物件

![](../attachment/Clip_2024-12-07_17-29-00.png)

![](../attachment/Clip_2024-12-07_17-44-27.png)

![](../attachment/Clip_2024-12-07_17-47-28.png)

![](../attachment/Clip_2024-12-07_17-50-29.png)

![](../attachment/Clip_2024-12-07_17-51-34.png)

![](../attachment/Clip_2024-12-07_17-51-57.png)

## Dashboard 結構說明

![](../attachment/Clip_2024-12-07_17-36-42.png)

![](../attachment/Clip_2024-12-07_17-39-07.png)

![](../attachment/Clip_2024-12-07_17-39-56.png)

## 模擬溫度顯示儀表盤

- 創建手動輸入溫度為 `25`
	![](../attachment/Clip_2024-12-07_18-31-29.png)
	
- 創建儀表盤
	![](../attachment/Clip_2024-12-07_18-30-24.png)

- 部署流程
	![](../attachment/Clip_2024-12-07_18-34-34.png)

- 輸出溫度
	![](../attachment/Clip_2024-12-07_18-35-37.png)

- 察看結果
	![](../attachment/Clip_2024-12-07_18-36-29.png)

## 訂閱 MQTT 主題並顯示

> 在使用此章節前請參考 [01 MQTT 協定介紹](../第%2002%20堂/01%20MQTT%20協定介紹.md) 和 [02 內網穿透](../第%2002%20堂/02%20內網穿透.md) 架設 MQTT 伺服器

- 設定添加 MQTT 伺服器
	![](../attachment/Clip_2024-12-07_18-59-25.png)

- 設定伺服器地址和端口
	![](../attachment/Clip_2024-12-07_19-00-42.png)

- 訂閱 `DHT` 主題，輸出解析 JSON 字串
	![](../attachment/Clip_2024-12-07_19-01-57.png)

- 使用 Debug 解析傳入 JSON
	![](../attachment/Clip_2024-12-07_19-07-55.png)

- 通過發送可以知道接收到的資料在 msg -> payload 底下
	![](../attachment/Clip_2024-12-07_19-10-50.png)

- 設定儀錶板顯示資料
	![](../attachment/Clip_2024-12-07_19-12-57.png)

	![](../attachment/Clip_2024-12-07_19-13-45.png)

- 儀錶板結果
	![](../attachment/Clip_2024-12-07_19-14-23.png)