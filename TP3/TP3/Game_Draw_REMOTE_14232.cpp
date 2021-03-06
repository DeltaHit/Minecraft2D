#include "Game.h"

// ############################################################################
//              DRAW
// ############################################################################

// Affiche les graphiques a l'ecran
void Game::drawWindow()
{
	_window.clear();

	updateWindowTitle();
	drawGrid();
	updateViews();
	drawMovableObjects();
	drawThingsDirectlyOnTheScreen();

	_window.display();
}

// Met a jour les view
void Game::updateViews()
{
	//if ((_view->getCenter().x) - (_view->getSize().x) <= _view->getSize().x / 2)
	//{
	//	_view[FOLLOW].setCenter(
	//		_view->getCenter().x,
	//		_player.getExactY());
	//}
	//if ((_view->getCenter().y * 2) - (_view->getSize().y) <= _view->getSize().y / 2)
	//{
	//	_view[FOLLOW].setCenter(
	//		_player.getExactX(),
	//		_view->getCenter().y);
	//}
 //   if ((_view->getCenter().y * 2) - (_view->getSize().y) > _view->getSize().y / 2
 //       && (_view->getCenter().x) - (_view->getSize().x) > _view->getSize().x / 2)
 //   {
	_view[FOLLOW].setCenter(
		_player.getExactX(),
		_player.getExactY());

	_view[FOLLOW_Y].setCenter(
		_map.nbCol() * TILE_SIZE / 2,
		_player.getExactY());
	////}
}

// Met a jour le titre de la fenetre
void Game::updateWindowTitle()
{
	// Ajoute de l'information dans le titre
	//_extraTitle += "Mouse: " +
	//    to_string((int)_mouseMagnet.getExactX()) + " " +
	//    to_string((int)_mouseMagnet.getExactY());
	//_extraTitle += "  Coord: " +
	//    to_string(_mouseMagnet.getGridCol()) + " " +
	//    to_string(_mouseMagnet.getGridLine());

	_extraTitle += toolName[_currentTool];

	if (_extraTitle != "")
		_extraTitle = " : " + _extraTitle;

	// Change le titre
	_window.setTitle(WINDOW_TITLE + _extraTitle);

	// Reinitialise pour la prochain iteration
	_extraTitle = "";
}

// Affiche la grille du labyrinthe
void Game::drawGrid()
{
	for (size_t l = 0; l < _map.nbLine(); l++)
	{
		for (size_t c = 0; c < _map.nbCol(); c++)
		{
			// Choix de la bonne tuile a afficher
			BLOCK_TYPE t = _map.at(l, c).getType();
			int v = _map.at(l, c).getVersion();
			_tileSprite[t][v].setPosition(c*TILE_SIZE, l*TILE_SIZE);
			_window.draw(_tileSprite[t][v]);
		}
	}
}

void Game::drawMovableObjects()
{
	// Mouse Square
	_mouseMagnet.setPositionExact(
		_mouseCoord.getPosition().x,
		_mouseCoord.getPosition().y);
	if (_currentTool == BUILD)
	{
		_mouseSquare.setPosition(
			_mouseMagnet.getGridCol() * TILE_SIZE,
			_mouseMagnet.getGridLine() * TILE_SIZE);
		_window.draw(_mouseSquare);
	}
	if (toolIsAShooter())
	{
		_mouseCursor.setPosition(
			_mouseCursor.getPosition().x,
			_mouseCursor.getPosition().y);
		_window.draw(_mouseCursor);
	}

	// Player
	_playerSprite.setPosition(
		_player.getExactX(),
		_player.getExactY());
	_window.draw(_playerSprite);

	for (Crawler& c : _bats)
	{
		_spiderSprite.setPosition(
			c.getExactX(),
			c.getExactY());
		_window.draw(_spiderSprite);
	}

	// Player
	_playerShape.setPosition(_player.getExactX(), _player.getExactY());
	_window.draw(_playerShape);

	// Bullet
	for (size_t i = 0; i < NB_SHIELD; i++)
	{
		_bulletShape.setPosition(_shieldSphere[i].getExactX(), _shieldSphere[i].getExactY());
		_window.draw(_bulletShape);
	}


	//Bullets
	_debug += "\r\nB: " + to_string(_bullets.size());

	for (list<Bullet>::iterator b = _bullets.begin(); b != _bullets.end(); b++)
	{
		_bulletShape.setPosition(b->getExactX(), b->getExactY());
		_window.draw(_bulletShape);
		//_debug += "\r\n" +
		//    to_string(b->getDirectionDegree()) + " " +
		//    to_string(b->getExactX()) + " " +
		//    to_string(b->getExactY()) + " " +
		//    to_string(b->getLength());
	}
}

// Affiche les objets qui ne sont pas affecter par la view
void Game::drawThingsDirectlyOnTheScreen()
{
	_window.setView(_view[NULL_VIEW]);

	// Ecran de pause
	if (_appState == PAUSED)
	{
		// Shader
		_window.draw(_shader);

		// Text Overlay
		_texteInstructions.setString(_message);
		_window.draw(_texteInstructions);
	}
	_debugInfo.setString(_debug);
	_window.draw(_debugInfo);
	_debug = "";

	_window.draw(_mouseCoord);

	_window.setView(_view[_currentView]);
}

// Miroir d'un sprite sur l'axe vertical
void Game::flipSpriteHorizontal(Sprite& s)
{
	s.setOrigin({ s.getLocalBounds().width, 0 });
	s.setScale({ -1, 1 });
}

// Affiche le contenu de map dans le _debug
void Game::printMap()
{
	_debug += "\r\n";
	for (size_t l = 0; l < 20; l++)
	{
		for (size_t c = 0; c < 20; c++)
		{
			_debug += _map.at(l, c).getType() + 48;
		}
		_debug += "\r\n";
	}
}