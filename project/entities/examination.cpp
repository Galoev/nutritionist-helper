#include "entities/examination.h"
#include <QDebug>

Client Examination::client() const
{
    return _client;
}

void Examination::setClient(Client client)
{
    _client = client;
}

bool Examination::isFullExamination() const
{
    return _isFullExamination;
}

void Examination::setIsFullExamination(bool isFullExamination)
{
    _isFullExamination = isFullExamination;
}

QDateTime Examination::date() const
{
    return _date;
}

void Examination::setDate(const QDateTime &date)
{
    _date = date;
}

void Examination::setFieldValue(QString fieldName, QString value)
{    
    for (int i = 0; i < _fields.size(); ++i){
        if (_fields[i].name() == fieldName) {
            _fields[i].setValue(value);
            return;
        }
    }

//    foreach (FormField& field, _fields) {
//        if (field.name() == fieldName) {
//            field.setValue(value);
//        }
//    }

    qDebug() << "Error: Examination::setFieldValue(QString , QString)"
             << "Doesn't contain fieldName ";
}

void Examination::initFields()
{
    _fields  = QVector<FormField>({
                                      { "formfield_1", FormField::UShort, "Пищевой анамнез 1 |  масса тела | колебания | мин." },
                                      { "formfield_2", FormField::UShort, "Пищевой анамнез 1 |  масса тела | колебания | макс." },
                                      { "formfield_3", FormField::UShort, "Пищевой анамнез 1 |  масса тела | в 20 лет" },
                                      { "formfield_4", FormField::UShort, "Пищевой анамнез 1 |  масса тела | комфортная" },
                                      { "formfield_5", FormField::ComboB, "Пищевой анамнез 1 |  масса тела | период времени" },
                                      { "formfield_6", FormField::String, "Пищевой анамнез 1 |  масса тела | причины набора " },
                                      { "formfield_7", FormField::ComboB, "Пищевой анамнез 1 | изменения питания | постепенно" },
                                      { "formfield_8", FormField::String, "Пищевой анамнез 1 | изменения питания | диеты" },
                                      { "formfield_9", FormField::String, "Пищевой анамнез 1 | изменения питания | голодание" },
                                      { "formfield_10", FormField::ComboB, "Пищевой анамнез 1 | состояние  | аппетита" },
                                      { "formfield_11", FormField::ComboB, "Пищевой анамнез 1 | состояние  | голода" },
                                      { "formfield_12", FormField::ComboB, "Пищевой анамнез 1 | состояние  | насыщения" },
                                      { "formfield_13", FormField::String, "Пищевой анамнез 2 | применение пищевых добавок и лекарств" },
                                      { "formfield_14", FormField::String, "Пищевой анамнез 2 | характер питания" },
                                      { "formfield_15", FormField::String, "Пищевой анамнез 2 | пищевые привычки" },
                                      { "formfield_16", FormField::String, "Пищевой анамнез 2 | переносимость продуктов" },
                                      { "formfield_17", FormField::ComboB, "Пищевой анамнез 2 | оценка | суточного рациона питания" },
                                      { "formfield_18", FormField::ComboB, "Пищевой анамнез 2 | оценка | пищевого дневника", true },
                                      { "formfield_19", FormField::ComboB, "Пищевой анамнез 2 | оценка | двигательной активности" },
                                      { "formfield_20", FormField::String, "Анамнез жизни | жалобы в настоящее время" },
                                      { "formfield_21", FormField::String, "Анамнез жизни | перенесенные заболевания" },
                                      { "formfield_22", FormField::String, "Анамнез жизни | хронические заболевания" },
                                      { "formfield_23", FormField::String, "Анамнез жизни | вредные привычки" },
                                      { "formfield_24", FormField::String, "Анамнез жизни | отягощенная наследственность" },
                                      { "formfield_25", FormField::String, "Анамнез жизни | аллергический фон" },
                                      { "formfield_26", FormField::String, "Анамнез жизни | гормональный фон" },
                                      { "formfield_27", FormField::UShort, "Анамнез жизни | дети", true },
                                      { "formfield_28", FormField::ComboB, "Анамнез жизни | семейное положение", true },
                                      { "formfield_29", FormField::Date, "Гинекологический и акушерский анамнез | менструальный цикл | дата последней", true },
                                      { "formfield_30", FormField::UShort, "Гинекологический и акушерский анамнез | менструальный цикл | длительность", true },
                                      { "formfield_31", FormField::UShort, "Гинекологический и акушерский анамнез | менструальный цикл | периодичность", true },
                                      { "formfield_32", FormField::ComboB, "Гинекологический и акушерский анамнез | менструальный цикл | болезненность", true },
                                      { "formfield_33", FormField::UShort, "Гинекологический и акушерский анамнез | менопауза | год", true },
                                      { "formfield_34", FormField::String, "Гинекологический и акушерский анамнез | менопауза | характер", true },
                                      { "formfield_35", FormField::UShort, "Гинекологический и акушерский анамнез | беременности", true },
                                      { "formfield_36", FormField::UShort, "Гинекологический и акушерский анамнез | роды", true },
                                      { "formfield_37", FormField::String, "Физикальный осмотр | кожа и подкожножировая клетчатка" },
                                      { "formfield_38", FormField::String, "Физикальный осмотр | дипигментация" },
                                      { "formfield_39", FormField::String, "Физикальный осмотр | волосы" },
                                      { "formfield_40", FormField::String, "Физикальный осмотр | отеки" },
                                      { "formfield_41", FormField::String, "Физикальный осмотр | мышечный слой" },
                                      { "formfield_42", FormField::Float, "Антропометрия | окружности | шея", true },
                                      { "formfield_43", FormField::Float, "Антропометрия | окружности | грудной клетки", true },
                                      { "formfield_44", FormField::Float, "Антропометрия | окружности | талии" },
                                      { "formfield_45", FormField::Float, "Антропометрия | окружности | бедер" },
                                      { "formfield_46", FormField::Float, "Антропометрия | динна тела" },
                                      { "formfield_47", FormField::Float, "Антропометрия | масса тала" },
                                      { "formfield_48", FormField::Float, "Антропометрия | плечо | верхняя треть", true },
                                      { "formfield_49", FormField::Float, "Антропометрия | плечо | средняя треть", true },
                                      { "formfield_50", FormField::Float, "Антропометрия | предплечье | средняя треть", true },
                                      { "formfield_51", FormField::Float, "Антропометрия | предплечье | нижняя треть" },
                                      { "formfield_52", FormField::Float, "Антропометрия | бедро | верхняя треть", true },
                                      { "formfield_53", FormField::Float, "Антропометрия | бедро | средняя треть", true },
                                      { "formfield_54", FormField::Float, "Антропометрия | голень | средняя треть", true },
                                      { "formfield_55", FormField::Float, "Антропометрия | голень | нижняя треть", true },
                                      { "formfield_56", FormField::UShort, "Физиометрия 1 | проба мартине-кушелевского | систолическое  | в покое", true },
                                      { "formfield_57", FormField::UShort, "Физиометрия 1 | проба мартине-кушелевского | систолическое  | после нагрузки", true },
                                      { "formfield_58", FormField::UShort, "Физиометрия 1 | проба мартине-кушелевского | диастолическое | в покое", true },
                                      { "formfield_59", FormField::UShort, "Физиометрия 1 | проба мартине-кушелевского | диастолическое | после нагрузки", true },
                                      { "formfield_60", FormField::UShort, "Физиометрия 1 | проба мартине-кушелевского | пульсовое | в покое", true },
                                      { "formfield_61", FormField::UShort, "Физиометрия 1 | проба мартине-кушелевского | пульсовое | после нагрузки", true },
                                      { "formfield_62", FormField::UShort, "Физиометрия 1 | проба мартине-кушелевского | чсс | в покое", true },
                                      { "formfield_63", FormField::UShort, "Физиометрия 1 | проба мартине-кушелевского | чсс | после нагрузки", true },
                                      { "formfield_64", FormField::UShort, "Физиометрия 1 | проба мартине-кушелевского | реституция", true },
                                      { "formfield_65", FormField::String, "Физиометрия 1 | проба мартине-кушелевского | резульат пробы", true },
                                      { "formfield_66", FormField::Float, "Физиометрия 1 | динамометрия | правой", true },
                                      { "formfield_67", FormField::Float, "Физиометрия 1 | динамометрия | левой", true },
                                      { "formfield_68", FormField::Float, "Физиометрия 1 | спирометрия (ЖЕЛ)", true },
                                      { "formfield_69", FormField::String, "Физиометрия 2 | показатели | индексы | массы тела" },
                                      { "formfield_70", FormField::String, "Физиометрия 2 | показатели | индексы | Руфье", true },
                                      { "formfield_71", FormField::String, "Физиометрия 2 | показатели | индексы | ОТ/ОБ" },
                                      { "formfield_72", FormField::String, "Физиометрия 2 | показатели | индексы | силовой", true },
                                      { "formfield_73", FormField::String, "Физиометрия 2 | показатели | индексы | жизненный", true },
                                      { "formfield_74", FormField::String, "Физиометрия 2 | показатели | индексы | Робинсона", true },
                                      { "formfield_75", FormField::String, "Физиометрия 2 | показатели | рекомедуемой массы тела", true },
                                      { "formfield_76", FormField::String, "Физиометрия 2 | показатели | уровень физического здоровья", true },
                                      { "formfield_77", FormField::String, "Физиометрия 2 | показатели | адаптационный потенциал", true },
                                      { "formfield_78", FormField::Float, "Физиометрия 2 | биохимические показатели | глюкоза" },
                                      { "formfield_79", FormField::Float, "Физиометрия 2 | биохимические показатели | холестерин" },
                                      { "formfield_80", FormField::Float, "Физиометрия 2 | биохимические показатели | общий белок", true },
                                      { "formfield_81", FormField::Float, "Физиометрия 2 | биохимические показатели | креатин", true },
                                      { "formfield_82", FormField::Float, "Физиометрия 2 | биохимические показатели | мочевая кислота", true },
                                      { "formfield_83", FormField::Float, "Физиометрия 2 | биохимические показатели | лептин", true },
                                      { "formfield_84", FormField::String, "Физиометрия 2 | биохимические показатели | дополнительные", true },
                                      { "formfield_85", FormField::ComboB, "Заключение | нутриционный статус" },
                                      { "formfield_86", FormField::ComboB, "Заключение | маетаболический синдром" },
                                      { "formfield_87", FormField::ComboB, "Заключение | масса тела" },
                                      { "formfield_88", FormField::ComboB, "Заключение | ожирение | тип" },
                                      { "formfield_89", FormField::ComboB, "Заключение | ожирение | абдоминальное" },
                                      { "formfield_90", FormField::String, "Заключение | дополнительно" },

                                  });
}

FormField Examination::field(QString fieldName)
{
    for (int i = 0; i < _fields.size(); ++i){
        if (_fields[i].name() == fieldName) {
            return _fields[i];
        }
    }

//    foreach (FormField field, _fields) {
//        if (field.name() == fieldName) {
//            return field;
//        }
//    }

    return FormField();
}

QVector<FormField> Examination::fields()
{
    return _fields;
}


Examination::Examination()
{
    initFields();
}

int Examination::id() const
{
    return _id;
}

void Examination::setId(int id)
{
    _id = id;
}

FormField::FormField(QString name, Type type, QString interpretation
                     , bool isMayBeEmpty)
        : _name(name), _type(type), _interpretation(interpretation)
        , _isMayBeEmpty(isMayBeEmpty)
{
    _notInit = false;
}

bool FormField::isMayBeEmpty() const
{
    return _isMayBeEmpty;
}

FormField::Type FormField::type() const
{
    return _type;
}

QString FormField::interpretation() const
{
    return _interpretation;
}

void FormField::setValue(const QString &value)
{
    _value = value;
}

QString FormField::value() const
{
    return _value;
}

QString FormField::name() const
{
    return _name;
}

