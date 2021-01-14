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

	public class VDBParticleSystemToMeshLabels
	{
		public const string CommandNameLabel = "VDBParticleSystemToMesh";
		public const string ParticleSystemIdLabel = "ParticleSystemId";
		public const string VDBMeshIdLabel = "VDBMeshId";
		public const string RadiusLabel = "Radius";
	}

	public class VDBSceneCreateLabels
	{
		public const string CommandNameLabel = "VDBSceneCreate";
		public const string SceneTypeLabel = "SceneType";
		public const string SceneType_VDBPointsLabel = "VDBPoints";
		public const string SceneType_VDBMeshLabel = "VDBMesh";
		public const string SceneType_VDBVolumeLabel = "VDBVolu,e";
		public const string NewIdLabel = "NewId";
	}

}
