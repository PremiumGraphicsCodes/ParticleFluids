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
		public const string VDBVolumeIdsLabel = "VDBVolumeIds";
		public const string FilePathLabel = "FilePath";
	}

	public class VDBInitLabels
	{
		public const string CommandNameLabel = "VDBInit";
	}

	public class VDBMeshToVolumeLabels
	{
		public const string CommandNameLabel = "VDBMeshToVolume";
		public const string VDBMeshIdLabel = "VDBMeshId";
		public const string VDBVolumeIdLabel = "VDBVolumeId";
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

	public class VDBPSToVolumeLabels
	{
		public const string CommandNameLabel = "VDBParticleSystemToMesh";
		public const string ParticleSystemIdLabel = "ParticleSystemId";
		public const string VolumeIdLabel = "VolumeId";
		public const string RadiusLabel = "Radius";
	}

	public class VDBSceneCreateLabels
	{
		public const string CommandNameLabel = "VDBSceneCreate";
		public const string SceneTypeLabel = "SceneType";
		public const string SceneType_VDBPointsLabel = "VDBPoints";
		public const string SceneType_VDBMeshLabel = "VDBMesh";
		public const string SceneType_VDBVolumeLabel = "VDBVolume";
		public const string NameLabel = "Name";
		public const string NewIdLabel = "NewId";
		public const string PositionsLabel = "Positions";
	}

	public class VDBVolumeToMeshLabels
	{
		public const string CommandNameLabel = "VDBVolumeToMesh";
		public const string VolumeIdLabel = "VolumeId";
		public const string VDBMeshIdLabel = "VDBMeshId";
	}

	public class VDBVolumeToPSLabels
	{
		public const string CommandNameLabel = "VDBVolumeToPS";
		public const string VDBVolumeIdLabel = "VDBVolumeId";
		public const string VDBParticleSystemIdLabel = "VDBParticleSystemId";
		public const string RadiusLabel = "Radius";
	}

}
