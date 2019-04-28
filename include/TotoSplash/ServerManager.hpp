////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
///	This file is part of the TotoSplash library.
///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///	@file 						TotoSplash/ServerManager.hpp
///	@author 					Lucas Bremond <lucas@axelspace.com>
///	@date 						9 Oct 2016

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __TotoSplash_ServerManager_HPP_INCLUDED__
#define __TotoSplash_ServerManager_HPP_INCLUDED__

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <SmingCore/SmingCore.h>

#include <TotoSplash/TaskManager.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace TotoSplash
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ServerManager
{

	public:

								ServerManager 								( ) ;

		bool					isActive									( ) const ;

		void					start										( ) ;
		void					stop										( ) ;

		void					associateTaskManager						(			TaskManager&				aTaskManager						) ;

	private:

		uint					port_ ;

		HttpServer*				serverPtr_ ;

		TaskManager*			taskManagerPtr_ ;

		void					onIndex										(			HttpRequest&				aRequest,
																						HttpResponse&				aResponse							) ;

		void					onFile										(			HttpRequest&				aRequest,
																						HttpResponse&				aResponse							) ;

		void					onStatus									(			HttpRequest&				aRequest,
																						HttpResponse&				aResponse							) ;

		void					onTime										(			HttpRequest&				aRequest,
																						HttpResponse&				aResponse							) ;

		void					onRules										(			HttpRequest&				aRequest,
																						HttpResponse&				aResponse							) ;

		void					onTasks										(			HttpRequest&				aRequest,
																						HttpResponse&				aResponse							) ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////