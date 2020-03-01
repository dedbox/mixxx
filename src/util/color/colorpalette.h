#pragma once

#include <QList>

#include "util/color/rgbcolor.h"

class ColorPalette {
  public:
    ColorPalette(QList<mixxx::RgbColor> colorList)
            : m_colorList(colorList) {
        DEBUG_ASSERT(m_colorList.size() != 0);
    }

    mixxx::RgbColor at(int i) const {
        return m_colorList.at(i);
    }

    int size() const {
        return m_colorList.size();
    }

    int indexOf(mixxx::RgbColor color) const {
        return m_colorList.indexOf(color);
    }

    QList<mixxx::RgbColor>::const_iterator begin() const {
        return m_colorList.begin();
    }

    QList<mixxx::RgbColor>::const_iterator end() const {
        return m_colorList.end();
    }

    static const ColorPalette mixxxHotcuePalette;

    const QList<mixxx::RgbColor>& getColorList() const {
        return m_colorList;
    }

  private:
    QList<mixxx::RgbColor> m_colorList;
};

inline bool operator==(
        const ColorPalette& lhs, const ColorPalette& rhs) {
    return lhs.getColorList() == rhs.getColorList();
}
