#include "ModelTools.h"
//#include "Enum.h"
#include <math.h>
#include "Matrix.h"
#include <assert.h>
#include "Model.h"
#include "d3dUtil.h"

/****************
***   CUBES   ***
****************/
/// Creates the unit box centered at the origin
void ModelTools::CreateUnitBox(StandardVertex *&pVerts, int& nverts, TriangleByIndex *&pTriList, int& ntri)
{
	nverts = 24;
	pVerts = new StandardVertex[nverts];
	ntri = 12;
	pTriList = new TriangleByIndex[ntri];

	// Setting up faces
	// Forward
	int vind = 0;
	int tind = 0;
	// Position, Normal, Struct
	// Normal (0, 0, 1)
	pVerts[vind].set(0.5f, 0.5f, 0.5f, Vect(0, 0, 1), Colors::Black);
	pVerts[vind + 1].set(-0.5f, 0.5f, 0.5f, Vect(0, 0, 1), Colors::Black);
	pVerts[vind + 2].set(-0.5f, -0.5f, 0.5f, Vect(0, 0, 1), Colors::Black);
	pVerts[vind + 3].set(0.5f, -0.5f, 0.5f, Vect(0, 0, 1), Colors::Black);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Back
	// Normal (0, 0, -1)
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, Vect(0, 0, -1), Colors::Lime);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, Vect(0, 0, -1), Colors::Lime);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, Vect(0, 0, -1), Colors::Lime);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, Vect(0, 0, -1), Colors::Lime);
	pTriList[tind].set(vind + 2, vind + 1, vind);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind);

	// Left
	// Normal (1, 0, 0)
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, Vect(1, 0, 0), Colors::Yellow);
	pVerts[vind + 1].set(0.5f, 0.5f, 0.5f, Vect(1, 0, 0), Colors::Yellow);
	pVerts[vind + 2].set(0.5f, -0.5f, 0.5f, Vect(1, 0, 0), Colors::Yellow);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, Vect(1, 0, 0), Colors::Yellow);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Right
	// Normal (-1, 0, 0)
	vind += 4;
	tind += 2;
	pVerts[vind].set(-0.5f, 0.5f, 0.5f, Vect(-1, 0, 0), Colors::Red);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, Vect(-1, 0, 0), Colors::Red);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, Vect(-1, 0, 0), Colors::Red);
	pVerts[vind + 3].set(-0.5f, -0.5f, 0.5f, Vect(-1, 0, 0), Colors::Red);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Top
	// Normal (0, 1, 0)
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, Vect(0, 1, 0), Colors::Blue);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, Vect(0, 1, 0), Colors::Blue);
	pVerts[vind + 2].set(-0.5f, 0.5f, 0.5f, Vect(0, 1, 0), Colors::Blue);
	pVerts[vind + 3].set(0.5f, 0.5f, 0.5f, Vect(0, 1, 0), Colors::Blue);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Bottom
	// Normal (0, -1, 0)
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, -0.5f, 0.5f, Vect(0, -1, 0), Colors::Magenta);
	pVerts[vind + 1].set(-0.5f, -0.5f, 0.5f, Vect(0, -1, 0), Colors::Magenta);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, Vect(0, -1, 0), Colors::Magenta);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, Vect(0, -1, 0), Colors::Magenta);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);
}

