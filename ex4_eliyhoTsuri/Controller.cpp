#include "Controller.h"
#include "I_Shape.h"
#include "J_Shape.h"
#include "L_Shape.h"
#include "O_Shape.h"
#include "S_Shape.h"
#include "T_Shape.h"
#include "Z_Shape.h"

Controller::Controller()
{
	set_game();
	set_shapes();
}
void Controller::set_game()
{
	Texture *back = Singleton::show().get_pic(1);
	m_back.setTexture(*back);
	m_music.openFromFile("sound/tetris_back.ogg");
	m_music_line.openFromFile("sound/line.ogg");
	m_music.setVolume(20);
	m_music_line.setVolume(100);
	vector<Point> a(4);
	vector<Point> b(4);
	vector<vector<int>> mat(M, vector<int>(N));
	m_a = a;
	m_b = b;
	m_mat = mat;
}
void Controller::set_shapes()
{
	m_speeds.push_back(0.9);
	m_speeds.push_back(0.8);
	m_speeds.push_back(0.7);
	m_speeds.push_back(0.6);
	m_speeds.push_back(0.5);
	m_speeds.push_back(0.4);
	m_speeds.push_back(0.3);
	m_speeds.push_back(0.2);
	m_speeds.push_back(0.1);
	m_speeds.push_back(0.001);
	m_shapes.push_back(make_shared <I_Shape>());
	m_shapes.push_back(make_shared <J_Shape>());
	m_shapes.push_back(make_shared <L_Shape>());
	m_shapes.push_back(make_shared <O_Shape>());
	m_shapes.push_back(make_shared <S_Shape>());
	m_shapes.push_back(make_shared <T_Shape>());
	m_shapes.push_back(make_shared <Z_Shape>());
}
void Controller::run()
{
	srand(unsigned(time(NULL)));
	RenderWindow window(VideoMode::getDesktopMode() / 2, "Tetris");
	window.setSize({ 1400, 800 });
	window.setPosition(sf::Vector2i(250, 80));
	Clock clock;
	m_music.play();
	while (window.isOpen())
	{
		Event event;
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;
		GameTime menu(m_level, m_points * m_level);
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
			{
				game_over(window);
				return;
			}
			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Space)
					system("pause");
				if (event.key.code == Keyboard::Up)
					m_rotate = true;
				else if (event.key.code == Keyboard::Left)
					m_dx = -1;
				if (event.type == Event::KeyPressed)
				{
					if (event.key.code == Keyboard::Up)
						m_rotate = true;
					else if (event.key.code == Keyboard::Left)
						m_dx = -1;
					else if (event.key.code == Keyboard::Right)
						m_dx = 1;
					else if (event.key.code == Keyboard::S)
						set_new_level(window);
				}
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Down))
			m_speed = 0.001;
		move();
		check_lines(window);
		draw(window, menu);
		if (m_points * m_level / m_level >= 10)
			set_new_level(window);
		window.display();
	}
}

void Controller::move()
{
	if (timer > m_speed)
	{
		m_b = m_a;
		vector<Dest> vdest;
		vdest.emplace_back(m_a, m_dx, false);
		m_a = vdest[0](0);
		if (!check_board())
			update_board();
		timer = 0;
	}
	m_b = m_a;
	vector<Dest> vdest;
	vdest.emplace_back(m_a, m_dx, true);
	m_a = vdest[0](0);
	if (!check_board())
		m_a = m_b;
	if (m_rotate)
		move_rotate();
}

void Controller::move_rotate()
{
	Point p = m_a[1];
	for (int i = 0; i < 4; i++)
	{
		int x = m_a[i].y - p.y;
		int y = m_a[i].x - p.x;
		m_a[i].x = p.x - x;
		m_a[i].y = p.y + y;
	}
	if (!check_board())
		m_a = m_b;
}

void Controller::check_tick(int timer, int delay)
{
	if (timer > delay)
	{
		m_b = m_a;
		vector<Dest> vdest;
		vdest.emplace_back(m_a, m_dx, false);
		m_a = vdest[0](0);
		if (!check_board())
			update_board();
		timer = 0;
	}
}

bool Controller::check_board()
{
	bool check = true;

	check = all_of(m_a.cbegin(), m_a.cend(), [](auto i)
	{
		if (i.x < 0 || i.x >= N || i.y >= M)
			return false;
	});
	for (int i = 0; i < 4; i++)
	{
		if (m_a[i].y == 20 || m_a[i].x == 10 || m_a[i].x < 0)
			continue;
		if (m_mat[m_a[i].y][m_a[i].x] > 0)
			return false;
	}
	return check;
}

