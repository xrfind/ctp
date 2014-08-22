#ifndef CTP_C_API_CCTPMSGQUEUE
#define CTP_C_API_CCTPMSGQUEUE

#include "header.h"

class CCTPMsgQueue
{
	//响应队列中可能出现的消息类型（按字母排序）
	enum EnumMsgType
	{
		E_fnOnConnect,	
		E_fnOnDisconnect,
		E_fnOnErrRtnOrderAction,
		E_fnOnErrRtnOrderInsert,
		E_fnOnErrRtnQuoteAction,
		E_fnOnErrRtnQuoteInsert,
		E_fnOnRspError,
		E_fnOnRspOrderAction,
		E_fnOnRspOrderInsert,
		E_fnOnRspQryDepthMarketData,
		E_fnOnRspQryInstrument,
		E_fnOnRspQryInstrumentCommissionRate,
		E_fnOnRspQryInstrumentMarginRate,
		E_fnOnRspQryInvestorPosition,
		E_fnOnRspQryInvestorPositionDetail,
		E_fnOnRspQryOrder,
		E_fnOnRspQryTrade,
		E_fnOnRspQrySettlementInfo,
		E_fnOnRspQryTradingAccount,
		E_fnOnRspQuoteAction,
		E_fnOnRspQuoteInsert,
		E_fnOnRtnDepthMarketData,
		E_fnOnRtnForQuoteRsp,
		E_fnOnRtnInstrumentStatus,
		E_fnOnRtnOrder,
		E_fnOnRtnQuote,
		E_fnOnRtnTrade,
	};

	struct SMsgItem
	{
		EnumMsgType							type;			//消息类型
		void*								pApi;			//指向类对象的指针
		CThostFtdcRspInfoField				RspInfo;		//响应信息
		bool								bIsLast;		//是否最后一个包
		union{
			int								nRequestID;
			ConnectionStatus				Status;
		};		
		union{
			CThostFtdcDepthMarketDataField			DepthMarketData;	//E_fnOnRspQryDepthMarketData与E_fnOnRtnDepthMarketData返回的数据格式相同
			CThostFtdcForQuoteRspField				ForQuoteRsp;
			CThostFtdcQuoteActionField				QuoteAction;
			CThostFtdcInputQuoteField				InputQuote;
			CThostFtdcInputQuoteActionField			InputQuoteAction;
			CThostFtdcInputOrderField				InputOrder;
			CThostFtdcInputOrderActionField			InputOrderAction;
			CThostFtdcInstrumentField				Instrument;
			CThostFtdcInstrumentCommissionRateField	InstrumentCommissionRate;
			CThostFtdcInstrumentMarginRateField		InstrumentMarginRate;
			CThostFtdcInstrumentStatusField			InstrumentStatus;
			CThostFtdcInvestorPositionField			InvestorPosition;
			CThostFtdcInvestorPositionDetailField	InvestorPositionDetail;
			CThostFtdcOrderField					Order;
			CThostFtdcOrderActionField				OrderAction;
			CThostFtdcRspUserLoginField				RspUserLogin;
			CThostFtdcTradeField					Trade;
			CThostFtdcSettlementInfoField			SettlementInfo;
			CThostFtdcTradingAccountField			TradingAccount;
			CThostFtdcQuoteField					Quote;
		};
	};

public:
	CCTPMsgQueue(void)
	{
		//m_hThread = NULL;
		m_bRunning = false;

		//回调函数地址指针
		m_fnOnConnect = NULL;
		m_fnOnDisconnect = NULL;
		m_fnOnErrRtnOrderAction = NULL;
		m_fnOnErrRtnOrderInsert = NULL;
		m_fnOnErrRtnQuoteAction = NULL;
		m_fnOnErrRtnQuoteInsert = NULL;
		m_fnOnRspError = NULL;
		m_fnOnRspOrderAction = NULL;
		m_fnOnRspOrderInsert = NULL;
		m_fnOnRspQryDepthMarketData = NULL;
		m_fnOnRspQryInstrument = NULL;
		m_fnOnRspQryInstrumentCommissionRate = NULL;
		m_fnOnRspQryInstrumentMarginRate = NULL;
		m_fnOnRspQryInvestorPosition = NULL;
		m_fnOnRspQryInvestorPositionDetail = NULL;
		m_fnOnRspQryOrder = NULL;
		m_fnOnRspQryTrade = NULL;
		m_fnOnRspQrySettlementInfo = NULL;
		m_fnOnRspQryTradingAccount = NULL;
		m_fnOnRspQuoteAction = NULL;
		m_fnOnRspQuoteInsert = NULL;
		m_fnOnRtnDepthMarketData = NULL;
		m_fnOnRtnForQuoteRsp = NULL;
		m_fnOnRtnInstrumentStatus = NULL;
		m_fnOnRtnOrder = NULL;
		m_fnOnRtnQuote = NULL;
		m_fnOnRtnTrade = NULL;

		//m_hEvent = CreateEvent(NULL,FALSE,FALSE,NULL);
	}
	virtual ~CCTPMsgQueue(void)
	{
		//StopThread();
		Clear();

		//CloseHandle(m_hEvent);
	}

public:
	//清空队列
	void Clear();

