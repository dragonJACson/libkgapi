/*
    libKGoogle - Ui - AccountsCombo
    Copyright (C) 2011  Dan Vratil <dan@progdan.cz>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef LIBKGOOGLE_UI_ACCOUNTSCOMBO_H
#define LIBKGOOGLE_UI_ACCOUNTSCOMBO_H

#include <qcombobox.h>
#include <qstandarditemmodel.h>

#include <libkgoogle/libkgoogle_export.h>

namespace KGoogle
{

  class Account;

  namespace Ui
  {

    class LIBKGOOGLE_EXPORT AccountsCombo : public QComboBox
    {
        Q_OBJECT

      public:
        enum ItemRoles
        {
          AccountDataRole = Qt::UserRole + 1
        };

        explicit AccountsCombo (QWidget *parent = 0);

        virtual ~AccountsCombo();

        KGoogle::Account* currentAccount() const;

      public Q_SLOTS:
        void reload();

      private:
        void initModel (QStandardItemModel *model);
    };

  }

}

#endif // KGOOGLE_UI_ACCOUNTSTREEVIEW_H