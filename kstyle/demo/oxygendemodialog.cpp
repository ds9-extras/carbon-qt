//////////////////////////////////////////////////////////////////////////////
// carbondemodialog.cpp
// carbon configuration dialog
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
#include "carbondemodialog.h"

#include "carbonbenchmarkwidget.h"
#include "carbonbuttondemowidget.h"
#include "carboninputdemowidget.h"
#include "carbonframedemowidget.h"
#include "carbonlistdemowidget.h"
#include "carbonmdidemowidget.h"
#include "carbonsliderdemowidget.h"
#include "carbontabdemowidget.h"
#include "config-libcarbon.h"

#include <QTextStream>
#include <QShortcut>
#include <QDialogButtonBox>

#include <QIcon>
#include <KStandardShortcut>

namespace Carbon
{
    //_______________________________________________________________
    DemoDialog::DemoDialog( QWidget* parent ):
        QDialog( parent ),
        _enableCheckBox( 0 ),
        _rightToLeftCheckBox( 0 )
    {

        setWindowTitle( i18n( "Carbon Demo" ) );

        // ui
        setupUi(this);

        #if CARBON_USE_KDE4
        // install Quit shortcut
        connect( new QShortcut( KStandardShortcut::quit().primary(), this ), SIGNAL(activated()), SLOT(close()) );
        connect( new QShortcut( KStandardShortcut::quit().alternate(), this ), SIGNAL(activated()), SLOT(close()) );
        #else
        // install Quit shortcut
        foreach( const QKeySequence& sequence, KStandardShortcut::quit() )
        { connect( new QShortcut( sequence, this ), SIGNAL(activated()), SLOT(close()) ); }
        #endif

        connect( buttonBox->button( QDialogButtonBox::Ok ), SIGNAL(clicked()), SLOT(close()) );

        // customize button box
        _enableCheckBox = new QCheckBox( i18n( "Enabled" ) );
        _enableCheckBox->setChecked( true );
        connect( _enableCheckBox, SIGNAL(toggled(bool)), SLOT(toggleEnable(bool)) );
        buttonBox->addButton( _enableCheckBox, QDialogButtonBox::ResetRole );

        _rightToLeftCheckBox = new QCheckBox( i18n( "Right to left layout" ) );
        connect( _rightToLeftCheckBox, SIGNAL(toggled(bool)), SLOT(toggleRightToLeft(bool)) );
        buttonBox->addButton( _rightToLeftCheckBox, QDialogButtonBox::ResetRole );

        // connections
        connect( pageWidget, SIGNAL(currentPageChanged(KPageWidgetItem*,KPageWidgetItem*)), SLOT(updateWindowTitle(KPageWidgetItem*)) );
        connect( pageWidget, SIGNAL(currentPageChanged(KPageWidgetItem*,KPageWidgetItem*)), SLOT(updateEnableState(KPageWidgetItem*)) );
        KPageWidgetItem *page;
        DemoWidget *widget;

        // inputs
        {
            page = new KPageWidgetItem( widget = new InputDemoWidget() );
            page->setName( i18n("Input Widgets") );
            setPageIcon( page, QStringLiteral( "edit-rename" ) );
            page->setHeader( i18n("Shows the appearance of text input widgets") );
            pageWidget->addPage( page );
            _widgets.append( widget );
        }

        // tab
        {
            page = new KPageWidgetItem( widget = new TabDemoWidget() );
            page->setName( i18n("Tab Widgets") );
            setPageIcon( page, QStringLiteral( "tab-detach" ) );
            page->setHeader( i18n("Shows the appearance of tab widgets") );
            pageWidget->addPage( page );
            _widgets.append( widget );
        }

        // buttons
        {
            page = new KPageWidgetItem( widget = new ButtonDemoWidget() );
            page->setName( i18n("Buttons") );
            setPageIcon( page, QStringLiteral( "go-jump-locationbar" ) );
            page->setHeader( i18n("Shows the appearance of buttons") );
            pageWidget->addPage( page );
            _widgets.append( widget );
        }

        // lists
        {
            page = new KPageWidgetItem( widget = new ListDemoWidget() );
            page->setName( i18n("Lists") );
            setPageIcon( page, QStringLiteral( "view-list-tree" ) );
            page->setHeader( i18n("Shows the appearance of lists, trees and tables") );
            pageWidget->addPage( page );
            _widgets.append( widget );

        }

        // frames
        {
            page = new KPageWidgetItem( widget = new FrameDemoWidget() );
            page->setName( i18n("Frames") );
            setPageIcon( page, QStringLiteral( "draw-rectangle" ) );
            page->setHeader( i18n("Shows the appearance of various framed widgets") );
            pageWidget->addPage( page );
            _widgets.append( widget );
        }

        // mdi
        {
            page = new KPageWidgetItem( widget = new MdiDemoWidget() );
            page->setName( i18n( "MDI Windows" ) );
            setPageIcon( page, QStringLiteral( "preferences-system-windows" ) );
            page->setHeader( i18n( "Shows the appearance of MDI windows" ) );
            pageWidget->addPage( page );
            _widgets.append( widget );
        }

        // sliders
        {
            page = new KPageWidgetItem( widget = new SliderDemoWidget() );
            page->setName( i18n("Sliders") );
            setPageIcon( page, QStringLiteral( "measure" ) );
            page->setHeader( i18n("Shows the appearance of sliders, progress bars and scrollbars") );
            pageWidget->addPage( page );
            _widgets.append( widget );
        }

        // benchmark
        {
            BenchmarkWidget* benchmarkWidget( new BenchmarkWidget() );
            page = new KPageWidgetItem( benchmarkWidget );
            page->setName( i18n("Benchmark") );
            setPageIcon( page, QStringLiteral( "system-run" ) );
            page->setHeader( i18n("Emulates user interaction with widgets for benchmarking") );
            benchmarkWidget->init( pageWidget );

            pageWidget->addPage( page );
            _widgets.append( benchmarkWidget );
        }

        // connections
        QShortcut* shortcut( new QShortcut( Qt::CTRL + Qt::Key_X, this ) );
        foreach( DemoWidget* widget, _widgets )
        {
            if( widget->metaObject()->indexOfSlot( "benchmark()" ) >= 0 )
            { connect( shortcut, SIGNAL(activated()), widget, SLOT(benchmark()) ); }

            connect( this, SIGNAL(abortSimulations()), &widget->simulator(), SLOT(abort()) );

        }

    }

