/***** BEGIN LICENSE BLOCK *****

BSD License

Copyright (c) 2005, NIF File Format Library and Tools
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:
1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.
3. The name of the NIF File Format Library and Tools projectmay not be
   used to endorse or promote products derived from this software
   without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

***** END LICENCE BLOCK *****/

#ifndef UVEDIT_H
#define UVEDIT_H

#include <QtOpenGL>
#include <QVector>

class NifModel;
class QModelIndex;
class QString;
class TexCache;
class Vector2;

class UVWidget : public QGLWidget
{
	Q_OBJECT
public:
	UVWidget( QWidget * parent = 0 );
	~UVWidget();

	bool setNifData( NifModel * nif, const QModelIndex & index );
			
	QSize sizeHint() const;
	QSize minimumSizeHint() const;
	
	void setSizeHint( const QSize & s );
	
	int heightForWidth( int width ) const;
	
protected:
	void initializeGL();
	void resizeGL( int width, int height );
	void paintGL();

	void mousePressEvent( QMouseEvent * e );
	void mouseReleaseEvent( QMouseEvent * e );
	void mouseMoveEvent( QMouseEvent * e );
	void wheelEvent( QWheelEvent * e );

private:
	enum {
		NoneSel, TexCoordSel, FaceSel
	} selectedType;

	int selectedTexCoord;
	int selectedFace;
	int selectCycle;

	struct face {
		int t[3];
	};

	QVector< Vector2 > texcoords;
	QVector< face > faces;
	
	QSize sHint;

	TexCache * textures;
	QString texfile;

	void drawTexCoords();

	void setupViewport( int width, int height );
	void updateViewRect( int width, int height );
	bool bindTexture( const QString & filename );

	int indexAt( const QPoint & hitPos );

	void updateNif();

	NifModel * nif;
	QModelIndex idx, iTexCoords;

	GLdouble glViewRect[4];

	QPoint pos;

	QPoint mousePos;

	GLdouble zoom;
};

#endif
