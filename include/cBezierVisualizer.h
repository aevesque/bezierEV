#include "../termGL/include/termGL.h"

#ifndef C_BEZIER_VISUALIZER
# define C_BEZIER_VISUALIZER

# define STARTING_MOVE_RESOLUTION 0.01f
# define MIN_MOVE_RESOLUTION 0.0001f
# define MAX_MOVE_RESOLUTION 1.0f

# define STEP_INCREMENT 0.01f
# define STARTING_STEP	0.01f
# define MIN_STEP	0.001f

# define LINE_COLOR	GREEN
# define POINT_COLOR	WHITE
# define SEL_POINT_COLOR	RED

fVec3	nBezier(const iVec3 *control_points, const unsigned int control_point_count, const float t);

typedef struct {
	int	should_quit;
	int	current_point;
	fVec3	*control_points;
	int	control_point_count;
	float	step;
	float	move_resolution;
}	Context;

void	inputHandler(char keycode, void *v_context);
void	displayPointInfo(Context *context, TermGL termGL);
#endif
