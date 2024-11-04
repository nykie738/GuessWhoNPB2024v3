#include <SFML/Graphics.hpp>
#include "iostream"
#include "Game.h"

sf::VideoMode display = sf::VideoMode::getDesktopMode();
float dwidth = static_cast<float>(display.width);
float dheight = static_cast<float>(display.height);
float ratio = (1200 / dheight);
sf::Vector2i centerWindow((display.width / 4) - (500 * ratio), (display.height / 4) - (535 * ratio));
Textbox textbox1(30, sf::Color::Blue, true);

// W_HEIGHT * (W_HEIGHT / display.height)
// W_WIDTH * (W_HEIGHT / display.height)
Game::Game() : window(sf::VideoMode(W_WIDTH * ratio, W_HEIGHT * ratio), "Guess the Baseball Player!"),
               currentState(Gamestate::Initial), tempState(Gamestate::Initial)
{
    playerManager.loadPlayers("players.csv");
    window.setPosition(centerWindow);
    window.setKeyRepeatEnabled(true);
}

void Game::run()
{
    while (window.isOpen())
    {
        processEvents();
        if (tempState == currentState)
        {
            rend = 0;
        }
        else
        {
            rend = 1;
            tempState = currentState;
        }
        update();
        render();
    }
}

void Game::update()
{
    switch (currentState)
    {
    case Gamestate::Initial:
        handleInitial();
        break;
    case Gamestate::Selection:
        handleSelection();
        break;
    case Gamestate::Guessing:
        handleGuessing();
        break;
    case Gamestate::Correct:
        handleCorrect();
        break;
    case Gamestate::Incorrect:
        handleIncorrect();
        break;
    case Gamestate::Complete:
        handleComplete();
        break;
    }
}

void Game::render()
{
    if (rend != 0)
    {
        window.clear(sf::Color::Black);
    }
    if (currentState == Gamestate::Guessing)
    {
        // textbox1.drawTo(window);
    }
    // Render elements based on current state
    window.display();
}

void Game::handleInitial()
{
    sf::RectangleShape startButton(sf::Vector2f(300 * ratio, 150 * ratio));
    startButton.setFillColor(sf::Color::Yellow);
    startButton.setPosition(350 * ratio, 500 * ratio);

    sf::Font font;
    if (!font.loadFromFile("misaki_gothic_2nd.ttf"))
    { // Use a font file (e.g. "arial.ttf")
        std::cerr << "Failed to load font." << std::endl;
        // Error handling (e.g. exit the program)
        std::exit(EXIT_FAILURE);
    }

    sf::Text startText("Start", font, 100 * ratio);
    startText.setFillColor(sf::Color::Black);
    startText.setPosition(370 * ratio, 500 * ratio);

    // std::cout << "width " << display.width << std::endl;
    // std::cout << "height" << display.height << std::endl;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (startButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
        {
            sf::sleep(sf::milliseconds(400));
            currentState = Gamestate::Selection;
        }
    }
    window.clear(sf::Color::Black);
    window.draw(startButton);
    window.draw(startText);
}