void ModelTools::CreateUnitBoxRepTexture(StandardVertex *&pVerts, int& nverts, TriangleByIndex *&pTriList, int& ntri)
{
	nverts = 24;
	pVerts = new StandardVertex[nverts];
	ntri = 12;
	pTriList = new TriangleByIndex[ntri];


	// Setting up faces
	// Forward
	int vind = 0;
	int tind = 0;
	pVerts[vind].set(0.5f, 0.5f, 0.5f, 1, 0, 0, 0, 1);
	pVerts[vind + 1].set(-0.5f, 0.5f, 0.5f, 0, 0, 0, 0, 1);
	pVerts[vind + 2].set(-0.5f, -0.5f, 0.5f, 0, 1, 0, 0, 1);
	pVerts[vind + 3].set(0.5f, -0.5f, 0.5f, 1, 1, 0, 0, 1);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Back
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 0, 0, 0, 0, -1);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 1, 0, 0, 0, -1);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 1, 1, 0, 0, -1);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 0, 1, 0, 0, -1);
	pTriList[tind].set(vind + 2, vind + 1, vind);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind);

	// Left
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 1, 0, 1, 0, 0);
	pVerts[vind + 1].set(0.5f, 0.5f, 0.5f, 0, 0, 1, 0, 0);
	pVerts[vind + 2].set(0.5f, -0.5f, 0.5f, 0, 1, 1, 0, 0);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 1, 1, 1, 0, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Right
	vind += 4;
	tind += 2;
	pVerts[vind].set(-0.5f, 0.5f, 0.5f, 1, 0, -1, 0, 0);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 0, 0, -1, 0, 0);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 0, 1, -1, 0, 0);
	pVerts[vind + 3].set(-0.5f, -0.5f, 0.5f, 1, 1, -1, 0, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Top
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 1, 0, 0, 1, 0);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 0, 0, 0, 1, 0);
	pVerts[vind + 2].set(-0.5f, 0.5f, 0.5f, 0, 1, 0, 1, 0);
	pVerts[vind + 3].set(0.5f, 0.5f, 0.5f, 1, 1, 0, 1, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Bottom
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, -0.5f, 0.5f, 1, 0, 0, -1, 0);
	pVerts[vind + 1].set(-0.5f, -0.5f, 0.5f, 0, 0, 0, -1, 0);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 0, 1, 0, -1, 0);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 1, 1, 0, -1, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);
}

void ModelTools::CreateUnitBoxSixFaceTexture(StandardVertex *&pVerts, int& nverts, TriangleByIndex *&pTriList, int& ntri)
{
	nverts = 24;
	pVerts = new StandardVertex[nverts];
	ntri = 12;
	pTriList = new TriangleByIndex[ntri];

	// Setting up faces
	// Forward
	int vind = 0;
	int tind = 0;
	// Position, Norm, UV
	pVerts[vind].set(0.5f, 0.5f, 0.5f, 0.25f, 0.625f, Vect(0, 0, 1));
	pVerts[vind + 1].set(-0.5f, 0.5f, 0.5f, 0.25f, 0.375f, Vect(0, 0, 1));
	pVerts[vind + 2].set(-0.5f, -0.5f, 0.5f, 0, 0.375f, Vect(0, 0, 1));
	pVerts[vind + 3].set(0.5f, -0.5f, 0.5f, 0, 0.625f, Vect(0, 0, 1));
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Back
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 0.5f, 0.625f, Vect(0, 0, -1));
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 0.5f, 0.375f, Vect(0, 0, -1));
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 0.75f, 0.375f, Vect(0, 0, -1));
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 0.75f, 0.625f, Vect(0, 0, -1));
	pTriList[tind].set(vind + 2, vind + 1, vind);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind);

	// Left
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, .5f, 0.625f, Vect(1, 0, 0));
	pVerts[vind + 1].set(0.5f, 0.5f, 0.5f, 0.25f, 0.625f, Vect(1, 0, 0));
	pVerts[vind + 2].set(0.5f, -0.5f, 0.5f, 0.25f, 0.875f, Vect(1, 0, 0));
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, .5f, 0.875f, Vect(1, 0, 0));
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Right
	vind += 4;
	tind += 2;
	pVerts[vind].set(-0.5f, 0.5f, 0.5f, 0.25f, 0.375f, Vect(-1, 0, 0));
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 0.5f, 0.375f, Vect(-1, 0, 0));
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 0.5f, 0.125f, Vect(-1, 0, 0));
	pVerts[vind + 3].set(-0.5f, -0.5f, 0.5f, 0.25f, 0.125f, Vect(-1, 0, 0));
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Top
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 0.5f, 0.375f, Vect(0, 1, 0));
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 0.5f, 0.625f, Vect(-1, 0, 0));
	pVerts[vind + 2].set(-0.5f, 0.5f, 0.5f, 0.25f, 0.625f, Vect(-1, 0, 0));
	pVerts[vind + 3].set(0.5f, 0.5f, 0.5f, 0.25f, 0.375f, Vect(-1, 0, 0));
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Bottom
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, -0.5f, 0.5f, 1, 0.625f, Vect(0, -1, 0));
	pVerts[vind + 1].set(-0.5f, -0.5f, 0.5f, 1, 0.375f, Vect(0, -1, 0));
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 0.75f, 0.375f, Vect(0, -1, 0));
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 0.75f, 0.625f, Vect(0, -1, 0));
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);
}