	//可以由外部发起，顺序处理队列触发回调函数
	bool Process();

	//由内部启动线程，内部主动调用Process触发回调
	void StartThread();
	void StopThread();

	//将外部的函数地址注册到队列(按字母排序)
	void RegisterCallback(fnOnConnect pCallback){ m_fnOnConnect = pCallback; }
	void RegisterCallback(fnOnDisconnect pCallback){ m_fnOnDisconnect = pCallback; }
	void RegisterCallback(fnOnErrRtnOrderAction pCallback){ m_fnOnErrRtnOrderAction = pCallback; }
	void RegisterCallback(fnOnErrRtnOrderInsert pCallback){ m_fnOnErrRtnOrderInsert = pCallback; }
	void RegisterCallback(fnOnErrRtnQuoteAction pCallback){ m_fnOnErrRtnQuoteAction = pCallback; }
	void RegisterCallback(fnOnErrRtnQuoteInsert pCallback){ m_fnOnErrRtnQuoteInsert = pCallback; }
	void RegisterCallback(fnOnRspError pCallback){ m_fnOnRspError = pCallback; }
	void RegisterCallback(fnOnRspOrderAction pCallback){ m_fnOnRspOrderAction = pCallback; }
	void RegisterCallback(fnOnRspOrderInsert pCallback){ m_fnOnRspOrderInsert = pCallback; }
	void RegisterCallback(fnOnRspQryDepthMarketData pCallback){ m_fnOnRspQryDepthMarketData = pCallback; }
	void RegisterCallback(fnOnRspQryInstrument pCallback){ m_fnOnRspQryInstrument = pCallback; }
	void RegisterCallback(fnOnRspQryInstrumentCommissionRate pCallback){ m_fnOnRspQryInstrumentCommissionRate = pCallback; }
	void RegisterCallback(fnOnRspQryInstrumentMarginRate pCallback){ m_fnOnRspQryInstrumentMarginRate = pCallback; }
	void RegisterCallback(fnOnRspQryInvestorPosition pCallback){ m_fnOnRspQryInvestorPosition = pCallback; }
	void RegisterCallback(fnOnRspQryInvestorPositionDetail pCallback){ m_fnOnRspQryInvestorPositionDetail = pCallback; }
	void RegisterCallback(fnOnRspQryOrder pCallback){ m_fnOnRspQryOrder = pCallback; }
	void RegisterCallback(fnOnRspQryTrade pCallback){ m_fnOnRspQryTrade = pCallback; }
	void RegisterCallback(fnOnRspQrySettlementInfo pCallback){ m_fnOnRspQrySettlementInfo = pCallback; }
	void RegisterCallback(fnOnRspQryTradingAccount pCallback){ m_fnOnRspQryTradingAccount = pCallback; }
	void RegisterCallback(fnOnRspQuoteAction pCallback){ m_fnOnRspQuoteAction = pCallback; }
	void RegisterCallback(fnOnRspQuoteInsert pCallback){ m_fnOnRspQuoteInsert = pCallback; }
	void RegisterCallback(fnOnRtnDepthMarketData pCallback){ m_fnOnRtnDepthMarketData = pCallback; }
	void RegisterCallback(fnOnRtnForQuoteRsp pCallback){ m_fnOnRtnForQuoteRsp = pCallback; }
	void RegisterCallback(fnOnRtnInstrumentStatus pCallback){ m_fnOnRtnInstrumentStatus = pCallback; }
	void RegisterCallback(fnOnRtnOrder pCallback){ m_fnOnRtnOrder = pCallback; }
	void RegisterCallback(fnOnRtnQuote pCallback){ m_fnOnRtnQuote = pCallback; }
	void RegisterCallback(fnOnRtnTrade pCallback){ m_fnOnRtnTrade = pCallback; }

