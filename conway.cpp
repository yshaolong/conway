/* REQUIREMENTS
Any live cell with fewer than two live neighbours dies, as if by underpopulation.
Any live cell with two or three live neighbours lives on to the next generation.
Any live cell with more than three live neighbours dies, as if by overpopulation.
Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.*/

#include <iostream>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <chrono>
#include <thread>
#include <assert.h>


/* PLAN
- create a grid[50][50] for the simulation to fit on the console
- ask the user to input an x and y value to place initial cells and repeat until user inputs start
- ask the user to input "start" to begin the simulation
- infinite while loop
	- clear previous lines that appear in the console
	(for loop to increment x and y values for the check)
	for all cells:
	-if
	-if there are 3 LIVE neighbours next to a DEAD cell
		-DEAD cell becomes aLIVE
	-if there are more than 3 LIVE neighbours next to a LIVE cell
		-LIVE cell DIES xx
	-if there are 2 or 3 LIVE neighbours next to a LIVE cell
		-LIVE cell stays ALIVE xx
	-if there are less than 2 LIVE neighbours next to a LIVE cell
		-LIVE cell DIES xx
	-if user hits enter break loop
*/
enum CellState { CellState_Dead, CellState_Alive };


int number_of_alive_neighbours(
	CellState location_one, CellState location_two, CellState location_three, CellState location_four,
	CellState location_five, CellState location_six, CellState location_seven, CellState location_eight
) {
	int neighbour_alive_counter = 0;
	if (location_one == CellState_Alive) {
		neighbour_alive_counter += 1;
	}
	if (location_two == CellState_Alive) {
		neighbour_alive_counter += 1;
	}
	if (location_three == CellState_Alive) {
		neighbour_alive_counter += 1;
	}
	if (location_four == CellState_Alive) {
		neighbour_alive_counter += 1;
	}
	if (location_five == CellState_Alive) {
		neighbour_alive_counter += 1;
	}
	if (location_six == CellState_Alive) {
		neighbour_alive_counter += 1;
	}
	if (location_seven == CellState_Alive) {
		neighbour_alive_counter += 1;
	}
	if (location_eight == CellState_Alive) {
		neighbour_alive_counter += 1;
	}
	return neighbour_alive_counter;
}

CellState location_state(CellState location_check, int neighbour_alive_counter) {
	//determining state of the location
	if ((location_check == CellState_Alive && neighbour_alive_counter < 2) || 
		(location_check == CellState_Alive && neighbour_alive_counter > 3)) {
		return CellState_Dead;
	}
	else if ((location_check == CellState_Alive && (neighbour_alive_counter >= 2 || neighbour_alive_counter <= 3))
		|| (location_check == CellState_Dead && neighbour_alive_counter == 3)) {
		return CellState_Alive;
	}
	else {
		return CellState_Dead;
	}
}

char enum_to_char(CellState location_check) {
	if (location_check == CellState_Alive) {
		return ' ';
	}
	else {
		return '@';
	}
}
int main()
{
	assert(CellState_Dead == location_state(CellState_Alive, 1));
	assert(CellState_Dead == location_state(CellState_Alive, 4));
	
	assert(CellState_Alive == location_state(CellState_Dead, 3));
	assert(CellState_Alive == location_state(CellState_Alive, 3));

	assert(CellState_Dead == location_state(CellState_Dead, 5));
	assert(CellState_Dead == location_state(CellState_Alive, 6));

	printf("test\n");
	const int grid_length = 50;
	CellState grid[grid_length][grid_length] = {};
	int x_coord = 0;
	int y_coord = 0;
	bool user_input_start = false;
	//although start has 5 characters, list an extra for the terminal null - a null character to indicate to the terminal that the string has ended.
	char buffer[6];
	// constant = invariable/remains the same and thus using in buffer_compare whereas in buffer, inserting user input and thus remains as char.
	const char* buffer_compare = "start";

	CellState cellstate[grid_length][grid_length];
	//strcmp = comparing two strings that are listed in different areas of memory so entering the arrays and comparBing the values at each index with the other string.

	while (user_input_start == false) {

		printf("Please input an x coordinate between 0 and 49 for cell placement\n");
		scanf_s("%i", &x_coord);
		printf("Please input a y coordinate between 0 and 49 for cell placement\n");
		scanf_s("%i", &y_coord);
		grid[x_coord][y_coord] = CellState_Alive;

		if (x_coord != 0) {
			grid[x_coord - 1][y_coord] = CellState_Alive;
		}
		if (x_coord != grid_length - 1) {
			grid[x_coord + 1][y_coord] = CellState_Alive;
		}
		if (y_coord != 0) {
			grid[x_coord][y_coord - 1] = CellState_Alive;
		}
		if (y_coord != grid_length - 1) {
			grid[x_coord][y_coord + 1] = CellState_Alive;
		}

		printf("input 'start' to begin simulation, else enter anything else \n");
		scanf_s("%s", &buffer, 6);
		if (strcmp(buffer, buffer_compare) == 0) {
			break;
		}
	}

	while (true) {
		for (int i = 0; i < grid_length; i++) {
			for (int j = 0; j < grid_length; j++) {
				//printf("i %d j %d", i, j);
				int	alive_neighbour_counter = 0;
				CellState top_neighbour = CellState_Dead;
				CellState bottom_neighbour = CellState_Dead;
				CellState left_neighbour = CellState_Dead;
				CellState right_neighbour = CellState_Dead;

				CellState top_right_neighbour = CellState_Dead;
				CellState top_left_neighbour = CellState_Dead;
				CellState bottom_right_neighbour = CellState_Dead;
				CellState bottom_left_neighbour = CellState_Dead;

				if (i != 0) {
					top_neighbour = grid[i - 1][j];
					if (j != 0) {
						top_left_neighbour = grid[i - 1][j - 1];
					}
					if (j != grid_length - 1) {
						top_right_neighbour = grid[i - 1][j + 1];
					}
				}
				if (i != grid_length - 1) {
					bottom_neighbour = grid[i + 1][j];
				}
				if (j != 0) {
					left_neighbour = grid[i][j - 1];
					if (i != grid_length) {
						bottom_left_neighbour = grid[i + 1][j - 1];
					}
				}
				if (j != grid_length - 1) {
					right_neighbour = grid[i][j + 1];
					if (i != grid_length - 1) {
						bottom_right_neighbour = grid[i + 1][j + 1];
					}
				}
				alive_neighbour_counter = number_of_alive_neighbours(
					top_neighbour, bottom_neighbour, left_neighbour, right_neighbour,
					bottom_right_neighbour, bottom_left_neighbour, top_right_neighbour, top_left_neighbour);

				cellstate[i][j] = location_state(grid[i][j], alive_neighbour_counter);
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		for (int i = 0; i < grid_length; i++) {
			for (int j = 0; j < grid_length; j++) {

				char char_of_grid_location = enum_to_char(grid[i][j]);
				printf("%c", char_of_grid_location);
				grid[i][j] = cellstate[i][j];
			}
			printf("\n");
		}
		printf("\n");
	}

}