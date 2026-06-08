#include "../include/cBezierVisualizer.h"

void	displayPointInfo(Context *context, TermGL termGL)
{
	fVec3	*current_point = &context->control_points[context->current_point];
	char point_info[50];

	sprintf(point_info, "Current point : %01d (%.4f, %.4f)", context->current_point, current_point->x, current_point->y * -1);
	putText(point_info, 0, getDisplayHeight(termGL) - 3, BLACK, WHITE, DISPLAY(termGL));
}

void	displayGeneralInfo(Context *context, TermGL termGL)
{
	char res_info[50];

	sprintf(res_info, "Resolution : %.4f. Curve Point count : %d", context->move_resolution, context->curve_point_count);
	putText(res_info, 0, getDisplayHeight(termGL) - 1, BLACK, WHITE, DISPLAY(termGL));
}
