# ParticleFluids Tutorial

2021 premiumgraphics

## 画面構成
タブが4つあります．

- PFFluid
- PFBoundary
- PFSolver
- PFTools

## シミュレーションの流れ

## データ構造

### Particle Systemデータの作成

Particleデータを作成します。
ポリゴンを選択し，[PFTools]->[Voxelizer]と選択します．
ここではBlenderデフォルトの[Cube]をそのまま用います．
ここで[DivideLength]を[0.1],[Name]を[FluidSource01]とします。
するとツリー上に[FluidSource01]というオブジェクトが現れます．

### Fluidデータの作成

[PFFluid]->[Add]で新しいFluidを作ります．
先ほど作成した[FluidSource01]を選択し，[SetSource]ボタンを押します．
[Name]を[Fluid01]とします．
するとツリー上に[Fluid01]というオブジェクトが現れます．

### Boundaryの作成
[PFBoundary]タブでBoundaryを追加します．
今回は[-1,-1,-1],[1,1,1]のBoxのままにします．
[Name]を[Boundary01]とします．
するとツリー上に[Boundary01]というオブジェクトが現れます．

### シミュレーションの開始
[PFSolver]タブでSolverを追加します．
[Start]ボタンでシミュレーションが開始されます．
[ExportPath]で出力されるシミュレーションデータのディレクトリを設定します．

### Meshing
作成されたファイルはParticleSystemデータであるため，ポリゴン化をする必要があります．
[PFTools]に[PSSeqMeshing]を選び，先ほど出力したディレクトリを，[ImportPath]で設定します．

