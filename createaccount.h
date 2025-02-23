    #ifndef CREATEACCOUNT_H
    #define CREATEACCOUNT_H

    #include <QLabel>

    #include "page.h"

    class CreateAccount : public Page
    {
    public:
        explicit CreateAccount(QStackedWidget *parent = nullptr);

    private:
        void loadUi();
        QLabel *passwordErrorLabel;       // Pointer declaration
        QLabel *confirmPasswordErrorLabel;
        void passwordFieldChanged(const QString &password);//, const QLabel &passwordLabel);
        void reEnterPasswordFieldChanged(const QString &passwordAgain);//, const QLabel &passwordAgainLabel);
    };

    #endif // CREATEACCOUNT_H
