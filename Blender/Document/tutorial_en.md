# ParticleFluids Tutorial

2021 premiumgraphics

## 画面構成
The Particle Fluids has 4 tabs on Blender window.

- PFFluid
- PFBoundary
- PFSolver
- PFTools

## Tutorial1

### Create Source Mesh
[]

### Create Particle System

Particleデータを作成します。
ポリゴンを選択し，[PFTools]->[Voxelizer]と選択します。
ここで[DivideLength]を[0.1],[Name]を[FluidSource01]とします。
するとツリー上に[FluidSource01]というオブジェクトが現れます．

### Fluidデータの作成

### Create Fluid Object
[PFFluid]->[Add]で新しいFluidを作ります．
先ほど作成した[FluidSource01]を選択し，[SetSource]ボタンを押します．
[Name]を[Fluid01]とします．

### Solverの設定
[PFSolver]で[Fluid01]，[]

### Boundaryの作成

## チュートリアル2
Box以外のBoundaryも追加してみましょう．
本アドオンにおいては，Fluidの作成と同様にBoundaryを追加することができます．

### Particleデータの作成
