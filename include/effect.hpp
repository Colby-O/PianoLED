#ifndef EFFECT_HPP_
#define EFFECT_HPP_

#include "color.hpp"
#include "key.hpp"

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

#endif
