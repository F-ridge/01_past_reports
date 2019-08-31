

# 数理実験第１（カオスシステム） レポート

学生証番号: XX-XXXXXX

氏名: 佐藤 瞭

所属: 数理情報工学コース ３年

提出日: 2019/07/16

連絡先: XXXXX

---

# 課題１

## 目的

Chua回路や二重振り子を題材として、数値シュミレーションと実際の電気回路の比較や、アトラクタの解析をすることでカオスへの理解を深める。



## 実験方法

### Chua回路

図１に示すような回路をChua回路という。この回路について、数値シュミレーション及び電気回路の作成によりアトラクタの観察を行う。

![chua](/home/neko/00_reports/3S/experiments/chaos/chua.jpg)

<div style="text-align: center;">
図1 Chua回路[1]
</div>

- 数値シュミレーション[2]: 以下の$v_{C_1} , v_{C_2} , i_L$に関する微分方程式を4次Runge-Kutta法で解き、アトラクタをプロットする。初期値は$v_{C_1} = v_{C_2} = i_L = 0.01$とした。、

$\begin{equation}\begin{aligned}
\begin{array}{l}{C_{1} \frac{d v_{C_{1}}}{d t}=G\left(v_{c_{2}}-v_{c_{1}}\right)-g\left(v_{c_{1}}\right)} \\ {C_{2} \frac{d v_{C_{2}}}{d t}=G\left(v_{C_{1}}-v_{C_{2}}\right)+i_{L}} \\ {L \frac{d i_{L}}{d t}=-v_{C_{2}}}\end{array}
\end{aligned}\end{equation}$

$\begin{equation}
    g\left(v_{c_{1}}\right)=m_{0} v_{C_{1}}+\frac{1}{2}\left(m_{1}-m_{0}\right)\left|v_{C_{1}}+B_{p}\right|+\frac{1}{2}\left(m_{0}-m_{1}\right)\left|v_{C_{1}}-B_{p}\right|
\end{equation}$

パラメータは以下の通り。

$\begin{equation}
\begin{array}{l}{\frac{1}{C_{1}}=9, \quad \frac{1}{C_{2}}=1, \quad \frac{1}{L}=7, \quad G=\frac{1}{R}=0.1 \sim 1.5} \\ {m_{0}=-0.5, \quad m_{1}=-0.8, \quad B_{p}=1}\end{array}
\end{equation}$



- 電気回路の作成: 図1の電気回路をブレッドボード上に作成し、可変抵抗の抵抗値を変化させながらオシロスコープで電圧を計測することでアトラクタを見る。



### 二重振り子

配布資料[2] p.30 の、二重振り子の数値シュミレーションを行う。陽的オイラー法とシンプレクティックオイラー法の2つを適用した。

<img src="/home/neko/00_reports/3S/experiments/chaos/huriko.jpg" style="zoom:20%" />

<div style="text-align: center;">
図2 二重振り子（図は[2]から引用）
</div>

図2のようにパラメータをとると、二重振り子の運動エネルギー$T$と位置エネルギー$U$は次のように表される。ただし、重力加速度は$g$とする。

$\begin{equation}
    T=\frac{1}{2} m_{1} l_{1}^{2} \dot{\theta}_{1}^{2}+\frac{1}{2} m_{2}\left(l_{1}^{2} \dot{\theta}_{1}^{2}+l_{2}^{2} \dot{\theta}_{2}^{2}+2 l_{1} l_{2} \dot{\theta}_{1} \dot{\theta}_{2} \cos \left(\theta_{1}-\theta_{2}\right)\right)
\end{equation}$

$\begin{equation}
    U=-m_{1} l_{1} g \cos \left(\theta_{1}\right)-m_{2} g\left(l_{1} \cos \left(\theta_{1}\right)+l_{2} \cos \left(\theta_{2}\right)\right)
\end{equation}$

今回は、パラメータは$g =9.8, l_1 =0.5, l_2 =0.5,m_1 =0.5,  m_2 =0.3$とした。

- 陽的オイラー法

