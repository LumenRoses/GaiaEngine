#include <SFML/Graphics.hpp> //Llama a la librería gráfica de SFML.
#include "GaiaWorld.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Title"); //Creamos una ventana con dimensiones 800x600. 

	sf::Event event; //Creamos un objeto tipo evento, llamado event. 

	//Cargando sprites. 
	sf::Texture boxTex1; 
	sf::Sprite boxSprite1;

	if (!boxTex1.loadFromFile("Assets/Sprites/box1.png"))
	{
		std::cout << "Could not load texture. . ." << std::endl;
		system("pause");
	}

	boxSprite1.setTexture(boxTex1);
	boxSprite1.setScale(sf::Vector2f(0.05f, 0.05f));

	//Colocamos el origen del sprite en el centro del sprite. 
	sf::Rect<float> size = boxSprite1.getGlobalBounds();
	boxSprite1.setOrigin(sf::Vector2f(size.width / 2, size.height / 2));
	
	//Para ilustrar lo que queremos... colocaremos la cajita en el centro de la pantalla.
	boxSprite1.setPosition(sf::Vector2f(400, 600));

	while (window.isOpen()) //Se mantiene el ciclo while mientras la ventana esté abierta. 
	{
		while (window.pollEvent(event)) //Lee si hubo alguna señal de entrada (mouse, teclado, joystick...) 
		{
			if (event.type == sf::Event::Closed) //Si el usuario presiona X (para salir de la ventana)...
			{
				window.close(); //... Cierra la ventana
			}
		}

		window.clear(sf::Color::Black);
		window.draw(boxSprite1);
		window.display();
	}

	return 0;
}