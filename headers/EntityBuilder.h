//#pragma once
//#include <utility>
//#include <iostream>
//
//#include "Player.h"
//
//class EntityBuilder {
//protected:
//    std::shared_ptr<Entity> entity;
//
//public:
//    explicit EntityBuilder(std::shared_ptr<Entity>input_entity) : entity(std::move(input_entity)){};
//
//    EntityBuilder& setPositon(int x, int y) {
//        entity->x = x;
//        entity->y = y;
//        return *this;
//    }
//
//    EntityBuilder& setHp(int hp) {
//        entity->hp = hp;
//        return *this;
//    }
//
//    virtual std::shared_ptr<Entity> build() {
//        return entity;
//    }
//};
//
//class PlayerBuilder : public EntityBuilder {
//public:
//    PlayerBuilder& setLevel(int level) {
//        auto* playerPtr = dynamic_cast<Player*>(entity.get());
//        if (playerPtr) {
//            playerPtr->level = level;
//            std::cout << "DEBUG";
//            return *this;
//        } else {
//            // TODO throw exception
//        }
//    }
//
//    PlayerBuilder& setName(std::string& name) {
//        auto* playerPtr = dynamic_cast<Player*>(entity.get());
//        if (playerPtr) {
//            playerPtr->name= name;
//            std::cout << "DEBUG";
//            return *this;
//        } else {
//            // TODO throw exception
//        }
//    }
//};