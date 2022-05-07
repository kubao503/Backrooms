#include "player.h"

void Player::setLocalVelocity(const b2Vec2 &newVelocity)
{
    const float angle{body_->GetAngle()};
    body_->SetLinearVelocity(rotateVec(newVelocity, angle));
}

Player::Player(b2World &world, const b2Vec2 &position, float angle)
    : Object{world, Type::PLAYER, position, angle}
{
    // Collision filter for PLAYER is set in Object's constructor

    // New fixture is added at the front
    body_->CreateFixture(&argList[static_cast<int>(Type::CAMERA)].fixDef_);

    // Changing camera mass to zero
    body_->GetFixtureList()->SetDensity(0.0f);
    body_->ResetMassData();

    setCollisionFilter(Category::CAMERA);
    setSensor(true);

    keyPresses_[sf::Keyboard::Q] = false;
}

void Player::move()
{
    static constexpr float LINEAR_VELOCITY = 2.0f;
    static constexpr float SPRINT_MULTIPLIER = 2.0f;
    b2Vec2 newVelocity(0.0f, 0.0f);

    // Moving
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        newVelocity += b2Vec2(0.0f, LINEAR_VELOCITY);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        newVelocity += b2Vec2(0.0f, -LINEAR_VELOCITY);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        newVelocity += b2Vec2(LINEAR_VELOCITY, 0.0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        newVelocity += b2Vec2(-LINEAR_VELOCITY, 0.0f);
    }

    newVelocity.Normalize();
    newVelocity *= LINEAR_VELOCITY;

    // Sprint
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
    {
        newVelocity *= SPRINT_MULTIPLIER;
    }

    setLocalVelocity(newVelocity);
}

void Player::lookAround(UserIO &userIO)
{
    static constexpr float ANGULAR_VELOCITY = 0.15f;

    // looking around
    int mouseXMovement(userIO.getMouseXMovement());
    body_->SetAngularVelocity(ANGULAR_VELOCITY * mouseXMovement);
}

#include <iostream> // DEBUG

void Player::itemOperations(Game &game)
{
    // Pickig up items
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && nearbyItem_)
    {
        auto item = game.shareObject(nearbyItem_);
        item->destroyBody();
        ownedItems_.push_back(std::move(item));
        // Deleting b2Body calls EndContact
        // but this is likely done by another "thread"
        // So Item is automatically removed from visibleObjects_ and nearbyItem_
    }

    // Dropping item
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
    {
        if (ownedItems_.size())
        {
            ownedItems_[currentItemIdx_]->drop(*body_->GetWorld(), *this);
            ownedItems_.erase(std::next(ownedItems_.begin(), currentItemIdx_));
            if (currentItemIdx_ == ownedItems_.size())
            {
                currentItemIdx_ = 0;
            }
        }
    }

    // Changing item from inventory
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && !keyPresses_.at(sf::Keyboard::Q))
    {
        if (++currentItemIdx_ >= ownedItems_.size())
            currentItemIdx_ = 0;
    }

    keyPresses_[sf::Keyboard::Q] = sf::Keyboard::isKeyPressed(sf::Keyboard::Q);
}

void Player::control(UserIO &userIO, Game &game)
{
    move();
    lookAround(userIO);
    itemOperations(game);

    // Sorting visible objects by distance from the player
    const b2Vec2 playerPosition{getPosition()};
    std::sort(visibleObjects_.begin(), visibleObjects_.end(), [&playerPosition](const Object2D *objA, const Object2D *objB)
              { return distance(playerPosition, objA->getPosition()) > distance(playerPosition, objB->getPosition()); });
}

const std::vector<const Object2D *> &Player::getVisibleObjects() const
{
    return visibleObjects_;
}

void Player::doItemAction(const b2World &world) const
{
    for (auto &&item : ownedItems_)
        item->action(world, *this);
}


void Player::objectObserved(const Object2D *object)
{
    std::cerr << "object observed\n";
    visibleObjects_.push_back(object);
}

void Player::objectLost(const Object2D *object)
{
    std::cerr << "object lost\n";
    auto foundObj = std::find(visibleObjects_.begin(), visibleObjects_.end(), object);
    if (foundObj != visibleObjects_.end())
        visibleObjects_.erase(foundObj);
}

void Player::itemContact(const Item *item)
{
    std::cerr << "Item contact\n";
    nearbyItem_ = item;
}

void Player::itemLost()
{
    std::cerr << "Item lost\n";
    nearbyItem_ = nullptr;
}
