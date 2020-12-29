namespace PG {
	public class VDBFileReadLabels
	{
		public const string CommandNameLabel = "VDBFileRead";
		public const string FilePathLabel = "FilePath";
		public const string NewIdLabel = "NewId";
	}

	public class VDBFileWriteLabels
	{
		public const string CommandNameLabel = "OpenVDBFileWrite";
		public const string ParticleSystemIdsLabel = "ParticleSystemIds";
		public const string FilePathLabel = "FilePath";
	}

	public class VDBInitLabels
	{
		public const string CommandNameLabel = "VDBInit";
	}

	public class VDBParticleSystemToMeshLabels
	{
		public const string CommandNameLabel = "VDBParticleSystemToMesh";
		public const string ParticleSystemIdLabel = "ParticleSystemId";
		public const string VDBMeshIdLabel = "VDBMeshId";
		public const string RadiusLabel = "Radius";
	}

}
