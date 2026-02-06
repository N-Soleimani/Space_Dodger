// The Making of the Game Space Dodger!
// creators: Negin Soleimani & Parya Pirhajati

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;
using namespace sf;

// --------- Structure for round scores --------- //
struct RoundScore{
    int roundNumber;
    int score;
};

// --------- Function to load all rounds from leaderboard.txt --------- //
vector<RoundScore> loadRoundScores(const string& filename){
    vector<RoundScore> rounds;
    ifstream file(filename);
    string line;
    while(getline(file, line)){
        RoundScore r;
        if(sscanf(line.c_str(), "Round %d: %d", &r.roundNumber, &r.score) == 2){
            rounds.push_back(r);
        }
    }
    return rounds;
}

// --------- Function to get the high score --------- //
int getHighScore(const vector<RoundScore>& rounds){
    int high = 0;
    for(auto& r : rounds){
        if (r.score > high) high = r.score;
    }
    return high;
}

// --------- Function to get the next round number --------- //
int getNextRoundNumber(const vector<RoundScore>& rounds){
    int maxRound = 0;
    for(auto& r : rounds){
        if (r.roundNumber > maxRound) maxRound = r.roundNumber;
    }
    return maxRound + 1;
}

// --------- Function to save a new round score --------- //
void saveRoundScore(const string& filename, int roundNumber, int score){
    ofstream file(filename, ios::app);
    file << "Round " << roundNumber << ": " << score << "\n";
}

int main(){
    srand(static_cast<unsigned>(time(0)));

    const int windowWidth = 1080;
    const int windowHeight = 900;
    RenderWindow window(VideoMode(windowWidth, windowHeight), "Space Dodger");
    Color spaceBlue(10, 10, 50);

    const string leaderboardFile = "leaderboard.txt";

    // --------- Load existing rounds --------- //
    vector<RoundScore> rounds = loadRoundScores(leaderboardFile);
    int roundNumber = getNextRoundNumber(rounds);

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
    player.setPosition(windowWidth / 2.f - player.getGlobalBounds().width / 2.f, windowHeight - 150);

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

    // --------- Score Text --------- //
    int score = 0;
    Text scoreText("Score: 0", font, 30);
    scoreText.setPosition(20, 20);

    // --------- High Score Text --------- //
    int highScore = getHighScore(rounds);
    Text highScoreText("High Score: " + to_string(highScore), font, 30);
    highScoreText.setFillColor(Color::Yellow);
    highScoreText.setPosition(20, 60);

    Clock spawnClock;

    // --------- Menu --------- //
    bool isMenu = true;
    Text titleText("SPACE DODGER", font, 80);
    titleText.setPosition(windowWidth / 2.f - titleText.getGlobalBounds().width / 2.f, 200);

    Text startText("Press ENTER to Start", font, 50);
    startText.setFillColor(Color::Yellow);
    startText.setPosition(windowWidth / 2.f - startText.getGlobalBounds().width / 2.f, 400);

    // --------- Countdown --------- //
    bool isCountdown = false;
    Clock countdownClock;
    int countdownNumber = 3;
    Text countdownText("", font, 120);
    countdownText.setFillColor(Color::White);

    // --------- Game Over --------- //
    bool isGameOver = false;
    bool scoreSaved = false;
    Text gameOverText("GAME OVER", font, 90);
    gameOverText.setFillColor(Color::Red);

    Text finalScoreText("", font, 50);
    Text restartText("Press R to return to menu", font, 40);
    restartText.setFillColor(Color::Yellow);

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
                scoreSaved = false;
            }

            window.clear(spaceBlue);
            window.draw(titleText);
            window.draw(startText);
            window.display();
            continue;
        }

        // --------- COUNTDOWN --------- //
        if(isCountdown){
            float timePassed = countdownClock.getElapsedTime().asSeconds();

            if(countdownNumber > 0){
                if(timePassed >= 1.f){
                    countdownNumber--;
                    countdownClock.restart();
                }
                if(countdownNumber > 0)
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
            if(!scoreSaved){
                saveRoundScore(leaderboardFile, roundNumber++, score);
                rounds = loadRoundScores(leaderboardFile);
                highScore = getHighScore(rounds);
                highScoreText.setString("High Score: " + to_string(highScore));
                scoreSaved = true;
            }

            if(Keyboard::isKeyPressed(Keyboard::R)){
                isMenu = true;
                isGameOver = false;
            }

            gameOverText.setPosition(windowWidth / 2.f - gameOverText.getGlobalBounds().width / 2.f, 250);
            finalScoreText.setString("Final Score: " + to_string(score));
            finalScoreText.setPosition(windowWidth / 2.f - finalScoreText.getGlobalBounds().width / 2.f, 380);
            restartText.setPosition(windowWidth / 2.f - restartText.getGlobalBounds().width / 2.f, 460);

            window.clear(spaceBlue);
            window.draw(gameOverText);
            window.draw(finalScoreText);
            window.draw(restartText);
            window.draw(highScoreText);
            window.display();
            continue;
        }

        // --------- GAME --------- //
        Vector2i mousePos = Mouse::getPosition(window);
        player.setPosition(mousePos.x - player.getGlobalBounds().width / 2.f, player.getPosition().y);
        if(player.getPosition().x < 0)
            player.setPosition(0, player.getPosition().y);
        if(player.getPosition().x + player.getGlobalBounds().width > windowWidth)
            player.setPosition(windowWidth - player.getGlobalBounds().width, player.getPosition().y);

        if(spawnClock.getElapsedTime().asSeconds() > 0.8f){
            Sprite enemy(enemyTex);
            enemy.setScale(0.3f, 0.3f);
            float enemyWidth = enemy.getGlobalBounds().width;
            float enemyHeight = enemy.getGlobalBounds().height;
            float xPos = rand() % (windowWidth - static_cast<int>(enemyWidth));
            enemy.setPosition(xPos, -enemyHeight);
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

        // --------- DRAW Everything --------- //
        window.clear(spaceBlue);
        window.draw(player);
        for(auto& e : enemies)
            window.draw(e);
        window.draw(scoreText);
        window.draw(highScoreText);
        window.display();
    }

return 0;
}