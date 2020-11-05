namespace PG {
	public class CSGBoundarySceneCreateLabels
	{
		public const string CommandNameLabel = "CSGBoundarySceneCreate";
		public const string BoxLabel = "Box";
		public const string NameLabel = "Name";
		public const string NewIdLabel = "NewId";
	}

	public class FluidSceneCreateLabels
	{
		public const string CommandNameLabel = "FluidSceneCreateCommand";
		public const string ParticleSystemIdLabel = "ParticleSystemId";
		public const string StiffnessLabel = "Stiffness";
		public const string ViscosityLabel = "Viscosity";
		public const string IsBoundary = "IsBoundary";
		public const string NameLabel = "Name";
		public const string NewIdLabel = "NewId";
	}

	public class FluidSimulationLabels
	{
		public const string CommandNameLabel = "FluidSimulationCommand";
		public const string FluidSceneIdsLabel = "FluidSceneIds";
		public const string CSGBoundarySceneIdsLabel = "CSGBoundarySceneIds";
		public const string TimeStepLabel = "TimeStep";
	}

}
