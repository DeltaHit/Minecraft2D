#include "Game.h"

// ############################################################################
//          INIT
// ############################################################################

// Constructeur
Game::Game()
{
    // initWindow() n'est pas dans init pour pouvoir faire un reset
    // avec init() sans reconstruire la fenetre
    initWindow();
    init();
}

// Initialiseur de la classe
void Game::init()
{
    srand(time(NULL));

    initWorldMap();

    initSprites();
    initShapes();


    initPlayer();
    initShield();
    initFoes();
    initBoss();
    _bullets.clear();

    initTexts();
    initMusic();
    initSounds();

    _currentView == FOLLOW_Y;
    _frameRun = 0;
    _frameTotal = 0;
}

// Initialize la window
void Game::initWindow()
{
    // Window
    _window.create(VideoMode(DEF_WINDOW_WIDTH, DEF_WINDOW_HEIGHT),
        WINDOW_TITLE, Style::Default, _settings);
    _settings.antialiasingLevel = ANTI_ALIASING_LEVEL;

    _window.setFramerateLimit(FRAMERATE);
    handleResizeWindow();

    // View
    _window.setView(_view[FOLLOW]);

    // Icon
    //_window.setIcon(image.GetWidth(), image.GetHeight(), image.GetPixelsPtr());
}

// Initialize les sprites
void Game::initSprites()
{
    // Load files
    if (!_tileset.loadFromFile("img\\tiles.bmp"))
        quitApplication();
    if (!_batTexture.loadFromFile("img\\bat.bmp"))
        quitApplication();
    if (!_batImage.loadFromFile("img\\bat.bmp"))
        quitApplication();
    if (!_playerTexture.loadFromFile("img\\waddle_doo.bmp"))
        quitApplication();
    if (!_playerImage.loadFromFile("img\\waddle_doo.bmp"))
        quitApplication();

    // Player
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 8; j++) // initialiser toutes les sprites
        {
            _playerSprites[i][j] = initOneSprite(i, j, _playerTexture);
            _playerImage.createMaskFromColor(Color(255, 255, 255));
            _playerTexture.update(_playerImage);
            _playerSprites[i][j].setTextureRect(IntRect(i * 30, j * 30, 30, 30));
            _playerSprites[i][j].setTexture(_playerTexture);
            _playerSprites[i][j].setOrigin(Vector2f(15, 30));
        }
    }

    // Bat
    _batImage.createMaskFromColor(Color(255, 255, 255));
    _batTexture.update(_batImage);
    _batSprite.setTextureRect(IntRect(64, 0, TILE_SIZE, TILE_SIZE));
    _batSprite.setTexture(_batTexture);
    _batSprite.setOrigin(Vector2f(TILE_SIZE / 2, TILE_SIZE / 2));

    // Map
    for (size_t version = 0; version < 8; version++)
    {
        _tileSprite[EMPTY_BLOCK][version] = initOneSprite(0 + version, 0, _tileset);
        _tileSprite[SOFT_BLOCK][version] = initOneSprite(7 + version, 5, _tileset);
        _tileSprite[HARD_BLOCK][version] = initOneSprite(8 + version, 8, _tileset);
        _tileSprite[VISITED][version] = initOneSprite(13 + version, 2, _tileset);
        _tileSprite[INVALID_BLOCK][version] = initOneSprite(5 + version, 4, _tileset);
    }
}

// Recupere un sprite a partir des parametres
Sprite Game::initOneSprite(unsigned int line, unsigned int col, Texture& texture,
    unsigned int tileSize, unsigned int separation)
{
    Sprite spr;
    int xMove = line * tileSize + (line * separation * 2);
    int yMove = col * tileSize + (col * separation * 2);
    spr.setTextureRect(IntRect(xMove, yMove, tileSize, tileSize));
    spr.setTexture(texture);
    return spr;
}

// Initialize les fonts
void Game::initTexts()
{
    // Font
    if (!_fontInvasion2000.loadFromFile("INVASION2000.TTF"))
        quitApplication();

    // Text Instructions
    _messageOnShader.setFont(_fontInvasion2000);
    _messageOnShader.setCharacterSize(36);                // In pixels
    _messageOnShader.setFillColor(Color(255, 255, 255));  // White
    _messageOnShader.setOutlineColor(Color(64, 64, 64));  // Dark grey
    _messageOnShader.setOutlineThickness(3);
    _messageOnShader.setPosition(32, 32);
    _messageOnShader.setString(STR_INSTRUCTIONS);

    // Text debugInfo
    _debugInfo.setFont(_fontInvasion2000);
    _debugInfo.setCharacterSize(24);                    // In pixels
    _debugInfo.setFillColor(Color(255, 255, 255, 128)); // White
    _debugInfo.setOutlineColor(Color(64, 64, 64, 128)); // Dark grey
    _debugInfo.setOutlineThickness(3);
    _debugInfo.setPosition(32, 32);
}