ラグランジュ関数$L=T-U$から得られる、$\theta_1 , \theta_2$に関する以下のラグランジュ方程式を、$x = {(\theta_1 , \theta_2, \dot{\theta_1}, \dot{\theta_2})}^T$に関する微分方程式$\dot{x} = f(x)$とみなして陽的オイラー法で数値解を求める。

$\begin{equation}
    \ddot{\theta}_{1}=\frac{\omega^{2} l\left(-\sin \theta_{1}+M \cos \Delta \theta \sin \theta_{2}\right)-M l\left(\dot{\theta}_{1}^{2} \cos \Delta \theta+l \dot{\theta}_{2}^{2}\right) \sin \Delta \theta}{l-M l \cos ^{2} \Delta \theta}
\end{equation}$



$\begin{equation}
    \ddot{\theta}_{2}=\frac{\omega^{2} \cos \Delta \theta \sin \theta_{1}-\omega^{2} \sin \theta_{2}+\left(\dot{\theta_{1}}^{2}+M l \dot{\theta_{2}}^{2} \cos \Delta \theta\right) \sin \Delta \theta}{l-M l \cos ^{2} \Delta \theta}
\end{equation}$



- シンプレクティックオイラー法

上のラグランジュ方程式に対して、以下のように$p_1, p_2, q_1, q_2$をおく。

$\begin{equation}
    \begin{array}{l}{\left(\begin{array}{l}{q_{1}} \\ {q_{2}}\end{array}\right)=\left(\begin{array}{l}{\theta_{1}} \\ {\theta_{2}}\end{array}\right)} \\ {\left(\begin{array}{l}{p_{1}} \\ {p_{2}}\end{array}\right)=\left(\begin{array}{cc}{\left(m_{1}+m_{2}\right) l_{1}^{2}} & {m_{2} l_{1} l_{2} \cos \left(\theta_{1}-\theta_{2}\right)} \\ {m_{2} l_{1} l_{2} \cos \left(\theta_{1}-\theta_{2}\right)} & {m_{2} l_{2}^{2}}\end{array}\right)\left(\begin{array}{c}{\dot{\theta}_{1}} \\ {\dot{\theta}_{2}}\end{array}\right)}\end{array}
\end{equation}$

すると、二重振り子のハミルトン方程式は以下のようになる（$H=T+U$）。

$\begin{equation}
    \begin{aligned} \frac{\mathrm{d} q_{1}}{\mathrm{d} t} &=\frac{\partial H}{\partial p_{1}}=\frac{F_{1}}{l_{1}^{2} l_{2} G} \\ \frac{\mathrm{d} q_{2}}{\mathrm{d} t} &=\frac{\partial H}{\partial p_{2}}=\frac{F_{2}}{m_{2} l_{1} l_{2}^{2} G} \\ \frac{\mathrm{d} p_{1}}{\mathrm{d} t} &=-\frac{\partial H}{\partial q_{1}}=-\frac{F_{1} F_{2} \sin \left(q_{1}-q_{2}\right)}{l_{1}^{2} l_{2}^{2} G^{2}}-\left(m_{1}+m_{2}\right) l_{1} g \sin q_{1} \\ \frac{\mathrm{d} p_{2}}{\mathrm{d} t} &=-\frac{\partial H}{\partial q_{2}}=\frac{F_{1} F_{2} \sin \left(q_{1}-q_{2}\right)}{l_{1}^{2} l_{2}^{2} G^{2}}-m_{2} l_{2} g \sin q_{2} \end{aligned}
\end{equation}$

ただし、

$\begin{equation}
    \begin{array}{l}{F_{1}=l_{2} p_{1}-l_{1} p_{2} \cos \left(q_{1}-q_{2}\right)} \\ {F_{2}=\left(m_{1} l_{1}+m_{2} l_{1}\right) p_{2}-m_{2} l_{2} p_{1} \cos \left(q_{1}-q_{2}\right)} \\ {G=m_{1}+m_{2}-m_{2} \cos ^{2}\left(q_{1}-q_{2}\right)}\end{array}
\end{equation}$

これに、以下のシンプレクティックオイラー法の離散化を用いる。

