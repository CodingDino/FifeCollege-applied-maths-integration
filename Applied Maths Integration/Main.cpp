// Library Includes	
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>

// The main() Function - entry point for our program
int main()
{
	sf::RenderWindow gameWindow;
	gameWindow.create(sf::VideoMode::getDesktopMode(), "Grenade Battle", sf::Style::Titlebar | sf::Style::Close);

	// -----------------------------------------------
	// Game Setup
	// -----------------------------------------------
	// Player Sprite
	sf::Texture playerTexture;
	playerTexture.loadFromFile("Assets/player_1.png");
	sf::Sprite playerSprite;
	playerSprite.setTexture(playerTexture);
	playerSprite.setPosition(
		gameWindow.getSize().x / 2 - playerTexture.getSize().x / 2,
		gameWindow.getSize().y / 2 - playerTexture.getSize().y / 2
	);

	// Pips
	sf::Texture pipTexture;
	pipTexture.loadFromFile("Assets/pip.png");
	const int NUM_PIPS = 10;
	sf::Sprite pipSprites[NUM_PIPS];
	for (int i = 0; i < NUM_PIPS; ++i)
	{
		pipSprites[i].setTexture(pipTexture);
	}

	// Prediction Variables
	sf::Vector2f gravity(0,750.0f);
	sf::Vector2f firingVelocity(500,-500);
	sf::Vector2f firingPosition(500, 500);
	float firingSpeed = 750.0f;

	// Game Clock
	sf::Clock gameClock;

	// Player Movement
	sf::Vector2f playerVelocity(0.0f, 0.0f);
	float playerSpeed = 100.0f;

	// Grenade
	sf::Texture grenadeTexture;
	grenadeTexture.loadFromFile("Assets/grenade.png");
	sf::Sprite grenadeSprite;
	grenadeSprite.setTexture(grenadeTexture);
	sf::Vector2f grenadeVelocity(0.0f, 0.0f);

	// Crates
	sf::Texture crateTexture;
	crateTexture.loadFromFile("Assets/crate.png");
	const int NUM_CRATES = 30;
	std::vector<sf::Sprite> crateSprites;
	for (int i = 0; i < NUM_CRATES; ++i)
	{
		crateSprites.push_back(sf::Sprite());
		crateSprites[i].setTexture(crateTexture);
		crateSprites[i].setPosition(i * 28, 500);
	}

	// Game Loop
	while (gameWindow.isOpen())
	{
		// -----------------------------------------------
		// Input Section
		// -----------------------------------------------
		sf::Event gameEvent;
		while (gameWindow.pollEvent(gameEvent))
		{
			// Did the player try to close the window?
			if (gameEvent.type == sf::Event::Closed)
			{
				// If so, call the close function on the window.
				gameWindow.close();
			}
		} // End event polling loop

		// Check if the movement keys are being pressed
		playerVelocity.x = 0.0f;
		playerVelocity.y = 0.0f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			// Move player up
			playerVelocity.y = -playerSpeed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			// Move player left
			playerVelocity.x = -playerSpeed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			// Move player down
			playerVelocity.y = playerSpeed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			// Move player right
			playerVelocity.x = playerSpeed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			// Fire ze missiles!
			grenadeSprite.setPosition(firingPosition);
			grenadeVelocity = firingVelocity;
		}


		// -----------------------------------------------
		// Update Section
		// -----------------------------------------------
		// Get the time passed since the last frame and restart our game clock
		sf::Time frameTime = gameClock.restart();

		// Move our player based on the time passed and their current velocity
		// This uses the equation:   s2 = s1 + v * t
		playerSprite.setPosition(playerSprite.getPosition() + playerVelocity * frameTime.asSeconds());


		// Update projectile prediction values
		firingPosition = playerSprite.getPosition();
		firingVelocity = sf::Vector2f(sf::Mouse::getPosition(gameWindow)) - firingPosition;

		// Normalize the velocity
		float mag = sqrt(firingVelocity.x * firingVelocity.x + firingVelocity.y * firingVelocity.y);
		firingVelocity.x /= mag;
		firingVelocity.y /= mag;

		// Scale by speed
		firingVelocity *= firingSpeed;

		// Calculate position for pips
		float pipTime = 0;
		for (int i = 0; i < NUM_PIPS; ++i)
		{
			pipTime += 0.1f; // 1/10th of a second further each pip
			sf::Vector2f pipPosition = firingPosition + firingVelocity * pipTime + 0.5f * gravity * pipTime * pipTime;
			pipSprites[i].setPosition(pipPosition);
		}

		// Update Grenade Position
		grenadeVelocity += gravity * frameTime.asSeconds(); // Increase downward velocity based on gravity
		grenadeSprite.setPosition(grenadeSprite.getPosition() + grenadeVelocity * frameTime.asSeconds());



		// -----------------------------------------------
		// Draw Section
		// -----------------------------------------------
		// Clear the window to a single colour
		gameWindow.clear(sf::Color::Black);

		// Draw everything to the window
		gameWindow.draw(playerSprite);
		for (int i = 0; i < NUM_PIPS; ++i)
		{
			gameWindow.draw(pipSprites[i]);
		}
		for (int i = 0; i < crateSprites.size(); ++i)
		{
			gameWindow.draw(crateSprites[i]);
		}

		// Draw grenade
		gameWindow.draw(grenadeSprite);

		// Display the window contents on the screen
		gameWindow.display();

	} // End of Game Loop
	return 0;

} // End of main() Function