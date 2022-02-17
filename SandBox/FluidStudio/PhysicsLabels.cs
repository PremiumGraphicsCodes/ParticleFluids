namespace PG {
	public class CSGBoundarySceneCreateLabels
	{
		public const string CommandNameLabel = "CSGBoundarySceneCreate";
		public const string NewIdLabel = "NewId";
	}

	public class CSGBoundarySceneUpdateLabels
	{
		public const string CommandNameLabel = "CSGBoundarySceneUpdate";
		public const string IdLabel = "Id";
		public const string BoundingBoxLabel = "BoundingBox";
		public const string NameLabel = "Name";
	}

	public class EmitterSceneCreateLabels
	{
		public const string CommandNameLabel = "EmitterSceneCreateCommand";
		public const string NewIdLabel = "NewId";
	}

	public class EmitterSceneUpdateLabels
	{
		public const string CommandNameLabel = "EmitterSceneUpdateCommand";
		public const string IdLabel = "Id";
		public const string ParticleSystemIdLabel = "ParticleSystemId";
		public const string ParticleRadiusLabel = "ParticleRadius";
		public const string StiffnessLabel = "Stiffness";
		public const string ViscosityLabel = "Viscosity";
		public const string InitialVelocityLabel = "InitialVelocity";
		public const string DensityLabel = "Density";
		public const string NameLabel = "Name";
		public const string StartStepLabel = "StartStep";
		public const string EndStepLabel = "EndStep";
		public const string IntervalLabel = "Interval";
	}

	public class FluidSceneCreateLabels
	{
		public const string CommandNameLabel = "FluidSceneCreateCommand";
		public const string NewIdLabel = "NewId";
	}

	public class FluidSceneToPSLabels
	{
		public const string CommandNameLabel = "FluidSceneToPSCommand";
		public const string FluidIdLabel = "FluidId";
		public const string ParticleSystemIdLabel = "ParticleSystemId";
	}

	public class FluidSceneUpdateLabels
	{
		public const string CommandNameLabel = "FluidSceneUpdateCommand";
		public const string IdLabel = "Id";
		public const string ParticleSystemIdLabel = "ParticleSystemId";
		public const string ParticleRadiusLabel = "ParticleRadius";
		public const string StiffnessLabel = "Stiffness";
		public const string ViscosityLabel = "Viscosity";
		public const string DensityLabel = "Density";
		public const string IsBoundary = "IsBoundary";
		public const string NameLabel = "Name";
	}

	public class FluidSimulationLabels
	{
		public const string CommandNameLabel = "FluidSimulationCommand";
		public const string SolverIdLabel = "SolverId";
	}

	public class MeshBoundarySceneCreateLabels
	{
		public const string CommandNameLabel = "MeshBoundarySceneCreate";
		public const string NewIdLabel = "NewId";
	}

	public class MeshBoundarySceneUpdateLabels
	{
		public const string CommandNameLabel = "MeshBoundarySceneUpdate";
		public const string IdLabel = "Id";
		public const string MeshIdLabel = "MeshId";
		public const string NameLabel = "Name";
	}

	public class PhysicsSolverCreateLabels
	{
		public const string CommandNameLabel = "PhysicsSolverCreateCommand";
		public const string NewIdLabel = "NewId";
	}

	public class PhysicsSolverUpdateLabels
	{
		public const string CommandNameLabel = "PhysicsSolverUpdateCommand";
		public const string IdLabel = "Id";
		public const string FluidSceneIdsLabel = "FluidSceneIds";
		public const string EmitterSceneIdsLabel = "EmitterSceneIds";
		public const string CSGBoundarySceneIdsLabel = "CSGBoundarySceneIds";
		public const string MeshBoundarySceneIdsLabel = "MeshBoundarySceneIds";
		public const string EffectLengthLabel = "EffectLength";
		public const string TimeStepLabel = "TimeStep";
		public const string NameLabel = "Name";
	}

	public class SPHSurfaceConstructionLabels
	{
		public const string CommandNameLabel = "SPHSurfaceConstructionCommand";
		public const string ParticleSystemIdLabel = "ParticleSystemId";
		public const string SparseVolumeIdLabel = "SparseVolumeId";
		public const string EffectLengthLabel = "EffectLength";
		public const string CellLengthLabel = "CellLength";
	}

}
