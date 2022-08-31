/*
    SPDX-FileCopyrightText: 1998 Anders Widell <d95-awi@nada.kth.se>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "StaticImage.h"

#include "images/data.c"

#include <cassert>

StaticImage::StaticImage()
{
    const unsigned char *const imageData[NO_OF_IMAGES] = {
        halfstone_1_data_,
        halfstone_2_data_,
        halfstone_3_data_,
        halfstone_4_data_,

        stone_1_data_,
        stone_2_data_,
        stone_3_data_,
        stone_4_data_,
        stone_5_data_,
        stone_6_data_,
    };

    const unsigned imageSize[NO_OF_IMAGES] = {
        sizeof halfstone_1_data_,
        sizeof halfstone_2_data_,
        sizeof halfstone_3_data_,
        sizeof halfstone_4_data_,

        sizeof stone_1_data_,
        sizeof stone_2_data_,
        sizeof stone_3_data_,
        sizeof stone_4_data_,
        sizeof stone_5_data_,
        sizeof stone_6_data_,
    };

    for (int i = 0; i < NO_OF_IMAGES; i++) {
        images_[i].loadFromData((const uchar *)imageData[i], (uint)imageSize[i]);
    }

    // resize(32,32);
}

StaticImage::~StaticImage() = default;
