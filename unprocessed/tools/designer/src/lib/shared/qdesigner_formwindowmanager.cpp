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

#include "qdesigner_formwindowmanager_p.h"
#include "plugindialog_p.h"

#include <QtDesigner/QDesignerFormEditorInterface>

QT_BEGIN_NAMESPACE

using namespace qdesigner_internal;

/*!
    \class QDesignerFormWindowManager

    Extends QDesignerFormWindowManagerInterface with methods to control
    the preview and printing of forms. It provides a facade that simplifies
    the complexity of the more general PreviewConfiguration & PreviewManager
    interfaces.

    \since 4.5
  */


QDesignerFormWindowManager::QDesignerFormWindowManager(QObject *parent)
    : QDesignerFormWindowManagerInterface(parent), m_unused(0)
{
}

QDesignerFormWindowManager::~QDesignerFormWindowManager()
{
}

/*!
    Allows you to intervene and control \QD's form "Preview" action. The
    function returns the original action.

    \since 4.5
  */
QAction *QDesignerFormWindowManager::actionDefaultPreview() const
{
    return 0;
}

/*!
    Allows you to intervene and control \QD's form "Preview in" style action. The
    function returns the original list of actions.

    The method calls PreviewManager::createStyleActionGroup() internally.

    \since 4.5
  */
QActionGroup *QDesignerFormWindowManager::actionGroupPreviewInStyle() const
{
    return 0;
}

/*!
    \fn QPixmap QDesignerFormWindowManager::createPreviewPixmap(QString *errorMessage)

    Creates a pixmap representing the preview of the currently active form.

    The method calls PreviewManager::createPreviewPixmap() internally.

    \since 4.5
  */


/*!
    \fn QPixmap QDesignerFormWindowManager::closeAllPreviews()

    Closes all preview windows generated by actionDefaultPreview, actionGroupPreviewInStyle
    and the corresponding methods in PreviewManager.

    \since 4.5
  */

/*!
    \fn PreviewManager *QDesignerFormWindowManager::previewManager()

    Accesses the previewmanager implementation.

    \since 4.5
    \internal
  */

/*!
    \fn QAction *QDesignerFormWindowManager::actionShowFormWindowSettingsDialog() const;

    Allows you to intervene and control \QD's form "Form Settings" action. The
    function returns the original action.

    \since 4.5
    \internal
  */

QAction *QDesignerFormWindowManager::actionShowFormWindowSettingsDialog() const
{
    return 0;
}

/*!
    \fn void QDesignerFormWindowManager::aboutPlugins()

    Pops up an "About plugins" dialog.

    \since 4.5
    \internal
  */

void QDesignerFormWindowManager::aboutPlugins()
{
    PluginDialog dlg(core(), core()->topLevel());
    dlg.exec();
}

/*!
    \fn
    void QDesignerFormWindowManager::formWindowSettingsChanged(QDesignerFormWindowInterface *fw);

    This signal is emitted when the form settings dialog was shown
    and changes have been made to the form.

    \since 4.5
    \internal
  */


QT_END_NAMESPACE
