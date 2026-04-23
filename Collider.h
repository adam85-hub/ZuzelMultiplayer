#include "vec2.h"
#include <allegro5/allegro.h>
#include "Player.h"
#include <cmath>

enum class ColliderType {
    Player,
    Wall,

    /// w celu okreœlania jak gracz dotyka linii startu
    Start,
    /// w celu okreœlania jak gracz dotyka linii mety
    Meta
};

class Collider {
private:
    ColliderType _type;
    Player* _owner;
    bool _isColliding = false;

	Utils::vec2 _start_point;
	Utils::vec2 _end_point;
    float _radius;


public:
    static float GetDistanceBetweenSegments(Utils::vec2 p1, Utils::vec2 p2, Utils::vec2 p3, Utils::vec2 p4);
    Collider(ColliderType type, Player* owner, float radius = 0.0f) : _owner(owner), _radius(radius), _type(type) {}

    // --- GETTERY ---
	Utils::vec2 GetCenter() const { return (_owner->position);}
	Player* GetOwnerPlayer() const { return _owner; }
    Utils::vec2 GetStartPoint() const { return _start_point; }
    Utils::vec2 GetEndPoint() const { return _end_point; }
    float GetRadius() const { return _radius; }
    bool GetColliding() const { return _isColliding; }
    ColliderType GetType() const { return _type; }

    // --- SETTERY ---
    void SetStartPoint(const Utils::vec2& start) { _start_point = start; }
    void SetEndPoint(const Utils::vec2& end) { _end_point = end; }
    void SetRadius(float radius) { _radius = radius; }
    void SetColliding(bool state) { _isColliding = state; }


	// --- Collision Detection ---
    void UpdateHitbox();
	bool CheckCollision(const Collider& other) const;

	// --- Debug ---
    void DrawDebug(ALLEGRO_COLOR color);
    void ResetCollision() { _isColliding = false; }

};