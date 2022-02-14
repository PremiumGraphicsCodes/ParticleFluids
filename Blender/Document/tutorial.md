# ParticleFluids Tutorial

2022 premiumgraphics

## インストール
Microsoft社のHPからVisualStudio2019ランタイム(x64)をインストールします．

本アドオンはソルバー本体と，OpenVDBツールから構成されています．
シミュレーション自体はOpenVDBを用いることなく実行できますが，
プリ、ポストまでBlender上で完結させることができます．

## チュートリアル1 Hello, Fluids!

### Particle Systemデータの作成

- Blenderデフォルトの[Cube]の[ScaleX],[ScaleY],[ScaleZ]をそれぞれ10,10,10とします．
- [Cube]を選択したまま，[Voxelizer]->[MeshToPS]を選択し，[Convert]を押します．
- するとツリー上に[ParticleSystem01]というオブジェクトが現れます．

![MeshToPS](/images/MeshToPS.PNG) 

### Fluidデータの作成

- 先ほど作成した[ParticleSystem01]を選択し，[Physics]タブを開きます．
- [ParticleFluids]ボタンを押します．
- パラメータ設定用タブが開きます．

![MeshToPS](/images/Fluid.PNG) 

### シミュレーションの開始
[PFSolver]タブでSolverを追加します．
[Start]ボタンでシミュレーションが開始されます．
[ExportPath]で出力されるシミュレーションデータのディレクトリを設定します．
plyファイルが連番で出力されてます．

### VDBボリュームへの変換
[PFSolver]タブでSolverを追加します．
[Start]ボタンでシミュレーションが開始されます．
[ExportPath]で出力されるシミュレーションデータのディレクトリを設定します．

### Meshing
Blender標準の機能で連番のOpenVDBファイルを入力として扱うことができます．

## チュートリアル2 Add Boundary

### 障害物の作成
[PFBoundary]タブでBoundaryを追加します．
今回は[-1,-1,-1],[1,1,1]のBoxのままにします．
[Name]を[Boundary01]とします．
するとツリー上に[Boundary01]というオブジェクトが現れます．


## それから
自由にParticleSystemを追加したり削除したりして自分のCGを作ってみてください．