#include <SFML/Graphics.hpp>
#include <cstdlib>

#define DEAD 0
#define LIVE 1

#define CELL_SIZE 12

#define WIDTH 110
#define HEIGHT 58

#define SCREEN_WIDTH (CELL_SIZE*WIDTH)+4
#define SCREEN_HEIGHT (CELL_SIZE*HEIGHT)+4

/**
	Initialize state, temp array and cells grid
*/
void init(bool state[][HEIGHT], bool temp[][HEIGHT], sf::RectangleShape cells[][HEIGHT]);

/**
	Count the number of neighbor cells for a given cell
*/
int count_neighbour(bool state[][HEIGHT], int x, int y);

/**
	Clear the grid and the state
*/
void clear_grid(bool state[][HEIGHT], bool temp[][HEIGHT], sf::RectangleShape cells[][HEIGHT]);

/**
	Runs the game with all the rules
*/
void run(bool state[][HEIGHT], bool temp[][HEIGHT], sf::RectangleShape cells[][HEIGHT]);

/**
	Draw all the cell grid in the given window
*/
void draw_grid(sf::RenderWindow* window, sf::RectangleShape cells[][HEIGHT]);


int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Game Of Life", sf::Style::Titlebar | sf::Style::Close);
	sf::Event event;
	sf::Vector2i mouse_cursor;
	bool state[WIDTH][HEIGHT] ;
	bool temp[WIDTH][HEIGHT];
	bool running = false;
	int cellX, cellY;
	sf::RectangleShape cells[WIDTH][HEIGHT];

	window.setFramerateLimit(60);

	init(state, temp, cells);

	while(window.isOpen())
	{
		while(window.pollEvent(event))
		{
			mouse_cursor = sf::Mouse::getPosition(window);
			cellX = mouse_cursor.x/CELL_SIZE;
			cellY = mouse_cursor.y/CELL_SIZE;

			if(event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();

			/*
				Prevents segmentation error in Release mode
			*/
			if(cellX == WIDTH)
				cellX--;
			if(cellY == HEIGHT)
				cellY--;

			if((mouse_cursor.x <= SCREEN_WIDTH && mouse_cursor.y <= SCREEN_HEIGHT) && (mouse_cursor.x > 0 && mouse_cursor.y > 0))
			{
				if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					cells[cellX][cellY].setFillColor(sf::Color::Black);
					state[cellX][cellY] = LIVE;
				}


				if(sf::Mouse::isButtonPressed((sf::Mouse::Right)))
				{
					cells[cellX][cellY].setFillColor(sf::Color::White);
					state[cellX][cellY] = DEAD;
				}
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::C))
				clear_grid(state, temp, cells);

			if(sf::Keyboard::isKeyPressed((sf::Keyboard::Space)))
				running = true;

			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
			{
				clear_grid(state, temp, cells);
				running = false;
			}

		}

		if(running)
			run(state, temp, cells);

		window.clear();
		draw_grid(&window, cells);
		window.display();
	}

    return EXIT_SUCCESS;
}

void init(bool state[][HEIGHT], bool temp[][HEIGHT], sf::RectangleShape cells[][HEIGHT])
{
	for(int x = 0; x < WIDTH; x++)
	{
		for(int y = 0; y < HEIGHT; y++)
		{
			state[x][y] = DEAD;
			temp[x][y] = DEAD;
			cells[x][y] = sf::RectangleShape(sf::Vector2f(CELL_SIZE, CELL_SIZE));
			cells[x][y].setFillColor(sf::Color::White);
			cells[x][y].setOutlineColor(sf::Color::Red);
			cells[x][y].setOutlineThickness(2.f);
			cells[x][y].setPosition(x*CELL_SIZE + 2, y*CELL_SIZE + 2);
		}
	}
}

int count_neighbour(bool state[][HEIGHT], int x, int y)
{
	int number_neighbour = 0;
	int left;
	int right = (x+1)%WIDTH;
	int up;
	int down = (y+1)%HEIGHT;

	/*
		Check for negative value with modulo, to make an infinite grid
	*/
	if(x-1<0)
		left = WIDTH - (abs(x-1) % WIDTH);
	else
		left = (x-1)%WIDTH;
	if(y-1<0)
		up = HEIGHT - (abs(y-1) % HEIGHT);
	else
		up = (y-1)%HEIGHT;

	/*
		Checking of all neighbor cells
	*/
	//Diagonal up-left
	if(state[left][up] == LIVE)
		number_neighbour++;

	//up
	if(state[x][up] == LIVE)
		number_neighbour++;

	//Diagonal up-right
	if(state[right][up] == LIVE)
		number_neighbour++;

	//left
	if(state[left][y] == LIVE)
		number_neighbour++;

	//right
	if(state[right][y] == LIVE)
		number_neighbour++;

	//Diagonal down-left
	if(state[left][down] == LIVE)
		number_neighbour++;

	//down
	if(state[x][down] == LIVE)
		number_neighbour++;

	//Diagonal down-right
	if(state[right][down] == LIVE)
		number_neighbour++;

	return number_neighbour;
}

void clear_grid(bool state[][HEIGHT], bool temp[][HEIGHT], sf::RectangleShape cells[][HEIGHT])
{
	for(int x = 0; x < WIDTH; x++)
	{
		for(int y = 0; y < HEIGHT; y++)
		{
			state[x][y] = DEAD;
			temp[x][y] = DEAD;
			cells[x][y].setFillColor(sf::Color::White);
		}
	}
}

void run(bool state[][HEIGHT], bool temp[][HEIGHT], sf::RectangleShape cells[][HEIGHT])
{
	for(int x = 0; x < WIDTH; x++)
	{
		for(int y = 0; y < HEIGHT; y++)
		{
			int number_neighboor = count_neighbour(state, x, y);

			//Death because not enough living cells around
			if(state[x][y] == LIVE && number_neighboor < 2)
				temp[x][y] = DEAD;

			//Stay alive
			if(state[x][y] == LIVE && (number_neighboor == 2 || number_neighboor == 3))
				temp[x][y] = LIVE;

			//Death because too much cells around
			if(state[x][y] == LIVE && number_neighboor > 3)
				temp[x][y] = DEAD;

			//Birth
			if(state[x][y] == DEAD && number_neighboor == 3)
				temp[x][y] = LIVE;
		}
	}

	/*
		Fills the color of the cells grid depending on the state array
	*/
	for(int x = 0; x < WIDTH; x++)
	{
		for(int y = 0; y < HEIGHT; y++)
		{
			state[x][y] = temp[x][y];
			if(state[x][y] == LIVE)
				cells[x][y].setFillColor(sf::Color::Black);
			else
				cells[x][y].setFillColor(sf::Color::White);
		}
	}
}

void draw_grid(sf::RenderWindow* window, sf::RectangleShape cells[][HEIGHT])
{
	for(int x = 0; x < WIDTH; x++)
	{
		for(int y = 0; y < HEIGHT; y++)
		{
			window->draw(cells[x][y]);
		}
	}
}
