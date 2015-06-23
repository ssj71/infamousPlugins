/*
 * Hydrogen
 * Copyright(c) 2002-2005 by Alex >Comix< Cominu [comix@users.sourceforge.net]
 *
 * http://www.hydrogen-music.org
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY, without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * $Id: LCD.cpp,v 1.17 2005/05/23 11:21:01 comix Exp $
 *
 */

#include "LCD.h"

//#include "../Skin.h"

//QPixmap* LCDDigit::m_pSmallBlueFontSet = NULL;
//QPixmap* LCDDigit::m_pSmallRedFontSet = NULL;
//QPixmap* LCDDigit::m_pLargeGrayFontSet = NULL;
//QPixmap* LCDDigit::m_pSmallGrayFontSet = NULL;

LCDDigit::LCDDigit( QWidget * pParent, LCDType type )
 : QWidget( pParent)// , "LCDDigit", )//, Qt::WRepaintNoErase | Qt::WResizeNoErase )
 //, Object( "LCDDigit" )
 , m_bChanged( true )
 , m_type( type )
{
        switch ( m_type ) {
                case SMALL_BLUE:{
                        QString sSmallBlueFontSet = "lcd/LCDSmallBlueFontSet.png";
                        bool ok = fontSet.load(sSmallBlueFontSet);
                        //d_w = 8;
                        //d_h = 11;
                        break;
                        }
                case SMALL_RED:{
                        //resize( 8, 11 );
                        QString sSmallRedFontSet = /*Skin::getImagePath() +*/ QString( "lcd/LCDSmallRedFontSet.png" );
                        bool ok = fontSet.load(sSmallRedFontSet);
                        //d_w = 8;
                        //d_h = 11;
			break;
                        }
                case LARGE_GRAY:{
                        //resize( 14, 16 );
                        QString sLargeGrayFontSet = /*Skin::getImagePath() +*/ QString( "lcd/LCDLargeGrayFontSet.png" );
                        bool ok = fontSet.load(sLargeGrayFontSet);
                        //d_w = 14;
                        //d_h = 16;
			break;
                        }
                case SMALL_GRAY:{
                        //resize( 12, 11 );
                        //d_w = 12;
                        //d_h = 11;
                        break;
                        }
        }

        //setMinimumSize( width(), height() );
        //setMaximumSize( width(), height() );
/*
        // Small blue FontSet image
        if (m_pSmallBlueFontSet == NULL ) {
                QString sSmallBlueFontSet = Skin::getImagePath() + QString( "/lcd/LCDSmallBlueFontSet.png" );
                //m_pSmallBlueFontSet = new QPixmap();
                //bool ok = m_pSmallBlueFontSet->load( sSmallBlueFontSet );
                bool ok = fontSet.load(sSmallBlueFontSet);
                if( ok == false ) {
                        //errorLog( string("Fader: Error loading pixmap") );
                }
        }

        // Small red FontSet image
        if (m_pSmallRedFontSet == NULL ) {
                QString sSmallRedFontSet = /*Skin::getImagePath() + QString( "/lcd/LCDSmallRedFontSet.png" );
                //m_pSmallRedFontSet = new QPixmap();
                //bool ok = m_pSmallRedFontSet->load( sSmallRedFontSet );
                bool ok = fontSet.load(sSmallRedFontSet);
                if( ok == false ) {
                        //errorLog("Fader: Error loading pixmap");
                }
        }

        // Large gray FontSet image
        if (m_pLargeGrayFontSet == NULL ) {
                QString sLargeGrayFontSet = /*Skin::getImagePath() + QString( "/lcd/LCDLargeGrayFontSet.png" );
                //m_pLargeGrayFontSet = new QPixmap();
                //bool ok = m_pLargeGrayFontSet->load( sLargeGrayFontSet );
                bool ok = fontSet.load(sLargeGrayFontSet);
                if( ok == false ) {
                        //errorLog("Fader: Error loading pixmap");
                }
        }

        // Small gray FontSet image
        if (m_pSmallGrayFontSet == NULL ) {
                QString sSmallGrayFontSet = /*Skin::getImagePath() + QString( "/lcd/LCDSmallGrayFontSet.png" );
                //m_pSmallGrayFontSet = new QPixmap();
                //bool ok = m_pSmallGrayFontSet->load( sSmallGrayFontSet );
                bool ok = fontSet.load(sSmallGrayFontSet);
                if( ok == false ) {
                        //errorLog("Fader: Error loading pixmap");
                }
        }

        m_temp.scaled( width(), height(),, );
*/
	set( ' ' );
}

LCDDigit::LCDDigit( QWidget * pParent, QString file )
 : QWidget( pParent)
 , m_bChanged( true )
{
        bool ok = fontSet.load(file);
        set(' ');
}

