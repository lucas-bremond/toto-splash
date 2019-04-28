////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
///	This file is part of the TotoSplash library.
///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///	@file 						TotoSplash/ApplicationStorage.hpp
///	@author 					Lucas Bremond <lucas@axelspace.com>
///	@date 						9 Oct 2016

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __TotoSplash_ApplicationStorage_HPP_INCLUDED__
#define __TotoSplash_ApplicationStorage_HPP_INCLUDED__

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <SmingCore/SmingCore.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace TotoSplash
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define APP_SETTINGS_FILE "Settings.json"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ApplicationStorage
{

	public:

								ApplicationStorage							( ) ;

		bool 					isDefined									( ) ;

		const String&			accessSSID									( ) const ;
		const String&			accessPassword								( ) const ;

		void 					load										( ) ;
		void 					save										( ) ;

	private:

		String 					ssid_ ;
		String 					password_ ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////