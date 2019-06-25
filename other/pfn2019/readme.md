# 課題の解答
GNNの実装は全て`src/graph_neural_network.py`に行った．
## 課題1のテスト
`src/test.py`に実装してある．なお，テストでは，結果を手計算しやすくするために，パラメータWの初期値を対角成分が1の対角行列，Aを成分が全て1のベクトル，bを0としている．
## 課題2でlossが減少することの確認
レポートのグラフから確認できる．
## 課題3，4のレポート
`report.pdf`を参照．なお，課題4ではAdamの実装を選択している．レポートの図は`output`に入っている． 
## 課題4の予測
`prediction.txt`に出力した．

# コードの実行方法
## 課題1のテスト
```
python src/test.py
```
## レポートの図の描画・出力
```
python src/plot_result.py
```
## 課題4の予測・出力
```
python src/predict.py
```
