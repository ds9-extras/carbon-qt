#ifndef carbonexceptiondialog_h
#define carbonexceptiondialog_h
//////////////////////////////////////////////////////////////////////////////
// carbonexceptiondialog.h
// -------------------
//
// Copyright (c) 2009 Hugo Pereira Da Costa <hugo.pereira@free.fr>
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

#include "ui_carbonexceptiondialog.h"
#include "../carbondecorationdefines.h"

#include <QCheckBox>
#include <QMap>

namespace Carbon
{

    class DetectDialog;

    //! carbon exceptions list
    class ExceptionDialog: public QDialog, Ui::CarbonExceptionDialog
    {

        Q_OBJECT

        public:

        //! constructor
        explicit ExceptionDialog( QWidget* parent );

        //! destructor
        virtual ~ExceptionDialog( void )
        {}

        //! set exception
        void setException( ConfigurationPtr );

        //! save exception
        void save( void );

        //! true if changed
        virtual bool isChanged( void ) const
        { return _changed; }

        Q_SIGNALS:

        //! emmited when changed
        void changed( bool );

        protected:

        //! set changed state
        virtual void setChanged( bool value )
        {
            _changed = value;
            emit changed( value );
        }

        protected Q_SLOTS:

        //! check whether configuration is changed and emit appropriate signal if yes
        virtual void updateChanged();

        private Q_SLOTS:

        //! select window properties from grabbed pointers
        void selectWindowProperties( void );

        //! read properties of selected window
        void readWindowProperties( bool );

        private:

        //! map mask and checkbox
        typedef QMap< ExceptionMask, QCheckBox*> CheckBoxMap;

        //! map mask and checkbox
        CheckBoxMap _checkBoxes;

        //! internal exception
        ConfigurationPtr _exception;

        //! detection dialog
        DetectDialog* _detectDialog;

        //! changed state
        bool _changed;

    };

}

#endif