void Game::handleSelection()
{
    sf::Font font;
    if (!font.loadFromFile("misaki_gothic_2nd.ttf"))
    { // Use a font file (e.g. "arial.ttf")
        std::cerr << "Failed to load font." << std::endl;
        // Error handling (e.g. exit the program)
        std::exit(EXIT_FAILURE);
    }

    sf::RectangleShape hanshinB(sf::Vector2f(300, 50));
    hanshinB.setFillColor(sf::Color::Yellow);
    hanshinB.setPosition(W_WIDTH / 2.0f * ratio, 230);
    hanshinB.setOrigin(hanshinB.getLocalBounds().width / 2.0f, hanshinB.getLocalBounds().height / 2.0f);
    sf::Text hanshinT("Hanshin Tigers", font, 25);
    hanshinT.setFillColor(sf::Color::Black);
    hanshinT.setPosition(W_WIDTH / 2.0f * ratio, 230);
    hanshinT.setOrigin(hanshinT.getLocalBounds().width / 2.0f, hanshinT.getLocalBounds().height / 2.0f);

    sf::RectangleShape giantsB(sf::Vector2f(300, 50));
    giantsB.setFillColor(sf::Color{255, 140, 0});
    giantsB.setPosition(W_WIDTH / 2.0f * ratio, 150);
    giantsB.setOrigin(giantsB.getLocalBounds().width / 2.0f, giantsB.getLocalBounds().height / 2.0f);
    sf::Text giantsT("Yomiuri Giants", font, 25);
    giantsT.setFillColor(sf::Color::Black);
    giantsT.setPosition(W_WIDTH / 2.0f * ratio, 150);
    giantsT.setOrigin(giantsT.getLocalBounds().width / 2.0f, giantsT.getLocalBounds().height / 2.0f);

    sf::RectangleShape bayB(sf::Vector2f(300, 50));
    bayB.setFillColor(sf::Color{0, 150, 255});
    bayB.setPosition(W_WIDTH / 2.0f * ratio, 310);
    bayB.setOrigin(bayB.getLocalBounds().width / 2.0f, bayB.getLocalBounds().height / 2.0f);
    sf::Text bayT("DeNA Baystars", font, 25);
    bayT.setFillColor(sf::Color::White);
    bayT.setPosition(W_WIDTH / 2.0f * ratio, 310);
    bayT.setOrigin(bayT.getLocalBounds().width / 2.0f, bayT.getLocalBounds().height / 2.0f);

    sf::RectangleShape carpB(sf::Vector2f(300, 50));
    carpB.setFillColor(sf::Color::Red);
    carpB.setPosition(W_WIDTH / 2.0f * ratio, 390);
    carpB.setOrigin(carpB.getGlobalBounds().width / 2.0f, carpB.getGlobalBounds().height / 2.0f);
    sf::Text carpT("Hiroshima Carp", font, 25);
    carpT.setFillColor(sf::Color::White);
    carpT.setPosition(W_WIDTH / 2.0f * ratio, 390);
    carpT.setOrigin(carpT.getGlobalBounds().width / 2.0f, carpT.getGlobalBounds().height / 2.0f);

    sf::RectangleShape swallowsB(sf::Vector2f(300, 50));
    swallowsB.setFillColor(sf::Color{137, 243, 54});
    swallowsB.setPosition(W_WIDTH / 2.0f * ratio, 470);
    swallowsB.setOrigin(swallowsB.getGlobalBounds().width / 2.0f, swallowsB.getGlobalBounds().height / 2.0f);
    sf::Text swallowsT("Yakult Swallows", font, 25);
    swallowsT.setFillColor(sf::Color{0, 5, 58});
    swallowsT.setPosition(W_WIDTH / 2.0f * ratio, 470);
    swallowsT.setOrigin(swallowsT.getGlobalBounds().width / 2.0f, swallowsT.getGlobalBounds().height / 2.0f);

    sf::RectangleShape dragonsB(sf::Vector2f(300, 50));
    dragonsB.setFillColor(sf::Color::Blue);
    dragonsB.setPosition(W_WIDTH / 2.0f * ratio, 550);
    dragonsB.setOrigin(dragonsB.getGlobalBounds().width / 2.0f, dragonsB.getGlobalBounds().height / 2.0f);
    sf::Text dragonsT("Chunichi Dragons", font, 25);
    dragonsT.setFillColor(sf::Color::White);
    dragonsT.setPosition(W_WIDTH / 2.0f * ratio, 550);
    dragonsT.setOrigin(dragonsT.getGlobalBounds().width / 2.0f, dragonsT.getGlobalBounds().height / 2.0f);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (hanshinB.getGlobalBounds().contains(mousePos.x, mousePos.y))
        {
            currentState = Gamestate::Guessing;
            selectedTeam = "Hanshin Tigers";
        }
        else if (giantsB.getGlobalBounds().contains(mousePos.x, mousePos.y))
        {
            currentState = Gamestate::Guessing;
            selectedTeam = "Yomiuri Giants";
        }
        else if (bayB.getGlobalBounds().contains(mousePos.x, mousePos.y))
        {
            currentState = Gamestate::Guessing;
            selectedTeam = "DeNA Baystars";
        }
        else if (carpB.getGlobalBounds().contains(mousePos.x, mousePos.y))
        {
            currentState = Gamestate::Guessing;
            selectedTeam = "Hiroshima Carp";
        }
        else if (swallowsB.getGlobalBounds().contains(mousePos.x, mousePos.y))
        {
            currentState = Gamestate::Guessing;
            selectedTeam = "Yakult Swallows";
        }
        else if (dragonsB.getGlobalBounds().contains(mousePos.x, mousePos.y))
        {
            currentState = Gamestate::Guessing;
            selectedTeam = "Chunichi Dragons";
        }
    }

    int halt2 = 0;

    if (halt2 == 0)
    {
        window.clear(sf::Color::Black);
        window.draw(hanshinB);
        window.draw(hanshinT);
        window.draw(giantsB);
        window.draw(giantsT);
        window.draw(bayB);
        window.draw(bayT);
        window.draw(carpB);
        window.draw(carpT);
        window.draw(swallowsB);
        window.draw(swallowsT);
        window.draw(dragonsB);
        window.draw(dragonsT);
        halt2++;
    }
}

