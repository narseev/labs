#include "ExampleWindow.h"

#include "Primitives.h"

#include <cmath>

static constexpr double Pi = acos(-1.);


ExampleWindow::ExampleWindow(int width, int height)
: Window(width, height),
  _TextureHouse("TexHouse.png"), _TextureRoof("TexRoof.png"),
  _green("green.png"), _brown("brown.png"), _orange("orange.png")
{

}

void ExampleWindow::setup()
{
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_TEXTURE);

	glClearColor(0.2f, 0.35f, 0.45f, 1.0f);

	glMatrixMode(GL_PROJECTION);
	gluPerspective(45.0, double(width()) / double(height()), 0.1, 30.0);
	glMatrixMode(GL_MODELVIEW);

}

//Куб для дома
static VertexVector s_cube_vertices {
	{  1.0,  8.0,  2.0 },
	{  1.0,  4.0,  2.0 },
	{ -3.0,  4.0,  2.0 },
	{ -3.0,  8.0,  2.0 },
	{  1.0,  8.0,  0.0 },
	{  1.0,  4.0,  0.0 },
	{ -3.0,  4.0,  0.0 },
	{ -3.0,  8.0,  0.0 },
};

static FaceVector s_cube_faces {
	{ 4, 0, 1, 2, 3 },
	{ 4, 7, 6, 5, 4 },
	{ 4, 1, 0, 4, 5 },
	{ 4, 3, 2, 6, 7 },
	{ 4, 0, 3, 7, 4 },
	{ 4, 2, 1, 5, 6 },
};

static NormalVector s_cube_normals {
	{  0.0,  0.0,  1.0 },
	{  0.0,  0.0, -1.0 },
	{  1.0,  0.0,  0.0 },
	{ -1.0,  0.0,  0.0 },
	{  0.0,  1.0,  0.0 },
	{  0.0, -1.0,  0.0 },
};

static ColorVector s_cube_colors {
	{  1.0f,  1.0f,  1.0f },
	{  1.0f,  1.0f,  1.0f },
	{  1.0f,  1.0f,  1.0f },
	{  1.0f,  1.0f,  1.0f },
	{  1.0f,  1.0f,  1.0f },
	{  1.0f,  1.0f,  1.0f },
};

static TexCoordVector s_cube_tex_coords {
	{ { 0.00, 0.00 }, { 0.00, 0.00 }, { 0.00, 0.00 }, { 0.00, 0.00 } },
	{ { 0.00, 0.00 }, { 0.00, 0.00 }, { 0.00, 0.00 }, { 0.00, 0.00 } },
	{ { 0.00, 0.00 }, { 0.50, 0.00 }, { 0.50, 0.50 }, { 0.00, 0.50 } },
	{ { 0.50, 0.50 }, { 1.00, 0.50 }, { 1.00, 1.00 }, { 0.50, 1.00 } },
	{ { 0.50, 0.00 }, { 1.00, 0.00 }, { 1.00, 0.50 }, { 0.50, 0.50 } },
	{ { 0.00, 0.50 }, { 0.50, 0.50 }, { 0.50, 1.00 }, { 0.00, 1.00 } },
};

//Крыша
static VertexVector s_roof_vertices {
	{  1.0,   3.8,  2.0 },
	{  1.0,   8.2,  2.0 },
	{ -3.0,   8.2,  2.0 },
	{ -3.0,   3.8,  2.0 },
	{  1.0,   6.0,  3.2 },
	{ -3.0,   6.0,  3.2 },
};

static FaceVector s_roof_faces {
	{ 4, 0, 1, 2, 3 },
	{ 4, 1, 4, 5, 2 },
	{ 4, 0, 3, 5, 4 },
	{ 3, 0, 4, 1 },
	{ 3, 2, 5, 3 },
};

static NormalVector s_roof_normals {
	{  0.0,  0.0, -1.0 },
	{  0.0,  1.0,  1.0 },
	{  0.0, -1.0,  1.0 },
	{  1.0,  0.0,  0.0 },
	{ -1.0,  0.0,  0.0 },
};

static ColorVector s_roof_colors {
	{  1.0f,  1.0f,  1.0f },
	{  1.0f,  1.0f,  1.0f },
	{  1.0f,  1.0f,  1.0f },
	{  1.0f,  1.0f,  1.0f },
	{  1.0f,  1.0f,  1.0f },
};

