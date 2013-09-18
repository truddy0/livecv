#ifndef QMATVALUES_HPP
#define QMATVALUES_HPP

#include <QQuickItem>
#include <QSGSimpleTextureNode>
#include "QMat.hpp"

class QPainter;
class QOpenGLPaintDevice;
class QOpenGLFramebufferObject;
class QMatReadNode : public QObject, public QSGSimpleTextureNode{

    Q_OBJECT

public:
    QMatReadNode(QQuickWindow* window);
    ~QMatReadNode();

    void render(QMat* image, const QFont& font, const QColor& color, int numberWidth = 5, bool equalAspectRatio = false);

private:
    QOpenGLFramebufferObject *m_fbo;
    QSGTexture               *m_texture;
    QQuickWindow             *m_window;
    QPainter                 *m_painter;
    QOpenGLPaintDevice       *m_paintDevice;

};

class QMatRead : public QQuickItem{

    Q_OBJECT
    Q_PROPERTY(QMat*  input       READ inputMat    WRITE setInputMat    NOTIFY inputChanged)
    Q_PROPERTY(QFont  font        READ font        WRITE setFont        NOTIFY fontChanged)
    Q_PROPERTY(QColor color       READ color       WRITE setColor       NOTIFY colorChanged)
    Q_PROPERTY(int    numberWidth READ numberWidth WRITE setNumberWidth NOTIFY numberWidthChanged)
    Q_PROPERTY(bool   squareCell  READ squareCell  WRITE setSquareCell  NOTIFY squareCellChanged)

public:
    explicit QMatRead(QQuickItem *parent = 0);
    ~QMatRead();

    QMat* inputMat();
    void setInputMat(QMat* mat);

    const QFont& font() const;
    const QColor& color() const;
    int numberWidth() const;
    bool squareCell() const;

    void setFont(const QFont &arg);
    void setColor(const QColor& arg);
    void setNumberWidth(int arg);
    void setSquareCell(bool arg);

    void calculateImplicitSize();

signals:
    void inputChanged();
    void fontChanged();
    void colorChanged();
    void numberWidthChanged();
    void squareCellChanged();

protected:
    QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *);

private:
    QMatRead(const QMatRead& other);
    QMatRead& operator= (const QMatRead& other);

    QMat*  m_input;
    QFont  m_font;
    QColor m_color;
    int    m_numberWidth;
    bool   m_squareCell;
};

inline const QFont& QMatRead::font() const{
    return m_font;
}

inline const QColor& QMatRead::color() const{
    return m_color;
}

inline int QMatRead::numberWidth() const{
    return m_numberWidth;
}

inline bool QMatRead::squareCell() const{
    return m_squareCell;
}

inline void QMatRead::setFont(const QFont& arg){
    if (m_font != arg) {
        m_font = arg;
        emit fontChanged();
        calculateImplicitSize();
        update();
    }
}

inline void QMatRead::setColor(const QColor& arg){
    if (m_color != arg) {
        m_color = arg;
        emit colorChanged();
        update();
    }
}

inline void QMatRead::setNumberWidth(int arg){
    if (m_numberWidth != arg) {
        m_numberWidth = arg;
        emit numberWidthChanged();
        calculateImplicitSize();
        update();
    }
}

inline void QMatRead::setSquareCell(bool arg){
    if (m_squareCell != arg) {
        m_squareCell = arg;
        emit squareCellChanged();
        calculateImplicitSize();
        update();
    }
}

inline QMat *QMatRead::inputMat(){
    return m_input;
}

inline void QMatRead::setInputMat(QMat *mat){
    if ( mat != m_input ){
        m_input = mat;
        calculateImplicitSize();
    } else {
        m_input = mat;
        if ( implicitHeight() == 0 || implicitWidth() == 0){
            calculateImplicitSize();
        }
    }
    emit inputChanged();
    update();
}

#endif // QMATVALUES_HPP
