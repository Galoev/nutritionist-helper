#include "ClientEdit.h"
#include <QMessageBox>
#include <QDebug>

#include <QRegExpValidator>

ClientEdit::ClientEdit(QWidget* wgt)
    :QWidget(wgt)
{
    _ui.setupUi(this);

    _ui.lineEdit_name->setValidator(new QRegExpValidator(QRegExp("[\\w]+")));
    _ui.lineEdit_surname->setValidator(new QRegExpValidator(QRegExp("[\\w]+")));
    _ui.lineEdit_patronymic->setValidator(new QRegExpValidator(QRegExp("[\\w]+")));
    _ui.lineEdit_birthdayYear->setValidator(new QIntValidator(1000, 9999));
    _ui.lineEdit_telNumber->setValidator(new QRegExpValidator(QRegExp("\\d{10}")));

    connect(_ui.pushButton_save, SIGNAL(pressed()), SLOT(onPushButtonSave()));
    connect(_ui.pushButton_cancel, SIGNAL(pressed()), SLOT(onPushButtonCancel()));
}

void ClientEdit::setInformation(const Client &c)
{
    _isEditingMod = true;

    _client.setId(c.id());

    _ui.lineEdit_name->setText(c.name());
    _ui.lineEdit_surname->setText(c.surname());
    _ui.lineEdit_patronymic->setText(c.patronymic());
    _ui.lineEdit_birthdayYear->setText(QString::number(c.birthDate().year()));
    _ui.radioButton_genderM->setChecked(c.gender() == 'm');
    _ui.radioButton_genderF->setChecked(c.gender() == 'f');
    _ui.lineEdit_telNumber->setText(c.telNumber());

    this->repaint();
}

void ClientEdit::onPushButtonSave()
{
    QString errorLog;

    if (!_ui.lineEdit_surname->hasAcceptableInput()) {
        errorLog += tr("Неправильный формат Фамилии\n");
    }
    if (!_ui.lineEdit_name->hasAcceptableInput()) {
        errorLog += tr("Неправильный формат Имени\n");
    }
    if (!_ui.lineEdit_surname->hasAcceptableInput()) {
        errorLog += tr("Неправильный формат Имени\n");
    }
    if (!_ui.lineEdit_birthdayYear->hasAcceptableInput()) {
        errorLog += tr("Неправильный формат Даты рождения\n");
    }
    if (!_ui.lineEdit_telNumber->hasAcceptableInput()) {
        errorLog += tr("Неправильный формат Номера телефона\n");
    }
    if(!_ui.radioButton_genderF->isChecked() && !_ui.radioButton_genderM->isChecked()) {
        errorLog += tr("Пол не установлен\n");
    }

    if (!errorLog.isEmpty()){
        QMessageBox::critical(this, tr("Ошибка заполнения"), errorLog);
        return;
    }

    QString name = _ui.lineEdit_name->text();
    QString surname = _ui.lineEdit_surname->text();
    QString patronymic = _ui.lineEdit_patronymic->text();
    QDate birthday = QDate(_ui.lineEdit_birthdayYear->text().toInt(), 1, 1);
    QChar gender = (_ui.radioButton_genderM->isChecked() ? 'm' : 'f');
    QString telNumber = _ui.lineEdit_telNumber->text();
    short age = QDate::currentDate().year() - birthday.year();

    _client = Client(_client.id(), name, surname, patronymic, birthday, gender, age, telNumber);

    if (_isEditingMod) {
        emit formEditedClientReady();
    } else {
        emit formNewClientReady();
    }

    this->close();
}

void ClientEdit::onPushButtonCancel()
{
    this->parent()->deleteLater();
}

Client ClientEdit::client() const
{
    return _client;
}

