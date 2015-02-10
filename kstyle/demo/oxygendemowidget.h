#ifndef carbondemowidget_h
#define carbondemowidget_h

//////////////////////////////////////////////////////////////////////////////
// carbondemowidget.h
// base class for carbon demo widgets
// -------------------
//
// Copyright (c) 2010 Hugo Pereira Da Costa <hugo.pereira@free.fr>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//////////////////////////////////////////////////////////////////////////////

#include <QWidget>

#include "carbonsimulator.h"

namespace Carbon
{

    class DemoWidget: public QWidget
    {

        Q_OBJECT

        public:

        //! constructo
        explicit DemoWidget( QWidget* parent ):
            QWidget( parent ),
            _simulator( new Simulator( this ) )
        {}

        //! destructor
        virtual ~DemoWidget( void )
        {}

        //! simulator
        Simulator& simulator( void ) const
        { return *_simulator; }

        private:

        //! simulator
        Simulator* _simulator;

    };

}

#endif
