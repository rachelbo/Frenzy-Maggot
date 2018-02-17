#pragma once
#ifdef _DEBUG
#pragma comment(lib, "sfml-main-d.lib")
#pragma comment(lib, "sfml-system-d.lib")
#pragma comment(lib, "sfml-window-d.lib")
#pragma comment(lib, "sfml-graphics-d.lib")
#pragma comment(lib, "sfml-audio-d.lib")
#elif defined(NDEBUG)
#pragma comment(lib, "sfml-main.lib")
#pragma comment(lib, "sfml-system.lib")
#pragma comment(lib, "sfml-window.lib")
#pragma comment(lib, "sfml-graphics.lib")
#pragma comment(lib, "sfml-audio.lib")

#else
#error "Unrecognized configuration!"
#endif
//----------------------------------includes-----------------------------------
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>
#include <memory>
#include <map>
#include <list>
#include <unordered_map>
//----------------------------------consts--------------------------------------
#define M_PI      3.141592653589
#define LINK_SIZE 80
const int TEXTURE_SIZE = 55, BOARD_SIZE = 3200;
//----------------------------------srtuct--------------------------------------
struct WormProfile
{
	unsigned boost = 0;
	unsigned laser = 0;
	unsigned wormSize = 5;
	sf::Texture wormProfileTexture;
	sf::Texture wormHeadTexture;
	sf::Texture wormBodyTexture;
};
//----------------------------------class--------------------------------------
class Singleton
{
public:
	static Singleton& instance();
	sf::Texture&	  getTexture(std::string texturName);
	std::shared_ptr<WormProfile>	  getWormProfile(unsigned profile);
	unsigned		  getWormProfileSize() const { return m_wormProfile.size(); }
	sf::Font&		  getFont() { return m_font; }
	//void			  playMusic(std::string musicName);
	//void			  StopMusic(std::string musicName);

private:
	Singleton();
	void readWormProfile();
	void setWormProfile(std::string line);
	void setFont();

	std::unordered_map<std::string, sf::Music> m_music;
	std::map<std::string, sf::Texture> m_textures;
	std::vector<std::shared_ptr<WormProfile>> m_wormProfile;
	sf::Font m_font;
};