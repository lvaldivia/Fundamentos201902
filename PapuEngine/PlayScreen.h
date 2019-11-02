#pragma once
#include "IGameScreen.h"
#include "Camera2D.h"
#include "GLS_Program.h"
#include "Window.h"
#include "SpriteBacth.h"
#include "GLTexture.h"
#include "SpriteFont.h"
#include "Background.h"

class PlayScreen: public IGameScreen
{
private:
	Camera2D camera;
	Background* background;
	GLS_Program _program;
	Window* _window = nullptr;
	SpriteBacth _spriteBatch;
	SpriteBacth _hudBach;
	SpriteFont* _spriteFont;
	void drawHUD();
public:
	PlayScreen(Window* window);
	virtual void build() override;
	virtual void destroy() override;
	virtual void onExit() override;
	virtual void onEntry() override;
	virtual void initGUI() override;
	virtual void draw() override;
	virtual void update()override;
	virtual void initSystem()override;
	virtual int getNextScreen() const override;
	virtual int getPreviousScreen() const override;
	virtual void checkInput() override;
	~PlayScreen();
};

