#include "printer.h"

#include <QPrintDialog>
#include <QPainter>
#include <QDebug>
#include <QTextDocument>


Printer::Printer(QWidget *wgt)
    : QWidget(wgt)
{
    _printer = new QPrinter(QPrinter::HighResolution);
    _printer->setOrientation(QPrinter::Portrait);
    _printer->setPageMargins(QMarginsF(10, 10, 10, 10), QPageLayout::Millimeter);
    _printer->setPaperSize(QPrinter::A4);
    _printer->setDocName(tr("Отчет по исследованию"));
}

Printer::~Printer()
{
    delete _printer;
}

void Printer::previewExamination(const Examination& exm, bool isFR)
{
    _exm = exm;
    _isFullReport = isFR;

    QPrintPreviewDialog* dialog = new QPrintPreviewDialog(_printer, this);
    dialog->setWindowFlags(Qt::Window);
   //dialog->setWindowState(Qt::WindowMaximized);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->setWindowTitle(tr("Просмотр исследования"));
    connect(dialog, SIGNAL(paintRequested(QPrinter*)), SLOT(previewPageExamination(QPrinter*)));
    dialog->exec();
}

void Printer::previewPageExamination(QPrinter *printer)
{
    QTextDocument document;
    document.setDefaultFont(QFont("Times New Roman"));
    _cursor = QTextCursor(&document);

    if (_isFullReport){
        drawFullExamination();
    } else {
        drawHalfExamination();
    }

    document.print(printer);
}

void Printer::drawHalfExamination()
{
    drawDocumentTitle(tr("Консультация Нутрициолога-диетолога:"));

    drawParagraph(tr("Фамилия: %1\nИмя: %2\nОтчество: %3\nВозраст: %4 (%5)")
                  .arg(_exm.client().surname())
                  .arg(_exm.client().name())
                  .arg(_exm.client().patronymic())
                  .arg(_exm.client().age())
                  .arg(_exm.client().birthDate().year())
                  );

    drawParagraphTitle(tr("Пищевой анамнез"));

    drawParagraph(tr("Колебания массы тела с %1 до %2 кг постепенно: %3 за период %4, при этом комфортная %5 кг, в 20 лет %6 кг")
                  .arg(_exm.field("formfield_1").value())
                  .arg(_exm.field("formfield_2").value())
                  .arg(_exm.field("formfield_7").value())
                  .arg(_exm.field("formfield_5").value())
                  .arg(_exm.field("formfield_4").value())
                  .arg(_exm.field("formfield_3").value())
                  );
    drawParagraph(tr("Наличие аппетита: %1, чувства голода: %2, насыщения: %3")
                  .arg(_exm.field("formfield_10").value())
                  .arg(_exm.field("formfield_11").value())
                  .arg(_exm.field("formfield_12").value())
                  );
    drawParagraph(tr("Причины набора массы тела: %1")
                  .arg(_exm.field("formfield_6").value())
                  );
    drawParagraph(tr("Изменение питания происходило постепенно: %1, использовались диеты: %2, голодание: %3, применялись пищевые добавки, лекарственные препараты: %4")
                  .arg(_exm.field("formfield_7").value())
                  .arg(_exm.field("formfield_8").value())
                  .arg(_exm.field("formfield_9").value())
                  .arg(_exm.field("formfield_13").value())
                  );
    drawParagraph(tr("Характер питания: %1 пищевые привычки: %2 переносимость продуктов: %3")
                  .arg(_exm.field("formfield_14").value())
                  .arg(_exm.field("formfield_15").value())
                  .arg(_exm.field("formfield_16").value())
                  );
    drawParagraph(tr("Суточный рацион питания оценивается как: %1, двигательная активность: %2")
                  .arg(_exm.field("formfield_17").value())
                  .arg(_exm.field("formfield_19").value())
                  );

    drawParagraphTitle(tr("Анамнез жизни"));

    drawParagraph(tr("Жалобы в настоящий момент: %1, перенесенные заболевания: %2, хронические заболевания: %3, вредные привычки %4")
                  .arg(_exm.field("formfield_20").value())
                  .arg(_exm.field("formfield_21").value())
                  .arg(_exm.field("formfield_22").value())
                  .arg(_exm.field("formfield_23").value())
                  );
    drawParagraph(tr("Аллергический фон: %3, гормональный фон: %4 ")
                  .arg(_exm.field("formfield_25").value())
                  .arg(_exm.field("formfield_26").value())
                  );

    drawParagraphTitle(tr("Физикальный осмотр"));

    drawParagraph(tr("Кожа и подкожно жировая клетчатка: %1, волосы: %2, депигментация: %3, отеки: %4, мышечный слой: %5")
                  .arg(_exm.field("formfield_37").value())
                  .arg(_exm.field("formfield_39").value())
                  .arg(_exm.field("formfield_38").value())
                  .arg(_exm.field("formfield_40").value())
                  .arg(_exm.field("formfield_41").value())
                  );

    drawParagraphTitle(tr("Антропометрия"));

    drawParagraph(tr("Длина тела %1 см, масса тела %2 кг, индекс массы тела %3 кг/м2, рекомендуемая масса тела %4 кг")
                  .arg(_exm.field("formfield_46").value())
                  .arg(_exm.field("formfield_47").value())
                  .arg(_exm.field("formfield_69").value())
                  .arg(_exm.field("formfield_75").value())
                  );
    drawParagraph(tr("Окружность талии %1, тазового пояса %2 см, соотношение %3, окружность запястья %4 см")
                  .arg(_exm.field("formfield_44").value())
                  .arg(_exm.field("formfield_45").value())
                  .arg(_exm.field("formfield_71").value())
                  .arg(_exm.field("formfield_51").value())
                  );

    drawParagraphTitle(tr("Биохимические показатели"));

    drawParagraph(tr("Глюкоза: %1, холестерин: %2.")
                  .arg(_exm.field("formfield_78").value())
                  .arg(_exm.field("formfield_79").value())
                  );

    drawParagraphTitle(tr("Заключение"));

    drawParagraph(tr("Нутриционный статус: %1, масса тела: %2, ожирение: %3 степени, метаболический синдром: %4.")
                  .arg(_exm.field("formfield_85").value())
                  .arg(_exm.field("formfield_87").value())
                  .arg(_exm.field("formfield_88").value())
                  .arg(_exm.field("formfield_86").value())
                  );
    drawParagraph(tr("Дополнительно: %1")
                  .arg(_exm.field("formfield_90").value())
                  );
}

