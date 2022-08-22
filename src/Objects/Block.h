#pragma once
#include "SFML/Graphics.hpp"
#include <array>
#include <list>

struct item {
    int count;
    int slot;
    std::string id;
};

struct Block {
public:
    virtual std::string getid() { return id; }
    virtual sf::Vector2i getpos() { return pos; }
    virtual std::string getname() { return custom_name; }
    std::string id;
    sf::Vector2i pos;
    int rotation;
    std::string custom_name;
    sf::Sprite sprite;
};

struct chest : public Block {
public:
    explicit chest(const Block &block) {
        id = block.id;
        pos = block.pos;
        custom_name = block.custom_name;
    }
    std::string getid() override {
        return Block::getid();
    }
    sf::Vector2i getpos() override {
        return Block::getpos();
    }
    std::string getname() override {
        return Block::getname();
    }
    std::array<item *, 50> items{};
};

struct conveyor : public Block {
public:
    explicit conveyor(const Block &block) {
        id = block.id;
        pos = block.pos;
        custom_name = block.custom_name;
    }
    std::string getid() override {
        return Block::getid();
    }
    sf::Vector2i getpos() override {
        return Block::getpos();
    }
    std::string getname() override {
        return Block::getname();
    }

    bool hasItems() {
        return item != nullptr;
    }
    item *item = nullptr;
};