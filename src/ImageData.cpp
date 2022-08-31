/*
    SPDX-FileCopyrightText: 1998 Anders Widell <awl@hem.passagen.se>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ImageData.h"

#include <QColor>
#include <QGuiApplication>
#include <QPainter>

#include <cassert>

ImageData::ImageData()
{
    stoneIndex_.setStoneCount(LARGE_STONES, SMALL_STONES);
}

ImageData::~ImageData() = default;

const QPixmap &ImageData::upperLarge(int index)
{
    assert(index >= 0);
    return largeStone_xpm_[stoneIndex_.upperLarge(index)];
}

const QPixmap &ImageData::lowerLarge(int index)
{
    assert(index >= 0);
    return largeStone_xpm_[stoneIndex_.lowerLarge(index)];
}

const QPixmap &ImageData::leftSmall(int index)
{
    assert(index >= 0);
    return smallStone_xpm_[stoneIndex_.leftSmall(index)];
}

const QPixmap &ImageData::rightSmall(int index)
{
    assert(index >= 0);
    return smallStone_xpm_[stoneIndex_.rightSmall(index)];
}

int ImageData::resize(int size)
{
    assert(size > 0);
    size &= ~1u;
    if (size == size_)
        return size;

    size_ = size;
    halfSize_ = size / 2;

    const qreal dpr = qApp->devicePixelRatio();
    const int deviceSize_ = size_ * dpr;
    halfdeviceSize_ = deviceSize_ / 2;

    for (int i = 0; i < SMALL_STONES; i++) {
        image2pixmap(images_[i].scaled(halfdeviceSize_, halfdeviceSize_, Qt::IgnoreAspectRatio, Qt::SmoothTransformation), smallStone_xpm_[i], dpr);
        //     smallStone_xpm_[i].convertFromImage(images_[i].smoothScale(halfSize_, halfSize_),
        //     QPixmap::ColorOnly|QPixmap::DiffuseDither|QPixmap::DiffuseAlphaDither|QPixmap::AvoidDither);
    }

    for (int i = 0; i < LARGE_STONES; i++) {
        image2pixmap(images_[SMALL_STONES + i].scaled(deviceSize_, halfdeviceSize_, Qt::IgnoreAspectRatio, Qt::SmoothTransformation), largeStone_xpm_[i], dpr);
        //     largeStone_xpm_[i].convertFromImage(images_[SMALL_STONES+i].smoothScale(size_, halfSize_) ,
        //     QPixmap::ColorOnly|QPixmap::DiffuseDither|QPixmap::DiffuseAlphaDither|QPixmap::AvoidDither);
    }

    return size_;
}

// Don't use DiffuseDither for the objects on the "floor" since
// it gives spurious dots on the floor around them

void ImageData::image2pixmap(const QImage &img, QPixmap &xpm, qreal dpr, bool diffuse)
{
    xpm = QPixmap::fromImage(img,
                             (diffuse ? (Qt::DiffuseDither | Qt::DiffuseAlphaDither) : (Qt::OrderedDither | Qt::OrderedAlphaDither)) | Qt::ColorOnly
                                 | Qt::AvoidDither);
    xpm.setDevicePixelRatio(dpr);
}

void ImageData::wall(QPainter &p, int x, int y, int index, bool left, bool right)
{
    if (left)
        p.drawPixmap(x, y, upperLarge(index - 1), halfdeviceSize_, 0, -1, -1);
    else
        p.drawPixmap(x, y, leftSmall(index));

    if (right)
        p.drawPixmap(x + halfSize_, y, upperLarge(index), 0, 0, halfdeviceSize_, -1);
    else
        p.drawPixmap(x + halfSize_, y, rightSmall(index));

    p.drawPixmap(x, y + halfSize_, lowerLarge(index));
}
