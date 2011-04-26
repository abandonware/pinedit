//Added by qt3to4:
#include <Q3BoxLayout>
#include <Q3VBoxLayout>
/***************************************************************************
                          snapdialog.cpp  -  description
                             -------------------
    begin                : Thu Jul 11 19:39:03 EET 2002
    copyright            : (C) 2002 by Henrik Enqvist
    email                : henqvist@excite.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

using namespace std;

// general includes
#include <iostream>
// qt includes
#include <q3textbrowser.h>
#include <qlayout.h>
// application includes
#include "textdialog.h"
// emilia includes
#include "Private.h"

TextDialog::TextDialog(QWidget * parent, const char * name, Qt::WFlags f) : QDialog(parent, name, f) {
  p_TextBrowser = new Q3TextBrowser(this);
  p_TextBrowser->setMinimumSize(600,600);
  Q3BoxLayout * layout = new Q3VBoxLayout(this);
  layout->addWidget(p_TextBrowser);
}

TextDialog::~TextDialog() {
}

void TextDialog::setSource(const QString & name) {
  p_TextBrowser->setSource(name);
}	

void TextDialog::slotBack() {
  EM_CERR("TextDialog::slotBack");
}

void TextDialog::slotCancel() {
  this->done(0);
  EM_CERR("TextDialog::slotCancel");
}