void ModelTools::CreateUnitSkyBox(StandardVertex *&pVerts, int& nverts, TriangleByIndex *&pTriList, int& ntri, float scale)
{
	nverts = 24;
	pVerts = new StandardVertex[nverts];
	ntri = 12;
	pTriList = new TriangleByIndex[ntri];

	// Setting up faces
	// Forward
	int vind = 0;
	int tind = 0;

	float onethird = 0.3333333333333f;
	float twothird = 0.666666666666f;

	pVerts[vind].set(scale, scale, scale, 0.25f, onethird, Vect(0, 0, -1));
	pVerts[vind + 1].set(-scale, scale, scale, 0, onethird, Vect(0, 0, -1));
	pVerts[vind + 2].set(-scale, -scale, scale, 0, twothird, Vect(0, 0, -1));
	pVerts[vind + 3].set(scale, -scale, scale, 0.25f, twothird, Vect(0, 0, -1));
	pTriList[tind].set(vind + 2, vind + 1, vind);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind);

	// Back
	vind += 4;
	tind += 2;
	pVerts[vind].set(-scale, scale, -scale, 0.75f, onethird, Vect(0, 0, 1));
	pVerts[vind + 1].set(scale, scale, -scale, 0.5f, onethird, Vect(0, 0, 1));
	pVerts[vind + 2].set(scale, -scale, -scale, 0.5f, twothird, Vect(0, 0, 1));
	pVerts[vind + 3].set(-scale, -scale, -scale, 0.75f, twothird, Vect(0, 0, 1));
	pTriList[tind].set(vind + 2, vind + 1, vind);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind);

	// Left
	vind += 4;
	tind += 2;
	pVerts[vind].set(scale, scale, -scale, .5f, onethird, Vect(-1, 0, 0));
	pVerts[vind + 1].set(scale, scale, scale, 0.25f, onethird, Vect(-1, 0, 0));
	pVerts[vind + 2].set(scale, -scale, scale, 0.25f, twothird, Vect(-1, 0, 0));
	pVerts[vind + 3].set(scale, -scale, -scale, .5f, twothird, Vect(-1, 0, 0));
	pTriList[tind].set(vind + 2, vind + 1, vind);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind);

	// Right
	vind += 4;
	tind += 2;
	pVerts[vind].set(-scale, scale, scale, 1, onethird, Vect(1, 0, 0));
	pVerts[vind + 1].set(-scale, scale, -scale, 0.75f, onethird, Vect(1, 0, 0));
	pVerts[vind + 2].set(-scale, -scale, -scale, 0.75f, twothird, Vect(1, 0, 0));
	pVerts[vind + 3].set(-scale, -scale, scale, 1, twothird, Vect(1, 0, 0));
	pTriList[tind].set(vind + 2, vind + 1, vind);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind);

	// Top
	vind += 4;
	tind += 2;
	pVerts[vind].set(scale, scale, -scale, 0.5f, onethird, Vect(0, -1, 0));
	pVerts[vind + 1].set(-scale, scale, -scale, 0.5f, 0.0f, Vect(0, -1, 0));
	pVerts[vind + 2].set(-scale, scale, scale, 0.25f, 0.f, Vect(0, -1, 0));
	pVerts[vind + 3].set(scale, scale, scale, 0.25f, onethird, Vect(0, -1, 0));
	pTriList[tind].set(vind, vind + 2, vind + 1);
	pTriList[tind + 1].set(vind, vind + 3, vind + 2);

	// Bottom
	vind += 4;
	tind += 2;
	pVerts[vind].set(scale, -scale, scale, 0.25, twothird, Vect(0, 1, 0));
	pVerts[vind + 1].set(-scale, -scale, scale, 0.25, 1, Vect(0, 1, 0));
	pVerts[vind + 2].set(-scale, -scale, -scale, 0.5, 1, Vect(0, 1, 0));
	pVerts[vind + 3].set(scale, -scale, -scale, 0.5f, twothird, Vect(0, 1, 0));
	pTriList[tind].set(vind, vind + 2, vind + 1);
	pTriList[tind + 1].set(vind, vind + 3, vind + 2);
}

