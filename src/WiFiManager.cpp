////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
///	This file is part of the TotoSplash library.
///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///	@file 						TotoSplash/WiFiManager.cpp
///	@author 					Lucas Bremond <lucas@axelspace.com>
///	@date 						9 Oct 2016

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <TotoSplash/applicationStorage.hpp>

#include <TotoSplash/WiFiManager.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace TotoSplash
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Will be called when WiFi station network scan was completed
void listNetworks(bool succeeded, BssList list)
{
	if(!succeeded) {
		Serial.println("Failed to scan networks");
		return;
	}

	for(int i = 0; i < list.count(); i++) {
		Serial.print("\tWiFi: ");
		Serial.print(list[i].ssid);
		Serial.print(", ");
		Serial.print(list[i].getAuthorizationMethodName());
		if(list[i].hidden)
			Serial.print(" (hidden)");
		Serial.println();
	}
}

// Will be called when WiFi station was connected to AP
void connectOk(IPAddress ip, IPAddress mask, IPAddress gateway)
{
	debugf("I'm CONNECTED");
	Serial.println(ip.toString());
}

// Will be called when WiFi station was disconnected
void connectFail(String ssid, uint8_t ssidLength, uint8_t* bssid, uint8_t reason)
{
	// The different reason codes can be found in user_interface.h. in your SDK.
	debugf("Disconnected from %s. Reason: %d", ssid.c_str(), reason);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

								WiFiManager::WiFiManager					( )
								:	mode_(WiFiManager::Mode::Station),
									SSID_(""),
									password_(""),
									active_(false),
									applicationStoragePtr_(nullptr)
{

}

bool							WiFiManager::isActive						( ) const
{
	return active_ ;
}

WiFiManager::Mode				WiFiManager::getMode						( ) const
{
	return mode_ ;
}

void							WiFiManager::setMode						(	const 	WiFiManager::Mode&			aMode								)
{
	mode_																		=		aMode ;
}

void							WiFiManager::start							( )
{

	if (this->isActive())
	{
		this->stop() ;
	}

	active_																		=		true ;

	// WifiStation.enable(mode_ == WiFiManager::Mode::Station) ;
	// WifiAccessPoint.enable(mode_ == WiFiManager::Mode::AccessPoint) ;

	// if (mode_ == WiFiManager::Mode::Station)
	// {

	// 	if ((applicationStoragePtr_ != nullptr) && applicationStoragePtr_->isDefined())
	// 	{

	// 		SSID_ = applicationStoragePtr_->accessSSID() ;
	// 		password_ = applicationStoragePtr_->accessPassword() ;

	// 	}

	// 	WifiStation.config(SSID_, password_) ;

	// 	WifiStation.waitConnection(Delegate<void()>(&WiFiManager::onConnectionSuccess, this), 30, Delegate<void()>(&WiFiManager::onConnectionFailure, this)) ; // TBM param

	// }

	// if (mode_ == WiFiManager::Mode::AccessPoint)
	// {
	// 	connectionSuccessHandler_() ;
	// }

	// Soft access point
	WifiAccessPoint.enable(true);
	WifiAccessPoint.config("Sming InternetOfThings", "", AUTH_OPEN);

	// Station - WiFi client
	WifiStation.enable(true);
	WifiStation.config(applicationStoragePtr_->accessSSID(), applicationStoragePtr_->accessPassword()); // Put you SSID and Password here

	// Optional: Change IP addresses (and disable DHCP)
	WifiAccessPoint.setIP(IPAddress(192, 168, 2, 1));
	WifiStation.setIP(IPAddress(192, 168, 1, 171));

	// Print available access points
	WifiStation.startScan(listNetworks); // In Sming we can start network scan from init method without additional code

	// Set callback that should be triggered when we have assigned IP
	WifiEvents.onStationGotIP(connectOk);

	// Set callback that should be triggered if we are disconnected or connection attempt failed
	WifiEvents.onStationDisconnect(connectFail);

}

void							WiFiManager::stop							( )
{

	if (!this->isActive())
	{
		return ;
	}

	if (mode_ == WiFiManager::Mode::Station)
	{
		WifiStation.enable(false) ;
	}

	if (mode_ == WiFiManager::Mode::AccessPoint)
	{
		WifiAccessPoint.enable(false) ;
	}

	active_																		=		false ;

}

void							WiFiManager::associateApplicationStorage	(			ApplicationStorage&			anApplicationStorage				)
{
	applicationStoragePtr_														=		&anApplicationStorage ;
}

void							WiFiManager::setConnectionSuccessHandler	(			Delegate<void()>			aDelegate							)
{
	connectionSuccessHandler_													=		aDelegate ;	
}

void							WiFiManager::setConnectionFailureHandler	(			Delegate<void()>			aDelegate							)
{
	connectionFailureHandler_													=		aDelegate ;	
}

void							WiFiManager::startmDNS						( )
{

	struct mdns_info*			info											=		(struct mdns_info*)os_zalloc(sizeof(struct mdns_info)) ;
	
	info->host_name																=		(char*) "TotoSplash" ;
	info->ipAddr																=		WifiStation.getIP() ;
	info->server_name															=		(char*) "Sming" ;
	info->server_port															=		80 ;
	info->txt_data[0]															=		(char*) "version = now" ;

	espconn_mdns_init(info) ;

}

void							WiFiManager::onConnectionSuccess			( )
{

	if (!active_)
	{
		return ;
	}

	this->startmDNS() ;

	if (connectionSuccessHandler_)
	{
		connectionSuccessHandler_() ;
	}

}

void							WiFiManager::onConnectionFailure			( )
{

	if (!active_)
	{
		return ;
	}

	// if (mode_ == WiFiManager::Mode::Station)
	// {

	// 	// Retry connection

	// 	WifiStation.waitConnection(Delegate<void()>(&WiFiManager::onConnectionSuccess, this), 10, Delegate<void()>(&WiFiManager::onConnectionFailure, this)) ; // TBM param

	// 	if (connectionFailureHandler_)
	// 	{
	// 		connectionFailureHandler_() ;
	// 	}

	// }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////