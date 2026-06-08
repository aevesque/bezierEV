#include "../include/cBezierVisualizer.h"

void	displayPointInfo(Context *context, TermGL termGL)
{
	fVec3	*current_point = &context->control_points[context->current_point];
	char point_info[40];

	sprintf(point_info, "Current point : %01d (%.4f, %.4f). Resolution : %.4f", context->current_point, context->control_points[context->current_point].x, context->control_points[context->current_point].y, context->move_resolution);
	putText(point_info, 0, getDisplayHeight(termGL) - 1, BLACK, WHITE, DISPLAY(termGL));
}