$\begin{equation}
    \begin{array}{l}{q^{(i+1)}=q^{(i)}+h \frac{\partial H}{\partial p}\left(q^{(i+1)}, p^{(i)}\right)} \\ {p^{(i+1)}=p^{(i)}-h \frac{\partial H}{\partial q}\left(q^{(i+1)}, p^{(i)}\right)}\end{array}
\end{equation}$

すると、離散化されたハミルトン方程式は以下のような形になる。

$\begin{equation}
\begin{array}{l}{q_{1}^{(i+1)}=q_{1}^{(i)}+h \frac{F_{1}}{l_{1}^{2} l_{2} G}} \\ {q_{2}^{(i+1)}=q_{2}^{(i)}+h \frac{F_{2}}{m_{2} l_{1} l_{2}^{2} G}} \\ {p_{1}^{(i+1)}=p_{1}^{(i)}+h\left(-\frac{F_{1} F_{2} \sin \left(q_{1}^{(i+1)}-q_{2}^{(i+1)}\right)}{l_{1}^{2} l_{2}^{2} G^{2}}-\left(m_{1}+m_{2}\right) l_{1} g \sin q_{1}^{(i+1)}\right)} \\ {p_{2}^{(i+1)}=p_{2}^{(i)}+h\left(\frac{F_{1} F_{2} \sin \left(q_{1}^{(i+1)}-q_{2}^{(i+1)}\right)}{l_{1}^{2} l_{2}^{2} G^{2}}-m_{2} l_{2} g \sin q_{2}^{(i+1)}\right)}\end{array}
\end{equation}$

ただし、

$\begin{equation}
    \begin{array}{l}{F_{1}=l_{2} p_{1}^{(i)}-l_{1} p_{2}^{(i)} \cos \left(q_{1}^{(i+1)}-q_{2}^{(i+1)}\right)} \\ {F_{2}=\left(m_{1} l_{1}+m_{2} l_{1}\right) p_{2}^{(i)}-m_{2} l_{2} p_{1}^{(i)} \cos \left(q_{1}^{(i+1)}-q_{2}^{(i+1)}\right)} \\ {G=m_{1}+m_{2}-m_{2} \cos ^{2}\left(q_{1}^{(i+1)}-q_{2}^{(i+1)}\right)}\end{array}
\end{equation}$

各反復で、$p_{1}^{(i)}, p_{2}^{(i)}, q_{1}^{(i)}, q_{2}^{(i)}$の計算後、${\theta}_{1}^{(i)}, {\theta}_{2}^{(i)}, {\dot{\theta}_{1}^{(i)}}, {\dot{\theta}_{2}^{(i)}}$は以下の計算により求めることができる。

$\begin{equation}
    \left(\begin{array}{c}{\theta_{1}^{(i)}} \\ {\theta_{2}^{(i)}}\end{array}\right)=\left(\begin{array}{l}{q_{1}^{(i)}} \\ {q_{2}^{(i)}}\end{array}\right)
\end{equation}$

$\begin{equation}
\left(\begin{array}{c}{\dot{\theta}_{1}^{(i)}} \\ {\dot{\theta}_{2}^{(i)}}\end{array}\right)=\left(\begin{array}{cc}{\left(m_{1}+m_{2}\right) l_{1}^{2}} & {m_{2} l_{1} l_{2} \cos \left(q_{1}^{(i)}-q_{2}^{(i)}\right)} \\ {m_{2} l_{1} l_{2} \cos \left(q_{1}^{(i)}-q_{2}^{(i)}\right)} & {m_{2} l_{2}^{2}}\end{array}\right)^{-1}\left(\begin{array}{c}{p_{1}^{(i)}} \\ {p_{2}^{(i)}}\end{array}\right)
\end{equation}$

ここで、$q_{1}^{(i+1)} -  q_{2}^{(i+1)}$の値はニュートン法により求めることとした。具体的には、$q_{1}^{(i+1)}, q_{2}^{(i+1)}$の離散スキームから得られる以下の式の左辺を$q_{1}^{(i+1)} -  q_{2}^{(i+1)} = x$の関数とみなし、$f(x)  = 0$をニュートン法で解いた。

$\begin{equation}
    \left(q_{1}^{(i+1)}-q_{2}^{(i+1)}\right)-\left(q_{1}^{(i)}+h \frac{F_{1}}{l_{1}^{2} l_{2} G}-q_{2}^{(i)}-h \frac{F_{2}}{m_{2} l_{1} l_{2}^{2} G}\right)=0
