#include "SFML/Graphics.hpp"
#include "pilka.h"
#include <vector>
#include <string>
#include <fstream>

void ekranHelp(sf::RenderWindow& window) {
	sf::Font font;
	if (!font.loadFromFile("arial.ttf")) {
		return;
	}

	sf::Text helpText;
	helpText.setFont(font);
	helpText.setString("Arkanoid Game Help\n\n- Move paddle: A (left), D (right)\n- Break all bloki to win\n- Avoid letting the ball fall below the paddle\n\nPress F1 to return to the game.");
	helpText.setCharacterSize(20);
	helpText.setFillColor(sf::Color::White);
	helpText.setPosition(50, 50);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F1)
				return;
		}

		window.clear(sf::Color::Black);
		window.draw(helpText);
		window.display();
	}
}
void koniecGry(sf::RenderWindow& window, bool& win)
{
	sf::Font font;
	if (!font.loadFromFile("arial.ttf")) {
		return;
	}

	sf::Text tekst;
	tekst.setFont(font);
	if (win)
		tekst.setString("Koniec gry. Wygrales zdobywajac punktow");
	else
		tekst.setString("Koniec gry. Przegrales, bo nie udalo ci sie zlapac pilki.\n Nacisnij escape aby skonczyc gre");
	tekst.setCharacterSize(20);
	tekst.setFillColor(sf::Color::White);
	tekst.setPosition(50, 50);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				return;
		}

		window.clear(sf::Color::Black);
		window.draw(tekst);
		window.display();
	}
}
void czyWyjsc(sf::RenderWindow& window)
{
	sf::Font font;
	if (!font.loadFromFile("arial.ttf")) {
		return;
	}

	sf::Text tekst;
	tekst.setFont(font);
	tekst.setString("Czy na pewno chcesz wyjsc?\nJesli tak, kliknij ENTER\nZeby wrocic kliknij escape");
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Enter)
				{
					window.close();
					return;
				}
				else if (event.key.code == sf::Keyboard::Escape)
					return;
			}
		}
		window.clear(sf::Color::Black);
		window.draw(tekst);
		window.display();
	}
}
void dopliku(int poziom)
{
	std::fstream plik;
	plik.open("zapis.txt", std::ios::out);
	plik.clear();
	plik << poziom;
	plik.close();
}
void plansza_pomiedzy(sf::RenderWindow& window, int poziom)
{
	sf::Font font;
	if (!font.loadFromFile("arial.ttf")) {
		return;
	}
	std::string lvl = std::to_string(poziom);
	sf::Text tekst;
	tekst.setFont(font);
	tekst.setString("Gratulacje! przeszedles poziom numer ");
	tekst.setString(lvl);
	tekst.setString("\n Zeby przejsc dalej kliknij enter \n zeby zapisac gre (punktacje i numer poziomu) kliknij s");

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Enter)
				{
					return;
				}
				if (event.key.code == sf::Keyboard::S)
				{
					dopliku(poziom);
				}

			}
		}
		window.clear(sf::Color::Black);
		window.draw(tekst);
		window.display();
	}
}

