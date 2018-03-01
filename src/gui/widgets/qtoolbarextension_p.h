/***********************************************************************
*
* Copyright (c) 2012-2018 Barbara Geller
* Copyright (c) 2012-2018 Ansel Sermersheim
* Copyright (c) 2012-2016 Digia Plc and/or its subsidiary(-ies).
* Copyright (c) 2008-2012 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
*
* This file is part of CopperSpice.
*
* CopperSpice is free software. You can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public License
* version 2.1 as published by the Free Software Foundation.
*
* CopperSpice is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*
* <http://www.gnu.org/licenses/>.
*
***********************************************************************/

#ifndef QToolBarExtension_P_H
#define QToolBarExtension_P_H

#include <QtGui/qtoolbutton.h>

QT_BEGIN_NAMESPACE

#ifndef QT_NO_TOOLBUTTON

class QToolBarExtension : public QToolButton
{
   GUI_CS_OBJECT(QToolBarExtension)
   Qt::Orientation orientation;

 public:
   explicit QToolBarExtension(QWidget *parent);

   void paintEvent(QPaintEvent *) override;
   QSize sizeHint() const override;

   GUI_CS_SLOT_1(Public, void setOrientation(Qt::Orientation o))
   GUI_CS_SLOT_2(setOrientation)
};

#endif // QT_NO_TOOLBUTTON

QT_END_NAMESPACE

#endif // QDYNAMICTOOLBAREXTENSION_P_H