void Game::handleGuessing()
{
    if (!currentPlayer && order == 1)
    {
        currentPlayer = &playerManager.getRandomPlayerByTeam(selectedTeam, order);
        std::cout << order << std::endl;
        // currentPlayer = &playerManager.getRandomPlayer();
    }
    else if (!currentPlayer && order > 1)
    {
        currentPlayer = &playerManager.getNextImage(wrongPlayer->getName(), order);
        std::cout << order << std::endl;
    }

    sf::Sprite playerSprite(currentPlayer->getTexture());

    // read just the image size info to fit into sfml window
    sf::Vector2u textureSize = playerSprite.getTexture()->getSize();
    const float adjWidth = 450.0f;
    const float adjHeight = 600.0f;
    float scaleX = adjWidth / textureSize.x * ratio;
    float scaleY = adjHeight / textureSize.y * ratio;
    float scale = std::min(scaleX, scaleY);

    playerSprite.setScale(scaleX, scaleY);
    playerSprite.setPosition(270 * ratio, 135 * ratio);

    sf::Font font;
    if (!font.loadFromFile("misaki_gothic_2nd.ttf"))
    { // Use a font file (e.g. "arial.ttf")
        std::cerr << "Failed to load font." << std::endl;
        // Error handling (e.g. exit the program)
        std::exit(EXIT_FAILURE);
    }

    textbox1.setFont(font);
    textbox1.setLimit(true, 20);
    textbox1.setPosition({W_WIDTH / 4.0f * ratio, 790 * ratio});

    sf::RectangleShape inputBox(sf::Vector2f(325, 50));
    inputBox.setFillColor(sf::Color::White);
    inputBox.setOutlineColor(sf::Color::Yellow);
    inputBox.setOutlineThickness(4);
    inputBox.setPosition(W_WIDTH / 2.0f * ratio, 820 * ratio);
    inputBox.setOrigin(inputBox.getGlobalBounds().width / 2.0f, inputBox.getGlobalBounds().height / 2.0f);

    sf::RectangleShape confirmButton(sf::Vector2f(100, 50));
    confirmButton.setFillColor(sf::Color::White);
    confirmButton.setPosition(W_WIDTH / 2.0f * ratio, 940 * ratio);
    confirmButton.setOrigin(confirmButton.getGlobalBounds().width / 2.0f, confirmButton.getGlobalBounds().height / 2.0f);

    sf::Text dareda("Guess the Player!", font, 50);
    dareda.setFillColor(sf::Color::Yellow);
    dareda.setPosition(W_WIDTH / 2.0f * ratio, 50 * ratio);
    dareda.setOrigin(dareda.getGlobalBounds().width / 2.0f, dareda.getGlobalBounds().height / 2.0f);
    sf::Text mouikkai("Incorrect! Try again!", font, 50);
    mouikkai.setFillColor(sf::Color::Yellow);
    mouikkai.setPosition(W_WIDTH / 2.0f * ratio, 50 * ratio);
    mouikkai.setOrigin(mouikkai.getGlobalBounds().width / 2.0f, mouikkai.getGlobalBounds().height / 2.0f);

    sf::Text confirmText("Confirm", font, 20);
    confirmText.setFillColor(sf::Color::Black);
    confirmText.setPosition(W_WIDTH / 2.0f * ratio, 940 * ratio);
    confirmText.setOrigin(confirmText.getGlobalBounds().width / 2.0f, confirmText.getGlobalBounds().height / 2.0f);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        if (mouseTrigger)
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (confirmButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
            {
                // bool deleteSprite = true;
                if (textbox1.getText() == currentPlayer->getName())
                {
                    std::cout << "SEIKAI" << std::endl;
                    std::cout << textbox1.getText() << std::endl;
                    userpoints += (5 - order);
                    guessedPlayers++;
                    currentState = Gamestate::Correct;
                }
                else
                {
                    std::cout << "Incorrect! Try again." << std::endl;
                    wrongGuess = true;
                    order++;
                    wrongPlayer = currentPlayer;
                    currentPlayer = nullptr;

                    if (order == 5)
                    {
                        guessedPlayers++;
                        currentState = Gamestate::Incorrect;
                    }
                }
                textbox1.clearText();
                mouseTrigger = false;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
            {
                if (textbox1.getText() == currentPlayer->getName())
                {
                    std::cout << "SEIKAI" << std::endl;
                    std::cout << textbox1.getText() << std::endl;
                    userpoints += (5 - order);
                    guessedPlayers++;
                    textbox1.clearText();
                    currentState = Gamestate::Correct;
                }
                else
                {
                    std::cout << "Incorrect! Try again." << std::endl;
                    wrongGuess = true;
                    order++;
                    wrongPlayer = currentPlayer;
                    currentPlayer = nullptr;

                    if (order == 5)
                    {
                        guessedPlayers++;
                        textbox1.clearText();
                        currentState = Gamestate::Incorrect;
                    }
                }
                // textbox1.clearText();
                mouseTrigger = false;
            }
        }
    }
    else
    {
        mouseTrigger = true;
    }
    window.clear(sf::Color::Black);
    window.draw(playerSprite);
    if (!wrongGuess)
    {
        window.draw(dareda);
    }
    else
    {
        window.draw(mouikkai);
    }
    window.draw(inputBox);
    window.draw(confirmButton);
    window.draw(confirmText);
    textbox1.drawTo(window);
}

