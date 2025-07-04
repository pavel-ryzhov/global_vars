#include <stdio.h>
#include <string.h>

struct Point {
	int num;
	Point *root_point;
	float root_distance;
	float passed_distance;
	bool ifpassed;
};

void Initialize_point_list(Point *point_list, int points_count)
{
	for (int i=0; i < points_count; i++)
	{
		point_list[i].ifpassed = false;
		point_list[i].num = i;
		point_list[i].passed_distance = 0;
		point_list[i].root_distance = 0;
		point_list[i].root_point = NULL;
	}
	return;
}

void Clear_ifpassed_and_passed_distance(Point *point_list, int points_count)
{
	for (int i=0; i < points_count; i++)
	{
		point_list[i].ifpassed = false;
		point_list[i].passed_distance = 0;
	}
	return;
}

int Read_file_and_Make_tree(char *filename, Point **point_list, int *points_count, int **task, int *tasks_count)
{
	FILE *input_file;
	
	input_file = fopen(filename, "r");
	if (input_file == NULL)
	{
		perror("Opening input file error!");
		getchar();
		return -1;
	}

	fscanf(input_file, "%d", points_count);
	if (*points_count <= 0)
	{
		printf("Wrong points quantity!");
		getchar();
		return -1;
	}

	*point_list = new Point[*points_count];
	Initialize_point_list(*point_list, *points_count);

	int point1;
	int point2;
	float distance;
	for (int i=0; i < *(points_count)-1; i++)
	{
		fscanf(input_file, "%d" "%d" "%f", &point1, &point2, &distance);
		if ((point1 < 1) || (point1 > *points_count) || (point2 < 1) || (point2 > *points_count))
		{
			printf("Wrong point number!");
			getchar();
			return -1;
		}
		point1--;
		point2--;
		if ((*point_list)[point2].root_point != NULL)
		{
			(*point_list)[point1].root_point = *point_list + point2;
			(*point_list)[point1].root_distance = distance;
		}
		else
		{
			(*point_list)[point2].root_point = *point_list + point1;
			(*point_list)[point2].root_distance = distance;
		}
	}
	
	fscanf(input_file, "%d", tasks_count);
	if (*tasks_count < 0)
	{
		printf("Wrong tasks quantity!");
		getchar();
		return -1;
	}

	*task = new int[(*tasks_count)*2];
	for (int i=0; i < *tasks_count*2; i=i+2)
	{
		fscanf(input_file, "%d" "%d", &point1, &point2);
		if ((point1 < 1) || (point1 > *points_count) || (point2 < 1) || (point2 > *points_count))
		{
			printf("Wrong point number!");
			getchar();
			return -1;
		}
		point1--;
		point2--;
		(*task)[i] = point1;
		(*task)[i+1] = point2;
	}
	fclose(input_file);

	return 0;
}

float Find_shortest_distance(Point *point_list, int points_count, int point1, int point2)
{
	Point *prev_point = point_list + point1;
	Point *curr_point;
	(*prev_point).ifpassed = true;

	while ((*prev_point).root_point != NULL)
	{
		curr_point = (*prev_point).root_point;
		(*curr_point).ifpassed = true;
		(*curr_point).passed_distance = (*curr_point).passed_distance + (*prev_point).passed_distance + (*prev_point).root_distance;
		prev_point = curr_point;
	}

	prev_point = point_list + point2;
	if ((*prev_point).ifpassed) return (*prev_point).passed_distance;

	while (!((*prev_point).ifpassed))
	{
		curr_point = (*prev_point).root_point;
		(*curr_point).passed_distance = (*curr_point).passed_distance + (*prev_point).passed_distance + (*prev_point).root_distance;
		prev_point = curr_point;
	}

	return (*prev_point).passed_distance;
}

void Write_result(float *result, int tasks_count, char *output_filename)
{
	FILE *output_file = fopen(output_filename, "w");

	for (int i=0; i < tasks_count; i++)
	{
		fprintf(output_file, "%f\n", result[i]);
	}
	fclose(output_file);
	return;
}

int main(int argc, char *argv[])
{
	char *input_filename = argv[1];
	char *output_filename = argv[2];
	Point *point_list;
	int points_count;
	int *task;
	int tasks_count;
	float *result;

	int iferror;
	iferror = Read_file_and_Make_tree(input_filename, &point_list, &points_count, &task, &tasks_count);
	if (iferror == -1) return 0;
	result = new float[tasks_count];

	for (int i=0,k=0; i < tasks_count*2; i=i+2,k++)
	{
		result[k] = Find_shortest_distance(point_list, points_count, task[i], task[i+1]);
		Clear_ifpassed_and_passed_distance(point_list, points_count);
	}

	Write_result(result, tasks_count, output_filename);

	return 0;
}