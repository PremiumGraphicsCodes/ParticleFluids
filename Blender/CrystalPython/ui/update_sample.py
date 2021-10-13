import bpy
import bmesh

verts = [(1, 1, 1), (0, 0, 0)]  # 2 verts made with XYZ coords
obj = bpy.data.objects["Cube"]  # add a new object using the mesh

mesh = obj.data
bm = bmesh.new()

for v in verts:
    bm.verts.new(v)  # add a new vert

# make the bmesh the object's mesh
bm.to_mesh(mesh)  
bm.free()  # always do this when finished