void Game::handleCorrect()
{
    sf::Font font;
    if (!font.loadFromFile("misaki_gothic_2nd.ttf"))
    { // Use a font file (e.g. "arial.ttf")
        std::cerr << "Failed to load font." << std::endl;
        // Error handling (e.g. exit the program)
        std::exit(EXIT_FAILURE);
    }

    sf::Text answer("You are correct! The player is:", font, 50 * ratio);
    answer.setFillColor(sf::Color::Yellow);
    answer.setPosition(W_WIDTH / 2.0f * ratio, 30 * ratio);
    answer.setOrigin(answer.getLocalBounds().width / 2.0f, answer.getLocalBounds().height / 2.0f);

    sf::Text answerName(currentPlayer->getName(), font, 50 * ratio);
    answerName.setFillColor(sf::Color::Yellow);
    answerName.setPosition(W_WIDTH / 2.0f * ratio, 80 * ratio);
    answerName.setOrigin(answerName.getLocalBounds().width / 2.0f, answerName.getLocalBounds().height / 2.0f);

    sf::Text points("You earned " + std::to_string(5 - order) + " points!", font, 50 * ratio);
    points.setFillColor(sf::Color::Yellow);
    points.setPosition(W_WIDTH / 2.0f * ratio, 160 * ratio);
    points.setOrigin(points.getLocalBounds().width / 2.0f, points.getLocalBounds().height / 2.0f);

    sf::Text pointsTotal("You currently have " + std::to_string(userpoints) + " points!", font, 50 * ratio);
    pointsTotal.setFillColor(sf::Color::Yellow);
    pointsTotal.setPosition(W_WIDTH / 2.0f * ratio, 210 * ratio);
    pointsTotal.setOrigin(pointsTotal.getLocalBounds().width / 2.0f, pointsTotal.getLocalBounds().height / 2.0f);

    sf::RectangleShape nextButton(sf::Vector2f(100, 50));
    nextButton.setFillColor(sf::Color::White);
    nextButton.setPosition(W_WIDTH / 2.0f * ratio, 870 * ratio);
    nextButton.setOrigin(nextButton.getLocalBounds().width / 2.0f, nextButton.getLocalBounds().height / 2.0f);
    sf::Text nextText("Proceed", font, 20);
    nextText.setFillColor(sf::Color::Black);
    nextText.setPosition(W_WIDTH / 2.0f * ratio, 870 * ratio);
    nextText.setOrigin(nextText.getLocalBounds().width / 2.0f, nextText.getLocalBounds().height / 2.0f);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (mouseTrigger)
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (nextButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
            {
                mouseTrigger = false;

                if (guessedPlayers < 6)
                {
                    playerManager.removePlayers(currentPlayer->getName());
                    currentPlayer = nullptr;
                    wrongPlayer = nullptr;
                    wrongGuess = false;
                    order = 1;
                    std::cout << "Next player aboard." << std::endl;
                    currentState = Gamestate::Guessing;
                }
                else
                {
                    playerManager.removePlayers(currentPlayer->getName());
                    currentPlayer = nullptr;
                    wrongPlayer = nullptr;
                    wrongGuess = false;
                    order = 1;
                    std::cout << "No more players to display." << std::endl;
                    currentState = Gamestate::Complete;
                }
            }
        }
    }
    else
    {
        mouseTrigger = true;
    }
    window.clear(sf::Color::Black);
    window.draw(answer);
    window.draw(answerName);
    window.draw(points);
    window.draw(pointsTotal);
    window.draw(nextButton);
    window.draw(nextText);
}

