#include "cConfiguration.h"

cConfiguration::cConfiguration(std::string Path) :
	m_PathFile(Path)
{
}
cConfiguration::cConfiguration(std::string Path, std::map<std::string, std::string> Default) :
	m_PathFile(Path),
	m_Default(Default)
{
}
cConfiguration::~cConfiguration() {}

void cConfiguration::LoadDefault()
{
	m_Data = m_Default;
}
void cConfiguration::Load()
{
	std::ifstream        fsStream(m_PathFile);
	std::string          ln;

	this->LoadDefault();

	if (!fsStream.is_open())
		this->Save();
	else
	{
		while (std::getline(fsStream, ln))
		{
			std::string	key;
			std::string	value;
			bool	keyFound = false;
			bool	readingValue = false;
			for (char x : ln)
			{
				if (x == '#' || x == '!' || x == ';')
					break;

				else if ((x == ' ' || x == '\t') && !readingValue)
					continue;

				else if (x == '=')
					keyFound = true;

				else if (!keyFound)
					key.push_back(x);

				else if (keyFound)
				{
					value.push_back(x);
					readingValue = true;
				}
			}
			if (keyFound)
				this->set(key, value);
		}
	}
	fsStream.close();
}
void cConfiguration::Save()  const
{
	std::fstream fsStream(m_PathFile, std::fstream::out);
	fsStream << "#######################################" << std::endl;
	fsStream << "###         System Engine 2017      ###" << std::endl;
	fsStream << "#######################################" << std::endl;
	fsStream << "#                                     #" << std::endl;
	fsStream << "#     t.me/youngcodersteam_official   #" << std::endl;
	fsStream << "#                                     #" << std::endl;
	fsStream << "#             system-bot.ru           #" << std::endl;
	fsStream << "#                                     #" << std::endl;
	fsStream << "#######################################" << std::endl;
	fsStream << std::endl;

	for (auto i : m_Data)
		fsStream << i.first << " = " << i.second << std::endl;

	fsStream.close();
}
void cConfiguration::Print() const
{
	for (auto i : m_Data)
		std::cout << i.first << " = " << i.second << std::endl;
}

void cConfiguration::set(const std::string& szKey, const std::string& value)
{
	if (m_Data.find(szKey) != m_Data.end())
		m_Data.at(szKey) = value;
	else
		m_Data.insert({ szKey, value });
}
void cConfiguration::set(const std::string& szKey, bool value)
{
	this->set(szKey, std::string((value) ? "true" : "false"));
}
void cConfiguration::set(const std::string& szKey, float value)
{
	this->set(szKey, std::to_string(value));
}
void cConfiguration::set(const std::string& szKey, int value)
{
	this->set(szKey, std::to_string(value));
}
void cConfiguration::set(const std::string& szKey, const char* value)
{
	this->set(szKey, std::string(value));
}

std::string cConfiguration::get(const std::string& szKey) const
{
	if (m_Data.find(szKey) != m_Data.end())
		return m_Data.at(szKey);
	else
		return "";
}
bool        cConfiguration::getBool(const std::string& szKey) const
{
	if (m_Data.find(szKey) != m_Data.end())
	{
		std::string value = m_Data.at(szKey);
		std::transform(value.begin(), value.end(), value.begin(), tolower);

		if (value == "true" || value == "1" ||
			value == "on" || value == "enable")
			return true;
	}
	return false;
}
float       cConfiguration::getFloat(const std::string& szKey) const
{
	if (m_Data.find(szKey) != m_Data.end())
		return std::atof(m_Data.at(szKey).c_str());
	else
		return 0.f;
}
int         cConfiguration::getInt(const std::string& szKey) const
{
	if (m_Data.find(szKey) != m_Data.end())
		return std::atoi(m_Data.at(szKey).c_str());
	else
		return 0;
}