/*******************
***   PYRAMIDS   ***
*******************/

void ModelTools::CreateUnitPyramid(StandardVertex *&pVerts, int& nverts, TriangleByIndex *&pTriList, int& ntri)
{
	nverts = 5;
	pVerts = new StandardVertex[nverts];
	ntri = 6;
	pTriList = new TriangleByIndex[ntri];

	pVerts[0].set(+0.0f, +0.5f, +0.0f, Colors::Black);	// top
	pVerts[1].set(-0.5f, -0.5f, +0.5f, Colors::Lime);	// front left
	pVerts[2].set(+0.5f, -0.5f, +0.5f, Colors::Yellow); // front right
	pVerts[3].set(-0.5f, -0.5f, -0.5f, Colors::Red);	// back left
	pVerts[4].set(+0.5f, -0.5f, -0.5f, Colors::Blue);	// back right
														// Left face
	pTriList[0].set(0, 3, 1); // top, back left, front left

							  // Front face
	pTriList[1].set(0, 1, 2); // top, front left, front right

							  // Right face
	pTriList[2].set(0, 2, 4); // top, front right, back right

							  // Back face
	pTriList[3].set(0, 4, 3); // top, back right, back left

							  // Bottom face
	pTriList[4].set(1, 3, 4); // back left, front left, front right
	pTriList[5].set(1, 4, 2); // back left, front right, back right
}

