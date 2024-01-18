# Game Engine Documentation

## Namespace
The namespace for the entire game engine is ge

## ECS
This game engine is based on a ECS model (Entity - Component - System).

Each scene is composed of a vector of Entity
Every object in the game MUST exist as an entity (may be the player, the bullets or even the UI elements)

An entity's type is defined by the components it owns, they are represented as a vector of IComponent objects
A component represents a attribute of the entity that owns it
There are components for many aspects of the game (physics, sprite, input, etc...)

## How to create your own game

You can use the already existing systems and components provided in the game engine
But if you want to push it further, you should create your own systems and components to match your game's requirements

Every custom component must be located in /engine/component and must inherit from the AComponent abstract class
Every custom system must be located in /engine/system and must inherit from the ASystem abstract class
They must be compliant with the associated interfaces to work properly

Example of a custom System and Component :

// /engine/component/MyCustomComp.hpp
class MyCustomComp : public AComponent
{
    public:
        MyCustomComp();
        ~MyCustomComp();
};

// /engine/system/MyCustomSystem.hpp
class CustomSystem : public ASystem
{
    public:
        CustomSystem();
        ~CustomSystem();

        void functionA();
        bool functionB();

        void update(std::vector<std::shared_ptr<Entity>> entities) override;
        // This override method is mandatory
};


## Inter-System Communication
Systems are independant and must not have direct interactions to keep a proper abstraction inside the engine.
Therefore, the engine uses a shared communication medium to allow systems to communicate information.
This medium is the **Event Bus**.

The Event Bus is managed in a decentralized way, it is composed of **Publishers** & **Subscribers**.

A system that needs to transmit data owns a private publisher.
A system that needs to receive data owns a private subscriber.
One can own both a publisher and a subscriber.

*Publisher implementation*

class Publisher
{
    public:
        Publisher();
        ~Publisher();

        void publish(Event& event);
        void subscribe(std::shared_ptr<ISubscriber> subscriber);

    private:
        std::vector<std::shared_ptr<ISubscriber>> _subscribers;
};

The subscribe() method adds the given subscriber to the publisher's list of subscribers.
The publish() method calls the publisher's subscribers onEvent() method with the broadcasted event reference passed as parameter.

*Subscriber implementation*

class ISubscriber
{
    public:
        virtual void onEvent(Event& event) = 0;
};

It's intended that the subscriber interface looks empty. Every system reacts differently when they receive a certain information.
Thus, each system must implement its own subscriber class that will handle the event according to their needs

The publishers are used to broadcast information as **Events**.
An Event is a structure that can contain any type of information

*Event implementation*

// TODO update the structure with the latest changes
struct Event
{
    std::string type; // (input | pos | scene )

    Key key;
    uint32_t entityId;
    Vector2 pos;
};

This event bus model combines genericity & speed.
All type of information are shared under the same format, and each system only subscribe to the required publishers.
This way, none of them receive useless information.