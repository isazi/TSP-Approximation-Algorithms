/*
 * ArgumentList.h
 *
 *  Created on: Jan 18, 2009
 *      Author: Alessio Sclocco <alessio@sclocco.eu>
 *
 *     License: See the end of this file for license information
 */

#ifndef ARGUMENTLIST_H_
#define ARGUMENTLIST_H_

#include <string>
#include <list>

using std::string;
using std::list;

namespace sclocco {

class ArgumentList {
public:
	ArgumentList(int argc, char *argv[]);
	~ArgumentList();

	/* Method for getting an empty switch */
	bool getSwitch(string opt);
	/* Method for getting the argument of a given switch */
	string getSwitchArgument(string opt);
	/* Method for getting the first argument */
	string getFirst();

private:
	list< string * > *args;
};

} // namespace sclocco

#endif /* ARGUMENTLIST_H_ */

/*
 * Copyright 2009 Alessio Sclocco <alessio@sclocco.eu>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