\end{equation}$



## 実験結果

### Chua回路

- 数値シュミレーションの結果を図3に示す。アトラクタを見やすくするために、10000回反復したうちの5000回目以降をプロットして、解軌道が（存在するならば）アトラクタに収束していると思われる部分のみ見えるようにしてある。

![chua01](/home/neko/00_reports/3S/experiments/chaos/chua01.png)

&thinsp;&thinsp;&thinsp;&thinsp;&thinsp;&thinsp;&thinsp;&thinsp;&thinsp;&thinsp;&thinsp;&thinsp;&thinsp;&thinsp;&thinsp;&thinsp;&thinsp;&thinsp;&thinsp;&thinsp;&thinsp;&thinsp;&thinsp;&thinsp;&thinsp;&thinsp;&thinsp;&thinsp;&thinsp;&thinsp;&thinsp;&thinsp;&thinsp;&thinsp;&thinsp;&thinsp;&thinsp;&thinsp;&thinsp;&thinsp;&thinsp;&thinsp;&thinsp;&thinsp;&thinsp; 図3 Chua回路の数値シュミレーション結果（初期値: $v_{C_1} = v_{C_2} = i_L = 0.01$）



- 実際に回路を組んでオシロスコープで電圧を測定した結果を図4-1から4-6に示す。図１でのGの値が大きくなる順に並べてある。

![07](/home/neko/00_reports/3S/experiments/chaos/photo/07.jpg)

<div style="text-align: center;">
図4-1 Chua回路の測定結果（R = 1.791kΩ）
</div>



![06](/home/neko/00_reports/3S/experiments/chaos/photo/06.jpg)

<div style="text-align: center;">
図4-2 Chua回路の測定結果（R = 1.760kΩ）
</div>



![05](/home/neko/00_reports/3S/experiments/chaos/photo/05.jpg)

<div style="text-align: center;">
図4-3 Chua回路の測定結果（R = 1.724kΩ）
</div>



![04](/home/neko/00_reports/3S/experiments/chaos/photo/04.jpg)

<div style="text-align: center;">
図4-4 Chua回路の測定結果（R = 1.623kΩ）
</div>



![03](/home/neko/00_reports/3S/experiments/chaos/photo/03.jpg)

<div style="text-align: center;">
図4-5 Chua回路の測定結果（R = 0.984kΩ）
</div>



![01](/home/neko/00_reports/3S/experiments/chaos/photo/01.jpg)

<div style="text-align: center;">
図4-6 Chua回路の測定結果（R = 0.003kΩ）
</div>







### 二重振り子

- 陽的オイラー法

初期値を$\theta_1 (0)=0.1, \theta_2 (0)=0, \dot{\theta_1}(0)=0, \dot{\theta_2}(0)=0$としたときの、振り子の$(\theta_1 , \theta_2)$の時間変化を図5-1に示す。

![huriko01](/home/neko/00_reports/3S/experiments/chaos/huriko01.png)

<div style="text-align: center;">
図5-1 陽的オイラー法による二重振り子の数値解
</div>



はじめの1000反復の様子を図5-2に示す。

![huriko03](/home/neko/00_reports/3S/experiments/chaos/huriko03.png)

<div style="text-align: center;">
図5-2 陽的オイラー法による二重振り子の数値解（はじめの1000反復）
</div>



ハミルトニアンの時間変化を図6に示す。

![huriko02](/home/neko/00_reports/3S/experiments/chaos/huriko02.png)

<div style="text-align: center;">
図6 陽的オイラー法による二重振り子の数値解のハミルトニアン
</div>



- シンプレクティックオイラー法

初期値 $\theta_1 (0)=0.1, \theta_2 (0)=0, \dot{\theta_1}(0)=0, \dot{\theta_2}(0)=0$としたときのハミルトニアンの推移を図7に示す。

![huriko04](/home/neko/00_reports/3S/experiments/chaos/huriko04.png)

<div style="text-align: center;">
図7 シンプレクティックオイラー法による二重振り子の数値解のハミルトニアン
</div>



