﻿/// \file
/// \author 
///
/// \brief Implementation of class for emoji list.
///  
/// Copyright (c) . All rights reserved.  
/// Licensed under the MIT License. See LICENSE file in the project root for full license information. 


#include "stdafx.h"
#include "EmojiList.h"
#include "BeeftextConstants.h"


//**********************************************************************************************************************
/// \param[in] parent The parent object of the instance.
//**********************************************************************************************************************
EmojiList::EmojiList(QObject* parent)
   : QAbstractTableModel(parent)
{
}


//**********************************************************************************************************************
/// \param[in] index The index of the item.
/// \return A reference to the emoji.
//**********************************************************************************************************************
SpEmoji& EmojiList::operator[](qint32 index)
{
   return list_[index];
}


//**********************************************************************************************************************
/// \param[in] index The index of the item.
/// \return A constant reference to the emoji.
//**********************************************************************************************************************
SpEmoji const& EmojiList::operator[](qint32 index) const
{
   return list_[index];
}


//**********************************************************************************************************************
/// \return An iterator to the beginning of the list.
//**********************************************************************************************************************
EmojiList::iterator EmojiList::begin()
{
   return list_.begin();
}


//**********************************************************************************************************************
/// \return A constant iterator to the beginning of the list.
//**********************************************************************************************************************
EmojiList::const_iterator EmojiList::begin() const
{
   return list_.begin();
}


//**********************************************************************************************************************
/// \return An iterator to the end of the list.
//**********************************************************************************************************************
EmojiList::iterator EmojiList::end()
{
   return list_.end();
}


//**********************************************************************************************************************
/// \return A constant iterator to the end of the list.
//**********************************************************************************************************************
EmojiList::const_iterator EmojiList::end() const
{
   return list_.end();
}


//**********************************************************************************************************************
//
//**********************************************************************************************************************
void EmojiList::clear()
{
   list_.clear();
}


//**********************************************************************************************************************
/// \param[in] shortcode The shortcode.
//**********************************************************************************************************************
bool EmojiList::contains(QString const& shortcode) const
{
   return list_.end() !=  std::find_if(list_.begin(), list_.end(), [&](SpEmoji const& emoji) -> bool
      { return emoji && (emoji->shortcode() == shortcode); });
}


//**********************************************************************************************************************
/// \param[in] shortcode The shortcode.
/// \return The emoji with the given shortcode.
/// \return A null pointer if there is no emoji with this shortcode.
//**********************************************************************************************************************
SpEmoji EmojiList::find(QString const& shortcode) const
{
   const_iterator const it = std::find_if(list_.begin(), list_.end(), [&](SpEmoji const& emoji) -> bool
      { return emoji && (emoji->shortcode() == shortcode); });
   return (it == list_.end()) ? SpEmoji() : *it;
}


//**********************************************************************************************************************
/// \param[in] emoji The emoji
//**********************************************************************************************************************
void EmojiList::append(SpEmoji const& emoji)
{
   list_.push_back(emoji);
}


//**********************************************************************************************************************
/// \return The number of emojis in the list.
//**********************************************************************************************************************
qsizetype EmojiList::size() const
{
   return list_.size();
}


//**********************************************************************************************************************
/// \return true if and only if the list is empty.
//**********************************************************************************************************************
bool EmojiList::isEmpty() const
{
   return list_.isEmpty();
}


//**********************************************************************************************************************
//
//**********************************************************************************************************************
int EmojiList::rowCount(const QModelIndex&) const
{
   return 0;
}


//**********************************************************************************************************************
//
//**********************************************************************************************************************
int EmojiList::columnCount(const QModelIndex&) const
{
   return 1;
}


//**********************************************************************************************************************
/// \param[in] index The index of the data to retrieve.
/// \param[in] role The role to retrieve data for.
//**********************************************************************************************************************
QVariant EmojiList::data(const QModelIndex& index, int role) const
{
   qint32 const row = index.row();
   if ((row < 0) || (row >= qint32(list_.size())))
      return QVariant();
   SpEmoji const emoji = list_[row];
   if (!emoji)
      return QVariant();

   switch (role)
   {
   case Qt::DisplayRole: return emoji->value();
   case constants::TypeRole: 
      return constants::Emoji;
   case constants::PointerRole: 
      return QVariant::fromValue(emoji);
   default: return QVariant();
   }
}


