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
- 0809
    - DS4のBluetooth接続
    - ROSノード構造の決定
## 次の動き
- 0808
    - お盆休み中にDS4で動くラジコンを完成させる(詳細は後日整理)
    - ~~DS4のBluetooth接続~~ (0809done)
    - ~~ROSノード構造の決定~~ (0809done)
- 0809
    - ~~PCとラズパイ3のROS連携(0812)~~ (0812done)
    - PCA9685のROSでの制御(0812)
    - joy情報をmotor_ctlに渡す(0813)
    - コントローラの割り当て検討(0813)
    - 動作確認(0814)
    - 細かいデバッグ(0815)
## 仕様
### 全体仕様
基本的にはROS2ロボットと同じ  
![](system.png)
### 車体情報
https://osoyoo.com/2020/08/01/osoyoo-raspberry-pi-v2-0-car-introduction/
### ROSノード構造

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
参考ページ  
https://qiita.com/srs/items/7d4aeb5e44138f97c770
https://qiita.com/srs/items/309a16ae331da563c2e3  

pc側は通常通りの運用でOK．ラズパイは.bashrcに設定を書き込み済み．  
pcでのroscore起動を忘れないこと．
### ロボット全体



#### GPIO制御

### 表示系
#### フルカラーLED
使用LED
https://akizukidenshi.com/catalog/g/gI-02476/
参考URL
https://www.souichi.club/raspberrypi/color-led/
- 
