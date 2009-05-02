/******************************************************************************\
*
* File:          UnionFind.h
* Creation date: September 16, 2005
* Author:        Francesco Iovine
*
* Purpose:       Fig.9.2
*
* License:       See the end of this file for license information
*
* Modifications:
*   1)  Commentati tutti i metodi della classe base.
*       October 2, 2006. Francesco Iovine
*
\******************************************************************************/
#ifndef _UNIONFIND_H
#define _UNIONFIND_H


namespace asd {

/*
Figura 9.2
La struttura UnionFind.
*/
template<class Elem>
class UnionFind
{
/* dati:
      una collezione di insiemi disgiunti di elementi 'elem'; 
      ogni insieme ha un nome 'name' */

  public:  // operazioni
    virtual ~UnionFind() {}
    
//    void* makeSet(const Elem& e);
//    void union_(void* a, void* b);
//    void* find(void* v) const;
};

}  // namespace asd


#endif /* _UNIONFIND_H */ 



/******************************************************************************\
 * Copyright (C) 2006 ASD Team

 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.

 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
\******************************************************************************/
