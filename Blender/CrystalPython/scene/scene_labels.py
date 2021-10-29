class CameraCreateCommand:
   CommandNameLabel="CameraCreate"
   NewIdLabel="NewId"
class CameraFitCommand:
   CameraFitCommandLabel="CameraFit"
   CameraXYCommandLabel="CameraXY"
   CameraYZCommandLabel="CameraYZ"
   CameraZXCommandLabel="CameraZX"
class CameraGetCommand:
   CommandNameLabel="CameraGet"
   NearLabel="Near"
   FarLabel="Far"
   EyePositionLabel="EyePosition"
   TargetPositionLabel="TargetPosition"
   UpVectorLabel="UpVector"
   ProjectionMatrixLabel="ProjectionMatrix"
   RotationMatrixLabel="RotationMatrix"
class CameraRotateCommand:
   CameraRotateCommandLabel="CameraRotate"
   MatrixLabel="Matrix"
class CameraSetCommand:
   CommandLabel="CameraSet"
   NearLabel="Near"
   FarLabel="Far"
   EyePositionLabel="EyePosition"
   TargetPositionLabel="TargetPosition"
   UpVector="UpVector"
class CameraTranslateCommand:
   TranslateLabel="Translate"
   CameraTranslateCommandLabel="CameraTranslate"
class CameraZoomCommand:
   CameraZoomCommandLabel="CameraZoom"
   ZoomRatioLabel="Ratio"
class ClearCommand:
   CommandNameLabel="ClearCommand"
   LayerLabel="Layer"
class DeleteCommand:
   CommandNameLabel="DeleteCommand"
   IdLabel="Id"
   IsItemLabel="IsItem"
class FileExportCommand:
   FileExportCommandLabel="FileExport"
   FilePathLabel="FilePath"
class FileImportCommand:
   FileImportCommandLabel="FileImport"
   FilePathLabel="FilePath"
   IsOkLabel="IsOk"
   NewIdLabel="NewId"
   STLFileImportCommandLabel="STLFileImport"
class GetCommand:
   PositionLabel="Position"
   SceneCountLabel="SceneCount"
   SceneListIdsLabel="SceneListIds"
   MaterialNameLabel="MaterialName"
class LightCreateCommand:
   CommandNameLabel="LightCreate"
   PositionLabel="Position"
   AmbientLabel="Ambient"
   DiffuseLabel="Diffuse"
   SpecularLabel="Specular"
   NameLabel="Name"
   NewIdLabel="NewId"
class LightGetCommand:
   CommandNameLabel="LightGet"
   IdLabel="Id"
   PositionLabel="Position"
   AmbientLabel="Ambient"
   DiffuseLabel="Diffuse"
   SpecularLabel="Specular"
   NameLabel="Name"
class LightSetCommand:
   CommandNameLabel="LightSet"
   IdLabel="Id"
   PositionLabel="Position"
   AmbientLabel="Ambient"
   DiffuseLabel="Diffuse"
   SpecularLabel="Specular"
   NameLabel="Name"
class MaterialCreateCommand:
   CommandNameLabel="MaterialCreate"
   AmbientLabel="Ambient"
   DiffuseLabel="Diffuse"
   SpecularLabel="Specular"
   ShininessLabel="Shininess"
   AmbientTextureNameLabel="AmbientTextureName"
   DiffuseTextureNameLabel="DiffuseTextureName"
   SpecularTextureNameLabel="SpecularTextureName"
   NameLabel="Name"
   NewIdLabel="NewId"
class MaterialGetCommand:
   CommandNameLabel="MaterialGet"
   IdLabel="Id"
   AmbientLabel="Ambient"
   DiffuseLabel="Diffuse"
   SpecularLabel="Specular"
   ShininessLabel="Shininess"
   TextureNameLabel="TextureName"
   NameLabel="Name"
class MaterialSetCommand:
   CommandNameLabel="MaterialSet"
   IdLabel="Id"
   AmbientLabel="Ambient"
   DiffuseLabel="Diffuse"
   SpecularLabel="Specular"
   ShininessLabel="Shininess"
   TextureNameLabel="TextureName"
   NameLabel="Name"
class MockCommand:
   MockCommandLabel="Mock"
class NewCommand:
   CommandNameLabel="NewCommand"
class OBJFileExportCommand:
   CommandNameLabel="OBJFileExport"
   FilePathLabel="FilePath"
   IdsLabel="Ids"
class OBJFileImportCommand:
   CommandNameLabel="OBJFileImport"
   FilePathLabel="FilePath"
   NewIdLabel="NewId"
class ParticleSystemCreateCommand:
   ParticleSystemAddLabel="ParticleSystemAdd"
   PositionsLabel="Positions"
   PointSizeLabel="PointSize"
   ColorLabel="Color"
   NameLabel="Name"
   LayerLabel="Layer"
   NewIdLabel="NewId"
class ParticleSystemGetCommand:
   CommandNameLabel="ParticleSystemGet"
   PSIdLabel="PSId"
   LayerLabel="Layer"
   PositionsLabel="Positions"
   PointSizeLabel="PointSize"
   ColorLabel="Color"
   NameLabel="Name"