このときの、$\dot{\theta_1}=0$でのポアンカレ断面を図8に示す。

![huriko05](/home/neko/00_reports/3S/experiments/chaos/huriko05.png)

<div style="text-align: center;">
図8 シンプレクティックオイラー法による二重振り子の数値解のポアンカレ断面(1)
</div>



また、初期値をわずかに変化させ、$\theta_1 (0)=0.1, \theta_2 (0)=0.001, \dot{\theta_1}(0)=0, \dot{\theta_2}(0)=0$としたときの、$\dot{\theta_1}=0$でのポアンカレ断面を図9に示す。

![huriko06](/home/neko/00_reports/3S/experiments/chaos/huriko06.png)

<div style="text-align: center;">
図9 シンプレクティックオイラー法による二重振り子の数値解のポアンカレ断面(2)
</div>



## 考察

### Chua回路

図3の数値解と、図4-1~4-6の測定結果を比較する。

まず、図３の数値解をみてみる。$G$の値を大きくしていくと、発散（$G = 0.4$）→１回巻きの周期アトラクタ（$G = 0.62$）→２回巻きの周期アトラクタ（$G = 0.635$）→4回巻きの周期アトラクタ（$G = 0.645$）→…→$2^n$回巻きの周期アトラクタ（$G  \simeq  0.657$）→ストレンジアトラクタ（$G = 0.67$）→ダブルスクロールアトラクタ（$G = 0.677$）→様々な形の周期アトラクタ（$G \simeq 0.7$）→発散（$G = 1$）と推移していった。

次に、図4-1~4-6の測定結果をみてみる。$G=1/R$の値を大きくしていくと、平衡点アトラクタ（$R = 1.791\rm{k} \Omega$）→周期アトラクタ（$R = 1.760\rm{k} \Omega$）→ストレンジアトラクタ（$R = 1.724\rm{k} \Omega$）→ダブルスクロールアトラクタ（$R = 1.623\rm{k} \Omega$）→より外側の周期アトラクタ（$R = 0.984\rm{k} \Omega$）→直線（周期アトラクタかどうかわからなかった）（$R = 0.003\rm{k} \Omega$）と推移していった。

数値解と測定結果の間に見られた相違点を挙げる。

- 数値解では、$2^n$回巻き周期アトラクタや、ダブルスクロールアトラクタはさまざまな形がみられたが、測定結果では、巻数の変化やダブルスクロールアトラクタの形の変化を確認できなかった。
  - 原因は2つ考えられる。
    - 数値解では、$G$の値を小さく変化させると、$2^n$回巻き周期アトラクタやダブルスクロールアトラクタの形が大きく変わることが、図3から確認できる。実際の回路でも可変抵抗の小さな変化に対してアトラクタの形が大きく変化することが予想されるが、今回は手作業で可変抵抗のつまみを回していたため、抵抗値の細かい制御が難しく、$2^n$回巻き周期アトラクタやダブルスクロールアトラクタの変化を記録するのが困難であったことが原因の1つとして考えられる。
    - オシロスコープの解像度が低く、線が重なっている部分でアトラクタの形の違いがあっても目視で判別できず、変化を目視で検知しにくかったことが原因の1つとして考えられる。



- $G$が大きいときに、数値解は、螺旋状に無限遠に向かって発散したのに対して、測定結果では周期アトラクタがみられた。
- $G$が小さいときに、数値解はある直線にそって発散したのに対して、測定結果では平衡点アトラクタがみられた。



### 二重振り子

#### 陽的オイラー法

図5-1, 5-2をみると、途中の反復までは$\theta_1 , \theta_2 $は周期的な振動を繰り返しているが、ある時間から先では振動せずに両者が発散していることがわかる。一方で図6をみると、$\theta_1 , \theta_2 $が振動しなくなったタイミングのあたりからハミルトニアンが急速に大きくなっていることがわかる。

図6にみられるような、ハミルトニアンが時間とともに大きくなる結果は、今回の二重振り子の設定に反する。なぜならば、今回の二重振り子の系は、外部とのエネルギーがやりとりがない保存系であり、この系のハミルトニアンは運動エネルギーと位置エネルギーの和であるために、ハミルトニアンは初期値によって定められる定数となるべきだからである。



