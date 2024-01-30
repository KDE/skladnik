# SPDX-FileCopyrightText: 2022 Friedrich W. H. Kossebau <kossebau@kde.org>
#
# SPDX-License-Identifier: BSD-3-Clause

add_subdirectory(images)

ecm_setup_version(${skladnik_VERSION}
    VARIABLE_PREFIX SKLADNIK
    VERSION_HEADER version.h
)

add_executable(skladnik
    Bookmark.cpp
    LevelMap.cpp
    Map.cpp
    Move.cpp
    PlayField.cpp
    PlayFieldView.cpp
    History.cpp
    InternalCollections.cpp
    main.cpp
    MoveSequence.cpp
    HtmlPrinter.cpp
    LevelCollection.cpp
    MainWindow.cpp
    PathFinder.cpp
    StoneIndex.cpp
    GroundItem.cpp
    SimpleTextItem.cpp

    skladnik.qrc
)

target_link_libraries(skladnik
    KDEGames6
    KF6::I18n
    KF6::WidgetsAddons
    KF6::Crash
    KF6::DBusAddons
    KF6::XmlGui
    KF6::KIOCore
)

install(TARGETS skladnik ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})

install(FILES org.kde.skladnik.desktop DESTINATION ${KDE_INSTALL_APPDIR})
install(FILES org.kde.skladnik.metainfo.xml DESTINATION ${KDE_INSTALL_METAINFODIR})