class ParticleSystemSetCommand:
   CommandNameLabel="ParticleSystemSet"
   IdLabel="Id"
   PositionsLabel="Positions"
   PointSizeLabel="PointSize"
   ColorLabel="Color"
   NameLabel="Name"
   LayerLabel="Layer"
   NewIdLabel="NewId"
class PCDFileExportCommand:
   CommandNameLabel="PCDFileExport"
   FilePathLabel="FilePath"
   IdsLabel="Ids"
   IsBinaryLabel="IsBinary"
class PCDFileImportCommand:
   CommandNameLabel="PCDFileImport"
   FilePathLabel="FilePath"
   NewIdLabel="NewId"
class PickCommand:
   PickCommandLabel="Pick"
   PositionLabel="Position"
   ParentIdLabel="ParentId"
   ChildIdLabel="ChildId"
class PolygonMeshAddFacesCommand:
   CommandNameLabel="PolygonMeshAddFaces"
   PolygonMeshIdLabel="PolygonMeshId"
   VertexIdsLabel="VertexIds"
class PolygonMeshAddVerticesCommand:
   CommandNameLabel="PolygonMeshAddVertices"
   PolygonMeshIdLabel="PolygonMeshId"
   PositionIdsLabel="PositionIds"
   NormalIdsLabel="NormalIds"
   TexCoordIdsLabel="TexCoordIds"
class PolygonMeshCreateCommand:
   CommandNameLabel="PolygonMeshCreate"
   PositionsLabel="Positions"
   NormalsLabel="Normals"
   TexCoordsLabel="TexCoords"
   NameLabel="Name"
   LayerLabel="Layer"
   NewIdLabel="NewId"
class PresenterSetCommand:
   CommandNameLabel="PresenterSet"
   IdLabel="Id"
   PresenterNameLabel="PresenterName"
class SceneGetCommand:
   CommandLabel="SceneGet"
   IdLabel="Id"
   BoundingBoxLabel="BoundingBox"
   IsPickableLabel="IsPickable"
   IsVisibleLabel="IsVisible"
   NameLabel="Name"
   TypeNameLabel="TypeName"
class SceneSetCommand:
   CommandNameLabel="SceneSet"
   IdLabel="Id"
   NameLabel="Name"
class ShaderBuildCommand:
   CommandNameLabel="ShaderBuild"
   IdLabel="Id"
class ShaderSendCommand:
   CommandNameLabel="ShaderSend"
   IdLabel="Id"
class ShapeSelectCommand:
   CommandNameLabel="ShapeSelectCommand"
   ShapeIdLabel="ShapeId"
class SolidCreateCommand:
   ParticleSystemAddLabel="SolidCreate"
   BoxLabel="Box"
   ColorLabel="Color"
   NameLabel="Name"
   LayerLabel="Layer"
   NewIdLabel="NewId"
class STLFileExportCommand:
   CommandNameLabel="STLFileExport"
   FilePathLabel="FilePath"
   IdsLabel="Ids"
   IsBinaryLabel="IsBinary"
class STLFileImportCommand:
   CommandNameLabel="STLFileImport"
   FilePathLabel="FilePath"
   NewIdLabel="NewId"
class TextureCreateCommand:
   CommandNameLabel="TextureCreate"
   FilePathLabel="FilePath"
   NameLabel="Name"
   NewIdLabel="NewId"
class TextureSetCommand:
   CommandNameLabel="TextureSet"
   IdLabel="Id"
   FilePathLabel="FilePath"
   IsOkLabel="IsOk"
class TransformCommand:
   TransformCommandLabel="Transform"
   IdLabel="Id"
   MatrixLabel="Matrix"
class TriangleMeshCreateCommand:
   CommandNameLabel="TriangleMeshCreate"
   TrianglesLabel="Triangles"
   NameLabel="Name"
   LayerLabel="Layer"
   NewIdLabel="NewId"
class TriangleMeshGetCommand:
   CommandNameLabel="TriangleMeshGet"
   MeshIdLabel="MeshId"
   LayerLabel="Layer"
   TrianglesLabel="Triangles"
   NormalsLabel="Normals"
   NameLabel="Name"
class TriangleMeshSetCommand:
   CommandNameLabel="TriangleMeshSet"
   MeshIdLabel="MeshId"
   TrianglesLabel="Triangles"
class TrimCommand:
   TrimCommandLabel="Trim"
   ShapeIdLabel="ShapeId"
   SpaceLabel="Space"
   NewIdLabel="NewId"
class TXTFileExportCommand:
   CommandNameLabel="TXTFileExport"
   FilePathLabel="FilePath"
   IdsLabel="Ids"
class TXTFileImportCommand:
   CommandNameLabel="TXTFileImport"
   FilePathLabel="FilePath"
   IdLabel="Id"
class WireFrameCreateCommand:
   WireFrameCreateLabel="WireFrameCreate"
   PositionsLabel="Positions"
   EdgeIndicesLabel="EdgeIndices"
   LineWidthLabel="LineWidth"
   ColorLabel="Color"
   NameLabel="Name"
   LayerLabel="Layer"
   NewIdLabel="NewId"
