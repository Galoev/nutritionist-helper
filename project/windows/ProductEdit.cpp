#include "productedit.h"
#include "ui_Product_edit.h"

ProductEdit::ProductEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProductEdit)
{
    ui->setupUi(this);
}

ProductEdit::~ProductEdit()
{
    delete ui;
}
