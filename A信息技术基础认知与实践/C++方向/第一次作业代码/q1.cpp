// 要求 C++ 17
// 要求 MinGW 13.0 工具链，线程模型 posix
// EasyX 240601

#include <iostream>
#include <easyx.h>
#include <set>
#include <unordered_map>
#include <cmath>
#include <memory>
#include <random>
#include <thread>
#include <vector>

constexpr float TIME_SCALE = 0.1f;
constexpr float BOUND_X = 600.0;
constexpr float BOUND_Y = 600.0;

float random(float from, float to) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(from, to);
    return dis(gen);
}

struct Vec2f {
    float x;
    float y;

    Vec2f() : x(0), y(0) {}
    Vec2f(float x, float y) : x(x), y(y) {}

    [[nodiscard]] bool isZero() const {
        return x == 0 && y == 0;
    }

    Vec2f operator+(const Vec2f& other) const {
        return {x + other.x, y + other.y};
    }

    Vec2f operator-(const Vec2f& other) const {
        return {x - other.x, y - other.y};
    }

    Vec2f operator*(float scalar) const {
        return {x * scalar, y * scalar};
    }

    Vec2f operator/(float scalar) const {
        return {x / scalar, y / scalar};
    }

    [[nodiscard]] Vec2f normalize() const {
        float magnitude = this->magnitude();
        return {x / magnitude, y / magnitude};
    }

    [[nodiscard]] float magnitude() const {
        return std::sqrt(x * x + y * y);
    }

    [[nodiscard]] float dot(const Vec2f& other) const {
        return x * other.x + y * other.y;
    }

    [[nodiscard]] Vec2f reflect(const Vec2f& normal) const {
        return *this - normal * 2.0f * this->dot(normal);
    }
};

class Entity;
class Component;

template <typename ComponentType, std::enable_if_t<std::is_base_of_v<Component, ComponentType>, int> = 0>
class System {
public:
    System() = default;
    ~System() = default;

    ComponentType* addComponent(ComponentType* component) {
        m_components.insert(component);
        return component;
    }

    void removeComponent(ComponentType* component) {
        m_components.erase(component);
    }

    void update() {
        for (auto& component : m_components) {
            component->update();
        }
    }
protected:
    std::set<ComponentType*> m_components;
};

class Component {
public:
    virtual void update() = 0;
    virtual ~Component() = default;
};

class Entity {
public:
    Entity() = default;
    ~Entity() {
        for (auto& component : m_components) {
            delete component.second;
        }
    }

    void addComponent(const std::string& name, Component* component) {
        m_components.insert({name, component});
    }

    template <typename ComponentType, typename... Args>
    ComponentType* addComponent(Args&&... args) {
        static_assert(std::is_constructible_v<ComponentType, Entity&, Args...>);
        if constexpr (std::is_constructible_v<ComponentType, Entity&, Args...>) {
            auto* ptr = new ComponentType(*this, std::forward<Args>(args)...);
            m_components[ComponentType::getId()] = reinterpret_cast<Component*>(ptr);
            return ptr;
        }
        return nullptr;
    }

    void removeComponent(const std::string& name) {
        m_components.erase(name);
    }

    Component* getComponent(const std::string& name) {
        return m_components[name];
    }

    template <typename T>
    T* getComponent() {
        if (!m_components.count(T::getId())) return nullptr;
        return dynamic_cast<T*>(m_components[T::getId()]);
    }

private:
    std::unordered_map<std::string, Component*> m_components;
};

class PositionComponent;
class VelocityComponent;
class CollisionComponent;

class VelocityComponent : public Component {
public:
    VelocityComponent(Entity& entity, float x, float y) : m_entity(entity), m_x(x), m_y(y) {}
    VelocityComponent(Entity& entity, Vec2f vel) : m_entity(entity), m_x(vel.x), m_y(vel.y) {}
    explicit VelocityComponent(Entity& entity) : m_entity(entity) {}

    void update() override {
    }

    [[nodiscard]] float getX() const {
        return m_x;
    }

    [[nodiscard]] float getY() const {
        return m_y;
    }

    [[nodiscard]] Vec2f get() const {
        return {m_x, m_y};
    }

    void setX(float x) {
        m_x = x;
    }

