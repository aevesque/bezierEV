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

void	inputHandler(char keycode, void *v_context)
{
	Context	*context = v_context;

	switch(keycode) {
		case 27: context->should_quit = 1; break;
		case 'w': context->control_points[context->current_point].y -= MOVE_INCREMENT; break;
		case 'a': context->control_points[context->current_point].x -= MOVE_INCREMENT; break;
		case 's': context->control_points[context->current_point].y += MOVE_INCREMENT; break;
		case 'd': context->control_points[context->current_point].x += MOVE_INCREMENT; break;
		case 'q': selectNextPoint(context); break;
		case 'Q': selectPrevPoint(context); break;
		case '+': createPoint(context); break;
		case '-': deleteLastPoint(context); break;
		case 'i': context->step += STEP_INCREMENT; break;
		case 'k': context->step = (context->step - STEP_INCREMENT < MIN_STEP ? MIN_STEP : context->step - STEP_INCREMENT); break;
	}
}
