////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
///	This file is part of the TotoSplash library.
///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///	@file 						TotoSplash/ServerManager.cpp
///	@author 					Lucas Bremond <lucas@axelspace.com>
///	@date 						9 Oct 2016

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <TotoSplash/ServerManager.hpp>
#include <TotoSplash/Version.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace TotoSplash
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef Delegate<void(HttpRequest&, HttpResponse&)> HttpPathDelegate ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

								ServerManager::ServerManager				( )
								:	port_(80),
									serverPtr_(nullptr),
									taskManagerPtr_(nullptr)
{

}

bool							ServerManager::isActive						( ) const
{
	return (serverPtr_ != nullptr) ;
}

void							ServerManager::start						( )
{

	Serial.println("Starting ServerManager...") ;

	if (this->isActive())
	{
		this->stop() ;
	}

	serverPtr_ = new HttpServer() ;

	serverPtr_->listen(port_) ;

	serverPtr_->paths.setDefault(HttpPathDelegate(&ServerManager::onFile, this)) ;
	serverPtr_->paths.set("/", HttpPathDelegate(&ServerManager::onIndex, this)) ;
	serverPtr_->paths.set("/status", HttpPathDelegate(&ServerManager::onStatus, this)) ;
	serverPtr_->paths.set("/time", HttpPathDelegate(&ServerManager::onTime, this)) ;


	// serverPtr_->paths.set("/", HttpPathDelegate(&ServerManager::onIndex, this)) ;
	// serverPtr_->paths.set("/rules", HttpPathDelegate(&ServerManager::onRules, this)) ;
	// serverPtr_->paths.set("/tasks", HttpPathDelegate(&ServerManager::onTasks, this)) ;

}

void							ServerManager::stop							( )
{

	Serial.println("Stopping ServerManager...") ;

	if (!this->isActive())
	{
		return ;
	}

	delete serverPtr_ ;

	serverPtr_ = nullptr ;

}

void							ServerManager::associateTaskManager			(			TaskManager&				aTaskManager						)
{
	taskManagerPtr_																=		&aTaskManager ;
}

// void onIndex(HttpRequest& request, HttpResponse& response)
// {
// 	counter++;
// 	bool led = request.getQueryParameter("led") == "on";
// 	digitalWrite(LED_PIN, led);

// 	TemplateFileStream* tmpl = new TemplateFileStream("index.html");
// 	auto& vars = tmpl->variables();
// 	vars["counter"] = String(counter);
// 	//vars["ledstate"] = (*portOutputRegister(digitalPinToPort(LED_PIN)) & digitalPinToBitMask(LED_PIN)) ? "checked" : "";
// 	vars["IP"] = WifiStation.getIP().toString();
// 	vars["MAC"] = WifiStation.getMAC();
// 	response.sendTemplate(tmpl); // this template object will be deleted automatically
// }

void							ServerManager::onIndex						(			HttpRequest&				aRequest,
																						HttpResponse&				aResponse							)
{

	aResponse.setCache(86400, true) ;

	aResponse.sendFile("index.html") ;

}

void							ServerManager::onFile						(			HttpRequest&				aRequest,
																						HttpResponse&				aResponse							)
{

	String file = aRequest.uri.Path ;

	if (file[0] == '/')
	{
		file = file.substring(1) ;
	}

	if (file[0] == '.')
	{
		aResponse.code = HTTP_STATUS_FORBIDDEN ;
	}
	else
	{
		aResponse.setCache(86400, true) ;
		aResponse.sendFile(file) ;
	}

}

void							ServerManager::onStatus						(			HttpRequest&				aRequest,
																						HttpResponse&				aResponse							)
{

	if (aRequest.method == HTTP_GET)
	{

		JsonObjectStream* jsonStream = new JsonObjectStream() ;

		JsonObject& jsonObject = jsonStream->getRoot() ;

		jsonObject["status"] = (bool)true ;
		jsonObject["version"] = (String)Version::Current().getString() ;

		aResponse.sendDataStream(jsonStream, MIME_JSON) ;

	}
	else
	{
		aResponse.code = HTTP_STATUS_FORBIDDEN ; // [TBM] Use bad_request
	}

}

