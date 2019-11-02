#include "PlayScreen.h"
#include "Game.h"
#include "MyScreens.h"



PlayScreen::PlayScreen(Window* window):_window(window)
{
}


PlayScreen::~PlayScreen()
{
}

void PlayScreen::initGUI() {
	
}

void PlayScreen::initSystem() {
	_program.compileShaders("Shaders/colorShaderVert.txt",
		"Shaders/colorShaderFrag.txt");
	_program.addAtribute("vertexPosition");
	_program.addAtribute("vertexColor");
	_program.addAtribute("vertexUV");
	_program.linkShader();
}

void PlayScreen::destroy() {
	
}

void PlayScreen::onExit() {}

void PlayScreen::onEntry() {
	initSystem();
	initGUI();
}



void PlayScreen::update() {
	checkInput();
}

void PlayScreen::checkInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		_game->onSDLEvent(event);
	}
}

void PlayScreen::draw() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void PlayScreen::drawHUD() {
	
}

void PlayScreen::build() {}

int PlayScreen::getPreviousScreen() const {
	return SCREEN_INDEX_MENU;
}

int PlayScreen::getNextScreen() const {
	return SCREEN_INDEX_OVER;
}
