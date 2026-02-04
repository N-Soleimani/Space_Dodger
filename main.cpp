// The Making of the Game Space Dodger!
// creators: Negin Soleimani & Parya Pirhajati

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

using namespace std;
using namespace sf;

int main(){
    srand(static_cast<unsigned>(time(0)));
    const int windowWidth = 1080;
    const int windowHeight = 900;

    RenderWindow window(VideoMode(windowWidth, windowHeight), "Space Dodger");

    Texture playerTex, enemyTex;
    if(!playerTex.loadFromFile("player.png") || !enemyTex.loadFromFile("enemy.png")){
        cout << "Error loading textures!" << endl;
        return 1;
    }

    Sprite player(playerTex);
    player.setScale(0.3f, 0.3f);
    player.setPosition(windowWidth/2.f - player.getGlobalBounds().width/2.f, windowHeight-150);

    vector<Sprite> enemies;
    float enemySpeed = 0.8f;
    float speedIncrement = 0.01f;
    Clock spawnClock;

    Font font;
    if(!font.loadFromFile("bitwise.ttf")){
        cout << "Error loading font!" << endl;
        return 1;
    }

    int score = 0;
    Text scoreText("Score: 0", font, 30);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition(20, 20);

    while(window.isOpen()){
        Event event;
        while(window.pollEvent(event)){
            if(event.type == Event::Closed)
                window.close();
        }

        Vector2i mousePos = Mouse::getPosition(window);
        player.setPosition(mousePos.x - player.getGlobalBounds().width/2.f, player.getPosition().y);
        if(player.getPosition().x < 0) player.setPosition(0, player.getPosition().y);
        if(player.getPosition().x + player.getGlobalBounds().width > windowWidth) player.setPosition(windowWidth - player.getGlobalBounds().width, player.getPosition().y);

        if(spawnClock.getElapsedTime().asSeconds() > 0.8f){
            Sprite enemy(enemyTex);
            enemy.setScale(0.3f,0.3f);
            enemy.setPosition(rand() % windowWidth, -100);
            enemies.push_back(enemy);
            spawnClock.restart();
        }

        for(int i=0; i<enemies.size(); i++){
            enemies[i].move(0, enemySpeed);
            if(enemies[i].getPosition().y > windowHeight){
                enemies.erase(enemies.begin()+i);
                score++;
                enemySpeed += speedIncrement;
                i--;
            }
        }

        scoreText.setString("Score: " + to_string(score));

        window.clear(Color::Black);
        window.draw(player);
        for(auto &e: enemies) window.draw(e);
        window.draw(scoreText);
        window.display();
    }

return 0;
}