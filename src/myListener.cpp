#include "myListener.h"

void MyListener::BeginContact(b2Contact *contact)
{
    Object *objA = (Object *)contact->GetFixtureA()->GetBody()->GetUserData().pointer;
    Object *objB = (Object *)contact->GetFixtureB()->GetBody()->GetUserData().pointer;

    if ((dynamic_cast<Enemy *>(objA) && dynamic_cast<Player *>(objB)) || (dynamic_cast<Player *>(objA) && dynamic_cast<Enemy *>(objB)))
    {
        std::cerr << "YOU FOOL YOU DIED\n";
        return;
    }

    Player *player = dynamic_cast<Player *>(objA);
    Item *item = dynamic_cast<Item *>(objB);
    if (player && item)
    {
        player->itemContact(item);
        return;
    }
    player = dynamic_cast<Player *>(objB);
    item = dynamic_cast<Item *>(objA);
    if (player && item)
    {
        player->itemContact(item);
        return;
    }
}
