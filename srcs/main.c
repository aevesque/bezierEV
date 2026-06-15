#include "../include/cBezierVisualizer.h"

void	renderFrame(Context *context, TermGL termGL)
{
	iVec3	control_points[context->control_point_count];

	for (int i = 0; i < context->control_point_count; ++i)
	{
		control_points[i] = toAbsoluteUnbound(context->control_points[i], DISPLAY(termGL));
		if (control_points[i].x >= 0 && control_points[i].x < (int)getDisplayWidth(termGL) && control_points[i].y >= 0 && control_points[i].y < (int)getDisplayHeight(termGL))
			setPixelZBuffered(control_points[i].x, control_points[i].y, ALWAYS_ON_TOP, (i == context->current_point ? SEL_POINT_COLOR : POINT_COLOR), DISPLAY(termGL));
	}

	for (float t = 0; t < 1; t += context->curve_resolution)
	{
		const fVec3	p = nBezier(control_points, context->control_point_count, t);
		if ((int)p.x >= 0 && p.x < getDisplayWidth(termGL) && (int)p.y >= 0 && p.y < getDisplayHeight(termGL))
			setPixelZBuffered(p.x, p.y, ZBUF_MAX, LINE_COLOR, DISPLAY(termGL));
	}

	displayGeneralInfo(context, termGL);
	displayPointInfo(context, termGL);
}

int main(int argc, char **argv)
{
	Parsed parsed;

	if (parse(argc, argv, &parsed))
		return (1);

	Context context;
	if (parsed.input_file)
	{
		if (buildContextFromFile(parsed.input_file, argv[0], &context))
			return (1);
	}
	else
		context = defaultContext();

	TermGL	termGL = termGLInit(100, 100);
	setFramerate(10, termGL);
	registerInputHandler(inputHandler, &context, termGL);

	while (!context.should_quit)
	{
		renderFrame(&context, termGL);
		renderDisplay(termGL);
	}

	generateOutput(&parsed, &context);

	free(context.control_points);
	termGLDestroy(termGL);
	return (0);
}