void ModelTools::CreateUnitPyramidRepTexture(StandardVertex *&pVerts, int& nverts, TriangleByIndex *&pTriList, int& ntri)
{
	nverts = 16;
	pVerts = new StandardVertex[nverts];
	ntri = 6;
	pTriList = new TriangleByIndex[ntri];

	/*
	pVerts[0].set(0.0f, 0.5f, 0.0f, Colors::Black);	// top
	pVerts[1].set(0.5f, -0.5f, -0.5f, Colors::Lime);	// front left
	pVerts[2].set(-0.5f, -0.5f, -0.5f, Colors::Yellow); // front right
	pVerts[3].set(0.5f, -0.5f, 0.5f, Colors::Red);	// back left
	pVerts[4].set(-0.5f, -0.5f, 0.5f, Colors::Blue);	// back right

	// converted to uv mappings
	pVerts[0].set(0.0f, 0.5f, 0.0f, 0.5f, 0 );	// top
	pVerts[1].set(-0.5f, -0.5f, 0.5f, 0, 1);	// front left
	pVerts[2].set(0.5f, -0.5f, 0.5f, 1, 1); // front right
	pVerts[3].set(-0.5f, -0.5f, -0.5f, 1, 1);	// back left
	pVerts[4].set(0.5f, -0.5f, -0.5f, 0, 1);	// back right

	// Left face
	pTriList[0].set(0, 3, 1); // top, back left, front left

	// Front face
	pTriList[1].set(0, 1, 2); // top, front left, front right

	// Right face
	pTriList[2].set(0, 2, 4); // top, front right, back right

	// Back face
	pTriList[3].set(0, 4, 3); // top, back right, back left

	// Bottom face
	pTriList[4].set(1, 3, 4); // back left, front left, front right
	pTriList[5].set(1, 4, 2); // back left, front right, back right\
	*/

	// Verts are (x, y, z, u, v)
	// u and v are range [0, 1], starting in top left corner of texture (in DX)
	
	Vect p1;
	Vect p2;
	Vect p3;
	Vect Normal;

	// Setting up faces
	// Forward (into screen)
	int vertIndex = 0;
	int triIndex = 0;

	p1.set(0.0f, 0.5f, 0.0f);
	p2.set(0.5f, -0.5f, -0.5f);
	p3.set(-0.5f, -0.5f, -0.5f);
	Normal = ((p2 - p1).cross(p3 - p1)).getNorm();

	pVerts[vertIndex].set(p1.X(), p1.Y(), p1.Z(), 0.5f, 0, Normal);
	pVerts[vertIndex + 1].set(p2.X(), p2.Y(), p2.Z(), 0, 1, Normal);
	pVerts[vertIndex + 2].set(p3.X(), p3.Y(), p3.Z(), 1, 1, Normal);
	pTriList[triIndex].set(vertIndex, vertIndex + 1, vertIndex + 2);

	// Back (coming out of screen)
	vertIndex += 3;
	triIndex += 1;

	p1.set(0.0f, 0.5f, 0.0f);
	p2.set(-0.5f, -0.5f, 0.5f);
	p3.set(0.5f, -0.5f, 0.5f);
	Normal = ((p2 - p1).cross(p3 - p1)).getNorm();

	pVerts[vertIndex].set(p1.X(), p1.Y(), p1.Z(), 0.5f, 0, Normal);
	pVerts[vertIndex + 1].set(p2.X(), p2.Y(), p2.Z(), 0, 1, Normal);
	pVerts[vertIndex + 2].set(p3.X(), p3.Y(), p3.Z(), 1, 1, Normal);
	pTriList[triIndex].set(vertIndex, vertIndex + 1, vertIndex + 2);

	// Left
	vertIndex += 3;
	triIndex += 1;

	p1.set(0.0f, 0.5f, 0.0f);
	p2.set(-0.5f, -0.5f, -0.5f);
	p3.set(-0.5f, -0.5f, 0.5f);
	Normal = ((p2 - p1).cross(p3 - p1)).getNorm();

	pVerts[vertIndex].set(p1.X(), p1.Y(), p1.Z(), 0.5f, 0, Normal);
	pVerts[vertIndex + 1].set(p2.X(), p2.Y(), p2.Z(), 0, 1, Normal);
	pVerts[vertIndex + 2].set(p3.X(), p3.Y(), p3.Z(), 1, 1, Normal);
	pTriList[triIndex].set(vertIndex, vertIndex + 1, vertIndex + 2);

	// Right
	vertIndex += 3;
	triIndex += 1;

	p1.set(0.0f, 0.5f, 0.0f);
	p2.set(0.5f, -0.5f, 0.5f);
	p3.set(0.5f, -0.5f, -0.5f);
	Normal = ((p2 - p1).cross(p3 - p1)).getNorm();

	pVerts[vertIndex].set(p1.X(), p1.Y(), p1.Z(), 0.5f, 0, Normal);
	pVerts[vertIndex + 1].set(p2.X(), p2.Y(), p2.Z(), 0, 1, Normal);
	pVerts[vertIndex + 2].set(p3.X(), p3.Y(), p3.Z(), 1, 1, Normal);
	pTriList[triIndex].set(vertIndex, vertIndex + 1, vertIndex + 2);

	// Bottom faces
	vertIndex += 3;
	triIndex += 1;

	p1.set(-0.5f, -0.5f, 0.5f);
	p2.set(-0.5f, -0.5f, -0.5f);
	p3.set(0.5f, -0.5f, -0.5f);
	//Normal = ((p2 - p1).cross(p3 - p1)).getNorm();

	pVerts[vertIndex].set(p1.X(), p1.Y(), p1.Z(), 1, 1, Vect(0, -1, 0));
	pVerts[vertIndex + 1].set(p2.X(), p2.Y(), p2.Z(), 0, 1, Vect(0, -1, 0));
	pVerts[vertIndex + 2].set(p3.X(), p3.Y(), p3.Z(), 0, 0, Vect(0, -1, 0));
	pVerts[vertIndex + 3].set(0.5f, -0.5f, 0.5f, 1, 0, Vect(0, -1, 0));
	pTriList[triIndex].set(vertIndex, vertIndex + 1, vertIndex + 2);
	pTriList[triIndex + 1].set(vertIndex, vertIndex + 2, vertIndex + 3);
}

