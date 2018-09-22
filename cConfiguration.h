#pragma once
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <algorithm>



class cConfiguration
{
public:
	cConfiguration(std::string Path);
	cConfiguration(std::string Path, std::map<std::string, std::string> Default);
	~cConfiguration();

	void	    Load();
	void	    LoadDefault();
	void	    Save() const;
	void	    Print() const;

	void	    set(const std::string& szKey, const std::string& value);
	void	    set(const std::string& szKey, bool               value);
	void	    set(const std::string& szKey, float              value);
	void	    set(const std::string& szKey, int                value);
	void	    set(const std::string& szKey, const char*        value);

	std::string	get(const std::string& szKey)      const;
	bool	    getBool(const std::string& szKey)  const;
	float	    getFloat(const std::string& szKey) const;
	int		    getInt(const std::string& szKey)   const;

private:
	std::map<std::string, std::string>	m_Data;
	std::map<std::string, std::string>	m_Default;
	std::string				            m_PathFile;
};