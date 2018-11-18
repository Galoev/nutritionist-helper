#ifndef PRINTMODULE_H
#define PRINTMODULE_H
#include "entities/examination.h"
#include <QWidget>
#include <QPrinter>
#include <QPaintDevice>
#include <QPrintPreviewDialog>
#include <QTextCursor>

class Printer : public QWidget
{
    Q_OBJECT
public:
    explicit Printer(QWidget* wgt = nullptr);
    virtual ~Printer();

    void previewExamination(const Examination& , bool isFullReport);

private slots:
    void previewPageExamination(QPrinter*);

private:
    void drawHalfExamination();
    void drawFullExamination();
    void drawParagraphTitle(const QString& );
    void drawParagraph(const QString& );
    void drawDocumentTitle(const QString& );

    Examination _exm;
    bool _isFullReport;
    QPrinter* _printer;

    QTextCursor _cursor;
};

#endif // PRINTMODULE_H
