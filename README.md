# ROS2ラジコン
## 目的
自己研鑽．

## 目標
- ros2の基礎の習得
- ハードウェアとソフトウェア両面の技術のアップデート

## 次の動き
- 0723
    - 上司へ計画を相談→ロボットの購入(~0726)
    - 基本的なpub-sub通信の実装(日本語チュートリアル1個目)(マキホリ)
    - フルカラーLEDの制御(マキホリ)
    - DS4の接続(マキホリ)

## 仕様
### 全体仕様
![](system.png)
### 

## 各系統について
### ROS2
- パッケージの作成
- pub-sub通信の理解

公式チュートリアルを参考にする．
日本語チュートリアル
https://www.moriken254.com/
#### DualShock4-RaspberryPi4通信
調査中...
https://demura.net/education/18004.html
#### raspi4-PC通信
~~調査中~~
同じネットワーク上にいれば勝手にpub-sub通信してくれる(すご……)
### ロボット全体
#### 購入ロボットの検討
最終的にROS2(rviz2)でシミュレーション，センサの追加等することから，シンプルな構造かつ安価(2万円以下？)なもの
- 候補1

- 候補2


#### GPIO制御
pigpioを使用．下記参照
https://qiita.com/NeK/items/da429f8c001476ec4544
まずはLチカ(単色・非PWM)→Lチカ(単色・PWM)→Lチカ(RGB)→ROS2制御
そのあとモータドライバ制御へ
### 表示系
#### フルカラーLED
使用LED
https://akizukidenshi.com/catalog/g/gI-02476/
参考URL
https://www.souichi.club/raspberrypi/color-led/
- 
