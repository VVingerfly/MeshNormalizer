# MeshNormalizer #
-------------------------------------

Uniformly scale a triangle mesh, then move the center of bounding box to a given position.

## Dependency
- [OpenMesh](http://www.openmesh.org/)

## Usage
- `meshNormalizer in.obj`
    Scale the mesh *in.obj* such that the maximum edge length of bounding box is `2` and the center of bounding box is `(0, 0, 0)`. The scaled mesh is saved with the name of *in_.obj*

- `meshNormalizer in.obj s cx cy cz`
    Scale the mesh *in.obj* such that the maximum edge length of bounding box is `s` and the center of bounding box is `(cx, cy, cz)`. The scaled mesh is saved with the name of *in_.obj*

- `meshNormalizer in.obj s cx cy cz out.obj`
    Scale the mesh *in.obj* such that the maximum edge length of bounding box is `s` and the center of bounding box is `(cx, cy, cz)`. The scaled mesh is saved with the name of *out.obj*



