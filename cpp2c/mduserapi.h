#ifndef CTP_C_API_MDUSERAPI_H
#define CTP_C_API_MDUSERAPI_H

#include "ctpcapi.h"
#include "cpp_api/ThostFtdcMdApi.h"

#include <set>
#include <string>
#include <mutex>

using namespace std;

class CMdUserApi : public CThostFtdcMdSpi
{
public:
	CMdUserApi(char *flowpath, char *servername);
	virtual ~CMdUserApi(void);

	void Connect(const string& szAddresses, const string& szBrokerId, const string& szInvestorId, const string& szPassword);
	void Disconnect();

	void Subscribe(const string& szInstrumentIDs);
	void Unsubscribe(const string& szInstrumentIDs);

	void SubscribeQuote(const string& szInstrumentIDs);
	void UnsubscribeQuote(const string& szInstrumentIDs);

private:
	//订阅行情
	void Subscribe(const set<string>& instrumentIDs);
	void SubscribeQuote(const set<string>& instrumentIDs);
	//登录请求
	void ReqUserLogin();

	//根据OnFrontDisconnected(int nReason)的值填上错误消息
	void GetOnFrontDisconnectedMsg(CThostFtdcRspInfoField* pRspInfo);

	//12 callback functions in CThostFtdcMdSpi
	//these functions will only be called by the CTP server.
	//the user defined callback function will be called in the following functions.
	virtual void OnFrontConnected();
	virtual void OnFrontDisconnected(int nReason);
	virtual void OnHeartBeatWarning(int nTimeLapse);
	virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	virtual void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	virtual void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	virtual void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	virtual void OnRspSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	virtual void OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData);
	virtual void OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp);

	//检查是否出错
	bool IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);//将出错消息送到消息队列
	bool IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo);//不送出错消息


public:
	//12 callback register functions 
	void RegisterCallback_ofc(fnOnFrontConnected pCallback) { m_fnOnFrontConnected = pCallback; }
	void RegisterCallback_ofd(fnOnFrontDisconnected pCallback) { m_fnOnFrontDisconnected = pCallback; }
	void RegisterCallback_ohb(fnOnHeartBeatWarning pCallback) { m_fnOnHeartBeatWarning = pCallback; }
	void RegisterCallback_oruli(fnOnRspUserLogin pCallback) { m_fnOnRspUserLogin = pCallback; }
	void RegisterCallback_orulo(fnOnRspUserLogout pCallback) { m_fnOnRspUserLogout = pCallback; }
	void RegisterCallback_ore(fnOnRspError pCallback) { m_fnOnRspError = pCallback; }
	void RegisterCallback_orsmd(fnOnRspSubMarketData pCallback) { m_fnOnRspSubMarketData = pCallback; }
	void RegisterCallback_orusmd(fnOnRspUnSubMarketData pCallback) { m_fnOnRspUnSubMarketData = pCallback; }
	void RegisterCallback_orsfqr(fnOnRspSubForQuoteRsp pCallback) { m_fnOnRspSubForQuoteRsp = pCallback; }
	void RegisterCallback_orusfqr(fnOnRspUnSubForQuoteRsp pCallback) { m_fnOnRspUnSubForQuoteRsp = pCallback; }
	void RegisterCallback_ordmd(fnOnRtnDepthMarketData pCallback) { m_fnOnRtnDepthMarketData = pCallback; }
	void RegisterCallback_orfqr(fnOnRtnForQuoteRsp pCallback) { m_fnOnRtnForQuoteRsp = pCallback; }

private:
	mutex						m_csMapInstrumentIDs;
	mutex						m_csMapQuoteInstrumentIDs;

	int							m_nRequestID;
	
	set<string>					m_setInstrumentIDs;		//正在订阅的合约
	set<string>					m_setQuoteInstrumentIDs;		//正在订阅的合约
	CThostFtdcMdApi*			m_pApi;					//行情API

	char *						m_szPath;				//生成配置文件的路径
	char *						m_server;
	set<string>					m_arrAddresses;			//服务器地址
	string						m_szBrokerId;			//期商ID
	string						m_szInvestorId;			//投资者ID
	string						m_szPassword;			//密码

	fnOnFrontConnected m_fnOnFrontConnected;
	fnOnFrontDisconnected m_fnOnFrontDisconnected;
	fnOnHeartBeatWarning m_fnOnHeartBeatWarning;
	fnOnRspUserLogin m_fnOnRspUserLogin;
	fnOnRspUserLogout m_fnOnRspUserLogout;
	fnOnRspError m_fnOnRspError;
	fnOnRspSubMarketData m_fnOnRspSubMarketData;
	fnOnRspUnSubMarketData m_fnOnRspUnSubMarketData;
	fnOnRspSubForQuoteRsp m_fnOnRspSubForQuoteRsp;
	fnOnRspUnSubForQuoteRsp m_fnOnRspUnSubForQuoteRsp;
	fnOnRtnDepthMarketData m_fnOnRtnDepthMarketData;
	fnOnRtnForQuoteRsp m_fnOnRtnForQuoteRsp;
	
};

#endif
