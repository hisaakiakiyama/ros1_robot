# ROS1ラジコン
## 目的
自己研鑽．
会社でのミニバラック計画の予習兼ロボット製作の感覚取り戻し．

## 目標
- ros1の基礎の復習
- ソフトウェア面の技術のアップデート
- ミニバラック計画の予習

## これまでの動き
- 0723
    - 上司へ計画を相談→購入ロボット決定(後述)(~0808)
    - 
## 次の動き
- 0808
    - お盆休み中にDS4で動くラジコンを完成させる(詳細は後日整理)
    - ~~DS4のBluetooth接続~~ (0809done)
    - ~~ROSノード構造の決定~~ (0809done)
- 0809
    - PCA9685のROSでの制御
    - joy情報をmotor_ctlに渡す

## 仕様
### 全体仕様
基本的にはROS2ロボットと同じ  
![](system.png)
### 車体情報
https://osoyoo.com/2020/08/01/osoyoo-raspberry-pi-v2-0-car-introduction/

## 各系統について
### ROS1
- パッケージの作成
- pub-sub通信の理解

公式チュートリアルを参考にする．  
http://wiki.ros.org/ROS/Tutorials
#### DualShock4-RaspberryPi3通信
https://qiita.com/Yuya-Shimizu/items/4bed435e65cefc6d2df1
使用ライブラリ
- ds4drv(ds4用のドライバ) done
- joy(ROS) done
- BlueZ(Bluetooth) doing

#### raspi3-PC通信

### ロボット全体



#### GPIO制御

### 表示系
#### フルカラーLED
使用LED
https://akizukidenshi.com/catalog/g/gI-02476/
参考URL
https://www.souichi.club/raspberrypi/color-led/
- 
