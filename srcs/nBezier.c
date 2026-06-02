#include "../include/cBezierVisualizer.h"

float	lerp(const float start, const float target, const float t)
{
	return (start + t * (target - start));
}

fVec3	nBezier(const iVec3 *control_points, const unsigned int control_point_count, const float t)
{
	if (control_point_count < 3)
		return ((fVec3) {
				.x = lerp(control_points[0].x, control_points[1].x, t),
				.y = lerp(control_points[0].y, control_points[1].y, t),
			});
	const fVec3 lp = nBezier(control_points, control_point_count - 1, t);
	const fVec3 rp = nBezier(control_points + 1, control_point_count - 1, t);

	return ((fVec3) {
			.x = lerp(lp.x, rp.x, t),
			.y = lerp(lp.y, rp.y, t),
		});
}
