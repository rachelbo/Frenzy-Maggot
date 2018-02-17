//----------------------------------includes-----------------------------------
#include "Singleton.h"
#include <fstream>
#include <string>

//----------------------------------c-tor--------------------------------------
Singleton::Singleton()
{
	auto desktopMode = sf::VideoMode::getDesktopMode();
	if (!m_textures["ant_left"].loadFromFile("images/left.png"))
		exit(1);
	if (!m_textures["ant_right"].loadFromFile("images/right.png"))
		exit(1);
	if (!m_textures["ant_down"].loadFromFile("images/down.png"))
		exit(1);
	if (!m_textures["ant_up"].loadFromFile("images/up.png"))
		exit(1);
	if (!m_textures["rock"].loadFromFile("images/rock.png"))
		exit(1);
	if (!m_textures["bomb"].loadFromFile("images/bomb.png"))
		exit(1);
	if (!m_textures["gift"].loadFromFile("images/gift.png"))
		exit(1);
	if (!m_textures["explosion"].loadFromFile("images/explosion.png"))
		exit(1);
	if (!m_textures["menu"].loadFromFile("images/menu.png"))
		exit(1);
	if (!m_textures["help"].loadFromFile("images/help.png"))
		exit(1);
	if (!m_textures["play"].loadFromFile("images/play.jpg"))
		exit(1);
	if (!m_textures["end_level"].loadFromFile("images/endLevel.png"))
		exit(1);
	if (!m_textures["choose"].loadFromFile("images/choosePlayer.jpg"))
		exit(1);
	if (!m_textures["ground"].loadFromFile("images/ground.png"))
		exit(1);
	if (!m_textures["play_button"].loadFromFile("images/play button.png"))
		exit(1);
	if (!m_textures["help_button"].loadFromFile("images/help button.png"))
		exit(1);
	if (!m_textures["return_button"].loadFromFile("images/return button.png"))
		exit(1);
	if (!m_textures["exit_button"].loadFromFile("images/exit button.png"))
		exit(1);
	if (!m_textures["you_lost"].loadFromFile("images/youLost.png"))
		exit(1);
	if (!m_textures["you_won"].loadFromFile("images/youWon.png"))
		exit(1);
	if (!m_textures["Bella_profile"].loadFromFile("images/Bella profile.png"))
		exit(1);
	if (!m_textures["Bob_profile"].loadFromFile("images/Bob profile.png"))
		exit(1);
	if (!m_textures["Chicko_profile"].loadFromFile("images/Chicko profile.png"))
		exit(1);
	if (!m_textures["Dino_profile"].loadFromFile("images/Dino profile.png"))
		exit(1);
	if (!m_textures["Loony_profile"].loadFromFile("images/Loony profile.png"))
		exit(1);
	if (!m_textures["Nelly_profile"].loadFromFile("images/Nelly profile.png"))
		exit(1);
	if (!m_textures["Peep_profile"].loadFromFile("images/Peep profile.png"))
		exit(1);
	if (!m_textures["Shmoopy_profile"].loadFromFile("images/Shmoopy profile.png"))
		exit(1);
	if (!m_textures["Sunny_profile"].loadFromFile("images/Sunny profile.png"))
		exit(1);
	if (!m_textures["Bella head"].loadFromFile("images/Bella head.png"))
		exit(1);
	if (!m_textures["Bob head"].loadFromFile("images/Bob head.png"))
		exit(1);
	if (!m_textures["Chicko head"].loadFromFile("images/Chicko head.png"))
		exit(1);
	if (!m_textures["Dino head"].loadFromFile("images/Dino head.png"))
		exit(1);
	if (!m_textures["Loony head"].loadFromFile("images/Loony head.png"))
		exit(1);
	if (!m_textures["Nelly head"].loadFromFile("images/Nelly head.png"))
		exit(1);
	if (!m_textures["Peep head"].loadFromFile("images/Peep head.png"))
		exit(1);
	if (!m_textures["Shmoopy head"].loadFromFile("images/Shmoopy head.png"))
		exit(1);
	if (!m_textures["Sunny head"].loadFromFile("images/Sunny head.png"))
		exit(1);
	if (!m_textures["Bella body"].loadFromFile("images/Bella body.png"))
		exit(1);
	if (!m_textures["Bob body"].loadFromFile("images/Bob body.png"))
		exit(1);
	if (!m_textures["Chicko body"].loadFromFile("images/Chicko body.png"))
		exit(1);
	if (!m_textures["Dino body"].loadFromFile("images/Dino body.png"))
		exit(1);
	if (!m_textures["Loony body"].loadFromFile("images/Loony body.png"))
		exit(1);
	if (!m_textures["Nelly body"].loadFromFile("images/Nelly body.png"))
		exit(1);
	if (!m_textures["Peep body"].loadFromFile("images/Peep body.png"))
		exit(1);
	if (!m_textures["Shmoopy body"].loadFromFile("images/Shmoopy body.png"))
		exit(1);
	if (!m_textures["Sunny body"].loadFromFile("images/Sunny body.png"))
		exit(1);

	for(auto it = m_textures.begin(); it != m_textures.end(); ++it)
		it->second.setSmooth(true);

	readWormProfile();
}
//-----------------------------------------------------------------------------
void Singleton::readWormProfile()
{
	std::ifstream wormProfile("wormProfile/profiles.txt");
	std::string line;

	while (getline(wormProfile, line))
		setWormProfile(line);
}
//-----------------------------------------------------------------------------
void Singleton::setWormProfile(std::string line)
{
	sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();

	WormProfile newProfile;
	sf::Texture newTexture;
	std::string temp;
	unsigned i = 0;

	//טקסטורה
	for (; line[i] != ' '; i++)
	{
		temp.push_back(line[i]);
	}
	newProfile.wormProfileTexture = m_textures[temp];
	temp.erase(temp.end() - 8, temp.end());
	temp += " body";
	newProfile.wormBodyTexture = m_textures[temp];
	temp.erase(temp.end() - 4, temp.end());
	temp += "head";
	newProfile.wormHeadTexture = m_textures[temp];
	
	temp.clear();

	//ליזר
	for (++i; line[i] != ' '; i++)
	{
		temp.push_back(line[i]);
	}
	newProfile.laser = std::stoi(temp);//stoi=string to int
	temp.clear();

	//בוסט
	for (++i; line[i] != ' '; i++)
	{
		temp.push_back(line[i]);
	}
	newProfile.boost = (std::stoi(temp)); //stoi=string to int
	temp.clear();

	//גודל
	for (++i; line[i] != ' '; i++)
	{
		temp.push_back(line[i]);
	}
	newProfile.wormSize = (std::stoi(temp));
	m_wormProfile.emplace_back(std::make_shared<WormProfile>(newProfile));
}
//-----------------------------------------------------------------------------
void Singleton::setFont()
{
	if (!m_font.loadFromFile("arial.ttf"))
		exit(1);
}
//-----------------------------------------------------------------------------
Singleton & Singleton::instance()
{
	static Singleton inst;
	return inst;
}
//-----------------------------------------------------------------------------
sf::Texture & Singleton::getTexture(std::string texturName)
{
	return m_textures[texturName];
}
//-----------------------------------------------------------------------------
std::shared_ptr<WormProfile> Singleton::getWormProfile(unsigned profile)
{
	return m_wormProfile[profile];
}