/******************
***   SPHERES   ***
******************/

void ModelTools::CreateUnitSphere(int vslice, int hslice, StandardVertex *&pVerts, int& nverts, TriangleByIndex *&pTriList, int& ntri)
{
	nverts = (vslice * hslice) + 1;
	ntri = 2 * vslice*(hslice - 1);

	//float pi = MATH_PI;

	pVerts = new StandardVertex[nverts];

	const float pi_1 = MATH_PI / vslice;
	const float pi_2 = MATH_2PI / hslice;

	/****************
	***   VERTS   ***
	****************/
	for (int j = 0; j < vslice; j++)
	{
		const float sin1 = sinf(pi_1 *j);
		const float cos1 = cosf(pi_1 *j);

		for (int i = 0; i < hslice; i++)
		{
			const float sin2 = sinf(pi_2 *i);
			const float cos2 = cosf(pi_2 *i);


			const float x = sin1 * cos2;
			const float y = cos1;
			const float z = sin1 * sin2;

			const float u = ((float)j / vslice) * 1.0f;
			const float v = (1.0f - (float)(i + 1.0f) / (i + 1.0f)*1.0f);

			pVerts[i + (j*hslice)].set(x, y, z, u, v, x, y, z);
		}
	}
	pVerts[vslice*hslice].set(0.0f, -1.0f, 0.0f, 0, 0, 0.0f, -1.0f, 0.0f);

	pTriList = new TriangleByIndex[ntri];
	int i = 0;

	
	/********************
	***   TOP SLICE   ***
	********************/
	int tri_1 = hslice + 1;//first
	int tri_2 = hslice + 1;//second
	int tri_3 = hslice;//last
	for (int j = 0; j < hslice - 1; j++)
	{
		pTriList[i++].set(0, tri_2++, tri_3++);

	}
	pTriList[i++].set(0, hslice, (2 * hslice) - 1);


	/***********************
	***   MIDDLE SLICE   ***
	***********************/
	for (int k = 1; k < vslice - 1; k++)
	{
		tri_1 = hslice * k + 1;
		tri_2 = tri_1 + hslice - 1;
		tri_3 = hslice * k;
		for (int j = 0; j < hslice - 1; j++)
		{
			pTriList[i++].set(tri_1, tri_2++, tri_3);
			pTriList[i++].set(tri_1++, tri_2, tri_3 + hslice);
			tri_3++;
		}
		tri_1 = hslice * k;
		pTriList[i++].set(tri_1, tri_2++, tri_3);
		tri_2 = hslice + (hslice*k);
		pTriList[i++].set(tri_1, tri_2, tri_3 + hslice);
	}

	/***********************
	***   BOTTOM SLICE   ***
	***********************/
	tri_1 = hslice * vslice;
	tri_2 = tri_1 - 2;
	tri_3 = tri_1 - 1;
	for (int j = 0; j < hslice - 1; j++)
	{
		pTriList[i++].set(tri_1, tri_2--, tri_3--);
	}
	pTriList[i++].set(tri_1, tri_1 - 1, tri_1 - hslice);
}