#include "../include/cBezierVisualizer.h"

Context	defaultContext(void)
{
	return ((Context) {
		.control_points = calloc(2, sizeof(fVec3)),
		.control_point_count = 2,
		.curve_resolution = STARTING_CURVE_RESOLUTION,
		.curve_point_count = 1 / STARTING_CURVE_RESOLUTION,
		.move_resolution = STARTING_MOVE_RESOLUTION,
	});
}

static void	toDelim(char *buffer, size_t *cursor, char delim)
{
	do
		*cursor = *cursor + 1;
	while (buffer[*cursor] != delim);
}

int	buildContextFromFile(const char *filename, char *program_name, Context *context)
{
	int	fd = open(filename, O_RDONLY);

	if (fd <= 0)
		return (printf("%s: Error: could not open file %s.\n", program_name, filename), 1);

	memset(context, 0, sizeof(*context));
	char buffer[1024];
	read(fd, buffer, sizeof(buffer) - 1);

	size_t	i = 0;
	int	scale[2];

	toDelim(buffer, &i, '\n');
	toDelim(buffer, &i, '\n');
	
	context->control_point_count = atoi(&buffer[i]);
	toDelim(buffer, &i, '\n');

	context->curve_point_count = atoi(&buffer[i]);
	toDelim(buffer, &i, '\n');

	toDelim(buffer, &i, '\n');
	toDelim(buffer, &i, '\n');

	for (int j = 0; j < 2; ++j)
	{
		toDelim(buffer, &i, '-');
		scale[j] = atoi(&buffer[i + 1]);
		toDelim(buffer, &i, '\n');
	}

	toDelim(buffer, &i, '\n');
	toDelim(buffer, &i, '\n');
	context->control_points = malloc(context->control_point_count * sizeof(fVec3));
	for (int j = 0; j < context->control_point_count; ++j)
	{
		context->control_points[j].x = atof(&buffer[i]) / scale[0];
		toDelim(buffer, &i, ',');
		context->control_points[j].y = atof(&buffer[i + 1]) / scale[1] * -1.0f;
		toDelim(buffer, &i, '\n');
	}
	close(fd);

	context->move_resolution = STARTING_MOVE_RESOLUTION;
	context->curve_resolution = 1.0f / context->curve_point_count;
	return (0);
}
