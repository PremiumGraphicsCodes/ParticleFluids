class CSGBoundarySceneCreateCommand:
   CommandNameLabel="CSGBoundarySceneCreate"
   NewIdLabel="NewId"
class CSGBoundarySceneUpdateCommand:
   CommandNameLabel="CSGBoundarySceneUpdate"
   IdLabel="Id"
   BoundingBoxLabel="BoundingBox"
   NameLabel="Name"
class EmitterSceneCreateCommand:
   CommandNameLabel="EmitterSceneCreateCommand"
   NewIdLabel="NewId"
class EmitterSceneUpdateCommand:
   CommandNameLabel="EmitterSceneUpdateCommand"
   IdLabel="Id"
   ParticleSystemIdLabel="ParticleSystemId"
   ParticleRadiusLabel="ParticleRadius"
   StiffnessLabel="Stiffness"
   ViscosityLabel="Viscosity"
   InitialVelocityLabel="InitialVelocity"
   DensityLabel="Density"
   NameLabel="Name"
   StartStepLabel="StartStep"
   EndStepLabel="EndStep"
   IntervalLabel="Interval"
class FluidSceneCreateCommand:
   CommandNameLabel="FluidSceneCreateCommand"
   NewIdLabel="NewId"
class FluidSceneToPSCommand:
   CommandNameLabel="FluidSceneToPSCommand"
   FluidIdLabel="FluidId"
   ParticleSystemIdLabel="ParticleSystemId"
class FluidSceneUpdateCommand:
   CommandNameLabel="FluidSceneUpdateCommand"
   IdLabel="Id"
   ParticleSystemIdLabel="ParticleSystemId"
   ParticleRadiusLabel="ParticleRadius"
   StiffnessLabel="Stiffness"
   ViscosityLabel="Viscosity"
   VorticityLabel="Vorticity"
   DensityLabel="Density"
   IsBoundary="IsBoundary"
   NameLabel="Name"
class FluidSimulationCommand:
   CommandNameLabel="FluidSimulationCommand"
   SolverIdLabel="SolverId"
class MeshBoundarySceneCreateCommand:
   CommandNameLabel="MeshBoundarySceneCreate"
   NewIdLabel="NewId"
class MeshBoundarySceneUpdateCommand:
   CommandNameLabel="MeshBoundarySceneUpdate"
   IdLabel="Id"
   MeshIdLabel="MeshId"
   NameLabel="Name"
class MVPSurfaceConstructionCommand:
   CommandNameLabel="MPVSurfaceConstructionCommand"
   VolumeParticleSystemIdLabel="VolumeParticleSystemId"
   MassParticleSystemIdLabel="MassParticleSystemId"
   TriangleMeshIdLabel="TriangleMeshId"
   ParticleRadiusLabel="ParticleRadius"
   ThresholdLabel="Threshold"
class PhysicsSolverCreateCommand:
   CommandNameLabel="PhysicsSolverCreateCommand"
   NewIdLabel="NewId"
class PhysicsSolverExportCommand:
   CommandNameLabel="PhysicsSolverExportCommand"
   FluidIdsLabel="FluidIds"
   FilePathLabel="FilePath"
   DoExportMicroLabel="DoExportMicro"
class PhysicsSolverUpdateCommand:
   CommandNameLabel="PhysicsSolverUpdateCommand"
   IdLabel="Id"
   FluidSceneIdsLabel="FluidSceneIds"
   EmitterSceneIdsLabel="EmitterSceneIds"
   CSGBoundarySceneIdsLabel="CSGBoundarySceneIds"
   EffectLengthLabel="EffectLength"
   ExternalForceLabel="ExternalForce"
   TimeStepLabel="TimeStep"
   NameLabel="Name"
class SPHSurfaceConstructionCommand:
   CommandNameLabel="SPHSurfaceConstructionCommand"
   ParticleSystemIdLabel="ParticleSystemId"
   TriangleMeshIdLabel="TriangleMeshId"
   ParticleRadiusLabel="ParticleRadius"
   CellLengthLabel="CellLength"
   ThresholdLabel="Threshold"
   IsIsotropicLabel="IsIsotoropic"
