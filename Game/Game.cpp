#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
}

bool Game::init(void)
{
	window.create(VideoMode(800, 800), "ZOMBIEEE!! AAGAHRG!!1!!!!!1!", Style::Fullscreen);
	view.setSize(window.getSize().x, window.getSize().y);
	window.setView(view);
	window.setVerticalSyncEnabled(true);
	window.setMouseCursorVisible(false);
	//window.setFramerateLimit(10);
	srand(time(NULL));
	cursor.init(&window, &view, &player);
	cursor.setLimit({ 2000, 2000 });
	return true;
}

void Game::run(void)
{
	TextureManager texManager;
	texManager.add("player", "bumbum.png"); //64x64
	texManager.add("grass", "grass.png"); //32x32
	texManager.add("bullet", "bullet.png"); //15x15
	texManager.add("zombie", "zombies.png"); //64x64

	Sprite grass;
	grass.setTextureRect(IntRect(0, 0, 2000, 2000));
	texManager.get("grass")->setRepeated(true);
	grass.setTexture(*texManager.get("grass"));

	Font f;
	f.loadFromFile("BAUHS93.TTF");

	Text life;
	life.setFont(f);
	life.setColor(Color::Red);
	life.setPosition(view.getCenter() - view.getSize() / 2.f + Vector2f(10, 10));
	life.setCharacterSize(30);

	vector<FloatingText> vt;

	FloatingText t;

	t.init("DEAD", 1000, 0.05);
	t.setFont(f);
	t.setSize(20);
	t.setColor(Color::Red);

	player.setMaxSpeed(0.8);
	player.init({ 1000, 1000 }, Animator(100, { 0, 0 }, { 64, 64 }, texManager.get("player"), { 4, 1 }));
	player.setCoolDown(500);
	player.setFull(30);

	int points = 0;
	bool lvlUp = false;
	int lvl = 1;

	life.setString("HP: " + player.getHp());

	Character zombie, boomer, dog, vomit;

	zombie.init({ 0, 0 }, Animator(130, { 0, 3 * 64 }, { 64, 64 }, texManager.get("zombie"), { 4,1 }));
	zombie.setDmg(5);
	zombie.setMaxSpeed(0.057);
	zombie.setFull(15);
	zombie.setCoolDown(600);

	boomer.init({ 0, 0 }, Animator(130, { 0, 0 * 64 }, { 64, 64 }, texManager.get("zombie"), { 4,1 }));
	boomer.setDmg(10);
	boomer.setMaxSpeed(0.04);
	boomer.setFull(20);
	boomer.setCoolDown(1200);

	dog.init({ 0, 0 }, Animator(130, { 0, 1 * 64 }, { 64, 64 }, texManager.get("zombie"), { 4,1 }));
	dog.setDmg(5);
	dog.setMaxSpeed(0.1);
	dog.setFull(8);
	dog.setCoolDown(300);

	vomit.init({ 0, 0 }, Animator(130, { 0, 2 * 64 }, { 64, 64 }, texManager.get("zombie"), { 4,1 }));
	vomit.setDmg(15);
	vomit.setMaxSpeed(0.07);
	vomit.setFull(10);
	vomit.setCoolDown(700);

	vector<Character> vz;
	Projectile p;
	p.init({ 0, 0 }, 0, 0, 0, texManager.get("bullet"));

	vector<Projectile> vp;

	Counter nextSpawn(100);

	Clock clock;
	Time elapsed;

	int edge;
	int x, y, kind;

	while (window.isOpen())
	{
		elapsed = clock.restart();

		nextSpawn.add(elapsed.asMilliseconds());

		if (nextSpawn.isFull())
		{
			nextSpawn.loop();
			if (vz.size() < lvl * lvl + 5)
			{
				kind = rand() % 4;
				edge = rand() % 4;
				switch (edge)
				{
				case 0:
					x = view.getCenter().x - view.getSize().x;
					y = rand() % 500 - 1000 + view.getCenter().y;
					break;
				case 1:
					x = rand() % 750 - 1500 + view.getCenter().x;
					y = view.getCenter().y - view.getSize().y;
					break;
				case 2:
					x = view.getCenter().x + view.getSize().x;
					y = rand() % 500 - 1000 + view.getCenter().y;
					break;
				case 3:
					x = rand() % 750 - 1500 + view.getCenter().x;
					y = view.getCenter().y + view.getSize().y;
					break;
				default:
					break;
				}

				switch (kind)
				{
				case 0: //boomer
					boomer.setPos({ (float)x, (float)y });
					boomer.randomAnimation();
					vz.push_back(boomer);
					break;
				case 1: //dog
					dog.setPos({ (float)x, (float)y });
					dog.randomAnimation();
					vz.push_back(dog);
					break;
				case 2: //vomit
					vomit.setPos({ (float)x, (float)y });
					vomit.randomAnimation();
					vz.push_back(vomit);
					break;
				case 3: //zombie
					boomer.setPos({ (float)x, (float)y });
					zombie.randomAnimation();
					vz.push_back(zombie);
					break;
				default:
					break;
				}
				zombie.setPos({ (float)x, (float)y });
				zombie.randomAnimation();
				vz.push_back(zombie);
			}
		}


		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed)
			{
				if (Keyboard::isKeyPressed(Keyboard::Escape))
					window.close();
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::W))
			player.addForce(0, -PLAYER_SPEED);
		if (Keyboard::isKeyPressed(Keyboard::A))
			player.addForce(-PLAYER_SPEED, 0);
		if (Keyboard::isKeyPressed(Keyboard::S))
			player.addForce(0, PLAYER_SPEED);
		if (Keyboard::isKeyPressed(Keyboard::D))
			player.addForce(PLAYER_SPEED, 0);
		if (Keyboard::isKeyPressed(Keyboard::LShift))
			player.speedMod(player.getMaxSpeed() * 2.0);

		if (player.getPos().x + player.getSize().x > LVL_X_LIMIT)
		{
			player.setPos({ LVL_X_LIMIT - player.getSize().x - 1, player.getPos().y });
		}
		else if (player.getPos().x - player.getSize().x / 2.f < 0)
		{
			player.setPos({ player.getSize().x / 2.f + 1, player.getPos().y });
		}

		if (player.getPos().y + player.getSize().y > LVL_Y_LIMIT)
		{
			player.setPos({ player.getPos().x, LVL_Y_LIMIT - player.getSize().y - 1 });
		}
		else if (player.getPos().y - player.getSize().y / 2.f < 0)
		{
			player.setPos({ player.getPos().x,  player.getSize().y / 2.f + 1 });
		}

		for (Projectile& p : vp)
		{
			p.update(elapsed);
		}

		player.look(cursor.getCursor().getPosition(), elapsed);
		player.update(elapsed);

		for (Projectile& p : vp)
		{
			for (Character& z : vz)
			{
				if (p.intersects(&z))
				{
					//z.damage(5);
					p.destroy();
					if (z.isDead())
					{
						t.init("DEAD", z.getPos());
						vt.push_back(t);
					}
					else
					{
						t.init("HIT", z.getPos());
						vt.push_back(t);
					}
				}
			}
		}

		vz.erase(remove_if(vz.begin(), vz.end(), [&points, &lvlUp](Character& p) {
			if (p.isDead())
			{
				points++;
				if (points % 5 == 0)
				{
					lvlUp = true;
				}
			} return p.isDead();
		}), vz.end());

		if (lvlUp)
		{
			player.setCoolDown(player.getCoolDown() - player.getCoolDown() * 0.035);
			lvl++;
			t.init("LEVEL UP", player.getPos());
			vt.push_back(t);
			lvlUp = false;
		}

		for (int k = 0; k < vz.size(); k++)
		{
			vz[k].look(player.getPos());
			vz[k].moveFwd();
			vz[k].update(elapsed);
		}

		for (Character& z : vz)
		{
			if (z.intersects(&player) && z.useDmg())
			{
				if (!GOD_MODE)
					player.damage(z.getDmg());
				t.init("OUCH", player.getPos());
				vt.push_back(t);
			}
		}

		life.setString("HP: " + to_string(player.getHp()) + "\nKILLS: " + to_string(points) + "\nLEVEL: " + to_string(lvl) + "\nTOTAL ZOMBIES: " + to_string(vz.size()) +
			"\nFPS: " + to_string((int)(1.f / elapsed.asSeconds())));


		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (player.useDmg())
			{
				p.init(player.getPos(), player.getAngle() - 90, 1.2, 2000);
				vp.push_back(p);
			}
		}

		vp.erase(remove_if(vp.begin(), vp.end(), [](Projectile& p) {return p.isDestroyed(); }), vp.end());

		cursor.update();
		cursor.setColor(Color::Red);

		life.setPosition(view.getCenter() - view.getSize() / 2.f);

		//player.look((Vector2f)Mouse::getPosition(window) + view.getCenter() - view.getSize() / 2.f);

		for (FloatingText& f : vt)
		{
			f.update(elapsed);
		}

		vt.erase(remove_if(vt.begin(), vt.end(), [](FloatingText& f) {return f.isDestroyed(); }), vt.end());

		window.draw(grass);

		for (Projectile& p : vp)
			p.draw(window);

		player.draw(window);

		for (Character& z : vz)
			z.draw(window);

		for (FloatingText& f : vt)
			window.draw(f);

		window.draw(cursor.getCursor());
		window.draw(life);

		if (player.isDead())
		{
			RectangleShape c;
			c.setFillColor(Color::Black);
			c.setSize({ 2000, 2000 });
			c.setPosition({ 0, 0 });
			window.draw(c);
			life.setString("YOU ARE DEAD!");
			life.setColor(Color::Red);
			life.setCharacterSize(60);
			sf::FloatRect textRect = life.getLocalBounds();
			life.setOrigin(textRect.left + textRect.width / 2.0f,
				textRect.top + textRect.height / 2.0f);
			life.setPosition(view.getCenter());
			window.draw(life);
		}

		window.display();
		window.clear();
	}
}