static TexCoordVector s_roof_tex_coords {
	{ { 0.00, 0.00 }, { 0.00, 0.00 }, { 0.00, 0.00 }, { 0.00, 0.00 } },
	{ { 0.00, 1.00 }, { 0.00, 0.00 }, { 0.50, 0.00 }, { 0.50, 1.00 } },
	{ { 0.50, 1.00 }, { 0.00, 1.00 }, { 0.00, 0.00 }, { 0.50, 0.00 } },
	{ { 0.50, 1.00 }, { 0.75, 0.7 },  { 1.00, 1.00 } },
	{ { 0.50, 1.00 }, { 0.75, 0.7 },  { 1.00, 1.00 } },
};

//Труба
static VertexVector s_tube_vertices {
	{ -0.25,  4.75, 3.4 },
	{ -0.25,  4.5,  3.4 },
	{ -0.5,   4.5,  3.4 },
	{ -0.5,   4.75, 3.4 },
	{ -0.25,  4.75, 2.0 },
	{ -0.25,  4.5,  2.0 },
	{ -0.5,   4.5,  2.0 },
	{ -0.5,   4.75, 2.0 },
};

static FaceVector s_tube_faces {
	{ 4, 0, 1, 2, 3 },
	{ 4, 7, 6, 5, 4 },
	{ 4, 1, 0, 4, 5 },
	{ 4, 3, 2, 6, 7 },
	{ 4, 0, 3, 7, 4 },
	{ 4, 2, 1, 5, 6 },
};

static NormalVector s_tube_normals {
	{  0.0,  0.0,  1.0 },
	{  0.0,  0.0, -1.0 },
	{  1.0,  0.0,  0.0 },
	{ -1.0,  0.0,  0.0 },
	{  0.0,  1.0,  0.0 },
	{  0.0, -1.0,  0.0 },
};

static ColorVector s_tube_colors {
	{  0.0f,  0.0f,  0.0f },
	{  1.0f,  1.0f,  1.0f },
	{  1.0f,  1.0f,  1.0f },
	{  1.0f,  1.0f,  1.0f },
	{  1.0f,  1.0f,  1.0f },
	{  1.0f,  1.0f,  1.0f },
};

static TexCoordVector s_tube_tex_coords {
	{ { 0.00, 0.00 }, { 0.00, 0.00 }, { 0.00, 0.00 }, { 0.00, 0.00 } },
	{ { 0.00, 0.00 }, { 0.00, 0.00 }, { 0.00, 0.00 }, { 0.00, 0.00 } },
	{ { 0.00, 0.00 }, { 1.00, 0.00 }, { 1.00, 1.00 }, { 0.00, 1.00 } },
	{ { 0.00, 0.00 }, { 1.00, 0.00 }, { 1.00, 1.00 }, { 0.00, 1.00 } },
	{ { 0.00, 0.00 }, { 1.00, 0.00 }, { 1.00, 1.00 }, { 0.00, 1.00 } },
	{ { 0.00, 0.00 }, { 1.00, 0.00 }, { 1.00, 1.00 }, { 0.00, 1.00 } },
};


SimpleModel cube { s_cube_vertices, s_cube_faces, s_cube_normals, s_cube_colors, s_cube_tex_coords };
SimpleModel roof { s_roof_vertices, s_roof_faces, s_roof_normals, s_roof_colors, s_roof_tex_coords };
SimpleModel tube { s_tube_vertices, s_tube_faces, s_tube_normals, s_tube_colors, s_tube_tex_coords };

