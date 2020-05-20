/* 
UNIVERSIDAD INTERAMERICANA DE PUERTO RICO
PROYECTO GUÍA PARA LOS ESTUDIANTES DE PHYS3300 - FÍSICA PARA VIDEOJUEGOS
POR: MIGDONIO A. GONZÁLEZ

Cada estudiante debe mostrar su originalidad y creatividad en el proyecto así como el dominio de las herramientas y conceptos aprendidos en el curso.
*/

//Incluir librerías necesarias.
#include <SFML/Graphics.hpp>
#include "AnimatedSprite.h"
#include "MyCollision.h"

//Función main().
int main()
{
    //Crear la ventana con sus dimensiones y títulos. Programar el límite de fps. 
    sf::RenderWindow window(sf::VideoMode(960, 640), "Robotic Jungle Adventure");
    window.setFramerateLimit(60);

    //Declarar las variables de timing para el Box2D y eventos de teclado. 
    sf::Event event;
    sf::Clock clock;
    float dt;
    const float PPM = 32.0f; //Pixel per Meter. Yo decidí escoger 32, puedes escoger otro. 

    //Cargamos el fondo (background). Este tiene varios layers para dar un efecto más nítido.
    sf::Texture layer2bgTexture;
    layer2bgTexture.loadFromFile("Assets/Background/Dio-sunset2.png"); //No es necesario poner el if. 
    sf::Sprite layer2bg;
    layer2bg.setTexture(layer2bgTexture);

    sf::Texture layer3bgTexture;
    layer3bgTexture.loadFromFile("Assets/Background/Dio-sunset3.png");
    sf::Sprite layer3bg;
    layer3bg.setTexture(layer3bgTexture);

    sf::Texture layer4bgTexture;
    layer4bgTexture.loadFromFile("Assets/Background/Dio-sunset4.png");
    sf::Sprite layer4bg;
    layer4bg.setTexture(layer4bgTexture);

    //Cargar el spritesheet del robot. 
    sf::Texture walkingTexture;
    walkingTexture.loadFromFile("Assets/Robot/chibi-robot.png");

    //Crear la animación de caminar hacia la derecha.
    Animation walkingAnimationRight;
    walkingAnimationRight.setSpriteSheet(walkingTexture);
    walkingAnimationRight.addFrame(sf::IntRect(0, 0, 34, 35)); //Todos los frames, tienen dimensiones 34x35
    walkingAnimationRight.addFrame(sf::IntRect(34, 0, 34, 35));
    walkingAnimationRight.addFrame(sf::IntRect(68, 0, 34, 35));
    walkingAnimationRight.addFrame(sf::IntRect(102, 0, 34, 35));
    walkingAnimationRight.addFrame(sf::IntRect(136, 0, 34, 35));
    walkingAnimationRight.addFrame(sf::IntRect(170, 0, 34, 35));

    //Crear la animación de caminar hacia la izquierda. 
    Animation walkingAnimationLeft;
    walkingAnimationLeft.setSpriteSheet(walkingTexture);
    walkingAnimationLeft.addFrame(sf::IntRect(0, 35, 34, 35));
    walkingAnimationLeft.addFrame(sf::IntRect(34, 35, 34, 35));
    walkingAnimationLeft.addFrame(sf::IntRect(68, 35, 34, 35));
    walkingAnimationLeft.addFrame(sf::IntRect(102, 35, 34, 35));
    walkingAnimationLeft.addFrame(sf::IntRect(136, 35, 34, 35));
    walkingAnimationLeft.addFrame(sf::IntRect(170, 35, 34, 35));

    //Crear animación de salto derecha. 
    Animation jumpingAnimationRight;
    jumpingAnimationRight.setSpriteSheet(walkingTexture);
    jumpingAnimationRight.addFrame(sf::IntRect(0, 70, 34, 35));
    jumpingAnimationRight.addFrame(sf::IntRect(34, 70, 34, 35));
    jumpingAnimationRight.addFrame(sf::IntRect(68, 70, 34, 35));
    jumpingAnimationRight.addFrame(sf::IntRect(102, 70, 34, 35));

    //Crear animación de salto izquierda. 
    Animation jumpingAnimationLeft;
    jumpingAnimationLeft.setSpriteSheet(walkingTexture);
    jumpingAnimationLeft.addFrame(sf::IntRect(0, 105, 34, 35));
    jumpingAnimationLeft.addFrame(sf::IntRect(34, 105, 34, 35));
    jumpingAnimationLeft.addFrame(sf::IntRect(68, 105, 34, 35));
    jumpingAnimationLeft.addFrame(sf::IntRect(102, 105, 34, 35));

    //Crear la animación de volar derecha. 
    Animation flyingAnimationRight;
    flyingAnimationRight.setSpriteSheet(walkingTexture);
    flyingAnimationRight.addFrame(sf::IntRect(0, 140, 34, 35));
    flyingAnimationRight.addFrame(sf::IntRect(34, 140, 34, 35));

    //Crear la animación de volar izquierda. 
    Animation flyingAnimationLeft;
    flyingAnimationLeft.setSpriteSheet(walkingTexture);
    flyingAnimationLeft.addFrame(sf::IntRect(68, 140, 34, 35));
    flyingAnimationLeft.addFrame(sf::IntRect(102, 140, 34, 35));

    //Animación con la que inicia el robot. 
    Animation* currentAnimation = &walkingAnimationRight;

    //Crear el animated sprite y configurar el tiempo que toma pasar de animation frame. 
    /* Puedes usar sf::microseconds(), sf::milliseconds(), sf::seconds() */
    AnimatedSprite animatedSprite(sf::microseconds(500)); //Modificar hasta que la animación se vea bien.

    /* Yo escalé el sprite porque estaba muy pequeño. Uso el método .setScale() de SFML */
    float k1 = 1.5f;
    float k2 = 1.5f;
    animatedSprite.setScale(sf::Vector2f(k1, k2));

    /* --------- USANDO BOX2D --------- */

    //Crear el mundo. Se define primero la gravedad y luego el mundo. Recuerda que la gravedad se va ajustando poco a poco. 
    b2Vec2 gravity(0.0f, 20.0f);
    b2World world(gravity);

    MyContactListener mainlistener; //IGNORE FOR NOW.
    world.SetContactListener(&mainlistener); //IGNORE FOR NOW.

    /*
        Definir el suelo. Se inicia haciendo un BodyDef y se da la posición inicial del mismo. 
        Luego un pointer como se muestra. 
        El cuerpo debe ser agregado al mundo. Esta es la forma recomendada por Box2D.
    */
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(335.0f / PPM, 563.0f / PPM); //Esto lo sacamos en el OneNote. 
    b2Body* groundBody = world.CreateBody(&groundBodyDef); //Agregamos el cuerpo al mundo. 

    /*
        Se define la forma del cuerpo como una caja. 
        Nos limitaremos a esta forma para esta materia (me refiero a la forma de rectángulo).
        Las dimensiones de la caja son divididas a la mitad según la documentación de Box2D.
    */
    b2PolygonShape groundBox;
    groundBox.SetAsBox( 335.0f / PPM,  51.5f / PPM); //Esto lo hicimos en el Notebook.

    groundBody->SetUserData((void*)1); //IGNORE FOR NOW.

    /*
        Se agrega la forma al cuerpo y se configura la densidad como 0.
        Por default, el cuerpo está definido como estático (no se mueve). 
        El valor que ponemos como 0.0f es la densidad. 
    */
    groundBody->CreateFixture(&groundBox,0.0f);

    /*
        Ahora crearemos un cuerpo dinámico para nuestro personaje. 
    */
    b2BodyDef characterBodyDef;
    characterBodyDef.type = b2_dynamicBody; //Por default el cuerpo es "estático" como el suelo. En este caso hay que especificar dinámico.
    characterBodyDef.position.Set(10.0f / PPM, 10.0f / PPM); //Posición inicial del personaje. 
    characterBodyDef.angle = 0.0f; 
    characterBodyDef.fixedRotation = true; //Esto es para que el personaje no rote al colisionar con algo. 
    b2Body* characterBody = world.CreateBody(&characterBodyDef); //Con las características, creamos el cuerpo. 
    b2PolygonShape characterBox;
    characterBox.SetAsBox(k1 * 34.0f / PPM, k2 * 35.0f / PPM); //Como hice setScale al sprite antes, debo tomar eso en cuenta aquí. 
    
    /* Para cuerpos dinámicos, definiremos las propiedades físicas que se conocen como Fixtures. */
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &characterBox; 
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.0f;
    characterBody->CreateFixture(&fixtureDef); //Agregamos estos fixtures al cuerpo. 

    characterBody->SetUserData((void*)2); //IGNORE FOR NOW. 

    //Posición inicial del sprite. 
    animatedSprite.setPosition(sf::Vector2f(characterBody->GetPosition().x * PPM, characterBody->GetPosition().y * PPM));

    float upFlag = false;
    float rightFlag = false;
    float leftFlag = false;
    float runFlag = false;
    float jumpFlag = false;

    //Iniciamos con el loop que funciona mientras la ventana esté abierta. 
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                    case sf::Keyboard::W: upFlag = true; break;
                    case sf::Keyboard::D: rightFlag = true; break;
                    case sf::Keyboard::A: leftFlag = true; break;
                    case sf::Keyboard::LShift: runFlag = true; break;
                    case sf::Keyboard::Space: jumpFlag = true; break;
                    default: break;
                }
            }

            if (event.type == sf::Event::KeyReleased)
            {
                switch (event.key.code)
                {
                    case sf::Keyboard::W: upFlag = false; break;
                    case sf::Keyboard::D: rightFlag = false; break;
                    case sf::Keyboard::A: leftFlag = false; break;
                    case sf::Keyboard::LShift: runFlag = false; break;
                    case sf::Keyboard::Space: jumpFlag = false; break;
                    default: break;
                }
            }
        }

        if (!onAir)
        {
            if ((rightFlag == true) && (runFlag == false))
            {
                characterBody->SetLinearVelocity(b2Vec2(5.0f, 0.0f));
                currentAnimation = &walkingAnimationRight;
            }
            else if ((rightFlag == true) && (runFlag == true))
            {
                characterBody->SetLinearVelocity(b2Vec2(10.0f, 0.0f));
                currentAnimation = &walkingAnimationRight;
            }
            else if ((leftFlag == true) && (runFlag == false))
            {
                characterBody->SetLinearVelocity(b2Vec2(-5.0f, 0.0f));
                currentAnimation = &walkingAnimationLeft;
            }
            else if ((leftFlag == true) && (runFlag == true))
            {
                characterBody->SetLinearVelocity(b2Vec2(-10.0f, 0.0f));
                currentAnimation = &walkingAnimationLeft;
            }
            else if ((rightFlag == false) && (leftFlag == false) && onAir == false)
            {
                characterBody->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
            }
        }

        if ((jumpFlag == true) && (onAir == false))
        {
            if (rightFlag == true)
            {
                characterBody->SetLinearVelocity(b2Vec2(10.0f, -10.0f));
                currentAnimation = &jumpingAnimationRight;
            }
            else if (leftFlag == true)
            {
                characterBody->SetLinearVelocity(b2Vec2(-10.0f, -10.0f));
                currentAnimation = &jumpingAnimationLeft;
            }
            else
            {
                characterBody->SetLinearVelocity(b2Vec2(0.0f, -10.0f));
                currentAnimation = &jumpingAnimationLeft;
            }
        }

        
        animatedSprite.play(*currentAnimation);
        animatedSprite.setPosition(sf::Vector2f(characterBody->GetPosition().x * PPM, characterBody->GetPosition().y * PPM));

        world.Step(clock.restart().asSeconds(), 6, 2);

        //Limpiar la ventana. 
        animatedSprite.update(clock.restart());

        //Dibujar el fondo. Debe ser dibujado en el orden adecuado.
        window.clear();

        window.draw(layer2bg);
        window.draw(layer3bg);
        window.draw(layer4bg);

        //Dibujar al robot. 
        window.draw(animatedSprite);

         //Mostrar dibujos en la ventana.
        window.display();
    }
    return 0;
}

