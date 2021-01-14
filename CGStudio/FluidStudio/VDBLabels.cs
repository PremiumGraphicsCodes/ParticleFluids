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

	public class VDBMeshCreateLabels
	{
		public const string CommandNameLabel = "VDBMeshCreate";
		public const string PositionsLabel = "Positions";
		public const string TriangleIndicesLabel = "TriangleIndices";
		public const string QuadIndicesIdLabel = "QuadIndices";
		public const string NewVDBMeshIdLabel = "NewVDBMeshId";
	}

	public class VDBMeshToParticleSystemLabels
	{
		public const string CommandNameLabel = "VDBMeshToParticleSystem";
		public const string VDBMeshIdLabel = "VDBMeshId";
		public const string ParticleSystemIdLabel = "ParticleSystemId";
		public const string RadiusLabel = "Radius";
	}

	public class VDBOBJFileReadLabels
	{
		public const string CommandNameLabel = "VDBOBJFileRead";
		public const string FilePathLabel = "FilePath";
		public const string VDBMeshIdLabel = "VDBMeshId";
	}

	public class VDBOBJFileWriteLabels
	{
		public const string CommandNameLabel = "VDBOBJFileWrite";
		public const string VDBMeshIdLabel = "VDBMeshId";
		public const string FilePathLabel = "FilePath";
	}

	public class VDBParticleSystemCreateLabels
	{
		public const string CommandNameLabel = "VDBParticleSystemCreate";
		public const string PositionsLabel = "Positions";
		public const string NewVDBPSIdLabel = "NewVDBPSId";
	}

	public class VDBParticleSystemToMeshLabels
	{
		public const string CommandNameLabel = "VDBParticleSystemToMesh";
		public const string ParticleSystemIdLabel = "ParticleSystemId";
		public const string VDBMeshIdLabel = "VDBMeshId";
		public const string RadiusLabel = "Radius";
	}

}
