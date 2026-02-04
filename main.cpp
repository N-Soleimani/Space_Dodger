// The Making of the Game Space Dodger!
// creators: Negin Soleimani & Parya Pirhajati

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

int main(){
    const int windowWidth = 1080;
    const int windowHeight = 900;

    RenderWindow window(VideoMode(windowWidth, windowHeight), "Space Dodger");

    Texture playerTex;
    if(!playerTex.loadFromFile("player.png")){
        cout << "Error: could not load player.png" << endl;
        return 1;
    }

    Sprite player(playerTex);
    player.setScale(0.3f, 0.3f);
    player.setPosition(windowWidth/2.f - player.getGlobalBounds().width/2.f, windowHeight-150);

    while(window.isOpen()){
        Event event;
        while(window.pollEvent(event)){
            if(event.type == Event::Closed)
                window.close();
        }

        window.clear(Color::Black);
        window.draw(player);
        window.display();
    }

return 0;
}