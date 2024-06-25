#ifndef EFFECT_HPP_
#define EFFECT_HPP_

#include "color.hpp"
#include "key.hpp"

#include <array>
#include <memory>

struct Theme {
	Color colors[8] = {
		Color(0, 0, 0),
		Color(66, 19, 137),
		Color(true, 16, 0.83, 0.85)
	};    
};

struct Effect {
	virtual ~Effect() {};
	
	virtual void update(const Key& key) = 0;
	virtual Color getColor(const Key& key, const Theme& theme) = 0;
};

struct DefaultEffect : Effect {
	void update(const Key& key) override;
	Color getColor(const Key& key, const Theme& theme) override;
};

struct FadeOutEffect : Effect {
	void update(const Key& key) override;
	Color getColor(const Key& key, const Theme& theme) override;
private:
	std::array<double, 128> m_keys;
	double m_releaseRate = 0.55;
};

struct RainbowEffect : Effect {
	void update(const Key& key) override;
	Color getColor(const Key& key, const Theme& theme) override;
private:
	double m_rot = 0;
	double m_rotRate = 4.0;
};

inline std::unique_ptr<Effect> createEffect(int id) {
	switch (id) {
	case 0: return std::make_unique<DefaultEffect>();
	case 1: return std::make_unique<FadeOutEffect>();
	default: return std::make_unique<DefaultEffect>();
	}
}

#endif