void Game::handleIncorrect()
{
    sf::Font font;
    if (!font.loadFromFile("misaki_gothic_2nd.ttf"))
    { // Use a font file (e.g. "arial.ttf")
        std::cerr << "Failed to load font." << std::endl;
        // Error handling (e.g. exit the program)
        std::exit(EXIT_FAILURE);
    }

    sf::Text answer("Incorrect! The correct player is:", font, 50 * ratio);
    answer.setFillColor(sf::Color::Yellow);
    answer.setPosition(W_WIDTH / 2.0f * ratio, 30 * ratio);
    answer.setOrigin(answer.getLocalBounds().width / 2.0f, answer.getLocalBounds().height / 2.0f);

    sf::Text answerName(wrongPlayer->getName(), font, 50 * ratio);
    answerName.setFillColor(sf::Color::Yellow);
    answerName.setPosition(W_WIDTH / 2.0f * ratio, 80 * ratio);
    answerName.setOrigin(answerName.getLocalBounds().width / 2.0f, answerName.getLocalBounds().height / 2.0f);

    sf::Text points("You earned " + std::to_string(5 - order) + " points!", font, 50 * ratio);
    points.setFillColor(sf::Color::Yellow);
    points.setPosition(W_WIDTH / 2.0f * ratio, 160 * ratio);
    points.setOrigin(points.getLocalBounds().width / 2.0f, points.getLocalBounds().height / 2.0f);

    sf::Text pointsTotal("You currently have " + std::to_string(userpoints) + " points!", font, 50 * ratio);
    pointsTotal.setFillColor(sf::Color::Yellow);
    pointsTotal.setPosition(W_WIDTH / 2.0f * ratio, 210 * ratio);
    pointsTotal.setOrigin(pointsTotal.getLocalBounds().width / 2.0f, pointsTotal.getLocalBounds().height / 2.0f);

    sf::RectangleShape nextButton(sf::Vector2f(100, 50));
    nextButton.setFillColor(sf::Color::White);
    nextButton.setPosition(W_WIDTH / 2.0f * ratio, 870 * ratio);
    nextButton.setOrigin(nextButton.getLocalBounds().width / 2.0f, nextButton.getLocalBounds().height / 2.0f);
    sf::Text nextText("Proceed", font, 20);
    nextText.setFillColor(sf::Color::Black);
    nextText.setPosition(W_WIDTH / 2.0f * ratio, 870 * ratio);
    nextText.setOrigin(nextText.getLocalBounds().width / 2.0f, nextText.getLocalBounds().height / 2.0f);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (mouseTrigger)
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (nextButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
            {
                mouseTrigger = false;
                // need function for removing wrongPlayer from list
                if (guessedPlayers < 6)
                {
                    playerManager.removePlayers(wrongPlayer->getName());
                    currentPlayer = nullptr;
                    wrongPlayer = nullptr;
                    wrongGuess = false;
                    order = 1;
                    std::cout << "Next player aboard." << std::endl;
                    currentState = Gamestate::Guessing;
                }
                else
                {
                    playerManager.removePlayers(wrongPlayer->getName());
                    currentPlayer = nullptr;
                    wrongPlayer = nullptr;
                    wrongGuess = false;
                    order = 1;
                    std::cout << "No more players to display." << std::endl;
                    currentState = Gamestate::Complete;
                }
            }
        }
    }
    else
    {
        mouseTrigger = true;
    }
    window.clear(sf::Color::Black);
    window.draw(answer);
    window.draw(answerName);
    window.draw(points);
    window.draw(pointsTotal);
    window.draw(nextButton);
    window.draw(nextText);
}

