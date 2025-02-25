    #ifndef CREATEACCOUNT_H
    #define CREATEACCOUNT_H

    #include <QLabel>
    #include <QVBoxLayout>
    #include <QLineEdit>
    #include "page.h"

    class CreateAccount : public Page
    {
    public:
        explicit CreateAccount(QStackedWidget *parent = nullptr);
        void validateFields();

    private:
        void loadUi();
        QList<QLabel*> errorLabels;

        QLineEdit* createInputField(const QString &labelText, QVBoxLayout *layout, QFont *labelFont, int paramIndex, bool isPassword = false);
    };

    #endif // CREATEACCOUNT_H
