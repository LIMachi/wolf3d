//
// Created by Hugo MARTZOLF on 11/29/18.
//

#include "../../inc/env.h"

t_vector	rotate_2d(t_vector vec, double deg)
{
	return ((t_vector){.x = vec.x * cos(deg * DEG_TO_RAD)
						- vec.y * sin(deg * DEG_TO_RAD),
						.y = vec.x * sin(deg * DEG_TO_RAD)
						+ vec.y * cos(deg * DEG_TO_RAD)});
}
