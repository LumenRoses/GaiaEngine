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

        void* o1 = f1->GetUserData();
        void* o2 = f2->GetUserData();

        if ((int)o1 == 1)
        {
            onAir = false;
            cout << "Reached ground." << endl;
        }

        if ((int)o2 == 1)
        {
            onAir = false;
            cout << "Reached ground." << endl;
        }

    }

    void EndContact(b2Contact* contact)
    {

        b2Fixture* f1 = contact->GetFixtureA();
        b2Fixture* f2 = contact->GetFixtureB();

        void* o1 = f1->GetUserData();
        void* o2 = f2->GetUserData();

        if ((int)o1 == 1)
        {
            onAir = true;
            cout << "Left ground." << endl;
        }

        if ((int)o2 == 1)
        {
            onAir = true;
            cout << "Left ground." << endl;
        }
        
    }
};