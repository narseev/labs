#include "ExampleWindow.h"

#include <stdexcept>
#include <SDL2/SDL_image.h>

ExampleWindow::ExampleWindow(int width, int height):
	Window(width, height),
	_cloud1_x(800), _cloud1_y(30),
	_cloud2_x(0), _cloud2_y(0),

	_redcar1_x(800), _redcar1_y(360),
	_redcar2_x(0), _redcar2_y(360),

	_road_x(0), _road_y(0),
	_road2_x(_width+0), _road2_y(0),

	_sun_x(950), _sun_y(-30),

	_tree_x(600), _tree_y(120),
	_tree2_x(_width+600), _tree2_y(120),

	_car_x(30), _car_y(430),

	_sky_x(0), _sky_y(0),

	_bush_x(_width+100), _bush_y(489),
	_bush2_x(_width*2+100), _bush2_y(489)
{
	_sky = std::shared_ptr<SDL_Texture>(
				IMG_LoadTexture(_renderer.get(), "sky.png"),
				SDL_DestroyTexture);
	_cloud = std::shared_ptr<SDL_Texture>(
				IMG_LoadTexture(_renderer.get(), "cloud.png"),
				SDL_DestroyTexture);
	_forest = std::shared_ptr<SDL_Texture>(
				IMG_LoadTexture(_renderer.get(), "forest.png"),
				SDL_DestroyTexture);
	_road = std::shared_ptr<SDL_Texture>(
				IMG_LoadTexture(_renderer.get(), "road.png"),
				SDL_DestroyTexture);
	_sun = std::shared_ptr<SDL_Texture>(
				IMG_LoadTexture(_renderer.get(), "sun.png"),
				SDL_DestroyTexture);
	_tree = std::shared_ptr<SDL_Texture>(
				IMG_LoadTexture(_renderer.get(), "tree.png"),
				SDL_DestroyTexture);
	_redcar = std::shared_ptr<SDL_Texture>(
					IMG_LoadTexture(_renderer.get(), "redcar.png"),
					SDL_DestroyTexture);
	_car = std::shared_ptr<SDL_Texture>(
				IMG_LoadTexture(_renderer.get(), "car.png"),
				SDL_DestroyTexture);
	_bush = std::shared_ptr<SDL_Texture>(
					IMG_LoadTexture(_renderer.get(), "bush.png"),
					SDL_DestroyTexture);
}

void ExampleWindow::render() {
	SDL_SetRenderDrawColor(_renderer.get(), 32, 32, 96, 255);
	SDL_RenderClear(_renderer.get());

	SDL_SetRenderDrawColor(_renderer.get(), 255, 255, 255, 255);

	SDL_Rect sky_rect { _sky_x, _sky_y, 1200, 600 };
	SDL_RenderCopy(_renderer.get(), _sky.get(), nullptr, &sky_rect);

	SDL_Rect sun_rect { _sun_x, _sun_y, 228, 222 };
	SDL_RenderCopy(_renderer.get(), _sun.get(), nullptr, &sun_rect);

	SDL_Rect cloud1_rect { _cloud1_x, _cloud1_y, 217, 96 };
	SDL_RenderCopy(_renderer.get(), _cloud.get(), nullptr, &cloud1_rect);
	SDL_Rect cloud2_rect { _cloud2_x, _cloud2_y, 247, 116 };
	SDL_RenderCopy(_renderer.get(), _cloud.get(), nullptr, &cloud2_rect);

	SDL_Rect road_rect { _road_x, _road_y, 1200, 600 };
	SDL_RenderCopy(_renderer.get(), _road.get(), nullptr, &road_rect);
	SDL_Rect road2_rect { _road2_x, _road2_y, 1200, 600 };
	SDL_RenderCopy(_renderer.get(), _road.get(), nullptr, &road2_rect);

	SDL_Rect tree_rect { _tree_x, _tree_y, 220, 257 };
	SDL_RenderCopy(_renderer.get(), _tree.get(), nullptr, &tree_rect);
	SDL_Rect tree2_rect { _tree2_x, _tree2_y, 220, 257 };
	SDL_RenderCopy(_renderer.get(), _tree.get(), nullptr, &tree2_rect);

	SDL_Rect redcar1_rect { _redcar1_x, _redcar1_y, 240, 100 };
	SDL_RenderCopy(_renderer.get(), _redcar.get(), nullptr, &redcar1_rect);
	SDL_Rect redcar2_rect { _redcar2_x, _redcar2_y, 240, 100 };
	SDL_RenderCopy(_renderer.get(), _redcar.get(), nullptr, &redcar2_rect);

	SDL_Rect car_rect { _car_x, _car_y, 240, 100 };
	SDL_RenderCopy(_renderer.get(), _car.get(), nullptr, &car_rect);

	SDL_Rect bush_rect { _bush_x, _bush_y, 292, 111};
	SDL_RenderCopy(_renderer.get(), _bush.get(), nullptr, &bush_rect);
	SDL_Rect bush2_rect { _bush2_x, _bush2_y, 292, 111};
	SDL_RenderCopy(_renderer.get(), _bush.get(), nullptr, &bush2_rect);
}

void ExampleWindow::do_logic() {

	_cloud1_x=_cloud1_x+1;
		if (_cloud1_x >= width())
			_cloud1_x = -256;
	_cloud2_x=_cloud2_x+1;
		if (_cloud2_x >= width())
			_cloud2_x = -256;

	_redcar1_x=_redcar1_x-4;
		if (_redcar1_x <= -250)
			_redcar1_x = 1500;
	_redcar2_x=_redcar2_x-4;
		if (_redcar2_x <= -250)
			_redcar2_x = 1500;

		_tree_x=_tree_x-2;
		if (_tree_x <= -250)
			_tree_x = 1500;
		_tree2_x=_tree2_x-2;
		if (_tree2_x <= -250)
			_tree2_x = 1500;

		_bush_x=_bush_x-8;
		if (_bush_x <= -250)
			_bush_x = 1500;
		_bush2_x=_bush2_x-8;
		if (_bush2_x <= -250)
			_bush2_x = 1500;

		_road_x--; if (_road_x <= -width()) _road_x = _road_x+(_width*2);

		_road2_x--; if (_road2_x <= -width()) _road2_x = _road2_x+(_width*2);

}

void ExampleWindow::handle_keys(const Uint8 *keys) {
	if (keys[SDL_SCANCODE_RIGHT]){
		_car_x=_car_x+3;
		}
	if (keys[SDL_SCANCODE_LEFT]){
		_car_x=_car_x-2;
	}
}
