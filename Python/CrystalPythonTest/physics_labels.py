class CSGBoundarySceneCreateLabels:
   CommandNameLabel="CSGBoundarySceneCreate"
   NewIdLabel="NewId"

class CSGBoundarySceneUpdateLabels:
   CommandNameLabel="CSGBoundarySceneUpdate"
   IdLabel="Id"
   BoundingBoxLabel="BoundingBox"
   NameLabel="Name"

class EmitterSceneCreateLabels:
   CommandNameLabel="EmitterSceneCreateCommand"
   NewIdLabel="NewId"

class EmitterSceneUpdateLabels:
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

class FluidSceneCreateLabels:
   CommandNameLabel="FluidSceneCreateCommand"
   NewIdLabel="NewId"

class FluidSceneToPSLabels:
   CommandNameLabel="FluidSceneToPSCommand"
   FluidIdLabel="FluidId"
   ParticleSystemIdLabel="ParticleSystemId"

class FluidSceneUpdateLabels:
   CommandNameLabel="FluidSceneUpdateCommand"
   IdLabel="Id"
   ParticleSystemIdLabel="ParticleSystemId"
   ParticleRadiusLabel="ParticleRadius"
   StiffnessLabel="Stiffness"
   ViscosityLabel="Viscosity"
   DensityLabel="Density"
   IsBoundary="IsBoundary"
   NameLabel="Name"

class FluidSimulationLabels:
   CommandNameLabel="FluidSimulationCommand"
   SolverIdLabel="SolverId"

class MeshBoundarySceneCreateLabels:
   CommandNameLabel="MeshBoundarySceneCreate"
   NewIdLabel="NewId"

class MeshBoundarySceneUpdateLabels:
   CommandNameLabel="MeshBoundarySceneUpdate"
   IdLabel="Id"
   MeshIdLabel="MeshId"
   NameLabel="Name"

class PhysicsSolverCreateLabels:
   CommandNameLabel="PhysicsSolverCreateCommand"
   NewIdLabel="NewId"

class PhysicsSolverUpdateLabels:
   CommandNameLabel="PhysicsSolverUpdateCommand"
   IdLabel="Id"
   FluidSceneIdsLabel="FluidSceneIds"
   EmitterSceneIdsLabel="EmitterSceneIds"
   CSGBoundarySceneIdsLabel="CSGBoundarySceneIds"
   MeshBoundarySceneIdsLabel="MeshBoundarySceneIds"
   EffectLengthLabel="EffectLength"
   TimeStepLabel="TimeStep"
   NameLabel="Name"

class SPHSurfaceConstructionLabels:
   CommandNameLabel="SPHSurfaceConstructionCommand"
   ParticleSystemIdLabel="ParticleSystemId"
   SparseVolumeIdLabel="SparseVolumeId"
   EffectLengthLabel="EffectLength"
   CellLengthLabel="CellLength"

