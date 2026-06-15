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

void	displayHelpPrompt(TermGL termGL)
{
	const char str[] = "Press h for help.";
	putText(str, getDisplayWidth(termGL) - (sizeof(str) - 1), getDisplayHeight(termGL) - 1, BLACK, WHITE, DISPLAY(termGL));
}

void	displayHelp(TermGL termGL)
{
	const char str[] =
		"wasd : move current point                     \n"
		"+/- : add/remove control point                \n"
		"q/Q : switch to next/previous control point   \n"
		"e/E : increase/decrease movement sensitivity  \n"
		"r/R : increase/decrease amount of curve points\n"
		"esc : save to file and quit                   \n"
		"h : close this window                         \n";

	putText(str, getDisplayWidth(termGL) * 0.2f, getDisplayHeight(termGL) * 0.2f, BLACK, WHITE, DISPLAY(termGL));
}