void Controller::update_board()
{
	for (int i = 0; i < 4; i++)
		m_mat[m_b[i].y][m_b[i].x] = m_colorNum;

	vector<Dest> vdest;
	vdest.emplace_back(m_a, m_dx, true);
	m_a = vdest[0](0);

	m_colorNum = 1 + rand() % 7;
	int n = rand() % 7;
	int next = rand() % 7;

	for (int i = 0; i < 4; i++)
	{
		m_a[i].x = figures[n][i] % 2;
		m_a[i].y = figures[n][i] / 2;
	}
}

void Controller::check_lines(RenderWindow &window)
{
	int k = M - 1;
	for (int i = M - 1; i > 0 && !m_end; i--)
	{
		int count = 0;
		for (int j = 0; j < N; j++)
		{
			if (m_mat[1][j] > 0)
			{
				m_end = true;
				break;
			}
			if (m_mat[i][j] > 0 || m_mat[i][j] > 0)
				count++;
			m_mat[k][j] = m_mat[i][j];

			if (count == 10)
			{
				m_points++;
				m_music_line.play();
			}
		}
		if (count < N)
			k--;
	}
	m_dx = 0;
	m_rotate = false;
	m_speed = m_speeds[m_level];
	if (m_end)
		game_over(window);
}

void Controller::draw(RenderWindow &window, GameTime &menu)
{
	window.clear(Color::White);
	window.draw(m_back);
	menu.draw(window);
	int index = rand() % 7;
	if (m_flag)
	{
		int num = rand() % 7;
		for (int i = 0; i < 4; i++)
		{
			m_a[i].x = figures[0][i] % 2;
			m_a[i].y = figures[0][i] / 2;
		}
		m_flag = false;
	}

	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (m_mat[i][j] == 0)
				continue;
			m_shapes[index]->draw(window, m_mat[i][j], i, j);
		}
	}

	for (int i = 0; i < 4; ++i)
		m_shapes[index]->move(window, m_a[i].x, m_a[i].y, m_colorNum);
}

void Controller::set_new_level(RenderWindow & window)
{
	Music level_end;
	Texture *back = Singleton::show().get_pic(5);
	back->setSmooth(true);
	Sprite next;
	Text score, num_score;
	Font font, n_font;
	level_end.openFromFile("sound/level_end.ogg");
	m_music.stop();
	next.setTexture(*back);
	window.clear();
	window.draw(next);
	level_end.play();
	n_font.loadFromFile("fonts/crackman.ttf");
	font.loadFromFile("fonts/FONT.ttf");
	score.setFont(font);
	num_score.setFont(n_font);
	num_score.setString(std::to_string(m_points * m_level));
	num_score.setCharacterSize(60);
	num_score.setPosition(635, 287);
	num_score.setFillColor(Color::Red);
	score.setString("Your Score: ");
	score.setCharacterSize(40);
	score.setFillColor(Color::Red);
	score.setPosition(260, 300);
	window.draw(score);
	window.draw(num_score);
	window.display();
	Sleep(3000);
	initialize_level();
	m_music.play();
}

void Controller::initialize_level()
{
	m_level++;
	m_points = 0;
	m_flag = true;
	vector<Point> a(4);
	vector<Point> b(4);
	vector<vector<int>> mat(M, vector<int>(N));
	m_a = a;
	m_b = b;
	m_mat = mat;
}

void Controller::game_over(RenderWindow & window)
{
	Music game_over;
	Sprite f_end;
	Sprite next;
	Text score, num_score;
	Font font, n_font;
	Texture *end = Singleton::show().get_pic(2);
	Texture *back = Singleton::show().get_pic(5);

	back->setSmooth(true);
	next.setTexture(*back);
	window.clear();
	window.draw(next);
	n_font.loadFromFile("fonts/crackman.ttf");
	font.loadFromFile("fonts/FONT.ttf");
	score.setFont(font);
	num_score.setFont(n_font);
	num_score.setString(std::to_string(m_points * m_level));
	num_score.setCharacterSize(60);
	num_score.setPosition(625, 408);
	num_score.setFillColor(Color::Red);
	score.setString("Your Score: ");
	score.setCharacterSize(40);
	score.setFillColor(Color::Red);
	score.setPosition(240, 420);
	f_end.setTexture(*end);
	game_over.openFromFile("sound/end.ogg");
	m_music.stop();
	window.draw(f_end);
	window.draw(score);
	window.draw(num_score);
	window.display();
	game_over.play();
	Sleep(3000);
	window.close();
}

sf::VideoMode operator/(const sf::VideoMode& mode, unsigned denom)
{
	return { mode.width / denom, mode.height / denom, mode.bitsPerPixel };
}