LCDDigit::~LCDDigit()
{
//	delete m_pSmallBlueFontSet;
//	m_pSmallBlueFontSet = NULL;

//	delete m_pSmallRedFontSet;
//	m_pSmallRedFontSet = NULL;
}


//void LCDDigit::mousePressEvent(QMouseEvent *ev)
void LCDDigit::mouseReleaseEvent(QMouseEvent* ev)
{
	emit digitClicked();
}


void LCDDigit::paintEvent(QPaintEvent *ev)
{
	if (!isVisible()) {
		return;
	}
        QPainter tmppntr(this);
        int x = m_nCol * width();
        int y = m_nRow * height();
/*
//	if (m_bChanged) {
//		m_bChanged = false;

//		int x = m_nCol * width();
//		int y = m_nRow * height();
//                tmppntr.drawImage(0,0, fontSet.scaled(width()/d_w,height()/d_h,,), x, y, width(), height(),  );

//		switch ( m_type ) {
//			case SMALL_BLUE:
//                                //bitBlt( &m_temp, 0, 0, m_pSmallBlueFontSet, x, y, width(), height(), CopyROP );
//                                tmppntr.drawImage(0,0, fontSet.scaled(width()/d_w,height()/d_h,,), x, y, width(), height(),  );

//				break;

//			case SMALL_RED:
//				bitBlt( &m_temp, 0, 0, m_pSmallRedFontSet, x, y, width(), height(), CopyROP );
//				break;

//			case LARGE_GRAY:
//                                bitBlt( &m_temp, 0, 0, m_pLargeGrayFontSet, x, y, width(), height(), CopyROP );
//				break;

//			case SMALL_GRAY:
//				bitBlt( &m_temp, 0, 0, m_pSmallGrayFontSet, x, y, width(), height(), CopyROP );
//				break;

//			default:
//                                //errorLog( "[paint] Unhandled type" );
//		}
//	}

        //bitBlt( this, 0, 0, &m_temp, 0, 0, width(), height(), CopyROP, true );
*/      //QImage tmp = fontSet.scaled(width(),height());
        tmppntr.drawImage(0,0, fontSet.scaled(66*width(),4*height()), x, y, width(), height(), Qt::AutoColor );
        //tmppntr.drawImage(0,0,fontSet,0,y,-1,-1,Qt::AutoColor);
}


void LCDDigit::set( QChar ch )
{
	int MAXCOL = 66;
        QString keymap = "ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz 0123456789  -:/\\,;.       !?";
	for ( int n = 0; n < 73; n++ ) {
            if ( keymap[n] == ch ) {
			m_nCol = n % MAXCOL;
			m_nRow = n / MAXCOL;
			break;
		}
	}

	m_bChanged = true;
	update();
}

/*
//void LCDDigit::setSmallRed()
//{
//	m_type = SMALL_RED;
//	m_bChanged = true;
//	update();
//}


//void LCDDigit::setSmallBlue()
//{
//	m_type = SMALL_BLUE;
//	m_bChanged = true;
//	update();
//}



// ::::::::::::::::::


*/
/*
LCDDisplay::LCDDisplay( QWidget * pParent, LCDDigit::LCDType type, int nDigits )
 : QWidget( pParent )
 , m_sMsg( "" )
{
        padded = false;
        switch ( type ) {
            case LCDDigit::SMALL_BLUE:
            case LCDDigit::SMALL_RED:
                    ratio = 11.0/8.0;
                    break;

            case LCDDigit::LARGE_GRAY:
                    ratio = 16.0/14.0;
                    break;
        }
	for ( int n = 0; n < nDigits; n++ ) {
		LCDDigit *pDigit = new LCDDigit( this, type );
		if ( ( type == LCDDigit::LARGE_GRAY ) || ( type == LCDDigit::SMALL_GRAY ) ) {
			pDigit->move( pDigit->width() * n, 0 );
		}
		else {
                        pDigit->move( pDigit->width() * n + 2, 2 );
		}
		connect( pDigit, SIGNAL( digitClicked() ), this, SLOT( digitClicked() ) );
		m_pDisplay.push_back( pDigit );
	}

	if ( ( type == LCDDigit::LARGE_GRAY ) || ( type == LCDDigit::SMALL_GRAY ) ) {
		int w = m_pDisplay[ 0 ]->width() * nDigits;
		int h = m_pDisplay[ 0 ]->height();

		resize( w, h );
	}
	else {
		int w = m_pDisplay[ 0 ]->width() * nDigits + 4;
		int h = m_pDisplay[ 0 ]->height() + 4;

		resize( w, h );
	}
        //setMinimumSize( width(), height() );
        //setMaximumSize( width(), height() );

	setText( "    ");
	
	// default background color..
        //setPaletteBackgroundColor( QColor( 49, 53, 61 ) ); experimental
}

LCDDisplay::LCDDisplay( QWidget * pParent, LCDDigit::LCDType type )
 : QWidget( pParent)
 , m_sMsg( "" )
 , m_type(type)
{
    padded = false;
    switch ( type ) {
        case LCDDigit::SMALL_BLUE:
        case LCDDigit::SMALL_RED:
                ratio = 11.0/8.0;
                break;

        case LCDDigit::LARGE_GRAY:
                ratio = 16.0/15.0;
                break;

        default:
                ratio = 1;
    }
    int nDigits = width()/height()*ratio + 2;
    for ( int n = 0; n < nDigits; n++ ) {
            LCDDigit *pDigit = new LCDDigit( this, type );

            pDigit->move( pDigit->width() * n, 0 );

            connect( pDigit, SIGNAL( digitClicked() ), this, SLOT( digitClicked() ) );
            m_pDisplay.push_back( pDigit );
    }

    setText( "    ");
}
*/
LCDDisplay::LCDDisplay( QWidget * pParent, bool large, QString file )
 : QWidget( pParent)
 , m_sMsg( "" )
 , imgfile(file)
{
    padded = false;
    if (large) ratio = 16.0/15.0;
    else ratio = 11.0/8.0;

    int nDigits = width()/height()*ratio + 2;
    for ( int n = 0; n < nDigits; n++ ) {
            LCDDigit *pDigit = new LCDDigit( this, imgfile);

            pDigit->move( pDigit->width() * n, 0 );

            connect( pDigit, SIGNAL( digitClicked() ), this, SLOT( digitClicked() ) );
            m_pDisplay.push_back( pDigit );
    }

    setText( "    ");
}


