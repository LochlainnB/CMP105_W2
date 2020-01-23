#include "Level.h"

Level::Level(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;
	input->setMouseRDown(false);

	// initialise game objects
	font.loadFromFile("font/arial.ttf");

	text.setFont(font);
	text.setPosition(0, 0);

	circle.setFillColor(sf::Color::Magenta);
	circle.setRadius(50);
	circle.setPosition(-100, -100);
}

Level::~Level()
{
	input = nullptr;
}

// handle user input
void Level::handleInput()
{
	//output if w pressed
	if (input->isKeyDown(22)) {
		std::cout << "W has been pressed.\n";
		input->setKeyUp(22);
	}

	//output if j+k+l pressed
	if (input->isKeyDown(9) && input->isKeyDown(10) && input->isKeyDown(11)) {
		std::cout << "J, K and L have been pressed.\n";
		input->setKeyUp(9);
		input->setKeyUp(10);
		input->setKeyUp(11);
	}

	//quit if escape pressed
	if (input->isKeyDown(36)) {
		window->close();
	}

	//set text to mouse position
	text.setString((std::string)"X: " + std::to_string(input->getMouseX()) + (std::string)", Y: " + std::to_string(input->getMouseY()) + "\n");

	//measure mouse drag distance
	if (input->isMouseLDown() && initialX == -1) {
		initialX = input->getMouseX();
		initialY = input->getMouseY();
	}
	if (!input->isMouseLDown() && initialX != -1) {
		std::cout << sqrt(pow(input->getMouseX() - initialX, 2) + pow(input->getMouseY() - initialY, 2)) << "\n";
		initialX = -1;
		initialY = -1;
	}

	//display circle
	if (input->isMouseRDown()) {
		circle.setPosition(input->getMouseX() - 50, input->getMouseY() - 50);
		input->setMouseRDown(false);
	}
}

// Update game objects
void Level::update()
{

}

// Render level
void Level::render()
{
	beginDraw();
	window->draw(text);
	window->draw(circle);
	endDraw();
}

// Begins rendering to the back buffer. Background colour set to light blue.
void Level::beginDraw()
{
	window->clear(sf::Color(100, 149, 237));
}

// Ends rendering to the back buffer, and swaps buffer to the screen.
void Level::endDraw()
{
	window->display();
}