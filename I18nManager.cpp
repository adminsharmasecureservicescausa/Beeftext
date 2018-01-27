/// \file
/// \author Xavier Michelon
///
/// \brief Declaration of internationalization manager
///  
/// Copyright (c) Xavier Michelon. All rights reserved.  
/// Licensed under the MIT License. See LICENSE file in the project root for full license information.  


#include "stdafx.h"
#include "I18nManager.h"


namespace {
   QList<QLocale> const kSupportedLocales = { QLocale::English, QLocale::French }; ///< The list of locales supported by the application
}


void removeTranslator(std::unique_ptr<QTranslator>& translator); ///< Remove a translator, free it and set the pointer that was pointing to it to zero


//**********************************************************************************************************************
/// \param[in] translator A pointer to the translator to remove
//**********************************************************************************************************************
void removeTranslator(std::unique_ptr<QTranslator>& translator)
{
   if (!translator)
      return;
   qApp->removeTranslator(translator.get());
   translator.reset();
}


//**********************************************************************************************************************
/// \return The only allowed instance of the class
//**********************************************************************************************************************
I18nManager& I18nManager::instance()
{
   static I18nManager instance;
   return instance;
}


//**********************************************************************************************************************
/// \param[in] locale The locale to validate
/// \return if locale is supported, it is returned, otherwise the default locale (English) is returned instead
//**********************************************************************************************************************
QLocale I18nManager::validateLocale(QLocale const& locale)
{
   Q_ASSERT(!kSupportedLocales.isEmpty());
   return kSupportedLocales.contains(locale) ? locale : kSupportedLocales.front();
}


//**********************************************************************************************************************
/// \param[in] combo The combo box
//**********************************************************************************************************************
void I18nManager::fillLocaleCombo(QComboBox& combo)
{
   QSignalBlocker blocker(&combo);
   combo.clear();
   for (QLocale const& locale : kSupportedLocales)
   {
      QString languageName = locale == QLocale::English ? "English" : locale.nativeLanguageName();
      if (!languageName.isEmpty())
         languageName[0] = languageName[0].toUpper();
      combo.addItem(languageName, locale);
   }
}


//**********************************************************************************************************************
/// \param[in] locale The combo
/// \param[in] combo The combo containing the locale
//**********************************************************************************************************************
void I18nManager::selectLocaleInCombo(QLocale const& locale, QComboBox& combo)
{
   for (qint32 i = 0; i < combo.count(); ++i)
   {
      QVariant data = combo.itemData(i);
      if (!data.canConvert<QLocale>())
         continue;
      QLocale const itemLocale = data.toLocale();
      if (itemLocale != locale)
         continue;
      if (i == combo.currentIndex())
         return;
      combo.setCurrentIndex(i);
   }
}



//**********************************************************************************************************************
/// \param[in] combo The combo box
//**********************************************************************************************************************
QLocale I18nManager::getSelectedLocaleInCombo(QComboBox const& combo)
{
   return validateLocale(combo.currentData().toLocale());
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void I18nManager::loadTranslation()
{
   this->removeAllTranslators();

   QLocale const locale(this->locale());
   QString const langStr(locale.name().left(2));
   if (QLocale::English == locale.language())
      return; // English needs no translation

   // load and install qt translations (containing all translations for Qt internal strings)
   qtTranslator_ = std::make_unique<QTranslator>(qApp);
   QString const qtTransFile = QString(":/Translations/qtbase_%1.qm").arg(langStr);
   if (!qtTranslator_->load(qtTransFile))
   {
      qtTranslator_.reset();
      QMessageBox::critical(nullptr, "Translation File Missing", "Could not find Qt translation file.");
      return;
   }

   // load and install application translations
   appTranslator_ = std::make_unique<QTranslator>(qApp);
   if (!appTranslator_->load(QString(":/Translations/beeftext_%1.qm").arg(langStr)))
   {
      appTranslator_.reset();
      QMessageBox::critical(nullptr, "Translation File Missing", "Could not find application translation file.");
      return;
   }

   // load and install xmilib translations
   xmilibTranslator_ = std::make_unique<QTranslator>(qApp);
   if (!xmilibTranslator_->load(QString(":/Translations/xmilib_%1.qm").arg(langStr)))
   {
      xmilibTranslator_.reset();
      QMessageBox::critical(nullptr, "Translation File Missing", "Could not find XMiLib translation file.");
      return;
   }

   qApp->installTranslator(qtTranslator_.get());
   qApp->installTranslator(appTranslator_.get());
   qApp->installTranslator(xmilibTranslator_.get());
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void I18nManager::unloadTranslation()
{
   this->removeAllTranslators();
}


//**********************************************************************************************************************
/// \return The current locale
//**********************************************************************************************************************
QLocale I18nManager::locale()
{
   return QLocale();
}


//**********************************************************************************************************************
/// \param[in] locale The new locale
//**********************************************************************************************************************
void I18nManager::setLocale(QLocale const& locale)
{
   if (locale == QLocale())
      return; // already set
   QLocale::setDefault(locale);
   this->loadTranslation();
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void I18nManager::removeAllTranslators()
{
   removeTranslator(qtTranslator_);
   removeTranslator(appTranslator_);
   removeTranslator(xmilibTranslator_);
}


