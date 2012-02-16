/*
    libKGoogle - Auth
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

#ifndef LIBKGOOGLE_AUTH_P_H_
#define LIBKGOOGLE_AUTH_P_H_

#include <qobject.h>

namespace KWallet {
  class Wallet;
}

class QNetworkReply;

namespace KGoogle {

  class Account;

  class Auth;

  /**
   * \internal
   */
  class AuthPrivate: public QObject
  {

    Q_OBJECT

    public:
      AuthPrivate(Auth* const parent);

      virtual ~AuthPrivate();

      QString kwalletFolder;
      KWallet::Wallet *kwallet;

      static KGoogle::Auth *instance;

    public Q_SLOTS:
      void fullAuthentication(KGoogle::Account *account, bool autoSave);
      void fullAuthenticationFinished(KGoogle::Account *account);

      void refreshTokens(KGoogle::Account *account, bool autoSave);
      void refreshTokensFinished(QNetworkReply *reply);

    private:
      Auth* const q_ptr;
      Q_DECLARE_PUBLIC(Auth)
  };

}

#endif /* LIBKGOOGLE_AUTH_P_H_ */