void Printer::drawFullExamination()
{
    drawDocumentTitle(tr("Консультация Нутрициолога-диетолога:"));
    drawParagraph(tr("Фамилия: %1\nИмя: %2\nОтчество: %3\nВозраст: %4 (%5)")
                  .arg(_exm.client().surname())
                  .arg(_exm.client().name())
                  .arg(_exm.client().patronymic())
                  .arg(_exm.client().age())
                  .arg(_exm.client().birthDate().year())
                  );

    drawParagraphTitle(tr("Пищевой анамнез"));
    drawParagraph(tr("Колебания массы тела с %1 до %2 кг постепенно: %3 за период %4, при этом комфортная %5 кг, в 20 лет %6 кг")
                  .arg(_exm.field("formfield_1").value())
                  .arg(_exm.field("formfield_2").value())
                  .arg(_exm.field("formfield_7").value())
                  .arg(_exm.field("formfield_5").value())
                  .arg(_exm.field("formfield_4").value())
                  .arg(_exm.field("formfield_3").value())
                  );
    drawParagraph(tr("Наличие аппетита: %1, чувства голода: %2, насыщения: %3")
                  .arg(_exm.field("formfield_10").value())
                  .arg(_exm.field("formfield_11").value())
                  .arg(_exm.field("formfield_12").value())
                  );
    drawParagraph(tr("Причины набора массы тела: %1")
                  .arg(_exm.field("formfield_6").value())
                  );
    drawParagraph(tr("Изменение питания происходило постепенно: %1, использовались диеты: %2, голодание: %3, применялись пищевые добавки, лекарственные препараты: %4")
                  .arg(_exm.field("formfield_7").value())
                  .arg(_exm.field("formfield_8").value())
                  .arg(_exm.field("formfield_9").value())
                  .arg(_exm.field("formfield_13").value())
                  );
    drawParagraph(tr("Характер питания: %1 пищевые привычки: %2 переносимость продуктов: %3")
                  .arg(_exm.field("formfield_14").value())
                  .arg(_exm.field("formfield_15").value())
                  .arg(_exm.field("formfield_16").value())
                  );
    drawParagraph(tr("Суточный рацион питания оценивается как: %1, пищевой дневник: %2, двигательная активность: %3")
                  .arg(_exm.field("formfield_17").value())
                  .arg(_exm.field("formfield_18").value())
                  .arg(_exm.field("formfield_19").value())
                  );

    drawParagraphTitle(tr("Анамнез жизни"));
    drawParagraph(tr("Жалобы в настоящий момент: %1, перенесенные заболевания: %2, хронические заболевания: %3, вредные привычки %4")
                  .arg(_exm.field("formfield_20").value())
                  .arg(_exm.field("formfield_21").value())
                  .arg(_exm.field("formfield_22").value())
                  .arg(_exm.field("formfield_23").value())
                  );
    drawParagraph(tr("Семейное положение: %1, наследственность отягощена: (дети: %2),  аллергический фон: %3, гормональный фон: %4 ")
                  .arg(_exm.field("formfield_28").value())
                  .arg(_exm.field("formfield_27").value())
                  .arg(_exm.field("formfield_25").value())
                  .arg(_exm.field("formfield_26").value())
                  );

    if(_exm.client().gender() == 'f'){
        drawParagraphTitle(tr("Гинекологический и акушерский анамнез "));
        drawParagraph(tr("Детей: %1, беременностей: %2, родов: %3 ")
                      .arg(_exm.field("formfield_27").value())
                      .arg(_exm.field("formfield_35").value())
                      .arg(_exm.field("formfield_36").value())
                      );
        drawParagraph(tr("Менструальный цикл: длится %1 дней, периодичность %2, дата последней %3, безболезненный %4. Менопауза наступила в %5 году, характер %6")
                      .arg(_exm.field("formfield_30").value())
                      .arg(_exm.field("formfield_31").value())
                      .arg(_exm.field("formfield_29").value())
                      .arg(_exm.field("formfield_32").value())
                      .arg(_exm.field("formfield_33").value())
                      .arg(_exm.field("formfield_36").value())
                      );
    }

    drawParagraphTitle(tr("Физикальный осмотр"));
    drawParagraph(tr("Кожа и подкожно жировая клетчатка: %1, волосы: %2, депигментация: %3, отеки: %4, мышечный слой: %5")
                  .arg(_exm.field("formfield_37").value())
                  .arg(_exm.field("formfield_39").value())
                  .arg(_exm.field("formfield_38").value())
                  .arg(_exm.field("formfield_40").value())
                  .arg(_exm.field("formfield_41").value())
                  );

    drawParagraphTitle(tr("Антропометрия"));
    drawParagraph(tr("Длина тела: %1 см. Масса тела %2 кг. Индекс массы тела: %3 кг/м2.")
                  .arg(_exm.field("formfield_46").value())
                  .arg(_exm.field("formfield_47").value())
                  .arg(_exm.field("formfield_69").value())
                  );
    drawParagraph(tr("Окружность: шеи: %1 см, грудной клетки: %2 см, талии: %3 см, тазового пояса: %4 см, плеча: %5/%6 см, предплечья: %7/%8 см, бедра: %9/%10 см, голени: %11/%12 см ")
                  .arg(_exm.field("formfield_42").value())
                  .arg(_exm.field("formfield_43").value())
                  .arg(_exm.field("formfield_44").value())
                  .arg(_exm.field("formfield_45").value())
                  .arg(_exm.field("formfield_48").value())
                  .arg(_exm.field("formfield_49").value())
                  .arg(_exm.field("formfield_50").value())
                  .arg(_exm.field("formfield_51").value())
                  .arg(_exm.field("formfield_52").value())
                  .arg(_exm.field("formfield_53").value())
                  .arg(_exm.field("formfield_54").value())
                  .arg(_exm.field("formfield_55").value())
                  );

    drawParagraphTitle(tr("Физиометрия"));
    drawParagraph(tr("Динамометрия правой: %1 левой: %2 кг. Силовой индекс: %3")
                  .arg(_exm.field("formfield_66").value())
                  .arg(_exm.field("formfield_67").value())
                  .arg(_exm.field("formfield_72").value())
                  );
    drawParagraph(tr("ЖЕЛ: %1 мл. Жизненный индекс: %2")
                  .arg(_exm.field("formfield_68").value())
                  .arg(_exm.field("formfield_72").value())
                  );
    drawParagraph(tr("ЧСС в покое: %1 уд/мин, после нагрузки: %2 уд/мин")
                  .arg(_exm.field("formfield_62").value())
                  .arg(_exm.field("formfield_63").value())
                  );
    drawParagraph(tr("АД в покое: %1/%2 мм.рт.ст., после нагрузки: %3/%4 мм.рт.ст.")
                  .arg(_exm.field("formfield_56").value())
                  .arg(_exm.field("formfield_58").value())
                  .arg(_exm.field("formfield_57").value())
                  .arg(_exm.field("formfield_59").value())
                  );
    drawParagraph(tr("Реституция: %1 сек.")
                  .arg(_exm.field("formfield_63").value())
                  );
    drawParagraph(tr("Результаты пробы  Мартинэ-Кушелеского: %1, индекса Руфье: %2, Робинсона: %3")
                  .arg(_exm.field("formfield_65").value())
                  .arg(_exm.field("formfield_70").value())
                  .arg(_exm.field("formfield_74").value())
                  );
    drawParagraph(tr("Рекомендуемая масса тела: %1 кг")
                  .arg(_exm.field("formfield_75").value())
                  );
    drawParagraph(tr("Уровень физического здоровья: %1, адаптационного потенциала: %2.")
                  .arg(_exm.field("formfield_76").value())
                  .arg(_exm.field("formfield_77").value())
                  );

    drawParagraphTitle(tr("Биохимические показатели"));
    drawParagraph(tr("Глюкоза: %1, холестерин: %2, общий белок: %3, креатин: %4, мочевая кислота: %5, лептин: %6")
                  .arg(_exm.field("formfield_78").value())
                  .arg(_exm.field("formfield_79").value())
                  .arg(_exm.field("formfield_80").value())
                  .arg(_exm.field("formfield_81").value())
                  .arg(_exm.field("formfield_82").value())
                  .arg(_exm.field("formfield_83").value())
                  );
    drawParagraph(tr("Дополнительные: %1")
                  .arg(_exm.field("formfield_84").value())
                  );

    drawParagraphTitle(tr("Заключение"));
    drawParagraph(tr("Нутриционный статус: %1, масса тела: %2, ожирение: %3 степени, метаболический синдром: %4.")
                  .arg(_exm.field("formfield_85").value())
                  .arg(_exm.field("formfield_87").value())
                  .arg(_exm.field("formfield_88").value())
                  .arg(_exm.field("formfield_86").value())
                  );
    drawParagraph(tr("Дополнительно: %1")
                  .arg(_exm.field("formfield_90").value())
                  );
}

void Printer::drawParagraphTitle(const QString& s)
{
    QTextCharFormat boldWeight;
    boldWeight.setFontWeight(QFont::Bold);
    QTextBlockFormat normalAlignment;
    normalAlignment.setAlignment(Qt::AlignLeft);

    _cursor.insertBlock(normalAlignment);
    _cursor.setBlockCharFormat(boldWeight);
    _cursor.insertText(s);
}

void Printer::drawParagraph(const QString& s)
{
    QTextCharFormat normalWeight;
    normalWeight.setFontWeight(QFont::Normal);
    QTextBlockFormat normalAlignment;
    normalAlignment.setAlignment(Qt::AlignLeft);

    _cursor.insertBlock(normalAlignment);
    _cursor.setBlockCharFormat(normalWeight);
    _cursor.insertText(s);
}

void Printer::drawDocumentTitle(const QString &s)
{
    QTextCharFormat boldWeight;
    boldWeight.setFontWeight(QFont::Bold);
    QTextBlockFormat centerAlignment;
    centerAlignment.setAlignment(Qt::AlignCenter);

    _cursor.setBlockFormat(centerAlignment);
    _cursor.insertText(s, boldWeight);
}
