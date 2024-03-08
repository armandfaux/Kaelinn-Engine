#ifndef EVENT_HPP_
#define EVENT_HPP_

#include "../core/Entity.hpp"
#include "../math/Vector2.hpp"

#include <cereal/archives/binary.hpp>
#include <cereal/types/memory.hpp>
#include <sstream>
#include <string>

namespace kln {
// systemB will receive events from systemA
#define SET_EVENT_ROUTE(systemA, systemB) systemA->subscribe(systemB->getSubscriber());

    enum Type {
        unknown,
        pos,                // Communicate an entity position
        input,              // Communicate a user input
        newEntity,          // Order the creation of an entity
        delEntity,          // Order the deletion of an entity
        newScene,           // Order the creation of a scene
        delScene,           // Order the deletion of a scene
        collisionEnter,     // Communicate 2 entities that start colliding
        collisionExit,      // Communicate 2 entities that stop colliding
        switchScene,        // Order a scene change
        clientConnection,   // Inform a newly connected client
        exit                // Close the window and exit the game
    };

    enum Key {
        Unknown = -1,
        A = 0,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z,
        Space,
        Enter,
        Num1,
        Num2,
        Num3,
        Num4,
        Num5,
        Num6,
        Num7,
        Num8,
        Num9,
        Num0,
        Left,
        Right,
        Up,
        Down,
        MouseLeft,
        MouseRight,
        MouseMiddle,
        MouseXButton1,
        MouseXButton2,
    };

    struct Event;

    struct Event {
        Type type = Type::unknown;
        uint32_t clientId = 0;

        Key key = Key::Unknown;
        bool keyPressed = false;
        bool keyReleased = false;
        uint32_t entityId1 = 0;
        uint32_t entityId2 = 0;
        Vector2 pos = {0, 0};
        uint32_t sceneId = 0;
        std::string prefabName = "";

        template <class Archive> void serialize(Archive &ar) {
            ar(
                CEREAL_NVP(type),
                CEREAL_NVP(clientId),
                CEREAL_NVP(key),
                CEREAL_NVP(keyPressed),
                CEREAL_NVP(keyReleased),
                CEREAL_NVP(entityId1), CEREAL_NVP(entityId2),
                CEREAL_NVP(pos),
                CEREAL_NVP(sceneId),
                CEREAL_NVP(prefabName)
            );
        }
    };

    inline std::ostream &operator<<(std::ostream &os, const Event &event) {
        os << "\n[EVENT] "
           << ((event.type == Type::pos)                ? "POSITION"
               : (event.type == Type::input)            ? "INPUT"
               : (event.type == Type::newEntity)        ? "NEW ENTITY"
               : (event.type == Type::delEntity)        ? "DEL ENTITY"
               : (event.type == Type::collisionEnter)   ? "COLLISION ENTER"
               : (event.type == Type::collisionExit)    ? "COLLISION EXIT"
               : (event.type == Type::switchScene)      ? "SCENE SWITCH"
               : (event.type == Type::newScene)         ? "NEW SCENE"
               : (event.type == Type::delScene)         ? "DEL SCENE"
               : (event.type == Type::clientConnection) ? "CLIENT CONNECTED"
               : (event.type == Type::exit)             ? "EXIT"
                                                        : "UNKNOWN");

        os << "\n  +-------------------+"
           << "\n  | .clientId         : " << event.clientId << "\n  | .pos              : " << event.pos
           << "\n  | .key              : " << event.key
           << "\n  | .keyPressed       : " << (event.keyPressed ? "True" : "False")
           << "\n  | .keyReleased      : " << (event.keyReleased ? "True" : "False")
           << "\n  | .entityId1        : " << event.entityId1
           << "\n  | .entityId2        : " << event.entityId2
           << "\n  | .sceneId          : " << event.sceneId
           << "\n  | .prefabName       : " << (event.prefabName == "" ? "None" : event.prefabName)
           << "\n  +-------------------+\n";

        return os;
    }
} // namespace kln

#endif /* !EVENT_HPP_ */