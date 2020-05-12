#include "Entity/Component.h"
class ProjectileBehaviour : public Component {
public:
	ProjectileBehaviour(json& args);
	void init(json& args);
	~ProjectileBehaviour() {};
	void start() override;
	void update() override;
	void setDir(Vector3 dir);
	void setSpeed(float speed);
	void setSource(std::string sourc);
	std::string getSource();
	void setDamage(float dmg);

	void OnCollision(Entity* other) override;

	bool ReceiveEvent(Event& event) override;

private:
	float speed;
	float damage;
	bool destructible;
	std::string source;
	Vector3 dir;
	float bordeSup;
	float bordeInf;
	float bordeDer;
	float bordeIzq;
};