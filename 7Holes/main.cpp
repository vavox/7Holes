#include <iostream>
#include <fstream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>


using namespace std;
using namespace sf;

void menu(RenderWindow & window);
void game(RenderWindow & window);
void win(int k, RenderWindow & window);
void infow(RenderWindow & window);

class ball 
{ // клас кульки
public:
	float x, y, w, h; //координати  х и у, висота ширина
	String File; //файл з розширенням
	Image image;//сфмл зображення
	Texture texture;//сфмл текстура
	Sprite sprite;//сфмл спрайт
	


	ball(String F, float X, float Y, float W, float H) {  //Конструктор з параметрами(формальными) для класса ball.
		File = F;//имя файла+расширение
		w = W; h = H;//высота и ширина
		image.loadFromFile("images/" + File);//передаємо/записуємо в image File( буде передаватись файл зображення)
		texture.loadFromImage(image);//записуємо зображення в текмтуру
		sprite.setTexture(texture);//заливаємо спрайт текстурою
		x = X; y = Y;//координата появи спрайту
	}
};

class hole
{//клас лунки, далі все описується аналогічно класу кульки
public:
	float x, y, w, h;
	String file;
	Image img;
	Texture texture;
	Sprite sprite;

	hole(String F, float X, float Y, float W, float H)
	{
		file = F;
		w = W; h = H;
		img.loadFromFile("images/" + file);
		texture.loadFromImage(img);
		sprite.setTexture(texture);
		x = X; y = Y;
	}
};


int main()
{
	sf::RenderWindow windowm(sf::VideoMode(1366, 768), "7Holes", Style::Default);//рендер(створення) вікна сфмл з розширенням 1366x768
	menu(windowm);//виклик меню
	return 0;
}

void menu(RenderWindow & window)//функція меню
{
	Texture menuTexture1, menuTexture2, menuTexture3, menuBackground, titleTexture, playTexture, infoTexture;//
	menuTexture1.loadFromFile("images/play.png");
	menuTexture2.loadFromFile("images/exit.png");
	menuBackground.loadFromFile("images/background.jpg");
	titleTexture.loadFromFile("images/holes.png");
	playTexture.loadFromFile("images/playm.png");
	infoTexture.loadFromFile("images/info.png");
	Sprite menu1(menuTexture1), menu2(menuTexture2), menuBg(menuBackground), title(titleTexture), play(playTexture), info(infoTexture);
	int f = 1, menuNum = 0;
	menu1.setPosition(610, 450);
	menu2.setPosition(600, 600);
	menuBg.setPosition(0, 0);
	title.setPosition(450, 50);
	play.setPosition(10, 10);
	info.setPosition(633, 525);
	sf::Music music;//створення об'єкта музики
	music.openFromFile("menu.ogg");//завантаження файлу
	music.stop();//зупинка музики
	music.play();//відтворення
	//////////////////////////////МЕНЮ////////////////////////////////
	while (window.isOpen())//цикл віктритого вікна
	{
		menu1.setColor(Color::White);//заливка кольору в текстуру 
		menu2.setColor(Color::White);
		info.setColor(Color::White);
		play.setColor(Color::White);
		menuNum = 0;
		window.clear();//ощищення вікна
		sf::Event event;
		while (window.pollEvent(event))
		{
			if ((event.type == sf::Event::Closed) || (Keyboard::isKeyPressed(Keyboard::Escape)))
			{
				window.close();
			}
		}
		if (IntRect(610, 450, 300, 50).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Green); menuNum = 1; }
		if (IntRect(600, 600, 300, 50).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Green); menuNum = 2; }
		if (IntRect(620, 525, 300, 50).contains(Mouse::getPosition(window))) { info.setColor(Color::Green); menuNum = 3; }
		if (IntRect(10, 10, 75, 75).contains(Mouse::getPosition(window)))
		{ 
			play.setColor(Color::Green);
			f = -1 * f; 
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				Sleep(50);
				if (f == -1) { music.stop(); }
				else { music.play(); }
			}
		}

	

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) { Sleep(50); music.stop(); window.close(); sf::RenderWindow windowg(sf::VideoMode(1366, 768), "7Holes", Style::Default); game(windowg); };//если нажали первую кнопку, то выходим из меню 
			if (menuNum == 2) { window.close(); }
			if (menuNum == 3) { Sleep(50); music.stop(); window.close(); sf::RenderWindow windowi(sf::VideoMode(1366, 768), "7Holes", Style::Default); infow(windowi); }
		}
		music.setLoop(true);//зациклення музики
		window.draw(menuBg);//вивід спарйтів на екран 
		window.draw(menu1);
		window.draw(menu2);
		window.draw(title);
		window.draw(play);
		window.draw(info);
		window.display();
	}
	////
}