// Initialize les shapes
void Game::initShapes()
{
    //_playerShape.setFillColor(Color::Green);
    //_playerShape.setSize(Vector2f(3, 3));
    //_playerShape.setOrigin(2, 2);

    // Bullet
    _bulletShape.setRadius(2);
    _bulletShape.setOrigin(1, 1);
    _bulletShape.setFillColor(Color::White);
    _bulletShape.setOutlineColor(Color::Cyan);
    _bulletShape.setOutlineThickness(1);

    // Coord de la souris sans la view
    _mouseCoord.setFillColor(Color::Red);
    _mouseCoord.setRadius(2);
    _mouseCoord.setOrigin(2, 2);

    // Aiming Sight
    _aimingSight.setFillColor(Color::Transparent);
    _aimingSight.setOutlineColor(Color(0, 255, 255, 64));
    _aimingSight.setOutlineThickness(1);
    _aimingSight.setRadius(TILE_SIZE / 2);
    _aimingSight.setOrigin(TILE_SIZE / 2, TILE_SIZE / 2);

    // Mouse Square
    int tk = 3; // thickness
    _mouseSquare.setOrigin(-tk, -tk);
    _mouseSquare.setSize(Vector2f(TILE_SIZE - tk * 2, TILE_SIZE - tk * 2));
    _mouseSquare.setFillColor(Color(0, 0, 0, 0));
    _mouseSquare.setOutlineColor(Color::Black);
    _mouseSquare.setOutlineThickness(tk);
    // Boss Health Bar
    _bossHealthBar.setFillColor(Color::Red);
    _bossHealthBar.setOutlineColor(Color(128, 0, 0));
    _bossHealthBar.setOutlineThickness(tk);

    // Shader pour l'ecran de pause
    _shader.setSize(Vector2f(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height));
    _shader.setFillColor(Color(0, 0, 0, 128)); // Noir transparent
}

// Initialize la carte de terrain
void Game::initWorldMap()
{
    _map.randomize();

    initViews();
}

void Game::initMusic()
{
    if (MUSIQUE)
    {
        _music.openFromFile("music\\zelda.wav");
        _music.play();
    }
}

void Game::initSounds()
{
    if (MUSIQUE)
    {
        _buffBullet.loadFromFile("music\\pew.wav");
        _soundBullet.setBuffer(_buffBullet);

        _buffFoes.loadFromFile("music\\flap.wav");
        _soundFlap.setBuffer(_buffFoes);
    }
}
void Game::initViews()
{
    // DO NOT CHANGE _currentView HERE
    //_currentView = CAMERA; == BAD

    // Zoom
    float maxDim = MAX(_map.nbCol(), _map.nbLine());
    _view[NULL_VIEW] = handleResizeWindow();
    _view[NEUTRAL] = handleResizeWindow();
    _view[NEUTRAL].zoom(maxDim / TILE_SIZE * 1.5);
    _view[CAMERA] = handleResizeWindow();
    _view[CAMERA].zoom(maxDim / TILE_SIZE * 1.5);

    // Center
    _view[NEUTRAL].setCenter(
        _map.nbCol() * TILE_SIZE / 2,
        _map.nbLine() * TILE_SIZE / 2);
    _view[CAMERA].setCenter(
        _map.nbCol() * TILE_SIZE / 2,
        _map.nbLine() * TILE_SIZE / 2);
    _view[FOLLOW_Y].zoom(0.8);

    // Setup
    _currentView = FOLLOW_Y;
    _view[FOLLOW_Y] = handleResizeWindow();
}

void Game::initPlayer()
{
    _player.setHpMax(3);
    _player.setHp(3);

    _player.setPositionInGrid(15, 4);
    _player.setSpeed(4);
    _map.at(_player.getGridLine(), _player.getGridCol());
}

void Game::initShield()
{
    for (size_t i = 0; i < NB_SHIELD; i++)
    {
        _shieldVA[i].init(25, 0, 1);
        _shieldVA[i].rotate(i * SHIELD_ANGLE);
    }
}

void Game::initBoss()
{
    _boss.setPositionInGrid(_map.nbCol() / 2, 2);
    _boss.setSpeed(5);
    _boss.setHpMax(100);
    _boss.setHp(100);
}

// Initialise Foes
void Game::initFoes()
{
    _bats.clear();
    for (int i = 0; i < NB_STARTING_BATS; i++)
    {
        _bats.push_back(Crawler());
    }

    int position_x = 4;

    for (list<Crawler>::iterator it = _bats.begin(); it != _bats.end(); it++)
    {
        it->setPositionInGrid(position_x, 1);
        position_x += 6;
    }
}