void Game::handleComplete()
{
    sf::Font font;
    if (!font.loadFromFile("misaki_gothic_2nd.ttf"))
    { // Use a font file (e.g. "arial.ttf")
        std::cerr << "Failed to load font." << std::endl;
        // Error handling (e.g. exit the program)
        std::exit(EXIT_FAILURE);
    }

    sf::Text answer("That's it! Thank you for playing!", font, 50 * ratio);
    answer.setFillColor(sf::Color::Yellow);
    answer.setPosition(W_WIDTH / 2.0f * ratio, 30 * ratio);
    answer.setOrigin(answer.getLocalBounds().width / 2.0f, answer.getLocalBounds().height / 2.0f);

    sf::Text score("Your score is " + std::to_string(userpoints) + "/24 !", font, 50 * ratio);
    score.setFillColor(sf::Color::Yellow);
    score.setPosition(W_WIDTH / 2.0f * ratio, 160 * ratio);
    score.setOrigin(score.getLocalBounds().width / 2.0f * ratio, score.getLocalBounds().height / 2.0f * ratio);

    sf::Text outstanding("You must be a big fan of ", font, 50 * ratio);
    outstanding.setFillColor(sf::Color::Yellow);
    outstanding.setPosition(W_WIDTH / 2.0f * ratio, 260 * ratio);
    outstanding.setOrigin(outstanding.getLocalBounds().width / 2.0f, outstanding.getLocalBounds().height / 2.0f);
    sf::Text outstanding2(selectedTeam + "!", font, 50 * ratio);
    outstanding2.setFillColor(sf::Color::Yellow);
    outstanding2.setPosition(W_WIDTH / 2.0f * ratio, 330 * ratio);
    outstanding2.setOrigin(outstanding2.getLocalBounds().width / 2.0f, outstanding2.getLocalBounds().height / 2.0f);

    sf::Text end("Press enter to end the game.", font, 50 * ratio);
    end.setFillColor(sf::Color::Yellow);
    end.setPosition(W_WIDTH / 2.0f * ratio, 420 * ratio);
    end.setOrigin(end.getLocalBounds().width / 2.0f, end.getLocalBounds().height / 2.0f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        currentState = Gamestate::Selection;
        window.close();
    }

    window.clear(sf::Color::Black);
    window.draw(answer);
    window.draw(score);
    if (userpoints > 19)
    {
        window.draw(outstanding);
        window.draw(outstanding2);
    }
    window.draw(end);
}

void Game::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {

        case sf::Event::Closed:
            window.clear(sf::Color::Black);
            currentState = Gamestate::Selection;
            window.close();
        case sf::Event::TextEntered:
            textbox1.typedOn(event);
        }
        // Handle other events based on current state
    }
}
