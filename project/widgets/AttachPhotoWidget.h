#pragma once
#include <QWidget>
#include <QImage>
#include <QImage>


namespace Ui {
class AttachPhotoWidget;
}

class AttachPhotoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AttachPhotoWidget(bool isEnable = true, QWidget *parent = nullptr);

    bool saveImage(const QString subFolderName, const QString &fileName) const;
    bool loadImage(const QString subFolderName, const QString &fileName);
    void setImage(const QString &fileName);

    void setEnable(bool );

    QImage image() const;

    void resizeEvent(QResizeEvent *) override;
protected:
    void enterEvent(QEvent *) override;
    void leaveEvent(QEvent *) override;
    void mousePressEvent(QMouseEvent *) override;


private:
    Ui::AttachPhotoWidget *m_ui;
    //qreal m_zoom;
    QString imgDir = "./img/";
    const qreal m_aspectRatio = 1/1;
    QWidget *centralWidget;
    bool m_isEnable;
};
