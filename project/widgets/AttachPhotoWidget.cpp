#include "ui_Attach_photo_widget.h"
#include "AttachPhotoWidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include <QLineEdit>
#include <QFileDialog>
#include <QStandardPaths>
#include <QDebug>
#include <QImageWriter>
#include <QImageReader>
AttachPhotoWidget::AttachPhotoWidget(bool isEnable, QWidget *parent)
    : QWidget(parent)
    , m_ui(new Ui::AttachPhotoWidget)
    , m_isEnable(isEnable)
{
    m_ui->setupUi(this);

}

bool AttachPhotoWidget::saveImage(const QString subFolderName, const QString &fileName) const
{
    QDir dir;
    dir.mkdir(imgDir);
    QString path = imgDir + "/" + subFolderName;
    dir.mkdir(path);
    QString allPath = path + "/" + fileName;

    QImageWriter writer(allPath);
    QImage img =  m_ui->image->pixmap()->toImage();
    if (!writer.write(img)) {
        return false;
    }
    return true;
}

bool AttachPhotoWidget::loadImage(const QString subFolderName, const QString &fileName)
{
    QString allPath = imgDir + "/" + subFolderName + "/" + fileName;
    setImage(allPath);

    return true;
}

void AttachPhotoWidget::enterEvent(QEvent *)
{
    m_ui->addImage->setPixmap(QPixmap(":/resources/add_hover.png"));
}

void AttachPhotoWidget::leaveEvent(QEvent *)
{
    m_ui->addImage->setPixmap(QPixmap(":/resources/add.png"));
}

void AttachPhotoWidget::mousePressEvent(QMouseEvent *)
{
    //if (m_ui->stackedWidget->currentIndex() != 0)
    //    return;

    if (!m_isEnable) return;

    QString fileName = QFileDialog::getOpenFileName(this,
        "Добавить изображение",
        QStandardPaths::displayName(QStandardPaths::DocumentsLocation),
        "Типы изображений(*.png *.jpg *.bmp)");

    if(!fileName.isEmpty()) {
        setImage(fileName);
    }
}

void AttachPhotoWidget::setImage(const QString &fileName)
{
    m_ui->image->setPixmap(QPixmap(fileName));
    m_ui->stackedWidget->setCurrentIndex(1);
    //resizeEvent(nullptr);
}

void AttachPhotoWidget::setEnable(bool isEnable)
{
    m_isEnable = isEnable;
}

QImage AttachPhotoWidget::image() const
{
    return m_ui->image->pixmap()->toImage();
}

void AttachPhotoWidget::resizeEvent(QResizeEvent *)
{
    int containerWidth = this->width();
    int containerHeight = this->height();

    int contentsHeight = containerHeight ;
    int contentsWidth = containerHeight * m_aspectRatio;
    if (contentsWidth > containerWidth ) {
        contentsWidth = containerWidth ;
        contentsHeight = containerWidth / m_aspectRatio;
    }

    resize(contentsWidth, contentsHeight);

    int addButtomScaleFactor = 2;
    m_ui->addImage->setFixedSize(contentsWidth / addButtomScaleFactor
                                 , contentsHeight / addButtomScaleFactor);

    m_ui->image->setFixedSize(m_ui->page_2->width() - 10, m_ui->page_2->height() - 10);
}
