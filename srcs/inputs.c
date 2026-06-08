#include "../include/cBezierVisualizer.h"

inline static void	selectNextPoint(Context *context)
{
	context->current_point = (context->current_point + 1) % context->control_point_count;
}

inline static void	selectPrevPoint(Context *context)
{
	context->current_point = (context->current_point - 1) + (context->control_point_count * (context->current_point == 0));
}

inline static void	createPoint(Context *context)
{
	context->control_point_count += 1;
	context->control_points = realloc(context->control_points, context->control_point_count * sizeof(*context->control_points));
	memmove(&context->control_points[context->current_point + 1], &context->control_points[context->current_point], (context->control_point_count - 1 - context->current_point) * sizeof(fVec3));
	selectNextPoint(context);
}

inline static void	deleteLastPoint(Context *context)
{
	if (context->control_point_count == 2)
		return ;
	context->control_point_count -= 1;
	context->control_points = realloc(context->control_points, context->control_point_count * sizeof(*context->control_points));
	if (context->current_point >= context->control_point_count)
		context->current_point = context->control_point_count - 1;
}

inline static void	decrementMoveResolution(Context *context)
{
	context->move_resolution *= 10;
	if (context->move_resolution > MAX_MOVE_RESOLUTION / 10)
		context->move_resolution = 0.1f;
}

inline static void	incrementMoveResolution(Context *context)
{
	context->move_resolution /= 10;
	if (context->move_resolution < MIN_MOVE_RESOLUTION)
		context->move_resolution = MIN_MOVE_RESOLUTION;
}

inline static void	decrementCurvePointCount(Context *context)
{
	if (context->curve_point_count == 1)
		return ;
	context->curve_point_count--;
	context->curve_resolution = 1.0f / context->curve_point_count;
}

inline static void	incrementCurvePointCount(Context *context)
{
	if (context->curve_point_count == 999)
		return ;
	context->curve_point_count++;
	context->curve_resolution = 1.0f / context->curve_point_count;
}

void	inputHandler(char keycode, void *v_context)
{
	Context	*context = v_context;

	switch(keycode) {
		case 27: context->should_quit = 1; break;
		case 'w': context->control_points[context->current_point].y -= context->move_resolution; break;
		case 'a': context->control_points[context->current_point].x -= context->move_resolution; break;
		case 's': context->control_points[context->current_point].y += context->move_resolution; break;
		case 'd': context->control_points[context->current_point].x += context->move_resolution; break;
		case 'q': selectNextPoint(context); break;
		case 'Q': selectPrevPoint(context); break;
		case '+': createPoint(context); break;
		case '-': deleteLastPoint(context); break;
		case 'E': incrementMoveResolution(context); break;
		case 'e': decrementMoveResolution(context); break;
		case 'r': incrementCurvePointCount(context); break;
		case 'R': decrementCurvePointCount(context); break;
	}
}
