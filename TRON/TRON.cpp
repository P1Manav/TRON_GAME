#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include <fstream>
#include <vector>

using namespace sf;

const int W = 1000;
const int H = 1000;
double speed = 0.8;
bool field[W][H] = { 0 };

struct Player
{
    int x, y, dir;
    Color color;
    Sprite sprite;
    int score;

    Player(Color c, const Texture& bikeTexture)
    {
        x = rand() % W;
        y = rand() % H;
        color = c;
        dir = rand() % 4;
        sprite.setTexture(bikeTexture);
        sprite.setColor(c);
        sprite.setOrigin(15, 15);
        sprite.setScale(0.2f, 0.2f);
        score = 0;
    }

    void tick()
    {
        if (dir == 0) y += 1;
        if (dir == 1) x -= 1;
        if (dir == 2) x += 1;
        if (dir == 3) y -= 1;

        if (x >= W) x = 0; if (x < 0) x = W - 1;
        if (y >= H) y = 0; if (y < 0) y = H - 1;

        sprite.setPosition(x, y);

        if (dir == 0) {
            sprite.setRotation(90);
            sprite.setPosition(x + 20, y);
        }
        else if (dir == 1) {
            sprite.setRotation(180);
            sprite.setPosition(x, y + 20);
        }
        else if (dir == 2) {
            sprite.setRotation(0);
            sprite.setPosition(x, y - 15);
        }
        else if (dir == 3) {
            sprite.setRotation(270);
            sprite.setPosition(x - 15, y);
        }
    }
};

bool loadFromFileToMemory(const std::string& filename, std::vector<char>& buffer)
{
    std::ifstream file(filename, std::ios::binary);
    if (!file)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return false;
    }

    file.seekg(0, std::ios::end);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);
    buffer.resize(size);
    if (!file.read(buffer.data(), size))
    {
        std::cerr << "Error reading file: " << filename << std::endl;
        return false;
    }

    return true;
}