	//响应结果处理后入队列(按字母排序)
	void Input_OnConnect(void* pApi,CThostFtdcRspUserLoginField *pRspUserLogin,ConnectionStatus result);
	void Input_OnDisconnect(void* pApi,CThostFtdcRspInfoField *pRspInfo,ConnectionStatus step);
	void Input_OnErrRtnOrderAction(void* pTraderApi,CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo);
	void Input_OnErrRtnOrderInsert(void* pTraderApi,CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo);
	void Input_OnErrRtnQuoteAction(void* pTraderApi, CThostFtdcQuoteActionField *pQuoteAction, CThostFtdcRspInfoField *pRspInfo);
	void Input_OnErrRtnQuoteInsert(void* pTraderApi, CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo);
	void Input_OnRspError(void* pApi,CThostFtdcRspInfoField* pRspInfo,int nRequestID,bool bIsLast);
	void Input_OnRspOrderAction(void* pTraderApi,CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	void Input_OnRspOrderInsert(void* pTraderApi,CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	void Input_OnRspQryDepthMarketData(void* pTraderApi,CThostFtdcDepthMarketDataField *pDepthMarketData, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	void Input_OnRspQryInvestorPosition(void* pTraderApi,CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	void Input_OnRspQryInvestorPositionDetail(void* pTraderApi,CThostFtdcInvestorPositionDetailField *pInvestorPositionDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	void Input_OnRspQryInstrument(void* pTraderApi,CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	void Input_OnRspQryInstrumentCommissionRate(void* pTraderApi,CThostFtdcInstrumentCommissionRateField *pInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	void Input_OnRspQryInstrumentMarginRate(void* pTraderApi,CThostFtdcInstrumentMarginRateField *pInstrumentMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	void Input_OnRspQryOrder(void* pTraderApi,CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	void Input_OnRspQryTrade(void* pTraderApi,CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	void Input_OnRspQrySettlementInfo(void* pTraderApi, CThostFtdcSettlementInfoField *pSettlementInfo, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	void Input_OnRspQryTradingAccount(void* pTraderApi,CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	void Input_OnRspQuoteAction(void* pTraderApi, CThostFtdcInputQuoteActionField *pInputQuoteAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	void Input_OnRspQuoteInsert(void* pTraderApi, CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	void Input_OnRtnDepthMarketData(void* pMdUserApi, CThostFtdcDepthMarketDataField *pDepthMarketData);
	void Input_OnRtnForQuoteRsp(void* pMdUserApi, CThostFtdcForQuoteRspField *pForQuoteRsp);
	void Input_OnRtnInstrumentStatus(void* pTraderApi,CThostFtdcInstrumentStatusField *pInstrumentStatus);
	void Input_OnRtnOrder(void* pTraderApi,CThostFtdcOrderField *pOrder);
	void Input_OnRtnQuote(void* pTraderApi, CThostFtdcQuoteField *pQuote);
	void Input_OnRtnTrade(void* pTraderApi,CThostFtdcTradeField *pTrade);
	
private:
	//friend DWORD WINAPI ProcessThread(LPVOID lpParam);
	//void RunInThread();

	//响应结果直接入队列
	void _Input_MD(SMsgItem* pMsgItem);
	void _Input_TD(SMsgItem* pMsgItem);
	//队列中的消息判断分发
	void _Output_MD(SMsgItem* pMsgItem);
	void _Output_TD(SMsgItem* pMsgItem);

	//响应输出
	void Output_OnConnect(SMsgItem* pItem)
	{
		if(m_fnOnConnect)
			(*m_fnOnConnect)(pItem->pApi,&pItem->RspUserLogin,pItem->Status);
	}
	void Output_OnDisconnect(SMsgItem* pItem)
	{
		if(m_fnOnDisconnect)
			(*m_fnOnDisconnect)(pItem->pApi,&pItem->RspInfo,pItem->Status);
	}
	void Output_OnErrRtnOrderAction(SMsgItem* pItem)
	{
		if(m_fnOnErrRtnOrderAction)
			(*m_fnOnErrRtnOrderAction)(pItem->pApi,&pItem->OrderAction,&pItem->RspInfo);
	}
	void Output_OnErrRtnOrderInsert(SMsgItem* pItem)
	{
		if(m_fnOnErrRtnOrderInsert)
			(*m_fnOnErrRtnOrderInsert)(pItem->pApi,&pItem->InputOrder,&pItem->RspInfo);
	}
	void Output_OnErrRtnQuoteAction(SMsgItem* pItem)
	{
		if (m_fnOnErrRtnQuoteAction)
			(*m_fnOnErrRtnQuoteAction)(pItem->pApi, &pItem->QuoteAction, &pItem->RspInfo);
	}
	void Output_OnErrRtnQuoteInsert(SMsgItem* pItem)
	{
		if (m_fnOnErrRtnQuoteInsert)
			(*m_fnOnErrRtnQuoteInsert)(pItem->pApi, &pItem->InputQuote, &pItem->RspInfo);
	}
	void Output_OnRspError(SMsgItem* pItem)
	{
		if(m_fnOnRspError)
			(*m_fnOnRspError)(pItem->pApi,&pItem->RspInfo,pItem->nRequestID,pItem->bIsLast);
	}
	void Output_OnRspOrderAction(SMsgItem* pItem)
	{
		if(m_fnOnRspOrderAction)
			(*m_fnOnRspOrderAction)(pItem->pApi,&pItem->InputOrderAction,&pItem->RspInfo,pItem->nRequestID,pItem->bIsLast);
	}
	void Output_OnRspOrderInsert(SMsgItem* pItem)
	{
		if(m_fnOnRspOrderInsert)
			(*m_fnOnRspOrderInsert)(pItem->pApi,&pItem->InputOrder,&pItem->RspInfo,pItem->nRequestID,pItem->bIsLast);
	}
	void Output_OnRspQryInvestorPosition(SMsgItem* pItem)
	{
		if(m_fnOnRspQryInvestorPosition)
			(*m_fnOnRspQryInvestorPosition)(pItem->pApi,&pItem->InvestorPosition,&pItem->RspInfo,pItem->nRequestID,pItem->bIsLast);
	}
	void Output_OnRspQryInvestorPositionDetail(SMsgItem* pItem)
	{
		if(m_fnOnRspQryInvestorPositionDetail)
			(*m_fnOnRspQryInvestorPositionDetail)(pItem->pApi,&pItem->InvestorPositionDetail,&pItem->RspInfo,pItem->nRequestID,pItem->bIsLast);
	}
	void Output_OnRspQryDepthMarketData(SMsgItem* pItem)
	{
		if(m_fnOnRspQryDepthMarketData)
			(*m_fnOnRspQryDepthMarketData)(pItem->pApi,&pItem->DepthMarketData,&pItem->RspInfo,pItem->nRequestID,pItem->bIsLast);
	}
	void Output_OnRspQryInstrument(SMsgItem* pItem)
	{
		if(m_fnOnRspQryInstrument)
			(*m_fnOnRspQryInstrument)(pItem->pApi,&pItem->Instrument,&pItem->RspInfo,pItem->nRequestID,pItem->bIsLast);
	}
	void Output_OnRspQryInstrumentCommissionRate(SMsgItem* pItem)
	{
		if(m_fnOnRspQryInstrumentCommissionRate)
			(*m_fnOnRspQryInstrumentCommissionRate)(pItem->pApi,&pItem->InstrumentCommissionRate,&pItem->RspInfo,pItem->nRequestID,pItem->bIsLast);
	}
	void Output_OnRspQryInstrumentMarginRate(SMsgItem* pItem)
	{
		if(m_fnOnRspQryInstrumentMarginRate)
			(*m_fnOnRspQryInstrumentMarginRate)(pItem->pApi,&pItem->InstrumentMarginRate,&pItem->RspInfo,pItem->nRequestID,pItem->bIsLast);
	}
	void Output_OnRspQryOrder(SMsgItem* pItem)
	{
		if(m_fnOnRspQryOrder)
			(*m_fnOnRspQryOrder)(pItem->pApi,&pItem->Order,&pItem->RspInfo,pItem->nRequestID,pItem->bIsLast);
	}
	void Output_OnRspQryTrade(SMsgItem* pItem)
	{
		if(m_fnOnRspQryTrade)
			(*m_fnOnRspQryTrade)(pItem->pApi,&pItem->Trade,&pItem->RspInfo,pItem->nRequestID,pItem->bIsLast);
	}
	void Output_OnRspQuoteAction(SMsgItem* pItem)
	{
		if (m_fnOnRspQuoteAction)
			(*m_fnOnRspQuoteAction)(pItem->pApi, &pItem->InputQuoteAction, &pItem->RspInfo, pItem->nRequestID, pItem->bIsLast);
	}
	void Output_OnRspQuoteInsert(SMsgItem* pItem)
	{
		if (m_fnOnRspQuoteInsert)
			(*m_fnOnRspQuoteInsert)(pItem->pApi, &pItem->InputQuote, &pItem->RspInfo, pItem->nRequestID, pItem->bIsLast);
	}
	void Output_OnRspQryTradingAccount(SMsgItem* pItem)
	{
		if(m_fnOnRspQryTradingAccount)
			(*m_fnOnRspQryTradingAccount)(pItem->pApi,&pItem->TradingAccount,&pItem->RspInfo,pItem->nRequestID,pItem->bIsLast);
	}
	void Output_OnRtnDepthMarketData(SMsgItem* pItem)
	{
		if(m_fnOnRtnDepthMarketData)
			(*m_fnOnRtnDepthMarketData)(pItem->pApi,&pItem->DepthMarketData);
	}
	void Output_OnRtnForQuoteRsp(SMsgItem* pItem)
	{
		if (m_fnOnRtnForQuoteRsp)
			(*m_fnOnRtnForQuoteRsp)(pItem->pApi, &pItem->ForQuoteRsp);
	}
	void Output_OnRtnInstrumentStatus(SMsgItem* pItem)
	{
		if(m_fnOnRtnInstrumentStatus)
			(*m_fnOnRtnInstrumentStatus)(pItem->pApi,&pItem->InstrumentStatus);
	}
	void Output_OnRtnOrder(SMsgItem* pItem)
	{
		if(m_fnOnRtnOrder)
			(*m_fnOnRtnOrder)(pItem->pApi,&pItem->Order);
	}
	void Output_OnRtnQuote(SMsgItem* pItem)
	{
		if (m_fnOnRtnQuote)
			(*m_fnOnRtnQuote)(pItem->pApi, &pItem->Quote);
	}
	void Output_OnRtnTrade(SMsgItem* pItem)
	{
		if(m_fnOnRtnTrade)
			(*m_fnOnRtnTrade)(pItem->pApi,&pItem->Trade);
	}
	void Output_OnRspQrySettlementInfo(SMsgItem* pItem)
	{
		if (m_fnOnRspQrySettlementInfo)
			(*m_fnOnRspQrySettlementInfo)(pItem->pApi, &pItem->SettlementInfo, &pItem->RspInfo, pItem->nRequestID, pItem->bIsLast);
	}

private:
	volatile bool				m_bRunning;
	//HANDLE						m_hEvent;
	//HANDLE						m_hThread;

	MSQueue<SMsgItem*>			m_queue_MD;			//响应队列
	MSQueue<SMsgItem*>			m_queue_TD;			//响应队列

	//回调函数指针（按字母排序）
	fnOnConnect							m_fnOnConnect;
	fnOnDisconnect						m_fnOnDisconnect;
	fnOnErrRtnOrderAction				m_fnOnErrRtnOrderAction;
	fnOnErrRtnOrderInsert				m_fnOnErrRtnOrderInsert;
	fnOnErrRtnQuoteAction				m_fnOnErrRtnQuoteAction;
	fnOnErrRtnQuoteInsert				m_fnOnErrRtnQuoteInsert;
	fnOnRspError						m_fnOnRspError;
	fnOnRspOrderAction					m_fnOnRspOrderAction;
	fnOnRspOrderInsert					m_fnOnRspOrderInsert;
	fnOnRspQryDepthMarketData			m_fnOnRspQryDepthMarketData;
	fnOnRspQryInstrument				m_fnOnRspQryInstrument;
	fnOnRspQryInstrumentCommissionRate	m_fnOnRspQryInstrumentCommissionRate;
	fnOnRspQryInstrumentMarginRate		m_fnOnRspQryInstrumentMarginRate;
	fnOnRspQryInvestorPosition			m_fnOnRspQryInvestorPosition;
	fnOnRspQryInvestorPositionDetail	m_fnOnRspQryInvestorPositionDetail;
	fnOnRspQryOrder						m_fnOnRspQryOrder;
	fnOnRspQryTrade						m_fnOnRspQryTrade;
	fnOnRspQrySettlementInfo			m_fnOnRspQrySettlementInfo;
	fnOnRspQryTradingAccount			m_fnOnRspQryTradingAccount;
	fnOnRspQuoteAction					m_fnOnRspQuoteAction;
	fnOnRspQuoteInsert					m_fnOnRspQuoteInsert;
	fnOnRtnDepthMarketData				m_fnOnRtnDepthMarketData;
	fnOnRtnForQuoteRsp					m_fnOnRtnForQuoteRsp;
	fnOnRtnInstrumentStatus				m_fnOnRtnInstrumentStatus;
	fnOnRtnOrder						m_fnOnRtnOrder;
	fnOnRtnQuote						m_fnOnRtnQuote;
	fnOnRtnTrade						m_fnOnRtnTrade;
};

#endif