void							ServerManager::onTime				(			HttpRequest&				aRequest,
																						HttpResponse&				aResponse							)
{

	if (aRequest.method == HTTP_GET)
	{

		JsonObjectStream* jsonStream = new JsonObjectStream() ;

		JsonObject&	jsonObject = jsonStream->getRoot() ;

		jsonObject["time"] = (String)Time::Now().getString() ;

		aResponse.sendDataStream(jsonStream, MIME_JSON) ;

	}
	else
	{
		aResponse.code = HTTP_STATUS_FORBIDDEN ; // [TBM] Use bad_request
	}

}

// void							ServerManager::onRules						(			HttpRequest&				aRequest,
// 																						HttpResponse&				aResponse							)
// {

// 	if (!taskManagerPtr_)
// 	{
// 		return aResponse.notFound() ;
// 	}

// 	if (aRequest.method == HTTP_GET)
// 	{

// 		JsonObjectStream* 		jsonStream										=		new JsonObjectStream() ;

// 		JsonObject&				JSONObject										=		jsonStream->getRoot() ;

// 		String					idString										=		aRequest.getQueryParameter("id", "") ;

// 		if (idString == "")
// 		{

// 			JsonArray&			ruleArray										=		JSONObject.createNestedArray("rules") ;

// 			for (uint idx = 0; idx < taskManagerPtr_->accessRules().size(); ++idx)
// 			{

// 				const Rule&		rule 											=		taskManagerPtr_->accessRules().elementAt(idx) ;

// 				JsonObject&		ruleObject										=		ruleArray.createNestedObject() ;

// 				ruleObject["id"]												=		(int)rule.getId() ;
// 				ruleObject["type"]												=		(String)Rule::StringFromType(rule.getType()) ;

// 				switch (rule.getType())
// 				{

// 					case Rule::Type::Time:
// 						ruleObject["time"]										=		(String)rule.getTime().getString(CalendarDate::Format::Time) ;
// 						break ;

// 					case Rule::Type::Interval:
// 						ruleObject["interval"]									=		(String)rule.getInterval().getString() ;
// 						break ;

// 					default:
// 						// Do nothing...
// 						break ;

// 				}

// 				ruleObject["duration"]											=		(String)rule.getTaskDuration().getString() ;

// 				if (rule.getPreviousExecutionTime().isDefined())
// 				{
// 					ruleObject["previous_execution_time"]						=		(String)CalendarDate::Time(rule.getPreviousExecutionTime()).getString(CalendarDate::Format::DateTime) ;
// 				}

// 			}

// 		}
// 		else
// 		{

// 			uint				id 												=		idString.toInt() ;

// 			if (id == 0)
// 			{
// 				return aResponse.badRequest() ;
// 			}

// 			if (taskManagerPtr_->hasRuleWithId(id))
// 			{

// 				const Rule&		rule 											=		taskManagerPtr_->accessRuleWithId(id) ;

// 				JSONObject["id"]												=		(int)rule.getId() ;
// 				JSONObject["type"]												=		(String)Rule::StringFromType(rule.getType()) ;

// 				switch (rule.getType())
// 				{

// 					case Rule::Type::Time:
// 						JSONObject["time"]										=		(String)rule.getTime().getString(CalendarDate::Format::Time) ;
// 						break ;

// 					case Rule::Type::Interval:
// 						JSONObject["interval"]									=		(String)rule.getInterval().getString() ;
// 						break ;

// 					default:
// 						// Do nothing...
// 						break ;

// 				}

// 				JSONObject["duration"]											=		(String)rule.getTaskDuration().getString() ;

// 				if (rule.getPreviousExecutionTime().isDefined())
// 				{
// 					JSONObject["previous_execution_time"]						=		(String)CalendarDate::Time(rule.getPreviousExecutionTime()).getString(CalendarDate::Format::DateTime) ;
// 				}

