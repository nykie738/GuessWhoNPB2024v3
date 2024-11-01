#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "PlayerManager.h"
#include "iostream"
#include <sstream>
#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

enum class Gamestate
{
    Initial,
    Selection,
    Guessing,
    Correct,
    Incorrect,
    Complete
};

class Game
{
public:
    Game();
    void run();
    bool mouseTrigger = true;
    bool wrongGuess = false;
    int rend = 0;
    int order = 1; // used for tracking remaining attempts and points reward
    int guessedPlayers = 0;
    int userpoints = 0;
    int W_WIDTH = 1000;
    int W_HEIGHT = 1200;
    const Player* currentPlayer = nullptr;
    const Player* wrongPlayer = nullptr;
    std::string selectedTeam;
    //sf::Font misaki;

private:
    sf::RenderWindow window;
    PlayerManager playerManager;
    Gamestate currentState = Gamestate::Initial;
    Gamestate tempState = Gamestate::Initial;

    void processEvents();
    void update();
    void render();

    void handleInitial();
    void handleSelection();
    void handleGuessing();
    void handleCorrect();
    void handleIncorrect();
    void handleComplete();
};

class Textbox
{
public:
    Textbox();
    void run();
    Textbox(int size, sf::Color color, bool sel)
    {
        textbox.setCharacterSize(size);
        textbox.setFillColor(color);
        // textbox.setColor(color);
        isSelected = sel;
        if (sel)
        {
            textbox.setString(" _");
        }
        else
        {
            textbox.setString("");
        }
    }

    void setFont(sf::Font& font)
    {
        textbox.setFont(font);
    }

    void setPosition(sf::Vector2f pos)
    {
        textbox.setPosition(pos);
    }

    void setLimit(bool ToF, int lim)
    {
        hasLimit = ToF;
        limit = lim;
    }

    void clearText()
    {
        text.str("");           // Clear the ostringstream
        text.clear();           // Reset any error flags
        textbox.setString(" _"); // Reset the displayed text
    }

    void setSelected(bool sel)
    {
        isSelected = sel;
        if (!sel)
        {
            std::string t = text.str();
            std::string newT = "";
            for (int i = 0; i < t.length() - 1; i++)
            {
                newT += t[i];
            }
            textbox.setString(newT);
        }
    }

    std::string getText()
    {
        return text.str();
    }

    void drawTo(sf::RenderWindow& window)
    {
        window.draw(textbox);
    }

    void typedOn(sf::Event input)
    {
        if (isSelected)
        {
            int charTyped = input.text.unicode;
            if (charTyped < 128)
            {
                if (hasLimit)
                {
                    if (text.str().length() <= limit)
                    {
                        inputLogic(charTyped);
                    }
                    else if (text.str().length() > limit && charTyped == DELETE_KEY)
                    {
                        deleteLastChar();
                    }
                }
                else
                {
                    inputLogic(charTyped);
                }
            }
        }
    }
private:
    sf::String playerInput;
    sf::Text inputText;
    sf::Font font;
    sf::Text textbox;
    std::ostringstream text;
    bool isSelected = false;
    bool hasLimit = false;
    int limit = 0;

    void inputLogic(int charTyped)
    {
        if (charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY)
        {
            text << static_cast<char>(charTyped);
        }
        else if (charTyped == DELETE_KEY)
        {
            if (text.str().length() > 0)
            {
                deleteLastChar();
            }
        }
        textbox.setString(" " + text.str() + "_");
    }

    void deleteLastChar()
    {
        std::string t = text.str();
        std::string newT = "";
        for (int i = 0; i < t.length() - 1; i++)
        {
            newT += t[i];
        }
        text.str("");
        text << newT;

        textbox.setString(text.str());
    }
};