LCDDisplay::~LCDDisplay() {
	for ( uint i = 0; i < m_pDisplay.size(); i++ ) {
		delete m_pDisplay[ i ];
	}
}


void LCDDisplay::setText( QString sMsg )
{
	m_sMsg = sMsg;
	// right aligned

	int nPadding = 0;
	int nLen = sMsg.length();
        if ( padded && nLen < (int)m_pDisplay.size() ) {
		nPadding = m_pDisplay.size() - nLen;
	}
	else {
		nLen = m_pDisplay.size();
	}

        for ( int i = 0; i < nPadding; i++) {
                m_pDisplay[ i ]->set( ' ' );
        }

	for ( int i = 0; i < nLen; i++ ) {
            m_pDisplay[ i + nPadding ]->set( sMsg[ i ] );
	}
        for ( int i = nLen; i < m_pDisplay.size(); i++ ) {
            m_pDisplay[ i ]->set( ' ' );
        }
}


/*
void LCDDisplay::setSmallRed()
{
	for ( uint i = 0; i < m_pDisplay.size(); i++) {
		m_pDisplay[ i ]->setSmallRed();
	}
}

void LCDDisplay::setSmallBlue()
{
	for ( uint i = 0; i < m_pDisplay.size(); i++) {
		m_pDisplay[ i ]->setSmallBlue();
	}
}*/

void LCDDisplay::digitClicked( void )
{
	emit displayClicked( this );
}

void LCDDisplay::resizeEvent(QResizeEvent *ev)
{
    int nDigits = width()/height()*ratio + 2;
    //if (nDigits < m_pDisplay.size())
    //{
        for (int i = m_pDisplay.size(); i > nDigits; i-- ) {
            delete m_pDisplay[ i-1 ];
            m_pDisplay.pop_back();
        }
    //}
    bool a = false;
    for ( int n = m_pDisplay.size(); n < nDigits; n++ ) {
            LCDDigit *pDigit = new LCDDigit( this, imgfile );
            //pDigit->set(' ');
            connect( pDigit, SIGNAL( digitClicked() ), this, SLOT( digitClicked() ) );
            m_pDisplay.push_back( pDigit );
            a = true;
    }
    if (a) setText(m_sMsg);
    //int a = height();
    //int b = width();
    //double c = ratio;
    int h = height();
    int w = h/ratio;
    //double q = height()/ratio;
    //w = (int)q;
    LCDDigit* p;
    int b = m_pDisplay.size();
    for ( int i = 0; i<m_pDisplay.size(); i++) {
        p = m_pDisplay[i];

        p->resize(w, h);
        p->move(w*i, 0 );
        p->show();

    }
    //show();
}

// :::::::::::::::::::