    void setY(float y) {
        m_y = y;
    }

    void set(Vec2f vel) {
        m_x = vel.x;
        m_y = vel.y;
    }

    static std::string getId() {
        return "VelocityComponent";
    }

private:
    float m_x {};
    float m_y {};

    Entity& m_entity;
};

class PositionComponent : public Component {
public:
    PositionComponent(Entity& entity, float x, float y) : m_entity(entity), m_x(x), m_y(y) {}
    PositionComponent(Entity& entity, Vec2f pos) : m_entity(entity), m_x(pos.x), m_y(pos.y) {}
    explicit PositionComponent(Entity& entity) : m_entity(entity) {}

    void update() override {
        m_x += m_entity.getComponent<VelocityComponent>()->getX() * TIME_SCALE;
        m_y += m_entity.getComponent<VelocityComponent>()->getY() * TIME_SCALE;

        // std::cout << "PositionComponent::update()" << std::endl;
    }

    [[nodiscard]] float getX() const {
        return m_x;
    }

    [[nodiscard]] float getY() const {
        return m_y;
    }

    [[nodiscard]] Vec2f get() const {
        return {m_x, m_y};
    }

    void setX(float x) {
        m_x = x;
    }

    void setY(float y) {
        m_y = y;
    }

    void set(Vec2f pos) {
        m_x = pos.x;
        m_y = pos.y;
    }

    static std::string getId() {
        return "PositionComponent";
    }

private:
    float m_x {};
    float m_y {};
    Entity& m_entity;
};

using MovementSystem = System<PositionComponent>;

class CollisionComponent : public Component {
public:
    CollisionComponent(Entity& entity, float radius, float mass) : m_entity(entity), m_radius(radius), m_mass(mass) {}

    [[nodiscard]] float getRadius() const {
        return m_radius;
    }

    [[nodiscard]] float getMass() const {
        return m_mass;
    }

    void setRadius(float radius) {
        m_radius = radius;
    }

    void setMass(float mass) {
        m_mass = mass;
    }

    Entity& getEntity() {
        return m_entity;
    }

    static std::string getId() {
        return "CollisionComponent";
    }

    void update() override {}
private:
    float m_radius;
    float m_mass;
    Entity& m_entity;
};

class RenderComponent : public Component {
public:
    explicit RenderComponent(Entity& entity) : m_entity(entity) {}

    void update() override {
        auto* posComp = m_entity.getComponent<PositionComponent>();
        auto* collisionComp = m_entity.getComponent<CollisionComponent>();

        fillcircle(posComp->getX(), posComp->getY(), collisionComp->getRadius());
    }

    static std::string getId() {
        return "RenderComponent";
    }

    Entity& getEntity() {
        return m_entity;
    }

private:
    Entity& m_entity;
};

class CollisionSystem : public System<CollisionComponent> {
public:
    void update() {
        checkCollisions();
    }

    void checkCollisions() {
        for (auto & m_collider : m_components) {
            auto bound = outOfBounds(m_collider);
            if (!bound.isZero()) {
                collideBounce1(m_collider, bound);
            }
        }
        for (auto it1 = m_components.begin(); it1 != m_components.end(); ++it1) {
            auto it2 = it1;
            for (++it2; it2 != m_components.end(); ++it2) {
                if (checkCollision(*it1, *it2)) {
                    collideBounce2(*it1, *it2);
                }
            }
        }
    }
private:

    static bool checkCollision(CollisionComponent* component1, CollisionComponent* component2) {
        auto* pos1 = component1->getEntity().getComponent<PositionComponent>();
        auto* pos2 = component2->getEntity().getComponent<PositionComponent>();
        double distSquared = std::pow(pos1->getX() - pos2->getX(), 2) + std::pow(pos1->getY() - pos2->getY(), 2);
        return distSquared <= std::pow(component1->getRadius() + component2->getRadius(), 2);
    }

    static Vec2f outOfBoundsX(PositionComponent* comp) {
        if (comp->getX() < 0) return {  1, 0 };
        if (comp->getX() > BOUND_X) return { -1, 0 };
        return { 0, 0 };
    }