int main()
{
    srand(time(0));

    RenderWindow window(VideoMode(W, H), "THE TRON GAME!");
    window.setFramerateLimit(60);

    std::vector<char> backgroundBuffer, bikeBuffer, fontBuffer;
    if (!loadFromFileToMemory("D:/Projects/TRON/background.jpg", backgroundBuffer) ||
        !loadFromFileToMemory("D:/Projects/TRON/bike.png", bikeBuffer) ||
        !loadFromFileToMemory("D:/Projects/TRON/Fonts/Roboto-Black.ttf", fontBuffer))
    {
        return -1;
    }


    Texture texture;
    if (!texture.loadFromMemory(backgroundBuffer.data(), backgroundBuffer.size()))
    {
        std::cerr << "Error loading background texture from memory" << std::endl;
        return -1;
    }

    Texture bikeTexture;
    if (!bikeTexture.loadFromMemory(bikeBuffer.data(), bikeBuffer.size()))
    {
        std::cerr << "Error loading bike texture from memory" << std::endl;
        return -1;
    }

    Font font;
    if (!font.loadFromMemory(fontBuffer.data(), fontBuffer.size()))
    {
        std::cerr << "Error loading font from memory" << std::endl;
        return -1;
    }

    Sprite sBackground(texture);

    Player p1(Color::Red, bikeTexture);
    Player p2(Color::Green, bikeTexture);

    Sprite sprite;
    RenderTexture t;
    t.create(W, H);
    t.setSmooth(true);
    sprite.setTexture(t.getTexture());
    t.clear();
    sBackground.setScale(static_cast<float>(W) / sBackground.getLocalBounds().width,
        static_cast<float>(H) / sBackground.getLocalBounds().height);
    t.draw(sBackground);

    Text winnerText;
    winnerText.setFont(font);
    winnerText.setCharacterSize(50);
    winnerText.setFillColor(Color::White);

    FloatRect textRect = winnerText.getLocalBounds();
    winnerText.setOrigin(textRect.left + textRect.width / 2.0f,
        textRect.top + textRect.height / 2.0f);
    winnerText.setPosition(W / 2.0f, H / 2.0f);

    Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(30);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition(10, 10);

    bool Game = true;
    bool p1Lost = false, p2Lost = false;

    while (window.isOpen())
    {
        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Left)) if (p1.dir != 2) p1.dir = 1;
        if (Keyboard::isKeyPressed(Keyboard::Right)) if (p1.dir != 1) p1.dir = 2;
        if (Keyboard::isKeyPressed(Keyboard::Up)) if (p1.dir != 0) p1.dir = 3;
        if (Keyboard::isKeyPressed(Keyboard::Down)) if (p1.dir != 3) p1.dir = 0;

        if (Keyboard::isKeyPressed(Keyboard::A)) if (p2.dir != 2) p2.dir = 1;
        if (Keyboard::isKeyPressed(Keyboard::D)) if (p2.dir != 1) p2.dir = 2;
        if (Keyboard::isKeyPressed(Keyboard::W)) if (p2.dir != 0) p2.dir = 3;
        if (Keyboard::isKeyPressed(Keyboard::S)) if (p2.dir != 3) p2.dir = 0;

        if (Game)
        {
            bool bothPlayersCollided = false;

            for (double i = 0; i < speed; i += 0.2)
            {
                p1.tick();
                p2.tick();

                if (field[p1.x][p1.y] == 1 && field[p2.x][p2.y] == 1)
                {
                    bothPlayersCollided = true;
                    break; 
                }
                else if (field[p1.x][p1.y] == 1)
                {
                    p1Lost = true;
                    break;  
                }
                else if (field[p2.x][p2.y] == 1)
                {
                    p2Lost = true;
                    break;  
                }

                field[p1.x][p1.y] = 1;
                field[p2.x][p2.y] = 1;

                CircleShape c(3);
                c.setPosition(p1.x, p1.y);
                c.setFillColor(p1.color);
                t.draw(c);
                c.setPosition(p2.x, p2.y);
                c.setFillColor(p2.color);
                t.draw(c);
            }

            if (bothPlayersCollided)
            {
                Game = false;
                p1Lost = true;
                p2Lost = true;
                p1.score++;
                p2.score++;
            }
            else if (p1Lost)
            {
                Game = false;
                p2.score++;
            }
            else if (p2Lost)
            {
                Game = false;
                p1.score++;
            }
        }


        t.display();

        window.clear();
        window.draw(sprite);
        window.draw(p1.sprite);
        window.draw(p2.sprite);

        std::string scoreStr = "Red: " + std::to_string(p1.score) + "  Green: " + std::to_string(p2.score);
        scoreText.setString(scoreStr);
        window.draw(scoreText);

        if (!Game)
        {
            if (p1Lost && !p2Lost)
            {
                winnerText.setString("Green Wins!");
                winnerText.setFillColor(Color::Green);
            }
            else if (p2Lost && !p1Lost)
            {
                winnerText.setString("Red Wins!");
                winnerText.setFillColor(Color::Red);
            }
            else
            {
                winnerText.setString("Draw!");
                winnerText.setFillColor(Color::White);
            }
            window.draw(winnerText);

            Text continueText("Press Enter to continue or Esc to exit", font, 30);
            continueText.setFillColor(Color::White);
            continueText.setPosition(W / 2 - continueText.getLocalBounds().width / 2, H / 2 + 50);
            window.draw(continueText);
            window.display();

            bool waitingForInput = true;
            while (waitingForInput)
            {
                while (window.pollEvent(e))
                {
                    if (e.type == Event::KeyPressed)
                    {
                        if (e.key.code == Keyboard::Enter)
                        {
                            p1.x = rand() % W; p1.y = rand() % H; p1.dir = rand() % 4;
                            p2.x = rand() % W; p2.y = rand() % H; p2.dir = rand() % 4;
                            std::fill(&field[0][0], &field[0][0] + sizeof(field), 0);
                            Game = true;
                            p1Lost = false;
                            p2Lost = false;
                            waitingForInput = false;
                            t.clear();
                            t.draw(sBackground);
                        }
                        else if (e.key.code == Keyboard::Escape)
                        {
                            window.close();
                            waitingForInput = false;
                        }
                    }
                }
            }
        }
        else
        {
            window.display();
        }
    }

    return 0;
}
