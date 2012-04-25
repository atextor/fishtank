/* Animation.h
 *
 * fishtank - fish swarm simulation
 * by Andreas Textor <textor.andreas@googlemail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#ifndef ANIMATION_H_
#define ANIMATION_H_
#include <list>
#include <iostream>
#include <cmath>
#include "Transform.h"
#include "Vector.h"
using std::list;
using std::cout;

/**
 * Class for cyclic animations. Each animation registers itself in the list of
 * animations which is implemented via a class variable. When the method
 * nextTick is called, all Animation instances in the list are increased on
 * tick. A cyclic animation has a wave form, a period and an amplitude and can
 * influence a combination of fields of a transformation.
 */
class Animation
{
private:
	/**
	 * The transformation which should be manipulated by this animation
	 */
	Transform* target;
	
	/**
	 * The wave form of the animation. Must be one of the static constants ANI_*
	 */
	int aniType;
	
	/**
	 * The period (wave width) of the animation. Is proportional to the
	 * calling frequency of the nextTick() method.
	 */
	double period;
	
	/**
	 * The amplitude (wave height) of the animation 
	 */
	double amplitude;
	
	/**
	 * The displacement (vertical wave offset). If displacement == amplitude,
	 * the range of values of the wave is between 0 and the amplitude.
	 */
	double displacement;
	
	/**
	 * Controls which components of the transformation vector are influenced
	 * by the animation.
	 * 1000 - x-component of the vector is influenced
	 * 0100 - y-component of the vector is influenced
	 * 0010 - z-component of the vector is influenced
	 * 0001 - w-component of the vector is influenced
	 * E.g. 0x6 changes y and y components simultaneously
	 */
	int fieldMask;
	
	/**
	 * List of animations that should be increased on call of nextTick()
	 */
	static list<Animation*> animations;
	
	/**
	 * Method a newly created Animation instance calls to register itself
	 */
	static void registerNew(Animation* ani);
	
public:
	/**
	 * Removes and animation from a transformation
	 */
	static void remove(Transform* t);
	
	/**
	 * Wave form: sinusoidal. Formular: (sin(tick/periode)*amplitude)+displacement
	 */
	static const int ANI_SINUSOIDAL = 0x0001;
	
	/**
	 * Wave form: saw tooth. Formular: (tick mod amplitude)*periode
	 */
	static const int ANI_SAWTOOTH = 0x0002;
	
	/**
	 * Constructor. Creating the animation object also starts the animation
	 */
	Animation(Transform* target, int aniType, double period, double amplitude,
			double displacement, int fieldMask);
	
	/**
	 * Increase all animation instances in the static list by one tick
	 */
	static void nextTick(unsigned long tick);
	
	/**
	 * Default destructor
	 */
	virtual ~Animation();
};

#endif /*ANIMATION_H_*/
