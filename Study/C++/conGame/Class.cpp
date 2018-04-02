#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include <Windows.h>
#include <conio.h>
#include <time.h>  // or simply <ctime>

#define SCREEN_SIZE		79

using namespace std;

class GameObject {
	string 	shape;
	int		pos;
	string  type;

public:
	GameObject(const char *shape, int pos, const char *type = "unknown") : shape(shape), pos(pos), type(type) {}
	virtual ~GameObject() {}

	void SetShape(const char *shape) { this->shape = shape; }

	void SetPos(int pos) { this->pos = pos; }
	int  GetPos() const { return this->pos; }

	void IncreasePos() { this->pos++; }
	void DecreasePos() { this->pos--; }

	bool IsType(const char *type) { return this->type == type; }

	virtual void ProcessInput(int major, int minor) {}

	virtual void Update() {}

	virtual void Draw(char *canvas) const
	{
		if (pos < 0 || pos >= SCREEN_SIZE) return;

		strncpy(canvas + pos, shape.c_str(), shape.size());
	}
};

class Player : public GameObject {

public:
	Player() : GameObject("^_^", rand() % SCREEN_SIZE, "player") {}

	// overriding
	void ProcessInput(int major, int minor)
	{
		if (major != 224) return;

		// major == 224
		if (minor == 75)DecreasePos();
		else if (minor == 77)  IncreasePos();
	}
};

class Enemy : public GameObject {
	int  hp;
	bool isAlive;

public:
	Enemy(int hp) : hp(hp), isAlive(true), GameObject("*_*", rand() % SCREEN_SIZE, "enemy") {}

	void OnAttacked()
	{
		if (hp > 0) --hp;
		if (hp <= 0) isAlive = false;
	}

	bool IsAlive() { return isAlive; }

	// overriding
	void ProcessInput(int major, int minor)
	{
		if (major != 224) return;

		// major == 224
		if (minor == 72) IncreasePos();
		else if (minor == 80) DecreasePos();
	}


	// overriding
	void Draw(char *canvas) const
	{
		if (isAlive == false) return;
		GameObject::Draw(canvas);
	}
};

class Bullet : public GameObject {
	bool 		isFired;
	Enemy* 		target;
	clock_t		firedTicks;

	void reset() { isFired = false; firedTicks = 0l; target = nullptr; }

public:
	Bullet() : isFired(false), GameObject(">", 0, "bullet"), target(nullptr), firedTicks(0l) {}

	void Fire(const Player& player, Enemy& enemy)
	{
		int player_pos = player.GetPos();
		int target_pos = enemy.GetPos();

		if (player_pos == target_pos) return;

		if (player_pos < target_pos) {
			SetShape(">");
		}
		else {
			SetShape("<");
		}

		SetPos(player_pos);
		target = &enemy;
		firedTicks = clock();
	}

	bool IsUsed() { return isFired || firedTicks != 0l; }

	//overriding
	void Update()
	{
		if (!target) return;

		if (isFired == false) {
			if (firedTicks == 0l) return;

			// 만일 다음 라인을 comment out한다면 5초후 발사 기능이 사라짐.
			// bseo. I will comment out the following line to shoot the bullet when a user hits a space bar.
			//if ( ((clock() - firedTicks) / CLOCKS_PER_SEC) < 5) return;

			isFired = true;
		}

		int pos = GetPos();
		int target_pos = target->GetPos();

		if (pos < 0 || pos >= SCREEN_SIZE)
		{
			reset();
			return;
		}

		if (pos == target_pos)
		{
			target->OnAttacked();
			reset();
			return;
		}

		if (pos < target_pos) {
			IncreasePos();
		}
		else {
			DecreasePos();
		}
	}

	// overriding
	void Draw(char *canvas) const
	{
		if (isFired == false || target == nullptr) return;

		GameObject::Draw(canvas);
	}
};

class GameObjectManager {
	GameObject**	gameObjects;
	char*			canvas;
	const int		screenSize;
	int				maxGameObjects;

	void clear_screen()
	{
		memset(canvas, ' ', screenSize);
		canvas[screenSize] = '\0';
	}

	void process_input()
	{
		if (_kbhit() == 0) return;
		int minor = 0;


		int major = _getch();
		if (major == 224) minor = _getch();

		GameObject* obj;
		for (int i = 0; i < maxGameObjects; i++)
		{
			obj = gameObjects[i];
			if (obj == nullptr) continue;

			obj->ProcessInput(major, minor);
		}

		if (major == ' ')
		{
			Player *player = nullptr;
			Enemy  *enemy = nullptr;
			Bullet *bullet = nullptr;

			for (int i = 0; i< maxGameObjects; i++) {
				if (gameObjects[i] && gameObjects[i]->IsType("player"))
				{
					player = static_cast<Player *>(gameObjects[i]);
					break;
				}
			}
			for (int i = 0; i < maxGameObjects; i++) {
				if (gameObjects[i] && gameObjects[i]->IsType("enemy"))
				{
					enemy = static_cast<Enemy *>(gameObjects[i]);
					break;
				}
			}

			if (player == nullptr || enemy == nullptr) return;
			for (int i = 0; i < maxGameObjects; i++)
			{
				if (gameObjects[i] == nullptr) {
					bullet = new Bullet;
					gameObjects[i] = bullet; // upcasting
				}
				else if (gameObjects[i]->IsType("bullet")) {
					bullet = static_cast<Bullet *>(gameObjects[i]);
					if (bullet->IsUsed()) continue;
				}
				else {
					continue;
				}
				bullet->Fire(*player, *enemy);
				break;
			}
		}
	}

	void draw()
	{
		for (int i = 0; i < maxGameObjects; i++)
		{
			if (gameObjects[i] == nullptr) continue;
			gameObjects[i]->Draw(canvas);
		}
	}

	void update()
	{
		for (int i = 0; i < maxGameObjects; i++)
		{
			if (gameObjects[i] == nullptr) continue;
			gameObjects[i]->Update();
			if (gameObjects[i]->IsType("enemy"))
			{
				Enemy *enemy = static_cast<Enemy *>(gameObjects[i]);
				if (!enemy->IsAlive()) 
				{
					delete gameObjects[i];
					gameObjects[i] = nullptr;
				}
			}
		}
	}

	void render()
	{
		canvas[screenSize] = '\0';
		cout << canvas << '\r';
		Sleep(33);
	}

public:
	GameObjectManager(int maxGameObjects, int screen_size): maxGameObjects(maxGameObjects), screenSize(screen_size),gameObjects(new GameObject*[maxGameObjects]),
		canvas(new char[screen_size + 1])
	{
		for (int i = 0; i < maxGameObjects; i++) gameObjects[i] = nullptr;

		gameObjects[0] = new Player; // upcasting
		gameObjects[1] = new Enemy(10); // upcasting

		clear_screen();
	}

	~GameObjectManager()
	{
		for (int i = 0; i < maxGameObjects; i++) {
			if (gameObjects[i] != nullptr)
				delete gameObjects[i]; // using "virtual" ~GameObject()
		}
		delete[] gameObjects;
	}

	void GameLoop()
	{
		while (true) {
			clear_screen();
			process_input();
			draw();
			update();
			render();
		}
	}
};


int main()
{
	GameObjectManager mgr(50, 79);

	mgr.GameLoop();

	return 0;
}