void game(RenderWindow & window)//функія з реалізацією геймплея та графіки самої гри
{
	const int N = 7;
	float oX[N];
	float oXc[N];
	float oY = 320;
	int k = 0;
	int f = 0;
	int fl[N];
	int l = 0;
	int tn, lk;
	for (int i = 0; i < N; i++)
	{
		oX[i] = 192 + 160*i;
		oXc[i] = 142 + 160*i;
		fl[3] = 0;
		if (i < 3)
		{
			fl[i] = 1;
		}
		if (i > 3)
		{
			fl[i] = 2;
		}
	}

	Font font;//шрифт 
	font.loadFromFile("Arial.ttf");//передаємо шрифту файл шрифта
	Text text("", font, 20);//створюємо об'єкт тексту.записуємо в об'єкт строку, шрифт, розмір шрифта(в пікселях);
	text.setFillColor(Color::Green);//заливка об'єкта кольором(зеленим)
	text.setPosition(1150, 50);
	text.setCharacterSize(50);
	text.setString("Step: ");
	Text text1("", font, 20);
	text1.setFillColor(Color::Green);
	text1.setPosition(1300, 50);
	text1.setCharacterSize(50);
	
	Texture playTexture;
	playTexture.loadFromFile("images/playm.png");
	Sprite play(playTexture);
	int fm = 1;
	play.setPosition(10, 10);

	Texture gamebackground;
	gamebackground.loadFromFile("images/gamebg.jpg");
	Sprite gamebg(gamebackground);
	ball p("Ballw.png", 250, 250, 96.0, 96.0);
	ball p1("Ballb.png", 768, 366, 96.0, 96.0);
	hole h("hole.png", 250, 250, 96.0, 96.0);
	hole hg("hole.png", 250, 250, 96.0, 96.0);
	hole hl("hole.png", 250, 250, 96.0, 96.0);

	sf::Music music;
	music.openFromFile("music.ogg");
	music.play();

	float tr;
	gamebg.setPosition(0, 0);
	while (window.isOpen())
	{
		play.setColor(Color::White);
		music.setLoop(true);
		sf::Event event;
		while (window.pollEvent(event))
		{
			if ((event.type == sf::Event::Closed) || (Keyboard::isKeyPressed(Keyboard::Escape)))
			{
				music.stop();
				window.close();
				RenderWindow windowm(sf::VideoMode(1366, 768), "7Holes", Style::Default);
				menu(windowm);
			}

		}

		if (IntRect(10, 10, 75, 75).contains(Mouse::getPosition(window)))
		{
			play.setColor(Color::Green);
			fm = -1 * fm;
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				Sleep(50);
				if (fm == -1) { music.stop(); }
				else { music.play(); }
			}
		}

		window.clear();
		window.draw(gamebg);

		h.sprite.setColor(Color::Red);
		for (int i = 0; i < N; i++)
		{
			h.sprite.setPosition(oXc[i], oY - 50);
			window.draw(h.sprite);
			if (fl[i] == 1)
			{

				p.sprite.setPosition(oX[i], oY);
				window.draw(p.sprite);
			}
			if (fl[i] == 2)
			{

				p1.sprite.setPosition(oX[i], oY);
				window.draw(p1.sprite);
			}

		}
		if (f == 1)
		{
			Sleep(1000);
			music.stop();
			window.close();
			RenderWindow windowg(sf::VideoMode(1366, 768), "7Holes", Style::Default);
			win(k, windowg);
		}
		Sleep(90);
		if (l < 7) { if (Keyboard::isKeyPressed(Keyboard::Right)) { l++; } }
		if (l >= 7) { l = 6; }
		if (l > 0) { if (Keyboard::isKeyPressed(Keyboard::Left)) { l--; } }
		if (l <= 0) { l = 0; }
		hg.sprite.setColor(Color::Green);
		hg.sprite.setPosition(oX[l] - 50, oY - 50);
		window.draw(hg.sprite);
		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			hl.sprite.setColor(Color::Yellow);
			hl.sprite.setPosition(oXc[l], oY - 50);
			window.draw(hl.sprite);
			tn = l;
			lk = fl[l];
		}
		if (Keyboard::isKeyPressed(Keyboard::Tab))
		{
			hl.sprite.setColor(Color::Yellow);
			hl.sprite.setPosition(oXc[l], oY - 50);
			window.draw(hl.sprite);
			if ((fl[l] == 0)&& ((l == tn + 1) || (l == tn + 2) || (l == tn - 1) || (l == tn - 2)))
			{
					fl[tn] = 0;
					fl[l] = lk;
					k++;
			}
		}
		auto s = std::to_string(k);
		text1.setString(s);
		if ((fl[0] == 2)&&(fl[1] == 2)&&(fl[2] == 2)&&(fl[3] == 0))
			{
				f = 1;
			}
			else
			{
				f = 0;
			}
		
		window.draw(text);
		window.draw(text1);
		window.draw(play);
		window.display();
	}
}

