#include <box2d/box2d.h>
#include <iostream>

using namespace std;

bool onAir = true;

class MyContactListener : public b2ContactListener
{
    void BeginContact(b2Contact* contact) 
    {

        b2Fixture* f1 = contact->GetFixtureA();
        b2Fixture* f2 = contact->GetFixtureB();

        b2Body* b1 = f1->GetBody();
        b2Body* b2 = f2->GetBody();

        void* o1 = b1->GetUserData();
        void* o2 = b2->GetUserData();

        if ((int)o1 == 1 && (int)o2 == 2)
        {
            onAir = false;
            cout << "Touched ground!" << endl;
        }
    }

    void EndContact(b2Contact* contact)
    {
        b2Fixture* f1 = contact->GetFixtureA();
        b2Fixture* f2 = contact->GetFixtureB();

        b2Body* b1 = f1->GetBody();
        b2Body* b2 = f2->GetBody();

        void* o1 = b1->GetUserData();
        void* o2 = b2->GetUserData();

        if ((int)o1 == 1 && (int)o2 == 2)
        {
            onAir = true;
            cout << "On air!" << endl;
        }
   }
};