void ExampleWindow::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity(); // Identity matrix - единичная матрица

	gluLookAt(10.0, 10.0, 10.0,
			  0.0, 0.0, 0.0,
			  0.0, 0.0, 1.0);


	glRotated(_angle, 0.0, 0.0, 1.0);

	_TextureHouse.bind();
	glEnable(GL_TEXTURE_2D);
	draw_model(cube);
	glDisable(GL_TEXTURE_2D);

	_TextureRoof.bind();
	glEnable(GL_TEXTURE_2D);
	draw_model(roof);
	glDisable(GL_TEXTURE_2D);

	_TextureRoof.bind();
	glEnable(GL_TEXTURE_2D);
	draw_model(tube);
	glDisable(GL_TEXTURE_2D);

	_green.bind();
	glEnable(GL_TEXTURE_2D);
	draw_cone_tree(32, 0., 0., 2, 1, 1.0);
	draw_cone_tree(32, 0., 0., 2.5, 1.5, 0.9);
	draw_cone_tree(32, 0., 0., 3.0, 2.0, 0.8);
	draw_cone_tree(32, 0., 0., 3.5, 2.5, 0.7);
	draw_cone_tree(32, 0., 0., 4.0, 3.0, 0.6);
	draw_cone_tree(32, 0., 0., 4.5, 3.5, 0.5);
	draw_cone_tree(32, 0., 0., 5.0, 4.0, 0.4);
	draw_cone_tree(32, 0., 0., 5.5, 4.5, 0.3);
	glDisable(GL_TEXTURE_2D);

	draw_sphere_smooth(64, 32, 2+xx, 2+yy, 0.5+zz, 0.5);
	draw_sphere_smooth(64, 32, 2+xx, 2+yy, 1.2+zz, 0.35);
	draw_sphere_smooth(64, 32, 2+xx, 2+yy, 1.7+zz, 0.2);

	draw_sphere_smooth(64, 32, -2-xx, -2-yy, 0.5+zz, 0.5);
	draw_sphere_smooth(64, 32, -2-xx, -2-yy, 1.2+zz, 0.35);
	draw_sphere_smooth(64, 32, -2-xx, -2-yy, 1.7+zz, 0.2);

	draw_sphere_smooth(32, 16, 0, -4, 0.5, 0.5);
	draw_sphere_smooth(32, 16, 0, -4, 1.2, 0.35);
	draw_sphere_smooth(32, 16, 0, -4, 1.7, 0.2);

	_brown.bind();
	glEnable(GL_TEXTURE_2D);
	draw_prism_smooth(32, 0., 0.);
	glDisable(GL_TEXTURE_2D);

	_orange.bind();
		glEnable(GL_TEXTURE_2D);
		if (k == 1){
			draw_pyramid(32, 2+xx, 1.7+zz, 1.5+yy, 1.9+yy, 0.03);
			draw_pyramid(32, -2-xx, 1.7+zz, -1.5-yy, -1.9-yy, 0.03);
		}if (k == 2){
			draw_cone_orange(32, 1.7+zz, 2+yy, 1.5+xx, 1.9+xx, 0.03);
			draw_cone_orange(32, 1.7+zz, -2-yy, -1.5-xx, -1.9-xx, 0.03);
		}if (k == 3){
			draw_pyramid(32, 2+xx, 1.7+zz, 2.5+yy, 2.1+yy, 0.03);
			draw_pyramid(32, -2-xx, 1.7+zz, -2.5-yy, -2.1-yy, 0.03);
		}if (k == 4){
			draw_cone_orange(32, 1.7+zz, 2+yy, 2.5+xx, 2.1+xx, 0.03);
			draw_cone_orange(32, 1.7+zz, -2-yy, -2.5-xx, -2.1-xx, 0.03);
		}

	draw_pyramid(32, 0, 1.7, -3.5, -4, 0.03);
	glDisable(GL_TEXTURE_2D);

}

void ExampleWindow::draw_model(SimpleModel &model)
{
	for (unsigned i = 0; i < model.faces.size(); ++i) {
		int count = model.faces[i][0];
		if (count == 3)
			glBegin(GL_TRIANGLES);
		else if (count == 4)
			glBegin(GL_QUADS);
		else
			glBegin(GL_POLYGON);

		glNormal3dv(&model.normals[i][0]);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, &model.colors[i][0]);
		for (int j = 1; j <= count; ++j) {
			glTexCoord2dv(&model.tex_coords[i][j-1][0]);
			glVertex3dv(&model.vertices[model.faces[i][j]][0]);
		}

		glEnd();
	}
}

void ExampleWindow::do_logic()
{
	_angle -= 0.5;
	if (_angle >= 360.)
		_angle -= 360.;

	zz += 0.05 * i;
	if (zz >= 0.5) i = -1;
	else if (zz <= 0) i = 1;

	if (k == 1) {
		yy -= 0.05;
		if (yy <= -4) k = 2;
	} else if (k == 2){
		xx -= 0.05;
		if (xx <= -4) k = 3;
	} else if (k == 3){
		yy += 0.05;
		if (yy >= 0) k = 4;
	} else if (k == 4){
		xx += 0.05;
		if (xx >= 0) k = 1;
	}

	_camera_z = 5 + sin(_angle / 45. * Pi) * 6.;
}
