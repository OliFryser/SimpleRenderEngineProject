#include "Engine/Component.h"

namespace Asteroids {
	class ComponentLaser : public MyEngine::Component {
		const float Velocity = 400.0f;
		float _startTime;
		glm::vec2 _direction;

	public:
		void Update(float) override;
		void Init() override;
	};
}