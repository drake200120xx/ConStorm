/*
 Code by Drake Johnson
*/
#include "../../include/cons/utilities/random.hpp"

namespace cons
{
	std::default_random_engine Random::s_Engine;

	void Random::engine_init()
	{
		if (s_Engine_init)
			return;

		s_Engine_init = true;

		// Seed engine
		auto rand_seed = std::random_device();
		s_Engine.seed(rand_seed());
	}

} // namespace cons
