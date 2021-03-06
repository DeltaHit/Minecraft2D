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

    drawShield();
    drawPlayer();
    drawFoes();
    drawBullets();
    drawMovableGui();

    drawThingsDirectlyOnTheScreen();

    _window.display();
}

// Met a jour les view
void Game::updateViews()
{
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

    _extraTitle += TOOL_NAMES[_currentTool];

    _extraTitle += "        Lives : " + to_string((int)_player.getHp()) + "/" + to_string((int)_player.getHpMax());
    _extraTitle += "        Game State : " + _appStateName[_appState];
    _extraTitle += "        Score : " + to_string(_score);

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

void Game::drawPlayer()
{
    _playerSprites[_animFrame][_animType].setPosition(_player.getExactX(), _player.getExactY());

    if (_player.isVulnerable(_frameRun))
    {
        _window.draw(_playerSprites[_animFrame][_animType]);
    }
    else
    {
        // Affiche le joueur en semi-transparent
        _playerSprites[_animFrame][_animType].setColor(Color(255, 255, 255, 128));
        _window.draw(_playerSprites[_animFrame][_animType]);
        _playerSprites[_animFrame][_animType].setColor(Color::White);
    }
}

void Game::drawShield()
{
    if (_currentTool == SPHERE_SHIELD)
    {
        for (size_t i = 0; i < _shield.size(); i++)
        {
            drawOneBullet(_shield[i]);
        }
    }
}

void Game::drawBullets()
{
    for (list<Bullet>::iterator b = _bullets.begin(); b != _bullets.end(); b++)
    {
        drawOneBullet(*b);
    }
}

void Game::drawOneBullet(Bullet& b)
{
    if (b.isFriendly())
    {
        int size = b.getHitBoxSize() / 10 + 1;
        _bulletShape[b.isFriendly()].setScale(
            Vector2f(size, size));
    }
    _bulletShape[b.isFriendly()].setPosition(b.getExactX(), b.getExactY());
    _window.draw(_bulletShape[b.isFriendly()]);
}

void Game::drawMovableGui()
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
        _aimingSight.setPosition(
            _mouseCoord.getPosition().x,
            _mouseCoord.getPosition().y);
        _window.draw(_aimingSight);
    }
}

void Game::drawFoes()
{
    int animationFrame = _frameFoes / 5 % 4;

    // Bats
    for (Crawler& c : _bats)
    {
        _batSprite[animationFrame][c.getDirection()].setPosition(
            c.getExactX(),
            c.getExactY());
        _window.draw(_batSprite[animationFrame][c.getDirection()]);
    }

    // Boss
    _batSprite[animationFrame][DOWN].setScale(Vector2f(2, 2));
    _batSprite[animationFrame][DOWN].setPosition(_boss.getExactX(), _boss.getExactY());
    _window.draw(_batSprite[animationFrame][DOWN]);
    _batSprite[animationFrame][DOWN].setScale(Vector2f(1, 1));
    
}

void Game::drawBossHealthBar()
{
    // Boss health bar
    if (_boss.isAlive())
    {
        float hpRatio = (float)_boss.getHp() / _boss.getHpMax();
        _bossHealthBar.setSize(Vector2f(
            (MAP_WIDTH_PIXELS - SHAPE_THICKNESS * 2) * hpRatio,
            HEALTH_BAR_HEIGHT));

        _window.draw(_bossHealthBar);
    }

    // Player health bar
    if (_player.isAlive())
    {
        float hpRatio = (float)_player.getHp() / _player.getHpMax();
        _playerHealthBar.setSize(Vector2f(
            (MAP_WIDTH_PIXELS - SHAPE_THICKNESS * 2) * hpRatio,
            HEALTH_BAR_HEIGHT));

        _window.draw(_playerHealthBar);
    }
}

// Affiche les objets qui ne sont pas affecter par la view
void Game::drawThingsDirectlyOnTheScreen()
{
    _window.setView(_view[NULL_VIEW]);

    drawBossHealthBar();

    // Affichage du shader
    if (_appState != RUNNING)
    {
        _window.draw(_shader);
        _window.draw(_messageOnShader);
    }


    _window.draw(_textToolSwitch);

    // Debug info
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
