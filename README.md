# ROS1ラジコン
## 目的
自己研鑽．
会社でのミニバラック計画の予習兼ロボット製作の感覚取り戻し．

## 目標
- ros1の基礎の復習
- ソフトウェア面の技術のアップデート
- ミニバラック計画の予習

0904追記
- 自律移動するロボットを作りたい
    - GNSS，カメラ(画像認識)で目標設定
    - カメラ，超音波センサで障害物検知
    - カメラ，IMUで自己位置推定
- シミュレーションと実体をリンクさせたい
    - 自己位置推定の発展形
    - IMUとあと一つ何か→カメラorLiDAR
- 追従走行するロボットを作りたい
    - 目標認識
        - カメラ
        - UWB?趣味レベルで実装可能？
    - 制御
        - 参考になるものを調べる
    - ログ保存
        - rosbagで十分

上記をやるならラズパイ3では足りない
    →買ったロボットの動作確認は取れたのでラズパイ3とラズパイ4を交換  
    サーボ，ライントレースを実装後(もしくは並行)，ラズパイ4への移植作業を実施

230608追記
ソフト開発の感覚を取り戻す．転職だなんだと騒いでいるが，最新技術に触れられていない
→AIラジコンで取り戻す
次の動き
これまでのラジコンをラズパイ4に移植→カメラを用いた自動運転の実装


## これまでの動き
- 0723
    - 上司へ計画を相談→購入ロボット決定(後述)(~0808)
- 0811
    - DS4のBluetooth接続
    - ROSノード構造の決定
- 0812
    - PCA9685の動作概要把握
    - ros-pwm-pca9685の概要把握
- 0813
    - DS4のBluetooth接続
    - 本体のラジコン操作
## 次の動き
- 0808
    - お盆休み中にDS4で動くラジコンを完成させる(詳細は後日整理)
    - ~~DS4のBluetooth接続~~ (0809done)
    - ~~ROSノード構造の決定~~ (0809done)
- 0809
    - ~~PCとラズパイ3のROS連携(0812)~~ (0812done)
    - PCA9685のROSでの制御(0812)
        - ~~ros-pwm-pca9685の概要理解~~ done

        - ~~ros-pwm-pca9685に合わせてarrayをpub(詳細は後述)~~
        - ~~gpioを制御~~
        - ~~モータの制御履歴(回転方向(bool?)，回転速度(int64?))をpub~~
    - joy情報をmotor_ctlに渡す(0813)
        - ~~joy情報のsub~~
        - ~~joy情報からモータ回転方向，回転速度を計算~~
        - ~~publisherへ受け渡し~~
    - ~~コントローラの割り当て検討(0813)~~
    - ~~動作確認(0814)~~
    - ~~細かいデバッグ(0815)~~
- 2306更新
    - ラズパイ4への移植
        - DS4の接続
        - ~~基本ノードの動作確認~~ OK
        - joyノードの動作確認
        - モータードライバ接続
        - モータードライバ動作確認
    - リサーチ
    - 今後のタスクの整理(0911)
## 仕様
### 全体仕様
基本的にはROS2ロボットと同じ  
![](system.png)
### 車体情報
https://osoyoo.com/2020/08/01/osoyoo-raspberry-pi-v2-0-car-introduction/
### ROSノード構造
![](ros_node.png)

## 各系統について
### ROS1
- パッケージの作成
- pub-sub通信の理解

公式チュートリアルを参考にする．  
http://wiki.ros.org/ROS/Tutorials
### DualShock4-RaspberryPi3通信
https://qiita.com/Yuya-Shimizu/items/4bed435e65cefc6d2df1
https://www.anypalette.com/ja/posts/20211121_setup-rasberrypie/

使用ライブラリ
- ds4drv(ds4用のドライバ) done
- joy(ROS) done
- BlueZ(Bluetooth) done

### raspi3-PC通信
参考ページ  
https://qiita.com/srs/items/7d4aeb5e44138f97c770
https://qiita.com/srs/items/309a16ae331da563c2e3  

pc側は通常通りの運用でOK．ラズパイは.bashrcに設定を書き込み済み．  
pcでのroscore起動を忘れないこと．

### PCA9685制御
#### モータドライバ情報
PCA9685.pdf  
#### 配線
![](2022-08-12-12-17-54.png)
![](2022-08-12-12-16-14.png)
![](2022-08-12-12-16-34.png)

#### 使用ライブラリ
https://github.com/dheera/ros-pwm-pca9685
https://www.sato-susumu.com/entry/pwm_pca9685

rosparam set /pca9685_node/timeout "[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]"

<b>モータ回転方向→gpioのON/OFFで制御</b>
right
| 22 | 27 | 挙動 |
|----|----|----|
| 0 | 0 ||
| 1 | 0 |正転|
| 0 | 1 |逆転|
| 1 | 1 |ブレーキ|

left
| 24 | 23 | 挙動 |
|----|----|----|
| 0 | 0 ||
| 1 | 0 |正転|
| 0 | 1 |逆転|
| 1 | 1 |ブレーキ|

<b>モータ回転速度→pwmで制御</b>
>/command std_msgs/Int32MultiArray -1 '{data:[left, right, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1]}'

rightもしくはleftを0~65535で設定し，pubすることで0%~100%の出力となる．  
-1で更新なしとなる．

rosノードのsudo権限について  
https://akeblo.blogspot.com/2017/09/rosnoderoot.html
### ロボット全体

#### GPIO制御

### 表示系
#### フルカラーLED
使用LED
https://akizukidenshi.com/catalog/g/gI-02476/  
参考URL
https://www.souichi.club/raspberrypi/color-led/