#### シンプレクティックオイラー法

図7をみると、ハミルトニアンは発散していないことがわかる。周期的な振動はみられるものの、ハミルトニアンはある一定の範囲に収まっており、先ほどの陽的オイラー法と比べて、ハミルトニアンの安定性という観点において改善されているといえる。また、先程述べたような、今回の系のハミルトニアンは一定であるべき、という要請を、陽的オイラー法と比べてより良く満たしているといえる。

また、図8・図9を見ると、初期値$ \theta_2 (0)$のわずかな変化に対してポアンカレ断面が鋭敏な依存性を見せている。このことから、カオスの有する性質[3]としての、初期値に対する鋭敏な依存性や、長期予測の困難性を確かめることができる。



# 課題2

「適切さ」を、安定性、計算時間の2つの意味で解釈し、それぞれについて考察する。

### 安定性の意味での適切さ

数値解による軌道の、真の解軌道との誤差が、時間とともに増大してしまうとき、その数値解法は「数値的に不安定」と呼ばれる。そのような数値解は現象を「適切」に表現できているとはいえないだろう。そのため、数値的な安定性は、現象を数値的に、「適切に」再現する上で重要になると考えられる。

今回の実験から例を与える。二重振り子に対する（時間刻み幅0.01の）陽的オイラー法は、ハミルトニアンの数値解の、真のハミルトニアン（ある定数）との誤差が時間とともに増大してしまっているために、数値的に不安定であるといえる。一方で、シンプレクティックオイラー法は、ハミルトニアンの数値解は一定の範囲を周期的に振動し続けるため、真のハミルトニアンとの誤差は、ある範囲の中で振動し、時間とともに増大しない。そのため、二重振り子に対する（時間刻み幅0.001の）シンプレクティックオイラー法は数値的に安定であるといえる。

なお、以下の図10に示すように、陽的オイラー法の刻み幅を0.001にしてハミルトニアンの数値解を求めても、ハミルトニアンの数値解は時間とともに増加し、刻み幅0.001の陽的オイラー法は数値的に不安定であると考えられる。したがって、同じ刻み幅でも安定するシンプレクティックオイラー法のほうが、今回の二重振り子の数値解法として、安定性の意味では「適切」であると考えられる。

![huriko07](/home/neko/00_reports/3S/experiments/chaos/huriko07.png)

<div style="text-align: center;">
図10 陽的オイラー法による二重振り子の数値解のハミルトニアン（刻み幅0.001）
</div>



### 計算時間の意味での適切さ

ある数値解法が安定であったとしても、反復に時間がかかったり、反復を増やしても誤算の収束が遅ければ、計算に長い時間がかかってしまい、その数値解法は実用的とはいえないだろう。そのため、1反復の計算量が小さい解法や、反復ごとの誤差の収束スピードが速い解法は、実用上「適切」であるといえる。

1反復の計算量に対して、今回の実験から例を与える。二重振り子に対する解法として、反復の計算量だけで考えれば、シンプレクティックオイラー法よりも陽的オイラー法のほうが「適切」な解法であるといえる。なぜならば、陽的オイラー法を適用する微分方程式

$\begin{equation}
    \ddot{\theta}_{1}=\frac{\omega^{2} l\left(-\sin \theta_{1}+M \cos \Delta \theta \sin \theta_{2}\right)-M l\left(\dot{\theta}_{1}^{2} \cos \Delta \theta+l \dot{\theta}_{2}^{2}\right) \sin \Delta \theta}{l-M l \cos ^{2} \Delta \theta}
\end{equation}$



$\begin{equation}
    \ddot{\theta}_{2}=\frac{\omega^{2} \cos \Delta \theta \sin \theta_{1}-\omega^{2} \sin \theta_{2}+\left(\dot{\theta_{1}}^{2}+M l \dot{\theta_{2}}^{2} \cos \Delta \theta\right) \sin \Delta \theta}{l-M l \cos ^{2} \Delta \theta}
\end{equation}$

は逐次計算で解くことができるが、シンプレクティックオイラー法の離散スキーム

