# ParticleFluids Tutorial

2022/03/31 

# Install
First of all, please visit the URL and download Visual Studio2019 runtime(x64).

[VisualC++runtime](https://docs.microsoft.com/ja-jp/cpp/windows/latest-supported-vc-redist?view=msvc-170
 "VisualC++runtime")

![Runtime](./images/InstallRuntime.png) 


# Configuration

This add-on consists of solver and OpenVDB tools.

Simulation itself can be done without OpenVDB.

However, using our OpenVDB tool, you can do whole process including pre, post processing.


## Flow of Simulation

```mermaid
graph TB
  A[MeshToParticles] --> B[Simulation]
  B --> C[ConvertToVDB]
  C --> D[VDBToMesh]
```

## Tutorial1 Hello Fluids!

## Creating Fluid

- Select [Cube] in Blender's default mesh,
- Select [Object Properties]，and set values [ScaleX],[ScaleY],[ScaleZ]to[10,10,10]．

![Mesh](./images/Mesh.png) 

- Keep selecting [Cube]，push [VDBTools]->[MeshToPS]->[Voxelize]．
- Converted points can be shown in [Object], which has no faces, can be appeared．

![MeshToPS](./images/MeshToPS.png) 

To simulate fluids, you have to add parameters to the particles.

- Select [Object]，and open [Physics Properties] tab．
- Push [PFFluid] button．
- You can set parameters．
- In this case, use default value.
![PSToFluid](./images/Fluid.png) 

## Adding Obstacle
On this add-on, you can set obstacles same as fluids.

- Make a plane with [Add]->[Mesh]->[Plane]．
![StaticMesh](./images/StaticMesh.png) 

- Select[Object Properties] tab, and change [Scale] to [20,20,1], and [Location]  to [0, 0,-20].

- This plane must convert to points with same as above.[VDBTools]->[MeshToPS]->[Voxelize].
![StaticMesh](./images/StaticPS.png) 

- **Please check [Static] chekck box**

### Start Simulation

 - Open [PFSolver] tab．
 - Set export directory on [ExportPath].
 - Press [Start] button, then simulation starts!
 - If you check [Render] checkbox, you can check particle's movements.

![StaticMesh](./images/StaticEnd.png) 

### Convert to VDB volume

- [PFTools]->[ToVDB], a dialog will be appeared.
- Select .ply files generated above.(On Blender, you can select all files with Ctrl+A)
![PSToVolume](./images/PSToVolume.png) 
- Then push [Convert] button, starts converts, and .vdb files are generated in the same directory.

### Meshing
Blender supports OpenVDB requential file import.
![VDBImport](./images/VDBImport.png) 
![VolumeToMesh](./images/VolumeToMesh.png) 