// 			}

// 		}

// 		aResponse.sendDataStream(jsonStream, MIME_JSON) ;

// 	}
// 	else if (aRequest.method == RequestMethod::POST)
// 	{

// 		String					idString										=		aRequest.getPostParameter("id", "") ;

// 		uint					id 												=		0 ;

// 		if (idString != "")
// 		{

// 			id 																	=		idString.toInt() ;

// 			if (id == 0)
// 			{
// 				return aResponse.badRequest() ;
// 			}

// 		}
// 		else
// 		{
// 			id 																	=		taskManagerPtr_->getNextRuleId() ;
// 		}

// 		String					ruleTypeString									=		aRequest.getPostParameter("type", "") ;

// 		if (ruleTypeString != "")
// 		{

// 			Rule::Type			ruleType 										=		Rule::TypeFromString(ruleTypeString) ;

// 			switch (ruleType)
// 			{

// 				case Rule::Type::Time:
// 				{

// 					String		calendarDateString								=		aRequest.getPostParameter("time", "") ;
// 					String		durationString									=		aRequest.getPostParameter("duration", "") ;

// 					Serial.println(calendarDateString) ;
// 					Serial.println(durationString) ;

// 					if (calendarDateString == "")
// 					{
// 						return aResponse.badRequest() ;
// 					}

// 					if (durationString == "")
// 					{
// 						return aResponse.badRequest() ;
// 					}

// 					CalendarDate calendarDate 									=		CalendarDate::Parse(calendarDateString) ;
// 					Duration	duration										=		Duration::Parse(durationString) ;

// 					Serial.println(calendarDate.getString()) ;
// 					Serial.println(duration.getString()) ;

// 					if (!calendarDate.isDefined())
// 					{
// 						return aResponse.badRequest() ;
// 					}

// 					if (!duration.isDefined())
// 					{
// 						return aResponse.badRequest() ;
// 					}

// 					if (!taskManagerPtr_->addRule(Rule::AtTime(id, calendarDate, duration)))
// 					{
// 						return aResponse.badRequest() ;
// 					}

// 					break ;

// 				}

// 				// case Rule::Type::Interval: // TBI
// 				// {
// 				// 	break ;
// 				// }

// 				default:
// 					return aResponse.badRequest() ;

// 			}

// 		}
// 		else
// 		{
// 			return aResponse.badRequest() ;
// 		}

// 	}
// 	else if (aRequest.method == RequestMethod::DELETE)
// 	{

// 		String					ruleIdString									=		aRequest.getQueryParameter("id", "") ;

// 		if (ruleIdString == "")
// 		{
// 			return aResponse.badRequest() ;
// 		}

// 		uint					ruleId											=		ruleIdString.toInt() ;

// 		if (ruleId == 0)
// 		{
// 			return aResponse.badRequest() ;
// 		}

// 		if (!taskManagerPtr_->removeRuleWithId(ruleId))
// 		{
// 			return aResponse.badRequest() ;
// 		}

// 	}
// 	else
// 	{
// 		aResponse.badRequest() ;
// 	}

// }

// void							ServerManager::onTasks						(			HttpRequest&				aRequest,
// 																						HttpResponse&				aResponse							)
// {

// 	if (!taskManagerPtr_)
// 	{
// 		return aResponse.notFound() ;
// 	}

// 	if (aRequest.method == HTTP_GET)
// 	{

// 		JsonObjectStream* 		jsonStream										=		new JsonObjectStream() ;

// 		JsonObject&				JSONObject										=		jsonStream->getRoot() ;

// 		String					idString										=		aRequest.getQueryParameter("id", "") ;

// 		if (idString == "")
// 		{

// 			JsonArray&			taskArray										=		JSONObject.createNestedArray("tasks") ;

// 			for (uint idx = 0; idx < taskManagerPtr_->accessTasks().size(); ++idx)
// 			{