$\begin{equation}
\begin{array}{l}{q_{1}^{(i+1)}=q_{1}^{(i)}+h \frac{F_{1}}{l_{1}^{2} l_{2} G}} \\ {q_{2}^{(i+1)}=q_{2}^{(i)}+h \frac{F_{2}}{m_{2} l_{1} l_{2}^{2} G}} \\ {p_{1}^{(i+1)}=p_{1}^{(i)}+h\left(-\frac{F_{1} F_{2} \sin \left(q_{1}^{(i+1)}-q_{2}^{(i+1)}\right)}{l_{1}^{2} l_{2}^{2} G^{2}}-\left(m_{1}+m_{2}\right) l_{1} g \sin q_{1}^{(i+1)}\right)} \\ {p_{2}^{(i+1)}=p_{2}^{(i)}+h\left(\frac{F_{1} F_{2} \sin \left(q_{1}^{(i+1)}-q_{2}^{(i+1)}\right)}{l_{1}^{2} l_{2}^{2} G^{2}}-m_{2} l_{2} g \sin q_{2}^{(i+1)}\right)}\end{array}
\end{equation}$

は逐次計算では解けないため、非線形方程式を1反復ごとに解く必要があるためである[2]。



以上の2つの適切さはトレードオフの関係にある。なぜならば、時間刻み幅を小さくしていくと数値解法は安定になりやすくなるが、時間刻み幅が小さいと反復を繰り返して進む時間が短くなってしまい、ある時間だけ先まで数値解を求めようとしたときに、必要な反復回数が増え、計算に時間がかかってしまうためである。



# 課題3

まず、アトラクタの定義を記す。資料[4]によれば、以下の通りである:

$H$: 相空間、すなわち、初期値$u_0 \in H$に対して、時刻$t > 0$における発展方程式の解$u(t) \in H$を対応させる解作用素$S(t) : H \rightarrow H$が定義できる、とする。このとき、

$A \in H$が$(H, \{ S(t) \}_{t \geq 0})$の（グローバル）アトラクタ $\overset{\rm{def}}{\Leftrightarrow}$ 以下の$(1)(2)$を両方とも満たす:

$(1)$ $A$は空でないコンパクト不変集合である。($t\geq 0$に対して$S(t)A = A$)

$(2)$任意の有界集合$X \subset H$を「アトラクト」する。すなわち、${\rm dist} (S(t)X, A) \rightarrow 0 \quad ({\rm as} \; t\rightarrow \infty) $

上の定義から、ある軌道、すなわち点の集合がその系に対するアトラクタであるためには、初期値に依存することなく、任意の解軌道がその軌道に収束しなければならない。しかし、図8と図９を見比べると、初期値を変化させたときの解軌道が異なっており、今回の実験の設定下にある二重振り子のカオスには**アトラクタは存在しない**という結論を得られる。

この考察は、資料[5]を参照すると、保存系全体を対象として、一般化して以下のように述べることができる。

今回の実験で数値シュミレーションを行った二重振り子は、ハミルトニアンが一定であり、エネルギーが保存される系である。保存系のカオスにはアトラクタは存在しない[5]ので、二重振り子のアトラクタは存在しないと考えられる。

現実に二重振り子を動かした場合は、摩擦や空気抵抗により、エネルギーが時間が経つとともに失われる散逸系と考えることができ、静止状態という不動点のアトラクタに収束していくものと考えられる。



# 参考文献

[1] P R Hobson and A N Lansbury. 1996. A simple electronic circuit to demonstrate bifurcation and chaos.

[2] 配布資料「カオスを電子回路でとらえる」 pp. 5, 9, 30-33.（ページ番号は、配布資料の各ページ中央下部に手書きで記されている数字に対応する。）

[3] http://www.hisenkei.net/~tohru/Lectures/2003/NLS/PDFs/mathematical_structures.pdf p.6. 2019/07/11 閲覧.

[4] http://user.numazu-ct.ac.jp/~hmatsu/wakate32/ShingoTakeuchi.pdf p.2. 2019/07/16 閲覧.

[5] https://brain.cc.kogakuin.ac.jp/~kanamaru/Chaos/DP/ 2019/07/11 閲覧.