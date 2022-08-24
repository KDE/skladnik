/*
    SPDX-FileCopyrightText: 1998 Anders Widell <d95-awi@nada.kth.se>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef MODALLABEL_H
#define MODALLABEL_H

#include <QLabel>

class ModalLabel : public QLabel
{
    Q_OBJECT

public:
    static void message(const QString &text, QWidget *parent);

protected:
    void timerEvent(QTimerEvent *) override;
    bool eventFilter(QObject *, QEvent *) override;

private:
    ModalLabel(const QString &text, QWidget *parent);

private:
    bool completed_ = false;
};

#endif /* MODALLABEL_H */