// 				const Task&		task 											=		taskManagerPtr_->accessTasks().elementAt(idx) ;

// 				JsonObject&		taskObject										=		taskArray.createNestedObject() ;

// 				taskObject["id"]												=		(int)task.getId() ;
// 				taskObject["status"]											=		(String)Task::getStringOfStatus(task.getStatus()) ;
// 				taskObject["execution_time"]									=		(String)task.getExecutionTime().getString() ;
// 				taskObject["duration"]											=		(String)task.getDuration().getString() ;

// 				if (task.isRuleDefined())
// 				{
// 					taskObject["rule_id"]										=		(int)task.getRuleId() ;
// 				}

// 			}

// 		}
// 		else
// 		{

// 			uint				id 												=		idString.toInt() ;

// 			if (id == 0)
// 			{
// 				return aResponse.badRequest() ;
// 			}

// 			if (taskManagerPtr_->hasTaskWithId(id))
// 			{

// 				const Task&		task 											=		taskManagerPtr_->accessTaskWithId(id) ;

// 				JSONObject["id"]												=		(int)task.getId() ;
// 				JSONObject["status"]											=		(String)Task::getStringOfStatus(task.getStatus()) ;
// 				JSONObject["execution_time"]									=		(String)task.getExecutionTime().getString() ;
// 				JSONObject["duration"]											=		(String)task.getDuration().getString() ;

// 				if (task.isRuleDefined())
// 				{
// 					JSONObject["rule_id"]										=		(int)task.getRuleId() ;
// 				}

// 			}

// 		}

// 		aResponse.sendDataStream(jsonStream, MIME_JSON) ;

// 	}
// 	else if (aRequest.method == RequestMethod::POST)
// 	{

// 		String					idString										=		aRequest.getPostParameter("id", "") ;

// 		uint					id 												=		0 ;

// 		if (idString != "")
// 		{

// 			id 																	=		idString.toInt() ;

// 			if (id == 0)
// 			{
// 				return aResponse.badRequest() ;
// 			}

// 		}
// 		else
// 		{
// 			id 																	=		taskManagerPtr_->getNextTaskId() ;
// 		}

// 		String					executionTimeString								=		aRequest.getPostParameter("execution_time", "") ;
// 		String					durationString									=		aRequest.getPostParameter("duration", "") ;

// 		if (executionTimeString != "")
// 		{

// 			Time 				executionTime 									=		Time::CalendarDate(CalendarDate::Parse(executionTimeString)) ;

// 			if (!executionTime.isDefined())
// 			{
// 				return aResponse.badRequest() ;
// 			}

// 			if (durationString != "")
// 			{

// 				Duration		duration										=		Duration::Parse(durationString) ;

// 				if (!duration.isDefined())
// 				{
// 					return aResponse.badRequest() ;
// 				}

// 				if (!taskManagerPtr_->addTask(Task(id, executionTime, duration)))
// 				{
// 					return aResponse.badRequest() ;
// 				}

// 			}
// 			else
// 			{

// 				if (!taskManagerPtr_->addTask(Task(id, executionTime)))
// 				{
// 					return aResponse.badRequest() ;
// 				}

// 			}

// 		}
// 		else
// 		{

// 			if (!taskManagerPtr_->addImmediateTask())
// 			{
// 				return aResponse.badRequest() ;
// 			}

// 		}

// 	}
// 	else if (aRequest.method == RequestMethod::DELETE)
// 	{

// 		String					taskIdString									=		aRequest.getQueryParameter("id", "") ;

// 		if (taskIdString == "")
// 		{
// 			return aResponse.badRequest() ;
// 		}

// 		uint					taskId											=		taskIdString.toInt() ;

// 		if (taskId == 0)
// 		{
// 			return aResponse.badRequest() ;
// 		}

// 		if (!taskManagerPtr_->removeTaskWithId(taskId))
// 		{
// 			return aResponse.badRequest() ;
// 		}

// 	}
// 	else
// 	{
// 		aResponse.badRequest() ;
// 	}

// }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////