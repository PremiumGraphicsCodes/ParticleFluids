# ParticleFluids Tutorial

2022 premiumgraphics

## インストール
Microsoft社のHPからVisualStudio2019ランタイム(x64)をインストールします．

[VisualC++runtime](https://docs.microsoft.com/ja-jp/cpp/windows/latest-supported-vc-redist?view=msvc-170
 "VisualC++runtime")

下にあるX64を選択します．

## 構成
本アドオンはソルバー本体と，OpenVDBツールから構成されています．
シミュレーション自体はOpenVDBを用いることなく実行できますが，
プリ、ポストまでBlender上で完結させることができます．

## シミュレーションの流れ
下図に示すように，MeshからParticleを生成し，それに物理属性を付与し，シミュレーションを行います．

```mermaid
graph TB
  A[MeshToParticles] --> B[Simulation]
  B --> C[ConvertToVDB]
  C --> D[VDBToMesh]
```


## チュートリアル Hello, Fluids!

### Particlesデータの作成

- Blenderデフォルトで生成されている[Cube]を選択し
- [Object Properties]から，[ScaleX],[ScaleY],[ScaleZ]をそれぞれ10,10,10とします．


![Mesh](./images/Mesh.png) 

- [Cube]を選択したまま，[VDBTools]->[MeshToPS]->[Voxelize]を押します．
- するとツリー上に[Object]という頂点だけのパーティクルオブジェクトが現れます．

![MeshToPS](./images/MeshToPS.PNG) 

### Fluidデータの作成

- 先ほど作成した[Object]を選択し，[Physics Properties]タブを開きます．
- [PFFluid]ボタンを押します．
- パラメータ設定用タブが開きます．
- ここではそのままデフォルト値を用います．

![MeshToPS](./images/Fluid.PNG) 

### シミュレーションの開始

 - [PFSolver]タブを開きます．
 - [ExportPath]で出力されるシミュレーションデータのディレクトリを設定します．
 - [Start]ボタンでシミュレーションが開始されます．
 - [Render]チェックボックスにチェックをつけておくと，シミュレーション途中のParticleの動きを確認できます．
![Start](./images/Start.PNG) 

### 結果の確認

 - [ExportPath]で設定したフォルダにplyファイルが連番で出力されているので，それを確認します．
 - Blenderでimportすると，落下していく様子が確認できます．

### 障害物の作成
この時点では障害物（床）がないため，粒子が落ちていくだけです．
現実的には障害物を設定しておく必要があります．
本アドオンでは，障害物の設定もFluidと同様に行うことができます．

- [Add]->[Mesh]->[Plane]で床にする平面を新たに作成します．
![StaticMesh](./images/StaticMesh.PNG) 
[Object Properties]から[Scale]を[20,20,1]とします．
流体下部に置きたいので，LocationのZ[-20]とします．

同様にして[Voxelize]を実行してParticlesに変換します．
![StaticMesh](./images/StaticPS.png) 

**ここで[Static]チェックボックスをマークしてください**

### 再びシミュレーションの開始
[PFSolver]タブを開き，[Start]ボタンでシミュレーションが開始されます．
今度は設定した床でParticlesが跳ね返っていることが確認できます．
![StaticMesh](./images/StaticEnd.png) 

### VDBボリュームへの変換
[PFSolver]->[Start]を押すとダイアログが表示されます．
ここで先ほど出力したplyファイルを選択します．
(BlenderではCtrl+Aで全選択できます)
![PSToVolume](./images/PSToVolume.png) 
[Convert]ボタンを押すとコンバート処理が始まり，同じフォルダにVDB形式のデータが作成されます．

### Meshing
Blender標準の機能で連番のOpenVDBファイルを入力として扱うことができます．
![VDBImport](./images/VDBImport.PNG) 

### レンダリング



## それから
自由にParticleSystemを追加したり削除したりして自分のCGを作ってみてください．