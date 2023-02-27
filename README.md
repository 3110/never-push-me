# 絶対に！押すなボタン

<img src="https://github.com/3110/never-push-me/raw/main/images/never-push-me.jpg" width="800px">

絶対に押しちゃダメなボタンです。押すなよ，絶対に押すなよ。

元ネタは「[『絶対に！押すな』のボタン、押し放題の誘惑](https://www.nikkei.com/article/DGXZQOUC26A8A0W2A420C2000000/)」（2022 年 6 月 5 日 日経 MJ）です。

## 動作環境

[M5Stack 社](https://m5stack.com/) の [ATOMS3](https://shop.m5stack.com/products/atoms3-dev-kit-w-0-85-inch-screen) で[M5Unified](https://github.com/m5stack/M5Unified)を使って実装しています。[VSCode](https://azure.microsoft.com/ja-jp/products/visual-studio-code) の [PlatformIO IDE](https://platformio.org/platformio-ide) 環境でコンパイルしてください。

私は Windows 11 上で動作確認をしています。

## 実行方法

ATOMS3 を PC に接続すると，USB キーボードとして認識されます。上記の写真では，[スイッチサイエンス](https://www.switch-science.com/)で販売している[USB Type-A/Type-C プラグアダプタ](https://ssci.to/7998)を使用しています。

絶対に押しちゃダメですが，押すと`CTRL+ALT+DELETE`が押されたのと同じ動作になります。

### LINE への通知機能

v0.0.2 より`env:never-push-me-with-line-notify`を選択してコンパイルすると，WiFi に接続して LINE Notify にボタンが押されたことを通知できるようになりました。

`data` ディレクトリ（`platformio.ini`の`[platformio]`セクションにある`data_dir`で指定したディレクトリ）に以下 JSON ファイル（`line_notify.json`）を置いて LINE Notify に接続するために必要な情報を記載します。

```line_notify.json
{
    "ssid": "[SSID]",
    "password": "[パスワード]",
    "token": "[LINE Notify のパーソナル・アクセス・トークン]"
}
```

※ここで指定するパーソナル・アクセス・トークンは LINE Notify のマイページから発行できます。

ファームウェアを書き込んだ後，PlatformIO メニューから「Upload Filesystem Image」を選択するか，コマンドラインから`pio run --target uploadfs`を実行して設定ファイルを SPIFFS にアップロードし，設定を反映します。
