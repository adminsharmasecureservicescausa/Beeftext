cmake_minimum_required(VERSION 3.16)

project(Beeftext VERSION 14.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

if (NOT DEFINED ENV{QTDIR})
   message(FATAL_ERROR "QTDIR needs to be defined and point to the root of your Qt folder. (e.g. /Users/MyName/Qt/5.10.1/clang_64).")
endif()

set(CMAKE_PREFIX_PATH  ${CMAKE_PREFIX_PATH} $ENV{QTDIR})
set(CMAKE_CXX_FLAGS_RELEASE  "${CMAKE_CXX_FLAGS_RELEASE} -DNDEBUG")

find_package(Qt6Core)
find_package(Qt6Gui)
find_package(Qt6Widgets)
find_package(Qt6Network)

include_directories("../..")
include_directories("../Submodules/XMiLib")

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC_MOC_OPTIONS "-bstdafx.h")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(POWERSHELL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../Scripts/Powershell)

add_definitions(-DUNICODE -D_UNICODE)

file(TO_NATIVE_PATH "${POWERSHELL_DIR}/CompileTranslationFiles.ps1" TRANS_SRC_DIR)
file(TO_NATIVE_PATH "${CMAKE_CURRENT_BINARY_DIR}/translations" TRANS_DST_DIR)

add_custom_target(translations
   COMMAND
   powershell.exe -ExecutionPolicy Bypass -NoProfile -NonInteractive -command \"${TRANS_SRC_DIR} ${TRANS_DST_DIR}\" >NUL
)

