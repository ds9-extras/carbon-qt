/*
 * Copyright 2007 Matthew Woehlke <mw_triad@users.sourceforge.net>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License version 2 as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef TILESET_H
#define TILESET_H

#include <QtGui/QPixmap>
#include <QtCore/QRect>
#include <QtCore/QVector>

#include "oxygen_export.h"

//! handles proper scaling of pixmap to match widget rect.
/*!
tilesets are collections of stretchable pixmaps corresponding to a given widget corners, sides, and center.
corner pixmaps are never stretched. center pixmaps are
*/
namespace Oxygen
{
    class OXYGEN_EXPORT TileSet
    {
        public:
        /**
        * Create a TileSet from a pixmap. The size of the bottom/right chunks is
        * whatever is left over from the other chunks, whose size is specified
        * in the required parameters.
        *
        * @param w1 width of the left chunks
        * @param h1 height of the top chunks
        * @param w2 width of the not-left-or-right chunks
        * @param h2 height of the not-top-or-bottom chunks
        */
        TileSet(const QPixmap&, int w1, int h1, int w2, int h2);

        /**
        * Create a TileSet from a pixmap. The size of the top/left and bottom/right
        * chunks is specified, with the middle chunks created from the specified
        * portion of the pixmap. This allows the middle chunks to overlap the outer
        * chunks (or to not use all pixels). The top/left and bottom/right chunks
        * are carved out of the corners of the pixmap.
        *
        * @param w1 width of the left chunks
        * @param h1 height of the top chunks
        * @param w3 width of the right chunks
        * @param h3 height of bottom chunks
        * @param x2 x-coordinate of the top of the not-left-or-right chunks
        * @param y2 y-coordinate of the left of the not-top-or-bottom chunks
        * @param w2 width of the not-left-or-right chunks
        * @param h2 height of the not-top-or-bottom chunks
        */
        TileSet(const QPixmap &pix, int w1, int h1, int w3, int h3, int x2, int y2, int w2, int h2);

        //! empty constructor
        TileSet();

        //! destructor
        virtual ~TileSet()
        {}

        /**
        * Flags specifying what sides to draw in ::render. Corners are drawn when
        * the sides forming that corner are drawn, e.g. Top|Left draws the
        * top-center, center-left, and top-left chunks. The center-center chunk is
        * only drawn when Center is requested.
        */
        enum Tile {
            Top = 0x1,
            Left = 0x2,
            Right = 0x8,
            Bottom = 0x4,
            Center = 0x10,
            Ring = 0x0f,
            Horizontal = 0x1a,
            Vertical = 0x15,
            Full = 0x1f
        };
        Q_DECLARE_FLAGS(Tiles, Tile)

        /**
        * Fills the specified rect with tiled chunks. Corners are never tiled,
        * edges are tiled in one direction, and the center chunk is tiled in both
        * directions. Partial tiles are used as needed so that the entire rect is
        * perfectly filled. Filling is performed as if all chunks are being drawn.
        */
        void render(const QRect&, QPainter*, Tiles = Ring) const;

        //! return size associated to this tileset
        QSize size( void ) const
        { return QSize( _w1 + _w3, _h1 + _h3 ); }

        //! is valid
        bool isValid( void ) const
        { return size().isValid() && _pixmap.size() == 9; }

        protected:

        // initialize pixmap
        void initPixmap( int, const QPixmap&, int w, int h, const QRect &region);

        //! pixmap arry
        QVector<QPixmap> _pixmap;

        // dimensions
        int _w1;
        int _h1;
        int _w3;
        int _h3;

    };

}

Q_DECLARE_OPERATORS_FOR_FLAGS(Oxygen::TileSet::Tiles)

#endif //TILESET_H