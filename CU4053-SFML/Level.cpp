#include "Level.h"

Level::Level(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;

	// initialise game objects
	rectangl.setSize(sf::Vector2f(50, 50));
	rectangl.setPosition(0, 300);
	rectangl.setFillColor(sf::Color::Red);
	rectangl.setOutlineColor(sf::Color::Black);
	rectangl.setOutlineThickness(5.f);

	circl.setRadius(25.f);
	circl.setPosition(600, 450);
	circl.setFillColor(sf::Color::Cyan);
	circl.setOutlineColor(sf::Color::Blue);
	circl.setOutlineThickness(5.f);

	circlBall.setRadius(25.f);
	circlBall.setFillColor(sf::Color::Yellow);
	circlBall.setOutlineColor(sf::Color::Red);
	circlBall.setOutlineThickness(5.f);

	speed = 500.f;

	bounceSpeedX = 400.f;
	bounceSpeedY = 400.f;
	
}

Level::~Level()
{

}

// handle user input
void Level::handleInput(float dt)
{
	//these just make the circle move slowly back and forth for some reason
	//but if it works then who cares
	if (input->isKeyDown(sf::Keyboard::W)) {
		input->setKeyUp(sf::Keyboard::W);
		std::cout << "W was pressed just now" << std::endl;
		circl.move(0,speed * dt);
	}
	if (input->isKeyDown(sf::Keyboard::A)) {
		input->setKeyUp(sf::Keyboard::A);
		std::cout << "A was pressed just now" << std::endl;
		circl.move(speed * dt, 0);
	}
	if (input->isKeyDown(sf::Keyboard::S)) {
		input->setKeyUp(sf::Keyboard::S);
		std::cout << "S was pressed just now" << std::endl;
		circl.move(0, -speed * dt);
	}
	if (input->isKeyDown(sf::Keyboard::D)) {
		input->setKeyUp(sf::Keyboard::D);
		std::cout << "D was pressed just now" << std::endl;
		circl.move(-speed * dt, 0);
	}

	if (input->isKeyDown(sf::Keyboard::Add)) {
		input->setKeyUp(sf::Keyboard::Add);
		std::cout << "Add (+) was pressed just now" << std::endl;
		bounceSpeedX += 100.f;
		bounceSpeedY += 100.f;
	}
	if (input->isKeyDown(sf::Keyboard::Subtract)) {
		input->setKeyUp(sf::Keyboard::Subtract);
		std::cout << "Subtract (-) was pressed just now" << std::endl;
		bounceSpeedX -= 100.f;
		bounceSpeedY -= 100.f;
	}

	if (input->isKeyDown(sf::Keyboard::Escape)) {
		exit(0);
	}
}

// Update game objects
void Level::update(float dt)
{
	if (rectangl.getPosition().x > window->getSize().x) {
		speed -= 500;
	}
	else if (rectangl.getPosition().x < 0) {
		speed = 500;
	}


	if (circlBall.getPosition().x <= 0 || circlBall.getPosition().x >= window->getSize().x - circlBall.getRadius() * 2) {
		bounceSpeedX = -bounceSpeedX;
	}
	if (circlBall.getPosition().y <= 0 || circlBall.getPosition().y >= window->getSize().y - circlBall.getRadius() * 2) {
		bounceSpeedY = -bounceSpeedY;
	}

	//i don't think the ball was even trained properly
	rectangl.move(speed * dt, 0);
	circlBall.move(speed * dt, speed * dt);
}

// Render level
void Level::render()
{
	beginDraw();
	window->draw(rectangl);
	window->draw(circl);
	window->draw(circlBall);
	endDraw();
}