    static Vec2f outOfBoundsY(PositionComponent* comp) {
        if (comp->getY() < 0) return { 0,  1 };
        if (comp->getY() > BOUND_Y) return { 0, -1 };
        return { 0, 0 };
    }

    static Vec2f outOfBounds(CollisionComponent* comp) {
        auto* pos = comp->getEntity().getComponent<PositionComponent>();
        return outOfBoundsX(pos) + outOfBoundsY(pos);
    }

    static float scatter(float f) {
        float scatter = random(-0.01f, 0.01f);
        return f * (1.0f + scatter);
    }

    static Vec2f scatter(const Vec2f& v) {
        return { scatter(v.x), scatter(v.y) };
    }

    static void collideBounce1(CollisionComponent* comp, const Vec2f& normal) {
        auto* vel = comp->getEntity().getComponent<VelocityComponent>();

        if (vel) {
            vel->set(scatter(vel->get().reflect(normal)));
        }
    }

    static void collideBounce2(CollisionComponent* comp1, CollisionComponent* comp2) {
        auto* vel1 = comp1->getEntity().getComponent<VelocityComponent>();
        auto* vel2 = comp2->getEntity().getComponent<VelocityComponent>();
        auto* pos1 = comp1->getEntity().getComponent<PositionComponent>();
        auto* pos2 = comp2->getEntity().getComponent<PositionComponent>();

        if (vel1 && vel2) {
            Vec2f normal = pos1->get() - pos2->get();
            normal = normal.normalize();

            Vec2f reflect1 = vel1->get().reflect(normal);
            vel1->set(scatter(reflect1));

            Vec2f reflect2 = vel2->get().reflect(normal);
            vel2->set(scatter(reflect2));
        }
    }
};

class RenderSystem : public System<RenderComponent> {
public:
    RenderSystem() {
        loadimage(&m_img, "back.jpg", 1024, 768, true);
    }

    void update() {
        static int hue = 0;
        static int hueCounter = 0;
        static COLORREF color = HSVtoRGB(0, 1, 1);

        if (hueCounter++ % 10 == 0) {
            color = HSVtoRGB(static_cast<float>(hue++ % 360), 1, 1);
        }

        cleardevice();

        // 用双缓冲画，不然闪
        BeginBatchDraw();

        setbkcolor(WHITE);
        drawBackground();

        setfillcolor(color);
        setlinecolor(color);

        for (auto m_component : m_components) {
            // m_component->update();
        }

        FlushBatchDraw();
        EndBatchDraw();
    }
private:
    IMAGE m_img;

    void drawBackground() const {
        putimage(0, 0, &m_img);
        for (int i = 0; i < 16; i++) {
            setlinecolor(BLACK);
            LINESTYLE style;
            style.thickness = 3;
            setlinestyle(&style);
            line(0, i * BOUND_Y / 16, BOUND_X, i * BOUND_Y / 16);
            line(i * BOUND_X / 16, 0, i * BOUND_X / 16, BOUND_Y);
        }
    }
};

int main() {
    std::cout << "Hello, World!" << std::endl;
    std::vector<std::unique_ptr<Entity>> entities;

    MovementSystem movementSystem;
    CollisionSystem collisionSystem;
    RenderSystem renderSystem;

    for (int i = 0; i < 4; i++) {
        std::unique_ptr<Entity> entity = std::make_unique<Entity>();
        auto* posComp = entity->addComponent<PositionComponent>(random(0,  BOUND_X), random(0, BOUND_Y));
        /*auto* velComp =*/ entity->addComponent<VelocityComponent>(random(-10, 10), random(-10, 10));
        auto* collisionComp = entity->addComponent<CollisionComponent>(25, 10);
        auto* renderComp = entity->addComponent<RenderComponent>();

        movementSystem.addComponent(posComp);
        collisionSystem.addComponent(collisionComp);
        renderSystem.addComponent(renderComp);

        entities.push_back(std::move(entity));
    }

    initgraph(BOUND_X, BOUND_Y);

    ExMessage msg {};
    while (true) {
        if (peekmessage(&msg, -1, false)) {
            getmessage(&msg);
            if (msg.message == WM_CLOSE) {
                break;
            }
        }
        movementSystem.update();
        collisionSystem.update();
        renderSystem.update();
    }

    return 0;
}