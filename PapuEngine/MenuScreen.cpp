#include "MenuScreen.h"
#include "MyScreens.h"
#include "Game.h"
#include <iostream>


MenuScreen::MenuScreen(Window* window):
	_window(window), btnGameClicked(false)
{
	_screenIndex = SCREEN_INDEX_MENU;
}

void MenuScreen::initGUI() {
}

void MenuScreen::initSystem() {
	_program.compileShaders("Shaders/colorShaderVert.txt",
							"Shaders/colorShaderFrag.txt");
	_program.addAtribute("vertexPosition");
	_program.addAtribute("vertexColor");
	_program.addAtribute("vertexUV");
	_program.linkShader();
}

void MenuScreen::destroy() {
	delete button;
	delete background;
	delete spriteFont;
}

void MenuScreen::onExit() {}

void MenuScreen::onEntry() {
	initSystem();
	initGUI();
	camera.init(_window->getScreenWidth(), _window->getScreenHeight());
	camera.setPosition(
		glm::vec2(
			_window->getScreenWidth() / 2.0f,
			_window->getScreenHeight() / 2.0f)
	);
	//isClicked = false;
	_spriteBatch.init();
	background = new Background("Textures/game.png");
	spriteFont = new SpriteFont("Fonts/signature.ttf",64);
	button = new Button("Textures/menu_button.png");
}

void MenuScreen::update(){
	camera.update();
	checkInput();
}

void MenuScreen::checkInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		_game->onSDLEvent(event);
	}
	if (_game->_inputManager.isKeyDown(SDL_BUTTON_LEFT)) {
		if (!isClicked && button->clicked(
			_game->_inputManager.getMouseCoords())) {
			//cambio de pantalla
			isClicked = true;
			_currentState = ScreenState::CHANGE_NEXT;
		}
	}
}

void MenuScreen::draw() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_program.use();
	glActiveTexture(GL_TEXTURE0);
	GLuint pLocation = _program.getUniformLocation("P");
	glm::mat4 cameraMatrix = camera.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	GLuint imageLocation = _program.getUniformLocation("myImage");
	glUniform1i(imageLocation, 0);
	_spriteBatch.begin();
	background->draw(_spriteBatch);
	button->draw(_spriteBatch);
	_spriteBatch.end();
	_spriteBatch.renderBatch();
	char buffer[256];
	_spriteBatch.begin();
	sprintf(
		buffer, "ELLA SE FUE :'v"
	);
	spriteFont->draw(_spriteBatch, buffer,
		glm::vec2(250, 100), glm::vec2(0.5), 0.0f,
		ColorRGBA(255, 255, 255, 255)
		);
	_spriteBatch.end();
	_spriteBatch.renderBatch();
	glBindTexture(GL_TEXTURE_2D, 0);
	_program.unuse();
}

void MenuScreen::build() {}

int MenuScreen::getPreviousScreen() const {
	return SCREEN_INDEX_NO_SCREEN;
}

int MenuScreen::getNextScreen() const {
	return SCREEN_INDEX_GAME;
}

MenuScreen::~MenuScreen()
{
}
