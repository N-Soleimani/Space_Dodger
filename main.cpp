// The Making of the Game Space Dodger!
// creators: Negin Soleimani & Parya Pirhajati

// The Making of the Game Space Dodger!
// creators: Negin Soleimani & Parya Pirhajati

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <ctime>

using namespace std;
using namespace sf;

int main(){
    srand(static_cast<unsigned>(time(0)));

    const int windowWidth = 1080;
    const int windowHeight = 900;
    RenderWindow window(VideoMode(windowWidth, windowHeight), "Space Dodger");
    Color spaceBlue(10, 10, 50);

    // --------- Load Textures --------- //
    Texture playerTex, enemyTex;
    if(!playerTex.loadFromFile("player.png") ||
        !enemyTex.loadFromFile("enemy.png")){
        cout << "Error loading textures!" << endl;
        return 1;
    }

    // --------- Player --------- //
    Sprite player(playerTex);
    player.setScale(0.3f, 0.3f);
    player.setPosition(
        windowWidth / 2.f - player.getGlobalBounds().width / 2.f,
        windowHeight - 150
    );

    // --------- Enemies --------- //
    vector<Sprite> enemies;
    float enemySpeed = 0.8f;
    float speedIncrement = 0.01f;
    float maxSpeed = 5.f;

    // --------- Font --------- //
    Font font;
    if(!font.loadFromFile("bitwise.ttf")){
        cout << "Error loading font!" << endl;
        return 1;
    }

    // --------- Score --------- //
    int score = 0;
    Text scoreText("Score: 0", font, 30);
    scoreText.setPosition(20, 20);

    Clock spawnClock;

    // --------- Menu --------- //
    bool isMenu = true;
    Text titleText("SPACE DODGER", font, 80);
    titleText.setPosition(
        windowWidth / 2.f - titleText.getGlobalBounds().width / 2.f, 200
    );

    Text startText("Press ENTER to Start", font, 50);
    startText.setFillColor(Color::Yellow);
    startText.setPosition(
        windowWidth / 2.f - startText.getGlobalBounds().width / 2.f, 400
    );

    // --------- Countdown --------- //
    bool isCountdown = false;
    Clock countdownClock;
    int countdownNumber = 3;

    Text countdownText("", font, 120);
    countdownText.setFillColor(Color::White);

    // --------- Game Over --------- //
    bool isGameOver = false;

    Text gameOverText("GAME OVER", font, 90);
    gameOverText.setFillColor(Color::Red);

    Text finalScoreText("", font, 50);
    Text restartText("Press R to return to menu", font, 40);
    restartText.setFillColor(Color::Yellow);

    // ================= GAME LOOP ================= //
    while(window.isOpen()){
        Event event;
        while(window.pollEvent(event)){
            if(event.type == Event::Closed)
                window.close();
        }

        // --------- MENU --------- //
        if(isMenu){
            if(Keyboard::isKeyPressed(Keyboard::Enter)){
                isMenu = false;
                isCountdown = true;
                countdownNumber = 3;
                countdownClock.restart();

                score = 0;
                enemySpeed = 0.8f;
                enemies.clear();
            }

            window.clear(spaceBlue);
            window.draw(titleText);
            window.draw(startText);
            window.display();
            continue;
        }

        // --------- COUNTDOWN (3، 2، 1، GO!) --------- //
        if(isCountdown){
            float timePassed = countdownClock.getElapsedTime().asSeconds();

            if(countdownNumber > 0 && timePassed >= 1.f){
                countdownNumber--;
                countdownClock.restart();
            }
            if(countdownNumber > 0) {
                countdownText.setString(to_string(countdownNumber));
            }else{
                countdownText.setString("GO!");
                if(timePassed >= 0.6f){
                    isCountdown = false;
                }
            }

            FloatRect b = countdownText.getLocalBounds();
            countdownText.setOrigin(b.width / 2, b.height / 2);
            countdownText.setPosition(windowWidth / 2.f, windowHeight / 2.f);

            window.clear(spaceBlue);
            window.draw(player);
            window.draw(countdownText);
            window.display();
            continue;
        }

        // --------- GAME OVER --------- //
        if(isGameOver){
            if(Keyboard::isKeyPressed(Keyboard::R)){
                isMenu = true;
                isGameOver = false;
            }
            gameOverText.setPosition(
                windowWidth / 2.f - gameOverText.getGlobalBounds().width / 2.f, 250
            );
            finalScoreText.setString("Final Score: " + to_string(score));
            finalScoreText.setPosition(
                windowWidth / 2.f - finalScoreText.getGlobalBounds().width / 2.f, 380
            );
            restartText.setPosition(
                windowWidth / 2.f - restartText.getGlobalBounds().width / 2.f, 460
            );

            window.clear(spaceBlue);
            window.draw(gameOverText);
            window.draw(finalScoreText);
            window.draw(restartText);
            window.display();
            continue;
        }

        // --------- GAME --------- //
        Vector2i mousePos = Mouse::getPosition(window);
        player.setPosition(
            mousePos.x - player.getGlobalBounds().width / 2.f,
            player.getPosition().y
        );
        if(player.getPosition().x < 0)
            player.setPosition(0, player.getPosition().y);
        if(player.getPosition().x + player.getGlobalBounds().width > windowWidth)
            player.setPosition(windowWidth - player.getGlobalBounds().width, player.getPosition().y);

        if(spawnClock.getElapsedTime().asSeconds() > 0.8f){
            Sprite enemy(enemyTex);
            enemy.setScale(0.3f, 0.3f);
            enemy.setPosition(rand() % windowWidth, -100);
            enemies.push_back(enemy);
            spawnClock.restart();
        }
        for(int i = 0; i < enemies.size(); i++){
            enemies[i].move(0, enemySpeed);
            if(enemies[i].getGlobalBounds().intersects(player.getGlobalBounds())){
                isGameOver = true;
                enemies.clear();
            }
            if(enemies[i].getPosition().y > windowHeight){
                enemies.erase(enemies.begin() + i);
                score++;
                enemySpeed += speedIncrement;
                i--;
            }
        }
        scoreText.setString("Score: " + to_string(score));
        window.clear(spaceBlue);
        window.draw(player);
        for(auto& e : enemies)
            window.draw(e);
        window.draw(scoreText);
        window.display();
    }

return 0;
}
