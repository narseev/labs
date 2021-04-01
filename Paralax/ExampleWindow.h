#ifndef EXAMPLEWINDOW_H_
#define EXAMPLEWINDOW_H_

#include "Window.h"

class ExampleWindow: public Window
{
protected:
	std::shared_ptr<SDL_Texture> _cloud,_forest,_road,_sun,_tree,_car,_redcar,_sky,_bush;
	int _cloud1_x, _cloud1_y,
		_cloud2_x, _cloud2_y,
		_road_x, _road_y, _road2_x, _road2_y,
		_sun_x, _sun_y,
		_tree_x, _tree_y, _tree2_x, _tree2_y,
		_car_x, _car_y,
		_redcar1_x, _redcar1_y,_redcar2_x, _redcar2_y,
		_sky_x, _sky_y,
		_bush_x, _bush_y, _bush2_x, _bush2_y;



public:
	ExampleWindow(
			int width = DEFAULT_WIDTH,
			int height = DEFAULT_HEIGHT);
	virtual ~ExampleWindow() = default;
	virtual void render() override;
	virtual void do_logic() override;
	virtual void handle_keys(const Uint8 *keys) override;
};

#endif /* EXAMPLEWINDOW_H_ */