void win(int k, RenderWindow & window)//функція вікна з повідомленням про перемогу
{
	sf::Music music;
	music.openFromFile("musicw.ogg");
	music.play();
	Texture gamebackground;
	gamebackground.loadFromFile("images/gamebg.jpg");
	Sprite gamebg(gamebackground);
	gamebg.setPosition(0, 0);
	Texture win;
	win.loadFromFile("images/youwon1.png");
	Sprite won(win);
	won.setPosition(496, 36);
	Font font;
	font.loadFromFile("Arial.ttf");
	Text text("", font, 20);
	text.setFillColor(Color::Green);
	text.setPosition(500, 290);
	text.setCharacterSize(50);
	text.setString("Amount of steps: ");
	Text text1("", font, 20);
	text1.setFillColor(Color::Green);
	text1.setPosition(900, 290);
	text1.setCharacterSize(50);
	auto s = std::to_string(k);
	text1.setString(s);
	Texture menuTexture1, menuTexture2;
	menuTexture1.loadFromFile("images/playa.png");
	menuTexture2.loadFromFile("images/exitm.png");
	Sprite menu1(menuTexture1), menu2(menuTexture2);

	Texture playTexture;
	playTexture.loadFromFile("images/playm.png");
	Sprite play(playTexture);
	int fm = 1;
	play.setPosition(10, 10);

	int menuNum = 0;
	menu1.setPosition(526, 450);
	menu2.setPosition(396, 550);
	while (window.isOpen())
	{
		play.setColor(Color::White);
		sf::Event event;
		while (window.pollEvent(event))
		{
			if ((event.type == sf::Event::Closed) || (Keyboard::isKeyPressed(Keyboard::Escape)))
			{
				window.close();
			}

		}
		menu1.setColor(Color::White);
		menu2.setColor(Color::White);
		menuNum = 0;
		if (IntRect(526, 450, 300, 100).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Green); menuNum = 1; }
		if (IntRect(396, 550, 650, 100).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Green); menuNum = 2; }
		if (IntRect(10, 10, 75, 75).contains(Mouse::getPosition(window)))
		{
			play.setColor(Color::Green);
			fm = -1 * fm;
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				Sleep(50);
				if (fm == -1) { music.stop(); }
				else { music.play(); }
			}
		}
		

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) { music.stop(); window.close(); sf::RenderWindow windowg(sf::VideoMode(1366, 768), "7Holes", Style::Default); game(windowg); };//если нажали первую кнопку, то выходим из меню 
			if (menuNum == 2) { Sleep(200); music.stop();  window.close(); sf::RenderWindow windowm(sf::VideoMode(1366, 768), "7Holes", Style::Default); menu(windowm); }

		}
		window.clear();
		window.draw(gamebg);
		window.draw(won);
		window.draw(text);
		window.draw(text1);
		window.draw(menu1);
		window.draw(menu2);
		window.draw(play);
		window.display();
	}
}

void infow(RenderWindow & window)//функція вікна з інформацією
{
	Font font;
	font.loadFromFile("Arial.ttf");
	Text faq("", font, 20);
	faq.setFillColor(Color::Green);
	faq.setPosition(50, 50);
	faq.setCharacterSize(40);
	faq.setString("How to play:\nChoose a hole by pressing KeyLeft or KeyRight\nPress Space to pick a ball.\nPress Tab to put a ball.");
	Text faq1("", font, 20);
	faq1.setFillColor(Color::Green);
	faq1.setPosition(50, 350);
	faq1.setCharacterSize(40);
	faq1.setString("Rules:\nYou can pick any ball.\nBut you can put the ball in the nearby empty hole\nor in empty hole that situated by the directly nearby ball\n\n\nPress Escape to back to main menu");
	Texture menuBackground;
	menuBackground.loadFromFile("images/background.jpg");
	Sprite bg(menuBackground);
	bg.setPosition(0, 0);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if ((event.type == sf::Event::Closed) || (Keyboard::isKeyPressed(Keyboard::Escape)))
			{
				Sleep(100);
				window.close();
				RenderWindow windowm(sf::VideoMode(1366, 768), "7Holes", Style::Default);
				menu(windowm);
			}

		}
			window.clear();
			window.draw(bg);
			window.draw(faq);
			window.draw(faq1);
			window.display();
		}
	
}