    //_______________________________________________________________
    void DemoDialog::updateWindowTitle( KPageWidgetItem* item )
    {

        QString title;
        QTextStream what( &title );
        if( item )
        {
            what << item->name();
            what << " - ";
        }

        what << i18n( "Carbon Demo" );
        setWindowTitle( title );
    }

    //_______________________________________________________________
    void DemoDialog::updateEnableState( KPageWidgetItem* item )
    {

        if( !( item && item->widget() && _enableCheckBox ) ) return;
        item->widget()->setEnabled( _enableCheckBox->isChecked() );

    }

    //_______________________________________________________________
    void DemoDialog::toggleEnable( bool value )
    {
        if( !( pageWidget->currentPage() && pageWidget->currentPage()->widget() ) ) return;
        pageWidget->currentPage()->widget()->setEnabled( value );
    }

    //_______________________________________________________________
    void DemoDialog::toggleRightToLeft( bool value )
    { qApp->setLayoutDirection( value ? Qt::RightToLeft:Qt::LeftToRight ); }

    //_______________________________________________________________
    void DemoDialog::closeEvent( QCloseEvent* event )
    {
        emit abortSimulations();
        QDialog::closeEvent( event );
    }

    //_______________________________________________________________
    void DemoDialog::hideEvent( QHideEvent* event )
    {
        emit abortSimulations();
        QDialog::hideEvent( event );
    }

    //_______________________________________________________________
    void DemoDialog::setPageIcon( KPageWidgetItem* page, const QString& iconName ) const
    {
        #if CARBON_USE_KDE4
        page->setIcon( KIcon( iconName ) );
        #else
        page->setIcon( QIcon::fromTheme( iconName ) );
        #endif
    }

}
