#pragma once
#ifndef EXAMPLEWINDOW_H_
#define EXAMPLEWINDOW_H_

#include <GL/gl.h>
#include <GL/glu.h>

#include "Window.h"

#include "Texture.h"

#include <vector>

using VertexVector = std::vector<std::vector<double>>;
using FaceVector = std::vector<std::vector<int>>;
using NormalVector = std::vector<std::vector<double>>;
using ColorVector = std::vector<std::vector<float>>;
using TexCoordVector = std::vector<std::vector<std::vector<double>>>;

struct SimpleModel
{
	VertexVector & vertices;
	FaceVector & faces;
	NormalVector & normals;
	ColorVector & colors;
	TexCoordVector & tex_coords;
};


class ExampleWindow: public Window
{
protected:
	double _camera_z { 0. };
	double _angle { 0. };
	double zz = 0., i = 1, k = 1;
	double xx = 0, yy = 0;

	Texture _TextureHouse;
	Texture _TextureRoof;
	Texture _green;
	Texture _brown;
	Texture _orange;

	void draw_model(SimpleModel &model);

public:
	ExampleWindow(int width = DEFAULT_WIDTH, int height = DEFAULT_HEIGHT);
	virtual ~ExampleWindow() = default;

	virtual void setup() override;
	virtual void render() override;
	virtual void do_logic() override;
};

#endif /* EXAMPLEWINDOW_H_ */
