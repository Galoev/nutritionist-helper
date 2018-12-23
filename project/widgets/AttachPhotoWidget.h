#pragma once
#include <QWidget>
#include <QImage>

namespace Ui {
class AttachPhotoWidget;
}

class AttachPhotoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AttachPhotoWidget(QWidget *parent = nullptr);

    bool saveImage(const QString subFolderName, const QString &fileName) const;
    void setImage(const QString &fileName);


protected:
    void resizeEvent(QResizeEvent *) override;
    void enterEvent(QEvent *) override;
    void leaveEvent(QEvent *) override;
    void mousePressEvent(QMouseEvent *) override;


private:
    Ui::AttachPhotoWidget *m_ui;
    //qreal m_zoom;
    QString imgDir = "./img/";
    const qreal m_aspectRatio = 1/1;
    QWidget *centralWidget;
};