void kolejnyPoziom(belka& paletka, pilka& pila, std::vector<blok>& bloki, int& poziom, sf::RenderWindow& window, bool fromstart) {

	if (!fromstart)
		plansza_pomiedzy(window, poziom);

	pila.reset(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

	// Dostosowanie trudności w zależności od poziomu
	if (poziom != 1) {
		pila.velocity = sf::Vector2f(6.f, -6.f); // Zwiększenie prędkości piłki
	}
	if (poziom == 3) {
		paletka.shape.setSize(sf::Vector2f(PADDLE_WIDTH / 2, PADDLE_HEIGHT)); // Zmniejszenie paletki
	}

	// Ponowne tworzenie bloków
	bloki.clear();
	for (int i = 0; i < ROWS; ++i) {
		for (int j = 0; j < COLS; ++j) {
			bloki.emplace_back(j * BLOCK_WIDTH + 1, i * BLOCK_HEIGHT + 1);
		}
	}
}
void zpliku(int& poziom)
{
	std::fstream plik;
	plik.open("zapis.txt", std::ios::in);
	if (!plik.is_open())
	{
		poziom = 1;
		return;
	}
	else
	{
		std::string lvl;
		plik >> lvl;
		poziom = std::stoi(lvl);
		if (poziom < 1)
			poziom = 1;
		else if (poziom > 3)
			poziom = 3;
	}
}
int main() {
	bool win = false; //czy wygrana
	bool fromstart = false; //czy wczytalismy poziom z pliku
	int poziom = 1;	//ktory mamy poziom

	std::fstream plik;

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Arkanoid Gra"); //inicjalizacja okna gry
	window.setFramerateLimit(60); //limit fps

	belka paletka(WINDOW_WIDTH / 2 - PADDLE_WIDTH / 2, WINDOW_HEIGHT - 50); //stworzenie belki do rtuszania
	pilka pila(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 4.f, -4.f); //to samo z pilka
	std::vector<blok> bloki;

	// inicjalizaaacja blokow
	for (int i = 0; i < ROWS; ++i)
	{
		for (int j = 0; j < COLS; ++j)
		{
			bloki.emplace_back(j * BLOCK_WIDTH + 1, i * BLOCK_HEIGHT + 1);
		}
	}

	// yświetlenie okna menu głównego
	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
	{
		return -1;
	}

	sf::Text menuText;
	menuText.setFont(font);
	menuText.setString("Welcome to Arkanoid!\n\nPress Enter to Start\nPress F1 for Help\n Press l to load last saved game");
	menuText.setCharacterSize(30);
	menuText.setFillColor(sf::Color::White);
	menuText.setPosition(100, 200);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Enter)
					goto start;
				if (event.key.code == sf::Keyboard::F1)
					ekranHelp(window);
				if (event.key.code == sf::Keyboard::L)
				{
					zpliku(poziom);
					fromstart = true;
					goto poziomwczyt;
				}
			}
		}

		window.clear(sf::Color::Black);
		window.draw(menuText);
		window.display();
	}

start:
	// petla glowna gry
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F1)
			{
				ekranHelp(window);
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				czyWyjsc(window);
		}

		// ruch paletki
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			paletka.move(-8.f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			paletka.move(8.f);
		}

		// ruch pilki
		pila.move();

		//sprawdzanie czy pilka jest w ramach okna czy moze juz poleciala
		if (pila.shape.getPosition().x <= 0 || pila.shape.getPosition().x + 2 * BALL_RADIUS >= WINDOW_WIDTH)
		{
			pila.bounceHorizontal();
		}
		if (pila.shape.getPosition().y <= 0)
		{
			pila.bounceVertical();
		}
		if (pila.shape.getPosition().y + 2 * BALL_RADIUS >= WINDOW_HEIGHT)
		{
			koniecGry(window, win);
			break;
		}

		if (pila.shape.getGlobalBounds().intersects(paletka.shape.getGlobalBounds())) // pilka vs paletka
		{
			pila.bounceVertical();
		}


		for (auto& block : bloki) //pilka vs klocki
		{
			if (!block.destroyed && pila.shape.getGlobalBounds().intersects(block.shape.getGlobalBounds())) {
				block.destroyed = true;
				pila.bounceVertical();
				break;
			}
		}
		if (bloki.empty()) //sprawdzanie pustosci wektora z klockami
		{
			if (poziom < 3)
			{
				poziom++;
			poziomwczyt:
				kolejnyPoziom(paletka, pila, bloki, poziom, window, fromstart);
				fromstart = false;
			}
			else {
				win = true;
				koniecGry(window, win); // koniec gry po 3 poziomie
				return 0;
			}
		}


		// usuwanie zniszczonych bloków
		bloki.erase(std::remove_if(bloki.begin(), bloki.end(), [](const blok& block)
			{
				return block.destroyed;
			}), bloki.end());

		// rnderowanie calosci
		window.clear(sf::Color::Black);
		window.draw(paletka.shape);
		window.draw(pila.shape);
		for (const auto& block : bloki)
		{
			window.draw(block.shape);
		}
		window.display();
	}

	return 0;
}