add_executable(Beeftext
   AutoStart.cpp
   AutoStart.h
   BeeftextConstants.cpp
   BeeftextConstants.h
   BeeftextGlobals.cpp
   BeeftextGlobals.h
   BeeftextUtils.cpp
   BeeftextUtils.h
   I18nManager.cpp
   I18nManager.h
   InputManager.cpp
   InputManager.h
   KeyboardMapper.cpp
   KeyboardMapper.h
   LatestVersionInfo.cpp
   LatestVersionInfo.h
   main.cpp
   MainWindow.cpp
   MainWindow.h
   MimeDataUtils.cpp
   MimeDataUtils.h
   SensitiveApplicationManager.cpp
   SensitiveApplicationManager.h
   Shortcut.cpp
   Shortcut.h
   stdafx.cpp
   stdafx.h
   Theme.cpp
   Theme.h
   WaveSound.cpp
   WaveSound.h
   Backup/BackupManager.cpp
   Backup/BackupManager.h
   Backup/BackupRestoreDialog.cpp
   Backup/BackupRestoreDialog.h
   Backup/BackupRestoreDialog.ui
   Clipboard/ClipboardManager.cpp
   Clipboard/ClipboardManager.h
   Clipboard/ClipboardManagerDefault.cpp
   Clipboard/ClipboardManagerDefault.h
   Clipboard/ClipboardManagerLegacy.cpp
   Clipboard/ClipboardManagerLegacy.h
   Combo/CaseSensitivity.cpp
   Combo/CaseSensitivity.h
   Combo/Combo.cpp
   Combo/Combo.h
   Combo/ComboDialog.cpp
   Combo/ComboDialog.h
   Combo/ComboDialog.ui
   Combo/ComboEditor.cpp
   Combo/ComboEditor.h
   Combo/ComboFrame.cpp
   Combo/ComboFrame.h
   Combo/ComboFrame.ui
   Combo/ComboImportDialog.cpp
   Combo/ComboImportDialog.h
   Combo/ComboImportDialog.ui
   Combo/ComboKeywordValidator.cpp
   Combo/ComboKeywordValidator.h
   Combo/ComboList.cpp
   Combo/ComboList.h
   Combo/ComboManager.cpp
   Combo/ComboManager.h
   Combo/ComboSortFilterProxyModel.cpp
   Combo/ComboSortFilterProxyModel.h
   Combo/ComboTableWidget.cpp
   Combo/ComboTableWidget.h
   Combo/ComboTableWidget.ui
   Combo/ComboVariable.cpp
   Combo/ComboVariable.h
   Combo/MatchingMode.cpp
   Combo/MatchingMode.h
   Dialogs/AboutDialog.cpp
   Dialogs/AboutDialog.h
   Dialogs/AboutDialog.ui
   Dialogs/ShortcutDialog.cpp
   Dialogs/ShortcutDialog.h
   Dialogs/ShortcutDialog.ui
   Dialogs/VariableInputDialog.cpp
   Dialogs/VariableInputDialog.h
   Emoji/Emoji.cpp
   Emoji/Emoji.h
   Emoji/EmojiList.cpp
   Emoji/EmojiList.h
   Emoji/EmojiManager.cpp
   Emoji/EmojiManager.h
   Group/Group.cpp
   Group/Group.h
   Group/GroupComboBox.cpp
   Group/GroupComboBox.h
   Group/GroupDialog.cpp
   Group/GroupDialog.h
   Group/GroupDialog.ui
   Group/GroupList.cpp
   Group/GroupList.h
   Group/GroupListWidget.cpp
   Group/GroupListWidget.h
   Group/GroupListWidget.ui
   LastUse/ComboLastUseFile.cpp
   LastUse/ComboLastUseFile.h
   LastUse/EmojiLastUseFile.cpp
   LastUse/EmojiLastUseFile.h
   Picker/PickerItemDelegate.cpp
   Picker/PickerItemDelegate.h
   Picker/PickerModel.cpp
   Picker/PickerModel.h
   Picker/PickerSortFilterProxyModel.cpp
   Picker/PickerSortFilterProxyModel.h
   Picker/PickerWindow.cpp
   Picker/PickerWindow.h
   Picker/PickerWindow.ui
   Picker/PickerWindowMoverResizer.cpp
   Picker/PickerWindowMoverResizer.h
   Preferences/Panes/PrefPane.h
   Preferences/Panes/PrefPaneAdvanced.cpp
   Preferences/Panes/PrefPaneAdvanced.h
   Preferences/Panes/PrefPaneAdvanced.ui
   Preferences/Panes/PrefPaneAppearance.cpp
   Preferences/Panes/PrefPaneAppearance.h
   Preferences/Panes/PrefPaneAppearance.ui
   Preferences/Panes/PrefPaneBehavior.cpp
   Preferences/Panes/PrefPaneBehavior.h
   Preferences/Panes/PrefPaneBehavior.ui
   Preferences/Panes/PrefPaneCombos.cpp
   Preferences/Panes/PrefPaneCombos.h
   Preferences/Panes/PrefPaneCombos.ui
   Preferences/Panes/PrefPaneEmojis.cpp
   Preferences/Panes/PrefPaneEmojis.h
   Preferences/Panes/PrefPaneEmojis.ui
   Preferences/PreferencesDialog.cpp
   Preferences/PreferencesDialog.h
   Preferences/PreferencesDialog.ui
   Preferences/PreferencesManager.cpp
   Preferences/PreferencesManager.h
   Snippet/DelaySnippetFragment.cpp
   Snippet/DelaySnippetFragment.h
   Snippet/KeySnippetFragment.cpp
   Snippet/KeySnippetFragment.h
   Snippet/ShortcutSnippetFragment.cpp
   Snippet/ShortcutSnippetFragment.h
   Snippet/SnippetFragment.cpp
   Snippet/SnippetFragment.h
   Snippet/TextSnippetFragment.cpp
   Snippet/TextSnippetFragment.h
   Update/UpdateCheckWorker.cpp
   Update/UpdateCheckWorker.h
   Update/UpdateDialog.cpp
   Update/UpdateDialog.h
   Update/UpdateDialog.ui
   Update/UpdateManager.cpp
   Update/UpdateManager.h
   Beeftext.qrc
   Beeftext.rc
)

add_dependencies(Beeftext translations)

#target_precompile_headers(Beeftext PUBLIC stdafx.h)
target_link_libraries(Beeftext Qt6::Core)
target_link_libraries(Beeftext Qt6::Gui)
target_link_libraries(Beeftext Qt6::Widgets)
target_link_libraries(Beeftext Qt6::Network)
target_link_libraries(Beeftext XMiLib)
target_link_libraries(Beeftext Winmm)
