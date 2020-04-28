#include "Entity/Component.h"
class ProjectileBehaviour : public Component {
public:
	ProjectileBehaviour(json& args);
	void init(json& args);
	~ProjectileBehaviour() {};
	void update() override;
	void setDir(Vector3 dir);
	void setSpeed(float speed);

private:
	float speed;
	Vector3 dir;
	float bordeSup;
	float bordeInf;
	float bordeDer;
	float bordeIzq;
};