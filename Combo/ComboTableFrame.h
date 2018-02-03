/// \file
/// \author Xavier Michelon
///
/// \brief Declaration of combo table frame
///  
/// Copyright (c) Xavier Michelon. All rights reserved.  
/// Licensed under the MIT License. See LICENSE file in the project root for full license information.  


#ifndef BEEFTEXT__COMBO__TABLE__FRAME__H
#define BEEFTEXT__COMBO__TABLE__FRAME__H


#include "ui_ComboTableFrame.h"
#include "ComboSortFilterProxyModel.h"
#include <memory>


//**********************************************************************************************************************
/// \brief A class for the frame containing the combo table and associated controls
//**********************************************************************************************************************
class ComboTableFrame: public QFrame
{
   Q_OBJECT
public: // member functions
	ComboTableFrame(QWidget* parent = nullptr); ///< Default constructor
	~ComboTableFrame() = default; ///< Default destructor

protected: // member functions
   bool eventFilter(QObject *object, QEvent *event) override; ///< Event filter to override the default behavior of double-click in the table view

private: // member functions
	ComboTableFrame(ComboTableFrame const&) = delete; ///< Disabled copy constructor
	ComboTableFrame(ComboTableFrame&&) = delete; ///< Disabled move constructor
	ComboTableFrame& operator=(ComboTableFrame const&) = delete; ///< Disabled assignment operator
	ComboTableFrame& operator=(ComboTableFrame&&) = delete; ///< Disabled move assignment operator
   void setupTable(); ///< Setup the combo table
   void setupContextMenu(); ///< Setup the context menu
   qint32 getSelectedComboCount() const; ///< Get the number of selected combo in the combo table
   QList<qint32> getSelectedComboIndexes() const; ///< Retrieve the list indexes of the selected combos
   void changeEvent(QEvent *event) override; ///< Change event handler

private slots:
   void updateGui() const; ///< Update the GUI state
   void onActionAddCombo(); ///< Slot for the 'Add Combo' action
   void onActionDuplicateCombo(); ///< Slot for the 'Duplicate Combo' action
   void onActionDeleteCombo(); ///< Slot for the 'Delete Combo' action
   void onActionEditCombo(); ///< Slot for the 'Edit Combo' action
   void onActionSelectAll() const; ///< Slot for the 'Select All' action
   void onActionDeselectAll() const; ///< Slot for the 'Deselect All' action
   void onActionEnableDisableCombo(); ///< Slot for the 'Enable/Disable' action
   void onActionExportCombo(); ///< Slot for the 'Export Combo' action
   void onActionImportCombos(); ///< Slot for the 'Import Combos' action
   void onSearchFilterChanged(QString const& text); ///< Slot for the changing of the search field
   void onContextMenuRequested(); ///< Slot for the combo table context menu
   void onDoubleClick(); ///< Slot for the double clicking in the table view

private: // data members
   Ui::ComboTableFrame ui_; ///< The GUI for the frame
   ComboSortFilterProxyModel proxyModel_; ///< The proxy model for sorting/filtering the combo table
   QMenu contextMenu_; ///< The context menu for the combo table
   std::unique_ptr<class ComboTableProxyStyle> proxyStyle_; ///< The proxy style to tweak appearance of the table view

};

#endif // #ifndef BEEFTEXT__COMBO__TABLE__FRAME__H
