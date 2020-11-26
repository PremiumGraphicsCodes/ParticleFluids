namespace PG {
	public class CameraGetLabels
	{
		public const string CommandNameLabel = "CameraGet";
		public const string NearLabel = "Near";
		public const string FarLabel = "Far";
		public const string EyePositionLabel = "EyePosition";
		public const string TargetPositionLabel = "TargetPosition";
		public const string UpVectorLabel = "UpVector";
		public const string ProjectionMatrixLabel = "ProjectionMatrix";
		public const string RotationMatrixLabel = "RotationMatrix";
	}

	public class CameraLabels
	{
		public const string CameraFitCommandLabel = "CameraFit";
		public const string CameraXYCommandLabel = "CameraXY";
		public const string CameraYZCommandLabel = "CameraYZ";
		public const string CameraZXCommandLabel = "CameraZX";
		public const string CameraRotateCommandLabel = "CameraRotate";
		public const string MatrixLabel = "Matrix";
		public const string TranslateLabel = "Translate";
		public const string CameraTranslateCommandLabel = "CameraTranslate";
		public const string CameraZoomCommandLabel = "CameraZoom";
		public const string ZoomRatioLabel = "Ratio";
	}

	public class CameraSetLabels
	{
		public const string CommandLabel = "CameraSet";
		public const string NearLabel = "Near";
		public const string FarLabel = "Far";
		public const string EyePositionLabel = "EyePosition";
		public const string TargetPositionLabel = "TargetPosition";
		public const string UpVector = "UpVector";
	}

	public class ClearLabels
	{
		public const string CommandNameLabel = "ClearCommand";
		public const string LayerLabel = "Layer";
	}

	public class DeleteLabels
	{
		public const string CommandNameLabel = "DeleteCommand";
		public const string IdLabel = "Id";
		public const string IsItemLabel = "IsItem";
	}

	public class FileExportLabels
	{
		public const string FileExportCommandLabel = "FileExport";
		public const string FilePathLabel = "FilePath";
	}

	public class FileImportLabels
	{
		public const string FileImportCommandLabel = "FileImport";
		public const string FilePathLabel = "FilePath";
		public const string IsOkLabel = "IsOk";
		public const string NewIdLabel = "NewId";
		public const string STLFileImportCommandLabel = "STLFileImport";
	}

	public class GetLabels
	{
		public const string PositionLabel = "Position";
		public const string SceneCountLabel = "SceneCount";
		public const string SceneListIdsLabel = "SceneListIds";
		public const string MaterialNameLabel = "MaterialName";
	}

	public class GetMatrixLabels
	{
		public const string CommandLabel = "SetMatrix";
		public const string IdLabel = "Id";
		public const string MatrixLabel = "Matrix";
	}

	public class LightCreateLabels
	{
		public const string CommandNameLabel = "LightCreate";
		public const string PositionLabel = "Position";
		public const string AmbientLabel = "Ambient";
		public const string DiffuseLabel = "Diffuse";
		public const string SpecularLabel = "Specular";
		public const string NameLabel = "Name";
		public const string NewIdLabel = "NewId";
	}

	public class LightGetLabels
	{
		public const string CommandNameLabel = "LightGet";
		public const string IdLabel = "Id";
		public const string PositionLabel = "Position";
		public const string AmbientLabel = "Ambient";
		public const string DiffuseLabel = "Diffuse";
		public const string SpecularLabel = "Specular";
		public const string NameLabel = "Name";
	}

	public class LightSetLabels
	{
		public const string CommandNameLabel = "LightSet";
		public const string IdLabel = "Id";
		public const string PositionLabel = "Position";
		public const string AmbientLabel = "Ambient";
		public const string DiffuseLabel = "Diffuse";
		public const string SpecularLabel = "Specular";
		public const string NameLabel = "Name";
	}

	public class MaterialCreateLabels
	{
		public const string CommandNameLabel = "MaterialCreate";
		public const string AmbientLabel = "Ambient";
		public const string DiffuseLabel = "Diffuse";
		public const string SpecularLabel = "Specular";
		public const string ShininessLabel = "Shininess";
		public const string AmbientTextureNameLabel = "AmbientTextureName";
		public const string DiffuseTextureNameLabel = "DiffuseTextureName";
		public const string SpecularTextureNameLabel = "SpecularTextureName";
		public const string NameLabel = "Name";
		public const string NewIdLabel = "NewId";
	}

	public class MaterialGetLabels
	{
		public const string CommandNameLabel = "MaterialGet";
		public const string IdLabel = "Id";
		public const string AmbientLabel = "Ambient";
		public const string DiffuseLabel = "Diffuse";
		public const string SpecularLabel = "Specular";
		public const string ShininessLabel = "Shininess";
		public const string TextureNameLabel = "TextureName";
		public const string NameLabel = "Name";
	}

	public class MaterialSetLabels
	{
		public const string CommandNameLabel = "MaterialSet";
		public const string IdLabel = "Id";
		public const string AmbientLabel = "Ambient";
		public const string DiffuseLabel = "Diffuse";
		public const string SpecularLabel = "Specular";
		public const string ShininessLabel = "Shininess";
		public const string TextureNameLabel = "TextureName";
		public const string NameLabel = "Name";
	}

	public class MockLabels
	{
		public const string MockCommandLabel = "Mock";
	}

	public class NewLabels
	{
		public const string CommandNameLabel = "NewCommand";
	}

	public class OBJFileExportLabels
	{
		public const string CommandNameLabel = "OBJFileExport";
		public const string FilePathLabel = "FilePath";
		public const string IdsLabel = "Ids";
	}

	public class OBJFileImportLabels
	{
		public const string CommandNameLabel = "OBJFileImport";
		public const string FilePathLabel = "FilePath";
		public const string NewIdLabel = "NewId";
	}

	public class ParticleSystemCreateLabels
	{
		public const string ParticleSystemAddLabel = "ParticleSystemAdd";
		public const string PositionsLabel = "Positions";
		public const string PointSizeLabel = "PointSize";
		public const string ColorLabel = "Color";
		public const string NameLabel = "Name";
		public const string LayerLabel = "Layer";
		public const string NewIdLabel = "NewId";
	}

	public class PCDFileExportLabels
	{
		public const string CommandNameLabel = "PCDFileExport";
		public const string FilePathLabel = "FilePath";
		public const string IdsLabel = "Ids";
		public const string IsBinaryLabel = "IsBinary";
	}

	public class PCDFileImportLabels
	{
		public const string CommandNameLabel = "PCDFileImport";
		public const string FilePathLabel = "FilePath";
		public const string NewIdLabel = "NewId";
	}

	public class PickLabels
	{
		public const string PickCommandLabel = "Pick";
		public const string PositionLabel = "Position";
		public const string ParentIdLabel = "ParentId";
		public const string ChildIdLabel = "ChildId";
	}

	public class PolygonMeshCreateLabels
	{
		public const string CommandNameLabel = "PolygonMeshCreate";
		public const string PositionsLabel = "Positions";
		public const string NormalsLabel = "Normals";
		public const string TexCoordsLabel = "TexCoords";
		public const string VerticesLabel = "Vertices";
		public const string FacesLabel = "Faces";
		public const string NameLabel = "Name";
		public const string LayerLabel = "Layer";
		public const string NewIdLabel = "NewId";
	}

	public class PositionGetLabels
	{
		public const string CommandNameLabel = "PositionGet";
		public const string ParentIdLabel = "ParentId";
		public const string ChildIdLabel = "ChildId";
		public const string PositionLabel = "Position";
	}

	public class PublicLabel
	{
	}

	public class SceneGetLabels
	{
		public const string CommandLabel = "SceneGet";
		public const string IdLabel = "Id";
		public const string BoundingBoxLabel = "BoundingBox";
		public const string IsPickableLabel = "IsPickable";
		public const string IsVisibleLabel = "IsVisible";
		public const string NameLabel = "Name";
		public const string TypeLabel = "Type";
	}

	public class SetLabels
	{
		public const string PointSizeLabel = "PointSize";
		public const string IsVisibleLabel = "IsVisible";
		public const string ColorLabel = "Color";
		public const string MaterialNameLabel = "MaterialName";
		public const string NameLabel = "Name";
	}

	public class ShaderBuildLabels
	{
		public const string CommandNameLabel = "ShaderBuild";
		public const string IdLabel = "Id";
	}

	public class ShaderSendLabels
	{
		public const string CommandNameLabel = "ShaderSend";
		public const string IdLabel = "Id";
	}

	public class ShapeSelectLabels
	{
		public const string CommandNameLabel = "ShapeSelectCommand";
		public const string ShapeIdLabel = "ShapeId";
	}

	public class STLFileExportLabels
	{
		public const string CommandNameLabel = "STLFileExport";
		public const string FilePathLabel = "FilePath";
		public const string IdsLabel = "Ids";
		public const string IsBinaryLabel = "IsBinary";
	}

	public class STLFileImportLabels
	{
		public const string CommandNameLabel = "STLFileImport";
		public const string FilePathLabel = "FilePath";
		public const string NewIdLabel = "NewId";
	}

	public class TextureCreateLabels
	{
		public const string CommandNameLabel = "TextureCreate";
		public const string FilePathLabel = "FilePath";
		public const string NameLabel = "Name";
		public const string NewIdLabel = "NewId";
	}

	public class TextureSetLabels
	{
		public const string CommandNameLabel = "TextureSet";
		public const string IdLabel = "Id";
		public const string FilePathLabel = "FilePath";
		public const string IsOkLabel = "IsOk";
	}

	public class TransformLabels
	{
		public const string TransformCommandLabel = "Transform";
		public const string IdLabel = "Id";
		public const string MatrixLabel = "Matrix";
	}

	public class TrimLabels
	{
		public const string TrimCommandLabel = "Trim";
		public const string ShapeIdLabel = "ShapeId";
		public const string SpaceLabel = "Space";
		public const string NewIdLabel = "NewId";
	}

	public class WireFrameCreateLabels
	{
		public const string WireFrameAddLabel = "WireFrameAdd";
		public const string PositionsLabel = "Positions";
		public const string EdgesLabel = "Edges";
		public const string LineWidthLabel = "LineWidth";
		public const string ColorLabel = "Color";
		public const string NameLabel = "Name";
		public const string LayerLabel = "Layer";
		public const string NewIdLabel = "NewId";
	}

}
