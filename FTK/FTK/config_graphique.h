/*
 * config_graphique.h
 *
 *  Created on: 10 mars 2013
 *      Author: benoit
 */

#ifndef CONFIG_GRAPHIQUE_H_
#define CONFIG_GRAPHIQUE_H_

#include <fstream>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

class Config_graphique {
private:
        friend class boost::serialization::access;

        template<class Archive>
        void serialize(Archive & ar, const unsigned int version) {
                ar & width;
                ar & height;
                ar & vision_max;
                ar & fps;
        }

        unsigned int width;
		unsigned int height;
		double vision_max;
        double fps;

public:
        Config_graphique() {};
        Config_graphique(unsigned int _width, unsigned int _height, double _vision_max, double _fps) :
        	width(_width), height(_height), vision_max(_vision_max), fps(_fps) {}
        /**
         * Permet de reccuperer la config dans les parametres donnés en reference
         */
        void dechargerConfig(unsigned int  &_width, unsigned int &_height, double &_vision_max, double &_fps) {
        	_width = width; _height = height;_vision_max = vision_max;_fps = fps;
        }
};


#endif /* CONFIG_GRAPHIQUE_H_ */
