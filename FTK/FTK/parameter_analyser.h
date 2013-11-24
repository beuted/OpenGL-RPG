/**
 * Fichier contenant la classe parameter_analyser
 */
#ifndef H__parameter_analyser__
#define H__parameter_analyser__

#include <map>
#include <string>

/**
 * \class parameter_analyser permettant de reccuperer et de gerer les
 * parametres lors de l'appel de l'application
 */
class parameter_analyser{
public:
	parameter_analyser();
	parameter_analyser(int, char**);
	std::map<std::string, bool> data;
};

#endif