/*
//// used in PlayerControl
//LCDSpinBox::LCDSpinBox( QWidget *pParent, int nDigits, LCDSpinBoxType type, int nMin, int nMax )
// : QWidget( pParent, "LCDSpinBox" )
// , Object( "LCDSpinBox" )
// , m_type( type )
// , m_fValue( 0 )
// , m_nMinValue( nMin )
// , m_nMaxValue( nMax )
//{
//	m_pDisplay = new LCDDisplay( this, LCDDigit::LARGE_GRAY, nDigits );
//	connect( m_pDisplay, SIGNAL( displayClicked(LCDDisplay*) ), this, SLOT( displayClicked(LCDDisplay*) ) );

//	resize( m_pDisplay->width(), m_pDisplay->height() );
//	setMinimumSize( width(), height() );
//	setMaximumSize( width(), height() );

////	string sUpBtn_on = Skin::getImagePath() + string( "/lcd/LCDSpinBox_up_on.png" );
////	string sUpBtn_off = Skin::getImagePath() + string( "/lcd/LCDSpinBox_up_off.png" );
////	string sUpBtn_over = Skin::getImagePath() + string( "/lcd/LCDSpinBox_up_over.png" );
////	string sUpBtn_off = sUpBtn_on;
////	string sUpBtn_over = sUpBtn_on;
////	string sDownBtn_on = Skin::getImagePath() + string( "/lcd/LCDSpinBox_down_on.png" );
////	string sDownBtn_off = Skin::getImagePath() + string( "/lcd/LCDSpinBox_down_off.png" );
////	string sDownBtn_over = Skin::getImagePath() + string( "/lcd/LCDSpinBox_down_over.png" );
////	string sDownBtn_on = sUpBtn_on;
////	string sDownBtn_off = sUpBtn_on;
////	string sDownBtn_over = sUpBtn_on;
////	m_pUpBtn = new Button( this, QSize( 10, 10 ), sUpBtn_on, sUpBtn_off, sUpBtn_over );
////	m_pUpBtn->move( m_pDisplay->width(), 0 );
////	connect( m_pUpBtn, SIGNAL( clicked(Button*) ), this, SLOT( upBtnClicked(Button*) ) );
////	m_pDownBtn = new Button( this, QSize( 10, 10 ), sDownBtn_on, sDownBtn_off, sDownBtn_over );
////	m_pDownBtn->move( m_pDisplay->width(),  10);
////	connect( m_pDownBtn, SIGNAL( clicked(Button*) ), this, SLOT( downBtnClicked(Button*) ) );

//	setValue( 0 );
//}



//LCDSpinBox::~LCDSpinBox()
//{
//	delete m_pDisplay;
////	delete m_pUpBtn;
////	delete m_pDownBtn;
//}


//void LCDSpinBox::upBtnClicked()
//{
//	switch( m_type ) {
//		case INTEGER:
//			if ( m_nMaxValue != -1 && m_fValue < m_nMaxValue ) {
//				setValue( m_fValue + 1);
//			}
//			break;
//		case FLOAT:
//			if ( m_nMaxValue != -1 && m_fValue < (float)m_nMaxValue ) {
//				setValue( m_fValue + 1.0);
//			}
//			break;
//	}

//	emit changed(this);
//}

//void LCDSpinBox::downBtnClicked()
//{
//	switch( m_type ) {
//		case INTEGER:
//			if ( m_nMinValue != -1 && m_fValue > m_nMinValue ) {
//				setValue( m_fValue -1);
//			}
//			break;
//		case FLOAT:
//			if ( m_nMinValue != -1 && m_fValue > m_nMinValue ) {
//				setValue( m_fValue - 1.0);
//			}
//			break;
//	}
//	emit changed(this);
//}


//void LCDSpinBox::setValue( float nValue )
//{
//	switch ( m_type ) {
//		case INTEGER:
//			if ( nValue != m_fValue ) {
//				m_fValue = (int)nValue;
//				m_pDisplay->setText( toString( m_fValue ) );
//			}
//			break;

//		case FLOAT:
//			if ( nValue != m_fValue ) {
//				m_fValue = nValue;
//				char tmp[20];
//				sprintf( tmp, "%#.2f", m_fValue );
//				m_pDisplay->setText( toString( tmp ) );
//			}
//			break;
//	}
//}

//void LCDSpinBox::displayClicked( LCDDisplay *pRef )
//{
//	emit spinboxClicked();
//}


//void LCDSpinBox::wheelEvent ( QWheelEvent *ev )
//{
//	ev->accept();

//	if ( ev->delta() > 0 ) {
//		switch( m_type ) {
//			case INTEGER:
//				setValue( m_fValue + 1);
//				break;
//			case FLOAT:
//				setValue( m_fValue + 1.0);
//				break;
//		}

//		emit changed(this);
//	}
//	else {
//		switch( m_type ) {
//			case INTEGER:
//				setValue( m_fValue -1);
//				break;
//			case FLOAT:
//				setValue( m_fValue - 1.0);
//				break;
//		}
//		emit changed(this);
//	}
//}
*/
