# ParticleFluids Tutorial 1 Hello, Fluids!

2022/03/31 

## Fluidの作成

- Blenderデフォルトで生成されている[Cube]を選択し
- [Object Properties]から，[Scale]をそれぞれ[10,10,10]とします．

![Mesh](./images/Mesh.png) 

- [Cube]を選択したまま，[VDBTools]->[MeshToPS]->[Voxelize]を押します．
- するとツリー上に[Object]という頂点だけのパーティクルオブジェクトが現れます．

![MeshToPS](./images/MeshToPS.png) 

- 作成した[Object]を選択し，[Physics Properties]タブを開きます．
- [PFFluid]ボタンを押します．
- パラメータ設定用タブが開きます．
- ここではそのままデフォルト値を用います．

![MeshToPS](./images/Fluid.png) 

## シミュレーションの開始

 - [PFSolver]タブを開きます．
 - [Min]を[0,0,-3]とします．
 - [ExportPath]で出力されるシミュレーションデータのディレクトリを設定します．
 - [Start]ボタンでシミュレーションが開始されます．
 - [Render]チェックボックスにチェックをつけておくと，シミュレーション途中のParticleの動きを確認できます．
![StaticMesh](./images/Start.png) 

## VDBボリュームへの変換

 - [PFSolver]->[Start]を押すとダイアログが表示されます．
 - 先ほど出力したplyファイルを選択します．(BlenderではCtrl+Aで全選択できます)
 - [Convert]ボタンを押すとコンバート処理が始まり，同じフォルダにVDB形式のデータが作成されます．
![PSToVolume](./images/PSToVolume.png) 

## Meshing
Blender標準の機能で連番のOpenVDBファイルを入力として扱うことができます．
![VDBImport](./images/VDBImport.png) 
![VolumeToMesh](./images/VolumeToMesh.png) 

ボリュームデータからメッシュへの変換は，[Cube]を選択し，
[Modifier Properties]->[AddModifier]->[VolumeToMesh]



## レンダリング
あとは通常のMeshと同じです．
Blenderのマテリアル設定を行えばレンダリングできます．
