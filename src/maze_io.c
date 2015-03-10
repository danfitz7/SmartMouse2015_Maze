#include "maze_io.h"

Maze *read_from_file(FILE *f){
	//check for bad file
	if (!f) return NULL;

	Maze *maze = create_maze();

	int len = 2 * MAZE_SIZE + 3;
	char *line = malloc(len*sizeof(char));
	char *l = line;
	char *success;

	int i;
	for (i=0;i< MAZE_SIZE;i++){ //read in each line
		success = fgets(line, len + 1,f);
		l = line;

		if (success == NULL) return NULL;

		//printf("successfully read... %s",line);

		int j;
		for (j=0;j<MAZE_SIZE;j++){
			Node *n = get_node(maze,i,j);
			Node *n_west = get_node(maze,i,j-1);
			Node *n_south = get_node(maze,i+1,j);

			//make sure west node isn't null
			if (n_west){
				if (*l != '|'){
					n->neighbors[W] = n_west;
					n_west->neighbors[E] = n;
				}
			}

			l++;

			//make sure south node isn't null
			if (n_south){
				if (*l != '_'){
					n->neighbors[S] = n_south;
					n_south->neighbors[N] = n;
				}
			}

			l++;
		}
	}
	printf("\n");

	free(line);

	return maze;
}

void print_maze(Maze *maze){
	int i,j;
	for (i=0;i<MAZE_SIZE;i++){
		char *str = calloc(sizeof(char),MAZE_SIZE + 2);
		char *s=str;
		for (j=0;j<MAZE_SIZE;j++){
			if (!get_node(maze,i,j)->neighbors[W]){
				strcpy(s++,"|");
				if (!get_node(maze,i,j)->neighbors[S]){
					strcpy(s++,"_");
				}
				else {
					strcpy(s++," ");
				}
			}
			else {
				strcpy(s++,"_");
				if (!get_node(maze,i,j)->neighbors[S]){
					strcpy(s++,"_");
				}
				else {
					strcpy(s++," ");
				}
			}
		}
		*(s++) = '|';
		*s = '\0';
		printf("%s\n",str);
	}
}

void print_weight_maze(Maze *maze){
	int i,j;
	for (i=0;i<MAZE_SIZE;i++){
		for (j=0;j<MAZE_SIZE;j++){
			int w = get_node(maze,i,j)->weight;
			if (w<10){
				printf(" %d ",w);
			}
			else {
				printf("%d ",w);
			}
		}
		printf("\n");
	}
}

void print_pointer_maze(Maze *maze){
	int i,j;
	for (i=0;i<MAZE_SIZE;i++){
		for (j=0;j<MAZE_SIZE;j++){
			printf("%p ", get_node(maze,i,j));
		}
		printf("\n");
	}
}
